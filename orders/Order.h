

#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include "OrderedProduct.h"
#include <utility>
#include<vector>
using namespace std;

class Order {
private:
    vector<OrderedProduct*> ordered_products;
    double total_price = 0.0;

public:
    Order() = default;

    double get_total_price() const {
        return total_price;
    }

    void add_product(string product_name, int quantity, double price) {
        ordered_products.push_back(new OrderedProduct(std::move(product_name), quantity, price));
    }

    void remove_product(const string& product_name) {
        for(auto product = ordered_products.begin(); product != ordered_products.end(); ++product) {
            if((*product)->get_product_name() == product_name) {
                ordered_products.erase(product);
                break;
            }
        }
    }

    void calculate_total_price() {
        for(auto& product : ordered_products) {
            total_price += product->get_price();
        }
    }

    void set_total_price(double total_price) {
        this->total_price = total_price;
    }


    ~Order() = default;
};



#endif //ORDER_H
