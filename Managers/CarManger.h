//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_CARMANGER_H
#define CAR_RENTAL_CARMANGER_H
#include "../Containers/DoublyLL.h"
#include "../Containers/AVL.h"
#include "../Entity/Car.h"
using namespace std;
class CarManager {
    private:
    DoublyLinkedList<Car> carsList;
    AVLTree<Car*> carTree;
    string fileName;

public:
    static int IDcounter;
    CarManager(string fileName = "cars.txt");

    void loadCarsFromFile();
    void saveCarsToFile();

    void addCar(const Car& car);
    bool removeCarByID(int id);

    Car* searchCarByID(int id);
    void displayAllCars();

    DoublyLinkedList<Car>* getCarsList();


};
#endif //CAR_RENTAL_CARMANGER_H