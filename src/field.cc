#include "field.h"
#include "cinder/Color.h"
//TODO make all variables camelCase
namespace naturalSelection {

using glm::vec2;
using std::vector;
/**
 * initializes numOfPlants to be 0, and the bounds of the box so I don't have to keep redoing calculation
 * @param margin
 * @param windowSize
 */
field::field(const int margin, const int containerSize, const size_t numPlants, const size_t numPixels) {
  //int containerSize = (windowSize - margin) / 4;
  numOfPlants = 0;
  xlowbound = margin;
  ylowbound = margin;
  xhighbound = containerSize - margin;
  yhighbound = containerSize - margin;
  numPlantsEachDay = numPlants;
  pixelsPerSide = numPixels;
  pixelsPerPixel = (xhighbound - xlowbound) / pixelsPerSide;

}

/**
 * displays what's in the container. Draws box, then plants.
 * displays number of plants at the top.
 */
void field::Display() const {

  ci::gl::color(ci::Color("blue"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(xlowbound, ylowbound), vec2(xhighbound, yhighbound)));

  for (size_t i = 0; i < numOfPlants; i++) {
    displayPlant(plants[i]);
  }
  std::string displayString = "Current number of plants: ";
  displayString+= std::to_string(numOfPlants);
  ci::gl::drawStringCentered(displayString,
                             vec2((xlowbound + xhighbound)/2, ylowbound / 2),
                             ci::Color("white"),
                             ci::Font("Arial", 28));
}

void field::displayPlant(Plant plant) const {
    ci::Rectf plantPixel(plant.position * (float) pixelsPerSide, (plant.position + vec2(1, 1)) * (float) pixelsPerSide);
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
  for (size_t i = 0; i < numOfPlants; i++) {
      updateAnimalPositions(plants[i]);
  }
}

void field::advanceDay() {
    //TODO advance one day
}

/**
 * adds a particle object to the container.
 * @param iparticle
 */
void field::generatePlant() {
    srand((unsigned int)time(NULL));
    vec2 plantCoords(rand() % 100, rand() % 100);
    Plant plant(plantCoords, ci::Color("green"));
    plants.push_back(plant);
    numOfPlants++;
    
  
}

void field::updateAnimalPositions(Plant &particle) {
  //TODO update animal positions
}


}  // namespace naturalSelection

