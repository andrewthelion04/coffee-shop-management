#ifndef COFFEESHOPMANAGER_H
#define COFFEESHOPMANAGER_H

#include<iostream>
#include "CoffeeShop.h"
#include "../reports/DailyReport.h"
#include<vector>
#include<fstream>
#include<sstream>
#include <ctime>

using namespace std;

class CoffeeShopManager {
private:
    string current_date;
    vector<CoffeeShop> coffee_shops;
    vector<DailyReport> reports;
public:

    string get_current_day() const {
        return current_date;
    }

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
        string city, address, size;
        int size_choice;

        cout << "Add coffee shop" << endl;

        cout << "Enter the city in which the coffee shop is located: ";
        getline(cin, city);

        cout << "Enter the address of the coffee shop: ";
        getline(cin, address);

        cout << "Select the size of the coffee shop:\n"
             << "1.Small\n\t-> Requires at least 1 Barista, 1 Waiter and 1 Manager\n\t-> Bills: 1000-1500 RON/month"
             << "\n2.Medium\n\t-> Requires at least 2 Baristas, 2 Waiters and 1 Manager\n\t-> Bills: 1500-2000 RON/month"
             << "\n3.Large\n\t-> Requires at least 3 Baristas, 3 Waiters and 2 Managers\n\t-> Bills: 2000-2500 RON/month"
             << "Your choice: ";
        cin >> size_choice;
        cin.ignore();

        switch(size_choice) {
            case 1:
                size = "Small";
            break;
            case 2:
                size = "Medium";
            break;
            case 3:
                size = "Large";
            break;
            default:
                throw "Invalid size choice!";
        }

        if (valid_city_name(city)) {
            // Adaugă cafeneaua în vectorul intern
            CoffeeShop shop(address, city, size);
            coffee_shops.push_back(shop);

            // Append în fișierul CSV
            ofstream coffee_shops_file("coffee_shops.csv", ios::app);
            if (!coffee_shops_file.is_open()) {
                cout << "Error: File not opened" << endl;
                return;
            }

            coffee_shops_file << city << "," << address << "," << size << endl;
            coffee_shops_file.close();

            cout << "Coffee shop was successfully added!" << endl;
        } else {
            throw "The entered city is not in the list of cities where we have coffee shops!";
        }
    }

    void remove_coffee_shop() {
        string city, address;

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
            string read_city, read_address, read_size;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss, read_size, ',');

            if(city == read_city && address == read_address ) {
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

            CoffeeShop removed_coffee_shop(address, city, "");
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

    void generate_daily_reports() {
        if(coffee_shops.empty()) {
            throw "No coffee shops available!";
        }

        ofstream reports_file("reports.csv", ios::app);
        if(!reports_file.is_open()) {
            throw "Error: File not opened";
        }

        for(auto& shop : coffee_shops) {
            double total_salaries = shop.calculate_total_salaries();
            double total_bills = shop.calculate_total_bills();
            double total_sales_orders = shop.calculate_total_sales();
            double total_acquisitions = shop.calculate_total_acquisitions();
            double total_cost_special_events = shop.calculate_total_cost_special_events();
            double total_sales_special_events = shop.calculate_total_sales_special_events();

            double total_expenses = total_salaries + total_bills + total_acquisitions + total_cost_special_events;
            double total_sales = total_sales_orders + total_sales_special_events;
            double profit = total_sales - total_expenses;

            DailyReport report(shop.get_coffee_shop_city(), shop.get_coffee_shop_address(), current_date, total_expenses, total_sales, profit);
            reports.push_back(report);

            reports_file << shop.get_coffee_shop_city() << "," << shop.get_coffee_shop_address() << ","<< current_date <<"," <<
                    total_expenses << "," << total_sales << "," << profit << endl;

        }

        reports_file.close();
    }


    void get_today_date() {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int year = 1900 + ltm->tm_year;
        int month = 1 + ltm->tm_mon;
        int day = ltm->tm_mday;

        stringstream date;
        date << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;

        current_date = date.str();
    }

    void go_to_next_day() {
        int year, month, day;
        char delimiter;

        stringstream date_stream(current_date);
        date_stream >> year >> delimiter >> month >> delimiter >> day;

        // array with the number of days in each month
        int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            days_in_month[1] = 29;
        }

        // increment the day
        day++;

        // check if the day exceeds the number of days in the current month
        if (day > days_in_month[month - 1]) {
            day = 1;
            month++;
        }

        // check if the month exceeds 12
        if (month > 12) {
            month = 1;
            year++;
        }

        // update the current_date attribute
        stringstream new_date;
        new_date << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;
        current_date = new_date.str();

        for(auto& shop : coffee_shops) {
            shop.get_new_products().clear();
            shop.get_orders().clear();
            shop.get_special_events().clear();
        }

    }

    ~CoffeeShopManager() = default;
};



#endif //COFFEESHOPMANAGER_H
