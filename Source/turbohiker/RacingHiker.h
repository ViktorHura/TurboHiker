//
// Created by viktor on 29.12.20.
//

#ifndef TURBOHIKER_RACINGHIKER_H
#define TURBOHIKER_RACINGHIKER_H

#include "Entity.h"

namespace turbohiker {

    /**
     * \class RacingHiker
     *
     * \brief abstract class to handle competing hiker logic
     */
    class RacingHiker : public Entity{
        int action = 0;
        int desiredlane = 0;

    public:
        const double speed_normal = 5;
        const double speed_slow = 4;
        const double speed_fast = 6;

        double cooldown = 0;

        explicit RacingHiker(int i);

        eType type() override;

        void update(const double& delta) override;

        void changeLane();
        void slowDown();
        void speedUp();

        virtual void shout() = 0;

    };

}

#endif //TURBOHIKER_RACINGHIKER_H
