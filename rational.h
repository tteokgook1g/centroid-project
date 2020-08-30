//This header defines about class 'Rational', rational number.

#pragma once
#ifndef CENTROID_PROJECT_RATIONAL_H
#define CENTROID_PROJECT_RATIONAL_H

#include <string>
#include "base.h"

RATIONAL_BEGIN

//use for Rational::Print
struct Options
{
	static const int kFraction = 0x0;
	static const int kDecimal = 0x1;
	static const int kThousandsSeparator = 0x2;
	static const int kForceSign = 0x4;
};

//rational number
//DataType must be an integer type.
class Rational {
public:
	using DataT = unsigned long long;
private:
	//false is +, true is -
	bool sign_;
	DataT numerator_;
	//If it is 0, then rational is Nan.
	DataT denominator_;

public:
	Rational() noexcept;
	Rational(int numerator, int denominator) noexcept;
	explicit Rational(DataT numerator, DataT denominator, bool sign = false) noexcept;
	explicit Rational(const double& val) noexcept;
	Rational(const std::string& val) noexcept;
	Rational(const Rational&) = default;
	Rational(Rational&&) = delete;
	~Rational() = default;

	Rational& operator=(const Rational&) noexcept = default;
	Rational& operator+=(const Rational& val) noexcept;
	Rational& operator-=(const Rational& val) noexcept;
	Rational& operator*=(const Rational& val) noexcept;
	Rational& operator/=(const Rational& val) noexcept;
	Rational& operator=(Rational&&) noexcept = delete;
	Rational operator-() const noexcept;
	Rational& operator++() noexcept;
	Rational operator++(int) noexcept;
	Rational& operator--() noexcept;
	Rational operator--(int) noexcept;

	friend Rational operator+(const Rational& val1, const Rational& val2) noexcept;
	friend Rational operator-(const Rational& val1, const Rational& val2) noexcept;
	friend Rational operator*(const Rational& val1, const Rational& val2) noexcept;
	friend Rational operator/(const Rational& val1, const Rational& val2) noexcept;
	friend bool operator<(const Rational& val1, const Rational& val2) noexcept;
	friend bool operator>(const Rational& val1, const Rational& val2) noexcept;
	friend bool operator<=(const Rational& val1, const Rational& val2) noexcept;
	friend bool operator>=(const Rational& val1, const Rational& val2) noexcept;
	friend bool operator==(const Rational& val1, const Rational& val2) noexcept;
	friend bool operator!=(const Rational& val1, const Rational& val2) noexcept;
	friend std::istream& operator>>(std::istream& istr, Rational& val) noexcept;
	friend std::ostream& operator<<(std::ostream& ostr, const Rational& val) noexcept;

	void Print(std::ostream& ostr = std::cout, int format = Options::kFraction) const noexcept;
};

RATIONAL_END

#endif // !CENTROID_PROJECT_RATIONAL_H
