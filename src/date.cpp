//
//  date.cpp
//  Date class implementation.
//
//  Created by Zakhary Kaplan on 2019-12-03.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#include <iostream>
#include <string>

#include "date.h"
#include "formatter.h"


// -- Globals --
// Enumerators
enum Month {
    Jan, Feb, Mar, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

// Arrays
const short monthDuration[] = {
    31, 28, 31, 30, 31, 30, // Jan - Jun
    31, 31, 30, 31, 30, 31  // Jul - Dec
};


// -- Methods --
// Update data members using epoch time
void Date::updateMembers() {
    long epochDate = this->epochSeconds;

    // Set time members from epoch time
    this->second = epochDate % 60;
    epochDate /= 60;

    this->minute = epochDate % 60;
    epochDate /= 60;

    epochDate += this->tz; // Add time zone offset
    this->hour = epochDate % 24;
    epochDate /= 24;

    // Set date members from epoch time
    int month = 0;
    int year = 1970;
    while (epochDate >= monthDuration[month]) {
        // Subtract days in each month from epochDate
        bool isLeapYear = ((month == Month::Feb) && !(year % 4) && (year % 200));
        epochDate -= monthDuration[month] + isLeapYear;

        // Update month and year
        month++;
        if (!(month % 12)) {
            month = 0;
            year++;
        }
    }

    this->day = epochDate;
    this->month = month + 1;
    this->year = year;
}


// Default constructor
Date::Date() {
    this->setEpoch(0);
}


// Construct from epoch date
Date::Date(long epochSeconds) {
    this->setEpoch(epochSeconds);
}


// Destructor
Date::~Date() {}


// Accessor for epochSeconds
long Date::getEpoch() const {
    return this->epochSeconds;
}


// Mutator for epochSeconds
void Date::setEpoch(long epochSeconds) {
    this->epochSeconds = epochSeconds;
    this->updateMembers();
}


// Overload for operator<
bool Date::operator<(const Date &rhs) const {
    return this->epochSeconds < rhs.epochSeconds;
}


// Overload for operator<=
bool Date::operator<=(const Date &rhs) const {
    return this->epochSeconds <= rhs.epochSeconds;
}


// Overload for operator==
bool Date::operator==(const Date &rhs) const {
    return this->epochSeconds == rhs.epochSeconds;
}


// Overload for operator>=
bool Date::operator>=(const Date &rhs) const {
    return this->epochSeconds >= rhs.epochSeconds;
}


// Overload for operator>
bool Date::operator>(const Date &rhs) const {
    return this->epochSeconds > rhs.epochSeconds;
}


// Overload for operator<<
std::ostream &operator<<(std::ostream &lhs, Date &rhs) {
    // Redirect formatted date string to ostream, and return ostream
    return lhs << Formatter::format(rhs);
}
