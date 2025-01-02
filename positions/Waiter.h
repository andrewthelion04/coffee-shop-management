//
// Created by leupe on 02.01.2025.
//

#ifndef WAITER_H
#define WAITER_H

#include "Position.h"
#include<iostream>
#include<random>
using namespace std;

class Waiter: public Position {
private:
    string position = "Waiter";
    int daily_orders;
    double tips;
public:
    Waiter(string name, string surname, string start_shift, string end_shift, string position, float salary)
        : Position(name, surname, start_shift, end_shift, position, salary) {}

    void generate_daily_orders() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(30, 60);
        daily_orders = dis(gen);
    }

    void generate_tips() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(50.0, 300);
        tips = dis(gen);
    }

    float calculate_salary() const override {
        double bonus = daily_orders * 0.8;
        return salary + tips + bonus;
    }
};

#endif //WAITER_H