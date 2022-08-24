#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Fruit {
  int x;
  int y;
};

struct Snake {
  int x;
  int y;
};

class GameUtilities {
 private:
  sf::RenderWindow m_window;
  
  sf::RectangleShape m_blocks[40][30], m_walls[4];

  Fruit m_fruit;

  std::vector<Snake> m_snake;

  sf::Font m_font;

  sf::Clock m_clock;
  float m_timer, m_delay;

 public:
  GameUtilities();

  void start();

  void generateGrid();

  void handleEvent();

  void draw();
};
