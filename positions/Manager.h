
#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"
#include<iostream>

class Manager: public Employee {
private:
    string position = "Manager";

public:
    Manager(string coffee_shop_city, string coffee_shop_address, string name, string surname, string start_shift, string end_shift, string position, float salary)
        : Employee(coffee_shop_city, coffee_shop_address, name, surname, start_shift, end_shift, position, salary) {}

    string get_position() const override {
        return position;
    }


    float calculate_salary() const override {
        return salary;
    }
};

#endif //MANAGER_H
