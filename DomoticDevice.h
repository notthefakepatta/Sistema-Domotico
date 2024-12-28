#ifndef DOMOTIC_DEVICE_H
#define DOMOTIC_DEVICE_H
#include <string>
#include <iostream>

class DomoticDevice
{
protected:
    // data members
    std::string name_;
    double power_amount_;

public:
    DomoticDevice();
    
    // disabled copy construtor
    DomoticDevice(const DomoticDevice&) = delete;

    // disabled copy assignment
    DomoticDevice& operator=(const DomoticDevice&) = delete;

    // virtual getters
    std::string get_name() const;
    virtual std::string get_id() const = 0;
    double get_power() const;
    
    virtual void set_name(std::string);
};

#endif // DOMOTIC_DEVICE_H