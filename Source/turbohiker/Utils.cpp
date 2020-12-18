//
// Created by viktor on 18.12.20.
//

#include "Utils.h"

turbohiker::Utils::Vector::Vector(const double &x_val, const double &y_val) {
  set(x_val, y_val);
}

turbohiker::Utils::Vector *turbohiker::Utils::Vector::set(const double &x_val,
                                                          const double &y_val) {
  x_ = x_val;
  y_ = y_val;
  return this;
}

double turbohiker::Utils::Vector::y() const { return y_; }

double turbohiker::Utils::Vector::x() const { return x_; }
