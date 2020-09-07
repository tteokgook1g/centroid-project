//This header defines class template 'Polygon'.

#pragma once
#ifndef CENTROID_PROJECT_POLYGON_H_
#define CENTROID_PROJECT_POLYGON_H_

#pragma warning(push)
#pragma warning(disable:4172)

#include "realnumber.h"
#include "point.h"

POLYGON_BEGIN

namespace {
	template<size_t left, size_t right>
	struct Subtract
	{
		static const size_t value = left - right;
	};
}

//CLASS TEMPLATE Polygon
template<size_t n_gon>
class Polygon {
public:
	using DataT = point::Point<2>;
	static const size_t dim_ = 2;
	static const size_t ngon_ = n_gon;
private:
	std::array<DataT, ngon_> points_;

	DataT& operator[](const size_t index) noexcept;
	const DataT& operator[](const size_t index) const noexcept;
public:
	Polygon() = default;
	Polygon(const std::initializer_list<DataT> val) noexcept;
	Polygon(const std::string& val) noexcept;
	//value_type of _Fwdit should be converted to point::Point<2>.
	template<typename _Fwdit>
	Polygon(_Fwdit _First, _Fwdit _Last) noexcept;
	Polygon(const Polygon&) = default;
	Polygon(Polygon&&) = default;
	~Polygon() = default;

	Polygon& operator=(const Polygon&) = default;
	Polygon& operator=(Polygon&&) = default;

	const DataT& At(const size_t index) const noexcept;
	real::FixedReal Area() const noexcept;
	std::array < Polygon<3>, Subtract<n_gon, 2>::value > Split() const noexcept;
	DataT Centroid() const noexcept;
};

template<size_t n_gon>
typename Polygon<n_gon>::DataT& Polygon<n_gon>::operator[](const size_t index) noexcept {
	if (index >= ngon_) {
		std::cout << "You tried to reference out of range" << std::endl;
		std::cout << __FILE__ << __FUNCTION__ << ',' << __LINE__ << std::endl;
		throw std::exception{};
	}
	else return points_[index];
}
template<size_t n_gon>
const typename Polygon<n_gon>::DataT& Polygon<n_gon>::operator[](const size_t index) const noexcept {
	if (index >= ngon_) return DataT();
	else return points_[index];
}


template<size_t n_gon>
Polygon<n_gon>::Polygon(const std::initializer_list<DataT> val) noexcept {
	int i = 0;
	for (auto iter = val.begin();i < ngon_ && iter != val.end();i++, iter++) {
		points_[i] = *iter;
	}
}
template<size_t n_gon>
Polygon<n_gon>::Polygon(const std::string& val) noexcept {
	std::string _val(val);
	_val.erase(0, _val.find('('));
	for (int i = 0;i < ngon_;i++) {
		points_[i] = _val.substr(_val.find('(') + 1, _val.find(')') - _val.find('(') - 1);
		if (_val.find(')') == _val.npos) {
			++i;
			break;
		}
		_val.erase(0, _val.find(')') + 1);
	}
}
template<size_t n_gon> template<typename _Fwdit>
Polygon<n_gon>::Polygon(_Fwdit _First, _Fwdit _Last) noexcept {
	int i = 0;
	for (_Fwdit iter = _First;i < ngon_ && iter != _Last;i++, iter++) {
		points_[i] = *iter;
	}
}

template<size_t n_gon>
const typename Polygon<n_gon>::DataT& Polygon<n_gon>::At(const size_t index) const noexcept {
	if (index >= ngon_) return DataT();
	else return points_[index];
}
template<size_t n_gon>
real::FixedReal Polygon<n_gon>::Area() const noexcept {
	real::FixedReal answer;
	for (int i = 0;i < n_gon - 1;i++) {
		answer += points_.at(i).At(0) * points_.at(i + 1).At(1);
		answer -= points_.at(i + 1).At(0) * points_.at(i).At(1);
	}
	answer += points_.at(n_gon - 1).At(0) * points_.at(0).At(1);
	answer -= points_.at(0).At(0) * points_.at(n_gon - 1).At(1);
	answer.Abs();
	answer /= 2;
	return answer;
}
template<size_t n_gon>
std::array < Polygon<3>, Subtract<n_gon, 2>::value >
Polygon<n_gon>::Split() const noexcept {
	std::array < Polygon<3>, Subtract<n_gon, 2>::value > answer;
	for (int i = 1;i <= ngon_ - 2;i++) {
		answer.at(i - 1) = { points_.at(0),points_.at(i),points_.at(i + 1) };
	}
	return answer;
}
template<>
Polygon<3>::DataT Polygon<3>::Centroid() const noexcept {
	DataT answer;
	answer.MoveTo(0, (points_.at(0).At(0) + points_.at(1).At(0) + points_.at(2).At(0)) / 3);
	answer.MoveTo(1, (points_.at(0).At(1) + points_.at(1).At(1) + points_.at(2).At(1)) / 3);
	return answer;
}
template<size_t n_gon>
typename Polygon<n_gon>::DataT Polygon<n_gon>::Centroid() const noexcept {
	real::FixedReal x_centroid, y_centroid;
	DataT answer;
	std::array < Polygon<3>, Subtract<n_gon, 2>::value > splited = Split();
	for (size_t i = 0;i < splited.size();i++) {
		x_centroid += splited.at(i).Area() * splited.at(i).Centroid().At(0);
		y_centroid += splited.at(i).Area() * splited.at(i).Centroid().At(1);
	}
	x_centroid /= Area();y_centroid /= Area();
	answer.MoveTo(0, x_centroid);
	answer.MoveTo(1, y_centroid);
	return answer;
}

template<size_t n_gon>
bool operator==(const Polygon<n_gon>& val1, const Polygon<n_gon>& val2) noexcept {
	for (int i = 0;i < n_gon;i++) {
		if (val1.At(i) != val2.At(i)) return false;
	}
	return true;
}
template<size_t n_gon>
bool operator!=(const Polygon<n_gon>& val1, const Polygon<n_gon>& val2) noexcept {
	return !(val1 == val2);
}
template<size_t n_gon>
std::istream& operator>>(std::istream& _Istr, Polygon<n_gon>& val) noexcept {
	std::string input;
	_Istr >> input;
	val = Polygon<n_gon>(input);
	return _Istr;
}
template<size_t n_gon>
std::ostream& operator<<(std::ostream& _Ostr, const Polygon<n_gon>& val) noexcept {
	_Ostr << val.At(0);
	for (int i = 1;i < n_gon;i++) {
		_Ostr << " , " << val.At(i);
	}
	return _Ostr;
}


//CLASS TEMPLATE Polygon SPECIALIZATION
template<>
class Polygon<0> {
public:
	using DataT = point::Point<2>;
	static const size_t dim_ = 2;
	static const size_t ngon_ = 0;
public:
	Polygon() = default;
	Polygon(const std::initializer_list<DataT> val) = delete;
	Polygon(const std::string& val) = delete;
	template<typename _Fwdit>
	Polygon(_Fwdit _First, _Fwdit _Last) = delete;
	Polygon(const Polygon&) = default;
	Polygon(Polygon&&) = default;
	~Polygon() = default;

	Polygon& operator=(const Polygon&) = default;
	Polygon& operator=(Polygon&&) = default;

	DataT At(const size_t index) const noexcept;
	real::FixedReal Area() const noexcept;
	std::array < Polygon<3>, Subtract<0, 2>::value > Split() const = delete;
	DataT Centroid() const noexcept;
};

typename Polygon<0>::DataT Polygon<0>::At(const size_t index) const noexcept {
	return DataT();
}
real::FixedReal Polygon<0>::Area() const noexcept {
	return 0;
}
typename Polygon<0>::DataT Polygon<0>::Centroid() const noexcept {
	return DataT();
}

template<>
bool operator==(const Polygon<0>& val1, const Polygon<0>& val2) noexcept {
	return true;
}
template<>
bool operator!=(const Polygon<0>& val1, const Polygon<0>& val2) noexcept {
	return false;
}
template<>
std::istream& operator>>(std::istream&, Polygon<0>&) = delete;
template<>
std::ostream& operator<<(std::ostream& _Ostr, const Polygon<0>& val) noexcept {
	_Ostr << "( )";
	return _Ostr;
}

//CLASS TEMPLATE Polygon SPECIALIZATION
template<>
class Polygon<1> {
public:
	using DataT = point::Point<2>;
	static const size_t dim_ = 2;
	static const size_t ngon_ = 1;
private:
	DataT point_;
public:
	Polygon() = default;
	Polygon(const std::initializer_list<DataT>) = delete;
	Polygon(const std::string& val) noexcept;
	template<typename _Fwdit>
	Polygon(_Fwdit, _Fwdit) = delete;
	Polygon(const Polygon&) = default;
	Polygon(Polygon&&) = default;
	~Polygon() = default;

	Polygon& operator=(const Polygon&) = default;
	Polygon& operator=(Polygon&&) = default;

	const DataT& At(const size_t index) const noexcept;
	real::FixedReal Area() const noexcept;
	std::array < Polygon<3>, Subtract<1, 2>::value > Split() const = delete;
	DataT Centroid() const noexcept;
};

const Polygon<1>::DataT& Polygon<1>::At(const size_t index) const noexcept {
	if (index == 0) return point_;
	else return DataT();
}
real::FixedReal Polygon<1>::Area() const noexcept {
	return 0;
}
Polygon<1>::DataT Polygon<1>::Centroid() const noexcept {
	return point_;
}
template<>
bool operator==(const Polygon<1>& val1, const Polygon<1>& val2) noexcept {
	if (val1.At(0) == val2.At(0)) return true;
	else return false;
}
template<>
bool operator!=(const Polygon<1>& val1, const Polygon<1>& val2) noexcept {
	if (val1.At(0) != val2.At(0)) return true;
	else return false;
}
template<>
std::istream& operator>>(std::istream& _Istr, Polygon<1>& val) {
	std::string input;
	_Istr >> input;
	val = Polygon<1>(input);
	return _Istr;
}
template<>
std::ostream& operator<<(std::ostream& _Ostr, const Polygon<1>& val) noexcept {
	_Ostr << val.At(0);
	return _Ostr;
}

//CLASS TEMPLATE Polygon SPECIALIZATION
template<>
class Polygon<2> {
public:
	using DataT = point::Point<2>;
	static const size_t dim_ = 2;
	static const size_t ngon_ = 2;
private:
	std::array<DataT, 2> points_;
public:
	Polygon() = default;
	Polygon(const std::initializer_list<DataT> val) noexcept;
	Polygon(const std::string& val) noexcept;
	template<typename _Fwdit>
	Polygon(_Fwdit _First, _Fwdit _Last) noexcept;
	Polygon(const Polygon&) = default;
	Polygon(Polygon&&) = default;
	~Polygon() = default;

	Polygon& operator=(const Polygon&) = default;
	Polygon& operator=(Polygon&&) = default;

	const DataT& At(const size_t index) const noexcept;
	real::FixedReal Area() const noexcept;
	std::array < Polygon<3>, Subtract<2, 2>::value > Split() const = delete;
	DataT Centroid() const noexcept;
};

real::FixedReal Polygon<2>::Area() const noexcept {
	return 0;
}
Polygon<1>::DataT Polygon<2>::Centroid() const noexcept {
	DataT answer;
	answer.MoveTo(0, (points_.at(0).At(0) + points_.at(1).At(0)) / 2);
	answer.MoveTo(1, (points_.at(0).At(1) + points_.at(1).At(1)) / 2);
	return answer;
}


POLYGON_END

#endif // !CENTROID_PROJECT_POLYGON_H_

#pragma warning(pop)
