//
// Created by viktor on 30.12.20.
//

#ifndef TURBOHIKER_SCORESUBJECT_H
#define TURBOHIKER_SCORESUBJECT_H

#include <vector>
#include <memory>
#include "ScoreObserver.h"

namespace turbohiker {

    /**
     * \class ScoreSubject
     * \ingroup turbohiker
     * \brief gathers score information, registers and notifies observers
     */
    class ScoreSubject {
        std::vector<std::unique_ptr<ScoreObserver>> observers;
    public:
        ScoreSubject() = default;
        ~ScoreSubject() = default;

        /**
         * attaches observer to this subject
         * @param observer
         */
        void attach(ScoreObserver* observer);

        /**
         * notifies all observers of the event
         *
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
         *  6 : reset the game
         *
         * @param entity
         * @param action
         * @return bool if game is over or not
         */
        bool notify(int entity, int action, const double& delta = 1);

        /**
         * send draw command to observers
         * @param delta
         */
        void draw(const double& delta);
    };
}


#endif //TURBOHIKER_SCORESUBJECT_H
