#include <SFML/Graphics.hpp>

struct Fruit {
  int x;
  int y;
} fruit;

struct Snake {
  int x;
  int y;
} snake;

int main() {
  int grid[40][30];
  for(int i = 0; i < 40; i++) for(int j = 0; j < 30; j++) grid[i][j] = 0;

  sf::RenderWindow window(sf::VideoMode(800,600), "Snake Game!", sf::Style::Titlebar|sf::Style::Close);

  sf::RectangleShape blocks[40][30];
  for(int i = 0; i < 40; i++) for(int j = 0; j < 30; j++) {
      blocks[i][j].setSize(sf::Vector2f(20.0f, 20.0f));
      blocks[i][j].setPosition(i*20, j*20);
      blocks[i][j].setOutlineThickness(1.0f);
      blocks[i][j].setOutlineColor(sf::Color(115, 115, 115));
    }

  sf::RectangleShape walls[4];
  // Upper Wall
  walls[0].setPosition(0.0f, 0.0f);
  walls[0].setSize(sf::Vector2f(800.0f, 1.0f));
  walls[0].setFillColor(sf::Color::Red);
  // Right Wall
  walls[1].setPosition(799.0f, 0.0f);
  walls[1].setSize(sf::Vector2f(1.0f, 600.0f));
  walls[1].setFillColor(sf::Color::Red);
  // Bottom Wall
  walls[2].setPosition(0.0f, 599.0f);
  walls[2].setSize(sf::Vector2f(800.0f, 1.0f));
  walls[2].setFillColor(sf::Color::Red);
  // Left Wall
  walls[3].setPosition(0.0f, 0.0f);
  walls[3].setSize(sf::Vector2f(1.0f, 600.0f));
  walls[3].setFillColor(sf::Color::Red);

  srand((int)time(0));
  fruit.x = rand() % 40;
  fruit.y = rand() % 30;

  sf::Clock clock;
  float timer = 0.0f, delay = 0.1f;

  while(window.isOpen()) {
    float time = clock.getElapsedTime().asSeconds();

    clock.restart();
    timer += time;
    
    sf::Event event;

    while(window.pollEvent(event)) {
      if(event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) window.close();
    }

    for(int i = 0; i < 40; i++) for(int j = 0; j <30; j++) {
	if(i == fruit.x && j == fruit.y) blocks[i][j].setFillColor(sf::Color(0, 204, 0));
	else blocks[i][j].setFillColor(sf::Color::Black);
      }

    window.clear(sf::Color::White);
    for(int i = 0; i < 40; i++) for(int j = 0; j < 30; j++) window.draw(blocks[i][j]);
    for(int i = 0; i < 4; i++) window.draw(walls[i]);
    window.display();
  }

  return EXIT_SUCCESS;
}
