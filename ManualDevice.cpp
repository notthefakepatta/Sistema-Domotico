// Giovanni Cerin 2111532

#include "ManualDevice.h"

int ManualDevice::manual_device_counter_ = 0;
const std::string ManualDevice::kManIdentifier = "MAN";

// costruttore di default
ManualDevice::ManualDevice()
{
    name_= "";
    power_amount_ = 0;
    id_ = "";
}

// costruttore di copia
ManualDevice::ManualDevice(const ManualDevice& man_copy)
{
    name_ = man_copy.name_;
    power_amount_ = man_copy.power_amount_;
    id_ = man_copy.id_;
}

// costruttore ricevente due argomenti:
// (nome del dispositivo, produzione/consumo di potenza)
ManualDevice::ManualDevice(std::string name_set, double power_set)
{
    name_ = name_set;
    power_amount_ = power_set;
    id_ = kManIdentifier + std::to_string(manual_device_counter_);
    manual_device_counter_++;
}

// funzione di accesso al membro privato id_
std::string ManualDevice::get_id() const
{
    return id_;
}

// operatore di copia
ManualDevice& ManualDevice::operator=(const ManualDevice& man_copy)
{
    name_ = man_copy.name_;
    power_amount_ = man_copy.power_amount_;
    id_ = man_copy.id_;
    
    return *this;
}

// Operator overloading <<
// il formato del messaggio stampato sarà del tipo:
    // Device name: *nome del dispositivo*
    // Type: manual (MAN)
    // ID: *ID del dispositivo*
    // Power usage/supplied: *potenza consumata/prodotta dal dispositivo* kW
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