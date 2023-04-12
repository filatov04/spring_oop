#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>
#include <iostream>

TEST_CASE("Testing own library Rational numbers") {
	MatrixS a(2, 4);
	a.at(0, 0) = 1;
	a.at(0, 1) = 2;
	CHECK(a.at(0, 0) == 1);
	a.resize(4, 4);
	CHECK(a.nRows() == 4);
	CHECK(a.nCols() == 4);
	a.resize(5, 3);
	CHECK(a.nRows() == 5);
	CHECK(a.nCols() == 3);
	a.resize(4, 4);
	CHECK(a.nRows() == 4);
	CHECK(a.nCols() == 4);
	a.resize(3, 3);
	CHECK(a.nRows() == 3);
	CHECK(a.nCols() == 3);
	std::tuple<int, int> l(2, 2);
	MatrixS b(l);
	CHECK(b.nRows() == 2);
	CHECK(b.nCols() == 2);
	l = { 3, 3 };
	b.resize(l);
	CHECK(b.nRows() == 3);
	CHECK(b.nCols() == 3);

}