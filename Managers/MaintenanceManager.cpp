//
// Created by asus on 2/11/2026.
//

#include "MaintenanceManager.h"
#include <iostream>
#include <fstream>
#include <string>
bool MaintenanceManager::LoadFF(string filename) {
    ifstream file(filename);
    if (!file.good())
        return false;
    string line;

    while (getline(file, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        Maintenance temp =  Maintenance();

        string EnDay, EnMonth, EnYear;
        ss >> EnDay >> EnMonth >> EnYear;
        temp.Entry.day = std::stoi(EnDay);
        temp.Entry.month = std::stoi(EnMonth);
        temp.Entry.year = std::stoi(EnYear);
        ss.ignore(1, '|');
        string ExDay, ExMonth, ExYear;
        ss >> ExDay >> ExMonth >> ExYear;
        temp.Exit.day = std::stoi(ExDay);
        temp.Exit.month = std::stoi(ExMonth);
        temp.Exit.year = std::stoi(ExYear);
        ss.ignore(1, '|');

        getline(ss, temp.Description, '|');
        ss >> temp.Cost;
        ss.ignore(1, '|');
        ss >> temp.CarId;
        ss.ignore(1, '|');
        ss >> temp.UserId;
        ss.ignore(1, '|');

        MainS.pushBack(temp);

    }
    file.close();
    return true;
}

void MaintenanceManager::SaveTF(string filename) {
    ofstream file(filename, ios::app); // append
    if (!file) {
        cout << "file Maintenance cannot be open";
        return;
    }
    auto curr = MainS.getHead();

    while (curr != nullptr)
    {
    file << curr->data.Entry.day << " " << curr->data.Entry.month << " " << curr->data.Entry.year << "|"
         << curr->data.Entry.day << " " << curr->data.Entry.month << " " << curr->data.Entry.year << "|"
         << curr->data.Description << "|"
         << curr->data.Cost << "|"
         << curr->data.CarId << "|"
         << curr->data.UserId << endl;


        curr = curr->next;
    }
    file.close();
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

        cout << "Car ID: " << m.CarId
             << " | Description: " << m.Description
             << " | Cost: " << m.Cost
             << " | Date(Entry): " << m.Entry.to_string()
             << " | Date(Exit): " << m.Exit.to_string()
             << endl;

        node = node->next;
    }
}
