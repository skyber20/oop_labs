#pragma once

#include <iosfwd>

namespace lab4 {
inline constexpr double eps = 1e-6;

struct Point {
    double x;
    double y;
};

class Shape {
public:
    virtual ~Shape() = default;

    [[nodiscard]] virtual double metric() const = 0;
    [[nodiscard]] virtual bool containsPoint(Point point) const = 0;
    [[nodiscard]] virtual Shape* clone() const = 0;

    virtual void print(std::ostream& out) const = 0;
    virtual void read(std::istream& in) = 0;

    explicit operator double() const;
    bool operator==(const Shape& other) const;
};

std::ostream& operator<<(std::ostream& out, const Shape& shape);
std::istream& operator>>(std::istream& in, Shape& shape);
}
