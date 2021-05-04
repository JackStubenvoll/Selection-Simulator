//
// Created by Jack on 3/22/2021.
//
#include "histogram.h"
#include <math.h>

namespace naturalSelection {
Histogram::Histogram(const int imargin, const int windowSize, const int sectionNumber, std::string dataType) {
  margin = imargin;
  nameOfData = dataType;
  switch (sectionNumber) {
    case 2:
      topBound = margin;
      leftBound = windowSize / 2 + margin;
      rightBound = windowSize - margin;
      bottomBound = windowSize / 2 - margin;
      break;
    case 3:
      topBound = windowSize / 2 + margin;
      leftBound = margin;
      rightBound = windowSize / 2 - margin;
      bottomBound = windowSize - margin;
      break;
    case 4:
      topBound = windowSize / 2 + margin;
      leftBound = windowSize / 2 + margin;
      rightBound = windowSize - margin;
      bottomBound = windowSize - margin;
      break;
  }
    pixelsPerJump = (bottomBound - topBound) / 10;

}

Histogram::Histogram() {}

void Histogram::updateGraph(double datapoint) {
  datapoints.push_back(datapoint);
  numDatapoints++;
  if (datapoints.size() > 1) {
      min = *std::min_element(datapoints.begin(), datapoints.begin() + datapoints.size());
      max = *std::max_element(datapoints.begin(), datapoints.begin() + datapoints.size());
      pixelsScalar = (int) ((float) (bottomBound - topBound) / (max - min));
      double temp = max - min;
      valuePerJump = temp / 10.0;
    }
}

void Histogram::Display() const {
  displayBox();
  if (numDatapoints > 1) {
    displayText();
    displayGraph();
    displayNumbers();
  }


}

void Histogram::displayBox() const {
  ci::gl::color(ci::Color("blue"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(leftBound, topBound), vec2(rightBound, bottomBound)));
}

void Histogram::displayGraph() const {
  ci::gl::color(ci::Color("white"));
  int sectionWidth = (rightBound - leftBound) / (dayCounter + 1);
  
  for (size_t t = 0; t < dayCounter; t++) {
    int sectionLeft = t * sectionWidth + leftBound;
    int sectionRight = (t + 1) * sectionWidth + leftBound;
    int xCoord = (sectionLeft + sectionRight) / 2;
    int yCoord = bottomBound - (int) ((datapoints[t] - min) * pixelsScalar);
    ci::gl::drawSolidCircle(vec2(xCoord, yCoord), 15);
  }
  //ci::gl::drawSolidCircle(vec2(1000, 1000), 70);
}

void Histogram::displayNumbers() const {
  for (float i = 0; i <= 10; i++) {
    ci::gl::drawStringCentered(std::to_string(min + valuePerJump * i),
                               vec2(leftBound - margin / 2, bottomBound - i * pixelsPerJump),
                               ci::Color("white"),
                               ci::Font("Arial", 28));
  }
  int sectionWidth = (rightBound - leftBound) / (dayCounter + 1);
  for (size_t t = 0; t < dayCounter; t++) {
    int sectionLeft = t * sectionWidth + leftBound;
    int sectionRight = (t + 1) * sectionWidth + leftBound;
    ci::gl::drawStringCentered(std::to_string(t + 1),
                               vec2((sectionLeft + sectionRight)/2, bottomBound + margin / 2),
                               ci::Color("white"),
                               ci::Font("Arial", 28));
  }
}

void Histogram::displayText() const {
  //x-axis label
  ci::gl::drawStringCentered("Days",
                             vec2((leftBound + rightBound) / 2, bottomBound + margin * 3 / 4),
                             ci::Color("white"),
                             ci::Font("Arial", 28));
  //Name of Data
    ci::gl::drawStringCentered(nameOfData,
                               vec2((leftBound + rightBound) / 2, topBound - margin * 3 / 4),
                               ci::Color("white"),
                               ci::Font("Arial", 28));
}
}
