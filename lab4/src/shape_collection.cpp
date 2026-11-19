#include "lab4/shape_collection.hpp"
#include <stdexcept>
#include <utility>

namespace lab4 {
ShapeCollection::ShapeCollection() : size_(0), capacity_(0), data_(nullptr) {}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
    : size_(0), capacity_(other.capacity_),
      data_(capacity_ == 0 ? nullptr : new Shape*[capacity_]) {
    try {
        for (std::size_t i{0}; i < other.size_; ++i) {
            data_[i] = other.data_[i]->clone();
            ++size_;
        }
    } catch (...) {
        for (std::size_t i{0}; i < size_; ++i) {
            delete data_[i];
        }
        delete[] data_;
        throw;
    }
}

ShapeCollection::ShapeCollection(ShapeCollection&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other) {
    if (this != &other) {
        ShapeCollection tmp(other);
        swap(tmp);
    }
    return *this;
}

ShapeCollection& ShapeCollection::operator=(ShapeCollection&& other) noexcept {
    if (this != &other) {
        ShapeCollection tmp(std::move(other));
        swap(tmp);
    }
    return *this;
}

ShapeCollection::~ShapeCollection() {
    for (std::size_t i{0}; i < size_; ++i) {
        delete data_[i];
    }
    delete[] data_;
}

void ShapeCollection::swap(ShapeCollection& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

void ShapeCollection::add(const Shape& shape) {
    if (size_ == capacity_) {
        const std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        Shape** new_data = new Shape*[new_capacity];

        for (std::size_t i{0}; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        try {
            new_data[size_] = shape.clone();
        } catch (...) {
            delete[] new_data;
            throw;
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    } else {
        data_[size_] = shape.clone();
    }

    ++size_;
}

bool ShapeCollection::remove(std::size_t index) {
    if (index >= size_) {
        return false;
    }

    delete data_[index];
    for (std::size_t i{index}; i + 1 < size_; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
    data_[size_] = nullptr;
    return true;
}

std::size_t ShapeCollection::size() const noexcept {
    return size_;
}

const Shape& ShapeCollection::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Invalid index");
    }
    return *data_[index];
}

double ShapeCollection::totalMetric() const {
    double total = 0.0;
    for (std::size_t i{0}; i < size_; ++i) {
        total += data_[i]->metric();
    }
    return total;
}
}
