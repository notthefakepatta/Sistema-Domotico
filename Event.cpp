//  Alessandro Pattaro 2101822

#include "Event.h"


/*  overloading operator< */
bool operator<(const Event& e1, const Event& e2)
{
    /*  un evento è stabilito "minore" di un altro se avviene
     *  prima di un altro */
    if (e1.start_or_end_time_ < e2.start_or_end_time_)
        return true;

    return false;
}

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Event& e)
{
    if (e.status_ == Event::ON)
        os<< "acceso";
    else
        os<< "spento";

    return os;
}
