#include "natural_selection_app.h"

using naturalSelection::naturalSelectionApp;

void prepareSettings(naturalSelectionApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(naturalSelectionApp, ci::app::RendererGl, prepareSettings);
