//
// Created by viktor on 21.12.20.
//

#ifndef TURBOHIKER_PASSINGHIKER1SFML_H
#define TURBOHIKER_PASSINGHIKER1SFML_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "../turbohiker/PassingHiker1.h"
#include "Animation.h"

namespace turbohikerSFML {

    /**
    * \class PassingHiker1
    * \ingroup turbohikerSFML
    * \brief SFML passinghiker1 presentation
    */
    class PassingHiker1 : public turbohiker::PassingHiker1{
        std::weak_ptr<sf::RenderWindow> window;

        sf::Texture texture;
        sf::Sprite sprite;
        Animation anim;

        double defaultframerate = 10;


        sf::Font font;
        sf::Text reactText;

        sf::SoundBuffer pBuf;
        sf::Sound ping;

        static std::vector<std::wstring> reactions;

    public:
        explicit PassingHiker1(std::weak_ptr<sf::RenderWindow> w);

        void draw(const double& delta) override;

        void react() override;
    };


}


#endif //TURBOHIKER_PASSINGHIKER1SFML_H
