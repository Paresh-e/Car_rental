//
// Created by asus on 2/11/2026.
//

#ifndef CAR_RENTAL_MAINTENANCE_H
#define CAR_RENTAL_MAINTENANCE_H


#include "Date.h"

class Maintenance {
public:
    Date Entry;
    Date Exit;
    string Description;
    double Cost;
    int CarId;
    int UserId;
    Maintenance();
    Maintenance(Date&,Date&,string&,double,int,int);

};


#endif //CAR_RENTAL_MAINTENANCE_H