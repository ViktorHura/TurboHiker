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

        double framerate = 10;  // animation framerate
        int frame=0;            // current frame
        int maxframes = 5;      // amount of frames
        double frametime = 0;   // amount of time current frame has lasted in seconds

        /**
         * draws next frame of the player animation
         */
        void nextFrame();
    public:
        /**
         * needs weak pointer to the window to be able to draw
         * @param w
         */
        explicit Player(std::weak_ptr<sf::RenderWindow> w);

        void draw(const double& delta) override;

    };
}


#endif //TURBOHIKER_PLAYERSFML_H
