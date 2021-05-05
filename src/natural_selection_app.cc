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
        field_ = field(margin, sectionSize, 200, 100);
  ci::app::setWindowSize(windowSize, windowSize);
}

/**
 * setup, sets running to false by default. Adds plants to selectionField.
 */
void naturalSelectionApp::setup() {
  srand((unsigned int)time(NULL));
  running = true;
  byFrame = true;
  field_.setup();
  speed = Histogram(margin, windowSize, 2, "Speed");
  population = Histogram(margin, windowSize, 3, "Population");
  intelligence = Histogram(margin, windowSize, 4, "Intelligence");
}

/**
 * draw first draws background, then calls the selectionField's display function.
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
  speed.Display();
  population.Display();
  intelligence.Display();
}

/**
 * only updates the canvas if simulation is in the running state.
 */
void naturalSelectionApp::update() {
  srand((unsigned int)time(NULL));
  if (running) {
      if (byFrame) {
          field_.advanceOneFrame();
          framesPassed++;
      } else {
          updateHistograms();
          field_.advanceDay();
          if (framesPassed == 0) {
              byFrame = !byFrame;
          }
      }
  }
  
  if (framesPassed >= numFramesPerDay) {
      framesPassed = 0;
      byFrame = !byFrame;
  }
  
  //population.updateGraph(field_);
  //intelligence.updateGraph(field_);


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
              framesPassed++;
              if (framesPassed >= numFramesPerDay) {
                  framesPassed = 0;
                  byFrame = !byFrame;
              }
          } else {
              field_.advanceDay();
              updateHistograms();
              byFrame = !byFrame;
          }
          
        
      }
      break;
    case ci::app::KeyEvent::KEY_KP0:
      byFrame = !byFrame;
      break;
  }

}

void naturalSelectionApp::updateHistograms() {
    population.updateGraph((float) field_.herbivores.size());
    speed.updateGraph(animalValueAverage(field_.herbivores, 1));
    intelligence.updateGraph(animalValueAverage(field_.herbivores, 2));
    
    population.dayCounter++;
    speed.dayCounter++;
    intelligence.dayCounter++;
}

    
double naturalSelectionApp::animalValueAverage(vector<Animal> animals, size_t valueType) {
    double sum = 0;  
    switch (valueType) {
        case 1:
            //wants speed
            for (size_t t = 0; t < animals.size(); t++) {
                sum += animals[t].speed;
            }
            break;
        case 2:
            //wants intelligence
            for (size_t t = 0; t < animals.size(); t++) {
                sum += animals[t].intelligence;
            }
            break;
        case 3:
            //wants sense
            for (size_t t = 0; t < animals.size(); t++) {
                //sum += herbivores[t].sense;
            }
            break;
    }
    if (animals.size() == 0) {
        return 0.0;
    } else {
        return sum / ((double) animals.size());
    }
}
    
    
}  // namespace naturalSelection
