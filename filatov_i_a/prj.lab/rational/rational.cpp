#include <rational/rational.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream& ostr, const Rational& rhs) {
	return rhs.WriteTo(ostr);
}

std::istream& operator>>(std::istream& istr, Rational& rhs) {
	return rhs.ReadFrom(istr);
}

Rational::Rational(int32_t number) {
	num = number;
	denom = 1;
}

Rational::Rational() {
	num = 0;
	denom = 1;
}

bool Rational::operator==(const int32_t& rhs) {
	Rational temp = Rational(rhs);
	return operator==(temp);
}

Rational::Rational(int32_t number, int32_t denomi) {
	if (denomi < 0) {
		denomi *= -1;
		number *= -1;
	}
	if (denomi == 0) {
		throw std::invalid_argument("Divide by zero exception");
	}
	num = number;
	denom = denomi;
	reduce(num, denom);
}

Rational::Rational(const Rational& copy) {
	num = copy.num;
	denom = copy.denom;
}

Rational& Rational::operator+=(const int32_t& rhs) {
	return operator+=(Rational(rhs));
}

Rational& Rational::operator-=(const int32_t& rhs) {
	return operator-=(Rational(rhs));
}

Rational& Rational::operator*=(const int32_t& rhs) {
	return operator*=(Rational(rhs));
}

Rational& Rational::operator/=(const int32_t& rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("Divison by Zero");
	}
	else {
		return operator/=(Rational(rhs));
	}
}

Rational& Rational::operator+(const int32_t& rhs) {
	return operator+=(Rational(rhs));
}

Rational& Rational::operator-(const int32_t& rhs) {
	return operator-=(Rational(rhs));
}

Rational& Rational::operator*(const int32_t& rhs) {
	return operator*=(Rational(rhs));
}

Rational& Rational::operator/(const int32_t& rhs) {
	if (rhs == 0) {
		throw std::invalid_argument("Divison by Zero");
	}
	else {
		return operator/=(Rational(rhs));
	}
}

Rational operator-(const Rational& rhs) {
	Rational temp(-1,1);
	temp *= rhs;
	return temp;
}

Rational operator+(const Rational& rhs) {
	Rational temp;
	temp += rhs;
	return rhs;
}

Rational operator+(const int32_t& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum += rhs;
	return sum;
}

Rational operator-(const int32_t& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum -= rhs;
	return sum;
}

Rational operator*(const int32_t& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum *= rhs;
	return sum;
}

Rational operator/(const int32_t& lhs, const Rational& rhs) {
	if (lhs == 0) {
		throw std::invalid_argument("Divison by Zero");
	}
	else {
		Rational temp(lhs);
		temp /= rhs;
		return temp;
	}
}

Rational& Rational::operator=(const Rational& rhs) {
	num = rhs.num;
	denom = rhs.denom;
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
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

Rational& Rational::operator-=(const Rational& rhs) {
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

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.num == 0) {
		throw std::invalid_argument("Division by zero is prohibited");
	}
	num *= rhs.denom;
	denom *= rhs.num;
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator +(const Rational& rhs) {
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

Rational& Rational::operator-(const Rational& rhs) {
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

Rational& Rational::operator*(const Rational& rhs) {
	num *= rhs.num;
	denom *= rhs.denom;
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator/(const Rational& rhs) {
	if (rhs.num == 0) {
		throw std::invalid_argument("Division by zero is prohibited");
	}
	num *= rhs.denom;
	denom *= rhs.num;
	reduce(num, denom);
	return *this;
}

Rational& Rational::operator++() {
	num = num + denom;
	return *this;
}

Rational Rational::operator++(int32_t) {
	Rational temp(*this);
	num++;
	denom++;
	return temp;
}

Rational& Rational::operator--() {
	num = num - denom;
	return *this;
}

Rational Rational:: operator--(int32_t) {
	Rational temp(*this);
	num--;
	denom--;
	return temp;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum += rhs;
	return sum;

}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum -= rhs;
	return sum;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum *= rhs;
	return sum;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	Rational sum(lhs);
	sum /= rhs;
	return sum;
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

std::ostream& Rational::WriteTo(std::ostream& ostr) const noexcept {
	ostr << num << slash << denom;
	return ostr;
}

std::istream& Rational::ReadFrom(std::istream& istr) {
	char sym('-');
	while (std::isspace(istr.peek())) {
		sym = istr.get();
	}
	int32_t number(0);
	int32_t denomi(0);
	sym = '-';
	bool isNeg(false);
	if (istr.peek() == '-') {
		isNeg = true;
		sym = istr.get();
	}

	while (std::isdigit(istr.peek())) {
		sym = istr.get();
		number *= 10;
		number += static_cast<int>(sym - '0');
	}
	if (sym == '-') {
		istr.setstate(std::ios_base::failbit);
		return istr;
	}

	if (istr.peek() != '/') {
		istr.setstate(std::ios_base::failbit);
		return istr;
	}
	sym = istr.get();

	while (std::isdigit(istr.peek())) {
		sym = istr.get();
		denomi *= 10;
		denomi += static_cast<int>(sym - '0');
	}
	if (sym == '/') {
		istr.setstate(std::ios_base::failbit);
		return istr;
	}

	if (istr.good() || istr.eof()) {
		if (denomi == 0) {
			istr.setstate(std::ios_base::failbit);
			return istr;
		}
		num = number;
		denom = denomi;
		if (isNeg) {
			num *= -1;
		}
		reduce(num,denom);
	}
	return istr;
}