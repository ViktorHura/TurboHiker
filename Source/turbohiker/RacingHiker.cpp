//
// Created by viktor on 29.12.20.
//

#include "RacingHiker.h"

turbohiker::RacingHiker::RacingHiker(int i) {
  setSize(Vector(0.5, 1.25));
  setSpeed(speed_normal);
  setMass(0.5);
  desiredlane = i;
  score_id = i;
}

turbohiker::eType turbohiker::RacingHiker::type() { return RacingH; }

void turbohiker::RacingHiker::update(const double &delta) {
  if (frozen) {
    return;
  }
  Vector vel(0, 1);

  // move to desired lane
  double destination = -3 + 2 * desiredlane;
  double dir = (destination - position().x());
  vel.add(Vector(dir, 0).normalize());

  setVel(vel);
}

void turbohiker::RacingHiker::changeLane() {
  desiredlane = Utils::nextLane(position().getLane());
}

void turbohiker::RacingHiker::speedUp() {
  if (getSpeed() == speed_slow) {
    setSpeed(speed_normal);
  } else {
    setSpeed(speed_fast);
  }
}

void turbohiker::RacingHiker::slowDown() {
  if (getSpeed() == speed_fast) {
    setSpeed(speed_normal);
  } else {
    setSpeed(speed_slow);
  }
}
