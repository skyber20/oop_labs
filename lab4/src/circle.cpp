#include "lab4/circle.hpp"
#include <cmath>
#include <istream>
#include <numbers>
#include <ostream>
#include <stdexcept>

namespace lab4 {
Circle::Circle() : Circle(1.0) {}

Circle::Circle(double radius) : radius_(radius) {
    if (radius_ <= 0.0) {
        throw std::invalid_argument("Invalid radius");
    }
}

double Circle::radius() const noexcept {
    return radius_;
}

double Circle::metric() const {
    return std::numbers::pi * radius_ * radius_;
}

bool Circle::containsPoint(Point point) const {
    return point.x * point.x + point.y * point.y <= radius_ * radius_;
}

Shape* Circle::clone() const {
    return new Circle(*this);
}

void Circle::print(std::ostream& out) const {
    out << "Circle: r=" << radius_ << " metric=" << metric();
}

void Circle::read(std::istream& in) {
    double radius;
    if (in >> radius) {
        if (radius <= 0.0) {
            in.setstate(std::ios::failbit);
        } else {
            radius_ = radius;
        }
    }
}
}
