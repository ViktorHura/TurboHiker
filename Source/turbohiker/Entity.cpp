//
// Created by viktor on 16.12.20.
//

#include "Entity.h"
#include <iostream>

Vector turbohiker::Entity::position() const { return pos; }

Vector turbohiker::Entity::velocity() const { return vel; }

Vector turbohiker::Entity::size() const { return size_; }

turbohiker::Entity &turbohiker::Entity::setPos(const Vector &position) {
  pos.set(position);
  setNextPos(position);
  return *this;
}

turbohiker::Entity &turbohiker::Entity::setVel(const Vector &velocity) {
  vel.set(velocity);
  return *this;
}

turbohiker::Entity &turbohiker::Entity::setSize(const Vector &size) {
  size_.set(size);
  return *this;
}

turbohiker::eType turbohiker::Entity::type() { return EntityT; }

turbohiker::Entity &turbohiker::Entity::setSpeed(const double &s) {
  speed = s;
  return *this;
}

double turbohiker::Entity::getSpeed() const { return speed; }

Vector turbohiker::Entity::nextpos() const { return nextPos; }

turbohiker::Entity &turbohiker::Entity::setNextPos(const Vector &position) {
  nextPos.set(position);
  return *this;
}

double turbohiker::Entity::mass() const { return mass_; }

turbohiker::Entity &turbohiker::Entity::setMass(const double &m) {
  mass_ = m;
  return *this;
}
