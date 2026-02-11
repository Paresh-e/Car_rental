#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <string>
#include "../Entity/Reservation.h"
#include "../Containers/MinHeap.h"

class ReservationManager
{
private:
    MinHeap<Reservation> reservations;

public:
    void addReservation( Reservation& r);
    Reservation getNextReservation();
    bool empty() const;

    void loadFromFile(const std::string& filename="Reservations.txt");
    void saveToFile(const std::string& filename="Reservations.txt") const;
    ReservationManager();
};

#endif
