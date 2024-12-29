// Alessandro Pattaro 2101822

#include "Time.h"
#include <iomanip>
#include <stdexcept>

/*  costruttore con orario definito */
Time::Time(int h, int m)
{
    /*  controllo di input: non sono ovviamente consentiti
     *  orari inesistenti */
    if (h<0 || h>23 || m<0 || m>59)
        throw std::invalid_argument("Invalid input");

    hours_ = h;
    minutes_ = m;
}

/*  modifica di orario */
void Time::set_time(int h, int m)
{
    /*  controllo di input: non sono ovviamente consentiti
     *  orari inesistenti */
    if (h<0 || h>23 || m<0 || m>59)
        throw std::invalid_argument("Invalid input");

    /*  superati i controlli si effettua l'aggiornamento */
    set_hours(h);
    set_minutes(m);
}

/*  overloading di operator> */
bool Time::operator>(const Time& t) const
{
    if (get_hours()>t.get_hours())
        return true;

    if (get_hours()==t.get_hours())
    {
        if (get_minutes()>t.get_minutes())
            return true;

         return false;
    }

    return false;
}

/*  overloading di operator< */
bool Time::operator<(const Time& t) const
{
    if (get_hours()<t.get_hours())
        return true;

    if (get_hours()==t.get_hours())
    {
        if (get_minutes()<t.get_minutes())
            return true;

        return false;
    }

    return false;
}

/*  l'oggetto della classe Time deve essere stampato secondo il formato
 *  hh:mm, come da specifica */
std::ostream& operator<<(std::ostream& os, const Time& t)
{
    os << std::setw(2) << std::setfill('0') << t.get_hours() << ":";
    os << std::setw(2) << std::setfill('0') << t.get_minutes();
    return os;
}

/*  variabile statica pensata per rappresentare l'orario di fine giornata in
 *  DomoticSystem */
const Time Time::ALL_DAY_LONG_TIMER(23,59);