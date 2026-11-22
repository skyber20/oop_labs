#pragma once

#include "lab5/product.hpp"
#include "lab5/product_selector.hpp"
#include "lab5/selection.hpp"

#include <cstddef>
#include <iosfwd>
#include <memory>

namespace lab5 {

class BinarySearchTree {
private:
    struct Node;
    std::unique_ptr<Node> root_;
    std::size_t size_;

    static std::size_t height(const Node* node);
    static void printInOrder(const Node* node, std::ostream& out);
    static void printReverse(const Node* node, std::ostream& out);
    static void select(const Node* node, const ProductSelector& selector, Selection& result);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other) = delete;
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;
    ~BinarySearchTree();

    bool insert(const Product& product);
    [[nodiscard]] std::weak_ptr<Product> find(const Product& key) const;
    bool remove(const Product& key);

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t height() const;
    void printInOrder(std::ostream& out) const;
    void printReverse(std::ostream& out) const;
    [[nodiscard]] Selection select(const ProductSelector& selector) const;
};

}
