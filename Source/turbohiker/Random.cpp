//
// Created by viktor on 21.12.20.
//

#include "Random.h"
#include <cstdlib>
#include <ctime>

turbohiker::Random *turbohiker::Random::instance() {
  if (!_instance) {
    _instance = new Random();
  }
  return _instance;
}

turbohiker::Random::Random() {
  srand(time(nullptr) );
  //srand(0);
}

turbohiker::Random *turbohiker::Random::_instance = nullptr;

int turbohiker::Random::Int(const int &min, const int &max) {
  return rand() % (max - min + 1) + min;
}

double turbohiker::Random::Double(const double &min, const double &max) {
  return min + Double() * (max - min);
}

double turbohiker::Random::Double() { return (double)rand() / RAND_MAX; }
