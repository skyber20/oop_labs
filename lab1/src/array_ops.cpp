#include "lab1/array_ops.hpp"

#include <algorithm>
#include <iostream>

namespace lab1 {
int* array_create(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    int* arr{new int[size]{}};
    return arr;
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

void array_print(const int* arr, std::size_t size) {
    for (std::size_t i{0}; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {
    if (size == new_size) {
        return arr;
    }
    if (new_size == 0) {
        array_delete(arr);
        return nullptr;
    }

    int* new_arr{array_create(new_size)};

    for (std::size_t i{0}; i < std::min(size, new_size); ++i) {
        new_arr[i] = arr[i];
    }

    delete[] arr;
    return new_arr;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if (pos > size) {
        return arr;
    }

    int* new_arr{array_create(size + 1)};

    for (std::size_t i{0}; i < size + 1; ++i) {
        if (i <= pos) {
            new_arr[i] = pos == i ? value : arr[i];
        } else {
            new_arr[i] = arr[i - 1];
        }
    }

    delete[] arr;
    ++size;

    return new_arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (pos >= size) {
        return arr;
    }
    if (size == 1) {
        array_delete(arr);
        size = 0;
        return nullptr;
    }

    int* new_arr{array_create(size - 1)};

    for (std::size_t i{0}; i < size; ++i) {
        if (i < pos) {
            new_arr[i] = arr[i];
        } else if (i == pos) {
            continue;
        } else {
            new_arr[i - 1] = arr[i];
        }
    }

    array_delete(arr);
    --size;

    return new_arr;
}

void selection_sort(int* arr, std::size_t size) {
    if (size <= 1) {
        return;
    }

    for (std::size_t i{0}; i < size - 1; ++i) {
        std::size_t mn_ind{i};

        for (std::size_t j{i + 1}; j < size; ++j) {
            if (arr[mn_ind] > arr[j]) {
                mn_ind = j;
            }
        }

        if (mn_ind != i) {
            int tmp{arr[i]};
            arr[i] = arr[mn_ind];
            arr[mn_ind] = tmp;
        }
    }
}

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index) {
    // тк массив лишь читаем, а не изменяем, то будем считать, что массив передали отсортированный
    std::size_t left{0}, right{size};
    std::size_t mid{};

    while (left < right) {
        mid = left + (right - left) / 2;

        if (arr[mid] > target) {
            right = mid;
        } else if (arr[mid] == target) {
            out_index = mid;
            return true;
        } else {
            left = mid + 1;
        }
    }

    return false;
}

void array_reverse(int* arr, std::size_t size) {
    if (size <= 1) {
        return;
    }

    int* left{arr};
    int* right{arr + size - 1};

    while (left < right) {
        int tmp{*left};
        *left = *right;
        *right = tmp;

        ++left;
        --right;
    }
}
}
