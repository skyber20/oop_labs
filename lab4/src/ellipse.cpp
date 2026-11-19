#include "lab4/ellipse.hpp"
#include <cmath>
#include <istream>
#include <numbers>
#include <ostream>
#include <stdexcept>

namespace lab4 {
Ellipse::Ellipse() : Ellipse(1.0, 1.0) {}

Ellipse::Ellipse(double a, double b) : a_(a), b_(b) {
    if (a_ <= 0.0 || b_ <= 0.0) {
        throw std::invalid_argument("Invalid semi-axes");
    }
}

bool Ellipse::isCircle() const {
    return std::abs(a_ - b_) < eps;
}

double Ellipse::metric() const {
    return std::numbers::pi * a_ * b_;
}

bool Ellipse::containsPoint(Point point) const {
    return point.x * point.x / (a_ * a_) + point.y * point.y / (b_ * b_) <= 1.0;
}

Shape* Ellipse::clone() const {
    return new Ellipse(*this);
}

void Ellipse::print(std::ostream& out) const {
    out << "Ellipse: a=" << a_ << " b=" << b_ << " metric=" << metric();
}

void Ellipse::read(std::istream& in) {
    double a;
    double b;
    if (in >> a >> b) {
        if (a <= 0.0 || b <= 0.0) {
            in.setstate(std::ios::failbit);
        } else {
            a_ = a;
            b_ = b;
        }
    }
}
}
