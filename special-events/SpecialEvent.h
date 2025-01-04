#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include<iostream>
#include <utility>
#include<vector>
#include "ProductsAndServices.h"
using namespace std;


class SpecialEvent {
private:
    string name;
    string description;
    vector<ProductsAndServices*>required_products;
    double total_costs = 0.0;
public:
    SpecialEvent(string name, string description) : name(std::move(name)), description(std::move(description)) {}

    string get_name() const {
        return name;
    }

    string get_description() const {
        return description;
    }

    vector<ProductsAndServices*> get_required_products() const {
        return required_products;
    }

    double get_total_costs() const {
        return total_costs;
    }

    void calculate_total_costs() {
        for(auto& product : required_products) {
            total_costs += product->get_quantity() * product->get_cost();
        }
    }

    void add_required_product(const string& product_name, const string& type, double cost, int quantity) {
        required_products.push_back(new ProductsAndServices(product_name, type, cost, quantity));
    }

    ~SpecialEvent() = default;
};



#endif //SPECIALEVENT_H
