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
    OrderedProduct(string product_name, int quantity, double price);

    // getter for the product name
    string get_product_name() const;

    // getter for the quantity
    int get_quantity() const;

    // getter for the price
    double get_price() const;

    // destructor to free the memory allocated for the ordered product
    ~OrderedProduct();
};


#endif //ORDEREDPRODUCT_H
