//
//  duration.h
//  Duration class header file.
//
//  Created by Zakhary Kaplan on 2019-12-23.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#pragma once

#include "date.h"

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
        int years() const;
        int months() const;
        int weeks() const;
        int days() const;
        int hours() const;
        int minutes() const;
        long seconds() const;

        // Operators
        Duration &operator=(const Duration &rhs) = default;
        Duration operator+(const Duration &rhs) const;
        friend Date Date::operator+(const Duration &rhs) const;
        Duration operator-(const Duration &rhs) const;
        Duration operator*(const double &rhs) const;
        friend Duration operator*(const double &lhs, const Duration &rhs);
        Duration operator/(const double &rhs) const;
        friend Duration operator/(const double &lhs, const Duration &rhs);
        bool operator<(const Duration &rhs) const;
        bool operator<=(const Duration &rhs) const;
        bool operator==(const Duration &rhs) const;
        bool operator>=(const Duration &rhs) const;
        bool operator>(const Duration &rhs) const;
};
