//
//  baseDate.hpp
//  lab2
//
//  Created by Marcus Bergholm on 15/10/15.
//  Copyright © 2015 Marcus Bergholm. All rights reserved.
//
// If the inheritance is public, everything that is aware of Base and Child is also aware that Child inherits from Base.
// If the inheritance is protected, only Child, and its children, are aware that they inherit from Base.
// If the inheritance is private, no one other than Child is aware of the inheritance.
//

#ifndef baseDate_hpp
#define baseDate_hpp

#include <stdio.h>
#include "date.hpp"

namespace lab2 {
    class BaseDate: public Date {
        
        protected:
        
            BaseDate() {};
            virtual ~BaseDate() {};
        
            // Check if the set date is valid.
            void isDateValid() const;

        public:
        
            virtual const int year() const;
            virtual const unsigned int month() const;
            virtual const unsigned int day() const;
        
            virtual const unsigned int week_day() const;
            virtual const unsigned int days_per_week() const;
            virtual const unsigned int days_this_month() const;
        
            virtual const std::string week_day_name() const;
            virtual const std::string month_name() const;
        
            virtual const int mod_julian_day() const;
        
            virtual Date & add_year (const int n = 1);
            virtual Date & add_month (const int n = 1);
        
        private:
            // stuff cals need to implements. like leap year, conversion between year mouth day mjd.
            virtual const bool isLeapYear(int) const = 0;
            virtual const int yearFromMjd() const = 0;
            virtual const int monthFromMjd() const = 0;
            virtual const int dayFromMjd() const = 0;
            virtual void setMjdFromDate(int year, int month, int day) = 0;
        
            // To get the names of weekdays, months and number of days of a month. Not needed for cals to implement
            static const std::string weekDays[7];
            static const std::string months[12];
            static const int daysPerMonth[12];
        
            const unsigned days_this_month(int year, int month) const;
        

    };
}

#endif /* baseDate_hpp */
