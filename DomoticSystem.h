// Alessandro Pattaro 2101822

#ifndef DOMOTICSYSTEM_H
#define DOMOTICSYSTEM_H


#include <set>
#include <vector>
#include <functional>
#include "Time.h"
#include "DomoticDevice.h"
#inlcude "ManualDevice.h"
#include "PresetDevice.h"

class DomoticSystem
{
public:
//  SETUP DI DOMOTICSYSTEM E COMANDI DI CLASSE

    /*  costruttore */
    DomoticSystem();

    /*  aggiunge un dispositivo al vettore all_devices_, indicando
        che l'attuale rete di elettrodomestici comprende anche questo
        dispositivo */
    void add(DomoticDevice d);
    {   all_devices_.push_back(d);}

    /*  consumo del dispositivo dal momento dell'attivazione a quello
        dell'invocazione della funzione stessa */
    double get_consumption(DomoticDevice d) const;

    /*  avanzamento nel tempo */
    void set_time(Time t);

    /*  legge l'ora */
    Time get_time() const
    {   return time_;}


//  FUNZIONI PER L'INTERFACCIA UTENTE

    /*  spegne un dispositivo acceso, rimuovendolo quindi da una delle
        strutture a cui appartiene (connected_devices_ o connected_timer_devices_) */
    void set_off(DomoticDevice d);

    /*  accende un dispositivo, aggiungendolo a una delle due strutture
        a seconda del tipo dell'oggetto: se si tratta di un ManualDevice
        sprovvisto di timer andrà in connected_devices, altrimenti in
        connected_timer_devices_ */
    void set_on(DomoticDevice d);

    /*  accende un dispositivo ManualDevice con un timer nel caso in cui sia spento,
        inserendolo in connected_timer_devices_ , altrimenti, se il dispositivo in
        questione è già acceso, lo rimuove da connected_devices_ per aggiungerlo
        a connected_timer_devices */
    void start_and_stop(ManualDevice m, Time start, Time stop);

    void start_and_stop(PresetDevice p, Time start);

    /*  rimuove il timer associato al dispositivo */
    void remove(ManualDevice m);

    /*  mostra resoconto di tutti i dispositivi inseriti da add in all_devices_ */
    std::string show() const;

    /*  mostra resoconto dello specifico dispositivo */
    std::string show(DomoticDevice d) const;


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
    double const POWER_ = 3.5;

    /*  cap di massimo consumo del sistema */
    double max_supplied_power_ = POWER_;

    /*  gestisce il tempo all'interno di un DomoticSystem.h */
    Time time_;

    /*  coda prioritaria che gestisce i dispositivi connessi
     *  che dispongono di un timer (quindi o dispositivi CP o manuali
     *  con timer inserito) */
    std::multiset<DomoticDevice> connected_timer_devices_;

    /*  vector contenente i dispositivi connessi manuali sprovvisti
     *  di relativo timer */
    std::vector<ManualDevice> connected_devices_;

    /*  vector contenente il resoconto di tutti i dispositivi connessi */
    std::vector<DomoticDevice> all_devices_;

    /*  modifica max_supplied_power_ qualora venga aggiunto un dispositivo
        di produzione energetica */
    void modify_supplied_power(double s);
};

#endif //DOMOTICSYSTEM_H