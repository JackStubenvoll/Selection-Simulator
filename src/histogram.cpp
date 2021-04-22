//
// Created by Jack on 3/22/2021.
//
#include "histogram.h"
#include <math.h>

namespace naturalSelection {
Histogram::Histogram(const int imargin, const int windowSize, field &ifield, const int sectionNumber) {
  margin = imargin;
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
  selectionField = &ifield;
//  animals = selectionField.getParticlesOfMass(massFilter);
  numAnimals = (*selectionField).animals.size();
}

Histogram::Histogram() {}

void Histogram::updateGraph(field &ifield) {
  selectionField = &ifield;
//  animals = selectionField.getParticlesOfMass(massFilter);
  numAnimals = (*selectionField).animals.size();
  doMath();
}

void Histogram::doMath() {
    //want to plot average speed over time
    float sum = 0;
    for (size_t t = 0; t < numAnimals; t++) {
        sum+= (*selectionField).animals[t].speed;
    }
    float avg = sum / numAnimals;
    averages.push_back(avg);
    
    
     //clear previous map of velocities to number of plants with that velocity
//  speedMap.clear();
//  int velocitySum = 0;
//  int velocity;
//  //iterate through plants and fill out the speedMap, determines the maximum height the graph needs to display
//  for (int i = 0; i < numAnimals; i++) {
////    int temp1 = (int) pow(animals[i].velocity.x, 2);
////    int temp2 = (int) pow(animals[i].velocity.y, 2);
// //   velocity = (int) sqrt(temp1 + temp2);
//    speedMap[velocity] += 1;
//    if (speedMap[velocity] > maxHeight) {
//      maxHeight = speedMap[velocity];
//    }
//    if (velocity > maximumVelocity) {
//      maximumVelocity = velocity;
//    }
//    if (velocity < minimumVelocity) {
//      minimumVelocity = velocity;
//    }
//    velocitySum += velocity;
//  }
//  for (int i = minimumVelocity; i < maximumVelocity; i++) {
//    if (speedMap.find(i) == speedMap.end()) {
//      speedMap[i] = 0;
//    }
//  }
//  if (numAnimals != 0) {
//    avgVelocity = velocitySum / numAnimals;
//  }
}

void Histogram::Display() const {
  displayBox();
  if (numAnimals != 0) {
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
    int yCoord = bottomBound - (int) (averages[t] * 250);
    ci::gl::drawSolidCircle(vec2(xCoord, yCoord), 15);
  }
  //ci::gl::drawSolidCircle(vec2(1000, 1000), 70);
}

void Histogram::displayNumbers() const {
  for (int i = 0; i <= (bottomBound - topBound) / 250; i++) {
    ci::gl::drawStringCentered(std::to_string(i),
                               vec2(leftBound - margin / 2, bottomBound - (i * 250)),
                               ci::Color("white"),
                               ci::Font("Arial", 28));
  }
  int sectionWidth = (rightBound - leftBound) / (dayCounter + 1);
  int test = (((rightBound - leftBound) / 10) / sectionWidth);
  for (size_t t = 0; t < dayCounter; t++) {
    int sectionLeft = t * sectionWidth + leftBound;
    int sectionRight = (t + 1) * sectionWidth + leftBound;
    ci::gl::drawStringCentered(std::to_string(t),
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
  //y-axis label
  ci::gl::drawStringCentered("Average\n Speed",
                             vec2(rightBound + margin/2, (topBound + bottomBound) / 2),
                             ci::Color("white"),
                             ci::Font("Arial", 28));
}
}
