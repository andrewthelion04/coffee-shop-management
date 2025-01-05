cmake_minimum_required(VERSION 3.29)
project(coffee_shop_management)

set(CMAKE_CXX_STANDARD 14)

add_executable(coffee_shop_management
    main.cpp
        files_initialization/initialize_files.h
        positions/Employee.h
        positions/Barista.h
        positions/Waiter.h
        positions/Manager.h
        products/Product.h
        coffee-shop/CoffeeShop.h
        coffee-shop/CoffeeShopManager.h
        orders/Client.h
        orders/Order.h
        orders/OrderedProduct.h
        special-events/SpecialEvent.h
        special-events/ProductsAndServices.h
        reports/DailyReport.h
        menus/menus.h
)
