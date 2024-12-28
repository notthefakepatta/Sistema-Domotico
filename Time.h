// Alessandro Pattaro 2101822

#ifndef TIME_H
#define TIME_H


#include <iostream>

/*  struct che indica il tempo di un elemento del progetto, sia esso un
 *  DomoticSystem.h o uno dei dispositivi ad esso collegati */
class Time
{
public:
//  COSTRUTTORI
    /*  costruttore di default */
    Time() : hours(0), minutes(0) {}

    /*  costruttore con orario definito */
    Time(int h, int m);


//  LETTURA ISTANZE PRIVATE
    /*  ore */
    int get_hours() const
    {   return hours_;}

    /*  minuti */
    int get_minutes() const
    {   return minutes_;}

//  MODIFICA ISTANZE PRIVATE
    /*  modifica di orario */
    void set_time(Time& t, int h, int m);


//  OVERLOADING OPERATORI UTILI
    /*  overloading operator+ */
    Time operator+(const Time& t) const;

    /*  overloading operator- */
    Time operator-(const Time& t) const;

    /*  overloading operator> */
    bool operator>(const Time& t) const;

    /*  overloading operator< */
    bool operator<(const Time& t) const;


private:
    int hours_;
    int minutes_;
};

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Time& t);

#endif //TIME_H
