#ifndef ORDEREDPRODUCT_H
#define ORDEREDPRODUCT_H

#include<iostream>
using namespace std;

// class that represents an ordered product
class OrderedProduct {
private: // encapsulation of the attributes
    string product_name;
    int quantity = 0;
    double price = 0.0;
public:
    // constructor which initializes the ordered product with the given product name, quantity and price
    OrderedProduct(string product_name, int quantity, double price)
        : product_name(std::move(product_name)), quantity(quantity), price(price) {}

    // getter for the product name
    string get_product_name() const {
        return product_name;
    }

    // getter for the quantity
    int get_quantity() const {
        return quantity;
    }

    // getter for the price
    double get_price() const {
        return price;
    }

    // destructor to free the memory allocated for the ordered product
    ~OrderedProduct() = default;
};



#endif //ORDEREDPRODUCT_H
