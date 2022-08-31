#include "header.h"

void GameUtilities::start() {
  GameUtilities::generateGrid();

  m_fruit.x = 6;
  m_fruit.y = 15;

  Snake segment;
  segment.x = 6;
  segment.y = 6;
  for(int i = 0; i < 4; i++) {
    m_snake.push_back(segment);
    segment.y -= 1;
  }

  sf::Clock clock;
  float timer = 0.0f, delay = 0.2f;

  while(m_window.isOpen()) {
    float time = clock.getElapsedTime().asSeconds();

    clock.restart();
    timer += time;

    if(timer > delay) {
      GameUtilities::move();
      timer = 0.0f;
    }

    GameUtilities::handleEvent();

    for(int i = 0; i < 40; i++) {
      for(int j = 0; j < 30; j++) {
	if(i == m_fruit.x && j == m_fruit.y) m_blocks[i][j].setFillColor(sf::Color(0, 204, 0));
	else if(i == m_snake.at(0).x && j == m_snake.at(0).y) m_blocks[i][j].setFillColor(sf::Color(255, 102, 102));
	else m_blocks[i][j].setFillColor(sf::Color::Black);
      }
    }
    for(int i = 1; i < m_snake.size(); i++) {
      m_blocks[m_snake.at(i).x][m_snake.at(i).y].setFillColor(sf::Color::White);
    }
    
    GameUtilities::draw();
  }
}
