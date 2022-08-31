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

/**
 * Contains information about the current direction
 * in which the snake is going
 **/
enum Direction {
  RIGHT = 1,

  DOWN,

  LEFT,

  UP
};

class GameUtilities {
 private:
  sf::RenderWindow m_window;
  
  sf::RectangleShape m_blocks[40][30], m_walls[4];

  Fruit m_fruit;

  std::vector<Snake> m_snake;

  Direction m_currDirection;

  sf::Font m_font;

  sf::Clock m_clock;

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
   * Function for handling snake movement.
   * Implementation present in SnakeMovement.cpp
   **/
  void move();

  /**
   * Function for drawing all graphics on the screen.
   * Implementation present in Display.cpp
   **/
  void draw();
};
