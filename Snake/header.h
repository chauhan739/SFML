#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Contains coordinates of fruits dispalyed on grid
 **/
struct Fruit {
  int x;
  int y;
};

/**
 * Contains coordinates of all segments of snake
 **/
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
   /**
    * Constructor. Implementation present in Init.cpp
    **/
  GameUtilities();

  /**
   * Funtion calling all other member functions except constructor.
   * Implementation present in RunAppliction.cpp
   **/
  void start();

  /**
   * Function creating playing field.
   * Implementation present in Gtid.cpp
   **/
  void generateGrid();

  /**
   * Function for handling user's event.
   * Implementation present in EventHandler.cpp
   **/
  void handleEvent();

  /**
   * Function for drawing all graphics on the screen.
   * Implementation present in Display.cpp
   **/
  void draw();
};
