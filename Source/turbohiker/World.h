//
// Created by viktor on 19.12.20.
//

#ifndef TURBOHIKER_WORLD_H
#define TURBOHIKER_WORLD_H

#include <vector>
#include "Entity.h"
#include "EntityFactory.h"
#include "ScoreSubject.h"
#include <memory>
#include <set>

namespace turbohiker {

    /**
     * \class World
     * \ingroup turbohiker
     * \brief represents the game world, handles physics, hold entities and delegates draw requests
     */
    class World : public Entity  {

        /**
         * 0 : background Entity
         * 1 : player Entity
         * 2-4 : npc Entity
         * 5-? : passing hikers
         */
        std::vector<std::unique_ptr<Entity>> entities;
        std::unique_ptr<EntityFactory> factory;

        std::unique_ptr<ScoreSubject> score;

        double sectionSize = 10;
        double section = 0; // current section
        double maxSpawnVar = 8; // maximum y-distance in hiker spawn variance

        int h1ToSpawn = 3; // type 1 hikers left to spawn
        int h2ToSpawn = 3; // type 2 hikers left to spawn

        bool canSpeed = false; // can npc's speed up yet?
                                // flag will be set after first section, to give player a small head start

        bool finished = false; // is game finished?

        /// checks if player has reached a new section
        void updateSection();

        /// called when player reaches a new section
        void newSection();

        /// choouses count lanes, used for spawning hikers
        static std::vector<int> chooseLanes(const int& count);

        /// creates a passing hiker
        void spawnHiker(const int& lane);

        /// physics, called each frame
        void handlePhysics(const double& delta);

        /// is an entity out of bounds(left-right bound)
        static bool outOfBounds(std::unique_ptr<Entity>& entity);

        /// remove hikers that are off-screen already
        void prunePassingHikers();

        /// find the right passing hiker and invoke shout on it
        void handleShout(const Vector& pos, int originator);

        /// check and resolve collisions for a given entity
        void handleCollisions(std::unique_ptr<Entity>& entity, const double& delta);

        /// check if two entities are colliding
        static bool areColliding(std::unique_ptr<Entity> &e1, std::unique_ptr<Entity> &e2);

        /// calculate potential new position based on current velocity
        static Vector calcNewPos(std::unique_ptr<Entity>& entity, const double& delta);

        /// update npc logic
        void updateNpcLogic(const double& delta);

        /// distance to closest enemy on same lane, 0 if no enemy in sight and type of enemy
        std::tuple<double, bool> distanceEnemy(turbohiker::RacingHiker * npc);

        /// checks for each racer if they reached the end
        /// freezes them, notifies scoreboard
        void checkFinish();

        /// gets collision data and notifies the scoreboard of the corresponding collisions
        void updateCollisionScores(const std::set<std::set<int>>& new_set, const double& delta);
    public:
        eType type() override;

        /**
         * create the world, must provide a concrete entity factory
         * @param f
         */
        explicit World(std::unique_ptr<EntityFactory> f);

        ~World() override;

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
         * @param keydown
         */
        void handleInput(const int& key, bool keydown);

        /**
         * have all racers reached the end?
         * @return bool
         */
        bool gameOver();
    };
}

#endif //TURBOHIKER_WORLD_H
