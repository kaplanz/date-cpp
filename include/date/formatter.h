// File:        formatter.h
// Author:      Zakhary Kaplan <https://zakhary.dev>
// Created:     03 Dec 2019
// SPDX-License-Identifier: NONE

#pragma once

#include <string>
#include <vector>

#include "date/date.h"

//  -- Date Formatting Table --
//  d       day     1       31
//  dd      day     01      31
//  ddd     day     Sun     Sat
//  dddd    day     Sunday  Saturday
//  M       month   1       12
//  MM      month   01      12
//  MMM     month   Jan     Dec
//  MMMM    month   January December
//  y       year    0       99
//  yy      year    00      99
//  yyy     year    000     9999
//  yyyy    year    0000    9999
//  c       century 0       99
//  cc      century 00      99
//
//  -- Time Formatting Table --
//  h       hour    0       12
//  hh      hour    00      12
//  H       hour    1       24
//  HH      hour    01      24
//  m       minute  0       59
//  mm      minute  00      59
//  s       second  0       59
//  ss      second  00      59
//  t       period  a       p
//  tt      period  am      pm
//  T       period  A       P
//  TT      period  AM      PM
//  z       tz      +0      +12
//  zz      tz      +00     +12

class Formatter {
private:
    // Constants
    const static std::string WEEKDAYS[];
    const static std::string MONTHS[];

    // Helper methods
    static void tokenize(const std::string src, std::vector<std::string> &tokens);
    static std::string substitute(const Date &date, std::string format);

    // Date formatting
    static std::string day(const Date &date, std::string format);
    static std::string month(const Date &date, std::string format);
    static std::string year(const Date &date, std::string format);
    static std::string century(const Date &date, std::string format);
    // Time formatting
    static std::string hour(const Date &date, std::string format);
    static std::string minute(const Date &date, std::string format);
    static std::string second(const Date &date, std::string format);
    static std::string period(const Date &date, std::string format);
    static std::string timezone(const Date &date, std::string format);

public:
    static std::string format(const Date &date);
    static std::string format(const Date &date, std::string specifier);
};
