
#include <gtest/gtest.h>
#include <initializer_list>
#include <sstream>
#include <utility>

#include "lab5/binary_search_tree.hpp"
#include "lab5/product_selector.hpp"

TEST(ProductTest, Compare) {
    lab5::Product a("A", "C", 10);
    lab5::Product b("B", "C", 10);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a < lab5::Product(20));
}

TEST(TreeTest, Insert) {
    lab5::BinarySearchTree tree;

    EXPECT_TRUE(tree.insert(lab5::Product("A", "C", 10)));
    EXPECT_FALSE(tree.insert(lab5::Product("B", "C", 10)));
    EXPECT_EQ(tree.size(), 1U);
}

TEST(TreeTest, Find) {
    lab5::BinarySearchTree tree;
    tree.insert(lab5::Product("Milk", "Food", 50));

    auto found = tree.find(lab5::Product(50));
    ASSERT_FALSE(found.expired());
    EXPECT_EQ(found.lock()->name(), "Milk");
    EXPECT_TRUE(tree.find(lab5::Product(90)).expired());

    tree.remove(lab5::Product(50));
    EXPECT_TRUE(found.expired());
}

TEST(TreeTest, Height) {
    lab5::BinarySearchTree tree;
    EXPECT_EQ(tree.height(), 0U);

    for (int x : {20, 10, 5})
        tree.insert(lab5::Product("A", "C", x));

    EXPECT_EQ(tree.height(), 3U);
}

TEST(TreeTest, Traversals) {
    lab5::BinarySearchTree tree;
    for (int x : {20, 10, 30})
        tree.insert(lab5::Product("A", "C", x));

    std::ostringstream a, b;
    tree.printInOrder(a);
    tree.printReverse(b);

    EXPECT_EQ(a.str(), "A C 10\nA C 20\nA C 30\n");
    EXPECT_EQ(b.str(), "A C 30\nA C 20\nA C 10\n");
}

TEST(TreeTest, RemoveLeaf) {
    lab5::BinarySearchTree tree;
    for (int x : {20, 10, 30})
        tree.insert(lab5::Product("A", "C", x));

    EXPECT_TRUE(tree.remove(lab5::Product(10)));
    std::ostringstream out;
    tree.printInOrder(out);
    EXPECT_EQ(out.str(), "A C 20\nA C 30\n");
}

TEST(TreeTest, RemoveOneChild) {
    lab5::BinarySearchTree tree;
    for (int x : {20, 10, 15})
        tree.insert(lab5::Product("A", "C", x));

    EXPECT_TRUE(tree.remove(lab5::Product(10)));
    std::ostringstream out;
    tree.printInOrder(out);
    EXPECT_EQ(out.str(), "A C 15\nA C 20\n");
}

TEST(TreeTest, RemoveTwoChildren) {
    lab5::BinarySearchTree tree;
    for (int x : {20, 10, 30, 25})
        tree.insert(lab5::Product("A", "C", x));

    EXPECT_TRUE(tree.remove(lab5::Product(20)));
    std::ostringstream out;
    tree.printInOrder(out);
    EXPECT_EQ(out.str(), "A C 10\nA C 25\nA C 30\n");
}

TEST(TreeTest, RemoveMissing) {
    lab5::BinarySearchTree tree;
    tree.insert(lab5::Product("A", "C", 10));

    EXPECT_FALSE(tree.remove(lab5::Product(20)));
    EXPECT_EQ(tree.size(), 1U);
}

TEST(TreeTest, Selection) {
    lab5::BinarySearchTree tree;
    for (int x : {150, 50, 90})
        tree.insert(lab5::Product("A", "C", x));

    auto result = tree.select(lab5::PriceBelowSelector(100));
    ASSERT_EQ(result.size(), 2U);
    EXPECT_EQ(result[0].lock()->price(), 50);
    EXPECT_EQ(result[1].lock()->price(), 90);
}

TEST(TreeTest, Criteria) {
    lab5::BinarySearchTree tree;
    EXPECT_TRUE(tree.select(lab5::AllProductsSelector()).empty());

    tree.insert(lab5::Product("A", "C", 10));
    tree.insert(lab5::Product("B", "C", 20));

    EXPECT_TRUE(tree.select(lab5::PriceBelowSelector(5)).empty());
    EXPECT_EQ(tree.select(lab5::AllProductsSelector()).size(), 2U);
}

TEST(TreeTest, ConstSelection) {
    lab5::BinarySearchTree tree;
    for (int x : {30, 10, 20})
        tree.insert(lab5::Product("A", "C", x));

    std::ostringstream before, after;
    tree.printInOrder(before);
    auto selected = tree.select(lab5::PriceBelowSelector(25));
    EXPECT_EQ(selected.size(), 2U);
    tree.printInOrder(after);

    EXPECT_EQ(before.str(), after.str());
    EXPECT_EQ(tree.size(), 3U);
    EXPECT_EQ(tree.height(), 3U);
}

TEST(SelectionTest, CopyMove) {
    lab5::BinarySearchTree tree;
    tree.insert(lab5::Product("A", "C", 10));

    auto original = tree.select(lab5::AllProductsSelector());
    lab5::Selection copy(original), assigned;
    assigned = original;

    lab5::Selection moved(std::move(copy)), target;
    target = std::move(assigned);

    EXPECT_TRUE(copy.empty());
    EXPECT_TRUE(assigned.empty());
    EXPECT_NE(&original[0], &moved[0]);

    tree.remove(lab5::Product(10));
    EXPECT_TRUE(original[0].expired());
    EXPECT_TRUE(target[0].expired());
    EXPECT_EQ(original.size(), 1U);
}

TEST(TreeTest, Lifetime) {
    EXPECT_EQ(lab5::Product::aliveCount(), 0);
    {
        lab5::BinarySearchTree tree;
        tree.insert(lab5::Product("A", "C", 10));

        lab5::BinarySearchTree moved(std::move(tree));
        lab5::BinarySearchTree assigned;
        assigned = std::move(moved);

        EXPECT_EQ(tree.size(), 0U);
        EXPECT_EQ(moved.size(), 0U);
        EXPECT_TRUE(assigned.remove(lab5::Product(10)));
    }
    EXPECT_EQ(lab5::Product::aliveCount(), 0);
}
