#include "DomoticDevice.h"

std::string DomoticDevice::get_name() const
{
    return name_;
}

double DomoticDevice::get_power() const
{
    return power_amount_;
}

void DomoticDevice::set_name(std::string new_name)
{
    name_ = new_name;
}