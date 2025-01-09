#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include "OrderedProduct.h"
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
    Order();

    // getter for the total price of the order
    double get_total_price() const;

    // getter for the vector of ordered products
    vector<OrderedProduct *> get_ordered_products() const;

    // method to add a product to the order
    void add_product(string product_name, int quantity, double price);

    // method to calculate the total price of the order
    void calculate_total_price();

    // setter for the total price of the order
    void set_total_price(double total_price);

    // destructor to free the memory allocated for the ordered products
    ~Order();
};


#endif //ORDER_H
