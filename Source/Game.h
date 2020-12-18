/**
 * \class Game
 *
 * \brief interacts with world by calling the world’s methods to enable the game logic
 *        holds the gameloop and calculates the delta between frames
 */

#ifndef TURBOHIKER_GAME_H
#define TURBOHIKER_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>

class Game {
    std::shared_ptr<sf::RenderWindow> window;

    sf::Font font;
    sf::Text startText;

    bool gameStarted = false;

    /// start the game loop after construction
    void run();

    /// draws start screen, waiting for user to start the game
    void drawStartScreen();

    /// inits start screen
    void initStartScreen();

public:
    /**
     * Constructs the game, world, opens the window and starts the game loop
     *
     * \note Window should be in 4:3 aspect ratio
     *
     * @param width initial width of window in pixels
     * @param height initial height of window in pixels
     */
    Game(int width, int height);



};


#endif //TURBOHIKER_GAME_H
