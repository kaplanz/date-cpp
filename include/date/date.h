// File:        date.h
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     03 Dec 2019
// SPDX-License-Identifier: NONE

#pragma once

#include <iostream>
#include <string>

class Duration;
class Formatter;

class Date {
    friend class Formatter;

private:
    // Data members
    long epochSeconds; // epoch time in seconds
    char tz;           // DST and time zone info

public:
    // Constructors
    Date();
    Date(const Date &date) = default;
    Date(long epochSeconds);

    // Destructor
    ~Date() = default;

    // Accessors
    long epoch() const;
    int timezone() const;
    bool DST() const;
    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;
    int second() const;

    // Mutators
    long epoch(const long epochSeconds);
    int timezone(const int tz);
    bool DST(const bool DST);

    // Operators
    Date &operator=(const Date &rhs) = default;
    Date operator+(const Duration &rhs) const;
    Duration operator-(const Date &rhs) const;
    bool operator==(const Date &rhs) const;
    bool operator!=(const Date &rhs) const;
    bool operator<(const Date &rhs) const;
    bool operator<=(const Date &rhs) const;
    bool operator>=(const Date &rhs) const;
    bool operator>(const Date &rhs) const;
    friend std::ostream &operator<<(std::ostream &lhs, const Date &rhs);
};
