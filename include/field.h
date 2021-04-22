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
  field() = default;

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
  void generateAnimal();
  void updateAnimalPosition(Animal &animal);
  void updateAnimalPopulation();
  void setup();
  float distance(vec2 position1, vec2 position2);
 private:
  void displayPlant(Plant plant) const;
  void displayAnimal(Animal animal) const;
  size_t numPlantsEachDay; 
  size_t startAnimals = 2;
  size_t pixelsPerSide;
  int xlowbound;
  int xhighbound;
  int ylowbound;
  int yhighbound;
  size_t pixelsPerPixel;
  std::vector<Plant> plants;
  std::vector<Animal> animals;
};

}  // namespace naturalSelection
