//
//  baseDate.cpp
//  lab2
//
//  Created by Marcus Bergholm on 15/10/15.
//  Copyright © 2015 Marcus Bergholm. All rights reserved.
//

#include <cmath>
#include "baseDate.hpp"

namespace lab2 {

    const int BaseDate::year() const {
        return yearFromMjd();
    };
    
    const unsigned int BaseDate::month() const {
        return monthFromMjd();
    };
    
    const unsigned int BaseDate::day() const {
        return dayFromMjd();
    };

    
    const unsigned int BaseDate::week_day() const {
        int j = MJD + 2400001;
        return (j % 7) + 1;
    };
    
    const unsigned int BaseDate::days_per_week() const {
        return 7;
    };
    
    const unsigned int BaseDate::days_this_month() const {
        int m = month();
        int y = year();
        if(m == 2 && isLeapYear(y)) {
            return 29;
        } else {
            return daysPerMonth[m-1];
        }
    };
    
    const unsigned int BaseDate::days_this_month(int year, int month) const {
        if(month == 2 && isLeapYear(year)) {
            return 29;
        } else {
            return daysPerMonth[month-1];
        }
    }

    
    const std::string BaseDate::week_day_name() const {
        return weekDays[week_day()-1];
    };
    
    const std::string BaseDate::month_name() const {
        return months[month()-1];
    };
    

    const int BaseDate::mod_julian_day() const {
        return MJD;
    };
    
    Date & BaseDate::add_year(const int n) {
        int d = day();
        int m = month();
        int y = year() + n; // Add the new years.
        if(!isLeapYear(y) && m == 2 && d == 29) {
            d = 28;
        }
        
        setMjdFromDate(y, m, d); // Set new MJD value
        return *this;
    };
    
    Date & BaseDate::add_month(const int n) {
        int d = day();
        int m = month();
        int y = year();
        
        if(n < 0) { // "removing" month's
            int j = abs(n); // n is negative..
            for(int i = 0; i < j; ++i) {
                --m;
                if(m == 0) {
                    --y;
                    m = 12;
                }
                int daysInMonth = days_this_month(y, m);
                if(d > daysInMonth) {
                    d = daysInMonth;
                }
            }
        } else { // adding month's
            for(int i = 0; i < n; ++i){
                ++m; // inc month
                if(m > 12) {
                    ++y;
                    m = 1;
                }
                int daysInMonth = days_this_month(y, m);
                if(d > daysInMonth) {
                    d = daysInMonth;
                }
            }
        }
        setMjdFromDate(y, m, d);
        return *this;
    };
    
    //names of weekdays, months and number of days of a month
    const std::string BaseDate::weekDays[7] = {
                                                "monday", "tuesday", "wednesday", "thursday",
                                                "friday", "saturday", "sunday"
                                               };
    
    const std::string BaseDate::months[12] = {
                                            "january", "february", "march", "april", "may", "june",
                                            "july", "august", "september", "october", "november", "december"
                                           };
    
    const int BaseDate::daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check if the set date is valid.
    void BaseDate::isDateValid() const {
        int d = day();
        int m = month();
        int y = year();
        if(y < 1858 || y > 2558) {
            std::out_of_range("Year is not vaild");
        }
        if(m < 1 || m > 12) {
            std::out_of_range("Month is not valid");
        }
        if (d < 1 || d > days_this_month()) {
            std::out_of_range("Day is not valid");
        }
    };
    
}



