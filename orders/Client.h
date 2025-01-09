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
    explicit Client(string name);

    // method to add an order to the client
    void add_order(Order *order);

    // method to display the orders of the client
    int get_number_of_orders() const;

    // getter for the name of the client
    string get_name() const;

    // destructor to free the memory allocated for the orders
    ~Client();
};


#endif //CLIENTS_H
