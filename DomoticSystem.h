// Alessandro Pattaro 2101822

#ifndef DOMOTICSYSTEM_H
#define DOMOTICSYSTEM_H


#include <set>
#include <vector>
#include <map>
#include "Time.h"
#include "Event.h"
#include "ConsumptionCard.h"
#include "DomoticDevice.h"
#include "ManualDevice.h"
#include "PresetDevice.h"

class DomoticSystem
{
public:
//  SETUP DI DOMOTICSYSTEM E COMANDI DI CLASSE
    /*  costruttore */
    DomoticSystem();

    /*  aggiunge un dispositivo al vettore all_devices_, indicando
        che l'attuale rete di elettrodomestici comprende anche questo dispositivo */
    void add(const DomoticDevice& d);

    /*  avanzamento nel tempo */
    void set_time(Time t);

    /*  legge l'ora */
    Time get_time() const
    {   return time_;}


//  FUNZIONI PER L'INTERFACCIA UTENTE

    /*  spegne un dispositivo acceso */
    void set_off(const std::string);

    /*  accende un dispositivo */
    void set_on(const std::string);

    /*  accende un dispositivo ManualDevice con orario di inizio
     *  e di fine prestabiliti */
    void start_and_stop(const std::string, Time start, Time stop);

    /*  accende un dispositivo PresetDevice ad un orario futuro prestabilito */
    void start_and_stop(const std::string, Time start);

    /*  rimuove il timer associato al dispositivo */
    void remove(const std::string);

    /*  mostra resoconto energetico di tutti i dispositivi inseriti */
    void show();

    /*  mostra resoconto dello specifico dispositivo */
    void show(const std::string);


//  COMANDI PER IL DEBUG

    /*  resetta tempo e dispositivi alla condizione iniziale; eventuali
        timer vengono mantenuti */
    void reset_time();

    /*  rimuove tutti i timers mantenendo lo stato attuale dei dispositivi */
    void reset_timers();

    /*  riporta il sistema alle condizioni iniziali, rimuovendo anche i timer */
    void reset_all();



private:
    /*  costante di potenza energetica fornita, 3.5kW come da specifica */
    double const kPower_ = 3.5;

    /*  cap di massimo consumo del sistema */
    double power_available_ = kPower_;

    /*  gestisce il tempo all'interno di un DomoticSystem.h */
    Time time_;

    /*  registro eventi di accensione e spegnimento di un dispositivo */
    std::multiset<Event> event_log_;

    /*  registro di consumo */
    std::map<std::string, ConsumptionCard> consumption_log_;

    /*  modifica max_supplied_power_ qualora venga aggiunto un dispositivo di produzione energetica */
    void modify_power_available(double s);

    /*  aggiorna con i dati mancanti il consumo di un dispositivo nell'apposita card se è necessario
        ovvero in caso di cicli non ultimati */
    void update_consumption(ConsumptionCard& c);
};

#endif //DOMOTICSYSTEM_H
