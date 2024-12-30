// Alessandro Pattaro 2101822

#include "DomoticSystem.h"
#include <algorithm>
#include <stdexcept>

/*  aggiunge un dispositivo alla rete di casa */
void DomoticSystem::add(DomoticDevice& d)
{
    /*  aggiungendo un elettrodomestico alla rete di casa
     *  è necessario inserirlo nella lista dei dispositivi
     *  collegati e creare un'opportuna consumptioncard per
     *  monitorare i consumi dello stesso */
    connected_devices_.push_back(d);
    ConsumptionCard c (d);
    consumption_log_.push_back(c);
}

/*  avanzamento nel tempo */
void DomoticSystem::set_time(Time t)
{
    /*  non è concesso tornare indietro nel tempo */
    if (time_ > t)
    {    throw std::invalid_argument("Invalid input");}

    time_ = t;
}

/*  spegne un dispositivo acceso */
void DomoticSystem::set_off(DomoticDevice& d)
{
    /*  inizialmente è necessario creare il nuovo evento di
     *  spegnimento da inserire nel log */
    Event new_off(d, time_, Event::kOff);
    event_log_.insert(new_off);

    /*  la ricerca dell'evento da rimuovere si basa anche sul tipo
     *  di oggetto coinvolto, quindi è necessario dividere i casi
     *  effettuando un controllo sull'id, in particolare si cerca di
     *  capire se le prime tre lettere di questo corrispondo alla
     *  stringa "MAN", direttamente fornita dalla classe ManualDevice */
    const int kCount = ManualDevice::kManIdentifier.size();
    std::string id = d.get_id();
    std::string begin_id = id.substr(id.begin(), kCount);

    /*  se il confronto ha successo d è un ManualDevice */
    if (begin_id == ManualDevice::kManIdentifier)
    {

    }

    /*  creazione dell'evento cercato */
    Event removing_off(d, )
    Event* ptr = std::find()
}

/*  accende un dispositivo */
void DomoticSystem::set_on(DomoticDevice& d)
{
    /*  è necessario capire che tipo di dispositivo sia d, così
     *  da poter creare un evento con i timer corretti*/
    const int COUNT = ManualDevice::kManIdentifier.size();
    std::string id = d.get_id();
    std::string begin_id = id.substr(id.begin(), COUNT);

    /*  manuale */
    if (begin_id == ManualDevice::kManIdentifier)
    {
        /*  se è manuale ci si serve della variabile statica
         *  ALL_DAY_LONG_TIMER così da essere sicuri che qualsiasi sia
         *  l'orario di inizio il dispositivo rimarrà acceso fino a fine
         *  giornata o, in alternativa, fino all'arrivo di nuove istruzioni.
         *  Creazione dei due Event da inserire in event_log_ */
        Event on(d, time_, Event::kOn);
        Event off(d, Time::ALL_DAY_LONG_TIMER, Event::kOff);

        /*  inserimento */
        event_log_.insert(on);
        event_log_.insert(off);
    }

    /*  ciclo prefissato */
    else
    {
        /*  creazione dei due Event da inserire in event_log_, che
         *  sono già muniti di timer */
        Event on(d, d.get_timer(), Event::kOn);
        Event off(d, d.get_timer(), Event::kOff);

        /*  inserimento */
        event_log_.insert(on);
        event_log_.insert(off);
    }
}

/*  accende un dispositivo ManualDevice con orario di inizio
 *  e di fine prestabiliti */
void DomoticSystem::start_and_stop(ManualDevice& m, Time start, Time stop)
{
    /*  creazione e inserimento degli eventi */
    Event on(m, start, Event::kOn);
    Event off(m, stop, Event::kOff);
    event_log_.insert(on);
    event_log_.insert(off);
}

/*  accende un dispositivo PresetDevice ad un orario futuro prestabilito */
void DomoticSystem::start_and_stop(PresetDevice& p, Time start)
{
    /*  creazione e inserimento degli eventi */
    Event on(p, start, Event::kOn);
    Event off(p, p.get_timer(), Event::kOff);
    event_log_.insert(on);
    event_log_.insert(off);
}

/*  rimuove il timer associato al dispositivo */
void DomoticSystem::remove(ManualDevice& m)
{

}

/*  mostra resoconto energetico di tutti i dispositivi inseriti */
std::string DomoticSystem::show() const
{
    std::string msg;
    int total_consumption;
    int total_production;
    for (ConsumptionCard c : consumption_log_)
    {
        /*  se il dispositivo genera energia */
        if (c.device_.get_power() > 0)
        {
            std::string card ("\n- Il dispositivo " + c.device_.get_name() + " ha prodotto " + c + "\n");
            total_production += c.consumption_;
            msg (msg + card);
        }

        /*  se il dispositivo assorbe energia */
        else
        {
            std::string card ("\n- Il dispositivo " + c.device_.get_name() + " ha consumato " + c + "\n");
            total_consumption += c.consumption_;
            msg (msg + card);
        }
    }

    std::cout << "\n[" << time_ << "] Attualmente il sistema ha prodotto " << total_production;
    std::cout << "e consumato " << total_consumption << ". Nello specifico:" << msg;
}

/*  mostra resoconto energetico del dispositivo */
std::string DomoticSystem::show(DomoticDevice& d) const
{
    /*  cercare in consumption_log_ */
    ConsumptionCard* c_ptr = std::find(consumption_log_.begin(), consumption_log_.end(), d);

    /*  dereference di c_ptr e restituzione del consumo */
    ConsumptionCard c = *c_ptr;

    std::cout << "\n[" + time_ + "] Il dispositivo " + c.device_.get_name()
}