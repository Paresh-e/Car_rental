//
// Created by asus on 2/11/2026.
//

#include "Maintenance.h"

Maintenance::Maintenance() {

}

Maintenance::Maintenance(Date & En, Date &Ex, string &Des, double Co, int CarId, string UserID) {
    this->Entry = En;
    this->Exit= Ex;
    this->Description = Des;
    this->Cost= Co;
    this->CarId = CarId;
    this->Technician = UserID;

}
