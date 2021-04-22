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
  Histogram(const int imargin, const int windowSize, field &ifield, const int sectionNumber);
  Histogram();
  void updateGraph(field &ifield);
  void Display() const;
  void doMath();
  void displayBox() const;
  void displayText() const;
  void displayGraph() const;
  void displayNumbers() const;
  std::vector<float> averages;
    size_t dayCounter = 0;
 private:
    
  int margin;
  int leftBound;
  int topBound;
  int rightBound;
  int bottomBound;
  field *selectionField;
  int avgVelocity;
  size_t numAnimals;
  int maxHeight = -1;

};

}
