//  ALESSANDRO PATTARO 2101822

#ifndef EVENT_H
#define EVENT_H
#include "Time.h"
#include "DomoticDevice.h"

struct Event
{
    //  dispositivo
    DomoticDevice device_;

    //  tempo in cui avviene l'evento di accensione o spegnimento
    Time start_or_end_time_;

    /*  stato del dispositivo: false indica spegnimento del dispositivo,
     *  true la sua accensione */
    bool status_;

    //  costruttore
    Event(const DomoticDevice& d, Time t, bool& s)
        : device_(d), start_or_end_time_(t), status_(s) {}


    static const bool ON = true;
    static const bool OFF = false;
};

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Event& e);

/*  overloading operator< */
bool operator<( const Event& e1, const Event& e2);

#endif //EVENT_H
