#include "field.h"
#include "cinder/Color.h"
//TODO make all variables camelCase
namespace naturalSelection {
    size_t distance(vec2 position1, vec2 position2) {
        size_t xdistance = std::abs(position1.x - position2.x);
        size_t ydistance = std::abs(position1.y - position2.y);
        return xdistance + ydistance;
    }

using glm::vec2;
using std::vector;
/**
 * initializes numOfPlants to be 0, and the bounds of the box so I don't have to keep redoing calculation
 * @param margin
 * @param windowSize
 */
field::field(const int margin, const int containerSize, const size_t numPlants, const size_t numPixels) {
  //int containerSize = (windowSize - margin) / 4;
  xlowbound = margin;
  ylowbound = margin;
  xhighbound = containerSize - margin;
  yhighbound = containerSize - margin;
  numPlantsEachDay = numPlants;
  pixelsPerSide = numPixels;
  pixelsPerPixel = (xhighbound - xlowbound) / pixelsPerSide;

}

void field::setup() {
    srand((unsigned int)time(NULL));
    for (size_t t = 0; t< numPlantsEachDay; t++) {
        generatePlant();    
    }
    
}

/**
 * displays what's in the container. Draws box, then plants.
 * displays number of plants at the top.
 */
void field::Display() const {

  ci::gl::color(ci::Color("blue"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(xlowbound, ylowbound), vec2(xhighbound, yhighbound)));

  for (size_t i = 0; i < plants.size(); i++) {
    displayPlant(plants[i]);
  }
  std::string displayString = "Current number of plants: ";
  displayString+= std::to_string(plants.size());
  ci::gl::drawStringCentered(displayString,
                             vec2((xlowbound + xhighbound)/2, ylowbound / 2),
                             ci::Color("white"),
                             ci::Font("Arial", 28));
}

void field::displayPlant(const Plant plant) const {
    vec2 topLeft = ((plant.position * (float) pixelsPerPixel) + vec2(xlowbound, ylowbound));
    vec2 bottomRight = (((plant.position + vec2(1, 1)) * (float) pixelsPerPixel)) + vec2(xlowbound, ylowbound);
    ci::Rectf plantPixel(topLeft, bottomRight);
    ci::gl::color(plant.color);
    ci::gl::drawSolidRect(plantPixel);
}

/**
 * advances simulation one frame
 * First iterates over plants, updating positions.
 * Detects for a wall collision in same loop
 * Detects for collisions between plants by iterating over the list and then checking remaining plants
 */
void field::advanceOneFrame() {
  for (size_t i = 0; i < animals.size(); i++) {
      updateAnimalPosition(animals[i]);
  }
}

void field::advanceDay() {
    plants.clear();
    for (size_t t = 0; t < numPlantsEachDay; t++) {
        generatePlant();
    }
}

void field::generatePlant() {
    vec2 plantCoords(rand() % 100, rand() % 100);
    Plant plant(plantCoords, ci::Color("green"));
    plants.push_back(plant);
}

void field::updateAnimalPopulation() {
    for (size_t t = 0; t < animals.size(); t++) {
        if (animals[t].canReproduce()) {
            
        }
    }
}

void field::updateAnimalPosition(Animal &animal) {
  size_t closestPlantIndex = 0;
  size_t shortestDistance = INT_MAX;
  for (size_t t = 1; t < plants.size(); t++) {
      size_t thisDistance = distance(animal.position, plants[t].position); 
      if (thisDistance < shortestDistance) {
          shortestDistance = thisDistance;
          closestPlantIndex = t;
      }
  }
  //closest plant has been found
  if (animal.moveTo(plants[closestPlantIndex].position)) {
      animal.eatFood();
      plants.erase(plants.begin() + closestPlantIndex);
  }
  
}


}  // namespace naturalSelection

