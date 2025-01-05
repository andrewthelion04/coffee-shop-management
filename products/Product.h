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
    Product(string name, string type, double purchase_price, double sale_price, int quantity)
        : name(std::move(name)), type(std::move(type)), purchase_price(purchase_price), sale_price(sale_price),
          quantity(quantity) {
    }

    // getters for the attributes of the product
    string get_name() const {
        return name;
    }

    string get_type() const {
        return type;
    }

    double get_purchase_price() const {
        return purchase_price;
    }

    double get_sale_price() const {
        return sale_price;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int quantity) {
        this->quantity = quantity;
    }

    double get_acquisition_cost() const {
        return purchase_price * quantity;
    }

    ~Product() = default; // destructor
};


#endif //PRODUCT_H
