//
// Created by asus on 2/11/2026.
//

#ifndef CAR_RENTAL_MAINTENANCEMANAGER_H
#define CAR_RENTAL_MAINTENANCEMANAGER_H


#include "../Containers/DoublyLL.h"
#include "../Entity/Maintenance.h"

class MaintenanceManager {
public:
    DoublyLinkedList<Maintenance> MainS;
    bool LoadFF(string = "maintenance.txt");
    void SaveTF(string = "maintenance.txt");
    void displayAllMaintenance();
};


#endif //CAR_RENTAL_MAINTENANCEMANAGER_H
