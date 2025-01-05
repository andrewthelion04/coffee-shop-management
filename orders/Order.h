#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include "OrderedProduct.h"
#include <utility>
#include<vector>
using namespace std;

// class that represents an order
class Order {
private:
    // encapsulation of the attributes
    vector<OrderedProduct *> ordered_products;
    double total_price = 0.0;

public:
    // constructor which initializes the order with an empty vector of ordered products
    Order() = default;

    // getter for the total price of the order
    double get_total_price() const {
        return total_price;
    }

    // getter for the vector of ordered products
    vector<OrderedProduct *> get_ordered_products() const {
        return ordered_products;
    }

    // method to add a product to the order
    void add_product(string product_name, int quantity, double price) {
        ordered_products.push_back(new OrderedProduct(std::move(product_name), quantity, price));
    }

    // method to calculate the total price of the order
    void calculate_total_price() {
        for (auto &product: ordered_products) {
            total_price += product->get_quantity() * product->get_price();
        }
    }

    // setter for the total price of the order
    void set_total_price(double total_price) {
        this->total_price = total_price;
    }

    // destructor to free the memory allocated for the ordered products
    ~Order() = default;
};


#endif //ORDER_H
