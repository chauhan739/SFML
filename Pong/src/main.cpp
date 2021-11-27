#include "SFML/Graphics.hpp"

using namespace sf;

bool intersects(RectangleShape&, RectangleShape&);

int main(){
  const int width = 640;
  const int height = 480;

  RenderWindow window(VideoMode(width, height), "Pong!", Style::Default);
  window.setFramerateLimit(60);

  Font font;
  if(!font.loadFromFile("../assets/arial.ttf")) return EXIT_FAILURE;

  // setting up Title
  Text title("SFML Pong", font, 50);
  title.setOutlineThickness(2.0f);
  title.setOutlineColor(Color::Red);
  title.setFillColor(Color::Green);
  title.setStyle(Text::Italic);
  title.setPosition((title.getGlobalBounds().width) - title.getGlobalBounds().width/4, (height/2 - 20) - title.getGlobalBounds().height/2);

  // setting up my name
  Text name("Developed by chauhan739", font, 25);
  name.setOutlineThickness(1.0f);
  name.setOutlineColor(Color::Red);
  name.setFillColor(Color::Green);
  name.setStyle(Text::Italic);
  name.setPosition((name.getGlobalBounds().width) - 2*name.getGlobalBounds().width/5, (height/2 - 20) + title.getGlobalBounds().height - name.getGlobalBounds().height/2);

  RectangleShape paddleRight, paddleLeft, ball, upperWall, lowerWall, leftWall, rightWall;

  // setting up paddleRight
  paddleRight.setSize(Vector2f(10.0f, 40.0f));
  paddleRight.setFillColor(Color::White);
  paddleRight.setPosition(width-10-5, 220.0f);

  // setting up paddleLeft
  paddleLeft.setSize(Vector2f(10.0f, 40.0f));
  paddleLeft.setFillColor(Color::White);
  paddleLeft.setPosition(5.0f, 220.0f);

  // setting up ball
  ball.setSize(Vector2f(10.0f, 10.0f));
  ball.setFillColor(Color::Red);
  ball.setPosition(width/2, height/2);
  Vector2f ballSpeed(5.0f, 3.0f);

  // setting up upperWall
  upperWall.setSize(Vector2f(width, 3.0f));
  upperWall.setFillColor(Color::Yellow);
  upperWall.setPosition(0.0f, 0.0f);

  // setting up lowerWall
  lowerWall.setSize(Vector2f(width, 3.0f));
  lowerWall.setFillColor(Color::Yellow);
  lowerWall.setPosition(0.0f, height-3);

  // setting up leftWall
  leftWall.setSize(Vector2f(3.0f, height));
  leftWall.setFillColor(Color::Yellow);
  leftWall.setPosition(0.0f, 0.0f);

  // setting up rightWall
  rightWall.setSize(Vector2f(3.0f, height));
  rightWall.setFillColor(Color::Yellow);
  rightWall.setPosition(width-3, 0.0f);

  enum states{START, PLAYING};
  int gameStates = START;

  bool leftGoing = false, rightGoing = true, upGoing = false, downGoing = true;

  while(window.isOpen()){

    window.clear(Color::Black);
    
    window.draw(upperWall);
    window.draw(lowerWall);
    window.draw(leftWall);
    window.draw(rightWall);

    switch(gameStates){
    case START:
      window.draw(title);
      window.draw(name);
      break;
    case PLAYING:
      window.draw(ball);
      window.draw(paddleLeft);
      window.draw(paddleRight);
      break;
    }
    
    window.display();
    
    Event ev;

    while(window.pollEvent(ev)){
      if(ev.type == Event::Closed || ev.key.code == Keyboard::Escape) window.close();
      else if(ev.key.code == Keyboard::Enter) gameStates = PLAYING;
    }

    if(gameStates != PLAYING) continue;
    
    // paddleRight auto movement
    if(paddleRight.getPosition().y >= 3.0f || paddleRight.getPosition().y <= (height-43)) paddleRight.setPosition(width-10-5, ball.getPosition().y-20);

    // paddleLeft user defined movement
    if(Keyboard::isKeyPressed(Keyboard::Key::Up) && paddleLeft.getPosition().y >= 3.0f) paddleLeft.move(0.0f, -3.0f);
    else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && paddleLeft.getPosition().y <= 437.0f) paddleLeft.move(0.0f, 3.0f);

    /* paddleLeft auto movement (just for testing purpose)
       uncomment this code only during testing and comment again after testing */
    // if(paddleLeft.getPosition().y >= 3.0f || paddleLeft.getPosition().y <= (height-43)) paddleLeft.setPosition(5.0f, ball.getPosition().y-20);

    // ball hitting paddleRight and paddleLeft
    if(intersects(ball, paddleRight) && upGoing){
      ballSpeed.x = -ballSpeed.x;
      rightGoing = false;
      leftGoing = true;
    }
    else if(intersects(ball, paddleRight) && downGoing){
      ballSpeed.x = -ballSpeed.x;
      rightGoing = false;
      leftGoing = true;
    }
    else if(intersects(ball, paddleLeft) && upGoing){
      ballSpeed.x = -ballSpeed.x;
      rightGoing = true;
      leftGoing = false;
    }
    else if(intersects(ball, paddleLeft) && downGoing){
      ballSpeed.x = -ballSpeed.x;
      rightGoing = true;
      leftGoing = false;
    }

    // ball hitting upperWall and lowerWall
    if(intersects(ball, upperWall) && leftGoing){
      ballSpeed.y = -ballSpeed.y;
      upGoing = false;
      downGoing = true;
    }
    else if(intersects(ball, upperWall) && rightGoing){
      ballSpeed.y = -ballSpeed.y;
      upGoing = false;
      downGoing = true;
    }
    else if(intersects(ball, lowerWall) && leftGoing){
      ballSpeed.y = -ballSpeed.y;
      upGoing = true;
      downGoing = false;
    }
    else if(intersects(ball, lowerWall) && rightGoing){
      ballSpeed.y = -ballSpeed.y;
      upGoing = true;
      downGoing = false;
    }

    ball.move(ballSpeed);
  }

  return EXIT_SUCCESS;
}

bool intersects(RectangleShape& r1, RectangleShape& r2){
  FloatRect a = r1.getGlobalBounds();
  FloatRect b = r2.getGlobalBounds();

  return a.intersects(b);
}
