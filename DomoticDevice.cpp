#include "DomoticDevice.h"

std::string DomoticDevice::get_name() const
{
    return name_;
}

double DomoticDevice::get_power() const
{
    return power_amount_;
}

// L'operatore == confronta soltanto gli ID dei dispositivi in quanto univoci
bool DomoticDevice::operator==(const DomoticDevice& d)
{
    return get_id() == d.get_id();
}