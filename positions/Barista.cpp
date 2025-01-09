#include<iostream>
#include "Barista.h"

using namespace std;

// constructor which initializes the barista with the given name, surname, start_shift, end_shift, position and salary
Barista::Barista(string name, string surname, string start_shift, string end_shift, string position, float salary)
    : Employee(name, surname, start_shift, end_shift, position, salary) {
}

// method to get the position of the barista
string Barista::get_position() const {
    return position;
}

// method to generate a random number of coffees made by the barista, in order to get a bonus for the salary
void Barista::generate_coffee_count() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(25, 150);
    num_coffees_made = dis(gen);
}

// method to calculate the salary of the barista (use of polymorphism)
float Barista::calculate_salary() const {
    double bonus = num_coffees_made * 0.8;
    return salary + bonus;
}

Barista::~Barista() = default;
