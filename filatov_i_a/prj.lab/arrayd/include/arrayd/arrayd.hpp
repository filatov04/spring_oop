#pragma once

#ifndef ARRAYD_ARRAYD_HPP_20230330
#define ARRAYD_ARRAYD_HPP_20230330

#include <iosfwd>
#include <cstdint>


class ArrayD {
public:
	ArrayD();
	explicit ArrayD(std::ptrdiff_t ssize);
	ArrayD(const ArrayD& other);
	~ArrayD();
	ArrayD& operator=(const ArrayD& rhs);

	[[nodiscard]] double& operator[](const std::ptrdiff_t i);
	[[nodiscard]] const double& operator[](const std::ptrdiff_t i) const;

	[[nodiscard]] std::ptrdiff_t ssize() const noexcept;
	void insert(const std::ptrdiff_t i, const double value);
	void resize(const std::ptrdiff_t new_size);
	void remove(const std::ptrdiff_t i);

	static const char separator{ ',' };

private:
	double* coords;//pointer to a dynamic array
	std::ptrdiff_t size;//current array sizeint
	std::ptrdiff_t capacity;
};


#endif
