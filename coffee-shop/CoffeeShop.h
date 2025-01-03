#ifndef COFFEESHOP_H
#define COFFEESHOP_H

#include<iostream>
#include "../positions/Employee.h"
#include "../positions/Barista.h"
#include "../positions/Waiter.h"
#include "../positions/Manager.h"
#include "../products/Product.h"
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

class CoffeeShop {
private:
    string coffee_shop_address;
    string coffee_shop_city;
    vector<Employee*> employees;
    vector<Product*> products;

public:
    CoffeeShop(string coffee_shop_address, string coffee_shop_city) : coffee_shop_address(coffee_shop_address), coffee_shop_city(coffee_shop_city) {}

    string get_coffee_shop_address() {
        return coffee_shop_address;
    }

    string get_coffee_shop_city() {
        return coffee_shop_city;
    }

    void add_employee() {
        string name, surname, position, salary, shift_start, shift_end;
        int position_choice;

        cout << "Adding an employee to the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address << "!" << endl;
        cout << "Enter the name of the employee: ";
        getline(cin, name);
        if(!is_name_valid(name)) {
            throw "Invalid name!";
        }

        cout << "Enter the surname of the employee: ";
        getline(cin, surname);
        if(!is_name_valid(surname)) {
            throw "Invalid surname!";
        }

        cout << "Select the position they will hold!\n" <<
            "1.Barista\n" << "2.Waiter\n" << "3.Manager\n";
        cout<<"Your choice: ";
        cin>>position_choice;
        cin.ignore();
        if(position_choice < 1 || position_choice > 3) {
            throw "Invalid choice!";
        }
        else {
            if(position_choice == 1) {
                position = "Barista";
            }
            else if(position_choice == 2) {
                position = "Waiter";
            }
            else {
                position = "Manager";
            }
        }

        cout << "Enter his/hers salary: ";
        getline(cin, salary);

        is_salary_valid(salary);

        cout << "Enter the shift start (HH:MM) : ";
        getline(cin, shift_start);

        cout << "Enter the shift end (HH:MM) : ";
        getline(cin, shift_end);

        is_shift_valid(shift_start, shift_end);

        Employee* employee = nullptr;
        switch (position_choice) {
            case 1:
                employees.push_back(new Barista(name, surname, shift_start, shift_end, position, stof(salary)));
            break;
            case 2:
                employees.push_back(new Waiter(name, surname, shift_start, shift_end, position, stof(salary)));
            break;
            case 3:
                employees.push_back(new Manager(name, surname, shift_start, shift_end, position, stof(salary)));
            break;
            default:
                throw "Invalid choice!";
        }

        delete employee;

        ofstream employees_file("employees.csv", ios::app);
        if (!employees_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        employees_file << coffee_shop_city << "," << coffee_shop_address << "," << name << "," << surname << "," << position << "," << salary << "," << shift_start << "," << shift_end << endl;
        employees_file.close();
    }

    void remove_employee() {
        string name, surname, position;
        cout << "Removing an employee from the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address << "!" << endl;

        cout<<"Enter the name of the employee: ";
        getline(cin, name);

        cout<<"Enter the surname of the employee: ";
        getline(cin, surname);

        cout<<"Enter the position of the employee: ";
        getline(cin, position);


        ifstream input_file("employees.csv");
        vector<string> lines;
        string line;
        bool employee_found = false;

        if(!input_file.is_open()) {
            throw "Error: File not opened";
        }

        //citeste header-ul si il adauga in vector
        getline(input_file, line);
        lines.push_back(line);

        while(getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address, read_name, read_surname, read_position, read_salary, read_shift_start, read_shift_end;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss,read_name, ',');
            getline(ss,read_surname, ',');
            getline(ss,read_position, ',');
            getline(ss,read_salary, ',');
            getline(ss,read_shift_start, ',');
            getline(ss,read_shift_end, ',');


            if(name == read_name && surname == read_surname && position == read_position) {
                employee_found = true;
            }
            else {
                lines.push_back(line);
            }
        }
        input_file.close();

        if(employee_found) {
            ofstream outputFile("employees.csv");
            if(!outputFile.is_open()) {
                throw "Error: File not opened";
            }

            for(const string& l : lines) {
                outputFile << l << endl;
            }
            outputFile.close();

            Employee* removed_employee = nullptr;
            if(position == "Barista") {
                removed_employee = new Barista(name, surname, "", "", position, 0);
            }
            else if(position == "Waiter") {
                removed_employee = new Waiter(name, surname, "", "", position, 0);
            }
            else if(position == "Manager") {
                removed_employee = new Manager(name, surname, "", "", position, 0);
            }

            for(auto employee = employees.begin(); employee != employees.end(); ++employee) {
                if((*employee)->get_name() == removed_employee->get_name() &&
                   (*employee)->get_surname() == removed_employee->get_surname() &&
                   (*employee)->get_position() == removed_employee->get_position()) {
                    employees.erase(employee);
                    break;
                   }
            }

            delete removed_employee;
            cout << "The employee was successfully removed!" << endl << endl;
        }
        else {
            throw "The employee was not found!";
        }
    }

    void add_product() {
        string product_name, type, purchase_price, sale_price, quantity;
        int type_choice;

        cout<<"Adding a product to the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address << "!" << endl;
        cout<<"Select the type of product you wish to add!\n" <<
        "1.Coffee\n" << "2.Beverage\n" << "3.Desert\n";
        cout << "Your choice: ";
        cin >> type_choice;
        cin.ignore();

        if(type_choice < 1 || type_choice > 3) {
            throw "Invalid choice!";
        }
        else {
            if(type_choice == 1) {
                type = "Coffee";
            }
            else if(type_choice == 2) {
                type = "Beverage";
            }
            else {
                type = "Desert";
            }
        }

        cout << "Enter the name of the product: ";
        getline(cin, product_name);

        cout << "Enter the quantity: ";
        getline(cin, quantity);

        cout << "Enter the purchase price of the product: ";
        getline(cin, purchase_price);

        cout << "Enter the sale price of the product: ";
        cin >> sale_price;
        cin.ignore();

        products.push_back(new Product(product_name, type, stof(purchase_price), stof(sale_price), stoi(quantity)));

        ofstream products_file("products.csv", ios::app);
        if(!products_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        products_file << coffee_shop_city << "," << coffee_shop_address << "," << product_name << "," << type << "," << purchase_price << "," << sale_price << "," << quantity << endl;
        products_file.close();
    }

    void delete_product() {
        string product_name, type;
        int type_choice;
        cout << "Removing a product from the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address << "!" << endl;

        cout << "Select the type of product you wish to remove:\n" <<
            "1.Coffee\n" << "2.Beverage\n" << "3.Desert\n";
        cin >> type_choice;
        cin.ignore();

        if(type_choice < 1 || type_choice > 3) {
            throw "Invalid choice!";
        }
        else {
            if(type_choice == 1) {
                type = "Coffee";
            }
            else if(type_choice == 2) {
                type = "Beverage";
            }
            else {
                type = "Desert";
            }
        }

        cout << "Enter the name of the product: ";
        getline(cin, product_name);

        ifstream input_file("products.csv");
        vector<string> lines;
        string line;
        bool product_found = false;

        if(!input_file.is_open()) {
            throw "Error: File not opened";
        }

        getline(input_file, line);
        lines.push_back(line);


        while(getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address, read_product_name, read_type, read_purchase_price, read_sale_price, read_quantity;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss, read_product_name, ',');
            getline(ss, read_type, ',');
            getline(ss, read_purchase_price, ',');
            getline(ss, read_sale_price, ',');
            getline(ss, read_quantity, ',');

            if(product_name == read_product_name && type == read_type) {
                product_found = true;
            }
            else {
                lines.push_back(line);
            }
        }
        input_file.close();

        if(product_found) {
            ofstream outputFile("products.csv");
            if(!outputFile.is_open()) {
                throw "Error: File not opened";
            }

            for(const string& l : lines) {
                outputFile << l << endl;
            }
            outputFile.close();

            Product *removed_product = new Product(product_name, type, 0, 0, 0);
            for(auto product = products.begin(); product != products.end(); ++product) {
                if((*product)->get_name() == removed_product->get_name() &&
                   (*product)->get_type() == removed_product->get_type()) {
                    products.erase(product);
                    break;
                }
            }

            delete removed_product;
            cout << "The product was successfully removed!" << endl << endl;

        }
        else {
            throw "The product was not found!";
        }
    }


    void display_employees_information(string coffee_shop_city, string coffee_shop_address) {
        int index = 0;

        if(employees.size() == 0) {
            throw "There are no employees at the coffee shop located in " + coffee_shop_city + " - " + coffee_shop_address + "!";
        }

        cout<<"Information regarding the employees at the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address << ":" << endl;
        for(auto& employee: employees) {
            cout << "Employee " << ++index << ": " << employee->get_name() << " " << employee->get_surname() << endl;
            cout << "\t->Position: " << employee->get_position() << endl;
            cout << "\t->Salary: " << employee->get_salary() << endl;
            cout << "\t->Shift: " << employee->get_start_shift() << " - " << employee->get_end_shift() << endl;
            cout << endl;

        }
    }

    void display_employees_shifts(string coffee_shop_city, string coffee_shop_address) {
        if(employees.size() == 0) {
            throw "There are no employees at the coffee shop located in " + coffee_shop_city + " - " + coffee_shop_address + "!";
        }

        cout << "List of all the employees and their shifts at the coffee shop located in " << coffee_shop_city << " - "
                << coffee_shop_address << ":" << endl;
        for(auto& employee : employees){
            cout << employee->get_name() << " " << employee->get_surname() << " -> " <<employee->get_start_shift() << " - " << employee->get_end_shift() << endl;
            cout << endl;
        }
    }

    static void is_salary_valid(string salary) {
        for(char& c: salary) {
            if(!isdigit(c)) {
                throw "Invalid salary! Please use only digits!";
            }
        }
    }

    static void is_shift_valid(string shift1, string shift2) {
        if((shift1.length() != 5 || shift1[2] != ':') || (shift2.length() != 5 || shift2[2] != ':')) {
            throw "Invalid shift format! Please use HH:MM!";
        }

        int hour_shift1 = stoi(shift1.substr(0,2));
        int hour_shift2 = stoi(shift2.substr(0,2));

        int minute_shift1 = stoi(shift1.substr(3, 5));
        int minute_shift2 = stoi(shift2.substr(3, 5));


        if((0 <= hour_shift1 && hour_shift1 <= 23 && 0 <= minute_shift1 && minute_shift1 <= 59) ||
            (0 <= hour_shift2 && hour_shift2 <= 23 && 0 <= minute_shift2 && minute_shift2 <= 59)) {
            if(hour_shift1 < hour_shift2) {
                throw "Invalid shift! The start shift must be before the end shift!";
            }
            if(hour_shift1 == hour_shift2) {
                if(minute_shift1 < minute_shift2) {
                    throw "Invalid shift! The start shift must be before the end shift!";
                }
            }
        }
    }

    static bool is_name_valid(string name) {
        for(char& c: name) {
            if(!isalpha(c)) {
                return false;
            }
        }
        return true;
    }


    ~CoffeeShop() = default;
};


#endif //COFFEESHOP_H
