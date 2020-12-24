//
// Created by viktor on 19.12.20.
//

#include "Player.h"
#include "Transformation.h"
#include <cmath>
#include <iostream>

void turbohikerSFML::Player::draw(const double &delta) {

  frametime += delta; // update frametime

  framerate = getSpeed() / speed_normal *
              defaultframerate; // framerate speeds up with speed also

  Transformation::instance()->setYpos(
      position().y() + 1); // update the camera position to player

  Transformation::instance()->setPspeed(getSpeed());

  if (frametime >= 1 / framerate) { // this frame has lasted long enough
    frametime = 0;
    nextFrame();
  }

  sprite.setPosition(Transformation::instance()->pos(position().add(
      Vector(-size().x() / 2, -size().y() * 1.5)))); // update sprite position

  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // borrow ownership of window

  w->draw(sprite); // draw player sprite

  if (shoutTimer > 0) { // if we're shouting, animate sonar
    shoutTimer -= delta;
    if (shoutTimer < 0) {
      shoutTimer = 0;
    }

    animateSonar();

    sonarSprite.setPosition(Transformation::instance()->pos(
        position().add(Vector(-size().x(), 0.3)))); // update sprite position
    w->draw(sonarSprite);
  }

  // bouding rectangle for debug
  /*sf::RectangleShape rectangle(Transformation::instance()->size(size()));
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

  sonarTexture.loadFromFile("../Resources/PNG/player/sonar.png");
  sonarSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
  sonarSprite.setTexture(sonarTexture);

  Transformation::instance()->rescaleSprite(Vector(1, 1), sonarSprite);
}

void turbohikerSFML::Player::nextFrame() {
  frame += 1;
  if (frame == maxframes) { // return to first frame
    frame = 0;
  }

  sf::IntRect current = sprite.getTextureRect();
  // set sprite to next frame texture
  sprite.setTextureRect(sf::IntRect(frame * current.width, current.top,
                                    current.width, current.height));
}

void turbohikerSFML::Player::shout() { shoutTimer = sonartime; }

void turbohikerSFML::Player::animateSonar() {
  double p = (sonartime - shoutTimer) / sonartime; // % of timer finished

  int sonarframe = std::floor(p / (1 / sonarFrames)); // frame we should be on

  sf::IntRect current = sonarSprite.getTextureRect();

  sonarSprite.setTextureRect(sf::IntRect(
      sonarframe * current.width, current.top, current.width, current.height));
}
