#include "lab5/product.hpp"

#include <cmath>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace lab5 {

int Product::alive_ = 0;

Product::Product(std::string name, std::string category, double price)
    : name_(std::move(name)), category_(std::move(category)), price_(price) {
    if (!std::isfinite(price_) || price_ < 0.0) {
        throw std::invalid_argument("Invalid price");
    }
    ++alive_;
}

Product::Product(double price) : Product("", "", price) {}

Product::Product(const Product& other)
    : Product(other.name_, other.category_, other.price_) {}

Product::Product(Product&& other) noexcept
    : name_(std::move(other.name_)), category_(std::move(other.category_)), price_(other.price_) {
    ++alive_;
}

Product::~Product() {
    --alive_;
}

const std::string& Product::name() const noexcept {
    return name_;
}

const std::string& Product::category() const noexcept {
    return category_;
}

double Product::price() const noexcept {
    return price_;
}

int Product::aliveCount() noexcept {
    return alive_;
}

bool Product::operator<(const Product& other) const {
    return price_ < other.price_;
}

bool Product::operator==(const Product& other) const {
    return price_ == other.price_;
}

std::ostream& operator<<(std::ostream& out, const Product& product) {
    out << product.name() << ' ' << product.category() << ' ' << product.price();
    return out;
}

}
