#ifndef PRODUCTSANDSERVICES_H
#define PRODUCTSANDSERVICES_H

#include<iostream>
using namespace std;

// class that represents a product or a service
class ProductsAndServices {
private:
    string name;
    string type;
    double cost = 0.0;
    int quantity = 0;

public:
    // constructor which initializes the product or service with the given name, type, cost and quantity
    ProductsAndServices(string name, string type, double cost, int quantity);

    // getters for the attributes of the product or service
    string get_product_name() const;

    string get_type() const;

    double get_cost() const;

    int get_quantity() const;

    ~ProductsAndServices();
};


#endif //PRODUCTSANDSERVICES_H
