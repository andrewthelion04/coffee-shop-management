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

class CoffeeShop {
private:
    string coffee_shop_address;
    string coffee_shop_city;
    string coffee_shop_size;
    vector<Employee*> employees; //utilizare template-uri pentru a evita duplicarea codului
    vector<Product*> all_products;
    vector<Product*> new_products;
    vector<Client*> clients;
    vector<Order*> orders;
    vector<SpecialEvent*> special_events;

public:
    CoffeeShop(string coffee_shop_address, string coffee_shop_city, string coffee_shop_size) : coffee_shop_address(coffee_shop_address), coffee_shop_city(coffee_shop_city), coffee_shop_size(coffee_shop_size) {}

    string get_coffee_shop_address() {
        return coffee_shop_address;
    }

    string get_coffee_shop_city() {
        return coffee_shop_city;
    }

    string get_coffee_shop_size() {
        return coffee_shop_size;
    }

    vector<Product*> get_new_products() {
        return new_products;
    }

    vector<Order*> get_orders() {
        return orders;
    }

    vector<SpecialEvent*> get_special_events() {
        return special_events;
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
        if(employees.empty()) {
            throw "There are no employees!\n";
        }

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

        all_products.push_back(new Product(product_name, type, stof(purchase_price), stof(sale_price), stoi(quantity)));
        new_products.push_back(new Product(product_name, type, stof(purchase_price), stof(sale_price), stoi(quantity)));


        ofstream products_file("products.csv", ios::app);
        if(!products_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        products_file << coffee_shop_city << "," << coffee_shop_address << "," << product_name << "," << type << "," << purchase_price << "," << sale_price << "," << quantity << endl;
        products_file.close();
    }

    void delete_product() {
        if(all_products.empty()) {
            throw "There are no products!\n";
        }

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
            ofstream output_file("products.csv");
            if(!output_file.is_open()) {
                throw "Error: File not opened";
            }

            for(const string& l : lines) {
                output_file << l << endl;
            }
            output_file.close();

            Product *removed_product = new Product(product_name, type, 0, 0, 0);
            for(auto product = all_products.begin(); product != all_products.end(); ++product) {
                if((*product)->get_name() == removed_product->get_name() &&
                   (*product)->get_type() == removed_product->get_type()) {
                    all_products.erase(product);
                    break;
                }
            }

            for(auto product = new_products.begin(); product != new_products.end(); ++product) {
                if((*product)->get_name() == removed_product->get_name() &&
                   (*product)->get_type() == removed_product->get_type()) {
                    new_products.erase(product);
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

    bool check_minimum_staff_required() {
        int barista_count = 0, waiter_count = 0, manager_count = 0;

        for(auto* employee : employees) {
            if(employee->get_position() == "Barista") {
                barista_count++;
            }
            if(employee->get_position() == "Waiter") {
                waiter_count++;
            }
            if(employee->get_position() == "Manager") {
                manager_count++;
            }
        }

        if(coffee_shop_size == "Small") {
            if(barista_count < 1 || waiter_count < 1 || manager_count < 1) {
                return false;
            }
        }
        if(coffee_shop_size == "Medium") {
            if(barista_count < 2 || waiter_count < 2 || manager_count < 2) {
                return false;
            }
        }
        if(coffee_shop_size == "Large") {
            if(barista_count < 3 || waiter_count < 3 || manager_count < 2) {
                return false;
            }
        }

        return true;
    }

    void place_order() {
        if(all_products.empty()) {
            throw "The coffee shop located in " + coffee_shop_city + " - " + coffee_shop_address + " has no products available!\n";

        }

        if(!check_minimum_staff_required()) {
            throw "The coffee shop located in" + coffee_shop_city + " - " + coffee_shop_address + " does not have enough staff to place an order!\n"
        }

        string client_name;
        cout << "Order placement!" << endl;
        cout << "Insert the client's full name: ";
        getline(cin, client_name);

        Client* client = nullptr;
        for (auto* c : clients) {
            if (c->get_name() == client_name) {
                client = c;
                break;
            }
        }

        if (!client) {
            client = new Client(client_name);
            clients.push_back(client);
        }

        client_order(client);
    }

    void client_order(Client* client) {
        Order* order = new Order();
        string response = "no";

        do {
            bool has_coffee = false, has_beverages = false, has_deserts = false;
            string product_name;
            int quantity;

            for (auto* product : all_products) {
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

            if (has_coffee) {
                cout << "Coffees: " << endl;
                for (auto* product : all_products) {
                    if (product->get_type() == "Coffee") {
                        cout << product->get_name() << " - " << product->get_sale_price() << " RON" << endl;
                    }
                }
            }

            if (has_beverages) {
                cout << "Beverages: " << endl;
                for (auto* product : all_products) {
                    if (product->get_type() == "Beverage") {
                        cout << product->get_name() << " - " << product->get_sale_price() << " RON" << endl;
                    }
                }
            }

            if (has_deserts) {
                cout << "Deserts: " << endl;
                for (auto* product : all_products) {
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
            if(cin.fail() || quantity <= 0) {
                throw "Cantitate invalida";
            }


            try {
                subtract_product(product_name, quantity);
            } catch (const char* msg) {
                cout << msg << endl;
                delete order;
                return;
            }

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

        order->calculate_total_price();

        // implementarea sistemului de fidelitate: la fiecare a 5-a comanda clientul primeste 10% reducere
        if((client->get_number_of_orders() + 1) % 5 == 0) {
            cout << client->get_name() << " has received a 10% discount for being a loyal customer!" << endl;
            order->set_total_price(order->get_total_price() * 0.9);
        }

        orders.push_back(order);
        client->add_order(order);

        string ordered_products;

        for (const auto& product : order->get_ordered_products()) {
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

        orders_file << coffee_shop_city << "," << coffee_shop_address << "," << client->get_name() << "," << ordered_products << "," << order->get_total_price() << endl;
        orders_file.close();

        cout << "Order has been placed! The total price is: " << order->get_total_price() << " RON" << endl;

        delete order;
    }

    void subtract_product(string product_name, int quantity) {
        for (auto product = all_products.begin(); product != all_products.end(); ++product) {
            if ((*product)->get_name() == product_name) {
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
                        string read_city, read_address, read_product_name, read_type, read_purchase_price, read_sale_price, read_quantity;
                        getline(ss, read_city, ',');
                        getline(ss, read_address, ',');
                        getline(ss, read_product_name, ',');
                        getline(ss, read_type, ',');
                        getline(ss, read_purchase_price, ',');
                        getline(ss, read_sale_price, ',');
                        getline(ss, read_quantity, ',');

                        if (product_name == read_product_name) {
                            lines.push_back(coffee_shop_city + "," + coffee_shop_address + "," + product_name + "," + read_type + "," + read_purchase_price + "," + read_sale_price + "," + to_string(stoi(read_quantity) - quantity));
                        } else {
                            lines.push_back(line);
                        }
                    }

                    input_file.close();

                    ofstream output_file("products.csv");
                    if (!output_file.is_open()) {
                        throw "Error: File not opened";
                    }

                    for (const string& l : lines) {
                        output_file << l << endl;
                    }

                    output_file.close();

                    if ((*product)->get_quantity() == 0) {
                        all_products.erase(product);
                    }

                    return;
                } else {
                    throw "Insufficient quantity!";
                }
            }
        }
        throw "Product not found!";
    }

    void add_special_event() {
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

        SpecialEvent *special_event = new SpecialEvent(name, description, start_time);

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
                    getline(cin, name);

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
            special_event->add_required_product(product_name, type, stof(cost), stoi(quantity));

            do {
                cout << "Do you wish to add more requirements for the event? (yes/no): ";
                getline(cin, response);
            } while (response != "yes" && response != "no");
        } while (response == "yes");


        special_event->calculate_total_costs();
        special_events.push_back(special_event);

        ofstream special_events_file("special_events.csv", ios::app);
        if (!special_events_file.is_open()) {
            cout << "Error: File not opened" << endl;
            return;
        }

        special_events_file << coffee_shop_city << "," << coffee_shop_address << "," << name << "," << description << start_time <<
                "," << special_event->get_total_costs() << endl;
        special_events_file.close();
    }

    void remove_special_event() {
        if(special_events.empty()) {
            throw "There are no special events available!";
        }

        cout << "Select the special event you wish to remove!" << endl;
        int events_index = 0;
        int events_choice;
        for(auto* special_event : special_events) {
            cout << ++events_index <<". "  << special_event->get_name();
        }
        cout << "Your choice: ";
        cin >> events_choice;
        cin.ignore();

        if(events_choice < 1 || events_choice > 2) {
            throw "Invalid choice!";
        }

        SpecialEvent* chosen_event = special_events[events_choice - 1];

        for(auto event = special_events.begin(); event != special_events.end(); ++event) {
            if((*event)->get_name() == chosen_event->get_name()) {
                special_events.erase(event);
                break;
            }
        }

        ifstream input_file("special_events.csv");
        vector<string> lines;
        string line;

        getline(input_file, line);
        lines.push_back(line);

        while(getline(input_file, line)) {
            stringstream ss(line);
            string read_city, read_address, read_event_name, read_event_description, read_event_start_time, read_costs;

            getline(ss, read_city, ',');
            getline(ss, read_address, ',');
            getline(ss, read_event_name, ',');
            getline(ss, read_event_description, ',');
            getline(ss, read_event_start_time, ',');
            getline(ss, read_costs, ',');
            if(chosen_event->get_name() != read_event_name) {
                lines.push_back(line);
            }
        }
        input_file.close();

        ofstream output_file("special_events.csv");
        if(!output_file.is_open()) {
            throw "Error: File not opened";
        }

        for(const string& l : lines) {
            output_file << l << endl;
        }

        output_file.close();
    }

    void display_special_events() {
        if(special_events.empty()) {
            throw "There are no special events booked at the coffee shop located in " + coffee_shop_city + " - " + coffee_shop_address + "!" + "\n";
        }
        int special_event_index = 0;
        cout << "Special event/s at the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address << ":" << endl;
        for(auto* special_event : special_events) {
            cout << ++special_event_index << "." << special_event->get_name() << endl;
            cout << "\t->Description: " << special_event->get_description() << endl;
            cout << "\t->Estimated costs: " << special_event->get_total_costs() << endl;
        }
    }

    void display_special_event_requirements() {
        if(special_events.empty()) {
            throw "There are no special events booked at the coffee shop located in" + coffee_shop_city + " - " + coffee_shop_address + "!" + "\n";
        }

        int special_event_index = 0;
        int special_event_choice;

        cout << "Select the special event you wish to see the requirements for!" << endl;
        for(auto* special_event : special_events) {
            cout << ++special_event_index << "." << special_event->get_name() << endl;
        }
        cout << "Your choice: ";
        cin >> special_event_choice;
        cin.ignore();

        SpecialEvent* event = special_events[special_event_choice - 1];

        bool has_food_and_beverages = false, has_service_personnel = false, has_decorative_elements = false;
        for(auto* required_product : event->get_required_products()) {
            if(required_product->get_type() == "Food and beverages") {
                has_food_and_beverages = true;
            }
            if(required_product->get_type() == "Service personnel") {
                has_service_personnel = true;
            }
            if(required_product->get_type() == "Decorative elements") {
                has_decorative_elements = true;
            }
        }

        cout << "Requirements for the special event " << event->get_name() << ":" << endl;
        if(has_food_and_beverages) {
            cout << "Food and beverages: " << endl;
            for(auto* required_product : event->get_required_products()) {
                if(required_product->get_type() == "Food and beverages") {
                    cout << required_product->get_product_name() << " - " << required_product->get_quantity() << " - " << required_product->get_cost() << " RON" << endl;
                }
            }
        }

        if(has_service_personnel) {
            cout << "Service personnel: " << endl;
            for(auto* required_product : event->get_required_products()) {
                if(required_product->get_type() == "Service personnel") {
                    cout << required_product->get_product_name() << " - " << required_product->get_cost() << " RON" << endl;
                }
            }
        }

        if(has_decorative_elements) {
            cout << "Decorative elements: " << endl;
            for(auto* required_product : event->get_required_products()) {
                if(required_product->get_type() == "Decorative elements") {
                    cout << required_product->get_product_name() << " - " << required_product->get_quantity() << " - " << required_product->get_cost() << " RON" << endl;
                }
            }
        }

        cout << "Total costs: " << event->get_total_costs() << " RON" << endl << endl;
    }


    void display_employees_information() {
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

    void display_employees_shifts() {
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

    void display_products() {
        int index = 0;
        cout << "List of all the products available at the coffee shop located in " << coffee_shop_city << " - " << coffee_shop_address << ":" << endl;
        for(auto product = all_products.begin(); product != all_products.end(); ++product) {
            cout << ++index << ". " << (*product)->get_name() << " - " << (*product)->get_type() << " - " << (*product)->get_sale_price() << " RON" << endl;
        }
        cout<<endl;
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
            if(hour_shift1 > hour_shift2) {
                throw "Invalid shift! The start shift must be before the end shift!";
            }
            if(hour_shift1 == hour_shift2) {
                if(minute_shift1 > minute_shift2) {
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

    //determinarea salariilor ce trebuie achitate pe o luna intreaga
    double calculate_total_salaries() {
        double total_salaries = 0.0;

        for(auto* employee : employees) {
            if(employee->get_position() == "Barista") {
                dynamic_cast<Barista*>(employee)->generate_coffee_count();
                total_salaries += employee->calculate_salary();
            }
            if(employee->get_position() == "Waiter") {
                dynamic_cast<Waiter*>(employee)->generate_tips();
                total_salaries += employee->calculate_salary();
            }
            if(employee->get_position() == "Manager") {
                total_salaries += employee->calculate_salary();
            }
        }

        return total_salaries / 21; //there are an average of 21 working days in a month
    }                   // we only need the total salaries for 1 day

    // determinarea sumei de plata la factura pe o luna intreaga
    double calculate_total_bills() {
        double total_bill = 0.0;
        std::random_device rd;  // pentru generare seed
        std::mt19937 gen(rd());

        if (coffee_shop_size == "Small") {
            std::uniform_real_distribution<float> dist(1000, 1500);
            total_bill = dist(gen);
        }
        else if(coffee_shop_size == "Medium") {
            std::uniform_real_distribution<float> dist(1500, 2000);
            total_bill = dist(gen);
        }
        else {
            std::uniform_real_distribution<float> dist(2000, 2500);
            total_bill = dist(gen);
        }

        return total_bill / 21; //there are an average of 21 working days in a month
    }                       // we only need the bill for 1 day

    double calculate_total_sales() {
        double total_sales = 0.0;

        for(auto* order : orders) {
            total_sales += order->get_total_price();
        }

        return total_sales;
    }

    double calculate_total_acquisitions() {
        double total_acquisitions = 0.0;

        for(auto* products : new_products) {
            total_acquisitions += products->get_acquisition_cost();
        }

        return total_acquisitions;
    }

    double calculate_total_cost_special_events() {
        double total_cost_special_events = 0.0;

        for(auto* special_event : special_events) {
            total_cost_special_events += special_event->get_total_costs();
        }

        return total_cost_special_events;
    }


    double calculate_total_sales_special_events() {
        double total_sales_special_events = 0.0;
        std::random_device rd;
        std::mt19937 gen(rd());

        for(auto* special_event : special_events) {
            std::uniform_real_distribution<double> dist(0.5*special_event->get_total_costs(), 1.5*special_event->get_total_costs());
            total_sales_special_events += dist(gen);
        }

        return total_sales_special_events;
    }



    ~CoffeeShop() = default;
};


#endif //COFFEESHOP_H
