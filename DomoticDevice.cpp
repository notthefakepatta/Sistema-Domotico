#include "DomoticDevice.h"

std::string DomoticDevice::get_name() const
{
    return name_;
}

double DomoticDevice::get_power() const
{
    return power_amount_;
}

Time DomoticDevice::get_off_time() const
{
    return turn_off_time_;
}

Time DomoticDevice::get_on_time() const
{
    return turn_on_time_;
}

Time DomoticDevice::get_timer() const
{
    return timer_;
}

void DomoticDevice::set_off_time(Time& t)
{
    turn_off_time_ = Time(t.get_hours(), t.get_minutes());
}

void DomoticDevice::set_on_time(Time& t)
{
    turn_on_time_ = Time(t.get_hours(), t.get_minutes());
}

void DomoticDevice::set_name(std::string new_name)
{
    name_ = new_name;
}