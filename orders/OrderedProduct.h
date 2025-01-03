#ifndef ORDEREDPRODUCT_H
#define ORDEREDPRODUCT_H

#include<iostream>
using namespace std;


class OrderedProduct {
private:
    string product_name;
    int quantity = 0;
    double price = 0.0;
public:
    OrderedProduct(string product_name, int quantity, double price)
        : product_name(std::move(product_name)), quantity(quantity), price(price) {}

    string get_product_name() const {
        return product_name;
    }

    int get_quantity() const {
        return quantity;
    }

    double get_price() const {
        return price;
    }

    ~OrderedProduct() = default;
};



#endif //ORDEREDPRODUCT_H
