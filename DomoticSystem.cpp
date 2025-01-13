// Alessandro Pattaro 2101822

#include "DomoticSystem.h"
#include <algorithm>
#include <stdexcept>
#include <cmath>

DomoticSystem::DomoticSystem() : time_(), event_log_(), consumption_log_() {}

/*  aggiunge un dispositivo alla rete di casa */
void DomoticSystem::add(const DomoticDevice& d)
{
    /*  aggiungendo un elettrodomestico alla rete di casa è necessario creare un'opportuna consumptioncard per
     *  monitorare i consumi dello stesso. */
    ConsumptionCard c(d);

    /*  controllare che il dispositivo non sia già inserito */
    std::map<std::string, ConsumptionCard>::iterator it = consumption_log_.find(c.device_.get_name());
    if (it != consumption_log_.end())
        throw std::logic_error("The device already exists");
    /*  inserimento rispettando il binomio chiave-valore della mappa */
    consumption_log_.insert({c.device_.get_name(), c});




    // DEBGUG
    //for(auto it = consumption_log_.begin(); it != consumption_log_.end(); it++)
        //std::cout << static_cast <ManualDevice&>(const_cast<DomoticDevice&>(it->second.device_)) << std::endl;
}

/*  avanzamento nel tempo */
void DomoticSystem::set_time(Time t)
{
    /*  non è concesso tornare indietro nel tempo */
    if (time_ > t)
    {    throw std::invalid_argument("Invalid input");}

    /*  gestione dei consumi: è necessario scandire il range in cui gli eventi vanno esaminati e stampati, ovvero
     *  tutti quelli nell'intervallo dal precedente valore di time all'ultimo aggiornato */
    Time first = time_;
    std::multiset<Event>::iterator start = std::find_if(event_log_.begin(), event_log_.end(),
                                            [this, &first] (const Event& e){return e.start_or_end_time_ >= first;});

    std::multiset<Event>::iterator end = std::find_if(event_log_.begin(), event_log_.end(), [this, &t] (const Event& e) {return e.start_or_end_time_ > t + Time::kOneMinute;});

    std::cout << "[" << time_ << "] " << "L'orario attuale e' " << time_ << std::endl;

    while (start != end)
    {
        Event& e = const_cast<Event&>(*start);

        if (e.ignore_ == false)
        {
            std::cout << e;

            /*  caso di spegnimento di un dispositivo */
            if (e.status_ == Event::kOff)
            {
                e.device_card_.status_ = ConsumptionCard::kOff;

                /*  aggiornamento consumo del dispositivo dall'ultimo check a al momento del suo spegnimento */
                Time elapsed_time = e.start_or_end_time_ - e.device_card_.last_check_;
                double energy_per_minute = e.device_card_.device_.get_power()/Time::kMinutesPerHour;
                double new_consumption = time_to_minutes(elapsed_time)*energy_per_minute;
                e.device_card_.consumption_ += new_consumption;

                /*  modificare la potenza disponibile: che sia un dispositivo di consumo o produzione di energia,
                 *  per ripristinare la potenza disponibile al valore precedente all'utilizzo dello stesso è necessario
                 *  prendere la potenza col segno opposto */
                double p = e.device_card_.device_.get_power();
                modify_power_available(-p);
            }
            /*  accensione */
            else
            {
                e.device_card_.status_ = ConsumptionCard::kOn;

                /*  controllo che venga rispettato il limite di potenza disponibile: se così non fosse, come da
                    specifica, si spegne in ordine inverso i dispositivi fino a tornare sotto il limite */
                double p = e.device_card_.device_.get_power();
                if (p < 0 && std::abs(p) > power_available_)
                {   set_off(e.device_card_.device_.get_name());}

                else
                {
                    /*  aggiornamento latest_check e dello status */
                    modify_power_available(p);
                    e.device_card_.last_check_ = e.start_or_end_time_;
                }
            }
        }
        ++start;
    }

    /*  aggiornamento di time_ */
    time_ = t;

    /*  aggiornamento consumi di cicli non ancora terminati */
    for (std::map<std::string, ConsumptionCard>::iterator it = consumption_log_.begin(); it != consumption_log_.end(); it++)
    {
        ConsumptionCard& c = it->second;
        update_consumption(c);
        c.last_check_ = time_;
    }

    std::cout << "[" << time_ << "] " << "L'orario attuale e' " << time_ << std::endl;
}

/*  spegne un dispositivo acceso */
void DomoticSystem::set_off(const std::string s)
{
    /*  il dispositivo deve fare parte del sistema */
    std::map<std::string, ConsumptionCard>::iterator it_map = consumption_log_.find(s);
    if (it_map == consumption_log_.end())
        throw std::invalid_argument("Device not found");

    ConsumptionCard& c = it_map->second;
    if (c.status_ != ConsumptionCard::kOn)
        throw std::domain_error("Device is currently off");

    /*  creazione dell'evento */
    Event new_off(c, time_);

    /*  settare status e trigger, inserimento nel log */
    new_off.status_ = Event::kOff;
    new_off.trigger_ = Event::kManualTrigger;
    event_log_.insert(new_off);

    /*  cambio stato della card */
    c.status_ = ConsumptionCard::kOff;

    /*  impostare come ignore l'evento precedentemente disposto per lo spegnimento. E' necessario controllare partendo
     *  dalla prima occorrenza di spegnimento del dispositivo nell'intervallo ]time_ : kAllDayLongTimer]*/
    std::multiset<Event>::iterator it = std::find_if(event_log_.begin(), event_log_.end(),
                                    [this] (const Event& e){   return e.start_or_end_time_ > time_;});

    while (it != event_log_.end())
    {
        Event& e = const_cast<Event&>(*it);
        if (e == c.device_ && e.ignore_ == false)
        {
            e.ignore_ = true;
            it = event_log_.end();
        }
        it++;
    }
}

/*  accende un dispositivo */
void DomoticSystem::set_on(const std::string s)
{
    /*  il dispositivo deve fare parte del sistema! */
    std::map<std::string, ConsumptionCard>::iterator it_map = consumption_log_.find(s);
    if (it_map == consumption_log_.end())
        throw std::invalid_argument("Device not found");

    ConsumptionCard& c = it_map->second;
    /*  il dispositivo deve essere spento, motivo per cui è necessario effettuare la scannerizzazione di event_log_ partendo
     *  da time_ e procedendo a ritroso fino alla prima occorrenza che riguarda il dispositivo: se questa non viene trovata
     *  o corrisponde a uno spegnimento allora si può procedere */
    if (c.status_ == ConsumptionCard::kOn)
        throw std::domain_error("Device is already on");

    /*  è necessario capire che tipo di dispositivo sia d, così da poter creare un evento con i timer corretti */
    const int COUNT = ManualDevice::kManIdentifier.size();
    std::string id = c.device_.get_id();
    std::string begin_id (id.begin(), id.begin() +COUNT);

    /*  manuale */
    if (begin_id == ManualDevice::kManIdentifier)
    {
        /*  se è manuale ci si serve della variabile statica
         *  ALL_DAY_LONG_TIMER così da essere sicuri che qualsiasi sia
         *  l'orario di inizio il dispositivo rimarrà acceso fino a fine
         *  giornata o, in alternativa, fino all'arrivo di nuove istruzioni.
         *  Creazione dei due Event da inserire in event_log_ */
        Event on(c, time_);
        on.trigger_ = Event::kManualTrigger;
        on.status_ = Event::kOn;

        Event off(c, Time::kAllDayLongTimer);
        off.trigger_ = Event::kManualTrigger;
        off.status_ = Event::kOff;

        /*  inserimento */
        event_log_.insert(on);
        event_log_.insert(off);
    }

    /*  ciclo prefissato */
    else
    {
        /*  creazione dei due Event da inserire in event_log_, che
         *  sono già muniti di timer */
        Event on(c, time_);
        on.trigger_ = Event::kManualTrigger;
        on.status_ = Event::kOn;

        /*  E' necessario fare un downcast di d, in quanto non è possibile la lettura del timer */
        const DomoticDevice* d_ptr = &c.device_;
        const PresetDevice* p_ptr = static_cast<const PresetDevice*>(d_ptr);

        Event off(c, time_ + p_ptr->get_timer());
        off.trigger_ = Event::kManualTrigger;
        off.status_ = Event::kOff;

        /*  inserimento */
        event_log_.insert(on);
        event_log_.insert(off);
    }
}

/*  accende un dispositivo ManualDevice con orario di inizio
 *  e di fine prestabiliti */
void DomoticSystem::start_and_stop(const std::string s, Time start, Time stop)
{
    /*  il dispositivo deve fare parte del sistema */
    std::map<std::string, ConsumptionCard>::iterator it_map = consumption_log_.find(s);
    if (it_map == consumption_log_.end())
    {    throw std::invalid_argument("Device not found");}

    /*  è concesso programmare solo nel futuro */
    if (time_ > start || time_ > stop)
    {    throw std::invalid_argument("Invalid input");}

    /*  controllo correttezza di input: start deve essere un orario antecedente a stop*/
    if (start > stop)
    {    throw std::invalid_argument("Invalid input");}

    /*  riconoscimento della card */
    ConsumptionCard& c = it_map->second;

    /*  creazione e inserimento degli eventi */
    Event on(c, start);
    on.status_ = Event::kOn;
    on.trigger_ = Event::kTimerTrigger;

    Event off(c, stop);
    off.status_ = Event::kOff;
    off.trigger_ = Event::kTimerTrigger;

    event_log_.insert(on);
    event_log_.insert(off);

    std::cout << "[" << time_ << "]" << " Impostato un timer per il dispositivo " << c.device_.get_name();
    std::cout << " dalle " << start << " alle " << stop << std::endl;
}

/*  accende un dispositivo PresetDevice ad un orario futuro prestabilito */
void DomoticSystem::start_and_stop(const std::string s, Time start)
{
    /*  il dispositivo deve fare parte del sistema */
    std::map<std::string, ConsumptionCard>::iterator it_map = consumption_log_.find(s);
    if (it_map == consumption_log_.end())
        throw std::invalid_argument("Device not found");

    /*  è concesso programmare solo nel futuro */
    if (time_ > start)
        throw std::domain_error("Invalid input");

    ConsumptionCard& c = it_map->second;

    /*  creazione e inserimento degli eventi */
    Event on(c, start);
    on.status_ = Event::kOn;
    on.trigger_ = Event::kTimerTrigger;

    Time stop = start + c.device_.get_timer();
    Event off(c, stop);
    on.status_ = Event::kOff;
    on.trigger_ = Event::kTimerTrigger;

    event_log_.insert(on);
    event_log_.insert(off);

    std::cout << "[" << time_ << "]" << " Impostato un timer per il dispositivo " << c.device_.get_name();
    std::cout << " dalle " << start << " alle " << stop << std::endl;
}

/*  rimuove il timer associato al dispositivo */
void DomoticSystem::remove(const std::string s)
{
    /*  il dispositivo deve fare parte del sistema */
    std::map<std::string, ConsumptionCard>::iterator it_map = consumption_log_.find(s);
    if (it_map == consumption_log_.end())
        throw std::invalid_argument("Device not found");

    /*  la rimozione di un timer per un dispositivo manuale corrisponde all'eliminazione di ogni evento che riguarda il dispositivo
     *  da event_log_ tranne la prima accensione che avverrà/è avvenuta, infatti rimuovendo tutti i timer il dispositivo
     *  è destinato a non spegnersi più dopo di essa. E' necessario dividere in due casi, ovvero quello in cui al
     *  momento dell'esecuzione il dispositivo è spento e quando invece è acceso */
    ConsumptionCard& c = it_map->second;
    const DomoticDevice& d_ref = c.device_;
    std::multiset<Event>::iterator first_occurrence_it = std::find_if(event_log_.begin(), event_log_.end(),
                                                            [this, &d_ref] (const Event& e){   return e == d_ref;});


    /*  se la prima occorrenza è di accensione del dispositivo, questa non va rimossa e
     *  quindi va incrementato l'iteratore affinché la escluda dall'algoritmo for_each, al
     *  contrario se si tratta di spegnimento va compresa nell'eliminazione */
    if (first_occurrence_it != event_log_.end() /*&& first_occurrence_it->status_ == Event::kOn*/)
    {   ++first_occurrence_it;}

    /*  ricerca e settaggio a ignore */
    for (; first_occurrence_it != event_log_.end(); ++first_occurrence_it)
    {
        if (first_occurrence_it->device_card_ == c.device_)
        {
            Event& non_const = const_cast<Event&>(*first_occurrence_it);
            non_const.ignore_ = true;
        }
    }

    /*  aggiunta di evento di spegnimento per m a fine giornata in quanto manual */
    Event new_off(c, Time::kAllDayLongTimer);
    new_off.status_ = Event::kOff;
    new_off.trigger_ = Event::kManualTrigger;
    event_log_.insert(new_off);
}

/*  mostra resoconto energetico di tutti i dispositivi inseriti */
void DomoticSystem::show()
{
    /*  è necessario calcolare il totale di produzione e assorbimento
     *  di energia di tutti i dispositivi registrati in consumption_log_ */
    std::string msg;
    double total_consumption = ConsumptionCard::kDefaultConsumption;
    double total_production = ConsumptionCard::kDefaultConsumption;

    for (std::map<std::string, ConsumptionCard>::iterator it_map = consumption_log_.begin(); it_map != consumption_log_.end(); ++it_map)
    {
        ConsumptionCard& c = it_map->second;
        /*  calcolo produzione */
        if (c.device_.get_power()>0)
        {   total_production = total_production + c.consumption_;}

        /*  o assorbimento */
        else
        {   total_consumption += c.consumption_;}

        /*  aggiornamento del resoconto */
        msg += "\n- " + to_string(c);
    }

    /*  completamento del messaggio e stampa */
    std::cout << "[" << time_ << "]" << " Attualmente il sistema ha prodotto " << std::abs(total_production) << " kWh";
    std::cout << " e consumato " << std::abs(total_consumption) << " kWh. Nello specifico:" << msg <<std::endl;
}

/*  mostra resoconto energetico del dispositivo */
void DomoticSystem::show(const std::string s)
{
    /*  cerca la card in consumption_log_ */
    std::map<std::string, ConsumptionCard>::iterator it_map = consumption_log_.find(s);

    /*  il dispositivo deve fare parte del sistema */
    if (it_map == consumption_log_.end())
        throw std::invalid_argument("Device not found");

    ConsumptionCard& c = it_map->second;

    std::cout << "[" << time_ << "]" << " " << c << std::endl;
}

/*  modifica max_supplied_power_ qualora venga aggiunto un dispositivodi produzione energetica */
void DomoticSystem::modify_power_available(double s)
{   power_available_ += s;}

/*  aggiorna coi dati mancanti il consumo di un dispositivo nell'apposita card se è necessario */
void DomoticSystem::update_consumption(ConsumptionCard& c)
{
    /*  aggiornamento se necessario */
    if (c.status_ == ConsumptionCard::kOn)
    {
        Time enlapsed_time = time_ - c.last_check_;
        double energy_per_minute = c.device_.get_power()/Time::kMinutesPerHour;
        double new_consumption = time_to_minutes(enlapsed_time)*energy_per_minute;
        c.consumption_ += new_consumption;
    }
}

void DomoticSystem::reset_time()
{
    // reset del tempo del sistema
    time_ = Time();

    // eliminia da event_log_ tutti gli eventi di accensione/spegnimento non associati a dei timer
    for(Event e : event_log_)
    {
        if(e.trigger_ == Event::kManualTrigger)
            event_log_.erase(e);
    }

    // porta tutti i dispositivi alle condizioni iniziali
    for(std::map<std::string, ConsumptionCard>::iterator it = consumption_log_.begin(); it != consumption_log_.end(); it++)
    {
        it->second.status_ = ConsumptionCard::kOff;
        it->second.consumption_ = ConsumptionCard::kDefaultConsumption;
        it->second.last_check_ = Time();
    }
}

/*  rimuove tutti i timers mantenendo lo stato attuale dei dispositivi */
void DomoticSystem::reset_timers()
{
    // eliminia da event_log_ tutti gli eventi di accensione/spegnimento associati a dei timer
    for(Event e : event_log_)
    {
        if(e.trigger_ == Event::kTimerTrigger)
            event_log_.erase(e);
    }
}

/*  riporta il sistema alle condizioni iniziali, rimuovendo anche i timer */
void DomoticSystem::reset_all()
{
    reset_time();
    reset_timers();
}