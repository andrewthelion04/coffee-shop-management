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
    CoffeeShops(string coffee_shop_address, string coffee_shop_city) : CoffeeShops(coffee_shop_address, coffee_shop_city) {}

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

            CoffeeShops desired_coffee_shop(address, city);
            for(auto shop = coffee_shops.begin(); shop != coffee_shops.end(); ++shop) {
                if(shop->get_coffee_shop_address() == desired_coffee_shop.get_coffee_shop_address() &&
                   shop->get_coffee_shop_city() == desired_coffee_shop.get_coffee_shop_city()) {
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

