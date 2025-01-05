#ifndef BARISTA_H
#define BARISTA_H

#include "Employee.h"
#include<iostream>
#include<random>

using namespace std;

// class that represents a barista, which inherits the Employee class
class Barista : public Employee {
private:
    string position = "Barista";
    int num_coffees_made;

public:
    // constructor which initializes the barista with the given name, surname, start_shift, end_shift, position and salary
    Barista(string name, string surname, string start_shift, string end_shift, string position, float salary)
        : Employee(name, surname, start_shift, end_shift, position, salary) {
    }

    // method to get the position of the barista
    string get_position() const override {
        return position;
    }

    // method to generate a random number of coffees made by the barista, in order to get a bonus for the salary
    void generate_coffee_count() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(25, 150);
        num_coffees_made = dis(gen);
    }

    // method to calculate the salary of the barista (use of polymorphism)
    float calculate_salary() const override {
        double bonus = num_coffees_made * 0.8;
        return salary + bonus;
    }

    ~Barista() = default;
};


#endif //BARISTA_H
