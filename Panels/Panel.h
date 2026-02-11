#ifndef PANEL_H
#define PANEL_H

#include <string>
#include "../Managers/CarManger.h"
#include "../Managers/UserManager.h"
#include "../Managers/ReservationManager.h"
#include "../Managers/MaintenanceManager.h"

#include <ctime>
class Panel {
private:
    CarManager& carManager;
    UserManager& userManager;
    ReservationManager& reservationManager;
    MaintenanceManager& maintenanceManager;
    void handleRegister();
    void showInitialMenu();
    void handleGuest();
    void handleCustomer(User* currentUser);
    void handleManager(User* currentUser);
    void handleStaff(User* currentUser);
    void handleMaintenance(User* currentUser);
public:
    
    Panel(CarManager& cm, UserManager& um, ReservationManager& rm ,MaintenanceManager& mm);



    void run();
};

#endif // PANEL_H