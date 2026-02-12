//
// Created by asus on 2/11/2026.
//

#ifndef CAR_RENTAL_MAINTENANCEMANAGER_H
#define CAR_RENTAL_MAINTENANCEMANAGER_H


#include "../Containers/DoublyLL.h"
#include "../Entity/Maintenance.h"

class MaintenanceManager {
public:

    string name;
    string fileName;
    DoublyLinkedList<Maintenance> MainS;
    void LoadFF();
    void SaveTF();
    void displayAllMaintenance();
    MaintenanceManager(string a ="F:/projects/car_rental/maintenance.txt" );
};



#endif //CAR_RENTAL_MAINTENANCEMANAGER_H
