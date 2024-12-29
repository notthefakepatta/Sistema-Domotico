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
    /*  costruttore di default */
    Time() : hours_(0), minutes_(0) {}

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
    void set_time(int h, int m);


//  OVERLOADING OPERATORI UTILI
    /*  overloading operator+ */
    Time operator+(const Time& t) const;

    /*  overloading operator- */
    Time operator-(const Time& t) const;

    /*  overloading operator> */
    bool operator>(const Time& t) const;

    /*  overloading operator< */
    bool operator<(const Time& t) const;


//  VARIABILE STATICA DI CLASSE
    static const Time ALL_DAY_LONG_TIMER;


private:
    int hours_;
    int minutes_;

    void set_hours(int h)
    {   hours_ = h;}
    void set_minutes(int m)
    {   minutes_ = m;}
};

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Time& t);

#endif //TIME_H
