#pragma once

#include "lab4/shape.hpp"

namespace lab4 {
class Circle : public Shape {
private:
    double radius_;

public:
    Circle();
    explicit Circle(double radius);

    [[nodiscard]] double radius() const noexcept;
    [[nodiscard]] double metric() const override;
    [[nodiscard]] bool containsPoint(Point point) const override;
    [[nodiscard]] Shape* clone() const override;

    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
};
}
