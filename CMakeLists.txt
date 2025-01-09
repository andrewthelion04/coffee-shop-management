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
        coffee-shop/CoffeeShop.cpp
        coffee-shop/CoffeeShopManager.cpp
        files_initialization/initialize_files.cpp
        menus/menus.cpp
        orders/Client.cpp
        orders/Order.cpp
        orders/OrderedProduct.cpp
        positions/Barista.cpp
        positions/Employee.cpp
        positions/Manager.cpp
        positions/Waiter.cpp
        products/Product.cpp
        reports/DailyReport.cpp
        special-events/ProductsAndServices.cpp
        special-events/SpecialEvent.cpp
)
