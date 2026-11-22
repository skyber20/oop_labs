#include "lab5/selection.hpp"

#include <ostream>
#include <stdexcept>
#include <utility>

namespace lab5 {

Selection::Selection() : size_(0), capacity_(0), data_(nullptr) {}

Selection::Selection(const Selection& other)
    : size_(other.size_), capacity_(other.capacity_),
      data_(capacity_ == 0 ? nullptr : std::make_unique<std::weak_ptr<Product>[]>(capacity_)) {
    for (std::size_t i{0}; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

Selection::Selection(Selection&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), data_(std::move(other.data_)) {
    other.size_ = 0;
    other.capacity_ = 0;
}

Selection& Selection::operator=(const Selection& other) {
    if (this != &other) {
        Selection tmp(other);
        swap(tmp);
    }
    return *this;
}

Selection& Selection::operator=(Selection&& other) noexcept {
    if (this != &other) {
        Selection tmp(std::move(other));
        swap(tmp);
    }
    return *this;
}

void Selection::swap(Selection& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

void Selection::add(const std::weak_ptr<Product>& product) {
    if (size_ == capacity_) {
        const std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        auto new_data = std::make_unique<std::weak_ptr<Product>[]>(new_capacity);

        for (std::size_t i{0}; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }

    data_[size_] = product;
    ++size_;
}

std::size_t Selection::size() const noexcept {
    return size_;
}

std::size_t Selection::capacity() const noexcept {
    return capacity_;
}

bool Selection::empty() const noexcept {
    return size_ == 0;
}

const std::weak_ptr<Product>& Selection::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Invalid index");
    }
    return data_[index];
}

std::ostream& operator<<(std::ostream& out, const Selection& selection) {
    out << selection.size() << '\n';

    for (std::size_t i{0}; i < selection.size(); ++i) {
        if (auto product = selection[i].lock()) {
            out << *product;
        } else {
            out << "[удалено]";
        }
        out << '\n';
    }
    return out;
}

}
