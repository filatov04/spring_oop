#pragma once
#ifndef RATIONAl_H_20232102
#define RATIONAL_H_20232102

#include <iosfwd>
#include <cstdint>

class Rational {
public:
	explicit Rational(int32_t number);
	Rational();
	Rational(int32_t number, int32_t denomi);
	Rational(const Rational& copy);
	~Rational() = default;

	Rational& operator=(const Rational& rhs);
	Rational& operator+=(const Rational& rhs); 
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	Rational& operator+(const Rational& rhs);
	Rational& operator-(const Rational& rhs);
	Rational& operator*(const Rational& rhs);
	Rational& operator/(const Rational& rhs);

	Rational& operator+=(const int32_t& rhs);
	Rational& operator-=(const int32_t& rhs);
	Rational& operator*=(const int32_t& rhs);
	Rational& operator/=(const int32_t& rhs);

	Rational& operator+(const int32_t& rhs);
	Rational& operator-(const int32_t& rhs);
	Rational& operator*(const int32_t& rhs);
	Rational& operator/(const int32_t& rhs);

	Rational& operator++();
	Rational& operator++(int32_t);
	Rational& operator--();
	Rational& operator--(int32_t);


	bool operator==(const Rational& rhs);
	bool operator!=(const Rational& rhs);
	bool operator>(const Rational& rhs);
	bool operator <(const Rational& rhs);
	bool operator<=(const Rational& rhs);
	bool operator>=(const Rational& rhs);


	bool operator==(const int32_t& rhs);


	std::ostream& writeTo(std::ostream& ostr) const;
	std::istream& readFrom(std::istream& istr);


	static const char slash{ '/' };

private:
	int32_t num;
	int32_t denom;
	int32_t gcd(int32_t a, int32_t b) {
		while (b != 0) {
			int32_t c = a % b;
			a = b;
			b = c;
		}
		return a;
	}

	void reduce(int32_t& a, int32_t& b) {
		int32_t c = gcd(std::abs(a), b);
		a /= c;
		b /= c;
	}
};

Rational operator-(const Rational& rhs);
Rational operator+(const Rational& rhs);

Rational operator+(const int32_t& lhs, const Rational& rhs);
Rational operator-(const int32_t& lhs, const Rational& rhs);
Rational operator*(const int32_t& lhs, const Rational& rhs);
Rational operator/(const int32_t& lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ostr, const Rational& rhs);
std::istream& operator>>(std::istream& istr, Rational& rhs);

#endif