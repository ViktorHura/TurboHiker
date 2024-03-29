#ifndef TURBOHIKER_ENTITY_H
#define TURBOHIKER_ENTITY_H

#include "Utils.h"

using namespace turbohiker::Utils;

namespace turbohiker
{
    enum eType{
        EntityT,
        WorldT,
        PlayerT,
        BackT,
        PassHT1,
        PassHT2,
        RacingH,
    };

    /**
    * \defgroup turbohiker
    * \brief static library that holds game logic
    *
    * \class Entity
    * \ingroup turbohiker
    * \brief most abstract game object
    */
    class Entity {
        Vector pos{};
        Vector nextPos{};
        Vector vel{};
        Vector size_{};
        double speed = 0;
        double mass_ = 1;
    protected:
        int score_id = 5; // used for scoring
        bool frozen = false;
    public:
        /**
         * get entity type
         */
         virtual eType type();

         virtual ~Entity() = default;

         /**
          * get score id
          */
        virtual int scoreId();

        /**
         * freeze entity
         */
        void freeze();

        /**
         * draws the entity on screen
         */
        virtual void draw(const double& delta)=0;

        /**
         * will update the entity's internal state
         */
        virtual void update(const double& delta) = 0;

        /**
         * gets position
         * @return
         */
        Vector position() const;

        /**
         * gets next potential position
         * @return
         */
        Vector nextpos() const;

        /**
         * gets velocity
         * @return
         */
        Vector velocity() const;

        /**
         * gets size
         * @return
         */
        Vector size() const;

        /**
         * get entity mass
         * @return
         */
        double mass() const;

        /**
         * get speed
         * @return
         */
        double getSpeed() const;

        /**
         * set mass
         * @param m
         * @return
         */
        Entity& setMass(const double& m);

        /**
         * set speed
         * @param s
         * @return
         */
        Entity& setSpeed(const double& s);

        /**
         * set position vector
         * @param position
         * @return
         */
        Entity& setPos(const Vector& position);

        /**
         * set next potential position vector
         * @param position
         * @return
         */
        Entity& setNextPos(const Vector& position);

        /**
         * set velocity vector
         * @param velocity
         * @return
         */
        Entity& setVel(const Vector& velocity);

        /**
         * set size vector
         * @param size
         * @return
         */
        Entity& setSize(const Vector& size);
    };

}
#endif //TURBOHIKER_ENTITY_H
