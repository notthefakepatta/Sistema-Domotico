#ifndef MANUAL_DEVICE_H
#define MANUAL_DEVICE_H
#include "DomoticDevice.h"

class ManualDevice : public DomoticDevice
{
private:
    static int manual_device_counter_;
    std::string id_;

public:
    ManualDevice();
    ManualDevice(std::string, double);

    void set_timer(Time&);
    std::string get_id() const;
};

std::ostream& operator<<(std::ostream&, ManualDevice&);

#endif // MANUAL_DEVICE_H