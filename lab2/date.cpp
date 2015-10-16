//
//  Implements the basic operators for date class
//
//  Created by Marcus Bergholm on 14/10/15.
//  Copyright © 2015 Marcus Bergholm. All rights reserved.
//

#include "date.hpp"
#include <iostream>

namespace lab2 {
    
    Date & Date::operator=(const Date &date) {
        MJD = date.MJD;
        return *this;
    };

    // PRE INC
    Date & Date::operator++() {
        MJD++;
        return *this;
    };
    Date & Date::operator--() {
        MJD--;
        return *this;
    };

    Date & Date::operator+=(const int n) {
        MJD += n;
        return *this;
    };
    
    Date & Date::operator-=(const int n) {
        MJD -= n;
        return *this;
    };
    
    int Date::operator-(const Date &date) {
        return MJD - date.MJD;
    };

    bool Date::operator==(const Date &date) const {
        return MJD == date.MJD;
    };
    
    bool Date::operator!=(const Date &date) const {
        return MJD != date.MJD;
    };
    
    bool Date::operator<(const Date &date) const {
        return MJD < date.MJD;
    };
    
    bool Date::operator<=(const Date &date) const {
        return MJD <= date.MJD;
    };
    
    bool Date::operator>(const Date &date) const {
        return MJD > date.MJD;
    };
    
    bool Date::operator>=(const Date &date) const {
        return MJD >= date.MJD;
    };

    std::ostream & operator<<(std::ostream & os, const Date & date) {
        os << date.year() << "-" << date.month() << "-" << date.day();
        return os;
    };

}