#include<iostream>
#include<fstream>
using namespace std;

void insert_employees_file()
{
    ofstream employees_file;
    employees_file.open("employees.csv", ios::app);
    if(!employees_file.is_open())
    {
        cout<<"Error: File not opened"<<endl;
        return;
    }

    employees_file<<"name,surname,postion,shift_start,shift_end"<<endl;
    employees_file.close();
}

void insert_products_file()
{
    ofstream products_file;
    products_file.open("products.csv", ios::app);
    if(!products_file.is_open())
    {
        cout<<"Error: File not opened"<<endl;
        return;
    }

    products_file<<"type,name,price,quantity"<<endl;
    products_file.close();
}

void insert_orders_file()
{
    ofstream orders_file;
    orders_file.open("orders.csv", ios::app);
    if(!orders_file.is_open())
    {
        cout<<"Error: File not opened"<<endl;
        return;
    }

    orders_file<<"client_name,product_name,quantity,price"<<endl;
    orders_file.close();
}

void insert_special_events_file()
{
    ofstream special_events_file;
    special_events_file.open("special_events.csv", ios::app);
    if(!special_events_file.is_open())
    {
        cout<<"Error: File not opened"<<endl;
        return;
    }

    special_events_file<<"name,date,description"<<endl;
    special_events_file.close();
}

void insert_reports_file()
{
    ofstream reports_file;
    reports_file.open("reports.csv", ios::app);
    if(!reports_file.is_open())
    {
        cout<<"Error: File not opened"<<endl;
        return;
    }

    reports_file<<"date,total_cost_products,employees_salaries,total_sales"<<endl;
    reports_file.close();
}