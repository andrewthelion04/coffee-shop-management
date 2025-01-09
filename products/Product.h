#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include <utility>

using namespace std;

// class that represents a product
class Product {
private:
    // encapsulation of the attributes
    string name;
    string type;
    double purchase_price = 0.0;
    double sale_price = 0.0;
    int quantity = 0;

public:
    // constructor which initializes the product with the given name, type, purchase price, sale price and quantity
    Product(string name, string type, double purchase_price, double sale_price, int quantity);

    // getters for the attributes of the product
    string get_name() const;

    string get_type() const;

    double get_purchase_price() const;

    double get_sale_price() const;

    int get_quantity() const;

    void set_quantity(int quantity);

    double get_acquisition_cost() const;

    ~Product(); // destructor
};


#endif //PRODUCT_H
