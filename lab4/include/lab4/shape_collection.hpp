#pragma once

#include "lab4/shape.hpp"
#include <cstddef>

namespace lab4 {
class ShapeCollection {
private:
    std::size_t size_;
    std::size_t capacity_;
    Shape** data_;

public:
    ShapeCollection();
    ShapeCollection(const ShapeCollection& other);
    ShapeCollection(ShapeCollection&& other) noexcept;
    ShapeCollection& operator=(const ShapeCollection& other);
    ShapeCollection& operator=(ShapeCollection&& other) noexcept;
    ~ShapeCollection();

    void swap(ShapeCollection& other) noexcept;
    void add(const Shape& shape);
    bool remove(std::size_t index);

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] const Shape& at(std::size_t index) const;
    [[nodiscard]] double totalMetric() const;
};
}
