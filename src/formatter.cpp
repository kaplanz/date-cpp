//
//  formatter.cpp
//  Date string formatter.
//
//  Created by Zakhary Kaplan on 2019-12-03.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#include <cstdio>
#include <string>
using std::string;

#include "date.h"
#include "formatter.h"


// -- Globals --
const std::string dayName[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};
const std::string monthName[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};
string specifiers[] = {
    "d", "dd", "M", "MM", "MMM", "MMMM", "y", "yy", "yyyy", "c", "cc",
    "h", "hh", "H", "HH", "m", "mm", "s", "ss", "t", "tt", "T", "TT", "z", "zz"
};


// -- Public Methods --

// Format a Date object by a string specifier
string Formatter::format(const Date &date) { return {}; }


// -- Private Methods --

// Formatting
string Formatter::day(const Date &date, string format) {
    int day = date.day;

    // Return formatted day string
    if (format == "d") {
        return std::to_string(day);
    } else if (format == "dd") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", day);
        return string(buffer);
    } else if (format == "ddd") {
        return string(dayName[day-1], 0, 3);
    } else if (format == "dddd") {
        return string(dayName[day-1]);
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::month(const Date &date, string format) {
    int month = date.month;

    // Return formatted month string
    if (format == "M") {
        return std::to_string(month);
    } else if (format == "MM") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", month);
        return string(buffer);
    } else if (format == "MMM") {
        return string(monthName[month-1], 0, 3);
    } else if (format == "MMMM") {
        return string(monthName[month-1]);
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::year(const Date &date, string format) {
    int year = date.year;

    // Return formatted year string
    if (format == "y") {
        return std::to_string(year);
    } else if (format == "yy") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", year % 100);
        return string(buffer);
    } else if (format == "yyy") {
        char buffer[5];
        snprintf(buffer, 5, "%03d", year);
        return string(buffer);
    } else if (format == "yyyy") {
        char buffer[5];
        snprintf(buffer, 5, "%04d", year);
        return string(buffer);
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::century(const Date &date, string format) {
    int century = date.year / 100;

    // Return formatted century string
    if (format == "c") {
        return std::to_string(century);
    } else if (format == "cc") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", century % 100);
        return string(buffer);
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::hour(const Date &date, string format) {
    int hour24 = date.hour;
    int hour12 = (hour24) ? hour24 % 12 : 12;

    // Return formatted hour string
    if (format == "h") {
        return std::to_string(hour12);
    } else if (format == "hh") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", hour12);
        return string(buffer);
    } else if (format == "H") {
        return std::to_string(hour24);
    } else if (format == "HH") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", hour24);
        return string(buffer);
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::minute(const Date &date, string format) {
    int minute = date.minute;

    // Return formatted minute string
    if (format == "m") {
        return std::to_string(minute);
    } else if (format == "mm") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", minute);
        return string(buffer);
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::second(const Date &date, string format) {
    int second = date.second;

    // Return formatted second string
    if (format == "m") {
        return std::to_string(second);
    } else if (format == "mm") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", second);
        return string(buffer);
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::period(const Date &date, string format) {
    string period = (date.hour < 12) ? "am" : "pm";

    // Return formatted period string
    if (format == "t") {
        return period.substr(0, 1);
    } else if (format == "tt") {
        return period;
    } else if (format == "T") {
        for (auto &c: period)
            c = toupper(c); // to upper case
        return period.substr(0, 1);
    } else if (format == "TT") {
        for (auto &c: period)
            c = toupper(c); // to upper case
        return period;
    }

    // Return empty string for invalid format
    return string();
}


string Formatter::tz(const Date &date, string format) {
    int tz = date.tz;

    // Return formatted tz string
    if (format == "z") {
        char buffer[4];
        snprintf(buffer, 4, "%+d", tz);
        return string(buffer);
    } else if (format == "zz") {
        char buffer[4];
        snprintf(buffer, 4, "%+02i", tz);
        return string(buffer);
    }

    // Return empty string for invalid format
    return string();
}