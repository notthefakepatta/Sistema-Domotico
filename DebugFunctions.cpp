// Giovanni Cerin 2111532

#include "DomoticSystem.h"

void DomoticSystem::reset_time()
{
    // reset del tempo del sistema
    time_ = Time();

    // eliminia da event_log_ tutti gli eventi di accensione/spegnimento non associati a dei timer
    for(Event e : event_log_)
    {
        if(e.trigger_ == Event::kJustOnOff)
            event_log_.erase(e);
    }

    // porta tutti i dispositivi alle condizioni iniziali
    for(DomoticDevice& generic_device : connected_devices_)
    {
        Event initial_conditions(generic_device, time_, Event::kOff, Event::kJustOnOff);
        event_log_.insert(initial_conditions);
    }
}

/*  rimuove tutti i timers mantenendo lo stato attuale dei dispositivi */
void DomoticSystem::reset_timers()
{
    // eliminia da event_log_ tutti gli eventi di accensione/spegnimento associati a dei timer
    for(Event e : event_log_)
    {
        if(e.trigger_ == Event::kTimer)
            event_log_.erase(e);
    }
}

/*  riporta il sistema alle condizioni iniziali, rimuovendo anche i timer */
void DomoticSystem::reset_all()
{
    // reset del tempo del sistema
    time_ = Time();

    // eliminia da event_log_ tutti gli eventi
    event_log_.clear();
    
    // porta tutti i dispositivi alle condizioni iniziali
    for(DomoticDevice& generic_device : connected_devices_)
    {
        Event initial_conditions(generic_device, time_, Event::kOff, Event::kJustOnOff);
        event_log_.insert(initial_conditions);
    }
}