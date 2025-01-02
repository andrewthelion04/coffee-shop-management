
#ifndef MANAGER_H
#define MANAGER_H

#include "Position.h"
#include<iostream>

class Manager: public Position {
private:
    string position = "Manager";

public:
    Manager(string name, string surname, string start_shift, string end_shift, string position, float salary, int num_coffees_made)
        : Position(name, surname, start_shift, end_shift, position, salary) {}


    static float calculate_salary() override {
        return salary;
    }
};

#endif //MANAGER_H
