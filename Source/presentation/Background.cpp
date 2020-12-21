//
// Created by viktor on 20.12.20.
//

#include "Background.h"
#include "Transformation.h"

void turbohikerSFML::Background::draw(const double &delta) {

  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // borrow ownership of window

      if (not Transformation::instance()->Yismax()){ // as long as the camera is still moving, keep scrolling background
          parallax_offset += parallax_speed*delta;
      }

  for (int i = 0; i < backgroundSprites.size(); i++) {
    Vector nmpos = Vector(position().x(), position().y() + 18.75 * i); // position of each tile

    Vector nbpos = Vector().set(nmpos).add(Vector(0,parallax_offset)); // add parallax offset to background


    backgroundSprites[i].setPosition(Transformation::instance()->pos(nbpos));
    midgroundSprites[i].setPosition(Transformation::instance()->pos(nmpos));

    w->draw(backgroundSprites[i]);
    w->draw(midgroundSprites[i]);

    for (int j = 0; j < 3; j++) { // set position of the chain tiles as well, 3 chains per background tile
      int c = i * 3 + j;

      Vector cpos = Vector(position().x() + 2 * (j + 1) - 0.1075,
                           position().y() + 18.75 * (i + 1));

      laneSprites[c].setPosition(Transformation::instance()->pos(cpos));
      w->draw(laneSprites[c]);
    }
  }
}

turbohikerSFML::Background::Background(std::weak_ptr<sf::RenderWindow> w) {
  window = std::move(w);

  // load textures
  backgroundTexture.loadFromFile("../Resources/PNG/environment/background.png");
  midgroundTexture.loadFromFile("../Resources/PNG/environment/midground.png");

  tilesTexture.loadFromFile("../Resources/PNG/environment/tiles.png");

  // create chain sprite
  sf::Sprite chain;
  chain.setTexture(tilesTexture);
  // select chain from texture
  chain.setTextureRect(sf::IntRect(469, 0, 11, 960));
  // rescale
  Transformation::instance()->rescaleSprite(Vector(0.215, 18.75), chain);

  sf::Sprite backgroundSprite;
  sf::Sprite midgroundSprite;

  // create background sprite, rescale and rotate
  backgroundSprite.setTexture(backgroundTexture);

  Transformation::instance()->rescaleSprite(Vector(18.75, 10),
                                            backgroundSprite);

  backgroundSprite.rotate(-90);

  // create midground sprite, rescale and rotate
  midgroundSprite.setTexture(midgroundTexture);

  Transformation::instance()->rescaleSprite(Vector(18.75, 10), midgroundSprite);

  midgroundSprite.rotate(-90);

  for (int i = 0; i < tileamount;
       i++) { // each tile gets 1 background and 3 chains to divide the lanes
    backgroundSprites.push_back(backgroundSprite);
    midgroundSprites.push_back(midgroundSprite);

    laneSprites.push_back(chain);
    laneSprites.push_back(chain);
    laneSprites.push_back(chain);
  }
}
