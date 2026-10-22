#include "lab2/string.hpp"

#include <sstream>
#include <stdexcept>
#include <utility>

#include <gtest/gtest.h>

namespace lab2 {

TEST(StringTest, Constructors) {
    const String empty;
    EXPECT_TRUE(empty.empty());
    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(empty.capacity(), 1);
    EXPECT_STREQ(empty.c_str(), "");

    const String text("a");
    EXPECT_EQ(text.size(), 1);
    EXPECT_STREQ(text.c_str(), "a");
}

TEST(StringTest, CopyConstructor) {
    String a("abc");
    const String b(a);

    a.push_back('d');
    EXPECT_STREQ(b.c_str(), "abc");
}

TEST(StringTest, MoveConstructor) {
    String a("abc");
    const String b(std::move(a));

    EXPECT_STREQ(b.c_str(), "abc");
    EXPECT_TRUE(a.empty());
    a.push_back('x');
    EXPECT_STREQ(a.c_str(), "x");
}

TEST(StringTest, Assignment) {
    String a("ab");
    String b("x");

    b = a;
    a.push_back('c');
    EXPECT_STREQ(b.c_str(), "ab");
    b = std::move(a);
    EXPECT_STREQ(b.c_str(), "abc");
    EXPECT_TRUE(a.empty());
}

TEST(StringTest, SelfAssignment) {
    String text("abc");

    text = text;
    EXPECT_STREQ(text.c_str(), "abc");
}

TEST(StringTest, PushBack) {
    String text;

    text.push_back('a');
    text.push_back('b');
    EXPECT_STREQ(text.c_str(), "ab");
    EXPECT_EQ(text.size(), 2);
    EXPECT_EQ(text.capacity(), 2);
}

TEST(StringTest, Append) {
    String text;

    text.append("ab");
    text.append("");
    text.append(String());
    text.append(text);
    EXPECT_STREQ(text.c_str(), "abab");
    EXPECT_EQ(text.size(), 4);
    EXPECT_EQ(text.capacity(), 4);
}

TEST(StringTest, Find) {
    const String text("abcabc");

    EXPECT_EQ(text.find("abc"), 0);
    EXPECT_EQ(text.find("bc"), 1);
    EXPECT_EQ(text.find("cabc"), 2);
    EXPECT_EQ(text.find(""), 0);
}

TEST(StringTest_Fail, FindNotFound) {
    const String text("abc");

    EXPECT_EQ(text.find("x"), String::npos);
    EXPECT_EQ(text.find("abcd"), String::npos);
    EXPECT_EQ(String().find("a"), String::npos);
}

TEST(StringTest, Print) {
    const String text("abc");
    std::ostringstream out;

    text.print(out);
    EXPECT_EQ(out.view(), "abc");
}

TEST(StringTest, Wrap) {
    const String text("aa bb ccc");

    EXPECT_STREQ(text.wrap(4).c_str(), "aa\nbb\nccc");
    EXPECT_STREQ(text.wrap(5).c_str(), "aa bb\nccc");
    EXPECT_STREQ(String().wrap(1).c_str(), "");
    EXPECT_STREQ(String("a").wrap(1).c_str(), "a");
    EXPECT_STREQ(String("a b").wrap(1).c_str(), "a\nb");
    EXPECT_STREQ(String("  a\t bb  ").wrap(4).c_str(), "a bb");
    EXPECT_STREQ(String("a\n\nb").wrap(1).c_str(), "a\n\nb");
    EXPECT_STREQ(text.c_str(), "aa bb ccc");
}

TEST(StringTest_Throw, InvalidWrap) {
    const String text("abc");

    EXPECT_THROW(text.wrap(0), std::invalid_argument);
    EXPECT_THROW(String().wrap(0), std::invalid_argument);
    EXPECT_THROW(text.wrap(2), std::invalid_argument);
}

}
