#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS::MatrixS() = default;

MatrixS::MatrixS(const MatrixS& other) {
	row_ = other.row_;
	col_ = other.col_;
	data_ = new int* [row_];
	for (std::ptrdiff_t i = 0; i < row_; i++) {
		data_[i] = new int[col_];
	}
	for (std::ptrdiff_t i = 0; i < row_; i++) {
		for (std::ptrdiff_t j = 0; j < col_; j++) {
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
	data_ = new int* [m];
	for (std::ptrdiff_t i = 0; i < m; i++) {
		data_[i] = new int[n];
	}
	for (std::ptrdiff_t i = 0; i < row_; i++) {
		for (std::ptrdiff_t j = 0; j < col_; j++) {
			data_[i][j] = 0;
		}
	}
}

MatrixS::~MatrixS() {
	for (ptrdiff_t i = 0; i < col_; i++) {
		delete[] data_[i];
	}
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
	MatrixS temp(std::get<0>(new_size), std::get<1>(new_size));
	for (std::ptrdiff_t i = 0; i < std::get<0>(new_size); i++) {
		for (std::ptrdiff_t j = 0; j < std::get<1>(new_size); j++) {
			if (row_ <= i || col_ <= j) {
				temp.at(SizeType(i, j)) = 0;
			}
			else {
				temp.at(SizeType(i, j)) = at(SizeType(i, j));
			}
		}
	}
		
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
	if (i <= 0 || j <= 0) {
		throw std::invalid_argument("Wrong position");
	}
	std::ptrdiff_t m = i;
	std::ptrdiff_t n = j;
	if (i <= 0 || j <= 0) {
		throw std::invalid_argument("Wrong position");
	}
	MatrixS temp(i, j);
	for (std::ptrdiff_t i = 0; i < m; i++) {
		for (std::ptrdiff_t j = 0; j < n; j++) {
			if (row_ <= i || col_ <= j) {
				temp.at(SizeType(i, j)) = 0;
			}
			else {
				temp.at(SizeType(i, j)) = at(SizeType(i, j));
			}
		}
	}
}

[[nodiscard]] const MatrixS::SizeType& MatrixS::ssize() const noexcept {
	return SizeType(row_, col_);
}

MatrixS& MatrixS::operator=(const MatrixS& rhs) {
	row_ = rhs.row_;
	col_ = rhs.col_;
	delete[] data_;
	data_ = new int* [row_];
	for (std::ptrdiff_t i = 0; i < row_; i++) {
		data_[i] = new int[col_];
	}
	for (std::ptrdiff_t i = 0; i < row_; i++) {
		for (std::ptrdiff_t j = 0; j < col_; j++) {
			data_[i][j] = rhs.data_[i][j];
		}
	}
	return *this;
}