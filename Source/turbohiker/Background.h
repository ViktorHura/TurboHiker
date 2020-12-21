//
// Created by viktor on 20.12.20.
//

#ifndef TURBOHIKER_BACKGROUND_H
#define TURBOHIKER_BACKGROUND_H


#include "Entity.h"

namespace turbohiker {

    /**
     * \class Background
     * \ingroup turbohiker
     * \brief abstract class to draw background elements
     */
    class Background : public Entity {

    public:
        eType type() override;

        Background();

        void update(const double &delta) override;


    };

}

#endif //TURBOHIKER_BACKGROUND_H
