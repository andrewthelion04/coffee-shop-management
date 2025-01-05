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
class Waiter: public Employee {
private:
    string position = "Waiter";
    int daily_orders;
    double tips;
public:

    // constructor which initializes the waiter with the given name, surname, start_shift, end_shift, position and salary
    Waiter(string name, string surname, string start_shift, string end_shift, string position, float salary)
        : Employee(std::move(name), surname, start_shift, end_shift, position, salary) {}

    // method to get the position of the waiter
    string get_position() const override {
        return position;
    }

    void generate_daily_orders() {  // method to generate a random number of daily orders
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(30, 60);
        daily_orders = dis(gen);
    }

    void generate_tips() {  // method to generate a random number of tips
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(50.0, 300);
        tips = dis(gen);
    }

    float calculate_salary() const override { // method to calculate the salary of the waiter (use of polymorphism)
        double bonus = daily_orders * 0.8;
        return salary + tips + bonus;
    }
    ~Waiter() = default; // destructor to free the memory allocated for the waiter
};

#endif //WAITER_H
