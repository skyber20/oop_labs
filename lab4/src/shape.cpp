#include "lab4/shape.hpp"
#include <cmath>
#include <istream>
#include <ostream>

namespace lab4 {
Shape::operator double() const {
    return metric();
}

bool Shape::operator==(const Shape& other) const {
    return std::abs(metric() - other.metric()) < eps;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape) {
    shape.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, Shape& shape) {
    shape.read(in);
    return in;
}
}
