//
// Created by viktor on 30.12.20.
//

#ifndef TURBOHIKER_SCOREOBSERVER_H
#define TURBOHIKER_SCOREOBSERVER_H

#include <vector>

namespace turbohiker {

    /**
     * \class ScoreObserver
     * \ingroup turbohiker
     * \brief observes the score object, holds score counts
     */
    class ScoreObserver {
        const std::vector<double> penalties = {
                -100, // hit passinghiker 1 (per second)
                -200, // hit passinghiker 2 (per second)
                -100, // hit another competitor (per second)
                -100,  // shouted at passinghiker 1
                -50,  // shouted at passinghiker 2
                1000, // finish bonus constant
        };

        // for each competitor, if they finished
        std::vector<bool> finished = {false,false,false,false};

    protected:
        // for each competitor, their scores
        std::vector<double> scores = {0,0,0,0};
        int runnersFinished = 0;
    public:
        ScoreObserver() = default;

        /**
         * entities
         *  0 : npc0
         *  1 : npc1
         *  2 : npc2
         *  3 : player
         *
         * actions
         *  0 : hit passinghiker 1
         *  1 : hit passinghiker 2
         *  2 : hit another competitor
         *  3 : shouted at passinghiker 1
         *  4 : shouted at passinghiker 2
         *  5 : arrived at finish
         *
         * @param entity
         * @param action
         * @return whether everyone arrived yet
         */
        bool update(int entity, int action, const double& delta);

        virtual void draw(const double& delta) = 0;
    };
}

#endif //TURBOHIKER_SCOREOBSERVER_H
