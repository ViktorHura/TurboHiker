//
// Created by viktor on 16.12.20.
//

#include "Entity.h"

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

int turbohiker::Entity::scoreId() { return score_id; }

void turbohiker::Entity::freeze() {
  frozen = true;
  setVel(Vector(0, 0));
  setPos(Vector(-3 + scoreId() * 2, position().y() + 5));
}

void turbohiker::Entity::unfreeze() { frozen = false; }
