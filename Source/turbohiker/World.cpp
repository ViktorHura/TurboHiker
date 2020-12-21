//
// Created by viktor on 19.12.20.
//

#include "World.h"
#include "Random.h"
#include <iostream>
#include <memory>

void turbohiker::World::update(const double &delta) {
  updateSection();

  // update each entity ( entities will set their new velocities but not
  // positions yet )
  for (const auto &ep : entities) {
    ep->update(delta);
  }
  // will check if velocity valid and actually update their positions
  handlePhysics(delta);
}

void turbohiker::World::draw(const double &delta) {
  // draw each entity
  for (const auto &ep : entities) {
    ep->draw(delta);
  }
}

turbohiker::World::World(std::unique_ptr<EntityFactory> f) {
  factory = std::move(f);

  // make background entity
  entities.push_back(std::unique_ptr<Entity>(factory->makeBackground()));
  // make player entity
  entities.push_back(std::unique_ptr<Entity>(factory->makePlayer()));
}

void turbohiker::World::handleInput(const int &key, bool keydown) {
  auto player = static_cast<turbohiker::Player *>(
      entities[1].get()); // second entity will always be player thus static
  if (key == 57) {        // space
                          //
  } else {
    player->handleInput(key, keydown); // let player handle the input
  }
}

turbohiker::eType turbohiker::World::type() { return WorldT; }

void turbohiker::World::handlePhysics(const double &delta) {
  for (auto &ep : entities) {
    double s = ep->getSpeed() * delta;
    Vector vel = ep->velocity().scalar(s);
    Vector newpos = ep->position().add(vel); // calculate potential new position

    if (outOfBounds(ep,
                    newpos)) { // if that pos is out of bounds, adjust velocity
      ep->setVel(Vector(0, ep->velocity().y())); // remove horizontal component
    }

    vel = ep->velocity().scalar(s); // calculate final new position
    newpos = ep->position().add(vel);
    ep->setPos(newpos); // set new pos
  }
}

bool turbohiker::World::outOfBounds(std::unique_ptr<Entity> &entity,
                                    const Vector &newpos) {
  if (newpos.x() + entity->size().x() / 2 > 4) { // left bound
    return true;
  }

  return newpos.x() - entity->size().x() / 2 < -4; // right bound
}

void turbohiker::World::updateSection() {
  auto player = static_cast<turbohiker::Player *>(entities[1].get());

  double sec = player->position().y() / sectionSize;

  if (sec > section + 1 &&
      player->position().y() < 240) { // player is in new section
    section++;
    // std::cout << "next section " << player->position().toString() <<
    // std::endl;
    newSection();
  }
}

void turbohiker::World::newSection() {
  double countchance = Random::instance()->Double();
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

  std::vector<int> toOccupy = chooseLanes(spawncount);

  for (const auto &lane : toOccupy) {
    spawnHiker(lane);
  }
}

std::vector<int> turbohiker::World::chooseLanes(const int &count) {
  std::vector<int> lanes = {};

  std::vector<int> choice = {0, 1, 2, 3};
  for (int i = 0; i < count; i++) {
    int r = Random::instance()->Int(0, choice.size() - 1);
    lanes.push_back(choice[r]);
    choice.erase(choice.begin() + r);
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
    spawntype = Random::instance()->Int(0, 1);
  }

  if (spawntype) {
    hiker = factory->makePassingHiker1();
    h2ToSpawn--;
  } else {
    hiker = factory->makePassingHiker1();
    h1ToSpawn--;
  }

  double posY =
      (section + 1) * sectionSize + Random::instance()->Double(0, maxSpawnVar);

  double posX = -3 + 2 * lane;

  hiker->setPos(Vector(posX, posY));

  hiker->setVel(Vector(0, -1));
  hiker->setSpeed(2);

  std::cout << hiker->position().toString() << std::endl;

  entities.push_back(std::unique_ptr<Entity>(hiker));
}
