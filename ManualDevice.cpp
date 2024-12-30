#include "ManualDevice.h"

int ManualDevice::manual_device_counter_ = 0;
const std::string ManualDevice::kManIdentifier = "MAN";

// Construcotrs
ManualDevice::ManualDevice()
{
    name_= "";
    power_amount_ = 0;
    id_ = "";
}

// Copy constructor
ManualDevice::ManualDevice(const ManualDevice& man_copy)
{
    name_ = man_copy.name_;
    power_amount_ = man_copy.power_amount_;
    id_ = man_copy.id_;
}

ManualDevice::ManualDevice(std::string name_set, double power_set)
{
    name_ = name_set;
    power_amount_ = power_set;
    id_ = kManIdentifier + std::to_string(manual_device_counter_);
    manual_device_counter_++;
}

// Getter
std::string ManualDevice::get_id() const
{
    return id_;
}

// copy assignment
ManualDevice& ManualDevice::operator=(const ManualDevice& man_copy)
{
    name_ = man_copy.name_;
    power_amount_ = man_copy.power_amount_;
    id_ = man_copy.id_;
    
    return *this;
}

// Operator overloading <<
std::ostream& operator<<(std::ostream& os, ManualDevice& to_print)
{
    os << "Device name: " << to_print.get_name() << std::endl;
    os << "Type: manual (MAN)" << std::endl;
    os << "ID: " << to_print.get_id() << std::endl;
    
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