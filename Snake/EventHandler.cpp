#include "header.h"

void GameUtilities::handleEvent() {
  sf::Event event;
  while(m_window.pollEvent(event)) {
    if(event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) m_window.close();
  }

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !m_playingGame)
    m_playingGame = true;

  if(m_playingGame) {
    // Handling snake current movement direction
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_currDirection != Direction::RIGHT)
      m_currDirection = Direction::LEFT;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_currDirection != Direction::LEFT)
      m_currDirection = Direction::RIGHT;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_currDirection != Direction::DOWN)
      m_currDirection = Direction::UP;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_currDirection != Direction::UP)
      m_currDirection = Direction::DOWN;
  }

  // Pausing the game
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_playingGame)
    m_playingGame = false;
}
