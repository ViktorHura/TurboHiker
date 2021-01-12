//
// Created by viktor on 19.12.20.
//

#include "Factory.h"

#include "../turbohiker/World.h"
#include "Background.h"
#include "PassingHiker1.h"
#include "PassingHiker2.h"
#include "Player.h"
#include "RacingHiker.h"
#include "Scoreboard.h"
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

turbohiker::PassingHiker2 *
turbohikerSFML::Factory::makePassingHiker2(const int &initialLane) {
  auto p = new turbohikerSFML::PassingHiker2(window);
  p->setDesired(initialLane);
  return p;
}

turbohiker::RacingHiker *turbohikerSFML::Factory::makeRacingHiker() {
  i++;
  return new turbohikerSFML::RacingHiker(window, i);
}

turbohiker::ScoreObserver *turbohikerSFML::Factory::makeScoreObserver() {
  return new turbohikerSFML::Scoreboard(window);
}
