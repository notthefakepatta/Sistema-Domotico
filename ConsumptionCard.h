// Alessandro Pattaro 2101822

#ifndef CONSUMPTIONCARD_H
#define CONSUMPTIONCARD_H

#include <iostream>

struct ConsumptionCard
{
//  ISTANZE DELLA STRUCT
    /*  dispositivo */
    DomoticDevice device_;

    /*  energia consumata/prodotta */
    double consumption_;

// COSTRUTTORE
    ConsumptionCard(const DomoticDevice& d)
        : device_(d) {}

//  VARIABILI STATICHE DI CLASSE
    static const bool kOn = true;
    static const bool kOff = false;
};

//  OVERLOADING OPERATORI UTILI
/*  overloading operator== */
bool operator==(const ConsumptionCard& other)
{
    if (device_==other.device_) return true;
    return false;
};

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const ConsumptionCard& c)
{
    os << c.consumption_ << " kWh";
    return os;
}


#endif //CONSUMPTIONCARD_H
