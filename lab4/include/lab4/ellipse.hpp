#pragma once

#include "lab4/shape.hpp"

namespace lab4 {
class Ellipse : public Shape {
private:
    double a_;
    double b_;

public:
    Ellipse();
    Ellipse(double a, double b);

    [[nodiscard]] bool isCircle() const;
    [[nodiscard]] double metric() const override;
    [[nodiscard]] bool containsPoint(Point point) const override;
    [[nodiscard]] Shape* clone() const override;

    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
};
}
