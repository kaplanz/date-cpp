//
//  date.h
//  Date class header file.
//
//  Created by Zakhary Kaplan on 2019-12-03.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>


class Date {
    friend class Formatter;

    private:
        // Data members
        long epochSeconds; // epoch time in seconds
        char tz; // DST and time zone info

    public:
        // Constructors
        Date();
        Date(Date &date);
        Date(long epochSeconds);

        // Destructor
        ~Date();

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
        Date &operator=(const Date &rhs);
        bool operator<(const Date &rhs) const;
        bool operator<=(const Date &rhs) const;
        bool operator==(const Date &rhs) const;
        bool operator>=(const Date &rhs) const;
        bool operator>(const Date &rhs) const;
        friend std::ostream &operator<<(std::ostream &lhs, Date &rhs);
};
