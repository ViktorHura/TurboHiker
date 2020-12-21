//
// Created by viktor on 19.12.20.
//

#ifndef TURBOHIKER_PLAYER_H
#define TURBOHIKER_PLAYER_H

#include "Entity.h"

namespace turbohiker {

    /**
     * \class Player
     *
     * \brief abstract class to handle player logic
     */
    class Player : public Entity {
        /// inputs
        bool u = false;
        bool l = false;
        bool r = false;
        bool d = false;

    protected:
        const double speed_normal = 6;
        const double speed_slow = 3;
        const double speed_fast = 9;

    public:
        Player();

        eType type() override;

        void update(const double& delta) override;

        /**
         * take input, updates u l d r, vars
         * @param key
         */
        void handleInput(const int& key, bool keydown);

    };
}


#endif //TURBOHIKER_PLAYER_H
