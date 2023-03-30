#include <arrayd/arrayd.hpp>
#include <iostream>
#include <sstream>

ArrayD::ArrayD() {
	size = 0;
	coords = nullptr;
	capacity = 0;
}

ArrayD::ArrayD(ptrdiff_t ssize) {
	size = ssize;
	capacity = ssize;
	coords = new double[ssize];
	for (int i = 0; i < ssize; i++) {
		coords[i] = 0;
	}
}

ArrayD::ArrayD(const ArrayD& other) {
	size = other.size;
	capacity = other.capacity;
	coords = new double[other.capacity];
	for (int i = 0; i < other.size; i++) {
		coords[i] = other.coords[i];
	}
}


ArrayD::~ArrayD() {
	delete[] coords;
}


ArrayD& ArrayD::operator=(const ArrayD& rhs) {
	if (this != &rhs) {
		size = rhs.size;
		capacity = rhs.capacity;
		coords = new double[capacity];
		std::copy(rhs.coords, rhs.coords + rhs.capacity, coords);
	}
	return *this;
}

[[nodiscard]] double& ArrayD::operator[](const std::ptrdiff_t i) {
	if (i <= size) {
		return coords[i];
	}
	else {
		throw std::invalid_argument("IndexOutOfRange");
	}
}


[[nodiscard]] const double& ArrayD::operator[](const std::ptrdiff_t i) const {
	if (i <= size) {
		return coords[i];
	}
	else {
		throw std::invalid_argument("IndexOutOfRange");
	}
}


[[nodiscard]] std::ptrdiff_t ArrayD::ssize() const noexcept {
	return size;
}


void ArrayD::insert(const std::ptrdiff_t i, const double value) {
	if (i < 0 || i >(size - 1)) { throw std::invalid_argument("Invalid index"); }
	size++;
	double* temp = new double[size];
	for (ptrdiff_t j = 0; j < size - 1; j++) {
		temp[j] = coords[j];
	}
	for (ptrdiff_t j = size - 1; j > i; j--) {
		temp[j] = temp[j - 1];
	}
	temp[i] = value;
	delete[] coords;
	coords = temp;
}


void ArrayD::resize(const std::ptrdiff_t new_size) {
	if (new_size <= 0) {
		throw std::invalid_argument("Wrong position");
	}
	if (new_size > capacity) {
		double* new_coords = new double[new_size * 2];
		std::copy(coords, coords + size, new_coords);
		delete[] coords;
		std::fill(new_coords + size, new_coords + new_size, 0);
		coords = new_coords;
		size = new_size;
		capacity = new_size * 2;
	}
	else {
		if (new_size > size) {
			std::fill(coords + size, coords + new_size, 0);
		}
		if (new_size < size) {
			std::fill(coords + new_size, coords + size, 0);
		}
		size = new_size;
	}
}


void ArrayD::remove(const std::ptrdiff_t i) {
	if (i < 0 || i >(size - 1)) { throw std::invalid_argument("Invalid index"); }
	size--;
	double* temp = new double[size];
	for (ptrdiff_t j = 0; j < i; j++) {
		temp[j] = coords[j];
	}
	for (ptrdiff_t j = i; j < size; j++) {
		temp[i] = coords[i + 1];
	}
	delete[] coords;
	coords = temp;
}