#include<iostream>
#include "Client.h"

using namespace std;

//constructor which initializes the client with the given name
Client::Client(string name): name(std::move(name)) {
}

// method to add an order to the client
void Client::add_order(Order *order) {
    orders.push_back(order);
}

// method to display the orders of the client
int Client::get_number_of_orders() const {
    return orders.size();
}

// getter for the name of the client
string Client::get_name() const {
    return name;
}

// destructor to free the memory allocated for the orders
Client::~Client() = default;
