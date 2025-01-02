#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include "initialize_files.h"

using namespace std;

class CoffeeShops {
private:
    string coffee_shop_address;
    string coffee_shop_city;

public:
    string get_coffee_shop_address() {
        return coffee_shop_address;
    }

    string get_coffee_shop_city() {
        return coffee_shop_city;
    }

};


class CoffeeShopManager {
private:
    vector<CoffeeShops> coffee_shops;
protected:

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

    static int add_coffee_shop() {
        string name, city, address;

        cout << "Add coffee shop" << endl << endl;

        cout << "Enter the name of the coffee shop: ";
        getline(cin, name);

        cout << "Enter the city in which the coffee shop is located: ";
        cin >> city;

        cout << "Enter the address of the coffee shop: ";
        cin >> address;

        ofstream coffee_shops_file;
        coffee_shops_file.open("coffee_shops.csv", ios::app);
        if(!coffee_shops_file.is_open()) {
            cout<<"Error: File not opened"<<endl;
            return -1;
        }

        if(valid_city_name(city)) {
            coffee_shops_file << name << "," << city << "," << address << endl;
            coffee_shops_file.close();
        }
        else {
            throw "The entered city is not in the list of cities where we have coffee shops!";
        }
        return 1;
    }

    static int remove_coffee_shop() {
        string name, city, address;

        cout<<"Remove coffee shop"<<endl<<endl;
        cout<<"Enter the name of the coffee shop: ";
        getline(cin, name);

        cout<<"Enter the city in which the coffee shop is located: ";
        getline(cin, city);

        cout<<"Enter the address of the coffee shop: ";
        getline(cin, address);

        ifstream input_file("coffee_shops.csv");
        vector<string> lines;
        string line;
        bool coffee_shop_found = false;

        if(!input_file.is_open()) {
            cout<<"Error: File not opened"<<endl;
            return -1;
        }

        //citeste header-ul si il adauga in vector
        getline(input_file, line);
        lines.push_back(line);

        while(getline(input_file, line)) {
            stringstream ss(line);
            string read_name, read_city, read_address;

            getline(ss, read_name, ',');
            getline(ss, read_city, ',');
            getline(ss, read_address, ',');

            if(name == read_name && city == read_city && address == read_address) {
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
                cout<<"Error: File not opened"<<endl;
                return -1;
            }

            for(const string& l : lines) {
                outputFile << l << endl;
            }
            outputFile.close();
            cout << "Coffee shop was successfully removed!" << endl << endl;
        }
        else {
            throw "The coffee shop was not found!" << endl << endl;
        }
        return 1;
    }
};



int main()
{
    insert_employees_file();
    insert_products_file();
    insert_orders_file();
    insert_special_events_file();
    insert_reports_file();


    return 0;
}

