#include "Panel.h"
#include <iostream>
#include <limits>
#include <functional>
using namespace std;

Panel::Panel(CarManager& cm, UserManager& um, ReservationManager& rm,MaintenanceManager& mm)
    : carManager(cm), userManager(um), reservationManager(rm), maintenanceManager(mm)
{}

void Panel::showInitialMenu()
{
    cout << "================ Car Rental Panel ================\n";
    cout << "1) Login\n";
    cout << "2) Continue as Guest\n";
    cout << "0) Exit\n";
    cout << "Enter choice: ";
}
//customer
void Panel::handleGuest()
{
    while (true)
    {
        cout << "\n--- Guest Menu ---\n";
        cout << "1) Show all cars (ID, Brand, Type, Price, Status)\n";
        cout << "2) Show car details by ID\n";
        cout << "3) Register (Customer / Maintenance)\n";
        cout << "0) Back to main menu\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {

            cout << "\nList of cars:\n";
            carManager.displayAllCars();
        }
        else if (choice == 2) {
            cout << "Enter Car ID: ";
            int id;
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID.\n";
                continue;
            }

            Car* c = carManager.searchCarByID(id);
            if (c == nullptr) {
                cout << "Car with ID " << id << " not found.\n";
            } else {
                cout << "\nCar details:\n";
                cout << "ID: " << c->id << "\n";
                cout << "Brand: " << c->brand << "\n";
                cout << "Type: " << c->type << "\n";
                cout << "Price per day: " << c->pricePerDay << "\n";
                cout << "Status: " << c->status << "\n";
            }
        }
        else if (choice == 3)
        {
    handleRegister();
        }
        else {
            cout << "Unknown option. Try again.\n";
        }
    }
}
//usermanager
void Panel::handleRegister()
{
    string username;
    string password;
    int roleChoice;

    cout << "\n--- Register Menu ---\n";
    cout << "1) Customer\n";
    cout << "2) Maintenance (Staff)\n";
    cout << "Enter choice: ";
    if (!(cin >> roleChoice)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    UserRole role;
    if (roleChoice == 1)
        role = CUSTOMER;
    else if (roleChoice == 2)
        role = STAFF;
    else {
        cout << "Invalid role.\n";
        return;
    }

    cout << "Enter username: ";
    if (!(cin >> username)) {
        cout << "Invalid username.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // چک یوزرنیم تکراری
    if (userManager.searchUserByUsername(username) != nullptr) {
        cout << "This username already exists.\n";
        return;
    }

    cout << "Enter password: ";
    if (!(cin >> password)) {
        cout << "Invalid password input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // هش کردن رمز (باید همان الگوریتمی باشد که در login استفاده شد)
    string passwordHash = to_string(std::hash<string>{}(password));

    bool success = userManager.registerUser(username, passwordHash, role);

    if (success) {
        cout << "Registration successful!\n";
        // در صورت تمایل می‌توان اینجا کاربر را اتوماتیک لاگین کرد:
        // User* u = userManager.searchUserByUsername(username);
        // if (u) handleCustomer(u);
    }
    else
        cout << "Registration failed!\n";
}
void Panel::handleCustomer(User* currentUser)
{
    if (currentUser == nullptr) return;

    using std::cout;
    using std::cin;
    using std::endl;

    cout << "\nWelcome, " << currentUser->username << " (Customer)\n";

    while (true)
    {
        cout << "\n--- Customer Menu ---\n";
        cout << "1) View all cars\n";
        cout << "2) Make a reservation\n";
        cout << "3) View my reservations\n";
        cout << "4) Pay for a reservation\n";
        cout << "5) Cancel a reservation\n";
        cout << "0) Logout\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        // consume leftover newline so getline works later
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "Logging out...\n";
            break;
        }
        else if (choice == 1) {
            cout << "\n--- Available Cars ---\n";
            carManager.displayAllCars();
        }
        else if (choice == 2) {
            // Make a reservation
            int carID;
            cout << "Enter Car ID to reserve: ";
            if (!(cin >> carID)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid Car ID.\n";
                continue;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string fromStr, toStr;
            cout << "Enter start date (YYYY-MM-DD): ";
            std::getline(cin, fromStr);
            cout << "Enter end date (YYYY-MM-DD): ";
            std::getline(cin, toStr);

            // validate car exists
            Car* carPtr = carManager.searchCarByID(carID);
            if (!carPtr) {
                cout << "Car with ID " << carID << " not found.\n";
                continue;
            }

            // build reservation
            Reservation r;
            r.reservationID = reservationManager.generateNewReservationID();
            r.userID = currentUser->id;
            r.carID = carID;

            // parse dates (assumes Date::from_string exists)
            try {
                r.requestDate = Date::today(); // اگر ندارید می‌توانید از reservedFrom استفاده کنید
                r.reservedFrom = Date::from_string(fromStr);
                r.reservedTo   = Date::from_string(toStr);
            } catch (...) {
                cout << "Invalid date format. Use YYYY-MM-DD.\n";
                continue;
            }

            // basic validation: end after start
            if (!(r.reservedFrom < r.reservedTo) && !(r.reservedFrom == r.reservedTo)) {
                cout << "End date must be same or after start date.\n";
                continue;
            }

            r.status = PENDING;
            r.totalCost = reservationManager.calculateReservationCost(r);
            r.paid = false;

            reservationManager.addReservation(r);
            // اگر addReservation داخل خودش save نمی‌کند اینجا صدا بزن:
            // reservationManager.saveToFile("reservations.txt");

            cout << "Reservation created. ID: " << r.reservationID
                 << " Total cost: " << r.totalCost << " (status: PENDING)\n";
            cout << "Use 'Pay for a reservation' to pay and confirm.\n";
        }
        else if (choice == 3) {
            // View user's reservations
            auto myRes = reservationManager.getReservationsByUser(currentUser->id);
            if (myRes.empty()) {
                cout << "You have no reservations.\n";
            } else {
                cout << "\n--- My Reservations ---\n";
                for (auto rp : myRes) {
                    cout << "ResID: " << rp->reservationID
                         << "  CarID: " << rp->carID
                         << "  From: " << rp->reservedFrom.to_string()
                         << "  To: "   << rp->reservedTo.to_string()
                         << "  Status: " << rp->status
                         << "  Paid: " << (rp->paid ? "Yes" : "No")
                         << "  Total: " << rp->totalCost
                         << "\n";
                }
            }
        }
        else if (choice == 4) {
            // Pay for reservation
            int rid;
            cout << "Enter reservation ID to pay: ";
            if (!(cin >> rid)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid reservation ID.\n";
                continue;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // payment (simulated)
            bool ok = reservationManager.payReservation(rid);
            if (ok) {
                cout << "Payment successful. Reservation confirmed and car marked as RENTED.\n";
            } else {
                cout << "Payment failed (reservation not found or not payable).\n";
            }
        }
        else if (choice == 5) {
            // Cancel reservation
            int rid;
            cout << "Enter reservation ID to cancel: ";
            if (!(cin >> rid)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid reservation ID.\n";
                continue;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            bool ok = reservationManager.cancelReservation(rid);
            if (ok) {
                cout << "Reservation canceled successfully.\n";
            } else {
                cout << "Cancellation failed (not found or cannot cancel).\n";
            }
        }
        else {
            cout << "Unknown option. Try again.\n";
        }
    } // end while
}
void Panel::run()
{
    while (true)
    {
        showInitialMenu();

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) {
                cout << "\nInput closed. Exiting.\n";
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        // consume leftover newline so subsequent getline/>> behave cleanly
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "Exiting. Bye!\n";
            break;
        }
        else if (choice == 1) {
            // --- Login flow ---
            string username;
            cout << "Username: ";
            if (!(cin >> username)) {
                cout << "Invalid username input.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // First check whether user exists and whether blocked
            User* u = userManager.searchUserByUsername(username);
            if (u == nullptr) {
                cout << "Invalid username or password.\n";
                continue;
            }
            if (u->blocked) {
                cout << "Your account is blocked. Contact admin.\n";
                continue;
            }

            string password;
            cout << "Password: ";
            if (!(cin >> password)) {
                cout << "Invalid password input.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // Hash password in UI (must match register hashing)
            string passwordHash = to_string(std::hash<string>{}(password));

            if (!userManager.login(username, passwordHash)) {
                // login failed: wrong password (we already know user exists and not blocked)
                cout << "Invalid username or password.\n";
            } else {
                // login successful
                User* user = userManager.searchUserByUsername(username); // same pointer u
                if (user->role == CUSTOMER)
                    handleCustomer(user);
                else if (user->role == STAFF)
                    handleStaff(user);
                else if (user->role == MANAGER)
                    handleManager(user);
                else if (user->role == TECHNICIAN)
                    handleMaintenance(user);

            }
        }
        else if (choice == 2) {
            handleGuest();
        }
        else {
            cout << "Unknown option. Try again.\n";
        }
    }
}
void Panel::handleManager(User* currentUser)
{
    cout << "\nWelcome, " << currentUser->username << " (Manager)\n";

    while (true)
    {
        cout << "\n--- Manager Menu ---\n";
        cout << "1) View all users\n";
        cout << "2) Block user\n";
        cout << "3) Add Staff\n";
        cout << "4) Add Maintenance\n";
        cout << "5) Save system backup\n";
        cout << "0) Logout\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) break;

        else if (choice == 1) {
            userManager.displayAllUsers();
        }

        else if (choice == 2) {
            string username;
            cout << "Enter username to block: ";
            cin >> username;

            User* u = userManager.searchUserByUsername(username);
            if (!u) {
                cout << "User not found.\n";
            } else {
                u->blocked = true;
                userManager.saveUsersToFile();
                cout << "User blocked successfully.\n";
            }
        }

        else if (choice == 3 || choice == 4) {

            string username, password;

            cout << "Enter username: ";
            cin >> username;

            if (userManager.searchUserByUsername(username)) {
                cout << "Username already exists.\n";
                continue;
            }

            cout << "Enter password: ";
            cin >> password;

            string hash = to_string(std :: hash<string>{}(password));

            UserRole role = (choice == 3) ? STAFF : TECHNICIAN;

            if (userManager.registerUser(username, hash, role)) {
                cout << "User created successfully.\n";
            } else {
                cout << "Creation failed.\n";
            }
        }

        else if (choice == 5) {
            userManager.saveUsersToFile();
            carManager.saveCarsToFile();
            cout << "Backup saved successfully.\n";
        }
    }
}

void Panel::handleStaff(User* currentUser)
{
    cout << "\nWelcome, " << currentUser->username << " (Staff)\n";

    while (true)
    {
        cout << "\n--- Staff Menu ---\n";
        cout << "1) Convert reservation to rented\n";
        cout << "2) Return car\n";
        cout << "3) Process reservation queue\n";
        cout << "4) Add new car\n";
        cout << "5) Remove car\n";
        cout << "0) Logout\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) break;

        else if (choice == 1) {
            int rid;
            cout << "Reservation ID: ";
            cin >> rid;

            if (reservationManager.convertReservationToRented(rid))
                cout << "Converted successfully.\n";
            else
                cout << "Failed.\n";
        }

        else if (choice == 2) {
            int rid;
            cout << "Reservation ID: ";
            cin >> rid;

            if (reservationManager.returnCar(rid))
                cout << "Car returned successfully.\n";
            else
                cout << "Failed.\n";
        }

        else if (choice == 3) {
            reservationManager.processReservationQueue();
            cout << "Queue processed.\n";
        }

        else if (choice == 4) {
            Car newCar;
            cout << "Enter ID: ";
            cin >> newCar.id;
            cout << "Brand: ";
            cin >> newCar.brand;
            cout << "Type: ";
            cin >> newCar.type;
            cout << "Price per day: ";
            cin >> newCar.pricePerDay;
            newCar.status = CarStatus::AVAILABLE;

            carManager.addCar(newCar);
            carManager.saveCarsToFile();

            cout << "Car added successfully.\n";
        }

        else if (choice == 5) {
            int id;
            cout << "Car ID to remove: ";
            cin >> id;

            if (carManager.removeCarByID(id)) {
                carManager.saveCarsToFile();
                cout << "Car removed.\n";
            } else {
                cout << "Car not found.\n";
            }
        }
    }
}

void Panel::handleMaintenance(User* currentUser)
{
    cout << "\nWelcome, " << currentUser->username << " (Maintenance)\n";

    while (true)
    {
        cout << "\n--- Maintenance Menu ---\n";
        cout << "1) Register repair\n";
        cout << "2) View maintenance records\n";
        cout << "0) Logout\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        else if (choice == 1) {

            Maintenance m;

            cout << "Car ID: ";
            cin >> m.CarId;

            cout << "Description: ";
            cin >> m.Description;

            cout << "Cost: ";
            cin >> m.Cost;

            maintenanceManager.MainS.pushBack(m);
            maintenanceManager.SaveTF();

            Car* car = carManager.searchCarByID(m.CarId);
            if (car)
                car->status = CarStatus::MAINTENANCE;

            carManager.saveCarsToFile();

            cout << "Repair registered.\n";
        }

        else if (choice == 2) {
            maintenanceManager.displayAllMaintenance();
        }
    }
}

