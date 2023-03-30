#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayt/arrayt.hpp>

typedef double T;
TEST_CASE("[arrayd] - ArrayT<T> ctor") {
    ArrayT<T> a(3);
    ArrayT<T> b{ 0.0, 0.0, 0.0 };
    CHECK(a == b);
    a = ArrayT<T>();
    b = ArrayT<T>(0);
    CHECK(a == b);
    CHECK_THROWS(a = ArrayT<T>(-3));
}