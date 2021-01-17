//
// Created by viktor on 21.12.20.
//

#include "PassingHiker1.h"
#include "../turbohiker/Random.h"
#include "Transformation.h"

void turbohikerSFML::PassingHiker1::draw(const double &delta) {

  anim.setRate(getSpeed() / speed *
               defaultframerate); // adjust animation speed to speed of hiker

  sprite.setPosition(Transformation::instance()->pos(position().add(
      Vector(size().x() / 2, -size().y() / 2)))); // update position

  anim.update(delta, sprite);

  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // borrow ownership of window

  w->draw(sprite); // draw sprite

  if (reactTime > 0) { // we are still reacting
    reactTime -= delta;
    if (reactTime < 0) {
      reactTime = 0;
    }

    reactText.setPosition(Transformation::instance()->pos(
        position().add(Vector(0, -size().y()))));

    w->draw(reactText);
  }

  // bouding rectangle for debugging
  /*sf::RectangleShape rectangle(Transformation::instance()->size(size()));
  rectangle.setPosition(Transformation::instance()->pos(position().add(Vector(-size().x()/2,
  -size().y()/2))));

  w->draw(rectangle);*/
}

turbohikerSFML::PassingHiker1::PassingHiker1(
    std::weak_ptr<sf::RenderWindow> w) {
  window = std::move(w);

  texture.loadFromFile("../Resources/PNG/enemies/fish.png");
  sprite.setTextureRect(sf::IntRect(0, 0, 28, 28));

  sprite.setTexture(texture);
  Transformation::rescaleSprite(size(), sprite);

  sprite.rotate(90);

  anim = Animation(4, defaultframerate, false);
  anim.play(sprite);

  font.loadFromFile("../Resources/fonts/Arial Unicode MS.ttf");
  reactText.setFont(font);
  reactText.setString(L"(〃＞＿＜;〃)");
  reactText.setCharacterSize(
      turbohikerSFML::Transformation::instance()->textSize(0.3));

  reactText.setFillColor(sf::Color::Yellow);
  reactText.setStyle(sf::Text::Bold);

    pBuf.loadFromFile("../Resources/sounds/reacts.wav");
    ping.setBuffer(pBuf);
    ping.setPitch(0.5);
}

void turbohikerSFML::PassingHiker1::react() {
  reactTime = 2;

  int i = turbohiker::Random::Int(
      0, reactions.size() - 1); // chose random reaction
  reactText.setString(reactions[i]);
  ping.play();
}

std::vector<std::wstring> turbohikerSFML::PassingHiker1::reactions = {
    L"⌣̀_⌣́",  L"￣Д￣",  L"￢_￢", L"￣︿￣", L"︶︹︺",
    L"⇀‸↼‶", L"＞﹏＜", L"O~O",   L"ভ_ ভ"};
