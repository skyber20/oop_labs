#include <cstddef>
#include <iostream>
#include <limits>
#include <new>

#include "lab1/array_ops.hpp"

namespace {
bool ReadInt(int& value) {
    if (std::cin >> value) {
        return true;
    }
    if (std::cin.eof() || std::cin.bad()) {
        return false;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Некорректный ввод.\n";
    return false;
}

void PrintMenu() {
    std::cout
        << "\n1. Создать массив из нулей\n"
        << "2. Напечатать массив\n"
        << "3. Вставить элемент\n"
        << "4. Удалить элемент\n"
        << "5. Изменить размер\n"
        << "6. Напечатать массив\n"
        << "7. Сортировка выбором + бин поиск + разворот\n"
        << "0. Выход\n"
        << "Выберите пункт: ";
}
}

int main() {
    int* array{nullptr};
    std::size_t size{0};
    bool running{true};

    while (running && std::cin) {
        PrintMenu();

        int command{};
        if (!ReadInt(command)) {
            continue;
        }

        try {
            switch (command) {
                case 1: {
                    std::cout << "Введите размер массива: ";
                    int count{};
                    if (!ReadInt(count)) {
                        break;
                    }
                    if (count < 0) {
                        std::cout << "Размер не может быть отрицательным.\n";
                        break;
                    }

                    int* new_array{lab1::array_create(count)};
                    lab1::array_delete(array);
                    array = new_array;
                    size = count;
                    std::cout << "Новый размер массива: " << size << '\n';
                    break;
                }
                case 2:
                    std::cout << "Размер массива: " << size << '\n';
                    lab1::array_print(array, size);
                    std::cout << '\n';
                    break;
                case 3: {
                    std::cout << "Введите индекс вставки (нумерация с 0): ";
                    int input{};
                    if (!ReadInt(input)) {
                        break;
                    }
                    if (input < 0) {
                        std::cout << "Индекс не может быть отрицательным.\n";
                        break;
                    }
                    const std::size_t pos = input;
                    if (pos > size) {
                        std::cout << "Неверный индекс.\n";
                        break;
                    }

                    std::cout << "Введите значение: ";
                    int value{};
                    if (!ReadInt(value)) {
                        break;
                    }
                    array = lab1::array_insert(array, size, pos, value);
                    std::cout << "Размер после вставки: " << size << '\n';
                    break;
                }
                case 4: {
                    std::cout << "Введите индекс удаления (нумерация с 0): ";
                    int input{};
                    if (!ReadInt(input)) {
                        break;
                    }
                    if (input < 0) {
                        std::cout << "Индекс не может быть отрицательным.\n";
                        break;
                    }
                    const std::size_t pos = input;
                    if (pos >= size) {
                        std::cout << "Неверный индекс.\n";
                        break;
                    }

                    array = lab1::array_remove(array, size, pos);
                    std::cout << "Размер после удаления: " << size << '\n';
                    break;
                }
                case 5: {
                    std::cout << "Введите новый размер массива: ";
                    int count{};
                    if (!ReadInt(count)) {
                        break;
                    }
                    if (count < 0) {
                        std::cout << "Размер не может быть отрицательным.\n";
                        break;
                    }

                    array = lab1::array_resize(array, size, count);
                    size = count;
                    std::cout << "Новый размер массива: " << size << '\n';
                    break;
                }
                case 6:
                    std::cout << "Размер массива: " << size << '\n';
                    lab1::array_print(array, size);
                    std::cout << '\n';
                    break;
                case 7: {
                    lab1::selection_sort(array, size);
                    std::cout << "После сортировки: ";
                    lab1::array_print(array, size);
                    std::cout << "\nВведите число для поиска: ";

                    int target{};
                    if (!ReadInt(target)) {
                        break;
                    }
                    std::size_t index{};
                    if (lab1::array_binary_search(array, size, target, index)) {
                        std::cout << "Найдено число " << array[index] << ", индекс: " << index << '\n';
                    } else {
                        std::cout << "Число не найдено.\n";
                    }

                    lab1::array_reverse(array, size);
                    std::cout << "После разворота: ";
                    lab1::array_print(array, size);
                    std::cout << '\n';
                    break;
                }
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Нет такого пункта меню.\n";
                    break;
            }
        } catch (const std::bad_alloc&) {
            std::cout << "Не удалось выделить память.\n";
        }
    }

    lab1::array_delete(array);
    std::cout << "Программа завершена.\n";
    return 0;
}
