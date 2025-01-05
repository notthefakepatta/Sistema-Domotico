// Alessandro Pattaro 2101822

#ifndef TIME_H
#define TIME_H

#include <iostream>

/*  classe che indica il tempo o il timer di un elemento del progetto, sia esso un
 *  sia esso un DomoticSystem o uno dei dispositivi ad esso collegati */
class Time
{
public:
//  COSTRUTTORI
    /*  costruttore di default corrisponde a 00:00 */
    Time() : hours_(KDefaultHours), minutes_(KDefaultMinutes) {}

    /*  costruttore con orario definito */
    Time(int h, int m);

//  LETTURA ISTANZE PRIVATE
    /*  ore */
    int get_hours() const
    {   return hours_;}

    /*  minuti */
    int get_minutes() const
    {   return minutes_;}

//  VARIABILI STATICHE DI CLASSE
    static const Time kAllDayLongTimer;
    static const Time kOneMinute;
    static const int kMinutesPerHour = 60;
    static const int KDefaultHours = 0;
    static const int KDefaultMinutes = 0;

private:
    int hours_;
    int minutes_;
};

//  OVERLOADING OPERATORI UTILI
/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Time& t);

/*  overloading operator+ */
Time operator+(const Time& t1, const Time& t2);

/*  overloading operator- */
Time operator-(const Time& t1, const Time& t2);

/*  overloading operator> */
bool operator>(const Time& t1, const Time& t2);

/*  overloading operator< */
bool operator<(const Time& t1, const Time& t2);

/*  overloading operator== */
bool operator==(const Time& t1, const Time& t2);

/*  overloading operator!= */
bool operator!=(const Time& t1, const Time& t2);

/*  overloading operator <= */
bool operator<=(const Time& t1, const Time& t2);

/*  helper che consente la conversione di oggetti in minuti,
 *  utile nel caso di conversione di differenze di orari (timer) */
int time_to_minutes(const Time& t);

#endif //TIME_H
