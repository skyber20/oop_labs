#pragma once

#include "lab5/product.hpp"

namespace lab5 {

class ProductSelector {
public:
    virtual ~ProductSelector() = default;
    [[nodiscard]] virtual bool matches(const Product& product) const = 0;
};

class PriceBelowSelector : public ProductSelector {
private:
    double limit_;

public:
    explicit PriceBelowSelector(double limit);
    [[nodiscard]] bool matches(const Product& product) const override;
};

class AllProductsSelector : public ProductSelector {
public:
    [[nodiscard]] bool matches(const Product& product) const override;
};

}
