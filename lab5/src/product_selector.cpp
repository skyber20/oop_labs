#include "lab5/product_selector.hpp"

namespace lab5 {

PriceBelowSelector::PriceBelowSelector(double limit) : limit_(limit) {}

bool PriceBelowSelector::matches(const Product& product) const {
    return product.price() < limit_;
}

bool AllProductsSelector::matches(const Product&) const {
    return true;
}

}
