// Giovanni Cerin 2111532

#ifndef DOMOTIC_DEVICE_H
#define DOMOTIC_DEVICE_H
#include <string>
#include <iostream>

class DomoticDevice
{
protected:
    // dati membro
    // nome del dispositivo
    std::string name_;
    
    // potenza consumata/prodotta
    double power_amount_;

public:
    // costruttore di default
    DomoticDevice() {};
    
    // costruttore di copia dosabilitato
    DomoticDevice(const DomoticDevice&) = delete;

    // operatore di copia disabilitato
    DomoticDevice& operator=(const DomoticDevice&) = delete;

    // funzioni di accesso ai membri privati
    std::string get_name() const;
    double get_power() const;
    virtual std::string get_id() const = 0;
    
    // overloading operatore ==
    bool operator==(const DomoticDevice&);
};

#endif // DOMOTIC_DEVICE_H