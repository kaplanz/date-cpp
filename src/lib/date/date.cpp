// File:        date.cpp
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     03 Dec 2019
// SPDX-License-Identifier: NONE

#include "date/date.h"

#include <ctime>
#include <iostream>
#include <string>

#include "date/duration.h"
#include "date/formatter.h"

// -- Constructors --
// Default constructor
Date::Date() {
    this->epochSeconds = 0;
    this->tz = 0;
}

// epochSeconds constructor
Date::Date(long epochSeconds) {
    this->epochSeconds = epochSeconds;
    this->tz = 0;
}

// -- Accessors --
long Date::epoch() const {
    return this->epochSeconds;
}

int Date::timezone() const {
    int sign = (this->tz & 0x40) ? -1 : 1;
    return sign * (this->tz & 0x0F);
}

bool Date::DST() const {
    return this->tz & 0x80;
}

int Date::year() const {
    long offset = this->epochSeconds + 3600 * (this->timezone() + this->DST());
    return std::gmtime(&offset)->tm_year + 1900;
}

int Date::month() const {
    long offset = this->epochSeconds + 3600 * (this->timezone() + this->DST());
    return std::gmtime(&offset)->tm_mon + 1;
}

int Date::day() const {
    long offset = this->epochSeconds + 3600 * (this->timezone() + this->DST());
    return std::gmtime(&offset)->tm_mday;
}

int Date::hour() const {
    long offset = this->epochSeconds + 3600 * (this->timezone() + this->DST());
    return std::gmtime(&offset)->tm_hour;
}

int Date::minute() const {
    long offset = this->epochSeconds + 3600 * (this->timezone() + this->DST());
    return std::gmtime(&offset)->tm_min;
}

int Date::second() const {
    long offset = this->epochSeconds + 3600 * (this->timezone() + this->DST());
    return std::gmtime(&offset)->tm_sec;
}

// -- Mutators --
long Date::epoch(long epochSeconds) {
    return this->epochSeconds = epochSeconds;
}

int Date::timezone(const int tz) {
    // Store sign in bit 7, value in lower 6 bits
    char sign = (tz < 0) ? -1 : 1;
    char value = abs(tz) % 16; // using 4 bits: values range between 0 and 15
    this->tz = (value & 0x0F) | ((sign >> 1) & 0x40) | (this->tz & 0x80);

    return this->timezone();
}

bool Date::DST(const bool DST) {
    // Store DST indicator in bit 8
    return this->tz = ((DST) ? 0x80 : 0x00) | (this->tz & 0x7F);
}

// -- Operators --
// Overload for operator+
Date Date::operator+(const Duration &rhs) const {
    Date sum(*this);
    sum.epochSeconds += rhs.durationSeconds;
    return sum;
}

// Overload for operator-
Duration Date::operator-(const Date &rhs) const {
    return Duration(this->epochSeconds - rhs.epochSeconds);
}

// Overload for operator==
bool Date::operator==(const Date &rhs) const {
    return this->epochSeconds == rhs.epochSeconds;
}

// Overload for operator!=
bool Date::operator!=(const Date &rhs) const {
    return this->epochSeconds != rhs.epochSeconds;
}

// Overload for operator<
bool Date::operator<(const Date &rhs) const {
    return this->epochSeconds < rhs.epochSeconds;
}

// Overload for operator<=
bool Date::operator<=(const Date &rhs) const {
    return this->epochSeconds <= rhs.epochSeconds;
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
std::ostream &operator<<(std::ostream &lhs, const Date &rhs) {
    // Redirect formatted date string to ostream, and return ostream
    return lhs << Formatter::format(rhs);
}
