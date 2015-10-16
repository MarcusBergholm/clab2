//
//  main.cpp
//  lab2
//
//  Created by Marcus Bergholm on 14/10/15.
//  Copyright © 2015 Marcus Bergholm. All rights reserved.
//

#include <iostream>
#include "kattistime.h"

int main(int argc, const char * argv[]) {
    // init kattis time
    time_t tp;
    time(&tp);
    set_k_time(tp);
    
    // get kattis time
    time_t mytime;
    k_time(&mytime);
    
    struct tm *t = gmtime(&mytime);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // månaderna och dagarna
    int day   = t->tm_mday;         // indexerade från ETT
    
    std::cout << mytime << std::endl << year << std::endl << month << std::endl << day << std::endl;
    return 0;
}
