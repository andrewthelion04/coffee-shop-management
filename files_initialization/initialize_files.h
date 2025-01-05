#include<iostream>
#include<fstream>
using namespace std;


// function to initialize the employees file
void initialize_employees_file(string language) {
    ofstream employees_file;
    employees_file.open("employees.csv");
    if (!employees_file.is_open()) {
        cout << "Error: File not opened" << endl;
        return;
    }
    if (language == "English") {
        employees_file <<
                "coffee_shop_city,coffee_shop_address,employee_name,employee_surname,position,salary,shift_start,shift_end"
                << endl;
    } else {
        employees_file <<
                "oras_cafenea,adresa_cafenea,nume_angajat,prenume_angajat,pozitie,salariu,ora_incepere_tura,ora_sfarsit_tura"
                << endl;
    }
    employees_file.close();
}

// function to initialize the products file
void initialize_products_file(string language) {
    ofstream products_file;
    products_file.open("products.csv");
    if (!products_file.is_open()) {
        cout << "Error: File not opened" << endl;
        return;
    }

    if (language == "English") {
        products_file << "coffee_shop_city,coffee_shop_address,name,type,purchase_price,sale_price,quantity" << endl;
    } else {
        products_file << "oras_cafenea,adresa_cafenea,nume,tip,pret_achizitie,pret_vanzare,cantitate" << endl;
    }

    products_file.close();
}

// function to initialize the orders file
void initialize_orders_file(string language) {
    ofstream orders_file;
    orders_file.open("orders.csv");
    if (!orders_file.is_open()) {
        cout << "Error: File not opened" << endl;
        return;
    }

    if (language == "English") {
        orders_file << "coffee_shop_city,coffee_shop_address,client_name,products_names_and_quantities,price" << endl;
    } else {
        orders_file << "oras_cafenea,adresa_cafenea,nume_client,produse_nume_si_cantitati,pret" << endl;
    }

    orders_file.close();
}

// function to initialize the special events file
void initialize_special_events_file(string language) {
    ofstream special_events_file;
    special_events_file.open("special_events.csv");
    if (!special_events_file.is_open()) {
        cout << "Error: File not opened" << endl;
        return;
    }

    if (language == "English") {
        special_events_file <<
                "coffee_shop_city,coffee_shop_address,event_name,event_description,start_time,event_costs" << endl;
    } else {
        special_events_file <<
                "oras_cafenea,adresa_cafenea,nume_eveniment,descriere_eveniment,ora_inceput,costuri_eveniment" << endl;
    }

    special_events_file.close();
}

// function to initialize the reports file
void initialize_reports_file(string language) {
    ofstream reports_file;
    reports_file.open("reports.csv");
    if (!reports_file.is_open()) {
        cout << "Error: File not opened" << endl;
        return;
    }

    if (language == "English") {
        reports_file << "coffee_shop_city,coffee_shop_address,date,total_expenses,total_sales,profit" << endl;
    } else {
        reports_file << "oras_cafenea,adresa_cafenea,data,cheltuieli_totale,vanzari_totale,profit" << endl;
    }

    reports_file.close();
}

// function to initialize the coffee shops file
void initialize_coffee_shops_file(string language) {
    ofstream coffee_shops_file;
    coffee_shops_file.open("coffee_shops.csv");
    if (!coffee_shops_file.is_open()) {
        cout << "Error: File not opened" << endl;
        return;
    }

    if (language == "English") {
        coffee_shops_file << "city,address,size" << endl;
    } else {
        coffee_shops_file << "oras,adresa,marime" << endl;
    }


    coffee_shops_file.close();
}
