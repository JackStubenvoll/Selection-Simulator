//
// Created by Jack on 4/19/2021.
//

#include "animal.h"

namespace naturalSelection {
    
    Animal::Animal(const vec2 &iposition, const size_t &ispeed, const ci::Color &icolor) {
        position = iposition;
        speed = ispeed;
        color = icolor;
        energyLevel = energyToLive;
    }
    
    void Animal::eatFood() {
        energyLevel += energyToLive;
    }
    
    bool Animal::moveTo(vec2 newPosition) {
        int dx = (newPosition.x - position.x);
        int dy = (newPosition.y - position.y);
        if (dx == 0 && dy == 0) {
            return true;
        }
        for (size_t t = 0; t < speed; t++) {
            if (std::abs(dx) >= std::abs(dy)) {
                if (dx > 0) {
                    position.x++;
                } else {
                    position.x--;
                }
            } else {
                if (dy > 0) {
                    position.y++;
                } else {
                    position.y--;
                }
            }
            energyLevel = energyLevel - (((float) speed + 1) / 2);
        }
        return false;
    }
    
    bool Animal::canLive() {
        return energyLevel >= energyToLive;
    }
    
    bool Animal::canReproduce() {
        return energyLevel >= energyToReproduce;
    }
    
}