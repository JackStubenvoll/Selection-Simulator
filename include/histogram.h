//
// Created by Jack on 3/22/2021.
//
#pragma once

#include "cinder/gl/gl.h"
#include "plant.h"
#include "field.h"

namespace naturalSelection {
using std::vector;
/**
 * the class which will represent individual histograms for each type of particle.
 */
class Histogram {
 public:
  Histogram(const int imargin, const int windowSize, float particleMass, const field &icontainer, const int sectionNumber);
  Histogram();
  void updateGraph(field &icontainer);
  void Display() const;
  void doMath();
  void displayBox() const;
  void displayText() const;
  void displayGraph() const;
  void displayNumbers() const;
  std::map<int, int> speedMap; //key is speed, value is number of plants
 private:
  int margin;
  int leftBound;
  int topBound;
  int rightBound;
  int bottomBound;
  field container;
  float massFilter;
  int avgVelocity;
  int numFilteredParticles;
  vector<Plant> filteredParticles;
  int maxHeight = -1;
  int minimumVelocity;
  int maximumVelocity;

};

}
