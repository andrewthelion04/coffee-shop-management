#include<iostream>
#include<fstream>
#include "initialize_files.h"
#include "coffee-shop/CoffeeShopManager.h"
#include "coffee-shop/CoffeeShop.h"

using namespace std;

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
                    CoffeeShop* selected_shop = manager.choose_coffee_shop();
                    selected_shop->add_employee();
                    selected_shop->remove_employee();

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

