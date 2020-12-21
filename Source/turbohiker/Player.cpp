//
// Created by viktor on 19.12.20.
//

#include "Player.h"
#include <iostream>

void turbohiker::Player::update(const double &delta) {
  Vector vel;
  if (u) {
    vel.add(Vector(0, 1));
  }
  if (l) {
    vel.add(Vector(-1, 0));
  }
  if (r) {
    vel.add(Vector(1, 0));
  }
  if (d) {
    vel.add(Vector(0, -1));
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
  setSpeed(6);
}
