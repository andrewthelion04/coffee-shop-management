//
// Created by leupe on 02.01.2025.
//

#ifndef WAITER_H
#define WAITER_H

#include "Employee.h"
#include<iostream>
#include<random>
#include <utility>
using namespace std;

// class that represents a waiter, which inherits the Employee class
class Waiter : public Employee {
private:
    string position = "Waiter";
    int daily_orders;
    double tips;

public:
    // constructor which initializes the waiter with the given name, surname, start_shift, end_shift, position and salary
    Waiter(string name, string surname, string start_shift, string end_shift, string position, float salary);

    // method to get the position of the waiter
    string get_position() const override;

    void generate_daily_orders();

    void generate_tips();

    float calculate_salary() const override;

    ~Waiter(); // destructor to free the memory allocated for the waiter
};

#endif //WAITER_H
