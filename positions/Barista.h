
#ifndef BARISTA_H
#define BARISTA_H

#include "Position.h"
#include<iostream>
#include<random>

using namespace std;

class Barista: public Position {
private:
    string position = "Barista";
    int num_coffees_made;

public:
    Barista(string name, string surname, string start_shift, string end_shift, string position, float salary, int num_coffees_made)
        : Position(name, surname, start_shift, end_shift, position, salary) {}

    void generate_coffee_count() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(25, 150);
        num_coffees_made = dis(gen);
    }

    float calculate_salary() const override {
        double bonus = num_coffees_made * 0.8;
        return salary + bonus;
    }
};



#endif //BARISTA_H
