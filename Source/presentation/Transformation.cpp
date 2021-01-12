//
// Created by viktor on 18.12.20.
//

#include "Transformation.h"

#include <cmath>
#include <utility>

turbohikerSFML::Transformation::Transformation(
    std::weak_ptr<sf::RenderWindow> w) {
  window = std::move(w);
}

turbohikerSFML::Transformation *
turbohikerSFML::Transformation::instance(std::weak_ptr<sf::RenderWindow> w) {
  if (!_instance) {
    _instance = new Transformation(std::move(w));
  }
  return _instance;
}

turbohikerSFML::Transformation *turbohikerSFML::Transformation::_instance =
    nullptr;

int turbohikerSFML::Transformation::textSize(const double &size) const {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // share window temporarily

  // size * 1/10 * screen diagonal, narrowing to int
  return std::floor(
      size *
      sqrt(pow(double(w->getSize().x), 2) + pow(double(w->getSize().y), 2)) /
      10);
}

float turbohikerSFML::Transformation::y(const double &y) const {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // share window temporarily

  return static_cast<float>(double(w->getSize().y) / 2.0 -
                            double(w->getSize().y) / 6.0 *
                                (y - y_pos)); // narrowing to float
}

float turbohikerSFML::Transformation::x(const double &x) const {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // share window temporarily

  return static_cast<float>(double(w->getSize().x) / 8.0 * x +
                            double(w->getSize().x) / 2.0); // narrowing to float
}

sf::Vector2f turbohikerSFML::Transformation::pos(
    const turbohiker::Utils::Vector &vec) const {
  return {x(vec.x()), y(vec.y())};
}

sf::Vector2f turbohikerSFML::Transformation::size(
    const turbohiker::Utils::Vector &vec) const {
  std::shared_ptr<sf::RenderWindow> w = window.lock();

  float x_ = double(w->getSize().x) / 8.0 * vec.x();
  float y_ = double(w->getSize().y) / 6.0 * vec.y();

  return {x_, y_};
}

void turbohikerSFML::Transformation::setYpos(const double &ypos) {
  if (ypos >= max_y_pos) {
    y_pos = max_y_pos;
    return;
  }
  y_pos = ypos;
  y_delta = y_pos - y_pos_old;
  y_pos_old = ypos;
}

void turbohikerSFML::Transformation::rescaleSprite(
    const turbohiker::Utils::Vector &s, sf::Sprite &sprite) {
  sf::Vector2f sp = Transformation::instance()->size(s);

  float x_scale = sp.x / sprite.getTextureRect().width;
  float y_scale = sp.y / sprite.getTextureRect().height;

  sprite.setScale(x_scale, y_scale);
}

bool turbohikerSFML::Transformation::Yismax() { return y_pos == max_y_pos; }

double turbohikerSFML::Transformation::getYdelta() const { return y_delta; }

double turbohikerSFML::Transformation::getPspeed() { return p_speed; }

void turbohikerSFML::Transformation::setPspeed(const double &p) { p_speed = p; }

sf::Vector2f turbohikerSFML::Transformation::posFixed(
    const turbohiker::Utils::Vector &vec) const {
  return {x(vec.x()), yFixed(vec.y())};
}

float turbohikerSFML::Transformation::yFixed(const double &y) const {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // share window temporarily

  return static_cast<float>(double(w->getSize().y) / 2.0 -
                            double(w->getSize().y) / 6.0 *
                                (y)); // narrowing to float
}

void turbohikerSFML::Transformation::reset() {
  y_pos = 0;
  y_pos_old = 0;
  y_delta = 0;
}
