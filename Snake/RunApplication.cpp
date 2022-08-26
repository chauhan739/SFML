#include "header.h"

void GameUtilities::start() {
  GameUtilities::generateGrid();

  srand((int)time(0));
  m_fruit.x = rand() % 40;
  m_fruit.y = rand() % 30;

  m_timer = 0.0f;
  m_delay = 0.1f;

  while(m_window.isOpen()) {
    float time = m_clock.getElapsedTime().asSeconds();

    m_clock.restart();
    m_timer += time;

    GameUtilities::handleEvent();

    for(int i = 0; i < 40; i++) {
      for(int j = 0; j < 30; j++) {
	if(i == m_fruit.x && j == m_fruit.y) m_blocks[i][j].setFillColor(sf::Color(0, 204, 0));
	else m_blocks[i][j].setFillColor(sf::Color::Black);
      }
    }

    GameUtilities::draw();
  }
}
