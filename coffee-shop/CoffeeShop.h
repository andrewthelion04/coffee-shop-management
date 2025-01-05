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
    CoffeeShop(string coffee_shop_address, string coffee_shop_city, string coffee_shop_size) : coffee_shop_address(
        coffee_shop_address), coffee_shop_city(coffee_shop_city), coffee_shop_size(coffee_shop_size) {
    }


    // getters for the coffee shop address, city and size
    string get_coffee_shop_address() {
        return coffee_shop_address;
    }

    string get_coffee_shop_city() {
        return coffee_shop_city;
    }

    string get_coffee_shop_size() {
        return coffee_shop_size;
    }

    // method to clear the new products vector
    void clear_new_products() {
        new_products.clear();
    }

    // method to clear the orders vector
    void clear_orders() {
        orders.clear();
    }

    // method to clear the special events vector
    void clear_special_events() {
        special_events.clear();
    }

    //methods to add, remove and get employees, products, orders and special events

    void add_employee() {
        // method to add an employee to the coffee shop (in the .csv file and in the vector)
        string name, surname, position, salary, shift_start, shift_end;
        int position_choice;

        // user input for the employee details
        cout << "Adding an employee to the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address
                << "!" << endl;
        cout << "Enter the name of the employee: ";
        getline(cin, name);
        if (!is_name_valid(name)) {
            throw "Invalid name!";
        }

        cout << "Enter the surname of the employee: ";
        getline(cin, surname);
        if (!is_name_valid(surname)) {
            throw "Invalid surname!";
        }

        cout << "Select the position they will hold!\n" <<
                "1.Barista\n" << "2.Waiter\n" << "3.Manager\n";
        cout << "Your choice: ";
        cin >> position_choice;
        cin.ignore();
        if (position_choice < 1 || position_choice > 3) {
            throw "Invalid choice!";
        } else {
            if (position_choice == 1) {
                position = "Barista";
            } else if (position_choice == 2) {
                position = "Waiter";
            } else {
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

        // check if the shift is valid
        is_shift_valid(shift_start, shift_end);

        // add the employee to the vector of all employees
        Employee *employee = nullptr;
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

        // append the employee to the .csv file
        ofstream employees_file("employees.csv", ios::app);
        if (!employees_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        employees_file << coffee_shop_city << "," << coffee_shop_address << "," << name << "," << surname << "," <<
                position << "," << salary << "," << shift_start << "," << shift_end << endl;
        employees_file.close();

        cout << "The employee was successfully added!" << endl << endl;
    }

    void remove_employee() {
        // method to remove an employee from the coffee shop (from the .csv file and from the vector)
        if (employees.empty()) {
            // check if there are employees in the coffee shop
            throw "There are no employees!\n";
        }

        // user input for the employee details
        string name, surname, position;
        cout << "Removing an employee from the coffee shop located in " << coffee_shop_city << " - " <<
                coffee_shop_address << "!" << endl;

        cout << "Enter the name of the employee: ";
        getline(cin, name);

        cout << "Enter the surname of the employee: ";
        getline(cin, surname);

        cout << "Enter the position of the employee: ";
        getline(cin, position);

        // read the employees from the .csv file and check if the employee exists
        ifstream input_file("employees.csv");
        vector<string> lines;
        string line;
        bool employee_found = false;

        if (!input_file.is_open()) {
            throw "Error: File not opened";
        }

        // read the header and add it to the vector
        getline(input_file, line);
        lines.push_back(line);

        while (getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address, read_name, read_surname, read_position, read_salary, read_shift_start,
                    read_shift_end;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss, read_name, ',');
            getline(ss, read_surname, ',');
            getline(ss, read_position, ',');
            getline(ss, read_salary, ',');
            getline(ss, read_shift_start, ',');
            getline(ss, read_shift_end, ',');

            // if the employee is found, set the flag to true
            if (name == read_name && surname == read_surname && position == read_position) {
                employee_found = true;
            } else {
                lines.push_back(line);
            }
        }
        input_file.close();

        // if the employee is found, remove it from the .csv file and from the vector
        if (employee_found) {
            ofstream outputFile("employees.csv");
            if (!outputFile.is_open()) {
                throw "Error: File not opened";
            }

            for (const string &l: lines) {
                outputFile << l << endl;
            }
            outputFile.close();

            Employee *removed_employee = nullptr;
            if (position == "Barista") {
                removed_employee = new Barista(name, surname, "", "", position, 0);
            } else if (position == "Waiter") {
                removed_employee = new Waiter(name, surname, "", "", position, 0);
            } else if (position == "Manager") {
                removed_employee = new Manager(name, surname, "", "", position, 0);
            }

            for (auto employee = employees.begin(); employee != employees.end(); ++employee) {
                if ((*employee)->get_name() == removed_employee->get_name() &&
                    (*employee)->get_surname() == removed_employee->get_surname() &&
                    (*employee)->get_position() == removed_employee->get_position()) {
                    employees.erase(employee);
                    break;
                }
            }

            delete removed_employee;
            cout << "The employee was successfully removed!" << endl << endl;
        } else {
            throw "The employee was not found!";
        }
    }

    void add_product() {
        // method to add a product to the coffee shop (in the .csv file and in the vector)
        string product_name, type, purchase_price, sale_price, quantity;
        int type_choice;

        // user input for the product details
        cout << "Adding a product to the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address <<
                "!" << endl;
        cout << "Select the type of product you wish to add!\n" <<
                "1.Coffee\n" << "2.Beverage\n" << "3.Desert\n";
        cout << "Your choice: ";
        cin >> type_choice;
        cin.ignore();


        if (type_choice < 1 || type_choice > 3) {
            throw "Invalid choice!";
        } else {
            if (type_choice == 1) {
                type = "Coffee";
            } else if (type_choice == 2) {
                type = "Beverage";
            } else {
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

        // add the product to the vector of all products and to the vector of new products
        all_products.push_back(new Product(product_name, type, stof(purchase_price), stof(sale_price), stoi(quantity)));
        new_products.push_back(new Product(product_name, type, stof(purchase_price), stof(sale_price), stoi(quantity)));


        // append the product to the .csv file
        ofstream products_file("products.csv", ios::app);
        if (!products_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        products_file << coffee_shop_city << "," << coffee_shop_address << "," << product_name << "," << type << "," <<
                purchase_price << "," << sale_price << "," << quantity << endl;
        products_file.close();

        cout << "Product added successfully!" << endl << endl;
    }

    void delete_product() {
        // method to remove a product from the coffee shop (from the .csv file and from the vector)
        if (all_products.empty()) {
            // check if there are products in the coffee shop
            throw "There are no products!\n";
        }

        string product_name, type;
        int type_choice;
        cout << "Removing a product from the coffee shop located in " << coffee_shop_city << " - " <<
                coffee_shop_address << "!" << endl;
        // user input for the product details
        cout << "Select the type of product you wish to remove:\n" <<
                "1.Coffee\n" << "2.Beverage\n" << "3.Desert\n";
        cin >> type_choice;
        cin.ignore();

        if (type_choice < 1 || type_choice > 3) {
            throw "Invalid choice!";
        } else {
            if (type_choice == 1) {
                type = "Coffee";
            } else if (type_choice == 2) {
                type = "Beverage";
            } else {
                type = "Desert";
            }
        }

        cout << "Enter the name of the product: ";
        getline(cin, product_name);
        // read the products from the .csv file and check if the product exists
        ifstream input_file("products.csv");
        vector<string> lines;
        string line;
        bool product_found = false;

        if (!input_file.is_open()) {
            throw "Error: File not opened";
        }

        getline(input_file, line);
        lines.push_back(line);


        while (getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address, read_product_name, read_type, read_purchase_price, read_sale_price,
                    read_quantity;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss, read_product_name, ',');
            getline(ss, read_type, ',');
            getline(ss, read_purchase_price, ',');
            getline(ss, read_sale_price, ',');
            getline(ss, read_quantity, ',');

            if (product_name == read_product_name && type == read_type) {
                product_found = true;
            } else {
                lines.push_back(line);
            }
        }
        input_file.close();
        // if the product is found, remove it from the .csv file and from the vector
        if (product_found) {
            ofstream output_file("products.csv");
            if (!output_file.is_open()) {
                throw "Error: File not opened";
            }

            for (const string &l: lines) {
                output_file << l << endl;
            }
            output_file.close();

            Product *removed_product = new Product(product_name, type, 0, 0, 0);
            for (auto product = all_products.begin(); product != all_products.end(); ++product) {
                if ((*product)->get_name() == removed_product->get_name() &&
                    (*product)->get_type() == removed_product->get_type()) {
                    all_products.erase(product);
                    break;
                }
            }

            for (auto product = new_products.begin(); product != new_products.end(); ++product) {
                if ((*product)->get_name() == removed_product->get_name() &&
                    (*product)->get_type() == removed_product->get_type()) {
                    new_products.erase(product);
                    break;
                }
            }


            delete removed_product;
            cout << "The product was successfully removed!" << endl << endl;
        } else {
            throw "The product was not found!";
        }
    }

    // method to add a special event to the coffee shop (in the .csv file and in the vector)
    bool check_minimum_staff_required() {
        // method to check if the coffee shop has the minimum staff required to place an order
        int barista_count = 0, waiter_count = 0, manager_count = 0;

        for (auto *employee: employees) {
            if (employee->get_position() == "Barista") {
                barista_count++;
            }
            if (employee->get_position() == "Waiter") {
                waiter_count++;
            }
            if (employee->get_position() == "Manager") {
                manager_count++;
            }
        }

        if (coffee_shop_size == "Small") {
            if (barista_count < 1 || waiter_count < 1 || manager_count < 1) {
                return false;
            }
        }
        if (coffee_shop_size == "Medium") {
            if (barista_count < 2 || waiter_count < 2 || manager_count < 2) {
                return false;
            }
        }
        if (coffee_shop_size == "Large") {
            if (barista_count < 3 || waiter_count < 3 || manager_count < 2) {
                return false;
            }
        }

        return true;
    }

    void place_order() {
        // method to place an order at the coffee shop
        if (all_products.empty()) {
            // check if there are available products to be bought in the coffee shop
            throw "The coffee shop located in " + coffee_shop_city + " - " + coffee_shop_address +
                  " has no products available!\n";
        }

        if (!check_minimum_staff_required()) {
            // check if the coffee shop has the minimum staff required to place an order
            throw "The coffee shop located in " + coffee_shop_city + " - " + coffee_shop_address +
                  " does not have enough staff to place an order!\n";
        }

        // user input for the client's full name
        string client_name;
        cout << "Order placement!" << endl;
        cout << "Insert the client's full name: ";
        getline(cin, client_name);

        // check if the client already exists in the vector of clients
        Client *client = nullptr;
        for (auto *c: clients) {
            if (c->get_name() == client_name) {
                client = c;
                break;
            }
        }

        // if the client does not exist, create a new client and add it to the vector of clients
        if (!client) {
            client = new Client(client_name);
            clients.push_back(client);
        }
        // call the client_order method
        client_order(client);
    }

    void client_order(Client *client) {
        // auxiliary method that places the order for the specified client
        Order *order = new Order();
        string response = "no";

        // user input for the products to be bought
        do {
            bool has_coffee = false, has_beverages = false, has_deserts = false;
            string product_name;
            int quantity;

            // check if the coffee shop has coffees, beverages and deserts
            for (auto *product: all_products) {
                if (product->get_type() == "Coffee") {
                    has_coffee = true;
                }
                if (product->get_type() == "Beverage") {
                    has_beverages = true;
                }
                if (product->get_type() == "Desert") {
                    has_deserts = true;
                }
            }

            cout << "Available products to be bought at our coffee shop!" << endl;
            // display the available products to be bought
            if (has_coffee) {
                cout << "Coffees: " << endl;
                for (auto *product: all_products) {
                    if (product->get_type() == "Coffee") {
                        cout << product->get_name() << " - " << product->get_sale_price() << " RON" << endl;
                    }
                }
            }

            if (has_beverages) {
                cout << "Beverages: " << endl;
                for (auto *product: all_products) {
                    if (product->get_type() == "Beverage") {
                        cout << product->get_name() << " - " << product->get_sale_price() << " RON" << endl;
                    }
                }
            }

            if (has_deserts) {
                cout << "Deserts: " << endl;
                for (auto *product: all_products) {
                    if (product->get_type() == "Desert") {
                        cout << product->get_name() << " - " << product->get_sale_price() << " RON" << endl;
                    }
                }
            }

            cout << endl << "Insert the name of the product you wish to buy: ";
            getline(cin, product_name);

            cout << "Insert the quantity: ";
            cin >> quantity;
            cin.ignore();
            if (cin.fail() || quantity <= 0) {
                throw "Cantitate invalida";
            }

            // check if the product exists and if there is enough quantity
            try {
                // call the subtract_product method
                subtract_product(product_name, quantity);
            } catch (const char *msg) {
                cout << msg << endl;
                delete order;
                return;
            }

            // add the product to the order
            for (auto product = all_products.begin(); product != all_products.end(); ++product) {
                if ((*product)->get_name() == product_name) {
                    order->add_product(product_name, quantity, (*product)->get_sale_price());
                    cout << quantity << " " << product_name << " added to the order!" << endl;
                    break;
                }
            }
            do {
                cout << "Do you wish to order more products? (yes/no): ";
                getline(cin, response);
            } while (response != "yes" && response != "no");
        } while (response == "yes");

        // calculate the total price of the order
        order->calculate_total_price();

        // check if the client has placed at least 5 orders and if so, apply a 10% discount (fidelity system)
        if ((client->get_number_of_orders() + 1) % 5 == 0) {
            cout << client->get_name() << " has received a 10% discount for being a loyal customer!" << endl;
            order->set_total_price(order->get_total_price() * 0.9);
        }

        // add the order to the vector of coffee shop orders (used for daily report) and to the client's vector of orders
        orders.push_back(order);
        client->add_order(order);

        string ordered_products;
        // write the order to the .csv file
        for (const auto &product: order->get_ordered_products()) {
            ordered_products += to_string(product->get_quantity()) + " " + product->get_product_name();
            if (&product != &order->get_ordered_products().back()) {
                ordered_products += ";";
            }
        }

        ofstream orders_file("orders.csv", ios::app);
        if (!orders_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        orders_file << coffee_shop_city << "," << coffee_shop_address << "," << client->get_name() << "," <<
                ordered_products << "," << order->get_total_price() << endl;
        orders_file.close();

        cout << "Order has been placed! The total price is: " << order->get_total_price() << " RON" << endl << endl;

        delete order;
    }

    void subtract_product(string product_name, int quantity) {
        // auxiliary method used to subtract a product from the coffee shop (from the .csv file and from the vector)
        // check if the product exists and if there is enough quantity
        for (auto product = all_products.begin(); product != all_products.end(); ++product) {
            if ((*product)->get_name() == product_name) {
                // if the product exists and there is enough quantity, subtract the quantity
                if ((*product)->get_quantity() >= quantity) {
                    (*product)->set_quantity((*product)->get_quantity() - quantity);

                    ifstream input_file("products.csv");
                    vector<string> lines;
                    string line;

                    if (!input_file.is_open()) {
                        throw "Error: File not opened";
                    }

                    getline(input_file, line);
                    lines.push_back(line);

                    while (getline(input_file, line)) {
                        stringstream ss(line);
                        string read_city, read_address, read_product_name, read_type, read_purchase_price,
                                read_sale_price, read_quantity;
                        getline(ss, read_city, ',');
                        getline(ss, read_address, ',');
                        getline(ss, read_product_name, ',');
                        getline(ss, read_type, ',');
                        getline(ss, read_purchase_price, ',');
                        getline(ss, read_sale_price, ',');
                        getline(ss, read_quantity, ',');

                        if (product_name == read_product_name) {
                            lines.push_back(
                                coffee_shop_city + "," + coffee_shop_address + "," + product_name + "," + read_type +
                                "," + read_purchase_price + "," + read_sale_price + "," + to_string(
                                    stoi(read_quantity) - quantity));
                        } else {
                            lines.push_back(line);
                        }
                    }

                    input_file.close();

                    ofstream output_file("products.csv");
                    if (!output_file.is_open()) {
                        throw "Error: File not opened";
                    }

                    for (const string &l: lines) {
                        output_file << l << endl;
                    }

                    output_file.close();

                    if ((*product)->get_quantity() == 0) {
                        all_products.erase(product);
                    }

                    return;
                } else {
                    throw "Insufficient quantity!\n";
                }
            }
        }
        throw "Product not found!\n";
    }

    void add_special_event() {
        // method to add a special event to the coffee shop (in the .csv file and in the vector)
        string name, description, start_time, product_name, type, cost, quantity;
        int type_choice;
        string response;

        cout << "Adding a special event to the coffee shop located in " << coffee_shop_city << " - " <<
                coffee_shop_address << "!" << endl;
        cout << "Enter the name of the special event: ";
        getline(cin, name);

        cout << "Enter the description of the special event: ";
        getline(cin, description);

        cout << "Specify the start time of the event (HH:MM): ";
        getline(cin, start_time);

        // create a new special event object
        SpecialEvent *special_event = new SpecialEvent(name, description, start_time);

        // user input for the requirements of the special event
        do {
            cout << "Select the type of requirements for the event:\n"
                    << "1. Food and beverages\n"
                    << "2. Service personnel\n"
                    << "3. Decorative elements\n";
            cout << "Your choice: ";
            cin >> type_choice;
            cin.ignore();

            switch (type_choice) {
                case 1:
                    type = "Food and beverages";
                    cout << "Enter the name of the product: ";
                    getline(cin, product_name);

                    cout << "Enter the quantity: ";
                    getline(cin, quantity);

                    cout << "Enter the price per item: ";
                    getline(cin, cost);
                    break;
                case 2:
                    int personnel_choice;
                    type = "Service personnel";
                    quantity = '1';
                    cout << "Select what type of additional service personnel you need for the event!\n"
                            << "1.DJ\n"
                            << "2.Entertainer\n"
                            << "3.Photographer\n"
                            << "4.Security Personnel\n"
                            << "5.Event coordinator\n"
                            << "Your choice: ";
                    cin >> personnel_choice;
                    cin.ignore();

                    switch (personnel_choice) {
                        case 1:
                            product_name = "DJ";
                            break;
                        case 2:
                            product_name = "Entertainer";
                            break;
                        case 3:
                            product_name = "Photographer";
                            break;
                        case 4:
                            product_name = "Security Personnel";
                            break;
                        case 5:
                            product_name = "Event coordinator";
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                            break;
                    }

                    cout << "Enter an estimated cost for the service: ";
                    getline(cin, cost);

                    break;
                case 3:
                    int decorative_choice;
                    type = "Decorative elements";
                    cout << "Select what type of decorative elements you need for the event!\n"
                            << "1.Balloons\n"
                            << "2.Flower arrangements\n"
                            << "3.Table centerpieces\n"
                            << "4.Candles\n"
                            << "5.Banners\n"
                            << "Your choice: ";
                    cin >> decorative_choice;
                    cin.ignore();

                    switch (decorative_choice) {
                        case 1:
                            product_name = "Balloon";
                            break;
                        case 2:
                            product_name = "Flower arrangement";
                            break;
                        case 3:
                            product_name = "Table centerpiece";
                            break;
                        case 4:
                            product_name = "Candle";
                            break;
                        case 5:
                            product_name = "Banner";
                            break;
                        default:
                            cout << "Invalid choice!";
                            break;
                    }

                    cout << "Enter the quantity: ";
                    getline(cin, quantity);

                    cout << "Enter the price per item: ";
                    getline(cin, cost);
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
            // add the required product to the special event's vector of required products
            special_event->add_required_product(product_name, type, stof(cost), stoi(quantity));

            do {
                cout << "Do you wish to add more requirements for the event? (yes/no): ";
                getline(cin, response);
            } while (response != "yes" && response != "no");
        } while (response == "yes");

        // calculate the total costs of the special event
        special_event->calculate_total_costs();
        // add the special event to the vector of special events
        special_events.push_back(special_event);

        // append the special event to the .csv file
        ofstream special_events_file("special_events.csv", ios::app);
        if (!special_events_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        special_events_file << coffee_shop_city << "," << coffee_shop_address << "," << name << "," << description <<
                start_time <<
                "," << special_event->get_total_costs() << endl;
        special_events_file.close();

        cout << "The special event was successfully added!" << endl << endl;
    }

    void remove_special_event() {
        // check if there are special events booked for today
        if (special_events.empty()) {
            throw "There are no special events booked for today!\n";
        }

        // user input for the special event to be removed
        cout << "Select the special event you wish to remove!" << endl;
        int events_index = 0;
        int events_choice;
        for (auto *special_event: special_events) {
            cout << ++events_index << ". " << special_event->get_name();
        }
        cout << "Your choice: ";
        cin >> events_choice;
        cin.ignore();

        if (events_choice < 1 || events_choice > 2) {
            throw "Invalid choice!";
        }

        SpecialEvent *chosen_event = special_events[events_choice - 1];
        // remove the special event from the vector of special events
        for (auto event = special_events.begin(); event != special_events.end(); ++event) {
            if ((*event)->get_name() == chosen_event->get_name()) {
                special_events.erase(event);
                break;
            }
        }

        // remove the special event from the .csv file
        ifstream input_file("special_events.csv");
        vector<string> lines;
        string line;

        getline(input_file, line);
        lines.push_back(line);

        while (getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address, read_event_name, read_event_description, read_event_start_time, read_costs;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss, read_event_name, ',');
            getline(ss, read_event_description, ',');
            getline(ss, read_event_start_time, ',');
            getline(ss, read_costs, ',');
            if (chosen_event->get_name() != read_event_name) {
                lines.push_back(line);
            }
        }
        input_file.close();

        ofstream output_file("special_events.csv");
        if (!output_file.is_open()) {
            throw "Error: File not opened";
        }

        for (const string &l: lines) {
            output_file << l << endl;
        }

        cout << "Special event removed!" << endl << endl;
        output_file.close();
    }

    void display_special_events() {
        // method to display the special events booked at the coffee shop
        if (special_events.empty()) {
            throw "There are no special events booked at the coffee shop located in " + coffee_shop_city + " - " +
                  coffee_shop_address + "!" + "\n";
        }
        int special_event_index = 0;
        cout << "Special event/s at the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address <<
                ":" << endl;
        for (auto *special_event: special_events) {
            cout << ++special_event_index << "." << special_event->get_name() << endl;
            cout << "\t->Description: " << special_event->get_description() << endl;
            cout << "\t->Estimated costs: " << special_event->get_total_costs() << "RON" << endl;
        }
    }

    void display_special_event_requirements() {
        // method to display the requirements for a special event
        if (special_events.empty()) {
            throw "There are no special events booked at the coffee shop located in" + coffee_shop_city + " - " +
                  coffee_shop_address + "!" + "\n";
        }

        int special_event_index = 0;
        int special_event_choice;

        cout << "Select the special event you wish to see the requirements for!" << endl;
        for (auto *special_event: special_events) {
            cout << ++special_event_index << "." << special_event->get_name() << endl;
        }
        cout << "Your choice: ";
        cin >> special_event_choice;
        cin.ignore();

        SpecialEvent *event = special_events[special_event_choice - 1];

        bool has_food_and_beverages = false, has_service_personnel = false, has_decorative_elements = false;
        for (auto *required_product: event->get_required_products()) {
            if (required_product->get_type() == "Food and beverages") {
                has_food_and_beverages = true;
            }
            if (required_product->get_type() == "Service personnel") {
                has_service_personnel = true;
            }
            if (required_product->get_type() == "Decorative elements") {
                has_decorative_elements = true;
            }
        }

        cout << "Requirements for the special event " << event->get_name() << ":" << endl;
        if (has_food_and_beverages) {
            cout << "Food and beverages: " << endl;
            for (auto *required_product: event->get_required_products()) {
                if (required_product->get_type() == "Food and beverages") {
                    cout << "\t->" << required_product->get_product_name() << " - " << required_product->get_quantity()
                            << " - " << required_product->get_cost() << " RON" << endl;
                }
            }
        }

        if (has_service_personnel) {
            cout << "Service personnel: " << endl;
            for (auto *required_product: event->get_required_products()) {
                if (required_product->get_type() == "Service personnel") {
                    cout << required_product->get_product_name() << " - " << required_product->get_cost() << " RON" <<
                            endl;
                }
            }
        }

        if (has_decorative_elements) {
            cout << "Decorative elements: " << endl;
            for (auto *required_product: event->get_required_products()) {
                if (required_product->get_type() == "Decorative elements") {
                    cout << required_product->get_product_name() << " - " << required_product->get_quantity() << " - "
                            << required_product->get_cost() << " RON" << endl;
                }
            }
        }

        // display the total costs of the special event
        cout << "Total costs: " << event->get_total_costs() << " RON" << endl << endl;
    }


    void display_employees_information() {
        // method to display the information regarding the employees at the coffee shop
        int index = 0;

        if (employees.size() == 0) {
            // check if there are employees in the coffee shop
            throw "There are no employees at the coffee shop located in " + coffee_shop_city + " - " +
                  coffee_shop_address + "!";
        }

        // display the information regarding the employees
        cout << "Information regarding the employees at the coffee shop located in " << coffee_shop_city << " - " <<
                coffee_shop_address << ":" << endl;
        for (auto &employee: employees) {
            cout << "Employee " << ++index << ": " << employee->get_name() << " " << employee->get_surname() << endl;
            cout << "\t->Position: " << employee->get_position() << endl;
            cout << "\t->Salary: " << employee->get_salary() << "RON" << endl;
            cout << "\t->Shift: " << employee->get_start_shift() << " - " << employee->get_end_shift() << endl;
            cout << endl;
        }
    }

    void display_employees_shifts() {
        // method to display the shifts of the employees at the coffee shop
        if (employees.size() == 0) {
            // check if there are employees in the coffee shop
            throw "There are no employees at the coffee shop located in " + coffee_shop_city + " - " +
                  coffee_shop_address + "!";
        }

        // display the shifts of the employees
        cout << "List of all the employees and their shifts at the coffee shop located in " << coffee_shop_city << " - "
                << coffee_shop_address << ":" << endl;
        for (auto &employee: employees) {
            cout << employee->get_name() << " " << employee->get_surname() << " -> " << employee->get_start_shift() <<
                    " - " << employee->get_end_shift() << endl;
            if (employee == employees.back()) {
                cout << endl;
            }
        }
    }

    void display_products() {
        // method to display the products available at the coffee shop
        if (all_products.empty()) {
            // check if there are products available at the coffee shop
            throw "There are no products available at the coffee shop located in " + coffee_shop_city + " - " +
                  coffee_shop_address + "!\n";
        }
        int index = 0;
        cout << "List of all the products available at the coffee shop located in " << coffee_shop_city << " - " <<
                coffee_shop_address << ":" << endl;
        for (auto product = all_products.begin(); product != all_products.end(); ++product) {
            cout << ++index << ". " << (*product)->get_name() << " - " << (*product)->get_type() << " - " << (*product)
                    ->get_sale_price() << " RON" << endl;
        }
        cout << endl;
    }

    static void is_salary_valid(string salary) {
        // method to check if the salary is valid
        for (char &c: salary) {
            if (!isdigit(c)) {
                throw "Invalid salary! Please use only digits!";
            }
        }
    }

    static void is_shift_valid(string shift1, string shift2) {
        // method to check if the shift is valid
        if ((shift1.length() != 5 || shift1[2] != ':') || (shift2.length() != 5 || shift2[2] != ':')) {
            throw "Invalid shift format! Please use HH:MM!";
        }

        int hour_shift1 = stoi(shift1.substr(0, 2));
        int hour_shift2 = stoi(shift2.substr(0, 2));

        int minute_shift1 = stoi(shift1.substr(3, 5));
        int minute_shift2 = stoi(shift2.substr(3, 5));


        if ((0 <= hour_shift1 && hour_shift1 <= 23 && 0 <= minute_shift1 && minute_shift1 <= 59) ||
            (0 <= hour_shift2 && hour_shift2 <= 23 && 0 <= minute_shift2 && minute_shift2 <= 59)) {
            if (hour_shift1 > hour_shift2) {
                throw "Invalid shift! The start shift must be before the end shift!";
            }
            if (hour_shift1 == hour_shift2) {
                if (minute_shift1 > minute_shift2) {
                    throw "Invalid shift! The start shift must be before the end shift!";
                }
            }
        }
    }

    static bool is_name_valid(string name) {
        // method to check if the name is valid
        for (char &c: name) {
            if (!isalpha(c)) {
                return false;
            }
        }
        return true;
    }


    double calculate_total_salaries() {
        // method to calculate the total salaries for the employees at the coffee shop
        double total_salaries = 0.0;

        for (auto *employee: employees) {
            if (employee->get_position() == "Barista") {
                dynamic_cast<Barista *>(employee)->generate_coffee_count();
                total_salaries += employee->calculate_salary();
            }
            if (employee->get_position() == "Waiter") {
                dynamic_cast<Waiter *>(employee)->generate_tips();
                total_salaries += employee->calculate_salary();
            }
            if (employee->get_position() == "Manager") {
                total_salaries += employee->calculate_salary();
            }
        }

        return total_salaries / 21; //there are an average of 21 working days in a month
    } // we only need the total salaries for 1 day

    // method to calculate the total bills for the coffee shop
    double calculate_total_bills() {
        double total_bill = 0.0;
        std::random_device rd; // obtain a random seed
        std::mt19937 gen(rd());

        if (coffee_shop_size == "Small") {
            std::uniform_real_distribution<float> dist(1000, 1500);
            total_bill = dist(gen); // generate a random bill between 1000 and 1500 RON for the Small coffee shop
        } else if (coffee_shop_size == "Medium") {
            std::uniform_real_distribution<float> dist(1500, 2000);
            total_bill = dist(gen); // generate a random bill between 1500 and 2000 RON for the Medium coffee shop
        } else {
            std::uniform_real_distribution<float> dist(2000, 2500);
            total_bill = dist(gen); // generate a random bill between 2000 and 2500 RON for the Large coffee shop
        }

        return total_bill / 21; //there are an average of 21 working days in a month
    } // we only need the bill for 1 day

    double calculate_total_sales() {
        // method to calculate the total sales from orders at the coffee shop
        double total_sales = 0.0;

        for (auto *order: orders) {
            total_sales += order->get_total_price();
        }

        return total_sales;
    }

    double calculate_total_acquisitions() {
        // method to calculate the total sum spent on acquisitions for the coffee shop for a day
        double total_acquisitions = 0.0;

        for (auto *products: new_products) {
            total_acquisitions += products->get_acquisition_cost();
        }

        return total_acquisitions;
    }

    double calculate_total_cost_special_events() {
        // method to calculate the total costs for the special events at the coffee shop for a day
        double total_cost_special_events = 0.0;

        for (auto *special_event: special_events) {
            total_cost_special_events += special_event->get_total_costs();
        }

        return total_cost_special_events;
    }


    double calculate_total_sales_special_events() {
        // method to calculate the total sales for the special events at the coffee shop for a day
        double total_sales_special_events = 0.0;
        std::random_device rd;
        std::mt19937 gen(rd());

        for (auto *special_event: special_events) {
            std::uniform_real_distribution<double> dist(0.5 * special_event->get_total_costs(),
                                                        1.5 * special_event->get_total_costs());
            total_sales_special_events += dist(gen);
            // the sales of the events can vary between 50% and 150% of the total costs
        }

        return total_sales_special_events;
    }


    ~CoffeeShop() = default; // destructor
};


#endif //COFFEESHOP_H
