//
// Created by viktor on 30.12.20.
//

#include "Scoreboard.h"
#include "Transformation.h"
#include <cmath>

void turbohikerSFML::Scoreboard::draw(const double &delta) {
  std::shared_ptr<sf::RenderWindow> w =
      window.lock(); // borrow ownership of window

  double playerScore = std::floor(scores[3]);
  scoreCounterText.setString(std::to_string((int)playerScore));

  scoreCounterText.setPosition(
      Transformation::instance()->posFixed(turbohiker::Utils::Vector(-4, 3)));

  w->draw(scoreCounterText);

  if (runnersFinished == 4) {
    DrawSummary(w);
  }
}

turbohikerSFML::Scoreboard::Scoreboard(std::weak_ptr<sf::RenderWindow> w) {
  window = std::move(w);

  font.loadFromFile("../Resources/fonts/Arial Unicode MS.ttf");
  scoreCounterText.setFont(font);
  scoreCounterText.setString("0");
  scoreCounterText.setCharacterSize(
      turbohikerSFML::Transformation::instance()->textSize(0.5));

  scoreCounterText.setFillColor(sf::Color::Yellow);
  scoreCounterText.setStyle(sf::Text::Bold);

  darken = sf::RectangleShape(turbohikerSFML::Transformation::instance()->size(
      turbohiker::Utils::Vector(8, 6)));
  darken.setFillColor(sf::Color(0, 0, 0, 150));

  summaryText.setFont(font);
  summaryText.setCharacterSize(
      turbohikerSFML::Transformation::instance()->textSize(0.35));

  summaryText.setFillColor(sf::Color::White);
  summaryText.setStyle(sf::Text::Bold);
}

bool compareSc(const std::tuple<int, double> &f,
               const std::tuple<int, double> &s) {
  return std::get<1>(f) > std::get<1>(s);
}

void turbohikerSFML::Scoreboard::DrawSummary(
    std::shared_ptr<sf::RenderWindow> &w) {

  darken.setPosition(
      Transformation::instance()->posFixed(turbohiker::Utils::Vector(-4, 3)));

  summaryText.setPosition(
      Transformation::instance()->posFixed(turbohiker::Utils::Vector(-2, 2)));

  if (!ranked) {
    resultString = "Results\n\n";

    sorted.clear();
    for (int i = 0; i < scores.size(); i++) {
      std::tuple<int, double> tmp(i, scores[i]);
      sorted.push_back(tmp);
    }

    std::sort(sorted.begin(), sorted.end(), compareSc);
    ranked = true;

    for (int i = 0; i < sorted.size(); i++) {
      std::string val = std::to_string(std::get<1>(sorted[i]));
      val.erase(val.end() - 4, val.end());

      resultString += "#" + std::to_string(i + 1) + " " +
                      intToName(std::get<0>(sorted[i])) + " : " + val + "\n";
    }

    resultString += "\nPress Space to Play Again";
  }

  summaryText.setString(resultString);

  w->draw(darken);
  w->draw(summaryText);
}

std::string turbohikerSFML::Scoreboard::intToName(const int &i) {
  switch (i) {
  case 0: // npc0
    return "Josh";
  case 1: // npc1
    return "Ivan";
  case 2: // npc2
    return "Margy";
  case 3: // player
    return "You";
  default: // if something goes wrong
    return "Error";
  }
}

void turbohikerSFML::Scoreboard::reset() {
  ScoreObserver::reset();
  ranked = false;
}
