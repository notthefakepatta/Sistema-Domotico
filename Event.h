//  Alessandro Pattaro 2101822

#ifndef EVENT_H
#define EVENT_H
#include "Time.h"
#include "DomoticDevice.h"

struct Event
{
//  ISTANZE DELLA STRUCT
    /*  dispositivo */
    DomoticDevice& device_;

    /*  tempo in cui avviene l'evento di accensione o spegnimento */
    Time start_or_end_time_;

    /*  stato del dispositivo: false indica spegnimento del dispositivo,
     *  true la sua accensione */
    bool status_;

    /* indicatore della natura dell'evento:
     * nel momento in cui viene inserito un oggetto Event all'interno del multiset event_log_ di DomoticSystem
     * è necessario avere un modo di sapere se il trigger dell'aggiunta di questo sia stato il comando
     * set ${DEVICENAME} on/off oppure il comando set ${DEVICENAME} ${START} [${STOP}] */
    bool trigger_;

//  COSTRUTTORE
    Event(DomoticDevice& d, Time t, bool s, bool tr)
        : device_(d), start_or_end_time_(t), status_(s) {}

//  VARIABILI STATICHE DI CLASSE
    static const bool kOn = true;
    static const bool kOff = false;

    static const bool kTimerTrigger = true;
    static const bool kManualTrigger = false;
};

//  OVERLOADING OPERATORI UTILI
/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Event& e);

/*  overloading operator< */
bool operator<( const Event& e1, const Event& e2);

#endif //EVENT_H
