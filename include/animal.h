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
        Animal(const vec2 &iposition, const float &ispeed, const ci::Color &icolor);
        vec2 position;
        float speed;
        ci::Color color;
        void eatFood();
        bool moveTo(vec2 newPosition);
        bool canLive();
        bool canReproduce();
        Animal* reproduce();
    private:
        float energyLevel;
        const float energyToLive = 20;
        const float energyToReproduce = 40;
    };
}