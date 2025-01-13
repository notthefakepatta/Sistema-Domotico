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

bool operator>=(const Time& t1, const Time& t2)
{
    return t1 > t2 || t1 == t2;
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
    return false;
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

/*  overloading operator+ */
Time operator+(const Time& t1, const Time& t2)
{
    int sum_minutes;
    int sum_hours;

    sum_minutes = (t1.get_minutes() + t2.get_minutes()) % 60;
    sum_hours = t1.get_hours() + t2.get_hours() + (t1.get_minutes() + t2.get_minutes()) / 60;
    
    if(sum_hours > 23)
    {
        sum_hours = 23;
        sum_minutes = 59;
    }

    Time time_sum(sum_hours, sum_minutes);
    return time_sum;
}

/*  overloading operator- */
Time operator-(const Time& t1, const Time& t2)
{
    int dif_hours = 0;
    int dif_minutes = 0;

    dif_minutes = t1.get_minutes() - t2.get_minutes();
    if(dif_minutes < 0)
    {
        dif_hours--;
        dif_minutes += 60;
    }
    
    dif_hours += t1.get_hours() - t2.get_hours();
    if(dif_hours < 0)
    {
        dif_hours = 0;
        dif_minutes = 0;
    }

    Time time_dif(dif_hours, dif_minutes);
    return time_dif;
}