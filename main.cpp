#include <iostream>

#include "Managers/CarManger.h"
#include "Managers/UserManager.h"
#include "Managers/ReservationManager.h"
#include "Managers/MaintenanceManager.h"

#include "Panels/Panel.h"
#include <filesystem>
using namespace std;

int main()

{

//    std::cout << std::filesystem::current_path();

        CarManager carManager("Cars.txt");
        UserManager userManager("Users.txt");
        MaintenanceManager maintenanceManager("maintenance.txt");
        ReservationManager reservationManager(carManager);

        // Load data
        carManager.loadCarsFromFile();
        userManager.loadUsersFromFile();
        maintenanceManager.LoadFF();
        reservationManager.loadFromFile();

        Panel panel(carManager, userManager, reservationManager, maintenanceManager);
        panel.run();






    return 0;
}