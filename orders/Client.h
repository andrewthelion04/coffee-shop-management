#ifndef CLIENTS_H
#define CLIENTS_H

#include<iostream>
#include "Order.h"
using namespace std;

// class that represents a client
class Client {
private: //encapsulation of the attributes
    string name;
    vector<Order *> orders;

public:
    //constructor which initializes the client with the given name
    explicit Client(string name): name(std::move(name)) {
    }

    // method to add an order to the client
    void add_order(Order *order) {
        orders.push_back(order);
    }

    // method to display the orders of the client
    int get_number_of_orders() const {
        return orders.size();
    }

    // getter for the name of the client
    string get_name() const {
        return name;
    }

    // destructor to free the memory allocated for the orders
    ~Client() = default;
};


#endif //CLIENTS_H
