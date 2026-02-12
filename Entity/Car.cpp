//
// Created by asus on 2/9/2026.
//

#include "Car.h"
#include "../Managers/CarManger.h"
#include "../Entity/reservation.h"
Car::Car()
{
    id = ++CarManager::IDcounter;
    pricePerDay = 0;
    status = AVAILABLE;
}

Car::Car(const std::string& brand,
         const std::string& type,
         double pricePerDay,
         CarStatus aw)
{
    this->id = id;
    this->brand = brand;
    this->type = type;
    this->pricePerDay = pricePerDay;
    this->status = aw;
    id = ++CarManager::IDcounter;
}
Car::~Car() {
    while(!waitingQueue.isEmpty()){
        delete waitingQueue.pop();
    }
}

CarStatus Car::intToStatus(int a) {

    if (a ==1) {return CarStatus::RESERVED;}
    else if (a ==2) {return CarStatus::RENTED;}
    else if (a ==3) {return CarStatus::MAINTENANCE;}
    else{return CarStatus::AVAILABLE;}
}

string Car::statusTostring(CarStatus a) {
    switch (a)
    {
        case AVAILABLE:   return "AVAILABLE";
        case RESERVED:    return "RESERVED";
        case RENTED:      return "RENTED";
        case MAINTENANCE: return "MAINTENANCE";
        default:          return "UNKNOWN";
    }
}


