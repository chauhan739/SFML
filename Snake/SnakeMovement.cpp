#include "header.h"

void GameUtilities::move() {
  srand((unsigned)time(0));
  
  // m_snake.front() is head of the snake
  Block segment = m_snake.front();

  if(m_playingGame) {
    if(m_currDirection == Direction::RIGHT) segment.x++;
    if(m_currDirection == Direction::DOWN) segment.y++;
    if(m_currDirection == Direction::LEFT) segment.x--;
    if(m_currDirection == Direction::UP) segment.y--;

    if(segment.x == m_fruit.x && segment.y == m_fruit.y) {
      m_eatingFruit.play();
    
      m_fruit.x = rand() % 40;
      m_fruit.y = rand() % 30;
    
      m_snake.push_front(segment);
    }
    else {
      m_snake.push_front(segment);
      m_snake.pop_back();
    }
  }
}
