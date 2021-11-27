#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

void updateBranches(int);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side{ LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main(){
  VideoMode vm(960, 540);
  RenderWindow window(vm, "TimberMan!!!", Style::Titlebar);

  Texture textureBackground;
  textureBackground.loadFromFile("../assets/graphics/Background.png");
  Sprite spriteBackground;
  spriteBackground.setTexture(textureBackground);
  spriteBackground.setPosition(0.0f, 0.0f);

  Texture textureTree;
  textureTree.loadFromFile("../assets/graphics/BackgroundTree.png");
  Sprite spriteTree;
  spriteTree.setTexture(textureTree);
  spriteTree.setPosition(405.0f, 0.0f);

  Texture textureBee;
  textureBee.loadFromFile("../assets/graphics/Bee.png");
  Sprite spriteBee;
  spriteBee.setTexture(textureBee);
  spriteBee.setPosition(0, 400);
  bool beeActive = false;
  float beeSpeed = 0.0f;

  Texture textureCloud;
  textureCloud.loadFromFile("../assets/graphics/Cloud.png");
  Sprite spriteCloud1, spriteCloud2, spriteCloud3;
  spriteCloud1.setTexture(textureCloud);
  spriteCloud2.setTexture(textureCloud);
  spriteCloud3.setTexture(textureCloud);
  spriteCloud1.setPosition(0, 0);
  spriteCloud2.setPosition(0, 75);
  spriteCloud3.setPosition(0, 150);
  bool cloud1Active = false, cloud2Active = false, cloud3Active = false;
  float cloud1Speed = 0.0f, cloud2Speed = 0.0f, cloud3Speed = 0.0f;

  Clock clock;

  RectangleShape timeBar;
  float timeBarStartWidth = 200.0f;
  timeBar.setSize(Vector2f(timeBarStartWidth, 40.0f));
  timeBar.setPosition((960/2.0f) - (timeBarStartWidth/2), 490.0f /*540-50*/);
  timeBar.setFillColor(Color::Red);

  RectangleShape timeBarOutline;
  timeBarOutline.setSize(Vector2f(200.0f, 40.0f));
  timeBarOutline.setOutlineThickness(2.0f);
  timeBarOutline.setFillColor(Color::Transparent);
  timeBarOutline.setOutlineColor(Color::White);
  
  Time gameTimeTotal;
  float timeRemaining = 6.0f;
  float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
  timeBarOutline.setPosition(380.0f, 490.0f);

  bool paused = true;

  int score = 0;

  Font font;
  font.loadFromFile("../assets/font/special.ttf");

  Text messageText;
  messageText.setFont(font);
  messageText.setLetterSpacing(1.3f);
  messageText.setString("Press Enter to Start!");
  messageText.setCharacterSize(40);
  messageText.setOutlineThickness(1.0f);
  messageText.setFillColor(Color::Red);
  messageText.setOutlineColor(Color::White);
  // Centering messageText
  FloatRect textRect = messageText.getGlobalBounds();
  messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  messageText.setPosition(960 / 2.0f, 540 / 2.0f);

  Text scoreText;
  scoreText.setFont(font);
  scoreText.setLetterSpacing(1.3f);
  scoreText.setString("Score = 0");
  scoreText.setCharacterSize(50);
  scoreText.setOutlineThickness(2.0f);
  scoreText.setFillColor(Color::Red);
  scoreText.setOutlineColor(Color::White);
  scoreText.setPosition(10, 10);

  Texture textureBranch;
  textureBranch.loadFromFile("../assets/graphics/Branch.png");

  for(int i = 0; i < NUM_BRANCHES; i++){
    branches[i].setTexture(textureBranch);
    branches[i].setPosition(-1000, 1000);

    branches[i].setOrigin(110, 10);
  }

  // Prepare the player
  Texture texturePlayer;
  texturePlayer.loadFromFile("../assets/graphics/Player.png");
  Sprite spritePlayer;
  spritePlayer.setTexture(texturePlayer);
  spritePlayer.setPosition(290, 360);

  side playerSide = side::LEFT;

  // Prepare the gravestone
  Texture textureRIP;
  textureRIP.loadFromFile("../assets/graphics/Grave.png");
  Sprite spriteRIP;
  spriteRIP.setTexture(textureRIP);
  spriteRIP.setPosition(300, 430);
  
  // Prepare the axe
  Texture textureAxe;
  textureAxe.loadFromFile("../assets/graphics/Axe.png");
  Sprite spriteAxe;
  spriteAxe.setTexture(textureAxe);
  spriteAxe.setPosition(350, 415);

  const float AXE_POSITION_LEFT = 350.0f;
  const float AXE_POSITION_RIGHT = 537.5f;

  // Prepare the flying log
  Texture textureLog;
  textureLog.loadFromFile("../assets/graphics/Log.png");
  Sprite spriteLog;
  spriteLog.setTexture(textureLog);
  spriteLog.setPosition(405, 360);
  
  bool logActive = false;
  float logSpeedX = 500;
  float logSpeedY = -750;

  bool acceptInput = false;

  // Preparing the sounds
  SoundBuffer chopBuffer;
  chopBuffer.loadFromFile("../assets/audio/chop.wav");
  Sound chop;
  chop.setBuffer(chopBuffer);

  SoundBuffer deathBuffer;
  deathBuffer.loadFromFile("../assets/audio/death.wav");
  Sound death;
  death.setBuffer(deathBuffer);

  SoundBuffer ootBuffer;
  ootBuffer.loadFromFile("../assets/audio/out_of_time.wav");
  Sound outOfTime;
  outOfTime.setBuffer(ootBuffer);

  while(window.isOpen()){
    Event event;
    while(window.pollEvent(event)){
      if(event.type == Event::KeyReleased && !paused){
	acceptInput = true;
	spriteAxe.setPosition(1000.0f, spriteAxe.getPosition().y);
      }
    }
    
    if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

    if(Keyboard::isKeyPressed(Keyboard::Return)){
      paused = false;

      score = 0;
      timeRemaining = 6.0f;

      // Removing all the branches except the first one
      for(int i = 1; i < NUM_BRANCHES; i++) branchPositions[i] = side::NONE;

      // Hiding the gravestone
      spriteRIP.setPosition(675.0f, 2000.0f);

      // Default position of player
      spritePlayer.setPosition(290.0f, 360.0f);

      acceptInput = true;
    }

    if(acceptInput){
      // Handle the right cursor key
      if(Keyboard::isKeyPressed(Keyboard::Right)){
	playerSide = side::RIGHT;
	score++;
	timeRemaining += (2 / score) + 0.15;

	spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

	spritePlayer.setPosition(600.0f, 360.0f);

	updateBranches(score);

	spriteLog.setPosition(405.0f, 360.0f);
	logSpeedX = 2500.0f;
	logActive = true;

	acceptInput = false;

	chop.play();
      }

      // Handle the left cursor keyboard
      if(Keyboard::isKeyPressed(Keyboard::Left)){
	playerSide = side::LEFT;
	score++;
	timeRemaining += (2 / score) + 0.15;

	spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);

	spritePlayer.setPosition(290.0f, 360.0f);

	updateBranches(score);

	spriteLog.setPosition(405.0f, 360.0f);
	logSpeedX = 2500.0f;
	logActive = true;

	acceptInput = false;

	chop.play();
      }
    }

    // Updating the scene
    if(!paused){
      Time dt = clock.restart();
      
      timeRemaining -= dt.asSeconds();
      timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, 40.0f));

      if(timeRemaining <= 0.0f){
	paused = true;

	messageText.setString("Out of Time!!");
	messageText.setLetterSpacing(1.3f);

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	messageText.setPosition(960 / 2.0f, 540 / 2.0f);

	outOfTime.play();
      }
      
      // Set-up the bee
      if(!beeActive){
	srand((int)time(0));
	beeSpeed = (rand() % 100) + 100;

	srand((int)time(0) * 10);
	float height = (rand() % 250) + 250;
	spriteBee.setPosition(1000.0f, height);

	beeActive = true;
      }
      else{
	spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
	if(spriteBee.getPosition().y < -50.0f) beeActive = false;
      }

      // Manage the clouds
      // Cloud 1
      if(!cloud1Active){
	srand((int)time(0) * 10);
	cloud1Speed = (rand() % 100);

	srand((int)time(0) * 10);
	float height = (rand() % 75);
	spriteCloud1.setPosition(-100, height);

	cloud1Active = true;
      }
      else{
	spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);

	if(spriteCloud1.getPosition().x > 960) cloud1Active = false;
      }
      // Cloud 2
      if(!cloud2Active){
	srand((int)time(0) * 20);
	cloud2Speed = rand() % 200;

	srand((int)time(0) * 20);
	float height = (rand() % 150) - 75;
	spriteCloud2.setPosition(-100, height);

	cloud2Active = true;
      }
      else{
	spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);

	if(spriteCloud2.getPosition().x > 960) cloud2Active = false;
      }
      // Cloud 3
      if(!cloud3Active){
	srand((int)time(0) * 30);
	cloud3Speed = rand() % 300;

	srand((int)time(0) * 30);
	float height = (rand() % 225) - 75;
	spriteCloud3.setPosition(-100, height);

	cloud3Active = true;
      }
      else{
	spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);

	if(spriteCloud3.getPosition().x > 960) cloud3Active = false;
      }

      // Update the Score Text
      std::stringstream ss;
      ss << "Score = " << score;
      scoreText.setString(ss.str());

      // Update the branch sprites
      for(int i = 0; i < NUM_BRANCHES; i++){
	float height = i * 75;

	if(branchPositions[i] == side::LEFT){
	  branches[i].setPosition(305.0f, height);
	  branches[i].setRotation(180.0f);
	}
	else if(branchPositions[i] == side::RIGHT){
	  branches[i].setPosition(665.0f, height);
	  branches[i].setRotation(0.0f);
	}
	else branches[i].setPosition(1500.0f, height);
      }

      if(logActive){
	spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

	if(spriteLog.getPosition().x < -50 || spriteLog.getPosition().x > 1000){
	  logActive = false;
	  spriteLog.setPosition(405.0f, 360.0f);
	}
      }

      // Handling Death
      if(branchPositions[5] == playerSide){
	paused = true;
	acceptInput = false;

	if(playerSide == side::LEFT) spriteRIP.setPosition(295.0f, 380.0f);
	else spriteRIP.setPosition(595.0f, 380.0f);

	spritePlayer.setPosition(1000.0f, 330.0f);

	messageText.setString("SQUISHED!!");
	messageText.setLetterSpacing(1.3f);
	
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(960 / 2.0f, 540 / 2.0f);

	death.play();
      }
    }
    
    // Drawing the scene
    window.clear();

    window.draw(spriteBackground);

    window.draw(spriteCloud1);
    window.draw(spriteCloud2);
    window.draw(spriteCloud3);

    for(int i = 0; i < NUM_BRANCHES; i++) window.draw(branches[i]);

    window.draw(spriteTree);

    window.draw(spritePlayer);

    window.draw(spriteAxe);

    window.draw(spriteLog);

    window.draw(spriteRIP);

    window.draw(spriteBee);

    window.draw(scoreText);

    window.draw(timeBarOutline);
    window.draw(timeBar);

    if(paused) window.draw(messageText);
    
    window.display();
  }
  return 0;
}

void updateBranches(int seed){
  for(int j = NUM_BRANCHES - 1; j > 0; j--) branchPositions[j] = branchPositions[j - 1];

  // Spawn a new branch at branches[0]
  srand((int)time(0) + seed);
  int r = (rand() % 5);

  switch(r){
  case 0:
    branchPositions[0] = side::LEFT;
    break;

  case 1:
    branchPositions[0] = side::RIGHT;
    break;

  default:
    branchPositions[0] = side::NONE;
    break;
  }
}

