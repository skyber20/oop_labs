#pragma once

#include <cstddef>

namespace lab1 {
int* array_create(std::size_t size);

void array_delete(int*& arr);

void array_print(const int* arr, std::size_t size);

int* array_resize(int* arr, std::size_t size, std::size_t new_size);

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value);

int* array_remove(int* arr, std::size_t& size, std::size_t pos);

void selection_sort(int* arr, std::size_t size);

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index);

void array_reverse(int* arr, std::size_t size);
}
