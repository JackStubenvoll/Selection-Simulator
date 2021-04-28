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
        Animal(const vec2 &iposition, const double &ispeed, const double &iintelligence, const ci::Color &icolor);
        vec2 position;
        double speed;
        double intelligence;
        ci::Color color;
        void eatFood();
        bool moveTo(vec2 newPosition);
        bool canLive();
        bool canReproduce();
        Animal* reproduce();
    private:
        double energyLevel;
        const double energyToLive = 20;
        const double energyToReproduce = 40;
    };
}