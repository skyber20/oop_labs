#pragma once

#include <iosfwd>
#include <string>

namespace lab5 {

class Product {
private:
    std::string name_;
    std::string category_;
    double price_;
    static int alive_;

public:
    Product(std::string name, std::string category, double price);
    explicit Product(double price);
    Product(const Product& other);
    Product(Product&& other) noexcept;
    Product& operator=(const Product& other) = delete;
    Product& operator=(Product&& other) = delete;
    ~Product();

    [[nodiscard]] const std::string& name() const noexcept;
    [[nodiscard]] const std::string& category() const noexcept;
    [[nodiscard]] double price() const noexcept;
    [[nodiscard]] static int aliveCount() noexcept;

    bool operator<(const Product& other) const;
    bool operator==(const Product& other) const;
};

std::ostream& operator<<(std::ostream& out, const Product& product);

}
