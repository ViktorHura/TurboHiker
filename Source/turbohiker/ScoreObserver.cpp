//
// Created by viktor on 30.12.20.
//
#include "ScoreObserver.h"

bool turbohiker::ScoreObserver::update(int entity, int action,
                                       const double &delta) {
  if (action < 5) {
    scores[entity] += penalties[action] * delta;
  } else if (action == 5) {
    if (not finished[entity]) {
      scores[entity] += penalties[action] * (3 - runnersFinished);
      finished[entity] = true;
      runnersFinished++;
    }
  }
  return (runnersFinished == 4);
}

