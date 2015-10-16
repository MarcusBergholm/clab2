#ifndef date_hpp
#define date_hpp
#include <iostream>

// DATE RANGE (1858-2558) ELSE std::out_of_range
// APPLY "friend, const, virtual, override" when appropiate

namespace lab2 {
    class Date {
        protected:
        
            int MJD; // Modified Julian Date number

        public:
        
            // operators
        
            virtual Date & operator=(const Date &date);
        
            virtual Date & operator++(); // pre
            virtual Date & operator--();
        
            virtual Date & operator+=(const int n);
            virtual Date & operator-=(const int n);
        
            virtual int operator-(const Date &date);
        
            virtual bool operator==(const Date &date) const;
            virtual bool operator!=(const Date &date) const;
            virtual bool operator<(const Date &date) const;
            virtual bool operator<=(const Date &date) const;
            virtual bool operator>(const Date &date) const;
            virtual bool operator>=(const Date &date) const;
        
            // CHECK FRIEND
            friend std::ostream & operator<<(std::ostream & os, const Date & date);
        
            // member-functions
        
            virtual const int year() const = 0;
            virtual const unsigned int month() const = 0;
            virtual const unsigned int day() const = 0;
            virtual const unsigned int week_day() const = 0;
            virtual const unsigned int days_per_week() const = 0;
            virtual const unsigned int days_this_month() const = 0;
            virtual const std::string week_day_name() const = 0;
            virtual const std::string month_name() const = 0;
            virtual const int mod_julian_day() const = 0;
        
            virtual Date & add_year (const int n = 1) = 0;
            virtual Date & add_month (const int n = 1) = 0;
        
            virtual ~Date() {};
        
            // Empty virtual destructor is needed so its possible to delete an obj assigned by a pointer
            // No need for constructors because all functions is pure virtual -> meaning we cant create a instance of
            // Date. This only implements all operators because its possible to just modify or compare the MJD number.
        
    };
}

#endif