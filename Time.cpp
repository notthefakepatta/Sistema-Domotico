// Alessandro Pattaro 2101822

#include "Time.h"
#include <iomanip>
#include <stdexcept>

void set_time(Time& t, int h, int m)
{
    /*  controllo di input: non sono ovviamente consentiti
     *  orari inesistenti */
    if (h<0 || h>23 || m<0 || m>59)
        throw std::invalid_argument("Invalid input");

    /*  confronto tra il nuovo orario e quello che sta per essere
     *  sostituito: non è consentito tornare indietro nel tempo */
    Time t2;
    t2.hours = h;
    t2.minutes = m;

    if (compareTo(const Time& t,const Time& t2)<0)
        throw std::invalid_argument("Invalid input");

    /*  superati i controlli si effettua l'aggiornamento */
    t = t2;
}

int compareTo(const Time& t1, const Time& t2)
{
    /*  distinzione dei casi. Il risultato fa riferimento al rapporto
     *  del primo orario rispetto al secondo: esso corrisponde a 1, 0, -1
     *  a seconda dell'esito della differenza rispettivamente di ore e minuti */
    int maggiore = 1;
    int minore = -1;
    int uguale = 0;

    /*  controllo della differenza tra le ore, da cui dipende
     *  l'eventuale controllo della differenza tra minuti nel caso di
     *  hours_difference == 0. Negli altri due casi quest'ultimo non
     *  è necessario in quanto il risultato è già completamente definito */
    int hours_difference;
    switch (hours_difference = t1.hours - t2.hours)
    {
        case hours_difference > 0:
            return maggiore;
            break;

        case hours_difference == 0:
        {
            /*  controllo della differenza tra i minuti */
            int minutes_difference;
            switch (minutes_difference = t1.minutes - t2.minutes)
            {
                case minutes_difference > 0:
                    return maggiore;
                    break;

                case minutes_difference == 0:
                    return uguale;
                    break;

                case minutes_difference < 0:
                    return minore;
                    break;
            }
            break;
        }

        case hours_difference < 0:
            return minore;
            break;
    }
}

/*  l'oggetto della classe Time deve essere stampato secondo il formato
 *  hh:mm, come da specifica */
std::ostream& operator<<(std::ostream& os, const Time& t)
{
    os << std::setw(2) << std::setfill('0') << t.hours << ":";
    os << std::setw(2) << std::setfill('0') << t.minutes;
    return os;
}