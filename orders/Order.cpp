#include<iostream>
#include "Order.h"

using namespace std;

// constructor which initializes the order with an empty vector of ordered products
Order::Order() = default;

// getter for the total price of the order
double Order::get_total_price() const {
    return total_price;
}

// getter for the vector of ordered products
vector<OrderedProduct *> Order::get_ordered_products() const {
    return ordered_products;
}

// method to add a product to the order
void Order::add_product(string product_name, int quantity, double price) {
    ordered_products.push_back(new OrderedProduct(std::move(product_name), quantity, price));
}

// method to calculate the total price of the order
void Order::calculate_total_price() {
    for (auto &product: ordered_products) {
        total_price += product->get_quantity() * product->get_price();
    }
}

// setter for the total price of the order
void Order::set_total_price(double total_price) {
    this->total_price = total_price;
}

// destructor to free the memory allocated for the ordered products
Order::~Order() = default;
