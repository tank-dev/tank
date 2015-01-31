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

    SECTION("Dereference operator gives the contained value") {
        auto u = std::make_unique<int>(4);
        tank::observing_ptr<int> p1 {u};
        REQUIRE(*p1 == 4);

        const tank::observing_ptr<int> p2 {u};
        REQUIRE(*p2 == 4);
    }

    SECTION("Call through operator allowes values and functions to be accessed") {
        struct S {
            bool f() {return true;}
            int b = true;
        };

        auto u = std::make_unique<S>();
        tank::observing_ptr<S> p1{u};
        REQUIRE(p1->b);
        REQUIRE(p1->f());

        const tank::observing_ptr<S> p2 {u};
        REQUIRE(p2->b);
        REQUIRE(p2->f());
    }


    SECTION("Usage in boolean expressions allows implicit boolean conversion") {
        int x = 10;
        tank::observing_ptr<int> p1{x};
        tank::observing_ptr<int> p2{nullptr};

        REQUIRE(p1);
        REQUIRE(!p2);
    }

    SECTION("Equality comparison on observing pointers") {
        auto up = std::make_unique<int>(4);
        tank::observing_ptr<int> p1 {up};
        tank::observing_ptr<int> p2 {up};
        tank::observing_ptr<int> p3;

        REQUIRE(p1 == p2);
        REQUIRE(p2 == p1);

        REQUIRE(p1 != p3);
        REQUIRE(p3 != p1);
    }

    SECTION("Equality comparison on unique pointers") {
        auto eq_unique = std::make_unique<int>(4);
        tank::observing_ptr<int> p {eq_unique};
        REQUIRE(p == eq_unique);
        REQUIRE(eq_unique == p);

        auto not_eq_unique = std::make_unique<int>(4);
        REQUIRE(p != not_eq_unique);
        REQUIRE(not_eq_unique != p);
    }

    SECTION("Equality comparison on raw pointers") {
        int* raw_ptr = new int(4);
        tank::observing_ptr<int> p {raw_ptr};
        REQUIRE(p == raw_ptr);
        REQUIRE(raw_ptr == p);

        int* raw_ptr2 = new int(4);
        REQUIRE(p != raw_ptr2);
        REQUIRE(raw_ptr2 != p);
    }

    SECTION ("Equality comparison on null pointers") {
        tank::observing_ptr<int> p;
        REQUIRE(p == nullptr);
        REQUIRE(nullptr == p);

        auto up = std::make_unique<int>(4);
        tank::observing_ptr<int> p1 {up};
        REQUIRE(p1 != nullptr);
        REQUIRE(nullptr != p1);
    }

    SECTION("Equality comparison on references") {
        auto up = std::make_unique<int>(4);
        tank::observing_ptr<int> p {up};
        int x = 4;

        REQUIRE(p == x);
        REQUIRE(x == p);

        x = 5;
        REQUIRE(p != x);
        REQUIRE(x != p);
    }

    SECTION("Hash function works as expected") {
        auto up1 = std::make_unique<int>(4);
        auto up2 = std::make_unique<int>(4);
        tank::observing_ptr<int> p1 {up1};
        tank::observing_ptr<int> p2 {up2};

        auto hash = std::hash<tank::observing_ptr<int>>{};

        REQUIRE(hash(p1) == hash(p1));
        REQUIRE(hash(p1) != hash(p2));
    }

}
