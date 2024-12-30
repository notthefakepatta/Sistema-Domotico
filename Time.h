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

//  VARIABILI STATICHE DI CLASSE
    static const Time kAllDayLongTimer;
    static const int kMinutesPerHour = 60;

private:
    int hours_;
    int minutes_;

    void set_hours(int h)
    {   hours_ = h;}
    void set_minutes(int m)
    {   minutes_ = m;}
};

//  OVERLOADING OPERATORI UTILI
/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Time& t);

//  HELPER FUNCTION
/*  helper che consente la conversione di oggetti in minuti,
 *  utile nel caso di conversione di differenze di orari (timer) */
int time_to_minutes(const Time& t);

#endif //TIME_H
