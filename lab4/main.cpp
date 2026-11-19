#include "lab4/circle.hpp"
#include "lab4/ellipse.hpp"
#include "lab4/sector.hpp"
#include "lab4/shape_collection.hpp"
#include <iostream>
#include <numbers>

int main() {
    lab4::Circle circle(3.0);
    lab4::Ellipse ellipse(4.0, 2.0);
    lab4::Sector sector(2.0, std::numbers::pi);

    lab4::ShapeCollection shapes;
    shapes.add(circle);
    shapes.add(ellipse);
    shapes.add(sector);

    for (std::size_t i{0}; i < shapes.size(); ++i) {
        std::cout << shapes.at(i) << '\n';
    }

    std::cout << "Суммарная площадь: " << shapes.totalMetric() << '\n';
    std::cout << "Точка (1, 1) внутри круга: "
              << circle.containsPoint({1.0, 1.0}) << '\n';

    for (std::size_t i{0}; i < shapes.size(); ++i) {
        if (const auto* c = dynamic_cast<const lab4::Circle*>(&shapes.at(i))) {
            std::cout << "Радиус круга: " << c->radius() << '\n';
        } else if (const auto* e = dynamic_cast<const lab4::Ellipse*>(&shapes.at(i))) {
            std::cout << "Эллипс является кругом: " << e->isCircle() << '\n';
        } else if (const auto* s = dynamic_cast<const lab4::Sector*>(&shapes.at(i))) {
            std::cout << "Сектор является полукругом: " << s->isSemicircle() << '\n';
        }
    }

    return 0;
}
