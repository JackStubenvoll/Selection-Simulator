//
// Created by Jack on 3/16/2021.
//
#include "plant.h"

namespace naturalSelection {

Plant::Plant(const vec2 &iposition, const ci::Color &icolor) {
  position = iposition;
  color = icolor;
}

bool Plant::isEqual(Plant other) {
    return (this->position == other.position) && this->color == other.color; 
}
}