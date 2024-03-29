//
// Created by viktor on 21.12.20.
//

#include "PassingHiker1.h"
#include "Random.h"

turbohiker::eType turbohiker::PassingHiker1::type() { return PassHT1; }

void turbohiker::PassingHiker1::update(const double &delta) {
  setVel(Vector(0, -1)); // reset vel
}

turbohiker::PassingHiker1::PassingHiker1() {
  setSize(Vector(1.7, 1.7));
  setSpeed(speed);
  setVel(Vector(0, -1)); // moving toward player
  setMass(2);
  score_id = -1;
}

void turbohiker::PassingHiker1::handleShout() {
  bool slowdown = Random::Int(0, 1); // 50%
  if (slowdown) {
    setSpeed(speed / 2);
    react();
  }
}
