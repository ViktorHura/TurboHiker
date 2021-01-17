//
// Created by viktor on 19.12.20.
//

#include "Player.h"

void turbohiker::Player::update(const double &delta) {
  if (frozen) {
    return;
  }

  Vector vel = Vector(0, 1);
  if (u) {
    setSpeed(speed_fast); // speed up
  }
  if (l) {
    vel.add(Vector(-1, 0)); // going left
  }
  if (r) {
    vel.add(Vector(1, 0)); // going right
  }
  if (d) {
    setSpeed(speed_slow); // slow down
  }

  if (not u and not d) {
    setSpeed(speed_normal); // back to normal speed
  }

  setVel(vel);
}

void turbohiker::Player::handleInput(const int &key, bool keydown) {
  switch (key) {
  case 73: // up key
    u = keydown;
    break;
  case 71: // left key
    l = keydown;
    break;
  case 72: // right key
    r = keydown;
    break;
  case 74: // down key
    d = keydown;
    break;
  }
}

turbohiker::eType turbohiker::Player::type() { return PlayerT; }

turbohiker::Player::Player() {
  setSize(Vector(0.5, 1.25));
  setSpeed(speed_normal);
  setMass(1);
  setPos(Vector(3, 0));
  score_id = 3;
}
