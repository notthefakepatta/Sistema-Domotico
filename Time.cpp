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
void Time::set_time(Time& t, int h, int m)
{
    /*  controllo di input: non sono ovviamente consentiti
     *  orari inesistenti */
    if (h<0 || h>23 || m<0 || m>59)
        throw std::invalid_argument("Invalid input");

    /*  superati i controlli si effettua l'aggiornamento */
    Time t2 = Time(h, m);
    t = t2;
}

/*  overloading operator+ */
Time Time::operator+(const Time& t) const
{
    int sum_minutes;
    int sum_hours;

    sum_minutes = (get_minutes() + t.get_minutes()) % 60;
    sum_hours = get_hours() + t.get_hours() + (get_minutes() + t.get_minutes()) / 60;
    if(sum_minutes > 23 && sum_hours > 59)
    {
        sum_hours = 23;
        sum_minutes = 59;
    }

    Time time_sum(sum_hours, sum_minutes);
    return time_sum;
}

/*  overloading operator- */
//Time Time::operator-(const Time& t) const
//{
//    return;
//}

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
