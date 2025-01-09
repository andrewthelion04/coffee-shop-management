#include<iostream>
#include "Employee.h"

using namespace std;

// constructor which initializes the employee with the given name, surname, start_shift, end_shift, position and salary
Employee::Employee(string name, string surname, string start_shift, string end_shift, string position, float salary)
    : name(name), surname(surname), start_shift(start_shift), end_shift(end_shift), position(position),
      salary(salary) {
}


//getters for the name, surname, start_shift, end_shift and salary of the employee
string Employee::get_name() const {
    return name;
}

string Employee::get_surname() const {
    return surname;
}

string Employee::get_start_shift() const {
    return start_shift;
}

string Employee::get_end_shift() const {
    return end_shift;
}

float Employee::get_salary() {
    return salary;
}

// destructor to free the memory allocated for the employee
Employee::~Employee() = default;
