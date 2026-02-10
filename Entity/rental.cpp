#include "Rental.h"

Rental::Rental()
{
    rentalID = 0;
    userID = 0;
    carID = 0;
    totalCost = 0;
    status = ACTIVE;
}

Rental::Rental(int rentalID,
               int userID,
               int carID,
               const Date& startDate,
               const Date& endDate,
               double totalCost,
            RentalStatus status
            )
{
    this->rentalID = rentalID;
    this->userID = userID;
    this->carID = carID;
    this->startDate = startDate;
    this->endDate = endDate;
    this->totalCost = totalCost;
    this->status = status;
}