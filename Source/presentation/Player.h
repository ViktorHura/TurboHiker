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
#include "../turbohiker/Player.h"

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

        sf::Texture sonarTexture; // sonar texture
        sf::Sprite sonarSprite; // sonar sprite
        double sonarFrames = 5; // amount of sonar frames
        double sonartime = 0.5; // amount of time the sonar animation wil take in seconds

        double defaultframerate = 10;
        double framerate = defaultframerate;  // animation framerate
        int frame=0;            // current frame
        int maxframes = 5;      // amount of frames
        double frametime = 0;   // amount of time current frame has lasted in seconds

        double shoutTimer = 0;

        /**
         * draws next frame of the player animation
         */
        void nextFrame();

        /**
         * draws correct frame of sonar animation
         */
        void animateSonar();
    public:
        /**
         * needs weak pointer to the window to be able to draw
         * @param w
         */
        explicit Player(std::weak_ptr<sf::RenderWindow> w);

        void draw(const double& delta) override;

        void shout() override;

    };
}


#endif //TURBOHIKER_PLAYERSFML_H
