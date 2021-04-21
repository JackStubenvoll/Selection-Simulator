//
// Created by Jack on 3/22/2021.
//
#include "histogram.h"
#include <math.h>

namespace naturalSelection {
Histogram::Histogram(const int imargin, const int windowSize, float particleMass, const field &icontainer, const int sectionNumber) {
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
  container = icontainer;
  massFilter = particleMass;
//  filteredParticles = container.getParticlesOfMass(massFilter);
  numFilteredParticles = filteredParticles.size();
}

Histogram::Histogram() {}

void Histogram::updateGraph(field &icontainer) {
  container = icontainer;
//  filteredParticles = container.getParticlesOfMass(massFilter);
  numFilteredParticles = filteredParticles.size();
  doMath();
}

void Histogram::doMath() {
  //clear previous map of velocities to number of plants with that velocity
  speedMap.clear();
  maximumVelocity = -1;
  minimumVelocity = INT_MAX; //arbitrary upper bound on velocity, this is impossible.
  int velocitySum = 0;
  int velocity;
  //iterate through plants and fill out the speedMap, determines the maximum height the graph needs to display
  for (int i = 0; i < numFilteredParticles; i++) {
//    int temp1 = (int) pow(filteredParticles[i].velocity.x, 2);
//    int temp2 = (int) pow(filteredParticles[i].velocity.y, 2);
 //   velocity = (int) sqrt(temp1 + temp2);
    speedMap[velocity] += 1;
    if (speedMap[velocity] > maxHeight) {
      maxHeight = speedMap[velocity];
    }
    if (velocity > maximumVelocity) {
      maximumVelocity = velocity;
    }
    if (velocity < minimumVelocity) {
      minimumVelocity = velocity;
    }
    velocitySum += velocity;
  }
  for (int i = minimumVelocity; i < maximumVelocity; i++) {
    if (speedMap.find(i) == speedMap.end()) {
      speedMap[i] = 0;
    }
  }
  if (numFilteredParticles != 0) {
    avgVelocity = velocitySum / numFilteredParticles;
  }
}

void Histogram::Display() const {
  displayBox();
  if (numFilteredParticles != 0) {
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
  int numSections = maximumVelocity - minimumVelocity + 1;
  int sectionWidth = (rightBound - leftBound) / numSections;
  for (int t = 0; t < numSections; t++) {
    int sectionLeft = t * sectionWidth + leftBound;
    int sectionRight = (t + 1) * sectionWidth + leftBound;
    int sectionBottom = bottomBound;
    int barHeight = speedMap.at(minimumVelocity + t);
    int sectionTop = bottomBound - barHeight * 100;
    ci::gl::drawSolidRect( ci::Rectf(vec2(sectionLeft, sectionBottom), vec2(sectionRight, sectionTop)));
  }
}

void Histogram::displayNumbers() const {
  for (int i = 0; i <= (bottomBound - topBound) / 100; i++) {
    ci::gl::drawStringCentered(std::to_string(i),
                               vec2(leftBound - margin / 2, bottomBound - (i * 100)),
                               ci::Color("white"),
                               ci::Font("Arial", 28));
  }
  int numSections = maximumVelocity - minimumVelocity + 1;
  int sectionWidth = (rightBound - leftBound) / numSections;
  int test = (((rightBound - leftBound) / 10) / sectionWidth);
  for (int t = 0; t < numSections; t+= std::max(1, (((rightBound - leftBound) / 10) / sectionWidth))) {
    int sectionLeft = t * sectionWidth + leftBound;
    int sectionRight = (t + 1) * sectionWidth + leftBound;
    ci::gl::drawStringCentered(std::to_string(minimumVelocity + t),
                               vec2((sectionLeft + sectionRight)/2, bottomBound + margin / 2),
                               ci::Color("white"),
                               ci::Font("Arial", 28));
  }
}

void Histogram::displayText() const {
  //average velocity
  ci::gl::drawStringCentered("Average velocity is: " + std::to_string(avgVelocity),
                             vec2((leftBound + rightBound) / 2, topBound - margin / 2),
                             ci::Color("white"),
                             ci::Font("Arial", 28));
  //x-axis label
  ci::gl::drawStringCentered("Speed Of Particles",
                             vec2((leftBound + rightBound) / 2, bottomBound + margin * 3 / 4),
                             ci::Color("white"),
                             ci::Font("Arial", 28));
  //y-axis label
  ci::gl::drawStringCentered("# of \nParticles \nw/ Speed",
                             vec2(rightBound + margin/2, (topBound + bottomBound) / 2),
                             ci::Color("white"),
                             ci::Font("Arial", 28));
}
}
