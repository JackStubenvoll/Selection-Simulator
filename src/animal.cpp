//
// Created by Jack on 4/19/2021.
//

#include "animal.h"

namespace naturalSelection {
    
    Animal::Animal(const vec2 &iposition, const double &ispeed, const double &iintelligence, const bool predator, const ci::Color &icolor) {
        position = iposition;
        speed = ispeed;
        intelligence = iintelligence;
        isPredator = predator;
        color = icolor;
        energyLevel = energyToLive;
    }
    
    Animal::Animal(const vec2 &iposition, const double &ispeed, const double &iintelligence, const bool predator,
                   const ci::Color &icolor, double startEnergy) {
        position = iposition;
        speed = ispeed;
        intelligence = iintelligence;
        isPredator = predator;
        color = icolor;
        energyLevel = startEnergy;
    }
    
    
    void Animal::eatFood() {
        if (isPredator) {
            //killCooldown = 50;
            energyLevel += energyToLive;
        } 
        energyLevel += energyToLive;
    }
    
    void Animal::starve() {
        if (energyLevel > 0) {
            energyLevel-= 0.4;
        }
        
    }
    
    bool Animal::moveTo(vec2 newPosition) {
        //srand((unsigned int)time(NULL));
        float dx = (newPosition.x - position.x);
        float dy = (newPosition.y - position.y);
        //animal on top of food source
        if (dx == 0 && dy == 0) {
            return true;
        }
        //prevents predators from ravenously consuming all prey
//        if (killCooldown > 0) {
//            killCooldown--;
//            return false;
//        }
        //food is out of range of energyLevel
        if ((dx + dy) * (1 + speed/20.0)  > energyLevel) {
            double moveProbability = rand() % 10 + 1;
            if (moveProbability > intelligence) {
                return false;
            }
        }
        if (speed == 0) {
            energyLevel--;
        }
        double tileMoveCounter = speed;
        while (tileMoveCounter > 0 && energyLevel > 0)  {
            dx = (newPosition.x - position.x);
            dy = (newPosition.y - position.y);
            if (position == newPosition) {
                return true;
            }
            if ((dx + dy) * (1 + speed/20.0) > energyLevel) {
                double moveProbability = rand() % 10 + 1;
                if (moveProbability < intelligence) {
                    return false;
                }
            }
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
            if (isPredator) {
                energyLevel = energyLevel - (1 + speed/20.0) / 4.0;
            } else {
                energyLevel = energyLevel - (1 + speed/20.0);
            }
            
            tileMoveCounter= tileMoveCounter - 1;
        }
        return false;
    }
    
    bool Animal::canLive() {
        return energyLevel >= energyToLive;
    }
    
    bool Animal::canReproduce() {
        return energyLevel >= energyToReproduce * 2;
    }
    
    Animal* Animal::reproduce() {
        //srand((unsigned int)time(NULL));
        energyLevel-= energyToReproduce;
        int speedOffsetProb = rand() % 10;
        double speedOffset = 0;
        switch (speedOffsetProb) {
            case 0:
                speedOffset = -1;
                break;
            case 9:
                speedOffset = 1;
                break;
        }
        double newSpeed = speed + speedOffset;
        double intOffset = (rand() % 101 - 50) / 100.0;
        double newInt = intelligence + intOffset;
        float gOffset = (rand() % 11 - 5) / 100.f;
        ci::Color newColor(color.r, color.g + gOffset, color.b);
        vec2 newPosition(rand() % 100, rand() % 100);
        Animal *child = new Animal(newPosition, newSpeed, newInt, isPredator, newColor, energyToReproduce);
        return child;
        
    }
    
}