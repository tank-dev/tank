#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Tank/Utility/Rect.hpp>

TEST_CASE("Rectangle struct", "[utility][Rect]")
{
    SECTION("Default Constructor sets elements to 0")
    {
        tank::Recti rect;
        REQUIRE(rect.x == 0);
        REQUIRE(rect.y == 0);
        REQUIRE(rect.w == 0);
        REQUIRE(rect.h == 0);
    }

    SECTION("Setting the values works as expected")
    {
        tank::Recti rect{1, 2, 3, 4};
        REQUIRE(rect.x == 1);
        REQUIRE(rect.y == 2);
        REQUIRE(rect.w == 3);
        REQUIRE(rect.h == 4);
    }

    SECTION("Setting from convertible types works as expected")
    {
        tank::Rectf rect{1u, 2u, 3u, 4u};
        REQUIRE(rect.x == 1);
        REQUIRE(rect.y == 2);
        REQUIRE(rect.w == 3);
        REQUIRE(rect.h == 4);
    }

    SECTION("Copy constructor sets relevant values")
    {
        tank::Recti rect{1, 2, 3, 4};
        tank::Recti copy{rect};

        REQUIRE(rect.x == copy.x);
        REQUIRE(rect.y == copy.y);
        REQUIRE(rect.w == copy.w);
        REQUIRE(rect.h == copy.h);
    }

    SECTION("Copy constructor from related type sets relevant values")
    {
        tank::Recti rect{1, 2, 3, 4};
        tank::Rectf copy{rect};

        REQUIRE(rect.x == 1.f);
        REQUIRE(rect.y == 2.f);
        REQUIRE(rect.w == 3.f);
        REQUIRE(rect.h == 4.f);
    }

    SECTION("Intersection of two rectangles")
    {
        tank::Rectu rect1{1, 2, 3, 4};
        tank::Rectu rect2{2, 3, 4, 5};
        REQUIRE(rect1.intersects(rect2));
    }

    SECTION("Intersection of rectangle and point")
    {
        tank::Rectu rect{1, 2, 3, 4};
        tank::Vectoru point{1, 2};
        REQUIRE(rect.intersects(point));
    }
}
