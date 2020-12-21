//
// Created by viktor on 19.12.20.
//

#include <iostream>
#include "Player.h"
#include "Transformation.h"

void turbohikerSFML::Player::draw(const double& delta) {

    frametime += delta; //update frametime

    Transformation::instance()->setYpos(position().y()+2.75); //update the camera position to player

    if (frametime >= 1/framerate){ // this frame has lasted long enough
        frametime=0;
        nextFrame();
    }

    sprite.setPosition(Transformation::instance()->pos(position().add(Vector(-size().x()/2,0)))); // update shape position

    std::shared_ptr<sf::RenderWindow> w =
            window.lock(); // borrow ownership of window

    w->draw(sprite); // draw player sprite
}

turbohikerSFML::Player::Player(std::weak_ptr<sf::RenderWindow> w) {
    window = std::move(w);

    // load texture and set sprite to first animation frame
    texture.loadFromFile("../Resources/PNG/player/player-fast.png");
    sprite.setTextureRect(sf::IntRect(0,0,50,20));

    //rescale sprite to fit player collision rectangle, we flip x and y because we will rotate the sprite afterwards
    Transformation::instance()->rescaleSprite(Vector(size().y(), size().x()), sprite);

    sprite.setTexture(texture);
    sprite.rotate(-90);

}

void turbohikerSFML::Player::nextFrame() {
    frame +=1;
    if (frame == maxframes){ //return to first frame
        frame = 0;
    }

    sf::IntRect current = sprite.getTextureRect();
    // set sprite to next frame texture
    sprite.setTextureRect(sf::IntRect(frame * current.width ,current.top,current.width,current.height));

}
