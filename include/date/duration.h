// File:        duration.h
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     23 Dec 2019
// SPDX-License-Identifier: NONE

#pragma once

#include "date/date.h"

class Duration {
private:
    // Data members
    long durationSeconds; // duration time in seconds

public:
    // Constructors
    Duration();
    Duration(const Duration &duration) = default;
    Duration(long durationSeconds);

    // Destructor
    ~Duration() = default;

    // Accessors
    int years() const;  // average years
    int months() const; // average months
    int weeks() const;
    int days() const;
    int hours() const;
    int minutes() const;
    long seconds() const;

    // Mutators
    void addYears(int years);   // average years
    void setYears(int years);   // average years
    void addMonths(int months); // average months
    void setMonths(int months); // average months
    void addWeeks(int weeks);
    void setWeeks(int weeks);
    void addDays(int days);
    void setDays(int days);
    void addHours(int hours);
    void setHours(int hours);
    void addMinutes(int minutes);
    void setMinutes(int minutes);
    void addSeconds(long seconds);
    void setSeconds(long seconds);

    // Operators
    Duration &operator=(const Duration &rhs) = default;
    Duration operator+(const Duration &rhs) const;
    friend Date Date::operator+(const Duration &rhs) const;
    Duration operator-(const Duration &rhs) const;
    Duration operator*(const double &rhs) const;
    friend Duration operator*(const double &lhs, const Duration &rhs);
    Duration operator/(const double &rhs) const;
    friend Duration operator/(const double &lhs, const Duration &rhs);
    bool operator==(const Duration &rhs) const;
    bool operator!=(const Duration &rhs) const;
    bool operator<(const Duration &rhs) const;
    bool operator<=(const Duration &rhs) const;
    bool operator>=(const Duration &rhs) const;
    bool operator>(const Duration &rhs) const;
};
