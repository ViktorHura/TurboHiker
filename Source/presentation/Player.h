//
// Created by viktor on 19.12.20.
//

#ifndef TURBOHIKER_PLAYERSFML_H
#define TURBOHIKER_PLAYERSFML_H


#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>
#include "../turbohiker/Player.h"
#include "Animation.h"

namespace turbohikerSFML {

    /**
    * \class Player
    * \ingroup turbohikerSFML
    * \brief SFML player presentation
    */
    class Player : public turbohiker::Player {
        std::weak_ptr<sf::RenderWindow> window;

        sf::Texture texture; // player texture
        sf::Sprite sprite; // player sprite
        Animation playerAnim; // player animation object

        sf::Texture sonarTexture; // sonar texture
        sf::Sprite sonarSprite; // sonar sprite
        Animation sonarAnim; // sonar animation object

        sf::SoundBuffer sBuf;
        sf::Sound backgroundSound;

        sf::SoundBuffer pBuf;
        sf::Sound ping;

        double defaultframerate = 10;
    public:
        /**
         * needs weak pointer to the window to be able to draw
         * @param w
         */
        explicit Player(std::weak_ptr<sf::RenderWindow> w);

        ~Player() override;

        void draw(const double& delta) override;

        void shout() override;

    };
}


#endif //TURBOHIKER_PLAYERSFML_H
