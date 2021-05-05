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
        Animal(const vec2 &iposition, const double &ispeed, const double &iintelligence, const bool predator, const ci::Color &icolor);
        vec2 position;
        double speed;
        double intelligence;
        bool isPredator = false;
        ci::Color color;
        void eatFood();
        void starve();
        bool moveTo(vec2 newPosition);
        bool canLive();
        bool canReproduce();
        Animal* reproduce();
    private:
        double killCooldown = 0;
        double energyLevel;
        double energyToLive = 20;
        double energyToReproduce = 40;
    };
}