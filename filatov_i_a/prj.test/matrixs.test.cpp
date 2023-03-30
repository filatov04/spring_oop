#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>
#include <iostream>

TEST_CASE("[matrixs] - MatrixS ctor") {
    MatrixS a(3, 3);
    MatrixS b(3, 3, 0);
    CHECK(a == b);
    CHECK_THROWS(b = MatrixS(1, -1));
}