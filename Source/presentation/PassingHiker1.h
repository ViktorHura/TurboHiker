//
// Created by viktor on 21.12.20.
//

#ifndef TURBOHIKER_PASSINGHIKER1SFML_H
#define TURBOHIKER_PASSINGHIKER1SFML_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../turbohiker/PassingHiker1.h"

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

        double defaultframerate = 10;
        double framerate = defaultframerate;  // animation framerate
        int frame=0;            // current frame
        int maxframes = 4;      // amount of frames
        double frametime = 0;   // amount of time current frame has lasted in seconds

        /**
         * draws next frame of the animation
         */
        void nextFrame();
    public:
        explicit PassingHiker1(std::weak_ptr<sf::RenderWindow> w);

        void draw(const double& delta) override;
    };

}


#endif //TURBOHIKER_PASSINGHIKER1SFML_H
