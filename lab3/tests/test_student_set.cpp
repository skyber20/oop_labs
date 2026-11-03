#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "lab3/student_set.hpp"

TEST(StudentSetTest, BasicOperations) {
    lab3::StudentSet set;

    lab3::Student ivan("Ivan", 1);
    lab3::Student petr("Petr", 2);
    lab3::Student duplicate("Fedor", 1);

    EXPECT_TRUE(set.empty());
    EXPECT_EQ(set.size(), 0u);
    EXPECT_FALSE(set.contains(ivan));

    EXPECT_TRUE(set.add(ivan));
    EXPECT_TRUE(set.add(petr));
    EXPECT_FALSE(set.add(duplicate));

    EXPECT_EQ(set.size(), 2u);
    EXPECT_TRUE(set.contains(ivan));
    EXPECT_TRUE(set(ivan));

    std::ostringstream out;
    out << set;

    EXPECT_EQ(out.str(),
              "{ Student(name=Ivan, id=1), Student(name=Petr, id=2) }");

    EXPECT_TRUE(set.remove(ivan));
    EXPECT_FALSE(set.remove(ivan));
    EXPECT_EQ(set.size(), 1u);

    set -= petr;
    EXPECT_TRUE(set.empty());
}

TEST(StudentSetTest, CopyAndMove) {
    lab3::StudentSet original;
    original += lab3::Student("Ivan", 1);

    lab3::StudentSet copied(original);
    copied += lab3::Student("Petr", 2);

    EXPECT_EQ(original.size(), 1u);
    EXPECT_EQ(copied.size(), 2u);

    lab3::StudentSet assigned;
    assigned = copied;
    EXPECT_EQ(assigned.size(), 2u);

    lab3::StudentSet moved(std::move(copied));
    EXPECT_TRUE(copied.empty());
    EXPECT_EQ(moved.size(), 2u);

    lab3::StudentSet moved_assigned;
    moved_assigned = std::move(moved);

    EXPECT_TRUE(moved.empty());
    EXPECT_EQ(moved_assigned.size(), 2u);
    EXPECT_TRUE(moved_assigned.contains(lab3::Student("Petr", 2)));
}

TEST(StudentSetTest, SetOperations) {
    lab3::StudentSet a;
    a += lab3::Student("Ivan", 1);
    a += lab3::Student("Petr", 2);

    lab3::StudentSet b;
    b += lab3::Student("Fedor", 2);
    b += lab3::Student("Oleg", 3);

    lab3::StudentSet united = a | b;
    lab3::StudentSet common = a & b;
    lab3::StudentSet diff = a - b;

    EXPECT_EQ(united.size(), 3u);
    EXPECT_TRUE(united.contains(lab3::Student("Oleg", 3)));

    EXPECT_EQ(common.size(), 1u);
    EXPECT_TRUE(common.contains(lab3::Student("Petr", 2)));

    EXPECT_EQ(diff.size(), 1u);
    EXPECT_TRUE(diff.contains(lab3::Student("Ivan", 1)));

    lab3::StudentSet equal;
    equal += lab3::Student("Petr", 2);
    equal += lab3::Student("Ivan", 1);

    EXPECT_TRUE(a == equal);
    EXPECT_FALSE(a != equal);
    EXPECT_TRUE(a != b);
}

TEST(StudentSetTest, Stress) {
    lab3::StudentSet set;

    for (int i{0}; i < 1000; ++i) {
        EXPECT_TRUE(set.add(lab3::Student("Ivan", i)));
    }

    EXPECT_EQ(set.size(), 1000u);

    for (int i{0}; i < 1000; ++i) {
        EXPECT_FALSE(set.add(lab3::Student("Petr", i)));
    }

    EXPECT_EQ(set.size(), 1000u);
}