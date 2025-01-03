#ifndef COFFEESHOPMANAGER_H
#define COFFEESHOPMANAGER_H

#include<iostream>
#include "CoffeeShop.h"
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

class CoffeeShopManager {
private:
    vector<CoffeeShop> coffee_shops;
public:

    static bool valid_city_name(const string &city_name) {
        for (char c : city_name) {
            if (!isalpha(c) && c != ' ' && c != '-') { // permite doar litere, spatii si cratime
                return false; // daca se gaseste un caracter invalid, returneaza false
            }
        }

        vector<string> cities = {"Bucuresti", "Cluj-Napoca", "Timisoara", "Iasi",  "Brasov"};
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
            CoffeeShop shop(address, city);
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

            CoffeeShop removed_coffee_shop(address, city);
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
        if(coffee_shops.size() == 0) {
            throw "No coffee shops available!";
        }

        cout << "List of all the coffee shops:" << endl;
        for (int i = 0; i < coffee_shops.size(); ++i) {
            cout << i + 1 << ". " << coffee_shops[i].get_coffee_shop_city()
                 << " - " << coffee_shops[i].get_coffee_shop_address() << endl;
        }
        cout << endl;
    }

    CoffeeShop* choose_coffee_shop() {
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



    ~CoffeeShopManager() = default;
};



#endif //COFFEESHOPMANAGER_H
