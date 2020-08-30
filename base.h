//This header defines basic things fof this project

#pragma once
#ifndef CENTROID_PROJECT_BASE_H
#define CENTROID_PROJECT_BASE_H

#ifndef DEFINE_NAMESPACE
#define DEFINE_NAMESPACE
#define BASE_BEGIN namespace base {
#define BASE_END }
#define RATIONAL_BEGIN namespace rational {
#define RATIONAL_END }
#endif // !DEFINE_NAMESPACE

#include <iostream>

BASE_BEGIN

template<typename Ty>
//Ty have to define <(comparison operator).
Ty Abs(const Ty& val) noexcept {
	if (val < 0)return -val;
	else return val;
}

template<typename Ty>
//Ty have to define %(modular operator).
Ty Gcd(const Ty& val1, const Ty& val2) noexcept {
	if (val1 < 0 || val2 < 0) return Gcd(Abs(val1), Abs(val2));
	else if (val2 > val1) return Gcd(val2, val1);
	else if (val2 == 0) return val1;
	else return Gcd(val2, val1 % val2);
}

BASE_END
#endif // !CENTROID_PROJECT_BASE_H
