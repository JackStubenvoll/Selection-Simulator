#pragma once

#include "cinder/gl/gl.h"
#include "plant.h"
#include "animal.h"

using glm::vec2;

namespace naturalSelection {

/**
 * The selectionField in which all herbivores and plants exist.
 */
class field {
 public:
  field(const int margin, const int containerSize, const size_t numPlants, const size_t numPixels, const size_t dayFrames);
  field() = default;

  /**
   * Displays the border of the selectionField and the current positions of plants and herbivores.
   */
  void Display() const;

  /**
   * Updates the positions of all herbivores.
   */
  void advanceOneFrame();
  void advanceDay();

  void generatePlant();
  void generateHerbivore();
  void generatePredator();
  void updateHerbivorePosition(Animal &herbivore);
  void updatePredatorPosition(Animal &predator);
  void updateAnimalPopulation();
  void setup();
  double distance(vec2 position1, vec2 position2);
  std::vector<Plant> plants;
  std::vector<Animal> herbivores;
  std::vector<Animal> predators;
 private:
  void displayPlant(Plant plant) const;
  void displayAnimal(Animal animal) const;
  size_t framesPerDay;
  size_t framesLeft;
  size_t numPlantsEachDay; 
  size_t startAnimals = 5;
  size_t pixelsPerSide;
  size_t dayNum = 0;
  int xlowbound;
  int xhighbound;
  int ylowbound;
  int yhighbound;
  size_t pixelsPerPixel;
};

}  // namespace naturalSelection
