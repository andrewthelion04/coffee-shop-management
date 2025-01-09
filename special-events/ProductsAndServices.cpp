#include<iostream>
#include "ProductsAndServices.h"

using namespace std;

// constructor which initializes the product or service with the given name, type, cost and quantity
ProductsAndServices::ProductsAndServices(string name, string type, double cost, int quantity) : name(name), type(type),
    cost(cost),
    quantity(quantity) {
}

// getters for the attributes of the product or service
string ProductsAndServices::get_product_name() const {
    return name;
}

string ProductsAndServices::get_type() const {
    return type;
}

double ProductsAndServices::get_cost() const {
    return cost;
}

int ProductsAndServices::get_quantity() const {
    return quantity;
}

ProductsAndServices::~ProductsAndServices() = default;
