#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>

/**
 * Represent individual block of the grid
 **/
struct Block {
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

  Block m_fruit;

  std::deque<Block> m_snake;

  Direction m_currDirection;

  sf::Font m_font;

  sf::SoundBuffer m_eatBuffer;
  sf::Sound m_eatingFruit;

  bool m_playingGame;

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
