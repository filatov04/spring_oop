#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS::MatrixS() = default;

MatrixS::MatrixS(const MatrixS& other) {
	row_ = other.row_;
	col_ = other.col_;
	int** data_ = new int* [row_];
	for (ptrdiff_t i = 0; i < row_; i++) {
		data_[i] = new int[col_];
	}
	for (ptrdiff_t i = 0; i < row_; i++) {
		for (ptrdiff_t j = 0; j < col_; j++) {
			data_[i][j] = other.data_[i][j];
		}
	}
}

MatrixS::MatrixS(std::ptrdiff_t m, std::ptrdiff_t n) {
	if (m <= 0 || n <= 0) {
		throw std::invalid_argument("Row or columns can not be negative");
	}
	row_ = m;
	col_ = n;
	int** data_ = new int* [m];
	for (ptrdiff_t i = 0; i < m; i++) {
		data_[i] = new int[n];
	}
	for (ptrdiff_t i = 0; i < row_; i++) {
		for (ptrdiff_t j = 0; j < col_; j++) {
			data_[i][j] = 0;
		}
	}
}

MatrixS::~MatrixS() {
	delete[] data_;
}

[[nodiscard]] std::ptrdiff_t MatrixS::nRow() {
	return row_;
}

[[nodiscard]] std::ptrdiff_t MatrixS::nCol() {
	return col_;
}

[[nodiscard]] int& MatrixS::at(const SizeType& elem) {
	if (std::get<0>(elem) <= 0 || std::get<1>(elem) <= 0 || std::get<0>(elem) >= row_ || std::get<1>(elem) >= col_) {
		throw std::out_of_range("Wrong position");
	}
	return data_[std::get<0>(elem)][std::get<1>(elem)];
}

[[nodiscard]] const int& MatrixS::at(const SizeType& elem) const {
	if (std::get<0>(elem) <= 0 || std::get<1>(elem) <= 0 || std::get<0>(elem) >= row_ || std::get<1>(elem) >= col_) {
		throw std::out_of_range("Wrong position");
	}
	return data_[std::get<0>(elem)][std::get<1>(elem)];
}

[[nodiscard]] int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
	if (i <= 0 || j <= 0 || i >= row_ || j >= col_) {
		throw std::out_of_range("Wrong position");
	}
	return data_[i][j];
}

[[nodiscard]] const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
	if (i <= 0 || j <= 0 || i >= row_ || j >= col_) {
		throw std::out_of_range("Wrong position");
	}
	return data_[i][j];
}

void MatrixS::resize(const SizeType& new_size) {
	if (std::get<0>(new_size) <= 0 || std::get<1>(new_size) <= 0) {
		throw std::invalid_argument("Wrong position");
	}
	//дописать

}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
	if (i <= 0 || j <= 0) {
		throw std::invalid_argument("Wrong position");
	}

	//дописать
}

[[nodiscard]] const MatrixS::SizeType& MatrixS::ssize() const noexcept {
	return SizeType(row_, col_);
}

MatrixS& MatrixS::operator=(const MatrixS& rhs) {
	row_ = rhs.row_;
	col_ = rhs.col_;
	delete[] data_;
	int** data_ = new int* [row_];
	for (ptrdiff_t i = 0; i < row_; i++) {
		data_[i] = new int[col_];
	}
	for (ptrdiff_t i = 0; i < row_; i++) {
		for (ptrdiff_t j = 0; j < col_; j++) {
			data_[i][j] = rhs.data_[i][j];
		}
	}
	return *this;
}