//
// Created by asus on 2/11/2026.
//

#include "MaintenanceManager.h"
#include <iostream>
#include <fstream>
#include <string>
void MaintenanceManager::LoadFF()
{
    ifstream in("maintenance.txt");
    if (!in.is_open()) {
        cout << "Maintenance file not found. Starting empty.\n";
        return;
    }

    string line;

    while (getline(in, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string carIdStr, description, costStr ,EntryDate,ExitDate;
        getline(ss, name, '|');
        getline(ss, carIdStr, '|');
        getline(ss, description, '|');
        getline(ss, costStr, '|');
        getline(ss, EntryDate, '|');
        getline(ss, ExitDate, '|');
        Maintenance m;
        m.CarId = stoi(carIdStr);
        m.Description = description;
        m.Cost = stod(costStr);
        m.Technician = name;
        m.Entry = Date::from_string(EntryDate);
        m.Exit = Date::from_string(ExitDate);
        MainS.pushBack(m);
    }

    in.close();
}


void MaintenanceManager::SaveTF()
{
    ofstream out("maintenance.txt");
    if (!out.is_open()) {
        cout << "Error opening maintenance file for writing.\n";
        return;
    }

    auto * temp = MainS.getHead();
    while (temp != nullptr)
    {
        out << this->name<<"|"
        <<temp->data.CarId << "|"
        << temp->data.Description << "|"
        << temp->data.Cost <<"|"
        << temp->data.Entry.to_string()<<"|"
        <<temp->data.Exit.to_string()<<"\n";

        temp = temp->next;
    }

    out.close();
}
void MaintenanceManager::displayAllMaintenance()
{
    if (MainS.isEmpty()) {
        cout << "No maintenance records.\n";
        return;
    }

    auto* node = MainS.getHead();
    while (node != nullptr) {
        Maintenance& m = node->data;
        if(m.Technician == name){
            cout<<"You:: ";
        }else{
            cout<<m.Technician;
        }
        cout << "Car ID: " << m.CarId
             << " | Description: " << m.Description
             << " | Cost: " << m.Cost
             << " | Date(Entry): " << m.Entry.to_string()
             << " | Date(Exit): " << m.Exit.to_string()
             << endl;

        node = node->next;
    }
}

MaintenanceManager::MaintenanceManager(string a) {
fileName = a ;
}
