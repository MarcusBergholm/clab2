//
//  calendar.hpp
//  lab2
//
//  Created by Marcus Bergholm on 15/10/15.
//  Copyright © 2015 Marcus Bergholm. All rights reserved.
//

#ifndef calendar_hpp
#define calendar_hpp

#include <stdio.h>
#include "date.hpp"
#include <string>
#include <map>
#include <iostream>
#include <sstream>

namespace lab2 {
    template<typename DateType>
    class Calendar {
        private:
            DateType date;
            std::multimap<DateType,std::string> events;
        public:
            // constructors
            Calendar();

            template <typename DateType2>
            Calendar(const Calendar<DateType2>  & cal);

            // member functions
            bool set_date(int year, int month, int day);

            bool add_event(std::string event_name);
            bool add_event(std::string event_name, int day);
            bool add_event(std::string event_name, int day, int month);
            bool add_event(std::string event_name, int day, int month, int year);

            bool remove_event(std::string event_name);
            bool remove_event(std::string event_name, int day);
            bool remove_event(std::string event_name, int day, int month);
            bool remove_event(std::string event_name, int day, int month, int year);

            // print out ... needs to be in iCal format]
        friend std::ostream & operator<<(std::ostream & os, const Calendar<DateType> & cal) {
            os << "BEGIN:VCALENDAR" << std::endl << "VERSION:2.0" << std::endl << "PRODID:-//Bergholm//SuperCalendar v1.0//EN" << std::endl;
            for(auto it = cal.events.begin(); it != cal.events.end(); ++it) {
                if(it->first >= cal.date) {
                    os << "BEGIN:VEVENT" << std::endl;
                    os << "DTSTART:" << it->first.year() << it->first.month() << it->first.day();
                    os << "T080000" << std::endl;
                    os << "DTEND:" << it->first.year() << it->first.month() << it->first.day();
                    os << "T090000" << std::endl;
                    os << "SUMMARY:" << it->second << std::endl;
                    os << "END:VEVENT" << std::endl;
                }
            }
            os << "END:VCALENDAR" << std::endl;
            return os;
        };
    };

    // Implementation of Calendar

    template <typename DateType>
    Calendar<DateType>::Calendar() {
        date = DateType();
    }

    template <typename DateType>
    template <typename DateType2>
    Calendar<DateType>::Calendar(const Calendar<DateType2> & cal) {
        date = cal.date;
        events = cal.events;
    }
    
    template <typename DateType>
    bool Calendar<DateType>::set_date(int year, int month, int day) {
        try {
            date = DateType(year, month, day);
        } catch (std::out_of_range e) {
            return false;
        }
        return true; 
    }
    
    template <typename DateType>
    bool Calendar<DateType>::add_event(std::string event_name) {
        int day = date.day();
        int month = date.month();
        int year = date.year();
        return add_event(event_name, day, month, year);
    }
    
    template <typename DateType>
    bool Calendar<DateType>::add_event(std::string event_name, int day) {
        int month = date.month();
        int year = date.year();
        return add_event(event_name, day, month, year);
    }
    
    template <typename DateType>
    bool Calendar<DateType>::add_event(std::string event_name, int day, int month) {
        int year = date.year();
        return add_event(event_name, day, month, year);
    }
    
    template <typename DateType>
    bool Calendar<DateType>::add_event(std::string event_name, int day, int month, int year) {
        try {
            DateType event(year, month, day);
            //check if event allready exists in cal.
            std::pair <
                        typename std::multimap<DateType,std::string>::iterator,
                        typename std::multimap<DateType,std::string>::iterator
                      > ret;
            ret = events.equal_range(event);
            for (typename std::multimap<DateType, std::string>::iterator it = ret.first; it != ret.second; ++it) {
                if(it->second == event_name) {
                    return false;
                }
            }
            events.insert(std::pair<DateType, std::string>(event, event_name));
            return true;
        } catch(std::out_of_range e) {
            std::cout << "CRASHED!!!!" << std::endl;
            return false;
        }
    }
    
    template <typename DateType>
    bool Calendar<DateType>::remove_event(std::string event_name) {
        int day = date.day();
        int month = date.month();
        int year = date.year();
        return remove_event(event_name, day, month, year);
    }
    
    template <typename DateType>
    bool Calendar<DateType>::remove_event(std::string event_name, int day) {
        int month = date.month();
        int year = date.year();
        return remove_event(event_name, day, month, year);
    }
    
    template <typename DateType>
    bool Calendar<DateType>::remove_event(std::string event_name, int day, int month) {
        int year = date.year();
        return remove_event(event_name, day, month, year);
    }
    
    template <typename DateType>
    bool Calendar<DateType>::remove_event(std::string event_name, int day, int month, int year) {
        try {
            DateType event(year, month, day);
            //check if event exists in cal.
            std::pair <
                typename std::multimap<DateType,std::string>::iterator,
                typename std::multimap<DateType,std::string>::iterator
            > ret;
            ret = events.equal_range(event);
            for(typename std::multimap<DateType, std::string>::iterator it = ret.first; it != ret.second; ++it) {
                if(it->second == event_name) {
                    events.erase(it);
                    return true;
                }
            }
            return false;
        } catch(std::out_of_range e) {
            return false;
        }
    }
}

#endif /* calendar_hpp */
