#include <gtest/gtest.h>
#include <utility>

#include "lab3/student.hpp"

TEST(StudentTest, RuleOfFiveAndEquality) {
    lab3::Student a("Ivan", 10);
    lab3::Student b("Petr", 10);
    lab3::Student c("Fedor", 20);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    lab3::Student copied(a);
    EXPECT_STREQ(copied.name(), "Ivan");
    EXPECT_NE(copied.name(), a.name());

    lab3::Student assigned;
    assigned = a;
    EXPECT_STREQ(assigned.name(), "Ivan");
    EXPECT_NE(assigned.name(), a.name());

    lab3::Student moved(std::move(copied));
    EXPECT_STREQ(moved.name(), "Ivan");
    EXPECT_STREQ(copied.name(), "");

    lab3::Student moved_assigned;
    moved_assigned = std::move(assigned);
    EXPECT_STREQ(moved_assigned.name(), "Ivan");
    EXPECT_STREQ(assigned.name(), "");
}