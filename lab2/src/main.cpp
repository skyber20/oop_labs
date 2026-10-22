#include <cstddef>
#include <exception>
#include <iostream>

#include "lab2/string.hpp"

int main() {
    try {
        lab2::String text;
        char symbol{0};

        std::cout << "Строка: ";
        while (std::cin.get(symbol) && symbol != '\n') {
            text.push_back(symbol);
        }

        std::cout << "Ширина: ";
        long long width{0};
        if (!(std::cin >> width) || width <= 0) {
            std::cerr << "Некорректная ширина\n";
            return 1;
        }

        const lab2::String result = text.wrap(static_cast<std::size_t>(width));
        result.print(std::cout);
        std::cout << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
