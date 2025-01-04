#ifndef REPORT_H
#define REPORT_H



class DailyReport {
private:
    string coffee_shop_city;
    string coffee_shop_address;
    string date;
    double total_expenses = 0.0;
    double total_sales = 0.0;
    double profit = 0.0;
public:
    DailyReport(string coffee_shop_city, string coffee_shop_address, string date, double total_expenses, double total_sales, double profit) : coffee_shop_city(std::move(coffee_shop_city)),
    coffee_shop_address(std::move(coffee_shop_address)), date(std::move(date)), total_expenses(total_expenses), total_sales(total_sales), profit(profit) {}

    string get_coffee_shop_city() const {
        return coffee_shop_city;
    }

    string get_coffee_shop_address() const {
        return coffee_shop_address;
    }

    string get_date() const {
        return date;
    }

    double get_total_expenses() const {
        return total_expenses;
    }

    double get_total_sales() const {
        return total_sales;
    }

    double get_profit() const {
        return profit;
    }

    void set_total_expenses(double total_expenses) {
        DailyReport::total_expenses = total_expenses;
    }

    void set_total_sales(double total_sales) {
        DailyReport::total_sales = total_sales;
    }

    void set_profit(double profit) {
        DailyReport::profit = profit;
    }

    void calculate_profit() {
        profit = total_sales - total_expenses;
    }

    ~DailyReport() = default;


};



#endif //REPORT_H
