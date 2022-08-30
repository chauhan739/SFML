#include "header.h"

void GameUtilities::move() {
  // m_snake.at(0) is head of the snake
  
  if(m_currDirection == Direction::RIGHT) m_snake.at(0).x++;
  if(m_currDirection == Direction::DOWN) m_snake.at(0).y++;
  if(m_currDirection == Direction::LEFT) m_snake.at(0).x--;
  if(m_currDirection == Direction::UP) m_snake.at(0).y--;
}
