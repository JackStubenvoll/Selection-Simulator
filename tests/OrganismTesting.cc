
#include <catch2/catch.hpp>

#include "field.h"
#include "plant.h"

using naturalSelection::field;

TEST_CASE("Plants Equal") {
    SECTION("Equal") {
        naturalSelection::Plant p1(vec2(0, 0), ci::Color("green"));
        naturalSelection::Plant p2(vec2(0, 0), ci::Color("green"));
        REQUIRE(p1.isEqual(p2));
    }
    SECTION("Not equal") {
        naturalSelection::Plant p1(vec2(0, 0), ci::Color("green"));
        naturalSelection::Plant p2(vec2(5, 5), ci::Color("green"));
        REQUIRE(!(p1.isEqual(p2)));
    }
}


