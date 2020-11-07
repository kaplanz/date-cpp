//
//  main.cpp
//  Program entry point.
//
//  Created by Zakhary Kaplan on 2019-01-01.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#include <iostream>

#include "date/date.h"
#include "date/duration.h"

using namespace std;


int main(int argc, char *argv[]) {
    // Create Date objects
    Date epoch;
    epoch.timezone(-5);
    Date today((argc > 1) ? stoi(argv[1]) : 946702800);
    today.timezone(-5);

    // Create Duration objects
    Duration hour(3600);
    Duration min(60);
    Duration custom = epoch - today;
    // custom.addyears(1);
    cout << custom.years() << endl;
    // custom.addmonths(2);
    cout << custom.months() << endl;
    // custom.addweeks(3);
    cout << custom.weeks() << endl;
    // custom.adddays(4);
    cout << custom.days() << endl;
    // custom.addhours(5);
    cout << custom.hours() << endl;
    // custom.addminutes(6);
    cout << custom.minutes() << endl;
    // custom.addseconds(7);
    cout << custom.seconds() << endl;

    // Testing
    cout << today << endl;
    cout << today + 10 * min + 20 * hour << endl;
    cout << epoch + 2. * (today - epoch) << endl;
    // today + epoch; // correctly causes an error
    // cout << (today != epoch) << endl;

    return EXIT_SUCCESS;
}
