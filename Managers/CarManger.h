//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_CARMANGER_H
#define CAR_RENTAL_CARMANGER_H
#include "../Containers/DoublyLL.h"
#include "../Containers/AVL.h"
#include "../Entity/Car.h"
class CarManger {
public:
    DoublyLinkedList<Car> Cars;

};


#endif //CAR_RENTAL_CARMANGER_H