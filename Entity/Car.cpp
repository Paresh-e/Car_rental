//
// Created by asus on 2/9/2026.
//

#include "Car.h"
int Car::IDcounter = 0 ;
Car::Car()
{
    id = ++IDcounter;
    pricePerDay = 0;
    status = AVAILABLE;
}

Car::Car(int id,
         const std::string& brand,
         const std::string& type,
         double pricePerDay)
{
    this->id = id;
    this->brand = brand;
    this->type = type;
    this->pricePerDay = pricePerDay;
    this->status = AVAILABLE;
}
