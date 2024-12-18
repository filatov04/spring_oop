#pragma once

#ifndef ARRAYT_ARRAYT_HPP_20230329
#define ARRAYT_ARRAYT_HPP_20230329

#include <sstream>
#include <iostream>
#include <cstdint>

template<typename T>
class ArrayT {
public:
	ArrayT();
	explicit ArrayT(std::ptrdiff_t ssize);
	ArrayT(const ArrayT<T>& other);
	ArrayT& operator=(const ArrayT<T>& rhs);
	~ArrayT();

	[[nodiscard]] T& operator[](const std::ptrdiff_t index);
	[[nodiscard]] const T& operator[](const std::ptrdiff_t index) const;

	[[nodiscard]] std::ptrdiff_t ssize() const noexcept;
	void insert(const std::ptrdiff_t index, const T value);
	void resize(const std::ptrdiff_t new_size);
	void remove(const std::ptrdiff_t i);

	static const char separator{ ',' };

private:
	T* coords;//pointer to a dynamic array
	std::ptrdiff_t size;//current array sizeint
	std::ptrdiff_t capacity;
};

template<typename T>
ArrayT<T>::ArrayT() {
	size = 0;
	coords = nullptr;
	capacity = 0;
}

template<typename T>
ArrayT<T>::ArrayT(std::ptrdiff_t ssize) {
	if (ssize < 0) {
		throw std::invalid_argument("Wrong size");
	}
	size = ssize;
	capacity = ssize;
	coords = new T[ssize];
	for (std::ptrdiff_t i = 0; i < ssize; i++) {
		coords[i] = 0;
	}
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT<T>& other) {
	size = other.size;
	capacity = other.capacity;
	coords = new T[other.capacity];
	for (std::ptrdiff_t i = 0; i < other.size; i++) {
		coords[i] = other.coords[i];
	}
}

template<typename T>
ArrayT<T>::~ArrayT() {
	delete[] coords;
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs) {
	if (this != &rhs) {
		size = rhs.size;
		capacity = rhs.capacity;
		coords = new T[capacity];
		std::copy(rhs.coords, rhs.coords + rhs.capacity, coords);
	}
	return *this;
}

template<typename T>
[[nodiscard]] T& ArrayT<T>::operator[](const std::ptrdiff_t index) {
	if (index < size && index >= 0) {
		return coords[index];
	}
	else {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template<typename T>
[[nodiscard]] const T& ArrayT<T>::operator[](const std::ptrdiff_t index) const {
	if (index < size && index >= 0) {
		return coords[index];
	}
	else {
		throw std::out_of_range("IndexOutOfRange");
	}
}

template<typename T>
[[nodiscard]] std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
	return size;
}

template<typename T>
void ArrayT<T>::insert(const std::ptrdiff_t index, const T value) {
	if (index < 0 || index >(size - 1)) {
		throw std::out_of_range("Invalid index");
	}
	size++;
	T* temp = new T[size];
	for (std::ptrdiff_t j = 0; j < size - 1; j++) {
		temp[j] = coords[j];
	}
	for (std::ptrdiff_t j = size - 1; j > index; j--) {
		temp[j] = temp[j - 1];
	}
	temp[index] = value;
	delete[] coords;
	coords = temp;

}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t new_size) {
	if (new_size <= 0) {
		throw std::out_of_range("Wrong position");
	}
	if (new_size > capacity) {
		T* new_coords = new T[new_size * 2];
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

template<typename T>
void ArrayT<T>::remove(const std::ptrdiff_t i) {
	if (i < 0 || i >(size - 1)) { throw std::out_of_range("Invalid index"); }
	for (std::ptrdiff_t j = i; j < size - 1; j++) {
		coords[j] = coords[j + 1];
	}
	resize(ssize() - 1);
}


#endif