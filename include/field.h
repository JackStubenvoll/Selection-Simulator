#pragma once

#include "cinder/gl/gl.h"
#include "plant.h"
#include "animal.h"

using glm::vec2;

namespace naturalSelection {

/**
 * The field in which all animals and plants exist.
 */
class field {
 public:
  field(const int margin, const int containerSize, const size_t numPlants, const size_t numPixels);
  field();

  /**
   * Displays the border of the field and the current positions of plants and animals.
   */
  void Display() const;

  /**
   * Updates the positions of all animals.
   */
  void advanceOneFrame();
  void advanceDay();

  void generatePlant();
  void updateAnimalPositions(Plant &particle);
 private:
  void displayPlant(Plant plant) const;
  size_t numPlantsEachDay; 
  size_t pixelsPerSide;
  int xlowbound;
  int xhighbound;
  int ylowbound;
  int yhighbound;
  size_t pixelsPerPixel;
  size_t numOfPlants;
  size_t numOfAnimals;
  std::vector<Plant> plants;
};

}  // namespace naturalSelection
