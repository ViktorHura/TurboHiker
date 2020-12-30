//
// Created by viktor on 29.12.20.
//

#ifndef TURBOHIKER_RACINGHIKERSFML_H
#define TURBOHIKER_RACINGHIKERSFML_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "../turbohiker/RacingHiker.h"
#include "Animation.h"

namespace turbohikerSFML {

    /**
    * \class RacingHiker
    * \ingroup turbohikerSFML
    * \brief SFML racing hiker presentation
    */
    class RacingHiker : public turbohiker::RacingHiker {
        std::weak_ptr<sf::RenderWindow> window;

        sf::Texture texture; // texture
        sf::Sprite sprite; // sprite
        Animation anim; // animation object

        sf::Texture sonarTexture; // sonar texture
        sf::Sprite sonarSprite; // sonar sprite
        Animation sonarAnim; // sonar animation object

        double defaultframerate = 10;
    public:
        /**
         * needs weak pointer to the window to be able to draw
         * @param w
         */
        explicit RacingHiker(std::weak_ptr<sf::RenderWindow> w, int i);

        void draw(const double& delta) override;

        void shout() override;
    };

}
#endif //TURBOHIKER_RACINGHIKER_H
