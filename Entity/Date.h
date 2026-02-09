//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_DATE_H
#define CAR_RENTAL_DATE_H


#pragma once

class Date
{
public:
    int year;
    int month;
    int day;

    Date();
    Date(int y, int m, int d);

    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
};


#endif //CAR_RENTAL_DATE_H
