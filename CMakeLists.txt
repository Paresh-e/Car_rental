cmake_minimum_required(VERSION 3.31)
project(car_rental)

set(CMAKE_CXX_STANDARD 26)

add_executable(car_rental main.cpp

        Entity/User.cpp
        Entity/User.h

        Entity/Car.cpp
        Entity/Car.h

        Entity/Date.cpp
        Entity/Date.h

        Entity/Maintenance.cpp
        Entity/Maintenance.h

        Entity/rental.cpp
        Entity/rental.h

        Entity/reservation.cpp
        Entity/reservation.h


        Panels/Panel.cpp
        Panels/Panel.h


        Containers/DoublyLL.tpp
        Containers/DoublyLL.h

        Containers/MinHeap.tpp
        Containers/MinHeap.h

        Containers/AVL.tpp
        Containers/AVL.h

        Containers/Hashtable.tpp
        Containers/Hashtable.h


        Managers/MaintenanceManager.cpp
        Managers/MaintenanceManager.h

        Managers/ReservationManager.cpp
        Managers/ReservationManager.h

        Managers/CarManger.cpp
        Managers/CarManger.h

        Managers/UserManager.cpp
        Managers/UserManager.h
)

