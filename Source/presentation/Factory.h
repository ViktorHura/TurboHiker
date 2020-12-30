//
// Created by viktor on 19.12.20.
//

#ifndef TURBOHIKER_FACTORY_H
#define TURBOHIKER_FACTORY_H

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../turbohiker/EntityFactory.h"


namespace turbohikerSFML {
    /**
    * \defgroup turbohikerSFML
    * \brief SFML representation of the turbohiker library
    *
    * \class Factory
    * \ingroup turbohikerSFML
    * \brief concrete factory for creating SFML entities
    */
    class Factory : public turbohiker::EntityFactory {
        /// weak pointer to the window object
        std::weak_ptr<sf::RenderWindow> window;
        int i = -1;
    public:
        /**
         * must provide SFML window for SFML entity factory
         * @param w
         */
        explicit Factory(std::weak_ptr<sf::RenderWindow> w);

        /**
         * makes player
         * @return
         */
        turbohiker::Player* makePlayer() override;

        /**
         * makes background
         * @return
         */
        turbohiker::Background* makeBackground() override;

        /**
         * makes passinghiker1
         * @return
         */
        turbohiker::PassingHiker1* makePassingHiker1() override;

        /**
         * makes passinghiker2
         * @return
         */
        turbohiker::PassingHiker2* makePassingHiker2(const int& initialLane) override;

        turbohiker::RacingHiker* makeRacingHiker() override;
    };
}

#endif //TURBOHIKER_FACTORY_H
