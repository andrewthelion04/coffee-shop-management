#include<iostream>
#include<fstream>
#include "initialize_files.h"

using namespace std;

int main()
{
    insert_employees_file();
    insert_products_file();
    insert_orders_file();
    insert_special_events_file();
    insert_reports_file();


    return 0;
}

