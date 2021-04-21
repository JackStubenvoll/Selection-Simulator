//
// Created by Jack on 3/16/2021.
//
#pragma once

#include "cinder/gl/gl.h"
#include <string>
using glm::vec2;

namespace naturalSelection {
class Plant {
  public:
   Plant(const vec2 &iposition, const ci::Color &icolor);
   vec2 position;
   ci::Color color;


};
}
