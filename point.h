//This header defines class template point(geometry)

#pragma once
#ifndef CENTROID_PROJECT_POINT_H_
#define CENTROID_PROJECT_POINT_H_

#pragma warning(push)
#pragma warning(disable:4172 6294)

#include "realnumber.h"
#include <array>
#include "base.h"

POINT_BEGIN

//CLASS TEMPLATE Point
template<size_t dimension>
class Point {
public:
	static const size_t dim_ = dimension;
	using DataT = real::FixedReal;
private:
	std::array<DataT, dimension> locations_;

	DataT& operator[](const size_t dimension);
	const DataT& operator[](const size_t dimension) const noexcept;
public:
	Point() = default;
	Point(const std::initializer_list<DataT>& val) noexcept;
	Point(const std::string& val) noexcept;
	template<typename _Fwdit>
	Point(_Fwdit _First, _Fwdit _Last) noexcept;
	Point(const Point&) = default;
	Point(Point&&) = default;
	~Point() = default;

	const DataT& At(const size_t dimension) const noexcept;
	Point& Move(const size_t dimension, const DataT& movement) noexcept;
	Point& MoveTo(const size_t dimension, const DataT& destination) noexcept;

	Point& operator=(const Point&) = default;
	Point& operator=(Point&&) = default;
};

template<size_t dimension>
typename Point<dimension>::DataT& Point<dimension>::operator[] (const size_t dimension) {
	if (dimension >= dim_) {
		std::cout << "You tried to reference out of dimension" << std::endl;
		std::cout << __FILE__ << __FUNCTION__ << ',' << __LINE__ << std::endl;
		throw std::exception{};
	}
	else return locations_[dimension];
}
template<size_t dimension>
const typename Point<dimension>::DataT& Point<dimension>::operator[](const size_t dimension) const noexcept {
	if (dimension >= dim_) return 0;
	else return locations_.at(dimension);
}

template<size_t dimension>
Point<dimension>::Point(const std::initializer_list<DataT>& val) noexcept {
	int i = 0;
	for (auto iter = val.begin();i < dim_ && iter != val.end();i++, iter++) {
		locations_[i] = *iter;
	}
}
template<size_t dimension>
Point<dimension>::Point(const std::string& val) noexcept {
	int i = 0;
	std::string _val(val);
	if (_val.at(0) == '(') {
		_val.erase(0, 1);
		_val.erase(_val.end() - 1);
	}
	for (;i < dim_;i++) {
		locations_[i] = _val.substr(0, _val.find(','));
		if (_val.find(',') == _val.npos) {
			++i;
			break;
		}
		_val.erase(0, _val.find(',') + 1);
	}
}
template<size_t dimension> template<typename _Fwdit>
Point<dimension>::Point(_Fwdit _First, _Fwdit _Last) noexcept {
	int i = 0;
	for (_Fwdit iter = _First;i < dim_ && iter != _Last;i++, iter++) {
		locations_[i] = *iter;
	}
}

template<size_t dimension>
const typename Point<dimension>::DataT& Point<dimension>::At(const size_t dimension) const noexcept {
	if (dimension >= dim_) return 0;
	else return locations_.at(dimension);
}
template<size_t dimension>
Point<dimension>& Point<dimension>::Move(const size_t dimension, const DataT& movement) noexcept {
	if (dimension >= dim_) return *this;
	locations_[dimension] += movement;
	return *this;
}
template<size_t dimension>
Point<dimension>& Point<dimension>::MoveTo(const size_t dimension, const DataT& destination) noexcept {
	if (dimension >= dim_) return *this;
	locations_[dimension] = destination;
	return *this;
}

//RatioT should be converted to FixedReal(DataT)
template<size_t dimension, typename RatioT>
Point<dimension> InternalDivision
(const Point<dimension>& p1, const Point<dimension>& p2, const RatioT& r1, const RatioT& r2) noexcept {
	Point<dimension> answer;
	for (int i = 0;i < answer.dim_;i++) {
		answer.MoveTo(i, (r1 * p2.At(i) + r2 * p1.At(i)) / (r1 + r2));
	}
	return answer;
}
//RatioT should be converted to FixedReal(DataT)
template<size_t dimension, typename RatioT>
Point<dimension> ExternalDivision
(const Point<dimension>& p1, const Point<dimension>& p2, const RatioT& r1, const RatioT& r2) noexcept {
	Point<dimension> answer;
	for (int i = 0;i < answer.dim_;i++) {
		answer.MoveTo(i, (r1 * p2.At(i) - r2 * p1.At(i)) / (r1 - r2));
	}
	return answer;
}


template<size_t dimension>
std::istream& operator>>(std::istream& _Istr, Point<dimension>& val) noexcept {
	std::string input;
	_Istr >> input;
	val = Point<dimension>(input);
	return _Istr;
}
template<size_t dimension>
std::ostream& operator<<(std::ostream& _Ostr, const Point<dimension>& val) noexcept {
	_Ostr << "( ";
	_Ostr << val.At(0);
	for (int i = 1;i < val.dim_;i++) {
		_Ostr << " , " << val.At(i);
	}
	_Ostr << " )";
	return _Ostr;
}
template<size_t dimension>
bool operator==(const Point<dimension>& val1, const Point<dimension>& val2) noexcept {
	for (int i = 0;i != dimension;i++) {
		if (val1.At(i) != val2.At(i)) return false;
	}
	return true;
}
template<size_t dimension>
bool operator!=(const Point<dimension>& val1, const Point<dimension>& val2) noexcept {
	return !(val1 == val2);
}


//CLASS TEMPLATE Point SPECIALIZATION
template<>
class Point<0> {
public:
	static const size_t dim_ = 0;
	using DataT = real::FixedReal;

	Point() = default;
	Point(const Point&) = default;
	Point(Point&&) = default;
	~Point() = default;

	DataT At(const size_t dimension) const noexcept;

	Point& operator=(const Point&) = default;
	Point& operator=(Point&&) = default;
};

Point<0>::DataT Point<0>::At(const size_t dimension) const noexcept {
	return 0;
}

std::ostream& operator<<(std::ostream& _Ostr, const Point<0>& val) noexcept {
	_Ostr << "( )";
	return _Ostr;
}
bool operator==(const Point<0>& val1, const Point<0>& val2) noexcept {
	return true;
}
bool operator!=(const Point<0>& val1, const Point<0>& val2) noexcept {
	return false;
}

POINT_END

#endif // !CENTROID_PROJECT_POINT_H_

#pragma warning(pop)
