
#include <catch2/catch.hpp>

#include "field.h"
#include "plant.h"
#include "histogram.h"

using naturalSelection::field;

TEST_CASE("One of each mass") {
  field container;
  naturalSelection::Plant p1(vec2(0, 0), vec2(1, 1), 10, 1, ci::Color("red"));
  naturalSelection::Plant p2(vec2(5, 5), vec2(1, 1), 10, 10, ci::Color("green"));
  naturalSelection::Plant p3(vec2(5, 5), vec2(1, 1), 10, 100, ci::Color("blue"));

}

