// Alessandro Pattaro 2101822

#ifndef TIME_H
#define TIME_H

#include <iostream>

/*  struct che indica il tempo di un elemento del progetto, sia esso un
 *  DomoticSystem o uno dei dispositivi ad esso collegati */
struct Time
{
    /*  di default viene impostato all'orario 00:00 */
    int hours=0;
    int minutes=0;
};

/*  possibilità di settare l'orario desiderato, purché questo sia
 *  un valore accettabile compreso tra [00:00] e [23:59] e che l'aggiornamento
 *  di questo avvenga sempre in senso crescente: non è permesso "tornare
 *  indietro" nel tempo */
void set_time(Time& t, int h, int m);

/*  possibilità di confrontare due orari tra di loro */
int compareTo(const Time &t1, const Time &t2);

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Time& t);

#endif //TIME_H
