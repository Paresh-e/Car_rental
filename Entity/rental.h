#ifndef CAR_RENTAL_RENTAL_H
#define CAR_RENTAL_RENTAL_H

#include "Date.h"

class Rental
{
public:
enum RentalStatus
{
    ACTIVE,
    FINISHED,
    CANCELED
};
RentalStatus status;
    int rentalID;

    int userID;   
    int carID;

    Date startDate;
    Date endDate;

    double totalCost;
//    int reservationID;
//
//    int userID;
//    int carID;
//
//    Date requestDate;
//    Date reservedFrom;
//    Date reservedTo;
    Rental();
    Rental(int rentalID, 
           int userID,
           int carID,
           const Date& startDate,
           const Date& endDate,
           double totalCost,
           RentalStatus status
        );
};

#endif 