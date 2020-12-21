//
// Created by viktor on 19.12.20.
//

#ifndef TURBOHIKER_WORLD_H
#define TURBOHIKER_WORLD_H

#include <vector>
#include "Entity.h"
#include "EntityFactory.h"
#include <memory>

namespace turbohiker {

    /**
     * \class World
     * \ingroup turbohiker
     * \brief represents the game world, handles physics, hold entities and delegates draw requests
     */
    class World : public Entity  {

        std::vector<std::unique_ptr<Entity>> entities;
        std::unique_ptr<EntityFactory> factory;

        double sectionSize = 12;
        double section = 0;
        double maxSpawnVar = 8;

        int h1ToSpawn = 3;
        int h2ToSpawn = 3;


        void updateSection();

        void newSection();

        std::vector<int> chooseLanes(const int& count);

        void spawnHiker(const int& lane);

        void handlePhysics(const double& delta);

        bool outOfBounds(std::unique_ptr<Entity>& entity, const Vector& newpos);



    public:
        eType type() override;

        /**
         * create the world, must provide a concrete entity factory
         * @param f
         */
        explicit World(std::unique_ptr<EntityFactory> f);

        /**
         * will draw all entities on screen
         */
        void draw(const double& delta) override;

        /**
         * update game logic
         * @param delta
         */
        void update(const double& delta) override;

        /**
         * forwards inputs to player
         * @param key
         */
        void handleInput(const int& key, bool keydown);

    };
}

#endif //TURBOHIKER_WORLD_H
