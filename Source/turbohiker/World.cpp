//
// Created by viktor on 19.12.20.
//

#include "World.h"
#include "Random.h"
#include <algorithm>
#include <memory>

void turbohiker::World::update(const double &delta) {
  updateSection();

  // update each entity ( entities will set their new velocities but not
  // positions yet )
  for (const auto &ep : entities) {
    ep->update(delta);
  }

  // make the npc's choose their moves
  updateNpcLogic(delta);

  // will check if velocity valid and actually update their positions
  handlePhysics(delta);

  // check who has finished
  checkFinish();
}

void turbohiker::World::draw(const double &delta) {
  // draw each entity
  for (const auto &ep : entities) {
    ep->draw(delta);
  }

  // draw the scoreboard
  score->draw(delta);
}

turbohiker::World::World(std::unique_ptr<EntityFactory> f) {
  factory = std::move(f);

  // makes score subject
  score = std::make_unique<ScoreSubject>();
  // subscribes score observer to it
  score->attach(factory->makeScoreObserver());

  // make background entity
  entities.push_back(std::unique_ptr<Entity>(factory->makeBackground()));
  // make player entity
  entities.push_back(std::unique_ptr<Entity>(factory->makePlayer()));
  // make competing hikers
  std::unique_ptr<Entity> c1(factory->makeRacingHiker());
  std::unique_ptr<Entity> c2(factory->makeRacingHiker());
  std::unique_ptr<Entity> c3(factory->makeRacingHiker());

  // position them
  c1->setPos(Vector(-3, 0));
  c2->setPos(Vector(-1, 0));
  c3->setPos(Vector(1, 0));

  entities.push_back(std::move(c1));
  entities.push_back(std::move(c2));
  entities.push_back(std::move(c3));
}

void turbohiker::World::handleInput(const int &key, bool keydown) {
  auto player = dynamic_cast<turbohiker::Player *>(
      entities[1].get());      // second entity will always be player
  if (key == 57 and keydown) { // space
    player->shout();
    handleShout(player->position(), player->scoreId());
  } else {
    player->handleInput(key, keydown); // let player handle the input
  }
}

turbohiker::eType turbohiker::World::type() { return WorldT; }

void turbohiker::World::handlePhysics(const double &delta) {

  for (auto &ep : entities) {
    if (ep->type() == BackT) {
      continue;
    } // background has no physics

    handleCollisions(ep,
                     delta); // will modify velocity to resolve any collisions

    // calculate final new position
    ep->setPos(calcNewPos(ep, delta)); // set new pos
  }
}

void turbohiker::World::handleCollisions(std::unique_ptr<Entity> &entity,
                                         const double &delta) {

  std::set<std::set<int>> collisions; // store all collisions to for later

  entity->setNextPos(
      calcNewPos(entity, delta)); // calculate the next potential pos

  for (auto &ep : entities) {
    if (ep.get() == entity.get()) {
      continue;
    } // don't check for itself

    if (areColliding(ep, entity)) {
      std::set<int> collision; // note the collision
      collision.insert(entity->scoreId());
      collision.insert(ep->scoreId());
      collisions.insert(collision);

      Vector away = entity->nextpos().add(
          ep->nextpos().scalar(-1)); // vector from other entity to entity
      double pushforce = (entity->mass() / ep->mass()) *
                         (entity->getSpeed() /
                          ep->getSpeed()); // how strong to push other entity

      entity->setVel(entity->velocity().add(away).scalar(
          1 / pushforce)); // push entity back
      ep->setVel(ep->velocity().add(
          away.scalar(-pushforce))); // push other entity back as well
    }
  }

  // lastly check if entity not going out of bounds
  entity->setNextPos(
      calcNewPos(entity, delta)); // calculate potential new position
  if (outOfBounds(entity)) { // if that pos is out of bounds, adjust velocity
    entity->setVel(entity->velocity().add(
        Vector(-entity->velocity().x(), 0))); // remove horizontal component
  }

  updateCollisionScores(collisions, delta); // pass the collisions to scoreboard
}

Vector turbohiker::World::calcNewPos(std::unique_ptr<Entity> &entity,
                                     const double &delta) {
  double s = entity->getSpeed() * delta;     // adjusted speed
  Vector vel = entity->velocity().scalar(s); // rescale current velocity vector
  return entity->position().add(vel);        // add to current position
}

bool turbohiker::World::outOfBounds(std::unique_ptr<Entity> &entity) {
  if (entity->nextpos().x() + entity->size().x() / 2 > 4) { // left bound
    return true;
  }

  return entity->nextpos().x() - entity->size().x() / 2 < -4; // right bound
}

void turbohiker::World::updateSection() {
  auto player = dynamic_cast<turbohiker::Player *>(entities[1].get());

  double sec = player->position().y() / sectionSize; // get player section

  if (sec > section + 1 &&
      player->position().y() < 170) { // player is in new section
    section++;
    newSection();
  }
}

void turbohiker::World::newSection() {
  canSpeed = true;
  prunePassingHikers(); // remove hikers that are off screen

  double countchance = Random::Double();
  int spawncount;
  // 20% chance to spawn just one passing hiker
  // 50% chance to spawn two hikers
  // 20% chance to spawn three hiker
  // 10% chance to spawn four hikers
  if (countchance < 0.2) {
    spawncount = 1;
  } else if (countchance < 0.7) {
    spawncount = 2;
  } else if (countchance < 0.9) {
    spawncount = 3;
  } else {
    spawncount = 4;
  }

  std::vector<int> toOccupy =
      chooseLanes(spawncount); // chosen lanes to spawn an enemy

  for (const auto &lane : toOccupy) {
    spawnHiker(lane);
  }
}

std::vector<int> turbohiker::World::chooseLanes(const int &count) {
  std::vector<int> lanes = {};

  std::vector<int> choice = {0, 1, 2, 3}; // remaining choice of lanes
  for (int i = 0; i < count; i++) {       // amount of times to choose
    int r = Random::Int(0, choice.size() - 1); // choose from remaining choices
    lanes.push_back(choice[r]);                // save choice
    choice.erase(choice.begin() + r);          // remove from remaining choices
  }
  return lanes;
}

void turbohiker::World::spawnHiker(const int &lane) {
  Entity *hiker;

  bool spawntype; // false for hiker 1, true for hiker 2

  if (h1ToSpawn <= 0 and h2ToSpawn > 0) {
    spawntype = true;
  } else if (h1ToSpawn > 0 and h2ToSpawn <= 0) {
    spawntype = false;
  } else { // choose randomly between the two, 50%
    spawntype = Random::Int(0, 1);
  }

  if (spawntype) {
    hiker = factory->makePassingHiker1();
    h2ToSpawn--;
  } else {
    hiker = factory->makePassingHiker2(lane);
    h1ToSpawn--;
  }

  // position at top of section + a random distance < maxSpawnVar
  double posY = (section + 1) * sectionSize + Random::Double(0, maxSpawnVar);

  double posX = -3 + 2 * lane; // positon in correct lane

  hiker->setPos(Vector(posX, posY));

  entities.push_back(std::unique_ptr<Entity>(hiker));
}

void turbohiker::World::prunePassingHikers() {
  auto player = dynamic_cast<turbohiker::Player *>(
      entities[1].get()); // player always will be second entity

  std::vector<int> to_delete;

  for (int i = 5; i < entities.size();
       i++) { // find indexes of entities that are already off-screen
    if (entities[i]->position().y() <
        player->position().y() - entities[i]->size().y()) {
      to_delete.push_back(i);
    }
  }

  for (const auto &d :
       to_delete) { // call the destructor of each deleted entity
    entities[d].reset();
  }

  // following piece of code is from stackoverflow, what I understand is that
  // it sorts to_deleted vector and deletes the needed indexes from back to
  // front to avoid a shift messing up the indexes
  std::sort(to_delete.begin(),
            to_delete.end()); // Make sure the container is sorted

  // iterator magic
  for (std::reverse_iterator<std::vector<int>::iterator> j = to_delete.rbegin();
       j != to_delete.rend(); ++j) {
    entities.erase(entities.begin() + *j);
  }
}

void turbohiker::World::handleShout(const Vector &pos, int originator) {
  int lane = pos.getLane();

  for (auto &entity : entities) { // find the entity to shout at
    if (entity->position().getLane() == lane &&
        entity->position().y() >
            pos.y() && // must be in same lane and in front of player
        (entity->type() == PassHT1 ||
         entity->type() == PassHT2)) { // must be a passing hiker

      auto hiker = dynamic_cast<turbohiker::PassingHiker1 *>(entity.get());
      hiker->handleShout();           // pass the event to hiker
      if (hiker->type() == PassHT1) { // notify scoreboard
        score->notify(originator, 3);
      } else {
        score->notify(originator, 4);
      }
    }
  }
}

bool turbohiker::World::areColliding(std::unique_ptr<Entity> &e1,
                                     std::unique_ptr<Entity> &e2) {
  double e1w = e1->size().x(); // e1 width
  double e1h = e1->size().y(); // e1 height

  double e2w = e2->size().x(); // e2 width
  double e2h = e2->size().y(); // e2 height

  Vector e1p = Vector(e1->nextpos().x() - e1w / 2,
                      e1->nextpos().y() - e1h / 2); // bottom left corner e1
  Vector e2p = Vector(e2->nextpos().x() - e2w / 2,
                      e2->nextpos().y() - e2h / 2); // bottom left corner e2

  // I once understood this code, now I understand not to touch it
  bool col = e1p.x() + e1w >= e2p.x() && e1p.x() <= e2p.x() + e2w &&
             e1p.y() - e1h <= e2p.y() && e1p.y() >= e2p.y() - e2h;

  return col;
}

void turbohiker::World::updateNpcLogic(const double &delta) {
  for (int i = 2; i < 5; i++) { // [2-4] will always be the npc players
    auto npc = dynamic_cast<turbohiker::RacingHiker *>(entities[i].get());

    npc->cooldown -= delta; // decrement cooldown
    if (npc->cooldown <= 0) {
      npc->cooldown = 0;
    } // cap at 0
    else if (npc->cooldown > 0) {
      continue;
    } // if on cooldown, no moves

    std::tuple<double, bool> result = distanceEnemy(
        npc); // get distance to closest passing hiker and it's type
    double dist = std::get<0>(result);
    bool type = std::get<1>(result);
    double rand = Random::Double();

    if (dist > 0 and dist < 6) { // if enemy exist in lane and is visible
      if (rand < 1 - dist / 6) { // the nearer the enemy the more chance we go
                                 // into "panick" branch
        rand = Random::Double();
        if (type) {         // if stationary hiker
          if (rand < 0.6) { // try to shout rather than avoid
            npc->shout();
            handleShout(npc->position(), npc->scoreId());
            npc->cooldown = 0.10;
          } else {
            npc->changeLane();
            npc->cooldown = 0.25;
          }
        } else {            // moving hiker
          if (rand < 0.3) { // try to avoid rather than shout
            npc->shout();
            handleShout(npc->position(), npc->scoreId());
            npc->cooldown = 0.10;
          } else {
            npc->changeLane();
            npc->cooldown = 0.25;
          }
        }
      } else { // else we stay cool
        rand = Random::Double();
        if (rand < 0.5) { // try to slow down
          npc->slowDown();
          npc->cooldown = 0.5;
        } else { // and change lane
          npc->changeLane();
          npc->cooldown = 0.25;
        }
      }
    } else if (rand < 0.5 and
               canSpeed) { // no enemy visible and allowed to speed up, speed up
      npc->speedUp();
      npc->cooldown = 1.5;
    }

    if (npc->position().y() - entities[1]->position().y() <
        -4) { // we're too far behind
      npc->setPos(Vector(npc->position().x(),
                         entities[1]->position().y() - 2)); // teleport ahead
      npc->setSpeed(npc->speed_fast + 1);                   // speed up a little
      npc->cooldown = 1.5;
    }
    if (npc->position().y() - entities[1]->position().y() >
        6) {                            // we're too far ahead
      npc->setSpeed(npc->speed_normal); // slow down
      npc->cooldown = 1.5;
    }
  }
}

std::tuple<double, bool>
turbohiker::World::distanceEnemy(turbohiker::RacingHiker *npc) {
  double dist = 0;
  bool type = false; // false = hiker1 else hiker 2

  for (int i = 5; i < entities.size(); i++) { // enemies
    if (entities[i]->position().getLane() == npc->position().getLane() and
        entities[i]->position().y() >
            npc->position().y()) { // same lane and in front of npc
      double d = npc->position().distanceTo(entities[i]->position());
      if (d > dist) { // closer
        type = !(entities[i]->type() == PassHT1);
        dist = d;
      }
    }
  }

  return {dist, type};
}

void turbohiker::World::checkFinish() {
  for (int i = 1; i < 5; i++) { // player and npc's
    double topPos = entities[i]->position().y() + entities[i]->size().y() / 2;
    if (topPos > 186) { // past screen
      entities[i]->freeze();
    } else if (topPos > 180) { // past finish
      if (score->notify(entities[i]->scoreId(),
                        5)) { // notify scoreboard, and if all competitors
                              // finished, we say game finished
        finished = true;
      }
    }
  }
}

void turbohiker::World::updateCollisionScores(
    const std::set<std::set<int>> &new_set, const double &delta) {
  for (const auto &collision : new_set) { // go over each collision
    int first = *std::next(collision.begin(), 0);
    int second = *std::next(collision.begin(), 1);

    if (first < 0 and second < 0) { // two passing hikers hit each other
      continue;
    } else if (first > 0 and second > 0) { // both are competing hikers
      score->notify(first, 2, delta);
      score->notify(second, 2, delta);
    } else { // a competitor and a passing hiker
      int subject;
      int action;
      if (first > 0) { // first is the competitor
        subject = first;
        action = std::abs(second) - 1; // scoreID -> scoreboard action
      } else {                         // second is the competitor
        subject = second;
        action = std::abs(first) - 1; // scoreID -> scoreboard action
      }
      score->notify(subject, action, delta);
    }
  }
}

bool turbohiker::World::gameOver() { return finished; }

turbohiker::World::~World() {
  for (auto &e : entities) { // destroy all entities
    e.reset();
  }
  score.reset();   // destroy score
  factory.reset(); // destroy factor
}
