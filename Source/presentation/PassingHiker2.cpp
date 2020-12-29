//
// Created by viktor on 24.12.20.
//

#include "PassingHiker2.h"
#include "Transformation.h"
#include "../turbohiker/Random.h"

void turbohikerSFML::PassingHiker2::draw(const double &delta) {

    anim.setRate(velocity().magnitude() / speed *
                defaultframerate); // adjust animation speed to speed of hiker*/

    sprite.setPosition(Transformation::instance()->pos(position().add(
            Vector(size().x() / 2, -size().y() / 2)))); // update position

    anim.update(delta,sprite);

    std::shared_ptr<sf::RenderWindow> w =
            window.lock(); // borrow ownership of window

    w->draw(sprite); // draw sprite


    if (reactTime > 0){
        reactTime -= delta;
        if (reactTime < 0){reactTime = 0;}

        reactText.setPosition(Transformation::instance()->pos(position().add(
                Vector(0, -size().y()))));

        w->draw(reactText);
    }
    // bouding rectangle for debugging
    /*sf::RectangleShape rectangle(Transformation::instance()->size(size()));
    rectangle.setPosition(Transformation::instance()->pos(position().add(Vector(-size().x()/2,
    -size().y()/2))));

    w->draw(rectangle);*/
}

turbohikerSFML::PassingHiker2::PassingHiker2(std::weak_ptr<sf::RenderWindow> w) {
    window = std::move(w);

    texture.loadFromFile("../Resources/PNG/enemies/fish-big.png");
    sprite.setTextureRect(sf::IntRect(0, 0, 49, 49));

    sprite.setTexture(texture);
    Transformation::instance()->rescaleSprite(size(), sprite);

    sprite.rotate(90);

    anim = Animation(4,defaultframerate,false);
    anim.play(sprite);

    font.loadFromFile("../Resources/fonts/Arial Unicode MS.ttf");
    reactText.setFont(font);
    reactText.setString(L"(〃＞＿＜;〃)");
    reactText.setCharacterSize(
            turbohikerSFML::Transformation::instance()->textSize(0.3));

    reactText.setFillColor(sf::Color::Green);
    reactText.setStyle(sf::Text::Bold);

}

void turbohikerSFML::PassingHiker2::react() {
    reactTime = 2;

    int i = turbohiker::Random::instance()->Int(0,reactions.size()-1); // choose random reaction
    reactText.setString(reactions[i]);
}

std::vector<std::wstring> turbohikerSFML::PassingHiker2::reactions = {L"ﾟ口ﾟ", L"〇o〇", L"౦ ‸ ౦", L"⊙_⊙", L"ノωヽ", L"º □ º", L"ヽ(°〇°)ﾉ", L"┌( >_<)┘", L"( つ＞＜)つ"};