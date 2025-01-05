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

/*  l'oggetto della classe Time deve essere stampato secondo il formato
 *  hh:mm, come da specifica */
std::ostream& operator<<(std::ostream& os, const Time& t)
{
    os << std::setw(2) << std::setfill('0') << t.get_hours() << ":";
    os << std::setw(2) << std::setfill('0') << t.get_minutes();
    return os;
}

/*  overloading di operator> */
bool operator>(const Time& t1, const Time& t2)
{
    if (t1.get_hours()>t2.get_hours())
        return true;

    if (t1.get_hours()==t2.get_hours())
    {
        if (t1.get_minutes()>t2.get_minutes())
            return true;
        return false;
    }
    return false;
}

/*  overloading di operator< */
bool operator<(const Time& t1, const Time& t2)
{
    if (t1.get_hours()<t2.get_hours())
        return true;

    if (t1.get_hours()==t2.get_hours())
    {
        if (t1.get_minutes()<t2.get_minutes())
            return true;
        return false;
    }
    return false;
}

/*  overloading operator== */
bool operator==(const Time& t1, const Time& t2)
{
    if (t1.get_hours() == t2.get_hours())
    {
        if (t1.get_minutes()==t2.get_minutes())
            return true;
    }
    return false;
}

/*  overloading operator!= */
bool operator!=(const Time& t1, const Time& t2)
{
    if (t1.get_hours() != t2.get_hours())
        return true;
}

/*  overloading operator<= */
bool operator<=(const Time& t1, const Time& t2)
{
    if (t1 == t2 || t1 < t2)
        return true;
    return false;
}

/*  variabile statica pensata per rappresentare l'orario di fine giornata in
 *  DomoticSystem */
const Time Time::kAllDayLongTimer(23,59);
const Time Time::kOneMinute(0,1);

/*  helper che consente la conversione di oggetti in minuti,
 *  utile nel caso di conversione di differenze di orari (timer) */
int time_to_minutes(const Time& t)
{
    int minutes = t.get_minutes() + t.get_hours()*Time::kMinutesPerHour;
    return minutes;
}