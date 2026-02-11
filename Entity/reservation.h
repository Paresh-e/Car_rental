#ifndef CAR_RENTAL_RESERVATION_H
#define CAR_RENTAL_RESERVATION_H

#include "Date.h"

enum ReservationStatus
{
    PENDING,
    CONFIRMED,
    CANCELED
};

class Reservation
{
public:
    int reservationID;
    int userID;
    int carID;
    double totalCost;
    bool paid;
    Date requestDate;     
    Date reservedFrom;   
    Date reservedTo;      

    ReservationStatus status;

    Reservation();

    Reservation(int reservationID,
                int userID,
                int carID,
                const Date& requestDate,
                const Date& reservedFrom,
                const Date& reservedTo,
                ReservationStatus status);
    bool operator<(const Reservation& other) const
    {
        if (status != other.status)
            return status == PENDING;

        return requestDate < other.requestDate;
    }
};

#endif //CAR_RENTAL_RESERVATION_H