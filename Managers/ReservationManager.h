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
    void addReservation(const Reservation& r);
    Reservation getNextReservation();
    bool empty() const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};

#endif
