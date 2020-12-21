//
// Created by viktor on 16.12.20.
//

#include <iostream>
#include "Entity.h"

Vector turbohiker::Entity::position() const {
    return pos;
}

Vector turbohiker::Entity::velocity() const {
    return vel;
}

Vector turbohiker::Entity::size() const {
    return size_;
}

turbohiker::Entity &turbohiker::Entity::setPos(const Vector &position) {
    pos.set(position);
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

turbohiker::eType turbohiker::Entity::type() {
    return EntityT;
}

turbohiker::Entity& turbohiker::Entity::setSpeed(const double &s) {
    speed = s;
    return *this;
}

double turbohiker::Entity::getSpeed() const {
    return speed;
}

