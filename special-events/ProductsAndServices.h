#ifndef PRODUCTSANDSERVICES_H
#define PRODUCTSANDSERVICES_H

#include<iostream>
using namespace std;

class ProductsAndServices {
private:
    string name;
    string type;
    double cost = 0.0;
    int quantity = 0;

public:
    ProductsAndServices(string name, string type, double cost, int quantity) : name(name), type(type), cost(cost), quantity(quantity) {}

    string get_product_name() const {
        return name;
    }

    string get_type() const {
        return type;
    }

    double get_cost() const {
        return cost;
    }

    int get_quantity() const {
        return quantity;
    }

    ~ProductsAndServices() = default;
};



#endif //PRODUCTSANDSERVICES_H
