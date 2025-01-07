// Alessandro Pattaro 2101822

#include "ConsumptionCard.h"

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const ConsumptionCard& c)
{
    /*  formato come da specifica */
    os << "Il dispositivo " << c.device_.get_name() << " ha attualmente ";
    if (c.device_.get_power() > 0)
    {    os << "prodotto";}

    /*  dispositivo a ciclo prefissato */
    else
    {   os << "consumato ";}

    os << c.consumption_ << " kWh";
    return os;
}

/*  conversione in stringa di operator<< */
std::string to_string(const ConsumptionCard& c)
{
    /*  formato come da specifica  */
    std::string msg("Il dispositivo " + c.device_.get_name() + " ha attualmente ");
    if (c.device_.get_power() > 0)
    {    msg += "prodotto";}

    /*  dispositivo a ciclo prefissato */
    else
    {   msg += "consumato ";}

    msg = msg + std::to_string(c.consumption_) + " kWh";
    return msg;
}

bool operator==(const ConsumptionCard& c, const DomoticDevice& d)
{
    return c.device_.get_id() == d.get_id();
}