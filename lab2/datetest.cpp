// projektlokala headerfiler
#include "kattistime.h"
#include "julian.hpp"
#include "gregorian.hpp"
#include "calendar.hpp"

// STL headerfiler
#include <iostream>
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <ctime>
#include <map>


// Obs att testerna f�ruts�tter att dina klasser returnerar
// m�nader och dagar indexerade fr�n ETT. Testerna �r inte
// fullst�ndiga


int main()
{
    using namespace lab2;        // Exponera funktionalitet i namnrymden lab2
    
    std::map<int, std::string> events;
    events[1] = "aa";
    if(events[2] == "") {
        std::cout << events[1] << std::endl;
    }
    
    ////////////////////////////////////////////////////////////
    // S�tt tiden. OBS skicka inte nedanst�ende kod till kattis
    time_t mytime;
    time(&mytime);
    set_k_time(mytime);
    ////////////////////////////////////////////////////////////


    Julian tj;                  // ok: defaultkonstruktor ger dagens datum
    Gregorian gtoday;           // ok f�r gregorian ocks�
    std::cout << "Idag r det " << gtoday << "  "<< tj << std::endl;
    assert(tj - gtoday == 0);
    Gregorian tg(2006, 10, 31); // ok: s�tt datum explicit
                                // f�ljande fungerar ocks�:
                                // Gregorian(2000, Gregorian::October, 31)
    Date &j = tj;               // �tkomst av funktioner genom Dates interface
    Date &g = tg;
    Date &today = gtoday;

    {
      Julian j1;
      Date & d1 = j1;
      Julian j2(d1);
      Date * dp = &j2;
      Julian j3(dp);
    }

    time_t tp;
    time(&tp);
    struct tm *t = gmtime(&tp);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // m�naderna och dagarna
    int day   = t->tm_mday;         // indexerade fr�n ETT

    std::cout << "Testing constructors..." << std::endl;
    assert(today.year() == year &&          // r�tt initierad
           today.month() == month &&
           today.day() == day);
    assert(g.year() == 2006 &&              // r�tt initierad
           g.month() == 10 &&
           g.day() == 31);                  // obs! ettindexerade

    std::cout << "Testing access..." << std::endl;
    assert(g.days_per_week() == 7);         // r�tt antal dagar per vecka
    assert(j.days_per_week() == 7);         // r�tt antal dagar per vecka
    assert(g.days_this_month() == 31);      // r�tt antal dagar denna m�nad
    std::cout << g << "  " << g.week_day() << std::endl;
    std::cout << j << "  " << j.week_day() << std::endl;
    assert(g.week_day() == 2); // r�tt veckodag

    std::cout << "Testing manipulation..." << std::endl;
    ++g;                                    // prefix �kning
    assert(g.week_day() == 3); // r�tt veckodag
    --g;                                    // prefix minskning
    assert(g.week_day() == 2); // r�tt veckodag
    g += 2;                                 // l�gg till tv� dagar
    assert(g.week_day() == 4); // r�tt veckodag
    g -= 3;                     // dra bort tre dagar
    g.add_month();              // l�gg till en m�nad
    g.add_month(-1);            // dra bort en m�nad
    g.add_year(10);             // l�gg till tio �r.

    std::cout << "Testing miscellaneous functions..." << std::endl;
    Julian jj(tj);              // kopieringskonstruktor
    const Gregorian gg;
    gg.year();                  // gg konstant, l�sa g�r bra
    g = gg;                     // tilldelning
    if(g == gg ||               // j�mf�relse
       g != gg ||               // j�mf�relse
       g < gg ||                // j�mf�relse
       g >= gg)                 // j�mf�relse
        {}

    std::cout << "Testing boundary violations" << std::endl;
    Gregorian temp(1900, 1, 1);
    Date &d = temp;

    // loopa �ver dagar och kolla att inga gr�nser �ver/underskrids
    for(int i = 0; i < 100000; ++i, ++d) {
            if(!(i % 5000)) {
                    std::cout << ".";
                    flush(std::cout);
            }
            int m[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if(d.year() >= 1900 &&
               d.month() >= 1 && d.month() <= 12 &&
               d.day() >= 1 && d.day() <= m[d.month() - 1]) {
                
            } else {
                    std::cout << std::endl;
                    std::cout << "boundary checks failed: " << std::endl;
                    std::cout << d.year() << ", "
                              << d.month() << ", "
                              << d.day() << std::endl;
                    return 1;
            }
        }
    std::cout << std::endl;

    std::cout << "Testing leap years..." << std::endl;
    // testa om skott�ren f�r sekelskiften fungerar som de ska
    for(int y = 1958; y < 2500; y += 100)
        {
            Gregorian temp(y, 2, 28);
            Date &e = temp;
            ++e;                                   // l�gg till en dag
            if((y % 400 == 0 && e.day() == 29) ||  // skottdag (obs! ETTindexerad)
               (y % 400 != 0 && e.day() == 1))     // ej skottdag
                {}
            else
                {
                    std::cout << std::endl << "leap day test failed: " << std::endl;
                    std::cout << e.year() << ", "
                              << e.month() << ", "
                              << e.day() << std::endl;
                    return 1;
                }
        }
    
    Gregorian test(1900, 1, 1);
    Julian test2 = test;
    std::cout << test << "  " << test2 << std::endl;
    
    Julian test3(1900, 1, 1);
    Gregorian test4 = test3;
    std::cout << test3 << "  " << test4 << std::endl;
    
    Gregorian test5(1858, 11, 16);
    Julian test6 = test5;
    std::cout << test5 << "  " << test6 << std::endl;
    
    Gregorian test7(1858, 11, 17);
    Julian test8 = test7;
    std::cout << test7 << "  " << test8 << std::endl;
    
    Gregorian test9(1858, 11, 18);
    Julian test10 = test9;
    std::cout << test9 << "  " << test10 << std::endl;

    std::cout << std::endl << "All tests were successful." << std::endl;
    
    
    /////////////////////////////////////////////////////////////
    /// TEST AV KALENDAR
    ////////////////////////////////////////////////////////////
    
    Calendar<Gregorian> cal;
    cal.set_date(2000, 12, 2);
    cal.add_event("Baskettraning", 4, 12, 2000);
    cal.add_event("Baskettraning", 11, 12, 2000);
    cal.add_event("Nyrsfrukost", 1, 1, 2001);
    cal.add_event("Forsta advent", 1);          // �r = 2000, m�nad = 12
    cal.add_event("Vardagjamning", 20, 3);      // �r = 2000
    cal.add_event("Julafton", 24, 12);
    cal.add_event("Kalle Anka halsar god jul", 24); // ocks� p� julafton
    cal.add_event("Julafton", 24); // En likadan h�ndelse samma datum ska
    // ignoreras och inte s�ttas in i kalendern
    cal.add_event("Min forsta cykel", 20, 12, 2000);
    cal.remove_event("Baskettraning", 4);
    std::cout << cal; // OBS! V�rdagj�mning och f�rsta advent �r
    // f�re nuvarande datum och skrivs inte ut
    std::cout << "----------------------------------------" << std::endl;
    cal.remove_event("Vardagjamning", 20, 3, 2000);
    cal.remove_event("Kalle Anka halsar god jul", 24, 12, 2000);
    cal.set_date(2000, 11, 2);
    if (! cal.remove_event("Julafton", 24)) {
        std::cout << " cal.remove_event(\"Julafton\", 24) tar inte"<< std::endl
        << " bort nagot eftersom aktuell manad ar november" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << cal;

    // f�ljande ska inte g� att kompilera
#if 0
    gg.leap_year();             // fel: kan inte komma �t protected/private medlem
    gg = g;                     // fel: kan inte tilldela konstant
    ++gg;                       // fel: kan inte �ndra p� en konstant
#endif

    return 0;
}

