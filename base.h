//This header defines basic things fof this project

#pragma once
#ifndef CENTROID_PROJECT_BASE_H
#define CENTROID_PROJECT_BASE_H

#ifndef DEFINE_NAMESPACE
#define DEFINE_NAMESPACE
#define RN realnumber
#define BASE_BEGIN namespace base {
#define BASE_END }
#define POINT_BEGIN namespace point {
#define POINT_END }
#endif // !DEFINE_NAMESPACE

#include <algorithm>
#include <iostream>

BASE_BEGIN

//Ty have to define <(comparison operator).
template<typename Ty>
inline Ty Abs(const Ty& val) noexcept {
	if (val < 0)return -1 * val;
	else return val;
}

//Ty have to define %(modular operator).
template<typename Ty>
inline Ty Gcd(const Ty& val1, const Ty& val2) noexcept {
	if (val1 < 0 || val2 < 0) return Gcd(Abs(val1), Abs(val2));
	else if (val2 > val1) return Gcd(val2, val1);
	else if (val2 == 0) return val1;
	else return Gcd(val2, val1 % val2);
}

template<typename ReturnTy>
inline ReturnTy PowerOfTen(const int exponent) {
	ReturnTy answer{ 1 };
	if (exponent > 0) {
		for (int i = exponent;i != 0;i--) {
			answer *= 10;
		}
	}
	else
	{
		for (int i = -exponent;i != 0;i--) {
			answer /= 10;
		}
	}
	return answer;
}

inline constexpr bool IsBlank(const char _Val) noexcept {
	if (_Val == ' ' || _Val == '	' || _Val == '\n') return true;
	return false;
}
//Delete ','
inline void DeleteComma(std::string& val) noexcept {
	val.erase(std::remove(val.begin(), val.end(), ','), val.end());
}
//Delete blanks
inline void DeleteBlank(std::string& val) noexcept {
	val.erase(std::remove_if(val.begin(), val.end(), IsBlank), val.end());
}

BASE_END
#endif // !CENTROID_PROJECT_BASE_H
