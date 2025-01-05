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

// singleton class that manages the coffee shops (use of a design pattern)
class CoffeeShopManager {
private:
    string current_date;
    vector<CoffeeShop> coffee_shops;
    vector<DailyReport> reports;

    // singleton instance
    static CoffeeShopManager *instance;

    // private constructor to prevent direct instantiation
    CoffeeShopManager() {
        get_today_date(); // initialize current_date with today's date
    }

public:
    // delete copy constructor and assignment operator
    CoffeeShopManager(const CoffeeShopManager &) = delete;

    CoffeeShopManager &operator=(const CoffeeShopManager &) = delete;

    // Method to get the singleton instance
    static CoffeeShopManager *getInstance() {
        if (instance == nullptr) {
            instance = new CoffeeShopManager();
        }
        return instance;
    }

    // getter for the current date
    string get_current_day() const {
        return current_date;
    }


    static bool valid_city_name(const string &city_name) {
        // metoda care verifica daca numele orasului este valid
        for (char c: city_name) {
            if (!isalpha(c) && c != ' ' && c != '-') {
                // allows just letters, spaces and hyphens
                return false; // returns false if the city name is not valid
            }
        }

        // list of cities where the coffee shops can be located
        vector<string> cities = {"Bucuresti", "Cluj-Napoca", "Timisoara", "Iasi", "Brasov"};
        for (const string &city: cities) {
            if (city_name == city) {
                return true;
            }
        }

        return false; // returns false if the city name is not in the list of cities
    }

    void add_coffee_shop() {
        // method to add a coffee shop to the list of coffee shops
        string city, address, size;
        int size_choice;

        cout << "Add coffee shop" << endl;
        // user input for the coffee shop details
        cout << "Enter the city in which the coffee shop is located: ";
        getline(cin, city);

        cout << "Enter the address of the coffee shop: ";
        getline(cin, address);

        cout << "Select the size of the coffee shop:\n"
                << "1.Small\n\t-> Requires at least 1 Barista, 1 Waiter and 1 Manager\n\t-> Bills: 1000-1500 RON/month"
                << "\n2.Medium\n\t-> Requires at least 2 Baristas, 2 Waiters and 1 Manager\n\t-> Bills: 1500-2000 RON/month"
                << "\n3.Large\n\t-> Requires at least 3 Baristas, 3 Waiters and 2 Managers\n\t-> Bills: 2000-2500 RON/month"
                << "\nYour choice: ";
        cin >> size_choice;
        cin.ignore();

        // selects the size of the coffee shop based on the user's input (the size influences the minimum number of employees required, as well
        // as the monthly bills)
        switch (size_choice) {
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

        // check if the city name is valid
        if (valid_city_name(city)) {
            // adds the coffee shop to the vector of coffee shops
            CoffeeShop shop(address, city, size);
            coffee_shops.push_back(shop);

            // adds the coffee shop to the .csv file
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
        // method to remove a coffee shop from the list of coffee shops
        string city, address;

        cout << "Remove coffee shop" << endl << endl;

        // user input for the coffee shop details
        cout << "Enter the city in which the coffee shop is located: ";
        getline(cin, city);

        cout << "Enter the address of the coffee shop: ";
        getline(cin, address);

        ifstream input_file("coffee_shops.csv");
        vector<string> lines;
        string line;
        bool coffee_shop_found = false;

        if (!input_file.is_open()) {
            throw "Error: File not opened";
        }

        // read the coffee shops from the .csv file and check if the coffee shop exists
        getline(input_file, line);
        lines.push_back(line);

        while (getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address, read_size;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss, read_size, ',');

            if (city == read_city && address == read_address) {
                coffee_shop_found = true;
            } else {
                lines.push_back(line);
            }
        }
        input_file.close();

        // if the coffee shop is found, remove it from the .csv file
        if (coffee_shop_found) {
            ofstream outputFile("coffee_shops.csv");
            if (!outputFile.is_open()) {
                throw "Error: File not opened";
            }

            for (const string &l: lines) {
                outputFile << l << endl;
            }
            outputFile.close();

            // remove the coffee shop from the vector of coffee shops
            CoffeeShop removed_coffee_shop(address, city, "");
            for (auto shop = coffee_shops.begin(); shop != coffee_shops.end(); ++shop) {
                if (shop->get_coffee_shop_address() == removed_coffee_shop.get_coffee_shop_address() &&
                    shop->get_coffee_shop_city() == removed_coffee_shop.get_coffee_shop_city()) {
                    coffee_shops.erase(shop);
                    break;
                }
            }

            cout << "Coffee shop was successfully removed!" << endl << endl;
        } else {
            throw "The coffee shop was not found!";
        }
    }

    void display_coffee_shops() {
        // method to display the list of coffee shops
        if (coffee_shops.size() == 0) {
            throw "No coffee shops available!\n";
        }

        cout << "List of all the coffee shops:" << endl;
        for (int i = 0; i < coffee_shops.size(); ++i) {
            cout << i + 1 << ". " << coffee_shops[i].get_coffee_shop_city()
                    << " - " << coffee_shops[i].get_coffee_shop_address() << endl;
        }
        cout << endl;
    }

    CoffeeShop *choose_coffee_shop() {
        // method to choose a coffee shop in order to manage it (add employees, products, take orders, etc.)
        if (coffee_shops.empty()) {
            // if there are no coffee shops available, throw an exception
            throw "No coffee shops available!\n";
        }

        cout << "Select a coffee shop:" << endl;
        display_coffee_shops();

        int choice;
        cout << "Your choice: ";
        cin >> choice;

        if (choice < 1 || choice > coffee_shops.size()) {
            throw "Invalid choice!";
        }

        return &coffee_shops[choice - 1];
    }

    void generate_daily_reports() {
        // method to generate daily reports for all coffee shops
        if (coffee_shops.empty()) {
            throw "No coffee shops available!\n";
        }

        ofstream reports_file("reports.csv", ios::app);
        if (!reports_file.is_open()) {
            throw "Error: File not opened";
        }

        // generate daily reports for all coffee shops
        for (auto &shop: coffee_shops) {
            double total_salaries = shop.calculate_total_salaries();
            double total_bills = shop.calculate_total_bills();
            double total_sales_orders = shop.calculate_total_sales();
            double total_acquisitions = shop.calculate_total_acquisitions();
            double total_cost_special_events = shop.calculate_total_cost_special_events();
            double total_sales_special_events = shop.calculate_total_sales_special_events();

            // calculate the total expenses, total sales and profit
            double total_expenses = total_salaries + total_bills + total_acquisitions + total_cost_special_events;
            double total_sales = total_sales_orders + total_sales_special_events;
            double profit = total_sales - total_expenses;

            // create a daily report object and add it to the vector of reports
            DailyReport report(shop.get_coffee_shop_city(), shop.get_coffee_shop_address(), current_date,
                               total_salaries, total_bills, total_sales_orders, total_acquisitions,
                               total_cost_special_events,
                               total_sales_special_events, total_expenses, total_sales, profit);
            reports.push_back(report);

            // append the daily report to the .csv file
            reports_file << shop.get_coffee_shop_city() << "," << shop.get_coffee_shop_address() << "," << current_date
                    << "," <<
                    total_expenses << "," << total_sales << "," << profit << endl;
        }
        cout << "Daily report/s were successfully generated!" << endl;

        reports_file.close();
    }

    void print_daily_reports() {
        // method to print the daily reports for a particular coffee shops
        if (coffee_shops.empty()) {
            throw "No coffee shops available!\n";
        }

        int coffee_shop_index = 0;
        int choice;

        // user input for the coffee shop to display the daily reports for
        cout << "Select the coffee shop you wish to see the report/s for!" << endl;
        for (auto &shop: coffee_shops) {
            cout << ++coffee_shop_index << ". " << shop.get_coffee_shop_city() << " - " << shop.
                    get_coffee_shop_address() << endl;
        }
        cout << "\nYour choice: ";
        cin >> choice;
        cin.ignore();

        if (choice < 1 || choice > coffee_shops.size()) {
            throw "Invalid choice!";
        }

        CoffeeShop shop = coffee_shops[choice - 1];

        // display the daily reports for the selected coffee shop
        cout << "Daily reports for the coffee shop located in " << shop.get_coffee_shop_city() << " - " << shop.
                get_coffee_shop_address() << endl;
        for (auto &report: reports) {
            if (report.get_coffee_shop_city() == shop.get_coffee_shop_city() && report.get_coffee_shop_address() == shop
                .get_coffee_shop_address()) {
                cout << "Date : " << current_date << endl;
                cout << "Total expenses: " << report.get_total_expenses() << " RON" << endl;
                cout << "Total sales: " << report.get_total_sales() << " RON" << endl;
                cout << "Profit: " << report.get_profit() << " RON" << endl << endl;
            }
        }
    }

    void print_detailed_daily_reports() {
        // method to print the detailed daily reports for a particular coffee shop
        if (coffee_shops.empty()) {
            throw "No coffee shops available!\n";
        }

        int coffee_shop_index = 0;
        int choice;

        // user input for the coffee shop to display the detailed daily reports for
        cout << "Select the coffee shop you wish to see the detailed report/s for!" << endl;
        for (auto &shop: coffee_shops) {
            cout << ++coffee_shop_index << ". " << shop.get_coffee_shop_city() << " - " << shop.
                    get_coffee_shop_address() << endl;
        }
        cout << "\nYour choice: ";
        cin >> choice;
        cin.ignore();

        if (choice < 1 || choice > coffee_shops.size()) {
            throw "Invalid choice!";
        }

        CoffeeShop shop = coffee_shops[choice - 1];

        // display the detailed daily reports for the selected coffee shop
        cout << "Daily detailed reports for the coffee shop located in " << shop.get_coffee_shop_city() << " - " << shop
                .get_coffee_shop_address() << endl;
        for (auto &report: reports) {
            if (report.get_coffee_shop_city() == shop.get_coffee_shop_city() && report.get_coffee_shop_address() == shop
                .get_coffee_shop_address()) {
                cout << "Date : " << current_date << endl;
                cout << "Total salaries: " << report.get_total_salaries() << " RON" << endl;
                cout << "Total bills: " << report.get_total_bills() << " RON" << endl;
                cout << "Total sales orders: " << report.get_total_sales_orders() << " RON" << endl;
                cout << "Total acquisitions: " << report.get_total_acquisitions() << " RON" << endl;
                cout << "Total cost special events: " << report.get_total_cost_special_events() << " RON" << endl;
                cout << "Total sales special events: " << report.get_total_sales_special_events() << " RON" << endl <<
                        endl;;

                // calculate the total expenses, total sales and profit
                cout <<
                        "Total expenses: Total salaries + Total bills + Total acquisitions + Total cost special events = "
                        << report.get_total_salaries() << " + " <<
                        report.get_total_bills() << " + " << report.get_total_acquisitions() << " + " << report.
                        get_total_cost_special_events() << " = " << report.get_total_expenses() << " RON" << endl;
                cout << "Total sales: Total sales orders + Total sales special events = " << report.
                        get_total_sales_orders() << " + " << report.get_total_sales_special_events() << " = " << report.
                        get_total_sales() << " RON" << endl;
                cout << "Profit: Total sales - Total expenses =  " << report.get_profit() << " RON" << endl << endl;
            }
        }
    }


    void get_today_date() {
        // method to get the current date
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
        // method to go to the next day
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

        // remove the products, the orders and the special events added the previous day
        for (auto &shop: coffee_shops) {
            shop.clear_new_products();
            shop.clear_orders();
            shop.clear_special_events();
        }
    }

    ~CoffeeShopManager() = default;
};

// initialize the static member
CoffeeShopManager *CoffeeShopManager::instance = nullptr;


#endif //COFFEESHOPMANAGER_H
