#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayd/arrayd.hpp>
#include <iostream>

TEST_CASE("Testing own library Double DynamicArray numbers") {
	ArrayD a(5);
	CHECK(a[0] == 0);
	CHECK(a[4] == 0);
	for (std::ptrdiff_t i = 0; i < a.ssize(); i++) {
		a[i] = double(i);
	}
	CHECK(a[1] == 1);
	REQUIRE(a.ssize() == 5);
	CHECK_THROWS(a.resize(-1));
	SUBCASE("Resize") {
		CHECK(a.ssize() == 5);
		a.resize(3);
		CHECK_THROWS(a[4]);
		CHECK(a.ssize() == 3);
		a.resize(8);
		CHECK(a[7] == 0);
		CHECK_THROWS(a[9]);
	}
	SUBCASE("Remove") {
		for (std::ptrdiff_t i = 0; i < a.ssize(); i++)
		{
			a[i] = i;
		}
		a.remove(0);
		CHECK(a[0] == 1);
		a.remove(3);
		CHECK(a[2] == 3);
		CHECK_THROWS(a.remove(-1));
	}
	SUBCASE("Insert") {
		a.insert(1, 11);
		CHECK(a[1] == 11);
		CHECK(a.ssize() == 6);
		CHECK(a[2] == 1);
		CHECK(a[5] == 4);
		a.insert(0, 100);
		CHECK(a[0] == 100);
		CHECK(a.ssize() == 7);
		CHECK_THROWS(a.insert(7, 18));
	}
}