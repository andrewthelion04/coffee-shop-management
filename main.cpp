#include<iostream>
#include<fstream>
#include <utility>
#include<vector>
#include<sstream>
#include "initialize_files.h"
#include "positions/Barista.h"
#include "positions/Waiter.h"
#include "positions/Manager.h"

using namespace std;

class CoffeeShops {
private:
    string coffee_shop_address;
    string coffee_shop_city;

public:
    CoffeeShops(string coffee_shop_address, string coffee_shop_city) : coffee_shop_address(coffee_shop_address), coffee_shop_city(coffee_shop_city) {}

    string get_coffee_shop_address() {
        return coffee_shop_address;
    }

    string get_coffee_shop_city() {
        return coffee_shop_city;
    }

    ~CoffeeShops() = default;
};


class CoffeeShopManager {
private:
    vector<CoffeeShops> coffee_shops;
    vector<Position> employees;
public:

    static bool valid_city_name(const string &city_name) {
        for (static char c : city_name) {
            if (!isalpha(c) && c != ' ' && c != '-') { // permite doar litere, spatii si cratime
                return false; // daca se gaseste un caracter invalid, returneaza false
            }
        }

        string cities[] = {"Bucuresti", "Cluj-Napoca", "Timisoara", "Iasi",  "Brasov"};
        for(const string& c : cities) {
            if(city_name == c) {
                return true;
                break;
            }
        }

        return false;
    }

    void add_coffee_shop() {
        string city, address;

        cout << "Add coffee shop" << endl;

        cout << "Enter the city in which the coffee shop is located: ";
        getline(cin, city);

        cout << "Enter the address of the coffee shop: ";
        getline(cin, address);

        if (valid_city_name(city)) {
            // Adaugă cafeneaua în vectorul intern
            CoffeeShops shop(address, city);
            coffee_shops.push_back(shop);

            // Append în fișierul CSV
            ofstream coffee_shops_file("coffee_shops.csv", ios::app);
            if (!coffee_shops_file.is_open()) {
                cout << "Error: File not opened" << endl;
                return;
            }

            coffee_shops_file << city << "," << address << endl;
            coffee_shops_file.close();

            cout << "Coffee shop was successfully added!" << endl;
        } else {
            throw "The entered city is not in the list of cities where we have coffee shops!";
        }
    }

    void remove_coffee_shop() {
        string name, city, address;

        cout<<"Remove coffee shop"<<endl<<endl;

        cout<<"Enter the city in which the coffee shop is located: ";
        getline(cin, city);

        cout<<"Enter the address of the coffee shop: ";
        getline(cin, address);

        ifstream input_file("coffee_shops.csv");
        vector<string> lines;
        string line;
        bool coffee_shop_found = false;

        if(!input_file.is_open()) {
            throw "Error: File not opened";

        }

        //citeste header-ul si il adauga in vector
        getline(input_file, line);
        lines.push_back(line);

        while(getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');

            if(city == read_city && address == read_address) {
                coffee_shop_found = true;
            }
            else {
                lines.push_back(line);
            }
        }
        input_file.close();

        if(coffee_shop_found) {
            ofstream outputFile("coffee_shops.csv");
            if(!outputFile.is_open()) {
                throw "Error: File not opened";
            }

            for(const string& l : lines) {
                outputFile << l << endl;
            }
            outputFile.close();

            CoffeeShops removed_coffee_shop(address, city);
            for(auto shop = coffee_shops.begin(); shop != coffee_shops.end(); ++shop) {
                if(shop->get_coffee_shop_address() == removed_coffee_shop.get_coffee_shop_address() &&
                   shop->get_coffee_shop_city() == removed_coffee_shop.get_coffee_shop_city()) {
                    coffee_shops.erase(shop);
                    break;
                }
            }

            cout << "Coffee shop was successfully removed!" << endl << endl;
        }
        else {
            throw "The coffee shop was not found!";
        }
    }

    void display_coffee_shops() {
        for (int i = 0; i < coffee_shops.size(); ++i) {
            cout << i + 1 << ". " << coffee_shops[i].get_coffee_shop_city()
                 << " - " << coffee_shops[i].get_coffee_shop_address() << endl;
        }
    }

    CoffeeShops* choose_coffee_shop() {
        if(coffee_shops.empty()) {
            throw "No coffee shops available!";
        }

        cout<<"Select a coffee shop:"<<endl;
        display_coffee_shops();

        int choice;
        cout<<"Your choice: ";
        cin>>choice;

        if(choice < 1 || choice > coffee_shops.size()) {
            throw "Invalid choice!";
        }

        return &coffee_shops[choice - 1];
    }

    void add_employee(string coffee_shop_city, string coffee_shop_address) {
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
        if(position_choice < 1 || position_choice > 3) {
            throw "Invalid choice!";
        }

        cout << "Enter his/hers salary: ";
        getline(cin, salary);
        if(!is_salary_valid(salary)) {
            throw "Invalid salary!";
        }

        cout << "Enter the shift start: ";
        getline(cin, shift_start);
        if(!is_shift_valid(shift_start)) {
            throw "Invalid shift start!";
        }

        cout << "Enter the shift end (HH:MM): ";
        getline(cin, shift_end);
        if(!is_shift_valid(shift_end)) {
            throw "Invalid shift end!";
        }

        switch (position_choice) {
            case 1:
                position = "Barista";
                Barista barista_employee(name, surname, shift_start, shift_end, position, stof(salary));
                employees.push_back(barista_employee);
            break;
            case 2:
                position = "Waiter";
                Waiter waiter_employee(name, surname, shift_start, shift_end, position, stof(salary));
                employees.push_back(waiter_employee);
            break;
            case 3:
                position = "Manager";
                Manager manager_employee(name, surname, shift_start, shift_end, position, stof(salary));
                employees.push_back(manager_employee);
            break;
            default:
                break;
        }

        ofstream employees_file("employees.csv", ios::app);
        if (!employees_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        employees_file << coffee_shop_city << "," << coffee_shop_address << "," << name << "," << surname << "," << position << "," << salary << "," << shift_start << "," << shift_end << endl;
        employees_file.close();
    }

    void remove_employee(string coffee_shop_city, string coffee_shop_address) {
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


            if(coffee_shop_city == read_city && coffee_shop_address == read_address && name == read_name && surname == read_surname && position == read_position) {
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

            Position* removed_employee = nullptr;
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
                if(employee->get_name() == removed_employee->get_name() &&
                   employee->get_surname() == removed_employee->get_surname() &&
                   employee->get_position() == removed_employee->get_position()) {
                    employees.erase(employee);
                    break;
                   }
            }

            delete removed_employee;
            cout << "Coffee shop was successfully removed!" << endl << endl;
        }
        else {
            throw "The coffee shop was not found!";
        }
    }

    static bool is_salary_valid(string salary) {
        for(char& c: salary) {
            if(!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    static bool is_shift_valid(string shift) {
        if(shift.length() != 5 || shift[2] != ':') {
            return false;
        }

        int hour = stoi(shift.substr(0,2));
        int minute = stoi(shift.substr(3, 5));

        if(0 <= hour && hour <= 23 && 0 <= minute && minute <= 59) {
            return true;
        }

        return false;
    }

    static bool is_name_valid(string name) {
        for(char& c: name) {
            if(!isalpha(c)) {
                return false;
            }
        }
        return true;
    }

    ~CoffeeShopManager() = default;
};

int main()
{
    insert_employees_file();
    insert_products_file();
    insert_orders_file();
    insert_special_events_file();
    insert_reports_file();
    insert_coffee_shops_file();

    CoffeeShopManager manager;
    while (true) {
        cout << "1. Add coffee shop" << endl;
        cout << "2. Remove coffee shop" << endl;
        cout << "3. Display coffee shops" << endl;
        cout << "4. Select coffee shop" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                manager.add_coffee_shop();
                break;
            case 2:
                manager.remove_coffee_shop();
                break;
            case 3:
                manager.display_coffee_shops();
                break;
            case 4:
                try {
                    CoffeeShops* selected_shop = manager.choose_coffee_shop();
                    if (selected_shop) {
                        cout << "You selected: " << selected_shop->get_coffee_shop_city()
                             << " - " << selected_shop->get_coffee_shop_address() << endl;
                    }
                } catch (const char* message) {
                    cout << message << endl;
                }
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

