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
field::field(const int margin, const int containerSize, const size_t numPlants, const size_t numPixels, const size_t dayFrames) {
  xlowbound = margin;
  ylowbound = margin;
  xhighbound = containerSize - margin;
  yhighbound = containerSize - margin;
  numPlantsEachDay = numPlants;
  pixelsPerSide = numPixels;
  pixelsPerPixel = (xhighbound - xlowbound) / pixelsPerSide;
  framesPerDay = dayFrames;
  framesLeft = dayFrames;

}

void field::setup() {
    srand((unsigned int)time(NULL));
    for (size_t t = 0; t < numPlantsEachDay; t++) {
        generatePlant();    
    }
    for (size_t t = 0; t < startAnimals; t++) {
        generateHerbivore();
    }
    generatePredator();
    
}

/**
 * displays what's in the selectionField. Draws box, then plants.
 * displays number of plants at the top.
 */
void field::Display() const {

  ci::gl::color(ci::Color("blue"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(xlowbound, ylowbound), vec2(xhighbound, yhighbound)));

  for (size_t t = 0; t < plants.size(); t++) {
    displayPlant(plants[t]);
  }
  for (size_t t = 0; t < herbivores.size(); t++) {
      displayAnimal(herbivores[t]);
  }
  for (size_t t = 0; t < predators.size(); t++) {
      displayAnimal(predators[t]);
  }
  std::string displayString = "Current number of plants: " + std::to_string(plants.size());
  displayString+= "\nCurrent number of herbivores: " + std::to_string(herbivores.size());
  displayString+= " | Current number of predators: " + std::to_string(predators.size());
  displayString+= "\nDay: " + std::to_string(dayNum);
  displayString+= " | Frames Left: " + std::to_string(framesLeft);
  ci::gl::drawStringCentered(displayString,
                             vec2((xlowbound + xhighbound)/2, 0),
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

void field::displayAnimal(Animal animal) const {
    vec2 topLeft = ((animal.position * (float) pixelsPerPixel) + vec2(xlowbound, ylowbound));
    vec2 bottomRight = (((animal.position + vec2(1, 1)) * (float) pixelsPerPixel)) + vec2(xlowbound, ylowbound);
    ci::Rectf plantPixel(topLeft, bottomRight);
    ci::gl::color(animal.color);
    ci::gl::drawSolidRect(plantPixel);
}

/**
 * advances simulation one frame
 * First iterates over plants, updating positions.
 * Detects for a wall collision in same loop
 * Detects for collisions between plants by iterating over the list and then checking remaining plants
 */
void field::advanceOneFrame() {
  for (size_t i = 0; i < herbivores.size(); i++) {
      updateHerbivorePosition(herbivores[i]);
  }
  for (size_t i = 0; i < predators.size(); i++) {
      updatePredatorPosition(predators[i]);
      Animal a = predators[i];
      double temp = predators[i].energyLevel;
      if (predators[i].energyLevel <= 0) {
          predators.erase(predators.begin() + i);
          i--;
      }
  }
  framesLeft--;
}

void field::advanceDay() {
    dayNum++;
    plants.clear();
    for (size_t t = 0; t < numPlantsEachDay; t++) {
        generatePlant();
    }
    updateAnimalPopulation();
    framesLeft = framesPerDay;
}

void field::generatePlant() {
    vec2 plantCoords(rand() % 100, rand() % 100);
    Plant plant(plantCoords, ci::Color("green"));
    plants.push_back(plant);
}

void field::generateHerbivore() {
    vec2 animalCoords(rand() % 100, rand() % 100);
    double speed = 1;
    double intelligence = 4;
    ci::Color startAnimalColor(0.25, 0, 0.5);
    Animal animal(animalCoords, speed, intelligence, false, startAnimalColor);
    herbivores.push_back(animal);
}

void field::generatePredator() {
    vec2 animalCoords(rand() % 100, rand() % 100);
    double speed = 1;
    double intelligence = 4;
    ci::Color startAnimalColor(0.75, 0, 0.5);
    Animal animal(animalCoords, speed, intelligence, true, startAnimalColor);
    predators.push_back(animal);
}

void field::updateAnimalPopulation() {
    //update herbivores
    std::vector<Animal> updatedHerbivoresList;
    for (size_t t = 0; t < herbivores.size(); t++) {
        if (herbivores[t].canReproduce()) {
            while (herbivores[t].canReproduce()) {
                Animal *child = herbivores[t].reproduce();
                updatedHerbivoresList.push_back(*child);
            }
        } else if (herbivores[t].canLive()) {
            updatedHerbivoresList.push_back(herbivores[t]);
        }
    }
    herbivores.clear();
    for (size_t t = 0; t < updatedHerbivoresList.size(); t++) {
        herbivores.push_back(updatedHerbivoresList[t]);
    }
    //update predators
    std::vector<Animal> updatedPredatorsList;
    for (size_t t = 0; t < predators.size(); t++) {
        if (predators[t].canReproduce()) {
            while (predators[t].canReproduce()) {
                Animal *child = predators[t].reproduce();
                updatedPredatorsList.push_back(*child);
            }
//            Animal *child1 = predators[t].reproduce();
//            Animal *child2 = predators[t].reproduce();
//            updatedPredatorsList.push_back(*child1);
//            updatedPredatorsList.push_back(*child2);
        } else if (predators[t].canLive()) {
            updatedPredatorsList.push_back(predators[t]);
        }
    }
    predators.clear();
    for (size_t t = 0; t < updatedPredatorsList.size(); t++) {
        predators.push_back(updatedPredatorsList[t]);
    }
    
    if (herbivores.size() == 0) {
        for (size_t t = 0 ; t < startAnimals; t++) {
            generateHerbivore();
        }
    }
    if (predators.size() == 0) {
        generatePredator();
    }
}

void field::updateHerbivorePosition(Animal &herbivore) {
  size_t closestPlantIndex = 0;
  if (plants.size() == 0) {
      return;
  }
  double shortestDistance = distance(herbivore.position, plants[0].position);
  for (size_t t = 1; t < plants.size(); t++) {
      double thisDistance = distance(herbivore.position, plants[t].position); 
      if (thisDistance < shortestDistance) {
          shortestDistance = thisDistance;
          closestPlantIndex = t;
      }
  }
  //closest plant has been found
  if (herbivore.moveTo(plants[closestPlantIndex].position)) {
      herbivore.eatFood();
      plants.erase(plants.begin() + closestPlantIndex);
  }
  
  if (herbivore.canReproduce()) {
      Animal *child = herbivore.reproduce();
      herbivores.push_back(*child);
  }
  
}

void field::updatePredatorPosition(Animal &predator) {
    size_t closestHerbivoreIndex = 0;
    if (herbivores.size() <= predators.size()) {
        predator.starve();
        return;
    }
    double shortestDistance = distance(predator.position, herbivores[0].position);
    for (size_t t = 1; t < herbivores.size(); t++) {
        double thisDistance = distance(predator.position, herbivores[t].position);
        if (thisDistance < shortestDistance) {
            shortestDistance = thisDistance;
            closestHerbivoreIndex = t;
        }
    }
    //closest herbivore has been found
    if (predator.moveTo(herbivores[closestHerbivoreIndex].position)) {
        predator.eatFood();
        herbivores.erase(herbivores.begin() + closestHerbivoreIndex);
    }
    
    
}
    
double field::distance(vec2 position1, vec2 position2) {
    double xdistance = std::abs(position1.x - position2.x);
    double ydistance = std::abs(position1.y - position2.y);
    return xdistance + ydistance;
}


}  // namespace naturalSelection

