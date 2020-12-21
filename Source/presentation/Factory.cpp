//
// Created by viktor on 19.12.20.
//

#include "Factory.h"

#include "../turbohiker/World.h"
#include "Background.h"
#include "PassingHiker1.h"
#include "Player.h"
#include <memory>

turbohikerSFML::Factory::Factory(std::weak_ptr<sf::RenderWindow> w) {
  window = std::move(w);
}

turbohiker::Player *turbohikerSFML::Factory::makePlayer() {
  return new turbohikerSFML::Player(window);
}

turbohiker::Background *turbohikerSFML::Factory::makeBackground() {
  return new turbohikerSFML::Background(window);
}

turbohiker::PassingHiker1 *turbohikerSFML::Factory::makePassingHiker1() {
  return new turbohikerSFML::PassingHiker1(window);
}
