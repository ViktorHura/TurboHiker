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

        sf::RectangleShape darken; // dark overlay

        sf::Text summaryText;

        // draws summary at end of game
        void DrawSummary(std::shared_ptr<sf::RenderWindow>& w);

        // competitor int to name
        static std::string intToName(const int& i);

        // sorted vector of competitor int and their score
        std::vector<std::tuple<int,double>> sorted;
        std::string resultString; // the summary string

    public:
        explicit Scoreboard(std::weak_ptr<sf::RenderWindow> w);
        ~Scoreboard() = default;

        void draw(const double& delta) override;
    };
}

#endif //TURBOHIKER_SCOREBOARD_H
