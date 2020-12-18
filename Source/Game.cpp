#include "Game.h"
#include <chrono>
#include <iostream>
#include <memory>

#include "presentation/Transformation.h"

using namespace std::chrono;

Game::Game(int width, int height) {
    // open window
    window = std::make_shared<sf::RenderWindow>( sf::VideoMode(width, height), "TurboHiker");

    // init transformation singleton
    Transformation::instance(window);

    // init start screen
    initStartScreen();

    // start gameloop
    run();
}

void Game::run() {
    auto start = high_resolution_clock::now(); // start clock

    while (window->isOpen())
    {
        auto stop = high_resolution_clock::now(); // stop clock
        auto duration = duration_cast<milliseconds>(stop - start); // calculate time since last frame started

        double delta = duration.count() / 1000; // time since last frame in milliseconds

        start = high_resolution_clock::now(); // start clock for next frame

        sf::Event event{};
        while (window->pollEvent(event)) // go through all events
        {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            //Respond to key pressed events
            if (event.type == sf::Event::EventType::KeyPressed){
                if (!gameStarted){
                    gameStarted = true;
                }else{

                }
            }

        }

        window->clear(); // clear window

        if (!gameStarted){      // redraw start screen
            drawStartScreen();
        }else{                  // or draw the next game frame

        }

        window->display();       // display frame
    }
}

void Game::drawStartScreen() {
    window->draw(startText);
}

void Game::initStartScreen() {
    font.loadFromFile("../Resources/fonts/arial.ttf");
    startText.setFont(font);
    startText.setString("press any key to start");
    startText.setCharacterSize(Transformation::instance()->textSize(0.5));

    startText.setPosition(Transformation::instance()->x(-2.5), Transformation::instance()->y(0));

    startText.setFillColor(sf::Color::White);
}
