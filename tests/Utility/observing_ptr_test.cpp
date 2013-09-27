#include <Tank/Utility/observing_ptr.hpp>
#include <gtest/gtest.h>
#include <memory>

class observing_ptr_test : public testing::Test {
protected:
    std::unique_ptr<int> unique{new int};
    tank::observing_ptr<int> ptr {unique};

    observing_ptr_test() {
        *ptr = 10;
    }
};

TEST_F(observing_ptr_test, unique_constructor)
{
    std::unique_ptr<int> u_ptr {new int};
    *u_ptr = 10;
    tank::observing_ptr<int> o_ptr {u_ptr};
    ASSERT_EQ(*o_ptr, 10);
}

TEST_F(observing_ptr_test, nullptr_constructor)
{
    tank::observing_ptr<int> o_ptr {nullptr};
    ASSERT_EQ(o_ptr, nullptr);
}

TEST_F(observing_ptr_test, copy_constructor)
{
    tank::observing_ptr<int> o_ptr {ptr};
    ASSERT_EQ(o_ptr, ptr);
    ASSERT_EQ(*o_ptr, 10);
}

TEST_F(observing_ptr_test, raw_constructor)
{
    tank::observing_ptr<int> o_ptr {unique.get()};
    ASSERT_EQ(*o_ptr, 10);
}

TEST_F(observing_ptr_test, dereference)
{
    ASSERT_EQ(*ptr, *unique);
}

TEST_F(observing_ptr_test, struct_dereference)
{
    std::unique_ptr<std::pair<int,int>> upair {new std::pair<int, int>{10,20}};
    tank::observing_ptr<std::pair<int, int>> o_ptr {upair};
    ASSERT_EQ(o_ptr->first, 10);
    ASSERT_EQ(o_ptr->second, 20);
}

TEST_F(observing_ptr_test, op_bool)
{
    ASSERT_TRUE(bool(ptr));

    tank::observing_ptr<int> null {nullptr};
    ASSERT_FALSE(bool(null));
}

TEST_F(observing_ptr_test, equals)
{
    tank::observing_ptr<int> p {unique};
    ASSERT_TRUE(ptr == p);
    ASSERT_TRUE(p == ptr);

    std::unique_ptr<int> tmp {new int(10)};
    tank::observing_ptr<int> p2 {tmp};
    ASSERT_FALSE(p2 == p);
    ASSERT_FALSE(p == p2);
}

TEST_F(observing_ptr_test, unique_equals)
{
    ASSERT_TRUE(ptr == unique);
    ASSERT_TRUE(unique == ptr);

    std::unique_ptr<int> p {new int(20)};
    ASSERT_FALSE(ptr == p);
    ASSERT_FALSE(p == ptr);
}

TEST_F(observing_ptr_test, raw_equals)
{
    auto* x = new int;
    tank::observing_ptr<int> p {x};
    ASSERT_TRUE(p == x);
    ASSERT_TRUE(x == p);

    auto* y = new int;
    ASSERT_FALSE(p == y);
    ASSERT_FALSE(y == p);
}

TEST_F(observing_ptr_test, not_equals)
{
    tank::observing_ptr<int> p {unique};
    ASSERT_FALSE(ptr != p);
    ASSERT_FALSE(p != ptr);

    std::unique_ptr<int> tmp {new int(20)};
    tank::observing_ptr<int> p2 {tmp};
    ASSERT_TRUE(ptr != p2);
    ASSERT_TRUE(p2 != ptr);
}

TEST_F(observing_ptr_test, unique_not_equals)
{
    ASSERT_FALSE(ptr != unique);
    ASSERT_FALSE(unique != ptr);

    std::unique_ptr<int> p {new int(20)};
    ASSERT_TRUE(ptr != p);
    ASSERT_TRUE(p != ptr);
}

TEST_F(observing_ptr_test, raw_not_equals)
{
    auto* x = new int;
    tank::observing_ptr<int> p {x};
    ASSERT_FALSE(p != x);
    ASSERT_FALSE(x != p);

    auto* y = new int;
    ASSERT_TRUE(p != y);
    ASSERT_TRUE(y != p);
}
