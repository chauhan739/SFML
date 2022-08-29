#include "header.h"

void GameUtilities::handleEvent() {
  sf::Event event;
  while(m_window.pollEvent(event)) {
    if(event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) m_window.close();
  }

  // Handling snake current movement direction
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_currDirection = Direction::LEFT;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_currDirection = Direction::RIGHT;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_currDirection = Direction::UP;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_currDirection = Direction::DOWN;
}
