//
// Created by asus on 2/10/2026.
//

#include "ReservationManager.h"
#include "ReservationManager.h"
#include <fstream>
#include <stdexcept>

void ReservationManager::addReservation(const Reservation& r)
{
    reservations.push(r);
}

Reservation ReservationManager::getNextReservation()
{
    if (reservations.isEmpty())
        throw std::runtime_error("No reservations");

    return reservations.pop();
}

bool ReservationManager::empty() const
{
    return reservations.isEmpty();
}
void ReservationManager::loadFromFile(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error("Cannot open file");

    while (!in.eof()) {
        Reservation r;
        int status;

        in >> r.reservationID >> r.userID >> r.carID;
        if (in.fail()) break;
        string reqDate,fromDate,toDate;

        in >> reqDate;
        r.requestDate = Date::from_string(reqDate);
        in >> fromDate;
        r.reservedFrom=Date::from_string(fromDate);

        in >> toDate;

        r.reservedTo = Date::from_string(toDate);
        in >> status;

        r.status = static_cast<ReservationStatus>(status);
        reservations.push(r);
    }

    in.close();
}
void ReservationManager::saveToFile(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out)
        throw std::runtime_error("Cannot open file");

    MinHeap<Reservation> temp = reservations;

    while (!temp.isEmpty()) {
        Reservation r = temp.pop();

        out << r.reservationID << " "
            << r.userID << " "
            << r.carID << "\n";

        out << r.requestDate.to_string() << "\n";
        out << r.reservedFrom.to_string() << "\n";
        out << r.reservedTo.to_string() << "\n";
        out << r.status << "\n";
    }

    out.close();
}
