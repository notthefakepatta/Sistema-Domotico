#include "PreSetDevice.h"

int PreSetDevice::preset_device_counter_ = 0;

// Construcotrs
PreSetDevice::PreSetDevice()
{
    name_= "";
    power_amount_ = 0;
    id_ = "";
    timer_ = Time();
}

PreSetDevice::PreSetDevice(std::string name_set, double power_set, Time& working_time)
{
    name_ = name_set;
    power_amount_ = power_set;
    id_ = "PRE" + std::to_string(preset_device_counter_);
    preset_device_counter_++;
    timer_ = Time(working_time.get_hours(), working_time.get_minutes());
}

// Getter
std::string PreSetDevice::get_id() const
{
    return id_;
}

Time PreSetDevice::get_timer()
{
    return timer_;
}

// Operator overloading <<
std::ostream& operator<<(std::ostream& os, PreSetDevice& to_print)
{
    os << "Device name: " << to_print.get_name() << std::endl;
    os << "Type: pre set cycle (PRE)" << std::endl;
    os << "ID: " << to_print.get_id() << std::endl;
    os << "Working time: " << to_print.get_timer().get_hours() << " ore e " << to_print.get_timer().get_minutes() << " minuti" << std::endl;

    /* Piccola modifica al messaggio stampato in output:
     * vengono stampate "power usage" o "power supplied"
     * rispettivamente se si ha a che fare con un disposiotivo che consuma o produce potenza
    */
    if(to_print.get_power() < 0)
        os << "Power usage: " << to_print.get_power() << " kW" << std::endl;
    else
        os << "Power supplied: " << to_print.get_power() << " kW" << std::endl;

    return os;
}