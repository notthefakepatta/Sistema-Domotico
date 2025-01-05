//  Alessandro Pattaro 2101822

#ifndef EVENT_H
#define EVENT_H
#include "Time.h"
#include "ConsumptionCard.h"


struct Event
{
//  ISTANZE DELLA STRUCT
    /*  dispositivo */
    ConsumptionCard& device_card_;

    /*  tempo in cui avviene l'evento di accensione o spegnimento */
    Time start_or_end_time_;

    /*  stato del dispositivo: false indica spegnimento del dispositivo,
     *  true la sua accensione */
    bool status_;

    /*  tipo di trigger del dispositivo: riconosce se esso è acceso manualmente
     *  tramite set_on/off o tramite start_and_stop */
    bool trigger_;

    /*  indica se ignorare o meno l'evento: viene settato a false di default
     *  (false == non ignorare l'evento) */
    bool ignore_;

//  COSTRUTTORE
    Event(ConsumptionCard& c, Time t)
        : device_card_(c), start_or_end_time_(t), ignore_(false) {}

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
bool operator<(const Event& e1, const Event& e2);

/*  overloading operator== */
bool operator==(const Event& e, const DomoticDevice& d)
{   return e.device_card_.device_.get_id() == d.get_id();}

#endif //EVENT_H
