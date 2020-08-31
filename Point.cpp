#pragma once
#include "point.h"

POINT_BEGIN

Point::Point() noexcept :point_x_{}, point_y_{} {}
Point::Point(const DataT& x, const DataT& y) noexcept :point_x_(x), point_y_(y) {}
Point::Point(const std::string& val) noexcept {
	std::string _val(val);
	base::DeleteBlank(_val);
	if (_val.at(0) == '(') {
		_val.erase(0, 1);
		_val.erase(_val.end() - 1);
	}
	point_x_ = DataT(_val.substr(0, _val.find(',')));
	point_y_ = DataT(_val.substr(_val.find(',') + 1));
}
Point& Point::Translation(const DataT& moving_x, const DataT& moving_y) noexcept {
	point_x_ += moving_x;
	point_y_ += moving_y;
	return *this;
}
Point::DataT Point::XCoordinate() noexcept {
	return point_x_;
}
Point::DataT Point::YCoordinate() noexcept {
	return point_y_;
}
Point InternalDivision
(const Point& p1, const Point& p2, const Point::DataT& ratio1, const Point::DataT& ratio2) noexcept {
	return Point{
		(ratio1 * p2.point_x_ + ratio2 * p1.point_x_) / (ratio1 + ratio2),
		(ratio1 * p2.point_y_ + ratio2 * p1.point_y_) / (ratio1 + ratio2)
	};
}
Point ExternalDivision
(const Point& p1, const Point& p2, const Point::DataT& ratio1, const Point::DataT& ratio2) noexcept {
	return Point{
		(ratio1 * p2.point_x_ - ratio2 * p1.point_x_) / (ratio1 - ratio2),
		(ratio1 * p2.point_y_ - ratio2 * p1.point_y_) / (ratio1 - ratio2)
	};
}
std::istream& operator>>(std::istream& istr, Point& p) noexcept {
	std::string userput;
	std::getline(istr, userput);
	p = Point(userput);
	return istr;
}
std::ostream& operator<<(std::ostream& ostr, const Point& p) noexcept {
	ostr << "( " << p.point_x_ << " , " << p.point_y_ << " )";
	return ostr;
}

POINT_END