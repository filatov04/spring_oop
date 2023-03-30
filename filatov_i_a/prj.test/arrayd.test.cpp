#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>
#include <iostream>

TEST_CASE("[arrayd] - ArrayD ctor") {
    ArrayD a(3);
    ArrayD b{ 0, 0, 0 };
    CHECK(a == b);
    a = ArrayD();
    b = ArrayD(0);
    CHECK(a == b);
    CHECK_THROWS(a = ArrayD(-3));
}