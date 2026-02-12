//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_CAR_H
#define CAR_RENTAL_CAR_H
#include <string>
#include "reservation.h"

#include "../Containers/MinHeap.h"

enum CarStatus
{
    AVAILABLE,
    RESERVED,
    RENTED,
    MAINTENANCE
};

class Car
{
public:

    int id;
    std::string brand;
    std::string type;
    double pricePerDay;
    CarStatus status;
    MinHeap<Reservation*> waitingQueue;
    Car();
    Car(
        const std::string& brand,
        const std::string& type,
        double pricePerDay,
        CarStatus aw);
    ~Car();
    CarStatus static intToStatus(int);
     static string statusTostring(CarStatus a);
};

#endif //CAR_RENTAL_CAR_H
