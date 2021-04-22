#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "field.h"
#include "histogram.h"

namespace naturalSelection {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class naturalSelectionApp : public ci::app::App {
 public:
  naturalSelectionApp();

  void setup() override;
  void draw() override;
  void update() override;

  // provided that you can see the entire UI on your screen.
  const int windowSize = 1750;
  const int margin = 100;
  const int sectionSize = (windowSize) / 2;

 private:
  bool running;
  bool byFrame;
  field field_;
  const size_t numFramesPerDay = 300;
  size_t framesPassed = 0;
  //Histogram topRight;
  //Histogram bottomLeft;
  //Histogram bottomRight;
  //const int topRightSectionNum = 2;
  //const int bottomLeftSectionNum = 3;
  //const int bottomRightSectionNum = 4;
  //const float smallMass = 1;
  //const float mediumMass = 10;
  //const float largeMass = 100;
  //const int numParticles = 25;
  void keyDown(ci::app::KeyEvent event);
  
};

}  // namespace naturalSelection
