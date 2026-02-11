#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <string>
#include <vector>
#include "../Entity/Reservation.h"
#include "../Containers/MinHeap.h"
#include "../Containers/DoublyLL.h"
#include "CarManger.h" 

class ReservationManager
{
private:
    MinHeap<Reservation*> reservationsHeap;     
    DoublyLinkedList<Reservation> resList;       
    CarManager& carManager; 

public:
    ReservationManager(CarManager& cm);
    // public:
int generateNewReservationID();
    
    void addReservation(const Reservation& r);

   
    std::vector<Reservation*> getReservationsByUser(int userID);

   
    Reservation* findReservationByID(int reservationID);

    
    bool payReservation(int reservationID);

  
    bool cancelReservation(int reservationID);

   
    double calculateReservationCost(const Reservation& r);

    
    bool empty() const;

    
    Reservation* getNextReservation();

    
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};

#endif