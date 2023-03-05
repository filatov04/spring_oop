#include "include/Rational/Rational.h"
#include <iostream>

std::ostream& operator<<(std::ostream& ostr, const Rational& rhs) {
	return rhs.writeTo(ostr);
}

std::istream& operator>>(std::istream& istr, Rational& rhs) {
	return rhs.readFrom(istr);
}

Rational::Rational(int32_t number) {
	num = number;
	denom = 1;
}

Rational::Rational() {
	num = 0;
	denom = 1;
}

Rational::Rational(const int32_t number, const int32_t denomi) {
	if (denom == 0) {
		throw std::invalid_argument("Division by zero");
	}
	num = number;
	denom = denomi;
	if (num != 0) {
		 reduce(num, denom);
	}
	else {
		denom = 1;
	}
	if (denom < 0) {
		num *= -1;
		denom *= -1;
	}
}

Rational::Rational(Rational& copy) {
	num = copy.num;
	denom = copy.denom;
}

Rational Rational::operator+(const Rational& rhs) {
	Rational temp;
	if (denom == rhs.denom) {
		temp.num = num + rhs.num;
		temp.denom = rhs.denom;
	}
	else {
		temp.num = num * rhs.denom + rhs.num * denom;
		temp.denom = rhs.denom * denom;
	}
	reduce(temp.num, temp.denom);
	return temp;
}

Rational Rational::operator-(const Rational& rhs) {
	Rational temp;
	if (denom == rhs.denom) {
		temp.num = num - rhs.num;
		temp.denom = rhs.denom;
	}
	else {
		temp.num = num * rhs.denom - rhs.num * denom;
		temp.denom = rhs.denom * denom;
	}
	reduce(temp.num, temp.denom);
	return temp;
}

Rational& Rational::operator=(const Rational& rhs) {
	num = rhs.num;
	denom = rhs.denom;
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator +=(const Rational& rhs) {
	if (denom == rhs.denom) {
		num += rhs.denom;
	}
	else {
		num = num * rhs.denom + rhs.num * denom;
		denom = rhs.denom * denom;
	}
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator -=(const Rational& rhs) {
	if (denom == rhs.denom) {
		num -= rhs.denom;
	}
	else {
		num = num * rhs.denom - rhs.num * denom;
		denom = rhs.denom * denom;
	}
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.num;
	denom *= rhs.denom;
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator /= (const Rational& rhs) {
	if (rhs.num == 0) {
		throw std::invalid_argument("Division by zero is prohibited");
	}
	num *= rhs.denom;
	denom *= rhs.num;
	reduce(num, denom);
	return *this;
}

Rational Rational::operator*(const Rational& rhs) {
	Rational temp;
	temp.num = num * rhs.num;
	temp.denom = denom * rhs.denom;
	reduce(temp.num, temp.denom);
	return temp;
}

Rational Rational::operator/(const Rational& rhs) {
	Rational temp;
	temp.num = num * rhs.denom;
	temp.denom = denom * rhs.num;
	reduce(temp.num, temp.denom);
	return temp;
}

Rational& Rational::operator++() {
	num = num + denom;
	return *this;
}

Rational& Rational::operator++(int32_t) {
	Rational temp(*this);
	num++;
	denom++;
	return temp;
}

Rational& Rational::operator--() {
	num = num - denom;
	return *this;
}

Rational& Rational:: operator--(int32_t) {
	Rational temp(*this);
	num--;
	denom--;
	return temp;
}

bool Rational::operator==(const Rational& rhs) {
	return (num == rhs.num && denom == rhs.denom);
}

bool Rational::operator!=(const Rational& rhs) {
	return !(num == rhs.num && denom == rhs.denom);
}

bool Rational::operator>(const Rational& rhs) {
	Rational result;
	if (denom == rhs.denom) {
		result.num = num - rhs.denom;
	}
	else {
		result.num = num * rhs.denom - rhs.num * denom;
		result.denom = rhs.denom * denom;
	}
	if (result.num > 0) {
		return true;
	}
	else
	{
		return false;
	}
}

bool Rational::operator<(const Rational& rhs) {
	Rational result;
	if (denom == rhs.denom) {
		result.num = num - rhs.denom;
	}
	else {
		result.num = num * rhs.denom - rhs.num * denom;
		result.denom = rhs.denom * denom;
	}
	if (result.num < 0) {
		return true;
	}
	else
	{
		return false;
	}

}

bool Rational::operator<=(const Rational& rhs) {
	return !operator>(rhs);
}

bool Rational::operator>=(const Rational& rhs) {
	return !operator<(rhs);
}

std::ostream& Rational::writeTo(std::ostream& ostr) const {
	ostr << num << slash << denom;
	return ostr;
}

std::istream& Rational::readFrom(std::istream& istr) {
	int32_t number(0);
	int32_t denomi(0);
	char comma(0);
	istr >> number >> comma >> denomi;
	if (istr.good()) {
		if (Rational::slash == comma) {
			if (denomi <= 0) {
				throw std::invalid_argument("Please, write the positive denom");
			}
			num = number;
			denom = denomi;
			reduce(num, denom);
		}
		else {
			istr.setstate(std::ios_base::failbit);
		}
	}
	return istr;
}