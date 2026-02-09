//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_CAR_H
#define CAR_RENTAL_CAR_H
#include <string>
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
    static int IDcounter;
    int id;
    std::string brand;
    std::string type;
    double pricePerDay;
    CarStatus status;

    Car();
    Car(int id,
        const std::string& brand,
        const std::string& type,
        double pricePerDay);
};

#endif //CAR_RENTAL_CAR_H
