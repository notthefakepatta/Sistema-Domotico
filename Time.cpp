// Alessandro Pattaro 2101822

#include "Time.h"
#include <iomanip>
#include <stdexcept>


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

bool Time::operator>(const Time& t) const
{
    if (get_hours()>t.get_hours())
        return true;

    else if (get_hours()==t.get_hours())
    {
        if (get_minutes()>t.get_minutes())
            return true;
    }

    else
        return false;
}

/*  confronta due orari */
int compareTo(const Time& t1, const Time& t2)
{
    /*  distinzione dei casi. Il risultato fa riferimento al rapporto
     *  del primo orario rispetto al secondo: esso corrisponde a 1, 0, -1
     *  a seconda dell'esito della differenza rispettivamente di ore e minuti */
    int const MAGGIORE = 1;
    int const MINORE = -1;
    int const UGUALE = 0;

    /*  controllo della differenza tra le ore, da cui dipende
     *  l'eventuale controllo della differenza tra minuti nel caso di
     *  hours_difference == 0. Negli altri due casi quest'ultimo non
     *  è necessario in quanto il risultato è già completamente definito */
    int hours_difference;
    int h1 = t1.get_hours();
    int h2 = t2.get_hours();
    switch (hours_difference = h1 - h2)
    {
        case hours_difference > 0:
            return MAGGIORE;
            break;

        case hours_difference == 0:
        {
            /*  controllo della differenza tra i minuti */
            int minutes_difference;
            int m1 = t1.get_minutes();
            int m2 = t2.get_minutes();
            switch (minutes_difference = m1 - m2)
            {
                case minutes_difference > 0:
                    return MAGGIORE;
                    break;

                case minutes_difference == 0:
                    return UGUALE;
                    break;

                case minutes_difference < 0:
                    return MINORE;
                    break;
            }
            break;
        }

        case hours_difference < 0:
            return MINORE;
            break;
    }
}

/*  l'oggetto della classe Time deve essere stampato secondo il formato
 *  hh:mm, come da specifica */
std::ostream& operator<<(std::ostream& os, const Time& t)
{
    os << std::setw(2) << std::setfill('0') << t.get_hours() << ":";
    os << std::setw(2) << std::setfill('0') << t.get_minutes();
    return os;
}