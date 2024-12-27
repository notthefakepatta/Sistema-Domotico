// Alessandro Pattaro 2101822

#ifndef TIME_H
#define TIME_H


#include <iostream>

/*  struct che indica il tempo di un elemento del progetto, sia esso un
 *  DomoticSystem o uno dei dispositivi ad esso collegati */
class Time
{
public:
    /*  costruttore di default */
    Time() : hours(0), minutes(0) {}

    /*  costruttore con orario definito */
    Time(int h, int m) : hours(h), minutes(m) {}

    /*  ore */
    int get_hours() const
    {   return hours;}

    /*  minuti */
    int get_minutes() const
    {   return minutes;}

    /*  modifica di orario */
    void set_time(Time& t, int h, int m);

    /*  overloading operator+ */
    Time operator+(const Time& t) const;

    /*  overloading operator- */
    Time operator-(const Time& t) const;

private:
    int hours;
    int minutes;
};

/*  possibilità di confrontare due orari tra di loro */
int compareTo(const Time &t1, const Time &t2);

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Time& t);

#endif //TIME_H
