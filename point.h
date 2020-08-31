//This header defines about class 'Point'.
#pragma once
#ifndef CENTROID_PROJECT_POINT_H_
#define CENTROID_PROJECT_POINT_H_

#include <iostream>
#include <string>
#include <realnumber.h>
#include "base.h"

POINT_BEGIN

class Point {
public:
	using DataT = RN::FixedReal;
private:
	DataT point_x_;
	DataT point_y_;
public:
	Point() noexcept;
	Point(const DataT& x, const DataT& y) noexcept;
	Point(const std::string& val) noexcept;
	Point(const Point&) = default;
	Point(Point&&) = default;
	~Point() = default;

	//parallel translation
	Point& Translation(const DataT& moving_x, const DataT& moving_y) noexcept;
	DataT XCoordinate() noexcept;
	DataT YCoordinate() noexcept;
	Point& operator=(const Point&) = default;
	Point& operator=(Point&&) = default;

	friend Point InternalDivision(const Point& p1, const Point& p2, const DataT& ratio1, const DataT& ratio2) noexcept;
	friend Point ExternalDivision(const Point& p1, const Point& p2, const DataT& ratio1, const DataT& ratio2) noexcept;
	friend std::istream& operator>>(std::istream& istr, Point& p) noexcept;
	friend std::ostream& operator<<(std::ostream& ostr, const Point& p) noexcept;
};

POINT_END

#endif // !CENTROID_PROJECT_POINT_H_