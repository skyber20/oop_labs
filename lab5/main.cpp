#include "lab5/binary_search_tree.hpp"
#include "lab5/product_selector.hpp"

#include <iostream>

int main() {
    lab5::BinarySearchTree tree;

    tree.insert(lab5::Product("Milk", "Food", 90));
    tree.insert(lab5::Product("Bread", "Food", 50));
    tree.insert(lab5::Product("Mouse", "Electronics", 150));
    tree.insert(lab5::Product("Tea", "Food", 70));
    tree.insert(lab5::Product("Keyboard", "Electronics", 120));

    std::cout << "Товары по возрастанию цены:\n";
    tree.printInOrder(std::cout);

    lab5::PriceBelowSelector cheap(100);
    auto result = tree.select(cheap);
    std::cout << "\nТовары дешевле 100:\n" << result;

    tree.remove(lab5::Product(70));
    std::cout << "\nПосле удаления товара с ценой 70:\n" << result;

    return 0;
}
