#ifndef POSITION_H
#define POSITION_H
#include <string>

using namespace std;

// abstract class that represents an employee (Abstraction)
class Employee {
protected:
    string name;
    string surname;
    string start_shift;
    string end_shift;
    string position;
    double salary = 0.0;

public:
    // constructor which initializes the employee with the given name, surname, start_shift, end_shift, position and salary
    Employee(string name, string surname, string start_shift, string end_shift, string position, float salary)
        : name(name), surname(surname), start_shift(start_shift), end_shift(end_shift), position(position),
          salary(salary) {
    }


    // pure virtual method to calculate the salary of the employee
    virtual float calculate_salary() const = 0;

    // pure virtual method to get the position of the employee
    virtual string get_position() const = 0;

    //getters for the name, surname, start_shift, end_shift and salary of the employee
    string get_name() const {
        return name;
    }

    string get_surname() const {
        return surname;
    }

    string get_start_shift() const {
        return start_shift;
    }

    string get_end_shift() const {
        return end_shift;
    }

    float get_salary() {
        return salary;
    }

    // destructor to free the memory allocated for the employee
    ~Employee() = default;
};


#endif //POSITION_H
