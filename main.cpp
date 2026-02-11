#include <iostream>

#include "Managers/CarManger.h"
#include "Managers/UserManager.h"
#include "Managers/ReservationManager.h"
#include "Managers/MaintenanceManager.h"

#include "Panels/Panel.h"

using namespace std;

int main()
{
    CarManager carManager("Cars.txt");
    UserManager userManager("Users.txt");
    MaintenanceManager maintenanceManager;

    ReservationManager reservationManager(carManager);

    // Load data
    carManager.loadCarsFromFile();
    userManager.loadUsersFromFile();
    maintenanceManager.LoadFF("maintenance.txt");
    reservationManager.loadFromFile("Reservations.txt");

    Panel panel(carManager, userManager, reservationManager, maintenanceManager);
    panel.run();

    return 0;
}