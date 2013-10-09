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
    tank::observing_ptr<int> o_ptr {u_ptr};
    *u_ptr = 10;
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

TEST_F(observing_ptr_test, op_bool_true)
{
    ASSERT_TRUE(bool(ptr));
}

TEST_F(observing_ptr_test, op_bool_false)
{
    tank::observing_ptr<int> null {nullptr};
    ASSERT_FALSE(bool(null));
}

TEST_F(observing_ptr_test, equals_true)
{
    tank::observing_ptr<int> p {unique};
    ASSERT_TRUE(ptr == p);
    ASSERT_TRUE(p == ptr);
}

TEST_F(observing_ptr_test, equals_false)
{
    std::unique_ptr<int> tmp {new int(10)};
    tank::observing_ptr<int> p2 {tmp};
    ASSERT_FALSE(p2 == ptr);
    ASSERT_FALSE(ptr == p2);
}

TEST_F(observing_ptr_test, unique_equals_true)
{
    ASSERT_TRUE(ptr == unique);
    ASSERT_TRUE(unique == ptr);
}

TEST_F(observing_ptr_test, unique_equals_false)
{
    std::unique_ptr<int> p {new int(20)};
    ASSERT_FALSE(ptr == p);
    ASSERT_FALSE(p == ptr);
}

TEST_F(observing_ptr_test, raw_equals_true)
{
    auto* x = new int;
    tank::observing_ptr<int> p {x};
    ASSERT_TRUE(p == x);
    ASSERT_TRUE(x == p);
}

TEST_F(observing_ptr_test, raw_equals_false)
{
    auto* y = new int;
    ASSERT_FALSE(ptr == y);
    ASSERT_FALSE(y == ptr);
}

TEST_F(observing_ptr_test, not_equals_true)
{
    std::unique_ptr<int> tmp {new int(20)};
    tank::observing_ptr<int> p2 {tmp};
    ASSERT_TRUE(ptr != p2);
    ASSERT_TRUE(p2 != ptr);
}

TEST_F(observing_ptr_test, not_equals_false)
{
    tank::observing_ptr<int> p {unique};
    ASSERT_FALSE(ptr != p);
    ASSERT_FALSE(p != ptr);
}

TEST_F(observing_ptr_test, unique_not_equals_true)
{
    std::unique_ptr<int> p {new int(20)};
    ASSERT_TRUE(ptr != p);
    ASSERT_TRUE(p != ptr);
}

TEST_F(observing_ptr_test, unique_not_equals_false)
{
    ASSERT_FALSE(ptr != unique);
    ASSERT_FALSE(unique != ptr);
}

TEST_F(observing_ptr_test, raw_not_equals_true)
{
    auto* y = new int;
    ASSERT_TRUE(ptr != y);
    ASSERT_TRUE(y != ptr);
}

TEST_F(observing_ptr_test, raw_not_equals_false)
{
    auto* x = new int;
    tank::observing_ptr<int> p {x};
    ASSERT_FALSE(p != x);
    ASSERT_FALSE(x != p);
}
