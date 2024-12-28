#ifndef DOMOTIC_DEVICE_H
#define DOMOTIC_DEVICE_H
#include <string>
#include <iostream>
#include "Time.h"

class DomoticDevice
{
protected:
    // data members
    std::string name_;
    double power_amount_;
    Time turn_off_time_;
    Time turn_on_time_;
    Time timer_;

public:
    DomoticDevice() {};
    
    // disabled copy construtor
    DomoticDevice(const DomoticDevice&) = delete;

    // disabled copy assignment
    DomoticDevice& operator=(const DomoticDevice&) = delete;

    // getters
    std::string get_name() const;
    double get_power() const;
    Time get_off_time() const;
    Time get_on_time() const;
    Time get_timer() const;
    virtual std::string get_id() const = 0;
    
    void set_off_time(Time&);
    void set_on_time(Time&);
    virtual void set_name(std::string);
};

#endif // DOMOTIC_DEVICE_H