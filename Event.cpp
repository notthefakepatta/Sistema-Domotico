//  Alessandro Pattaro 2101822

#include "Event.h"

/*  overloading operator< */
bool operator<(const Event& e1, const Event& e2)
{
    /*  un evento è stabilito "minore" di un altro se avviene
     *  prima di un altro */
    return e1.start_or_end_time_ < e2.start_or_end_time_;
}

/*  overloading dell'operator<< */
std::ostream& operator<<(std::ostream& os, const Event& e)
{
    os << "[" << e.start_or_end_time_ << "]" << " Il dispositivo \"" << e.device_card_.device_.get_name() << "\" si e' ";
    if (e.status_ == Event::kOn)
        os << "acceso" << std::endl;
    else
        os << "spento" << std::endl;
    return os;
}