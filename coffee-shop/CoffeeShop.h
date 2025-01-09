#ifndef COFFEESHOP_H
#define COFFEESHOP_H

#include<iostream>
#include "../positions/Employee.h"
#include "../positions/Barista.h"
#include "../positions/Waiter.h"
#include "../positions/Manager.h"
#include "../products/Product.h"
#include "../orders/Client.h"
#include "../orders/Order.h"
#include "../special-events/SpecialEvent.h"
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<random>

using namespace std;

//class that represents a coffee shop
class CoffeeShop {
    //encapsulation of the attributes
private:
    string coffee_shop_address; // attribute for the address of the coffee shop
    string coffee_shop_city; // attribute for the city where the coffee shop is located
    string coffee_shop_size; // attribute for the size of the coffee shop

    // using templates to avoid code duplication
    vector<Employee *> employees; // vector of objects of type Employee
    vector<Product *> all_products; // vector of objects of type Product
    vector<Product *> new_products; // vector of new products added to the coffee shop (used for the daily report)
    vector<Client *> clients; // vector of objects of type Client
    vector<Order *> orders; // vector of objects of type Order
    vector<SpecialEvent *> special_events; // vector of objects of type SpecialEvent

public:
    //constructor which initializes the coffee shop with the given address, city and size
    CoffeeShop(string coffee_shop_address, string coffee_shop_city, string coffee_shop_size);

    string get_coffee_shop_address();

    string get_coffee_shop_city();

    string get_coffee_shop_size();

    void clear_new_products();

    void clear_orders();

    void clear_special_events();

    void add_employee();

    void remove_employee();

    void add_product();

    void delete_product();

    bool check_minimum_staff_required();

    void place_order();

    void client_order(Client *client);

    void subtract_product(string product_name, int quantity);

    void add_special_event();

    void remove_special_event();

    void display_special_events();

    void display_special_event_requirements();

    void display_employees_information();

    void display_employees_shifts();

    void display_products();

    static void is_salary_valid(string salary);

    static void is_quantity_valid(string quantity);

    static void is_product_price_valid(string product_price);

    static void is_shift_valid(string shift1, string shift2);

    static bool is_name_valid(string name);

    double calculate_total_salaries();

    double calculate_total_bills();

    double calculate_total_sales();

    double calculate_total_acquisitions();

    double calculate_total_cost_special_events();

    double calculate_total_sales_special_events();

    ~CoffeeShop(); // destructor
};


#endif //COFFEESHOP_H
