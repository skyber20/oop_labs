#pragma once

#include "lab5/product.hpp"

#include <cstddef>
#include <iosfwd>
#include <memory>

namespace lab5 {

class Selection {
private:
    std::size_t size_;
    std::size_t capacity_;
    std::unique_ptr<std::weak_ptr<Product>[]> data_;

public:
    Selection();
    Selection(const Selection& other);
    Selection(Selection&& other) noexcept;
    Selection& operator=(const Selection& other);
    Selection& operator=(Selection&& other) noexcept;
    ~Selection() = default;

    void swap(Selection& other) noexcept;
    void add(const std::weak_ptr<Product>& product);

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] const std::weak_ptr<Product>& operator[](std::size_t index) const;
};

std::ostream& operator<<(std::ostream& out, const Selection& selection);

}
