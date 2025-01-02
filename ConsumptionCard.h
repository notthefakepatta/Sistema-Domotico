// Alessandro Pattaro 2101822

#ifndef CONSUMPTIONCARD_H
#define CONSUMPTIONCARD_H

#include <iostream>
#include "Time.h"
#include "Event.h"
#include "DomoticDevice.h"
#include "ManualDevice.h"
#include "PresetDevice.h"

struct ConsumptionCard
{
//  ISTANZE DELLA STRUCT
    /*  dispositivo */
    DomoticDevice& device_;

    /*  energia consumata/prodotta */
    double consumption_;

// COSTRUTTORE
    ConsumptionCard(DomoticDevice& d)
        : device_(d) {}

//  OVERLOADING OPERATORI UTILI
/*  overloading operator== */
    bool operator==(const ConsumptionCard& other)
    {
        if (device_ == other.device_) return true;
        return false;
    };

//  VARIABILI STATICHE DI CLASSE
    static const bool kOn = true;
    static const bool kOff = false;
};

//  OVERLOADING OPERATORI UTILI
/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const ConsumptionCard& c)
{
    os << c.consumption_ << " kWh";
    return os;
}

bool operator==(DomoticDevice& d_dev, const ConsumptionCard& c_card)
{
    return d_dev == c_card.device_;
}


#endif //CONSUMPTIONCARD_H
