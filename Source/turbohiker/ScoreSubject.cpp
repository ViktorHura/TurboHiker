//
// Created by viktor on 30.12.20.
//

#include "ScoreSubject.h"

void turbohiker::ScoreSubject::attach(turbohiker::ScoreObserver *observer) {
  observers.push_back(std::unique_ptr<ScoreObserver>(observer));
}

bool turbohiker::ScoreSubject::notify(int entity, int action,
                                      const double &delta) {
  bool rtn = false;
  for (const auto &observer : observers) {
    if (observer->update(entity, action, delta)) {
      rtn = true; // if a single observer says that game is over, it is over
      break;
    }
  }
  return rtn;
}

void turbohiker::ScoreSubject::draw(const double &delta) {
  for (const auto &observer : observers) {
    observer->draw(delta);
  }
}
