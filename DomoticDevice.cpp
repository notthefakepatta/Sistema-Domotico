#include "DomoticDevice.h"

DomoticDevice::DomoticDevice()
{
    name_ = "";
    power_amount_ = 0;
}

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