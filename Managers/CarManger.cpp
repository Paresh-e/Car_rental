//
// Created by asus on 2/9/2026.
//

#include "CarManger.h"
#include "iostream"
#include "fstream"
#include "sstream"

int CarManager::IDcounter = 0 ;
CarManager::CarManager(string fileName)
{
    this->fileName = fileName;
}

void CarManager::loadCarsFromFile()
{
    ifstream inFile(fileName);

    if (!inFile)
    {
        cout << "Error: Cannot open file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        int id;
        string brand;
        string type;
        double price;
        int statusInt;

        ss >> id >> brand >> type >> price >> statusInt;

        Car car(brand, type, price,Car::intToStatus(statusInt));



        carsList.pushBack(car);
        Car* carPtr = &(carsList.getTail()->data);
        carTree.insert(to_string(carPtr->id), carPtr);

        if (id > IDcounter)
            IDcounter = id;
    }

    inFile.close();
}

void CarManager::saveCarsToFile()
{
    ofstream outFile(fileName);

    if (!outFile)
    {
        cout << "Error: Cannot open file for writing: " << fileName << endl;
        return;
    }

    auto node = carsList.getHead();
    
    while (node)
    {
        Car& car = node->data;

        outFile << car.id << " "
                << car.brand << " "
                << car.type << " "
                << car.pricePerDay << " "
                << (int)car.status << endl;

        node = node->next;
    }

    outFile.close();
}

void CarManager::addCar(const Car& car)
{
    carsList.pushBack(car);
    Car* carPtr = &(carsList.getTail()->data);
    carTree.insert(to_string(carPtr->id), carPtr);

}

bool CarManager::removeCarByID(int id)
{
   
    Car* carPtr = carTree.search(to_string(id));
    if (carPtr != nullptr) {
        carTree.remove(to_string(id));
    } else {
        
        return false;
    }

   
    auto node = carsList.getHead();
    while (node != nullptr)
    {
        if (node->data.id == id)
        {
            carsList.remove(node); 
            return true;
        }
        node = node->next;
    }

    return false;
}

Car* CarManager::searchCarByID(int id)
{
    return carTree.search(to_string(id));
}

void CarManager::displayAllCars()
{
    auto node = carsList.getHead();
    while (node)
    {
        Car& car = node->data;
        cout << "ID: " << car.id
             << " Brand: " << car.brand
             << " Type: " << car.type
             << " Price: " << car.pricePerDay
             << " Status: " << Car::statusTostring(car.status)
             << endl;
        node = node->next;
    }
}

DoublyLinkedList<Car>* CarManager::getCarsList()
{
    return &carsList;
}