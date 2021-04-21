//
// Created by Jack on 4/19/2021.
//

#pragma once

#include "cinder/gl/gl.h"
#include <string>
using glm::vec2;

namespace naturalSelection {
    class Animal {
    public:
        Animal(const vec2 &iposition, const vec2 &ispeed, const ci::Color &icolor);
        vec2 position;
        vec2 speed;
        ci::Color color;
        
        
    };
}