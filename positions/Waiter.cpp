#include<iostream>
#include "Waiter.h"

using namespace std;


// constructor which initializes the waiter with the given name, surname, start_shift, end_shift, position and salary
Waiter::Waiter(string name, string surname, string start_shift, string end_shift, string position, float salary)
    : Employee(std::move(name), surname, start_shift, end_shift, position, salary) {
}

// method to get the position of the waiter
string Waiter::get_position() const{
    return position;
}

void Waiter::generate_daily_orders() {
    // method to generate a random number of daily orders
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(30, 60);
    daily_orders = dis(gen);
}

void Waiter::generate_tips() {
    // method to generate a random number of tips
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(50.0, 300);
    tips = dis(gen);
}

float Waiter::calculate_salary() const {
    // method to calculate the salary of the waiter (use of polymorphism)
    double bonus = daily_orders * 0.8;
    return salary + tips + bonus;
}

Waiter::~Waiter() = default; // destructor to free the memory allocated for the waiter
