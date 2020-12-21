//
// Created by viktor on 21.12.20.
//

#include "PassingHiker1.h"

turbohiker::eType turbohiker::PassingHiker1::type() { return PassHT1; }

void turbohiker::PassingHiker1::update(const double &delta) {}

turbohiker::PassingHiker1::PassingHiker1() {
  setSize(Vector(2, 2));
  setSpeed(speed);
}
