// Alessandro Pattaro 2101822

#ifndef CONSUMPTIONCARD_H
#define CONSUMPTIONCARD_H

#include <iostream>
#include "DomoticDevice.h"
#include "Time.h"

struct ConsumptionCard
{
//  ISTANZE DELLA STRUCT
    /*  dispositivo */
    const DomoticDevice& device_;

    /*  energia consumata/prodotta */
    double consumption_;

    /*  stato del dispositivo */
    bool status_;

    /*  orario corrispondente all'ultima accensione di consumo */
    Time last_check_;

// COSTRUTTORE
    ConsumptionCard(const DomoticDevice& d)
                    : device_(d), consumption_(kDefaultConsumption), status_(kOff) {}

//  VARIABILI STATICHE DI CLASSE
    static const bool kOn = true;
    static const bool kOff = false;
    static constexpr double kDefaultConsumption = 0.0;
};

//  OVERLOADING OPERATORI UTILI
/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const ConsumptionCard& c);

/*  overloading dell'operator== */
bool operator==(const ConsumptionCard& c, const DomoticDevice& d);

/*  conversione in stringa di operator<< */
std::string to_string(const ConsumptionCard& c);

#endif //CONSUMPTIONCARD_H
