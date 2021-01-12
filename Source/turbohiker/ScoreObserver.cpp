//
// Created by viktor on 30.12.20.
//
#include "ScoreObserver.h"

bool turbohiker::ScoreObserver::update(int entity, int action, const double& delta) {
    if (action < 5){
        scores[entity] += penalties[action] * delta;
    }else if (action == 5) {
        if (not finished[entity]){
            scores[entity] += penalties[action] * (3 - runnersFinished);
            finished[entity] = true;
            runnersFinished++;
        }
    }else{
        reset();
    }
    return (runnersFinished == 4);
}

void turbohiker::ScoreObserver::reset() {
    scores = {0,0,0,0};
    runnersFinished = 0;
    finished = {false,false,false,false};
}
