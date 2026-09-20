#include "lab1/array_ops.hpp"

#include <cstddef>

#include <gtest/gtest.h>

TEST(ArrayOpsTest, CreateArray) {
    const std::size_t size{5};
    int* array{lab1::array_create(size)};

    ASSERT_NE(array, nullptr);
    for (std::size_t i{0}; i < size; ++i) {
        EXPECT_EQ(array[i], 0);
    }

    lab1::array_delete(array);
}

TEST(ArrayOpsTest, DeleteArray) {
    int* array{lab1::array_create(3)};

    lab1::array_delete(array);
    EXPECT_EQ(array, nullptr);

    lab1::array_delete(array);
    EXPECT_EQ(array, nullptr);
}

TEST(ArrayOpsTest, ResizeArray) {
    int* array{new int[3]{1, 2, 3}};

    array = lab1::array_resize(array, 3, 5);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 0);
    EXPECT_EQ(array[4], 0);

    array = lab1::array_resize(array, 5, 2);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest, ResizeEmptyArray) {
    int* array{lab1::array_create(0)};
    EXPECT_EQ(array, nullptr);

    array = lab1::array_resize(array, 0, 2);
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);

    array = lab1::array_resize(array, 2, 0);
    EXPECT_EQ(array, nullptr);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest, InsertMiddle) {
    std::size_t size{3};
    int* array{new int[3]{1, 2, 3}};

    array = lab1::array_insert(array, size, 1, 10);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 10);
    EXPECT_EQ(array[2], 2);
    EXPECT_EQ(array[3], 3);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest, InsertEdges) {
    std::size_t size{0};
    int* array{nullptr};

    array = lab1::array_insert(array, size, 0, 2);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(array[0], 2);

    array = lab1::array_insert(array, size, 0, 1);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);

    array = lab1::array_insert(array, size, size, 3);
    EXPECT_EQ(size, 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest_Fail, InvalidInsertPosition) {
    std::size_t size{2};
    int* array{new int[2]{1, 2}};

    array = lab1::array_insert(array, size, 3, 10);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest, RemoveElements) {
    std::size_t size{4};
    int* array{new int[4]{1, 2, 3, 4}};

    array = lab1::array_remove(array, size, 1);
    EXPECT_EQ(size, 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 3);
    EXPECT_EQ(array[2], 4);

    array = lab1::array_remove(array, size, 0);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(array[0], 3);
    EXPECT_EQ(array[1], 4);

    array = lab1::array_remove(array, size, size - 1);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(array[0], 3);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest, RemoveLastElement) {
    std::size_t size{1};
    int* array{new int[1]{7}};

    array = lab1::array_remove(array, size, 0);
    EXPECT_EQ(size, 0);
    EXPECT_EQ(array, nullptr);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest_Fail, InvalidRemovePosition) {
    std::size_t size{2};
    int* array{new int[2]{1, 2}};

    array = lab1::array_remove(array, size, size);
    EXPECT_EQ(size, 2);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);

    lab1::array_delete(array);
    size = 0;

    array = lab1::array_remove(array, size, 0);
    EXPECT_EQ(size, 0);
    EXPECT_EQ(array, nullptr);

    lab1::array_delete(array);
}

TEST(ArrayOpsTest, SortArray) {
    int array[]{3, -2, 0, 3, 1};
    const int expected[]{-2, 0, 1, 3, 3};

    lab1::selection_sort(array, 5);
    for (std::size_t i{0}; i < 5; ++i) {
        EXPECT_EQ(array[i], expected[i]);
    }
}

TEST(ArrayOpsTest, BinarySearch) {
    const int array[]{1, 2};
    std::size_t index{10};

    ASSERT_TRUE(lab1::array_binary_search(array, 2, 1, index));
    EXPECT_EQ(index, 0);

    ASSERT_TRUE(lab1::array_binary_search(array, 2, 2, index));
    EXPECT_EQ(index, 1);

    const int repeated[]{1, 2, 2, 2, 3};
    ASSERT_TRUE(lab1::array_binary_search(repeated, 5, 2, index));
    EXPECT_GE(index, 1);
    EXPECT_LE(index, 3);
}

TEST(ArrayOpsTest_Fail, BinarySearchNotFound) {
    const int array[]{1, 3, 5};
    std::size_t index{10};

    EXPECT_FALSE(lab1::array_binary_search(array, 3, 0, index));
    EXPECT_EQ(index, 10);
    EXPECT_FALSE(lab1::array_binary_search(array, 3, 6, index));
    EXPECT_EQ(index, 10);
    EXPECT_FALSE(lab1::array_binary_search(nullptr, 0, 1, index));
    EXPECT_EQ(index, 10);

    const int single[]{5};
    EXPECT_FALSE(lab1::array_binary_search(single, 1, 4, index));
    EXPECT_EQ(index, 10);
}

TEST(ArrayOpsTest, ReverseArray) {
    int arr[]{1, 2, 3, 4, 5};
    const int expected[]{5, 4, 3, 2, 1};

    lab1::array_reverse(arr, 5);
    for (std::size_t i{0}; i < 5; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }

    int even[]{1, 2};
    lab1::array_reverse(even, 2);
    EXPECT_EQ(even[0], 2);
    EXPECT_EQ(even[1], 1);
}

TEST(ArrayOpsTest, SingleElement) {
    int array[]{7};
    lab1::selection_sort(array, 1);
    EXPECT_EQ(array[0], 7);

    lab1::array_reverse(array, 1);
    EXPECT_EQ(array[0], 7);

    std::size_t index{10};
    ASSERT_TRUE(lab1::array_binary_search(array, 1, 7, index));
    EXPECT_EQ(index, 0);
}
