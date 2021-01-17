//
// Created by viktor on 21.12.20.
//

#ifndef TURBOHIKER_PASSINGHIKER1_H
#define TURBOHIKER_PASSINGHIKER1_H

#include "Entity.h"

namespace turbohiker {

    /**
     * \class PassingHiker1
     * \ingroup turbohiker
     * \brief abstract class to handle moving hiker logic
     */
    class PassingHiker1 : public Entity {
    protected:
        double speed = 2;
        double reactTime = 0; // used for visual rep
    public:
        PassingHiker1();
        ~PassingHiker1() override = default;

        eType type() override;

        void update(const double& delta) override;

        /**
         * handle being shouted at
         */
        virtual void handleShout();

        /**
         * react to shout (visual handler)
         */
        virtual void react() = 0;
    };

}

#endif //TURBOHIKER_PASSINGHIKER1_H
