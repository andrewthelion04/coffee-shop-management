#include<iostream>
#include "DailyReport.h"

using namespace std;


DailyReport::DailyReport(string coffee_shop_city, string coffee_shop_address, string date, double total_salaries,
                         double total_bills, double total_sales_order,
                         double total_acquisitions, double total_cost_special_events, double total_sales_special_events,
                         double total_expenses,
                         double total_sales, double profit) : coffee_shop_city(std::move(coffee_shop_city)),
                                                              coffee_shop_address(std::move(coffee_shop_address)),
                                                              date(std::move(date)), total_salaries(total_salaries),
                                                              total_bills(total_bills),
                                                              total_sales_orders(total_sales_order),
                                                              total_acquisitions(total_acquisitions),
                                                              total_cost_special_events(total_cost_special_events),
                                                              total_sales_special_events(total_sales_special_events),
                                                              total_expenses(total_expenses),
                                                              total_sales(total_sales), profit(profit) {
}

string DailyReport::get_coffee_shop_city() const {
    return coffee_shop_city;
}

string DailyReport::get_coffee_shop_address() const {
    return coffee_shop_address;
}

string DailyReport::get_date() const {
    return date;
}

double DailyReport::get_total_salaries() const {
    return total_salaries;
}

double DailyReport::get_total_bills() const {
    return total_bills;
}

double DailyReport::get_total_sales_orders() const {
    return total_sales_orders;
}

double DailyReport::get_total_acquisitions() const {
    return total_acquisitions;
}

double DailyReport::get_total_cost_special_events() const {
    return total_cost_special_events;
}

double DailyReport::get_total_sales_special_events() const {
    return total_sales_special_events;
}

double DailyReport::get_total_expenses() const {
    return total_expenses;
}

double DailyReport::get_total_sales() const {
    return total_sales;
}

double DailyReport::get_profit() const {
    return profit;
}

void DailyReport::set_total_expenses(double total_expenses) {
    DailyReport::total_expenses = total_expenses;
}

void DailyReport::set_total_sales(double total_sales) {
    DailyReport::total_sales = total_sales;
}

void DailyReport::set_profit(double profit) {
    DailyReport::profit = profit;
}

void DailyReport::calculate_profit() {
    profit = total_sales - total_expenses;
}

DailyReport::~DailyReport() = default;
