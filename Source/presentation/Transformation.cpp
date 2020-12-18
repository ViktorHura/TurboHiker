//
// Created by viktor on 18.12.20.
//

#include "Transformation.h"

#include <cmath>
#include <utility>

Transformation::Transformation(std::weak_ptr<sf::RenderWindow> w) {
  window = std::move(w);
}

Transformation *Transformation::instance(std::weak_ptr<sf::RenderWindow> w) {
  if (!_instance) {
    _instance = new Transformation(std::move(w));
  }
  return _instance;
}

Transformation *Transformation::_instance = nullptr;

int Transformation::textSize(const double &size) const {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // share window temporarily

  // size * 1/10 * screen diagonal, narrowing to int
  return std::floor(
      size *
      sqrt(pow(double(w->getSize().x), 2) + pow(double(w->getSize().y), 2)) /
      10);
}

float Transformation::y(const double &y) const {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // share window temporarily

  return (double(w->getSize().y) / 2 -
          double(w->getSize().y) / 6 * y); // narrowing to float
}

float Transformation::x(const double &x) const {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // share window temporarily

  return (double(w->getSize().x) / 8 * x +
          double(w->getSize().x) / 2); // narrowing to float
}
