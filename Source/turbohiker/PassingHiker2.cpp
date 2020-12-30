//
// Created by viktor on 24.12.20.
//

#include "PassingHiker2.h"
#include "Random.h"

turbohiker::PassingHiker2::PassingHiker2() {
  setSize(Vector(1.8, 1.8));
  setSpeed(speed);
  setVel(Vector(0, -1)); // moving toward player
  setMass(3);
}

turbohiker::eType turbohiker::PassingHiker2::type() { return PassHT2; }

void turbohiker::PassingHiker2::update(const double &delta) {

  double destination = -3 + 2 * desiredLane;

  double dir = double(destination - position().x()) * 1.75;
  // if (dir != 0){
  //     dir = dir/std::abs(dir);
  // }

  Vector vel = Vector(dir, 0);

  setVel(vel); // reset vel
}

void turbohiker::PassingHiker2::handleShout() {
  bool ignore = Random::instance()->Int(0, 1); // 50%
  if (ignore) {
    return;
  }

  desiredLane = Utils::nextLane(position().getLane());

  react();
}

void turbohiker::PassingHiker2::setDesired(const int &l) { desiredLane = l; }
