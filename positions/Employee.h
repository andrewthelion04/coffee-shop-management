

#ifndef POSITION_H
#define POSITION_H
#include <string>

using namespace std;

class Employee {
protected:
    string coffee_shop_city;
    string coffee_shop_address;
    string name;
    string surname;
    string start_shift;
    string end_shift;
    string position;
    double salary = 0.0;
public:
    Employee(string coffee_shop_city, string coffee_shop_address, string name, string surname, string start_shift, string end_shift, string position, float salary)
        : coffee_shop_city(coffee_shop_city), coffee_shop_address(coffee_shop_address), name(name), surname(surname), start_shift(start_shift), end_shift(end_shift), position(position), salary(salary) {}


    virtual float calculate_salary() const = 0;

    virtual string get_position() const = 0;

    string get_coffee_shop_city() const {
        return coffee_shop_city;
    }

    string get_coffee_shop_address() const {
        return coffee_shop_address;
    }

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

    ~Employee() = default;
};



#endif //POSITION_H