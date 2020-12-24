//
// Created by viktor on 21.12.20.
//

#include <iostream>
#include "PassingHiker1.h"
#include "Random.h"

turbohiker::eType turbohiker::PassingHiker1::type() { return PassHT1; }

void turbohiker::PassingHiker1::update(const double &delta) {
    setVel(Vector(0, -1)); // reset vel
}

turbohiker::PassingHiker1::PassingHiker1() {
  setSize(Vector(2, 2));
  setSpeed(speed);
  setVel(Vector(0, -1)); // moving toward player
  setMass(2);
}

void turbohiker::PassingHiker1::handleShout() {
    bool slowdown = Random::instance()->Int(0,1); // 50%
    if (slowdown){
        setSpeed(speed/2);
    }
}
