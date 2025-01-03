
#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include <utility>

using namespace std;

class Product {
private:

    string name;
    string type;
    double purchase_price = 0.0;
    double sale_price = 0.0;
    int quantity = 0;

public:
    Product(string name, string type, double purchase_price, double sale_price, int quantity)
        :name(std::move(name)), type(std::move(type)), purchase_price(purchase_price), sale_price(sale_price), quantity(quantity) {}

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
};



#endif //PRODUCT_H
