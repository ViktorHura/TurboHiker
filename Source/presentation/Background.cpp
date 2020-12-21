//
// Created by viktor on 20.12.20.
//

#include "Background.h"
#include "Transformation.h"

void turbohikerSFML::Background::draw(const double& delta) {

    std::shared_ptr<sf::RenderWindow> w =
            window.lock(); // borrow ownership of window

    for (int i=0; i < backgroundSprites.size(); i++){
        Vector npos = Vector(position().x(),position().y() + 18.75*i);

        sf::Vector2f nposP = Transformation::instance()->pos(npos);

        backgroundSprites[i].setPosition(nposP);
        midgroundSprites[i].setPosition(nposP);



        w->draw(backgroundSprites[i]);
        w->draw(midgroundSprites[i]);

        for (int j=0; j < 3; j++){
            int c = i*3 + j;

            Vector cpos = Vector(position().x() + 2*(j+1) - 0.1075,position().y() + 18.75*(i+1));

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
    chain.setTextureRect(sf::IntRect(469,0,11,960));
    //rescale
    Transformation::instance()->rescaleSprite(Vector(0.215, 18.75), chain);


    sf::Sprite backgroundSprite;
    sf::Sprite midgroundSprite;

    //create background sprite, rescale and rotate
    backgroundSprite.setTexture(backgroundTexture);

    Transformation::instance()->rescaleSprite(Vector(18.75, 10), backgroundSprite);

    backgroundSprite.rotate(-90);


    //create midground sprite, rescale and rotate
    midgroundSprite.setTexture(midgroundTexture);

    Transformation::instance()->rescaleSprite(Vector(18.75, 10), midgroundSprite);

    midgroundSprite.rotate(-90);

    for (int i=0; i < tileamount; i++){// each tile gets 1 background and 3 chains to divide the lanes
        backgroundSprites.push_back(backgroundSprite);
        midgroundSprites.push_back(midgroundSprite);

        laneSprites.push_back(chain);
        laneSprites.push_back(chain);
        laneSprites.push_back(chain);
    }

}
