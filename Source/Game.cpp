#include "Game.h"
#include <chrono>
#include <memory>

#include "presentation/Factory.h"
#include "presentation/Transformation.h"

using namespace std::chrono;

Game::Game(int width, int height) {
  // open window
  window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode(width, height), "TurboHiker",
      sf::Style::Titlebar | sf::Style::Close);
  window->setKeyRepeatEnabled(false);

  // init transformation singleton
  turbohikerSFML::Transformation::instance(window);

  // make entity factory
  std::unique_ptr<turbohiker::EntityFactory> factory =
      std::make_unique<turbohikerSFML::Factory>(window);

  // create world and give it a factory
  world = std::make_unique<turbohiker::World>(std::move(factory));

  // init start screen
  initStartScreen();

  // start gameloop
  run();
}

void Game::run() {
  auto start = high_resolution_clock::now(); // start clock

  while (window->isOpen()) {
    auto stop = high_resolution_clock::now(); // stop clock
    auto duration = duration_cast<nanoseconds>(
        stop - start); // calculate time since last frame started

    double delta = double(duration.count()) /
                   1000000000; // time since last frame in seconds

    start = high_resolution_clock::now(); // start clock for next frame

    sf::Event event{};
    while (window->pollEvent(event)) // go through all events
    {
      if (event.type == sf::Event::Closed) {
        window->close();
      }

      // Respond to key pressed events
      if (event.type == sf::Event::EventType::KeyPressed) {
        if (!gameStarted) {
          gameStarted = true;
        }else if (world->gameOver() and event.key == 57) {
            reset();
            continue;
        } else {
          world->handleInput(event.key,
                             true); // pass keydown event to the world
        }
      }
      // Respond to key pressed events
      if (event.type == sf::Event::EventType::KeyReleased) {
        if (gameStarted) {
          world->handleInput(event.key, false); // pass keyup event to the world
        }
      }
    }

    window->clear(); // clear window

    if (!gameStarted) { // redraw start screen
      drawStartScreen();
    } else { // or draw the next game frame
      world->update(delta); // update world and
      world->draw(delta);   // draw it
    }

    window->display(); // display frame
  }
}

void Game::drawStartScreen() { window->draw(startText); }

void Game::initStartScreen() {
  font.loadFromFile("../Resources/fonts/Arial Unicode MS.ttf");
  startText.setFont(font);
  startText.setString("press any key to start");
  startText.setCharacterSize(
      turbohikerSFML::Transformation::instance()->textSize(0.5));

  startText.setPosition(turbohikerSFML::Transformation::instance()->x(-2.5),
                        turbohikerSFML::Transformation::instance()->y(0));

  startText.setFillColor(sf::Color::White);
}

void Game::reset() {
    turbohikerSFML::Transformation::instance()->reset();

    // make entity factory
    std::unique_ptr<turbohiker::EntityFactory> factory =
            std::make_unique<turbohikerSFML::Factory>(window);

    // create world and give it a factory
    world.reset();
    world = std::make_unique<turbohiker::World>(std::move(factory));
}
