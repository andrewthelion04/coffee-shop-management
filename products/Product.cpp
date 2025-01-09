#include<iostream>
#include "Product.h"

using namespace std;

// constructor which initializes the product with the given name, type, purchase price, sale price and quantity
Product::Product(string name, string type, double purchase_price, double sale_price, int quantity)
    : name(std::move(name)), type(std::move(type)), purchase_price(purchase_price), sale_price(sale_price),
      quantity(quantity) {
}

// getters for the attributes of the product
string Product::get_name() const {
    return name;
}

string Product::get_type() const {
    return type;
}

double Product::get_purchase_price() const {
    return purchase_price;
}

double Product::get_sale_price() const {
    return sale_price;
}

int Product::get_quantity() const {
    return quantity;
}

void Product::set_quantity(int quantity) {
    this->quantity = quantity;
}

double Product::get_acquisition_cost() const {
    return purchase_price * quantity;
}

Product::~Product() = default; // destructor
