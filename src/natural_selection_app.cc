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
        field_ = field(margin, sectionSize, 100, 100);
  ci::app::setWindowSize(windowSize, windowSize);
}

/**
 * setup, sets running to false by default. Adds plants to container.
 */
void naturalSelectionApp::setup() {
  srand((unsigned int)time(NULL));
  running = true;
  byFrame = true;
  field_.setup();
  //topRight = Histogram(margin, windowSize, smallMass, field_, topRightSectionNum);
  //bottomLeft = Histogram(margin, windowSize, mediumMass, field_, bottomLeftSectionNum);
  //bottomRight = Histogram(margin, windowSize, largeMass, field_, bottomRightSectionNum);
}

/**
 * draw first draws background, then calls the container's display function.
 */
void naturalSelectionApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  ci::gl::drawLine(vec2(windowSize / 2, 0), vec2(windowSize  / 2, windowSize));
  ci::gl::drawLine(vec2(0, windowSize / 2), vec2(windowSize, windowSize / 2));
  ci::Rectf byFrameIndicator(vec2(0, 0), vec2(10, 10));
  if (byFrame) {
      ci::gl::color(ci::Color("red"));
  } else {
      ci::gl::color(ci::Color("blue"));
  }
  ci::gl::drawSolidRect(byFrameIndicator);
  field_.Display();
  //topRight.Display();
  //bottomLeft.Display();
  //bottomRight.Display();
}

/**
 * only updates the canvas if simulation is in the running state.
 */
void naturalSelectionApp::update() {
  srand((unsigned int)time(NULL));
  if (running) {
      if (byFrame) {
          field_.advanceOneFrame();
      } else {
          field_.advanceDay();
      }
  }
  //topRight.updateGraph(field_);
  //bottomLeft.updateGraph(field_);
  //bottomRight.updateGraph(field_);


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
      running = !running;
      break;
    case ci::app::KeyEvent::KEY_TAB:
      if (!running) {
          if (byFrame) {
              field_.advanceOneFrame();
          } else {
              field_.advanceDay();
          }
          
        //topRight.updateGraph(field_);
        //bottomLeft.updateGraph(field_);
        //bottomRight.updateGraph(field_);
      }
      break;
    case ci::app::KeyEvent::KEY_KP0:
      byFrame = !byFrame;
      break;
  }

}


}  // namespace naturalSelection
