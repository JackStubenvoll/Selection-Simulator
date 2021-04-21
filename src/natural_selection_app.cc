#include "natural_selection_app.h"
#include <iostream>
#include "plant.h"
#include "cinder/gl/gl.h"

namespace naturalSelection {

using glm::vec2;

/**
 * constructor for app
 */
naturalSelectionApp::naturalSelectionApp() {
  container_ = field(margin, sectionSize, 100, 100);
  ci::app::setWindowSize(windowSize, windowSize);
}

/**
 * setup, sets playing to false by default. Adds plants to container.
 */
void naturalSelectionApp::setup() {
  srand((unsigned int)time(NULL));
  playing = false;
  //topRight = Histogram(margin, windowSize, smallMass, container_, topRightSectionNum);
  //bottomLeft = Histogram(margin, windowSize, mediumMass, container_, bottomLeftSectionNum);
  //bottomRight = Histogram(margin, windowSize, largeMass, container_, bottomRightSectionNum);
}

/**
 * draw first draws background, then calls the container's display function.
 */
void naturalSelectionApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::color(ci::Color("green"));
  ci::gl::drawLine(vec2(windowSize / 2, 0), vec2(windowSize  / 2, windowSize));
  ci::gl::drawLine(vec2(0, windowSize / 2), vec2(windowSize, windowSize / 2));

  container_.Display();
  //topRight.Display();
  //bottomLeft.Display();
  //bottomRight.Display();
}

/**
 * only updates the canvas if simulation is in the playing state.
 */
void naturalSelectionApp::update() {
  srand((unsigned int)time(NULL));
  if (playing) {
      container_.advanceOneFrame();
  }
  topRight.updateGraph(container_);
  bottomLeft.updateGraph(container_);
  bottomRight.updateGraph(container_);


}

/**
 * detects if a key is pressed:
 * Space paused the simulation
 * Tab moves the simulation forward one frame if the simulation is paused.
 * Up arrow key adds a particle to the simulation.
 * @param event
 */
void naturalSelectionApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      //update state to pause the function
      if (playing) {
        playing = false;
      } else {
        playing = true;
      }
      break;
    case ci::app::KeyEvent::KEY_TAB:
      if (!playing) {
          container_.advanceOneFrame();
        topRight.updateGraph(container_);
        bottomLeft.updateGraph(container_);
        bottomRight.updateGraph(container_);
      }
      break;
  }

}


}  // namespace naturalSelection
