// Alessandro Pattaro 2101822

#ifndef CONSUMPTIONCARD_H
#define CONSUMPTIONCARD_H

#include <iostream>

struct ConsumptionCard
{
    /*  dispositivo */
    DomoticDevice device_;

    /*  energia consumata/prodotta */
    double consumption_;

    //  costruttore
    ConsumptionCard(const DomoticDevice& d)
        : device_(d) {}

};

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const ConsumptionCard& c)
{
    os << c.consumption_ << " kWh";
    return os;
}


#endif //CONSUMPTIONCARD_H
