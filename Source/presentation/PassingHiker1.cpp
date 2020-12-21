//
// Created by viktor on 21.12.20.
//

#include "PassingHiker1.h"
#include "Transformation.h"

void turbohikerSFML::PassingHiker1::draw(const double &delta) {

    frametime += delta; //update frametime

    if (frametime >= 1/framerate){ // this frame has lasted long enough
        frametime=0;
        nextFrame();
    }

    sprite.setPosition(Transformation::instance()->pos(position().add(Vector(size().x()/2,0)))); // update position

    std::shared_ptr<sf::RenderWindow> w =
            window.lock(); // borrow ownership of window

    w->draw(sprite); // draw player sprite

}

turbohikerSFML::PassingHiker1::PassingHiker1(std::weak_ptr<sf::RenderWindow> w) {
    window = std::move(w);

    texture.loadFromFile("../Resources/PNG/enemies/fish-big.png");
    sprite.setTextureRect(sf::IntRect(0,0,49,49));

    sprite.setTexture(texture);
    Transformation::instance()->rescaleSprite(size(), sprite);

    sprite.rotate(90);

}

void turbohikerSFML::PassingHiker1::nextFrame() {
    frame +=1;
    if (frame == maxframes){ //return to first frame
        frame = 0;
    }

    sf::IntRect current = sprite.getTextureRect();
    // set sprite to next frame texture
    sprite.setTextureRect(sf::IntRect(frame * current.width ,current.top,current.width,current.height));
}
