#include "header.h"

void GameUtilities::generateGrid() {
  for(int i = 0; i < 40; i++) {
    for(int j = 0; j < 30; j++) {
      m_blocks[i][j].setSize(sf::Vector2f(20.0f, 20.0f));
      m_blocks[i][j].setPosition((float)i*20, (float)j*20);
      m_blocks[i][j].setOutlineThickness(1.0f);
      m_blocks[i][j].setOutlineColor(sf::Color(115, 115, 115));
    }
  }

  // Upper Wall
  m_walls[0].setPosition(0.0f, 0.0f);
  m_walls[0].setSize(sf::Vector2f(800.0f, 1.0f));
  // Right Wall
  m_walls[1].setPosition(799.0f, 0.0f);
  m_walls[1].setSize(sf::Vector2f(1.0f, 600.0f));
  // Bottom Wall
  m_walls[2].setPosition(0.0f, 599.0f);
  m_walls[2].setSize(sf::Vector2f(800.0f, 1.0f));
  // Left Wall
  m_walls[3].setPosition(0.0f, 0.0f);
  m_walls[3].setSize(sf::Vector2f(1.0f, 600.0f));

  for(int i = 0; i < 4; i++)
    m_walls[i].setFillColor(sf::Color::Red);
}
