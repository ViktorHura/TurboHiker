//
// Created by viktor on 29.12.20.
//

#ifndef TURBOHIKER_RACINGHIKER_H
#define TURBOHIKER_RACINGHIKER_H

#include "Entity.h"

namespace turbohiker {

    /**
     * \class RacingHiker
     * \ingroup turbohiker
     * \brief abstract class to handle competing hiker logic
     */
    class RacingHiker : public Entity{
        int desiredlane = 0; // lane to stay in
    public:
        const double speed_normal = 5;
        const double speed_slow = 4;
        const double speed_fast = 6;

        double cooldown = 0; // cooldown in seconds before we make another decision

        /**
         * creates npc, with the correct number i in [0,2]
         * @param i
         */
        explicit RacingHiker(int i);
        ~RacingHiker() override = default;

        eType type() override;

        void update(const double& delta) override;

        /**
         * change lane
         */
        void changeLane();

        /**
         * slow down
         */
        void slowDown();

        /**
         * speed up
         */
        void speedUp();

        /**
         * shout handler
         */
        virtual void shout() = 0;

    };

}

#endif //TURBOHIKER_RACINGHIKER_H
