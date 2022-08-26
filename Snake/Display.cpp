#include "header.h"

void GameUtilities::draw() {
  m_window.clear(sf::Color::White);

  for(int i = 0; i < 40; i++) for(int j = 0; j < 30; j++) m_window.draw(m_blocks[i][j]);
  for(int i = 0; i < 4; i++) m_window.draw(m_walls[i]);

  m_window.display();
}
