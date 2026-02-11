//
// Created by asus on 2/9/2026.
//

#ifndef CAR_RENTAL_DATE_H
#define CAR_RENTAL_DATE_H

#include <string>
#include <sstream>
#include <ctime>
using namespace std;
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

    string to_string() const;
    static Date from_string(const string& s);

    // برگرداندن تاریخ امروز سیستم
    static Date today();
};

#endif //CAR_RENTAL_DATE_H