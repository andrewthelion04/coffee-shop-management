#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"
#include<iostream>

// class that represents a manager, which inherits the Employee class
class Manager : public Employee {
private:
    string position = "Manager";

public:
    // constructor which initializes the manager with the given name, surname, start_shift, end_shift, position and salary
    Manager(string name, string surname, string start_shift, string end_shift, string position, float salary);


    // method to get the position of the manager
    string get_position() const override;

    // method to calculate the salary of the manager (use of polymorphism)
    float calculate_salary() const override;

    // destructor to free the memory allocated for the manager
    ~Manager();
};

#endif //MANAGER_H
