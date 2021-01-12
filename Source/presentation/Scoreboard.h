//
// Created by viktor on 30.12.20.
//

#ifndef TURBOHIKER_SCOREBOARD_H
#define TURBOHIKER_SCOREBOARD_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../turbohiker/ScoreObserver.h"

namespace turbohikerSFML {

    /**
    * \class Scoreboard
    * \ingroup turbohikerSFML
    * \brief SFML scoreboard presentation
    */
    class Scoreboard : public turbohiker::ScoreObserver{
        std::weak_ptr<sf::RenderWindow> window;

        sf::Font font;
        sf::Text scoreCounterText;

        sf::RectangleShape darken;

        sf::Text summaryText;

        void DrawSummary(std::shared_ptr<sf::RenderWindow>& w);

        static std::string intToName(const int& i);

        std::vector<std::tuple<int,double>> sorted;
        bool ranked = false;
        std::string resultString;

    public:
        explicit Scoreboard(std::weak_ptr<sf::RenderWindow> w);
        void draw(const double& delta) override;
        void reset() override;
    };
}

#endif //TURBOHIKER_SCOREBOARD_H
