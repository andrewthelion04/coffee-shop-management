

#ifndef POSITION_H
#define POSITION_H
#include <string>

using namespace std;

class Position {
protected:
    string name;
    string surname;
    string start_shift;
    string end_shift;
    string position;
    double salary = 0.0;
public:
    Position(string name, string surname, string start_shift, string end_shift, string position, float salary)
        : Position(name, surname, start_shift, end_shift, position, salary) {}


    virtual float calculate_salary() const = 0;

    virtual string get_position() const = 0;

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

    ~Position() = default;
};



#endif //POSITION_H
