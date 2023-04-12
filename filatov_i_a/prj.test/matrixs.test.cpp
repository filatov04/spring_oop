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
	CHECK(b.at(2, 2) == 0);
	int k = 0;
	for (std::ptrdiff_t i = 0; i < b.nRows(); i++) {
		for (std::ptrdiff_t j = 0; j < b.nCols(); j++) {
			b.at(i, j) = k;
			k++;
		}
	}
	b.resize(5, 5);
	CHECK(b.at(4, 4) == 0);
	CHECK(b.at(0, 0) == 0);
	CHECK(b.at(0, 1) == 1);
	CHECK(b.at(2, 2) == 8);
	CHECK(b.at(2, 3) == 0);
	CHECK_THROWS(b.at(7, 7));
}