#ifndef REPORT_H
#define REPORT_H

#include<iostream>

using namespace std;

class DailyReport {
private:
    string coffee_shop_city;
    string coffee_shop_address;
    string date;
    double total_salaries = 0.0;
    double total_bills = 0.0;
    double total_sales_orders = 0.0;
    double total_acquisitions = 0.0;
    double total_cost_special_events = 0.0;
    double total_sales_special_events = 0.0;
    double total_expenses = 0.0;
    double total_sales = 0.0;
    double profit = 0.0;

public:
    DailyReport(string coffee_shop_city, string coffee_shop_address, string date, double total_salaries,
                double total_bills, double total_sales_order,
                double total_acquisitions, double total_cost_special_events, double total_sales_special_events,
                double total_expenses,
                double total_sales, double profit);

    string get_coffee_shop_city() const;

    string get_coffee_shop_address() const;

    string get_date() const;

    double get_total_salaries() const;

    double get_total_bills() const;

    double get_total_sales_orders() const;

    double get_total_acquisitions() const;

    double get_total_cost_special_events() const;

    double get_total_sales_special_events() const;

    double get_total_expenses() const;

    double get_total_sales() const;

    double get_profit() const;

    void set_total_expenses(double total_expenses);

    void set_total_sales(double total_sales);

    void set_profit(double profit);

    void calculate_profit();

    ~DailyReport();
};


#endif //REPORT_H
