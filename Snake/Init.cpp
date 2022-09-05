#include "header.h"

GameUtilities::GameUtilities() {
  m_window.create(sf::VideoMode(800, 600), "Snake Game!", sf::Style::Titlebar | sf::Style::Close);

  m_font.loadFromFile("assets/font/TYPEWR__.TTF");

  m_eatBuffer.loadFromFile("assets/audio/fruit-crunch.wav");

  m_playingGame = false;
}
