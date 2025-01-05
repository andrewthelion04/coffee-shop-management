#include<iostream>
#include "files_initialization/initialize_files.h"
#include "coffee-shop/CoffeeShopManager.h"
#include "menus/menus.h"

using namespace std;

// main function
int main()
{

    int select_language;
    string language;
    // user input for the language used in the .csv files
    do {
        cout << "Welcome to the Coffee Shop Management System!" << endl;
        cout << "Select the language used in the .csv files:" << endl;
        cout << "1. English" << endl;
        cout << "2. Romanian" << endl;
        cout << "3. Exit program" << endl;
        cout << "Your choice: ";
        cin >> select_language;
        cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl << endl;
            cout<<"Press any key to continue...";
            cin.get();
        }

        switch(select_language) {
            case 1:
                language = "English";
                break;
            case 2:
                language = "Romanian";
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice! Please try again!" << endl;
                cout<<"Press any key to continue...";
                cin.get();
        }

    }while(select_language != 1 && select_language != 2);

    // initialize the .csv files
    initialize_employees_file(language);
    initialize_products_file(language);
    initialize_orders_file(language);
    initialize_special_events_file(language);
    initialize_reports_file(language);
    initialize_coffee_shops_file(language);

    // create a Singleton instance of the CoffeeShopManager class
    CoffeeShopManager* manager = CoffeeShopManager::getInstance();

    // display the main menu
    main_menu(manager);

    return 0;
}

