#include<iostream>
#include "OrderedProduct.h"

using namespace std;


// constructor which initializes the ordered product with the given product name, quantity and price
OrderedProduct::OrderedProduct(string product_name, int quantity, double price)
    : product_name(std::move(product_name)), quantity(quantity), price(price) {
}

// getter for the product name
string OrderedProduct::get_product_name() const {
    return product_name;
}

// getter for the quantity
int OrderedProduct::get_quantity() const {
    return quantity;
}

// getter for the price
double OrderedProduct::get_price() const {
    return price;
}

// destructor to free the memory allocated for the ordered product
OrderedProduct::~OrderedProduct() = default;
