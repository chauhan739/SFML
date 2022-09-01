#include "header.h"

GameUtilities::GameUtilities() {
  m_window.create(sf::VideoMode(800, 600), "Snake Game!", sf::Style::Titlebar | sf::Style::Close);

  m_font.loadFromFile("font/TYPEWR__.TTF");

  m_playingGame = false;
}
