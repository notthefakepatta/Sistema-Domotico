#include "ManualDevice.h"

int ManualDevice::manual_device_counter_ = 0;

// Construcotrs
ManualDevice::ManualDevice()
{
    name_= "";
    power_amount_ = 0;
    id_ = "";
    turn_off_time_ = Time();
    turn_on_time_ = Time();
    timer_ = Time();
}

ManualDevice::ManualDevice(std::string name_set, double power_set)
{
    name_ = name_set;
    power_amount_ = power_set;
    id_ = "MAN" + std::to_string(manual_device_counter_);
    manual_device_counter_++;
}

void ManualDevice::set_timer(Time& new_timer)
{
    timer_ = Time(new_timer.get_hours(), new_timer.get_minutes());
}

// Getter
std::string ManualDevice::get_id() const
{
    return id_;
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

int main()
{
    ManualDevice man_dev1("name1", 1.5);
    std::cout << man_dev1;
    
    ManualDevice man_dev2("name2", -3.2);
    std::cout << man_dev2;
    Time t(10,15);
    man_dev2.set_timer(t);
    //man_dev2.set_off_time(t);
    std::cout << man_dev2.get_timer();

    ManualDevice man_dev3;
    std::cout << man_dev3;

    return 0;
}