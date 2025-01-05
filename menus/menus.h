#ifndef MENUS_H
#define MENUS_H

#include<iostream>
#include "../coffee-shop/CoffeeShop.h"
#include "../coffee-shop/CoffeeShopManager.h"

// function to display the special events menu
void special_events_menu(CoffeeShop *shop) {
    int choice;
    do {
        cout << "Special event operations menu" << endl;
        cout << "1. Add special event" << endl;
        cout << "2. Remove special event" << endl;
        cout << "3. Display special events" << endl;
        cout << "4. Display requirements and costs for a special event" << endl;
        cout << "5. Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        // check if the input is valid
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl << endl;
            cout << "Press any key to continue...";
            cin.get();
            continue;
        }

        // switch case for the user's choice
        switch (choice) {
            case 1:
                try {
                    shop->add_special_event();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    // catch the exception thrown when the special event already exists
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 2:
                try {
                    shop->remove_special_event();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when the special event is not found
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 3:
                try {
                    shop->display_special_events();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (string &message) {
                    //catch the exception thrown when there are no special events
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 4:
                try {
                    shop->display_special_event_requirements();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (string &message) {
                    //if the special event is not found
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice! Please try again!\n";
                cout << "Press any key to continue...";
                cin.get();
                break;
        }
    } while (choice != 5);
}

// function to display the employee operations menu
void employee_operations_menu(CoffeeShop *shop) {
    int choice;
    do {
        cout << "Employee operations menu" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Remove employee" << endl;
        cout << "3. Display employees" << endl;
        cout << "4. Display employees shifts" << endl;
        cout << "5. Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl << endl;
            cout << "Press any key to continue...";
            cin.get();
            continue;
        }

        // switch case for the user's choice
        switch (choice) {
            case 1:
                try {
                    shop->add_employee();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when the name or surname is not valid
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 2:
                try {
                    shop->remove_employee();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when the employee is not found / when there are no employees
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 3:
                try {
                    shop->display_employees_information();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when there are no employees
                    cout << message << endl << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 4:
                try {
                    shop->display_employees_shifts();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when there are no employees
                    cout << message << endl << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                cout << "Press any key to continue...";
                cin.get();
                break;
        }
    } while (choice != 5);
}

// function to display the product operations menu
void product_operations_menu(CoffeeShop *shop) {
    int choice;
    do {
        cout << "Product operation menu" << endl;
        cout << "1. Add product" << endl;
        cout << "2. Remove product" << endl;
        cout << "3. Display the list of products" << endl;
        cout << "4. Exit" << endl;

        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl << endl;
            cout << "Press any key to continue...";
            cin.get();
            continue;
        }

        // switch case for the user's choice
        switch (choice) {
            case 1:
                try {
                    shop->add_product();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    // catch the exception thrown when the name or the quantity is not valid
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 2:
                try {
                    shop->delete_product();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when the product is not found / when there are no products
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 3:
                try {
                    shop->display_products();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when there are no products
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                cout << "Press any key to continue...";
                cin.get();
                break;
        }
    } while (choice != 4);
}

// function to display the menu for selecting a coffee shop
void coffee_shop_select_menu(CoffeeShopManager *manager) {
    int choice;
    CoffeeShop *selected_shop = manager->choose_coffee_shop();
    do {
        cout << "Selection menu for the coffee shop located in " << selected_shop->get_coffee_shop_city() << " - " <<
                selected_shop->get_coffee_shop_address() << endl;
        cout << "1. Employee operations" << endl;
        cout << "2. Product operations" << endl;
        cout << "3. Take an order" << endl;
        cout << "4. Special event operations" << endl;
        cout << "5. Main menu" << endl;


        cout << "Your choice:";
        cin >> choice;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl << endl;
            continue;
        }

        // switch case for the user's choice
        switch (choice) {
            case 1:
                // call the employee operations menu
                employee_operations_menu(selected_shop);
                break;
            case 2:
                // call the product operations menu
                product_operations_menu(selected_shop);
                break;
            case 3:
                try {
                    selected_shop->place_order();
                } catch (string &message) {
                    //catch the exception thrown when there are no products / when there are not enough employees
                    cout << message << endl;
                }
                break;
            case 4:
                // call the special events menu
                special_events_menu(selected_shop);
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                cout << "Press any key to continue...";
                cin.get();
                break;
        }
    } while (choice != 5);
}

// function to display the reports menu
void reports_menu(CoffeeShopManager *manager) {
    int choice;
    do {
        cout << "Daily reports menu!" << endl;
        cout << "1. Generate daily reports for all coffee shops" << endl;
        cout << "2. Print daily reports for a specific coffee shop" << endl;
        cout << "3. Print detailed daily reports for a specific coffee shop" << endl;
        cout << "4. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl << endl;
            continue;
        }

        // switch case for the user's choice
        switch (choice) {
            case 1:
                try {
                    // call the method to generate daily reports
                    manager->generate_daily_reports();
                    // call the method to go to the next day
                    manager->go_to_next_day();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when there are no coffee shops
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 2:
                try {
                    manager->print_daily_reports();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when there are no coffee shops
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 3:
                try {
                    manager->print_detailed_daily_reports();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catch the exception thrown when there are no coffee shops
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                cout << "Press any key to continue...";
                cin.get();
        }
    } while (choice != 4);
}

// function to display the main menu
void main_menu(CoffeeShopManager *manager) {
    manager->get_today_date();
    int choice;
    do {
        cout << "Welcome to the coffee shop manager! Date: " << manager->get_current_day() << endl;
        cout << "1. Add coffee shop" << endl;
        cout << "2. Remove coffee shop" << endl;
        cout << "3. Display coffee shops" << endl;
        cout << "4. Manage a coffee shop" << endl;
        cout << "5. Reports menu" << endl;
        cout << "6. Exit" << endl;


        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl << endl;
            cout << "Press any key to continue...";
            cin.get();
            continue;
        }

        switch (choice) {
            case 1:
                try {
                    manager->add_coffee_shop();
                } catch (const char *msg) {
                    //catching the exception thrown by the add_coffee_shop method
                    cout << msg << endl << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                cout << "Press any key to continue...";
                cin.get();
                break;
            case 2:
                try {
                    manager->remove_coffee_shop();
                } catch (const char *msg) {
                    //catching the exception thrown by the remove_coffee_shop method
                    cout << msg << endl << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                cout << "Press any key to continue...";
                cin.get();
                break;
            case 3:
                try {
                    manager->display_coffee_shops();
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catching the exception thrown by the display_coffee_shops method
                    cout << message << endl << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 4:
                try {
                    coffee_shop_select_menu(manager);
                    cout << "Press any key to continue...";
                    cin.get();
                } catch (const char *message) {
                    //catching the exception thrown by the choose_coffee_shop method
                    cout << message << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                }
                break;
            case 5:
                reports_menu(manager);
                cout << "Press any key to continue...";
                cin.get();
                break;

            case 6:
                break;

            default:
                cout << "Invalid choice! Please try again!" << endl;
        }
    } while (choice != 6);
}


#endif //MENUS_H
