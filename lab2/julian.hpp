//
//  julian.hpp
//  lab2
//
//  Created by Marcus Bergholm on 15/10/15.
//  Copyright © 2015 Marcus Bergholm. All rights reserved.
//

#ifndef julian_hpp
#define julian_hpp

#include <stdio.h>
#include "baseDate.hpp"

namespace lab2 {
    class Julian: public BaseDate {
        
        public:
        
            Julian();
            Julian(const Date&);
            Julian(Date*);
            Julian(int, int, int);
        
            // post inc operator, need constructor to implement this.
            virtual Date operator++(int);
            virtual Date operator--(int);
        
        private:
        
            virtual const bool isLeapYear(int) const;
            virtual const int yearFromMjd() const;
            virtual const int monthFromMjd() const;
            virtual const int dayFromMjd() const;
            virtual void setMjdFromDate(int year, int month, int day);
    };
}

#endif /* julian_hpp */
