#include "lab4/sector.hpp"
#include <cmath>
#include <istream>
#include <numbers>
#include <ostream>
#include <stdexcept>

namespace lab4 {
Sector::Sector() : Sector(1.0, std::numbers::pi / 2.0) {}

Sector::Sector(double radius, double angle) : radius_(radius), angle_(angle) {
    if (radius_ <= 0.0 ||
        angle_ < 0.0 || angle_ > 2.0 * std::numbers::pi) {
        throw std::invalid_argument("Invalid sector");
    }
}

bool Sector::isSemicircle() const {
    return std::abs(angle_ - std::numbers::pi) < eps;
}

double Sector::metric() const {
    return angle_ * radius_ * radius_ / 2.0;
}

bool Sector::containsPoint(Point point) const {
    if (point.x * point.x + point.y * point.y > radius_ * radius_) {
        return false;
    }

    if (point.x == 0.0 && point.y == 0.0) {
        return true;
    }

    double angle = std::atan2(point.y, point.x);
    if (angle < 0.0) {
        angle += 2.0 * std::numbers::pi;
    }

    return angle <= angle_ + eps;
}

Shape* Sector::clone() const {
    return new Sector(*this);
}

void Sector::print(std::ostream& out) const {
    out << "Sector: r=" << radius_ << " angle=" << angle_ << " metric=" << metric();
}

void Sector::read(std::istream& in) {
    double radius;
    double angle;
    if (in >> radius >> angle) {
        if (radius <= 0.0 ||
            angle < 0.0 || angle > 2.0 * std::numbers::pi) {
            in.setstate(std::ios::failbit);
        } else {
            radius_ = radius;
            angle_ = angle;
        }
    }
}
}
