#include<iostream>
#include "Manager.h"

using namespace std;

// constructor which initializes the manager with the given name, surname, start_shift, end_shift, position and salary
Manager::Manager(string name, string surname, string start_shift, string end_shift, string position, float salary)
    : Employee(name, surname, start_shift, end_shift, position, salary) {
}

// method to get the position of the manager
string Manager::get_position() const{
    return position;
}

// method to calculate the salary of the manager (use of polymorphism)
float Manager::calculate_salary() const{
    return salary;
}

// destructor to free the memory allocated for the manager
Manager::~Manager() = default;
