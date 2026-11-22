#include "lab5/binary_search_tree.hpp"

#include <ostream>
#include <utility>

namespace lab5 {

struct BinarySearchTree::Node {
    std::shared_ptr<Product> data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const Product& product) : data(std::make_shared<Product>(product)) {}
};

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept
    : root_(std::move(other.root_)), size_(other.size_) {
    other.size_ = 0;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        root_ = std::move(other.root_);
        size_ = other.size_;
        other.size_ = 0;
    }
    return *this;
}

BinarySearchTree::~BinarySearchTree() = default;

bool BinarySearchTree::insert(const Product& product) {
    std::unique_ptr<Node>* current = &root_;

    while (*current) {
        if (product < *(*current)->data) {
            current = &(*current)->left;
        } else if (*(*current)->data < product) {
            current = &(*current)->right;
        } else {
            return false;
        }
    }

    *current = std::make_unique<Node>(product);
    ++size_;
    return true;
}

std::weak_ptr<Product> BinarySearchTree::find(const Product& key) const {
    const Node* current = root_.get();

    while (current) {
        if (key < *current->data) {
            current = current->left.get();
        } else if (*current->data < key) {
            current = current->right.get();
        } else {
            return current->data;
        }
    }
    return {};
}

bool BinarySearchTree::remove(const Product& key) {
    std::unique_ptr<Node>* current = &root_;

    while (*current) {
        if (key < *(*current)->data) {
            current = &(*current)->left;
        } else if (*(*current)->data < key) {
            current = &(*current)->right;
        } else {
            break;
        }
    }

    if (!*current) return false;

    if (!(*current)->left) {
        auto child = std::move((*current)->right);
        *current = std::move(child);
    } else if (!(*current)->right) {
        auto child = std::move((*current)->left);
        *current = std::move(child);
    } else {
        std::unique_ptr<Node>* next = &(*current)->right;
        while ((*next)->left) {
            next = &(*next)->left;
        }
        (*current)->data = std::move((*next)->data);
        auto child = std::move((*next)->right);
        *next = std::move(child);
    }

    --size_;
    return true;
}

std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}

std::size_t BinarySearchTree::height(const Node* node) {
    if (!node) return 0;

    const std::size_t left = height(node->left.get());
    const std::size_t right = height(node->right.get());
    return 1 + (left > right ? left : right);
}

std::size_t BinarySearchTree::height() const {
    return height(root_.get());
}

void BinarySearchTree::printInOrder(const Node* node, std::ostream& out) {
    if (!node) return;
    printInOrder(node->left.get(), out);
    out << *node->data << '\n';
    printInOrder(node->right.get(), out);
}

void BinarySearchTree::printInOrder(std::ostream& out) const {
    printInOrder(root_.get(), out);
}

void BinarySearchTree::printReverse(const Node* node, std::ostream& out) {
    if (!node) return;
    printReverse(node->right.get(), out);
    out << *node->data << '\n';
    printReverse(node->left.get(), out);
}

void BinarySearchTree::printReverse(std::ostream& out) const {
    printReverse(root_.get(), out);
}

void BinarySearchTree::select(const Node* node, const ProductSelector& selector, Selection& result) {
    if (!node) return;
    select(node->left.get(), selector, result);
    if (selector.matches(*node->data)) {
        result.add(node->data);
    }
    select(node->right.get(), selector, result);
}

Selection BinarySearchTree::select(const ProductSelector& selector) const {
    Selection result;
    select(root_.get(), selector, result);
    return result;
}

}
