//
// Created by asus on 2/10/2026.
//

#include "ReservationManager.h"
#include <fstream>
#include <stdexcept>
#include <cmath>

ReservationManager::ReservationManager(CarManager& cm)
    : carManager(cm) {}


void ReservationManager::addReservation(const Reservation& r)
{
    Reservation copy = r;
    resList.pushBack(copy);
    Reservation* ptr = &(resList.getTail()->data);
    reservationsHeap.push(ptr);

    // ذخیره به فایل بلافاصله بعد از اضافه شدن
    saveToFile("reservations.txt");
}

int ReservationManager::generateNewReservationID()
{
    int maxID = 0;
    auto node = resList.getHead();
    while (node != nullptr)
    {
        if (node->data.reservationID > maxID)
            maxID = node->data.reservationID;
        node = node->next;
    }
    return maxID + 1;
}
std::vector<Reservation*> ReservationManager::getReservationsByUser(int userID)
{
    std::vector<Reservation*> result;
    auto node = resList.getHead();

    while (node != nullptr)
    {
        if (node->data.userID == userID)
            result.push_back(&(node->data));

        node = node->next;
    }

    return result;
}


Reservation* ReservationManager::findReservationByID(int reservationID)
{
    auto node = resList.getHead();
    while (node != nullptr)
    {
        if (node->data.reservationID == reservationID)
            return &(node->data);

        node = node->next;
    }
    return nullptr;
}


bool ReservationManager::payReservation(int reservationID)
{
    Reservation* r = findReservationByID(reservationID);
    if (r == nullptr) return false;
    if (r->status != PENDING) return false; // فقط قابل پرداخت در وضعیت PENDING

    // mark as paid
    r->paid = true;
    r->status = CONFIRMED;

    // تبدیل وضعیت خودرو به RENTED
    Car* car = carManager.searchCarByID(r->carID);
    if (car) {
        car->status = RENTED;
        // ذخیره تغییرات خودرو در فایل
        carManager.saveCarsToFile();
    }

    // ذخیره تغییرات رزرو در فایل
    saveToFile("reservations.txt");

    return true;
}


bool ReservationManager::cancelReservation(int reservationID)
{
    Reservation* r = findReservationByID(reservationID);
    if (r == nullptr) return false;
    if (r->status != PENDING) return false; // نمی‌توان رزروی را که تایید یا اجرا شده لغو کرد

    r->status = CANCELED;
    saveToFile("reservations.txt");
    return true;
}

double ReservationManager::calculateReservationCost(const Reservation& r)
{
    Car* car = carManager.searchCarByID(r.carID);
    if (!car) return 0;

    int days = (r.reservedTo.year*365 + r.reservedTo.month*30 + r.reservedTo.day)
             - (r.reservedFrom.year*365 + r.reservedFrom.month*30 + r.reservedFrom.day);
    if (days <= 0) days = 1;

    return car->pricePerDay * days;
}

// چک کردن خالی بودن هیپ
bool ReservationManager::empty() const
{
    return reservationsHeap.isEmpty();
}

// گرفتن رزرو بعدی از هیپ
Reservation* ReservationManager::getNextReservation()
{
    if (reservationsHeap.isEmpty())
        throw std::runtime_error("No reservations");

    return reservationsHeap.pop();
}

// بارگذاری از فایل
void ReservationManager::loadFromFile(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error("Cannot open file");

    while (!in.eof())
    {
        Reservation r;
        int status;

        in >> r.reservationID >> r.userID >> r.carID;
        if (in.fail()) break;

        std::string reqDate, fromDate, toDate;
        in >> reqDate >> fromDate >> toDate >> status;

        r.requestDate = Date::from_string(reqDate);
        r.reservedFrom = Date::from_string(fromDate);
        r.reservedTo = Date::from_string(toDate);
        r.status = static_cast<ReservationStatus>(status);

        addReservation(r);
    }

    in.close();
}

// ذخیره در فایل
void ReservationManager::saveToFile(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out)
        throw std::runtime_error("Cannot open file");

    auto node = resList.getHead();
    while (node)
    {
        Reservation r = node->data;

        out << r.reservationID << " "
            << r.userID << " "
            << r.carID << " "
            << r.requestDate.to_string() << " "
            << r.reservedFrom.to_string() << " "
            << r.reservedTo.to_string() << " "
            << r.status
            << "\n";

        node = node->next;
    }

    out.close();
}

bool ReservationManager::convertReservationToRented(int reservationID)
{
    Reservation* r = findReservationByID(reservationID);
    if (!r) return false;

    if (r->status != ReservationStatus::PENDING)
        return false;

    Car* car = carManager.searchCarByID(r->carID);
    if (!car) return false;

    r->status = ReservationStatus::CONFIRMED;
    car->status = CarStatus::RENTED;

    this->saveToFile();
    carManager.saveCarsToFile();

    return true;
}
bool ReservationManager::returnCar(int reservationID)
{
    Reservation* r = findReservationByID(reservationID);
    if (!r) return false;

    if (r->status != ReservationStatus::CONFIRMED)
        return false;

    Car* car = carManager.searchCarByID(r->carID);
    if (!car) return false;

    Date today = Date::today();

    double fine = 0;

    if (today > r->reservedTo) {
        int lateDays = today.daysFrom(r->reservedTo);

        fine = lateDays * car->pricePerDay;    // configurable
    }

    r->status = ReservationStatus::COMPLETED;
    r->paid = false;
    r->totalCost += fine;

    car->status = CarStatus::AVAILABLE;

    saveToFile();
    carManager.saveCarsToFile();

    return true;
}
void ReservationManager::processReservationQueue()
{
    auto* node = carManager.getCarsList()->getHead();

    while (node != nullptr) {

        Car& car = node->data;

        if (car.status == CarStatus::AVAILABLE && !car.waitingQueue.isEmpty()) {

            Reservation* nextRes = car.waitingQueue.pop();

            nextRes->status = ReservationStatus::CONFIRMED;
            car.status = CarStatus::RENTED;

            cout << "Car " << car.id
                 << " assigned to reservation "
                 << nextRes->reservationID << endl;
        }

        node = node->next;
    }

    saveToFile();
    carManager.saveCarsToFile();
}
