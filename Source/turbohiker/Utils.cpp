//
// Created by viktor on 18.12.20.
//

#include "Utils.h"
#include <cmath>
#include <string>

turbohiker::Utils::Vector::Vector(const double &x_val, const double &y_val) {
  set(x_val, y_val);
}

turbohiker::Utils::Vector &turbohiker::Utils::Vector::set(const double &x_val,
                                                          const double &y_val) {
  x_ = x_val;
  y_ = y_val;
  return *this;
}

double turbohiker::Utils::Vector::y() const { return y_; }

double turbohiker::Utils::Vector::x() const { return x_; }

turbohiker::Utils::Vector &
turbohiker::Utils::Vector::add(const turbohiker::Utils::Vector &vec2) {
  x_ += vec2.x();
  y_ += vec2.y();

  return *this;
}

turbohiker::Utils::Vector &turbohiker::Utils::Vector::scalar(const double &s) {
  x_ *= s;
  y_ *= s;

  return *this;
}

turbohiker::Utils::Vector &turbohiker::Utils::Vector::normalize() {
  double l = magnitude();
  if (l == 0) {
    return *this;
  }
  return scalar(1 / l);
}

double turbohiker::Utils::Vector::magnitude() const {
  return std::sqrt(x_ * x_ + y_ * y_);
}

turbohiker::Utils::Vector &
turbohiker::Utils::Vector::set(const turbohiker::Utils::Vector &vec2) {
  x_ = vec2.x();
  y_ = vec2.y();
  return *this;
}

std::string turbohiker::Utils::Vector::toString() {
  return "( " + std::to_string(x()) + " ; " + std::to_string(y()) + " )";
}

int turbohiker::Utils::Vector::getLane() const {
  return std::floor((x() + 4) / 2);
}
