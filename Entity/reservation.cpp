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

string Reservation::statusTostringRes(ReservationStatus a) {
    switch (a)
    {
        case  PENDING:   return "PENDING";
        case APPROVED:    return "APPROVED";
        case REJECTED:      return "REJECTED";
        case DELIVERED: return "DELIVERED";
        case COMPLETED: return "COMPLETED";
        case CANCELED: return "CANCELED";
        default:          return "UNKNOWN";
    }
}

ReservationStatus  Reservation::intToStatusRes(int a) {
    if (a ==1) {return ReservationStatus::APPROVED;}
    else if (a ==2) {return ReservationStatus::REJECTED;}
    else if (a ==3) {return ReservationStatus::DELIVERED;}
    else if (a ==4) {return ReservationStatus::COMPLETED;}
    else if (a ==5) {return ReservationStatus::CANCELED;}
    else{return ReservationStatus::PENDING;}
}

