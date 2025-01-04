
#ifndef CLIENTS_H
#define CLIENTS_H

#include<iostream>
#include "Order.h"
using namespace std;

class Client {
private:
    string name;
    vector<Order*>orders;
public:
    explicit Client(string name): name(std::move(name)) {}

    void add_order(Order* order) {
        orders.push_back(order);
    }

    int get_number_of_orders() const {
        return orders.size();
    }




    string get_name() const {
        return name;
    }


    ~Client() = default;
};



#endif //CLIENTS_H
