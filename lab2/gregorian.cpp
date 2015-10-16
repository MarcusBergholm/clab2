//
//  gregorian.cpp
//  lab2
//
//  Created by Marcus Bergholm on 15/10/15.
//  Copyright © 2015 Marcus Bergholm. All rights reserved.
//

#include "gregorian.hpp"
#include "kattistime.h"

namespace lab2 {

    Gregorian::Gregorian() {
        // get kattis time
        time_t mytime;
        k_time(&mytime);

        // Get current time in days from unix time.
        // Add the missing days since modified julian day.
        // i.e 40587 days since there is 2440587.5 days between julian day and unix time (1970-01-01 00:00)
        // and 2400000.5 days between julian day and modified julian day.
        int days = (int) mytime / 86400;
        MJD = days + 40587;
    };

    Gregorian::Gregorian(const Date& date){
        MJD = date.mod_julian_day();
    };

    Gregorian::Gregorian(Date* date) {
        MJD = date->mod_julian_day();
    };

    Gregorian::Gregorian(int year, int month, int day) {
        setMjdFromDate(year, month, day);
    };

    // post inc operator, need constructor to implement this.
    Date Gregorian::operator++(int) {
        Gregorian copy(*this);
        ++MJD;
        return copy;
    };
    Date Gregorian::operator--(int) {
        Gregorian copy(*this);
        --MJD;
        return copy;
    };

    const bool Gregorian::isLeapYear(int year) const {
        if( year % 4 == 0) {
            if(year % 100 == 0) {
                if(year % 400) {
                    return true;
                }
                return false;
            }
            return true;
        }
        return false;
    };

    const int Gregorian::yearFromMjd() const {
        int ff = MJD + 2400001 + 1401;
        int b = (4 * (MJD + 2400001) + 274277) / 146097;
        int f = ff + ( b * 3) / 4 - 38;
        int e = (4 * f) + 3;
        int g = (e % 1461) / 4;
        int h = (5 * g) + 2;
        int m = ((h / 153) + 2 % 12) + 1;
        int y = (e / 1461) - 4716 + ((12 + 2 - m) / 12);
        if(m > 12) {
            m -= 12;
            ++y;
        }
        return y;
    };


    const int Gregorian::monthFromMjd() const {
        int ff = MJD + 2400001 + 1401;
        int b = (4 * (MJD + 2400001) + 274277) / 146097;
        int f = ff + ( b * 3) / 4 - 38;
        int e = (4 * f) + 3;
        int g = (e % 1461) / 4;
        int h = (5 * g) + 2;
        int m = ((h / 153) + 2 % 12) + 1;
        if(m > 12) {
            m -= 12;
        }
        return m;
    };

    const int Gregorian::dayFromMjd() const {
        int ff = MJD + 2400001 + 1401;
        int b = (4 * (MJD + 2400001) + 274277) / 146097;
        int f = ff + ( b * 3) / 4 - 38;
        int e = (4 * f) + 3;
        int g = (e % 1461) / 4;
        int h = (5 * g) + 2;
        return (h % 153) / 5 + 1; // OBS! Satt +2 is'llet f;r +1, kanske fungerar nu
    };

    void Gregorian::setMjdFromDate(int year, int month, int day) {
        int a = (14 - month) / 12;
        int y = year + 4800 - a;
        int m = month + 12 * a - 3;
        int jd = day + (((153 * m) + 2)/ 5) + (365 * y) + (y / 4)  - (y / 100) + (y / 400) - 32045; // not MJD
        MJD = jd - 2400001;
        isDateValid(); // check if date is valid
    };

}
