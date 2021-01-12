//
// Created by viktor on 20.12.20.
//

#ifndef TURBOHIKER_BACKGROUNDSFML_H
#define TURBOHIKER_BACKGROUNDSFML_H


#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../turbohiker/Background.h"

namespace turbohikerSFML {

    /**
    * \class Background
    * \ingroup turbohikerSFML
    * \brief SFML background presentation
    */
    class Background : public turbohiker::Background {
        std::weak_ptr<sf::RenderWindow> window;

        sf::Texture backgroundTexture;
        sf::Texture midgroundTexture;

        sf::Texture tilesTexture;

        sf::Texture propTexture;
        sf::Sprite finish;

        std::vector<sf::Sprite> backgroundSprites;
        std::vector<sf::Sprite> midgroundSprites;

        std::vector<sf::Sprite> laneSprites;

        double parallax_offset = 0; // current offset of the background for the parallax effect
        double parallax_speed = 1.9; // speed /s of the background in parallax

        int tileamount = 10; //amount of time to repeat background

    public:
        explicit Background(std::weak_ptr<sf::RenderWindow> w);

        void draw(const double& delta) override;
    };

}

#endif //TURBOHIKER_BACKGROUNDSFML_H
