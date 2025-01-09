#ifndef MENUS_H
#define MENUS_H

#include<iostream>
#include "../coffee-shop/CoffeeShop.h"
#include "../coffee-shop/CoffeeShopManager.h"

// function to display the special events menu
void special_events_menu(CoffeeShop *shop);

// function to display the employee operations menu
void employee_operations_menu(CoffeeShop *shop);

// function to display the product operations menu
void product_operations_menu(CoffeeShop *shop);

// function to display the menu for selecting a coffee shop
void coffee_shop_select_menu(CoffeeShopManager *manager);

// function to display the reports menu
void reports_menu(CoffeeShopManager *manager);

// function to display the main menu
void main_menu(CoffeeShopManager *manager);

#endif //MENUS_H
