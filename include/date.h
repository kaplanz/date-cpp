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
        // Date and time
        int year;
        short month;
        short day;
        short hour;
        short minute;
        short second;

        // Epoch seconds
        long epochSeconds;

        // Time zone
        short tz = 0;
        bool DST = false;

        // Date format
        std::string format;

        // Function members
        void updateMembers();

    public:
        // Constructors
        Date();
        Date(long epochSeconds);

        // Destructor
        ~Date();

        // Accessors
        long getEpoch() const;
        std::string getFormat() const;

        // Mutators
        void setEpoch(long epochSeconds);
        void setFormat(std::string format);

        // Operators
        bool operator<(const Date &rhs) const;
        bool operator<=(const Date &rhs) const;
        bool operator==(const Date &rhs) const;
        bool operator>=(const Date &rhs) const;
        bool operator>(const Date &rhs) const;
        friend std::ostream &operator<<(std::ostream &lhs, Date &rhs);
};
