//
//  duration.cpp
//  Duration class implementation.
//
//  Created by Zakhary Kaplan on 2019-12-23.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#include "date.h"
#include "duration.h"


// -- Constructors --
// Default constructor
Duration::Duration() {
    this->durationSeconds = 0;
}


// durationSeconds constructor
Duration::Duration(long durationSeconds) {
    this->durationSeconds = durationSeconds;
}


// -- Accessors --
int Duration::years() const {
    return this->durationSeconds / (86400 * 365); // average years
}


int Duration::months() const {
    return this->durationSeconds / (86400 * 365 / 12); // average months
}


int Duration::weeks() const {
    return this->durationSeconds / (86400 * 7);
}


int Duration::days() const {
    return this->durationSeconds / 86400;
}


int Duration::hours() const {
    return this->durationSeconds / 3600;
}


int Duration::minutes() const {
    return this->durationSeconds / 60;
}


long Duration::seconds() const {
    return this->durationSeconds;
}


// -- Operators --
// Overload for operator+
Duration Duration::operator+(const Duration &rhs) const {
    return Duration(this->durationSeconds + rhs.durationSeconds);
}


// Overload for operator-
Duration Duration::operator-(const Duration &rhs) const {
    return Duration(this->durationSeconds - rhs.durationSeconds);
}


// Overload for operator*
Duration Duration::operator*(const double &rhs) const {
    return Duration(this->durationSeconds * rhs);
}
Duration operator*(const double &lhs, const Duration &rhs) {
    return rhs * lhs;
}


// Overload for operator/
Duration Duration::operator/(const double &rhs) const {
    return Duration(this->durationSeconds / rhs);
}
Duration operator/(const double &lhs, const Duration &rhs) {
    return rhs / lhs;
}


// Overload for operator<
bool Duration::operator<(const Duration &rhs) const {
    return this->durationSeconds < rhs.durationSeconds;
}


// Overload for operator<=
bool Duration::operator<=(const Duration &rhs) const {
    return this->durationSeconds <= rhs.durationSeconds;
}


// Overload for operator==
bool Duration::operator==(const Duration &rhs) const {
    return this->durationSeconds == rhs.durationSeconds;
}


// Overload for operator>=
bool Duration::operator>=(const Duration &rhs) const {
    return this->durationSeconds >= rhs.durationSeconds;
}


// Overload for operator>
bool Duration::operator>(const Duration &rhs) const {
    return this->durationSeconds > rhs.durationSeconds;
}
