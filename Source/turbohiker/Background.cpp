//
// Created by viktor on 20.12.20.
//

#include "Background.h"

void turbohiker::Background::update(const double &delta) {}

turbohiker::Background::Background() { setPos(Vector(-4, -2.5)); }

turbohiker::eType turbohiker::Background::type() { return BackT; }
