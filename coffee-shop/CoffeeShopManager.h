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


    string get_current_day() const;

    static bool valid_city_name(const string &city_name);

    void add_coffee_shop();

    void remove_coffee_shop();

    void display_coffee_shops();

    CoffeeShop *choose_coffee_shop();

    void generate_daily_reports();

    void print_daily_reports();

    void print_detailed_daily_reports();

    void get_today_date();

    void go_to_next_day();

    ~CoffeeShopManager();
};

// initialize the static member
static CoffeeShopManager *instance;

#endif //COFFEESHOPMANAGER_H
