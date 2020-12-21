//
// Created by viktor on 21.12.20.
//

#ifndef TURBOHIKER_PASSINGHIKER1_H
#define TURBOHIKER_PASSINGHIKER1_H

#include "Entity.h"

namespace turbohiker {

    /**
     * \class PassingHiker1
     *
     * \brief abstract class to handle static hiker logic
     */
    class PassingHiker1 : public Entity {
    public:
        PassingHiker1();

        eType type() override;

        void update(const double& delta) override;
    };

}

#endif //TURBOHIKER_PASSINGHIKER1_H
