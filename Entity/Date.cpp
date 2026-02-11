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

string Date::to_string() const
{
    return std::to_string(this->year) + "|" +
           std::to_string(this->month) + "|" +
           std::to_string(this->day);
}

Date Date::from_string(const string& s)
{
    stringstream ss(s);
    string d, m, y;
    std::getline(ss, d, '|');
    std::getline(ss, m, '|');
    std::getline(ss, y, '|');
    return Date(std::stoi(y), std::stoi(m), std::stoi(d));
}

Date Date::today()
{
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return Date(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
}