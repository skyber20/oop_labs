#include "lab4/circle.hpp"
#include "lab4/ellipse.hpp"
#include "lab4/sector.hpp"
#include "lab4/shape_collection.hpp"
#include <gtest/gtest.h>
#include <numbers>
#include <sstream>
#include <stdexcept>
#include <utility>

TEST(ShapeTest, Metrics) {
    EXPECT_NEAR(lab4::Circle(3.0).metric(), 9.0 * std::numbers::pi, lab4::eps);
    EXPECT_NEAR(lab4::Ellipse(4.0, 2.0).metric(), 8.0 * std::numbers::pi, lab4::eps);
    EXPECT_NEAR(lab4::Sector(2.0, std::numbers::pi).metric(), 2.0 * std::numbers::pi, lab4::eps);
}

TEST(ShapeTest, SpecialMethods) {
    lab4::Circle circle(3.0);
    lab4::Ellipse ellipse(2.0, 2.0);
    lab4::Sector sector(2.0, std::numbers::pi);
    const lab4::Shape* shapes[] = {&circle, &ellipse, &sector};

    EXPECT_NE(dynamic_cast<const lab4::Circle*>(shapes[0]), nullptr);
    EXPECT_NE(dynamic_cast<const lab4::Ellipse*>(shapes[1]), nullptr);
    EXPECT_NE(dynamic_cast<const lab4::Sector*>(shapes[2]), nullptr);
    EXPECT_EQ(dynamic_cast<const lab4::Circle*>(shapes[1]), nullptr);
    EXPECT_DOUBLE_EQ(dynamic_cast<const lab4::Circle*>(shapes[0])->radius(), 3.0);
    EXPECT_TRUE(dynamic_cast<const lab4::Ellipse*>(shapes[1])->isCircle());
    EXPECT_TRUE(dynamic_cast<const lab4::Sector*>(shapes[2])->isSemicircle());
}

TEST(ShapeTest, ContainsPoint) {
    lab4::Circle circle(5.0);
    lab4::Ellipse ellipse(4.0, 2.0);
    lab4::Sector sector(3.0, std::numbers::pi / 2.0);

    EXPECT_TRUE(circle.containsPoint({3.0, 4.0}));
    EXPECT_FALSE(circle.containsPoint({6.0, 0.0}));
    EXPECT_TRUE(ellipse.containsPoint({2.0, 1.0}));
    EXPECT_FALSE(ellipse.containsPoint({4.0, 1.0}));
    EXPECT_TRUE(sector.containsPoint({1.0, 1.0}));
    EXPECT_FALSE(sector.containsPoint({-1.0, 1.0}));
}

TEST(ShapeTest, Output) {
    std::ostringstream out;
    out << lab4::Circle(1.0) << '\n'
        << lab4::Ellipse(2.0, 1.0) << '\n'
        << lab4::Sector(2.0, 1.0);

    EXPECT_EQ(out.str(), "Circle: r=1 metric=3.14159\n"
                         "Ellipse: a=2 b=1 metric=6.28319\n"
                         "Sector: r=2 angle=1 metric=2");
}

TEST(ShapeTest, Input) {
    lab4::Circle circle;
    lab4::Ellipse ellipse;
    lab4::Sector sector;
    std::istringstream in("3 4 2 2 1");
    in >> circle >> ellipse >> sector;

    EXPECT_NEAR(circle.metric(), 9.0 * std::numbers::pi, lab4::eps);
    EXPECT_NEAR(ellipse.metric(), 8.0 * std::numbers::pi, lab4::eps);
    EXPECT_DOUBLE_EQ(sector.metric(), 2.0);
}

TEST(ShapeTest, EqualityAndConversion) {
    lab4::Circle circle(1.0);
    lab4::Ellipse ellipse(2.0, 0.5);

    EXPECT_TRUE(circle == ellipse);
    EXPECT_FALSE(circle == lab4::Circle(2.0));
    EXPECT_NEAR(static_cast<double>(circle), std::numbers::pi, lab4::eps);
}

TEST(ShapeTest, InvalidDimensions) {
    EXPECT_THROW(lab4::Circle(0.0), std::invalid_argument);
    EXPECT_THROW(lab4::Ellipse(-1.0, 2.0), std::invalid_argument);
    EXPECT_THROW(lab4::Sector(1.0, -1.0), std::invalid_argument);

    lab4::Circle circle;
    std::istringstream in("-2");
    in >> circle;
    EXPECT_TRUE(in.fail());
}

TEST(ShapeCollectionTest, BasicOperations) {
    lab4::ShapeCollection shapes;
    EXPECT_EQ(shapes.size(), 0U);
    EXPECT_DOUBLE_EQ(shapes.totalMetric(), 0.0);

    shapes.add(lab4::Circle(2.0));
    shapes.add(lab4::Ellipse(2.0, 1.0));
    EXPECT_EQ(shapes.size(), 2U);
    EXPECT_NEAR(shapes.totalMetric(), 6.0 * std::numbers::pi, lab4::eps);
    EXPECT_NE(dynamic_cast<const lab4::Ellipse*>(&shapes.at(1)), nullptr);
    EXPECT_TRUE(shapes.remove(0));
    EXPECT_EQ(shapes.size(), 1U);
}

TEST(ShapeCollectionTest, CopyAndMove) {
    lab4::ShapeCollection first;
    first.add(lab4::Circle(2.0));

    lab4::ShapeCollection copy(first);
    EXPECT_NE(&first.at(0), &copy.at(0));

    lab4::ShapeCollection assigned;
    assigned = first;
    EXPECT_NE(&first.at(0), &assigned.at(0));

    lab4::ShapeCollection moved(std::move(copy));
    EXPECT_EQ(copy.size(), 0U);

    assigned = std::move(moved);
    EXPECT_EQ(moved.size(), 0U);
    EXPECT_EQ(assigned.size(), 1U);
}

TEST(ShapeTest, VirtualDestructor) {
    struct TrackedCircle : lab4::Circle {
        bool& destroyed;
        explicit TrackedCircle(bool& value) : destroyed(value) {}
        ~TrackedCircle() override { destroyed = true; }
    };

    bool destroyed = false;
    lab4::Shape* shape = new TrackedCircle(destroyed);
    delete shape;
    EXPECT_TRUE(destroyed);
}
