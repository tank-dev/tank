#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Tank/Utility/observing_ptr.hpp>

TEST_CASE("Observing Pointer Class", "[utility][observing_ptr]")
{
    SECTION("Default observing_ptr is null") {
        tank::observing_ptr<int> p;
        REQUIRE(p.get() == nullptr);
    }

    SECTION("Constructing an observing_ptr from a reference makes them equal") {
        int y = 10;
        tank::observing_ptr<int> p {y};
        REQUIRE(*p == y);
        REQUIRE(p == &y);
    }

    SECTION("Constructing an observing_ptr from a unique_ptr makes them equal"){
        auto u = std::make_unique<int>(4);
        tank::observing_ptr<int> p {u};
        REQUIRE(p.get() == u.get());
        REQUIRE(*p == *u);
    }

    SECTION("Constructing an observing_ptr from a null pointer makes it null") {
        tank::observing_ptr<int> p1 {nullptr};
        REQUIRE(p1.get() == nullptr);

        tank::observing_ptr<int> p2 {NULL};
        REQUIRE(p2.get() == nullptr);
    }

    SECTION("Constructing from another observing_ptr makes them equal") {
        auto u = std::make_unique<int>(4);
        tank::observing_ptr<int> p1 {u};
        tank::observing_ptr<int> p2 {p1};
        REQUIRE(p1.get() == p2.get());
        REQUIRE(*p1 == *p2);
    }

    SECTION("Constructing an observing_ptr from a raw pointer makes them equal") {
        int* x = new int(5);
        tank::observing_ptr<int> p{x};
        REQUIRE(*p == *x);
        REQUIRE(p.get() == x);
        delete x;
    }

    SECTION("Call through operator allowes values and functions to be accessed") {
        struct S {
            bool f() {return true;}
            int b = true;
        };

        auto u = std::make_unique<S>();
        tank::observing_ptr<S> p{u};
        REQUIRE(p->b);
        REQUIRE(p->f());
    }

    SECTION("Usage in boolean expressions allows implicit boolean conversion") {
        int x = 10;
        tank::observing_ptr<int> p1{x};
        tank::observing_ptr<int> p2{nullptr};

        REQUIRE(bool(p1));
        REQUIRE(!bool(p2));
    }

}
