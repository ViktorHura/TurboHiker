//
// Created by viktor on 24.12.20.
//

#ifndef TURBOHIKER_PASSINGHIKER2SFML_H
#define TURBOHIKER_PASSINGHIKER2SFML_H

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "../turbohiker/PassingHiker2.h"
#include "Animation.h"

namespace turbohikerSFML {

    /**
    * \class PassingHiker2
    * \ingroup turbohikerSFML
    * \brief SFML passinghiker2 presentation
    */
    class PassingHiker2 : public turbohiker::PassingHiker2{
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
        explicit PassingHiker2(std::weak_ptr<sf::RenderWindow> w);
        ~PassingHiker2() override = default;

        void draw(const double& delta) override;

        void react() override;
    };
}

#endif //TURBOHIKER_PASSINGHIKER2SFML_H
