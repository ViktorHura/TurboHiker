//
// Created by viktor on 24.12.20.
//

#ifndef TURBOHIKER_PASSINGHIKER2_H
#define TURBOHIKER_PASSINGHIKER2_H

#include "Entity.h"
#include "PassingHiker1.h"

namespace turbohiker {

    /**
     * \class PassingHiker2
     * \ingroup turbohiker
     * \brief abstract class to handle static hiker logic
     */
class PassingHiker2 : public PassingHiker1 {
    protected:
        int desiredLane = 0;

    public:
        PassingHiker2();

        void setDesired(const int& l);

        eType type() override;

        void update(const double& delta) override;

        void handleShout() override;

        virtual void react() override = 0;
    };

}

#endif //TURBOHIKER_PASSINGHIKER2_H
