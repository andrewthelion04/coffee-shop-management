#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include<iostream>
#include <utility>
#include<vector>
#include "ProductsAndServices.h"
using namespace std;

// class that represents a special event
class SpecialEvent {
private:
    string name;
    string description;
    string start_time;
    vector<ProductsAndServices*>required_products; // vector of objects of type ProductsAndServices
    double total_costs = 0.0;
public:
    // constructor which initializes the special event with the given name, description and start time
    SpecialEvent(string name, string description, string start_time) : name(std::move(name)), description(std::move(description)), start_time(std::move(start_time)) {}

    // getters for the attributes of the special event
    string get_name() const {
        return name;
    }

    string get_description() const {
        return description;
    }

    string get_start_time() const {
        return start_time;
    }

    vector<ProductsAndServices*> get_required_products() const {
        return required_products;
    }

    double get_total_costs() const {
        return total_costs;
    }

    // method to calculate the total costs of the special event
    void calculate_total_costs() {
        for(auto& product : required_products) {
            total_costs += product->get_quantity() * product->get_cost();
        }
    }

    // method to add a required product to the special event (in the vector of required products)
    void add_required_product(const string& product_name, const string& type, double cost, int quantity) {
        required_products.push_back(new ProductsAndServices(product_name, type, cost, quantity));
    }

    ~SpecialEvent() = default;
};



#endif //SPECIALEVENT_H
