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
bool Date::operator>(const Date& other) const
{
    if (year != other.year) return year > other.year;
    if (month != other.month) return month > other.month;
    return day > other.day;
}
bool Date::operator==(const Date& other) const
{
    return year == other.year &&
           month == other.month &&
           day == other.day;
}
int Date::daysFrom(const Date& other) const
{
    std::tm a = {};
    a.tm_year = year - 1900;
    a.tm_mon  = month - 1;
    a.tm_mday = day;

    std::tm b = {};
    b.tm_year = other.year - 1900;
    b.tm_mon  = other.month - 1;
    b.tm_mday = other.day;

    time_t timeA = std::mktime(&a);
    time_t timeB = std::mktime(&b);

    const int secondsPerDay = 60 * 60 * 24;

    return static_cast<int>((timeA - timeB) / secondsPerDay);
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