//
// Created by viktor on 29.12.20.
//

#include "RacingHiker.h"
#include "Transformation.h"

void turbohikerSFML::RacingHiker::draw(const double &delta) {
    sprite.setPosition(Transformation::instance()->pos(position().add(
            Vector(-size().x() / 2, -size().y() * 1.5)))); // update sprite position

    anim.setRate(getSpeed() / speed_normal *
                       defaultframerate); // framerate proportional to speed

    anim.update(delta, sprite); // update animation of sprite

    std::shared_ptr<sf::RenderWindow> w =
            window.lock(); // borrow ownership of window

    w->draw(sprite); // draw player sprite

    if (sonarAnim.isPlaying()) {
        sonarSprite.setPosition(Transformation::instance()->pos(
                position().add(Vector(-size().x(), 0.3)))); // update sprite position

        sonarAnim.update(delta, sonarSprite); // update sprite animation

        w->draw(sonarSprite); // draw sprite
    }
}

turbohikerSFML::RacingHiker::RacingHiker(std::weak_ptr<sf::RenderWindow> w, int i) : turbohiker::RacingHiker(i) {
    window = std::move(w);

    // load texture and set sprite to first animation frame
    texture.loadFromFile("../Resources/PNG/enemies/competing"+ std::to_string(i) + ".png");
    sprite.setTextureRect(sf::IntRect(0, 0, 50, 20));

    // rescale sprite to fit player collision rectangle, we flip x and y because
    // we will rotate the sprite afterwards
    Transformation::instance()->rescaleSprite(Vector(size().y(), size().x()),
                                              sprite);

    sprite.setTexture(texture);
    sprite.rotate(-90);

    anim = Animation(5, defaultframerate, false);
    anim.play(sprite);

    sonarTexture.loadFromFile("../Resources/PNG/player/sonar.png");
    sonarSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    sonarSprite.setTexture(sonarTexture);
    sonarSprite.setColor(sf::Color(i*125,255,255));

    Transformation::instance()->rescaleSprite(Vector(1, 1), sonarSprite);

    sonarAnim = Animation(5, 0, true).setDuration(0.5);
}

void turbohikerSFML::RacingHiker::shout() {
    sonarAnim.play(sonarSprite);
}
