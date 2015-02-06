#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Tank/Utility/Vector.hpp>

TEST_CASE("Vector struct", "[utility][Vector]")
{
    SECTION("Default constructor sets values to 0")
    {
        tank::Vectoru v;
        REQUIRE(v.x == 0);
        REQUIRE(v.y == 0);
    }
}
