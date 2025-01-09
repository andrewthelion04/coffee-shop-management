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
    Barista(string name, string surname, string start_shift, string end_shift, string position, float salary);

    // method to get the position of the barista
    string get_position() const override;

    // method to generate a random number of coffees made by the barista, in order to get a bonus for the salary
    void generate_coffee_count();

    // method to calculate the salary of the barista (use of polymorphism)
    float calculate_salary() const override;

    ~Barista();
};


#endif //BARISTA_H
