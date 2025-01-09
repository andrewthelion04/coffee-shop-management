#include<iostream>
#include "SpecialEvent.h"

using namespace std;

// constructor which initializes the special event with the given name, description and start time
SpecialEvent::SpecialEvent(string name, string description, string start_time) : name(std::move(name)),
    description(std::move(description)),
    start_time(std::move(start_time)) {
}

// getters for the attributes of the special event
string SpecialEvent::get_name() const {
    return name;
}

string SpecialEvent::get_description() const {
    return description;
}

string SpecialEvent::get_start_time() const {
    return start_time;
}

vector<ProductsAndServices *> SpecialEvent::get_required_products() const {
    return required_products;
}

double SpecialEvent::get_total_costs() const {
    return total_costs;
}

// method to calculate the total costs of the special event
void SpecialEvent::calculate_total_costs() {
    for (auto &product: required_products) {
        total_costs += product->get_quantity() * product->get_cost();
    }
}

// method to add a required product to the special event (in the vector of required products)
void SpecialEvent::add_required_product(const string &product_name, const string &type, double cost, int quantity) {
    required_products.push_back(new ProductsAndServices(product_name, type, cost, quantity));
}

SpecialEvent::~SpecialEvent() = default;
