#include<iostream>
#include<fstream>
#include "initialize_files.h"
#include "coffee-shop/CoffeeShopManager.h"
#include "coffee-shop/CoffeeShop.h"

using namespace std;

void special_events_menu(CoffeeShop *shop) {
    int choice;
    do {
        cout << "1. Add special event" << endl;
        cout << "2. Remove special event" << endl;
        cout << "3. Display special events" << endl;
        cout << "4. Display requirements and costs for a special event" << endl;
        cout << "5. Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                try {
                    shop->add_special_event();
                }catch(const char* message) {
                    cout << message << endl;
                }
                break;
            case 2:
                try {
                    shop->remove_special_event();
                }catch(const char* message) {
                    cout << message << endl;
                }
                break;
            case 3:
                try {
                    shop->display_special_events();
                }catch(const char* message) {
                    cout << message << endl;
                }

            case 4:
                try {
                    shop->display_special_event_requirements();
                }catch(const char* message) {
                    cout << message << endl;
                }
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice!\n";
            break;


        }
    }while(choice != 4);
}

void product_operations_menu(CoffeeShop* shop) {
    int choice;
    do {
        cout << "1. Add product" << endl;
        cout << "2. Remove product" << endl;
        cout << "3. Display the list of products" << endl;
        cout << "4. Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                try {
                    shop->add_product();
                }catch(const char* message) {
                    cout << message << endl;
                }
            break;
            case 2:
                try {
                    shop->delete_product();
                }catch(const char* message) {
                    cout << message << endl;
                }
                break;
            case 3:
                try {
                    shop->display_products();
                }catch(const char* message) {
                    cout << message << endl;
                }
            break;
            case 4:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
            break;
        }
    }while(choice != 4);
}

void employee_operations_menu(CoffeeShop* shop) {
    int choice;
    do {
        cout << "1. Add employee" << endl;
        cout << "2. Remove employee" << endl;
        cout << "3. Display employees" << endl;
        cout << "4. Display employees shifts" << endl;
        cout << "5. Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                try {
                    shop->add_employee();
                }catch(const char* message) {
                    cout << message << endl;
                }
                break;
            case 2:
                try {
                    shop->remove_employee();
                }catch(const char* message) {
                    cout << message << endl;
                }
                break;
            case 3:
                try {
                    shop->display_employees_information();
                }catch(const char* message) {
                    cout << message << endl << endl;
                }
                break;
            case 4:
                try {
                    shop->display_employees_shifts();
                }catch(const char* message) {
                    cout << message << endl << endl;
                }
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
            break;
        }
    }while(choice != 5);
}

void coffee_shop_select_menu(CoffeeShopManager* manager) {
    int choice;
    CoffeeShop *selected_shop = manager->choose_coffee_shop();
    do {
        cout << "Coffee shop located in " << selected_shop->get_coffee_shop_city() << " - " << selected_shop->get_coffee_shop_address() << endl;
        cout << "1. Employee operations" << endl;
        cout << "2. Product operations" << endl;
        cout << "3. Order a product" << endl;
        cout << "4. Special event operations" << endl;
        cout << "5. Report operations" << endl;
        cout << "6. Exit" << endl;

        cout << "Your choice:";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                employee_operations_menu(selected_shop);
                break;
            case 2:
                product_operations_menu(selected_shop);
                break;
            case 3:
                selected_shop->place_order();
                break;
            case 4:
                special_events_menu(selected_shop);
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                break;
        }

    }while(choice != 6);
}

int main()
{
    insert_employees_file();
    insert_products_file();
    insert_orders_file();
    insert_special_events_file();
    insert_reports_file();
    insert_coffee_shops_file();

    int choice;
    CoffeeShopManager manager;
    manager.get_today_date();

    do{
        cout << "Welcome to the coffee shop manager! Date: " << manager.get_current_day() << endl;
        cout << "1. Add coffee shop" << endl;
        cout << "2. Remove coffee shop" << endl;
        cout << "3. Display coffee shops" << endl;
        cout << "4. Select coffee shop" << endl;
        cout << "5. Generate a report for each coffee shop" << endl;
        cout << "6. Exit" << endl;


        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                try {
                    manager.add_coffee_shop();
                }catch(const char* msg) {
                    cout<< msg << endl << endl;
                }
                break;
            case 2:
                manager.remove_coffee_shop();
                break;
            case 3:
                try {
                    manager.display_coffee_shops();
                }catch(const char* message) {
                    cout << message << endl << endl;
                }
                break;
            case 4:
                try {
                    coffee_shop_select_menu(&manager);
                }catch (const char* message) {
                    cout << message << endl;
                }
                break;
            case 5:
                try {

                    manager.generate_daily_reports();
                    manager.go_to_next_day();
                }catch(const char* message) {
                    cout << message << endl;
                }
                break;

            default:
                cout << "Invalid choice! Please try again!" << endl;
        }
    }while(choice != 6);

    return 0;
}

