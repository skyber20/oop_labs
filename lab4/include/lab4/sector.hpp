#pragma once

#include "lab4/shape.hpp"

namespace lab4 {
class Sector : public Shape {
private:
    double radius_;
    double angle_;

public:
    Sector();
    Sector(double radius, double angle);

    [[nodiscard]] bool isSemicircle() const;
    [[nodiscard]] double metric() const override;
    [[nodiscard]] bool containsPoint(Point point) const override;
    [[nodiscard]] Shape* clone() const override;

    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
};
}
