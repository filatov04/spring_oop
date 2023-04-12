#pragma once

#ifndef MATRIXS_MATRIXS_HPP_20230330
#define MATRIXS_MATRIXS_HPP_20230330

#include <iosfwd>
#include <tuple>

class MatrixS {
public:
	using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;
public:
	explicit MatrixS(const SizeType& size = { 0, 0 });
	MatrixS(const MatrixS& other);
	MatrixS(std::ptrdiff_t m, std::ptrdiff_t n);
	~MatrixS();

	[[nodiscard]] std::ptrdiff_t nRows() const noexcept;
	[[nodiscard]] std::ptrdiff_t nCols() const noexcept;

	[[nodiscard]] int& at(const SizeType& elem);
	[[nodiscard]] const int& at(const SizeType& elem) const;
	[[nodiscard]] int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
	[[nodiscard]] const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

	void resize(const SizeType& new_size);
	void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);
	[[nodiscard]] const SizeType& ssize() const noexcept;

	MatrixS& operator=(const MatrixS& rhs);

private:
	std::ptrdiff_t row_ = 0;
	std::ptrdiff_t col_ = 0;
	int** data_ = nullptr;
};

#endif 