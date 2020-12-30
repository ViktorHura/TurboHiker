//
// Created by viktor on 19.12.20.
//

#ifndef TURBOHIKER_ENTITYFACTORY_H
#define TURBOHIKER_ENTITYFACTORY_H

#include "Entity.h"
#include "Player.h"
#include "Background.h"
#include "PassingHiker1.h"
#include "PassingHiker2.h"
#include "RacingHiker.h"
#include <memory>

namespace turbohiker {

    /**
     * \class EntityFactory
     * \ingroup turbohiker
     * \brief Abstract factory for creating entities
     */
    class EntityFactory {
    public:
        EntityFactory() = default;

        virtual turbohiker::Player* makePlayer() = 0;

        virtual turbohiker::Background* makeBackground() = 0;

        virtual turbohiker::PassingHiker1* makePassingHiker1() = 0;

        virtual turbohiker::PassingHiker2* makePassingHiker2(const int& initialLane) = 0;

        virtual turbohiker::RacingHiker* makeRacingHiker() = 0;
    };
}

#endif //TURBOHIKER_ENTITYFACTORY_H
