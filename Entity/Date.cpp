//
// Created by asus on 2/9/2026.
//

#include "Date.h"


Date::Date() : year(0), month(0), day(0) {}

Date::Date(int y, int m, int d)
        : year(y), month(m), day(d) {}

bool Date::operator<(const Date& other) const
{
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator==(const Date& other) const
{
    return year == other.year &&
           month == other.month &&
           day == other.day;
}
