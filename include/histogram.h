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
  Histogram(const int imargin, const int windowSize, const int sectionNumber, std::string dataType);
  Histogram();
  void updateGraph(double datapoint);
  void Display() const;
  void displayBox() const;
  void displayText() const;
  void displayGraph() const;
  void displayNumbers() const;
  std::vector<double> datapoints;
    size_t dayCounter = 0;
 private:
    
  int margin;
  int leftBound;
  int topBound;
  int rightBound;
  int bottomBound;
  size_t numDatapoints = 0;
  std::string nameOfData;

};

}
