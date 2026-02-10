#include "Reservation.h"

Reservation::Reservation()
{
    reservationID = 0;
    userID = 0;
    carID = 0;
    status = PENDING;
}

Reservation::Reservation(int reservationID,
                         int userID,
                         int carID,
                         const Date& requestDate,
                         const Date& reservedFrom,
                         const Date& reservedTo,
                         ReservationStatus status)
{
    this->reservationID = reservationID;
    this->userID = userID;
    this->carID = carID;
    this->requestDate = requestDate;
    this->reservedFrom = reservedFrom;
    this->reservedTo = reservedTo;
    this->status = status;
}