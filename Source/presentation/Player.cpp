//
// Created by viktor on 19.12.20.
//

#include "Player.h"
#include "Transformation.h"
#include <cmath>
#include <iostream>

void turbohikerSFML::Player::draw(const double &delta) {
  Transformation::instance()->setYpos(
      position().y() + 1); // update the camera position to player

  Transformation::instance()->setPspeed(
      getSpeed()); // update parallax background speed

  sprite.setPosition(Transformation::instance()->pos(position().add(
      Vector(-size().x() / 2, -size().y() * 1.5)))); // update sprite position

  playerAnim.setRate(getSpeed() / speed_normal *
                     defaultframerate); // framerate proportional to speed

  playerAnim.update(delta, sprite); // update animation of sprite

  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // borrow ownership of window

  w->draw(sprite); // draw player sprite

  if (sonarAnim.isPlaying()) {
    sonarSprite.setPosition(Transformation::instance()->pos(
        position().add(Vector(-size().x(), 0.3)))); // update sprite position

    sonarAnim.update(delta, sonarSprite); // update sprite animation

    w->draw(sonarSprite); // draw sprite
  }

  // bouding rectangle for debug
  /*
  sf::RectangleShape rectangle(Transformation::instance()->size(size()));
  rectangle.setPosition(Transformation::instance()->pos(position().add(Vector(-size().x()/2,
  -size().y()/2))));

  w->draw(rectangle);*/
}

turbohikerSFML::Player::Player(std::weak_ptr<sf::RenderWindow> w) {
  window = std::move(w);

  // load texture and set sprite to first animation frame
  texture.loadFromFile("../Resources/PNG/player/player-fast.png");
  sprite.setTextureRect(sf::IntRect(0, 0, 50, 20));

  // rescale sprite to fit player collision rectangle, we flip x and y because
  // we will rotate the sprite afterwards
  Transformation::instance()->rescaleSprite(Vector(size().y(), size().x()),
                                            sprite);

  sprite.setTexture(texture);
  sprite.rotate(-90);

  playerAnim = Animation(5, defaultframerate, false);
  playerAnim.play(sprite);

  sonarTexture.loadFromFile("../Resources/PNG/player/sonar.png");
  sonarSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
  sonarSprite.setTexture(sonarTexture);

  Transformation::instance()->rescaleSprite(Vector(1, 1), sonarSprite);

  sonarAnim = Animation(5, 0, true).setDuration(0.5);
}

void turbohikerSFML::Player::shout() { sonarAnim.play(sonarSprite); }
