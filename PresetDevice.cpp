// Giovanni Cerin 2111532

#include "PresetDevice.h"

int PresetDevice::preset_device_counter_ = 0;
const std::string PresetDevice::kPreIdentifier = "PRE";

// costruttore di default
PresetDevice::PresetDevice()
{
    name_= "";
    power_amount_ = 0;
    id_ = "";
    timer_ = Time();
}

// costruttore di copia
PresetDevice::PresetDevice(const PresetDevice& pre_copy)
{
    name_ = pre_copy.name_;
    power_amount_ = pre_copy.power_amount_;
    id_ = pre_copy.id_;
    timer_ = Time(pre_copy.timer_.get_hours(), pre_copy.timer_.get_minutes());
}

// costruttore ricevente tre argomenti:
// (nome del dispositivo, produzione/consumo di potenza, durata del ciclo)
PresetDevice::PresetDevice(std::string name_set, double power_set, Time& working_time)
{
    name_ = name_set;
    power_amount_ = power_set;
    id_ = kPreIdentifier + std::to_string(preset_device_counter_);
    preset_device_counter_++;
    timer_ = Time(working_time.get_hours(), working_time.get_minutes());
}

// operatore di copia
PresetDevice& PresetDevice::operator=(const PresetDevice& pre_copy)
{
    name_ = pre_copy.name_;
    power_amount_ = pre_copy.power_amount_;
    id_ = pre_copy.id_;
    timer_ = Time(pre_copy.timer_.get_hours(), pre_copy.timer_.get_minutes());
    
    return *this;
}

// funzioni di accesso ai membri privati
std::string PresetDevice::get_id() const
{
    return id_;
}

Time PresetDevice::get_timer()
{
    return timer_;
}

// Operator overloading <<
// il formato del messaggio stampato sarà del tipo:
    // Device name: *nome del dispositivo*
    // Type: preset cycle (PRE)
    // ID: *ID del dispositivo*
    // Working time: *durata del ciclo prefissato del dispositivo*
    // Power usage/supplied: *potenza consumata/prodotta dal dispositivo* kW
std::ostream& operator<<(std::ostream& os, PresetDevice& to_print)
{
    os << "Device name: " << to_print.get_name() << std::endl;
    os << "Type: preset cycle (PRE)" << std::endl;
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