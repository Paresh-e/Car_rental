#ifndef PANEL_H
#define PANEL_H

#include <string>
#include "CarManger.h" 
#include "UserManager.h"
#include "ReservationManager.h"
#include <ctime>
class Panel {
private:
    CarManager& carManager;
    UserManager& userManager;
    ReservationManager& reservationManager;
    void handleRegister();
    void showInitialMenu();
    void handleGuest();
    void handleCustomer(User* currentUser);

public:
    
    Panel(CarManager& cm, UserManager& um, ReservationManager& rm );

   
    void run();
};

#endif // PANEL_H