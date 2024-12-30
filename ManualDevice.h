#ifndef MANUAL_DEVICE_H
#define MANUAL_DEVICE_H
#include "DomoticDevice.h"

class ManualDevice : public DomoticDevice
{
private:
    static int manual_device_counter_;
    std::string id_;

public:
    static const std::string kManIdentifier;
    
    ManualDevice();
    ManualDevice(const ManualDevice&);
    ManualDevice(std::string, double);

    std::string get_id() const;

    // copy assignment
    ManualDevice& operator=(const ManualDevice&);
};

std::ostream& operator<<(std::ostream&, ManualDevice&);

#endif // MANUAL_DEVICE_H