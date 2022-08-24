#include "header.h"

void GameUtilities::handleEvent() {
  sf::Event event;
  while(m_window.pollEvent(event)) {
    if(event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) m_window.close();
  }
}
