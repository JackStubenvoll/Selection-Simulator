
#include <catch2/catch.hpp>

#include "field.h"
#include "plant.h"

using naturalSelection::field;

TEST_CASE("Plant Collisions") {
  field container;
  SECTION("Should collide, same mass") {
    naturalSelection::Plant p1(vec2(0, 0), vec2(1, 1), 10, 1, ci::Color("red"));
    naturalSelection::Plant p2(vec2(5, 5), vec2(-1, -1), 10, 1, ci::Color("red"));
    REQUIRE(container.doParticlesCollide(p1, p2));
    container.particleCollisionVelocityChange(p1, p2);
    REQUIRE((p1.velocity == vec2(-1, -1) && p2.velocity == vec2(1, 1)));
  }
  SECTION("Should collide, different mass") {
    naturalSelection::Plant p1(vec2(0, 0), vec2(1, 1), 10, 1, ci::Color("red"));
    naturalSelection::Plant p2(vec2(5, 5), vec2(-1, -1), 10, 10, ci::Color("green"));
    REQUIRE(container.doParticlesCollide(p1, p2));
    std::cout << "~~~~~~~~~~~~~~~" << std::endl;
    container.particleCollisionVelocityChange(p1, p2);
    std::cout << p1.velocity << "\n" << p2.velocity << std::endl;
    REQUIRE((p1.velocity == vec2(-80 / 11, -80 / 11) && p2.velocity == vec2(-3 / 11, -3 / 11)));
  }
  SECTION("No collision, too far away") {
    naturalSelection::Plant p1(vec2(0, 0), vec2(1, 1), 10, 1, ci::Color("red"));
    naturalSelection::Plant p2(vec2(15, 15), vec2(-1, -1), 10, 1, ci::Color("red"));
    REQUIRE(!container.doParticlesCollide(p1, p2));
  }
  SECTION("No collision, same direction") {
    naturalSelection::Plant p1(vec2(0, 0), vec2(1, 1), 10, 1, ci::Color("red"));
    naturalSelection::Plant p2(vec2(5, 5), vec2(1, 1), 10, 1, ci::Color("red"));
    REQUIRE(!container.doParticlesCollide(p1, p2));
  }
}

TEST_CASE("Wall Collisions") {
  field container(100, 875);
  SECTION("Should collide with top wall") {
    naturalSelection::Plant p1(vec2(400, 105), vec2(0, -1), 10, 1, ci::Color("red"));
    REQUIRE(container.doesCollideWithWall(p1));
    container.wallCollisionVelocityChange(p1);
    REQUIRE(p1.velocity == vec2(0, 1));
  }
  SECTION("Should collide with right wall") {
    naturalSelection::Plant p1(vec2(770, 400), vec2(1, 0), 10, 1, ci::Color("red"));
    REQUIRE(container.doesCollideWithWall(p1));
    container.wallCollisionVelocityChange(p1);
    REQUIRE(p1.velocity == vec2(-1, 0));
  }
  SECTION("Should collide with bottom wall") {
    naturalSelection::Plant p1(vec2(400, 770), vec2(0, 1), 10, 1, ci::Color("red"));
    REQUIRE(container.doesCollideWithWall(p1));
    container.wallCollisionVelocityChange(p1);
    REQUIRE(p1.velocity == vec2(0, -1));
  }
  SECTION("Should collide with left wall") {
    naturalSelection::Plant p1(vec2(105, 400), vec2(-1, 0), 10, 1, ci::Color("red"));
    REQUIRE(container.doesCollideWithWall(p1));
    container.wallCollisionVelocityChange(p1);
    REQUIRE(p1.velocity == vec2(1, 0));
  }
  SECTION("Should not collide with any wall") {
    naturalSelection::Plant p1(vec2(400, 400), vec2(1, 1), 10, 1, ci::Color("red"));
    REQUIRE(!container.doesCollideWithWall(p1));
  }

}

TEST_CASE("Plant Positions") {
  field container(100, 875);
  SECTION("Plant's position is updated properly") {
    naturalSelection::Plant p1(vec2(0, 0), vec2(1, 1), 10, 1, ci::Color("red"));
        container.updateAnimalPositions(p1);
    REQUIRE(p1.position == vec2(1, 1));
  }

}


