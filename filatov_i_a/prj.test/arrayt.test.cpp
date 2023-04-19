#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayt/arrayt.hpp>
#include <iostream>

TEST_CASE("Testing own library of template array") {
	ArrayT<int> a(5);
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
	}
	SUBCASE("Insert") {
		a.insert(1, 11);
		CHECK(a[1] == 11);
		CHECK(a.ssize() == 6);
		CHECK(a[2] == 1);
		CHECK(a[5] == 4);
		CHECK(a.ssize() == 6);
		a.insert(0, 12);
		CHECK(a[0] == 12);
		CHECK(a.ssize() == 7);
	}
	/*SUBCASE("Operator []") {
		CHECK(a.ssize() == 6);
		CHECK_THROWS(a[-1]);
		CHECK_THROWS(a[6]);
		CHECK(a[5] == 4);
	}*/
	
}