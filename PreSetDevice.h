#ifndef PRESET_DEVICE_H
#define PRESET_DEVICE_H
#include "DomoticDevice.h"
#include "Time.h"

class PreSetDevice : public DomoticDevice
{
private:
    static int preset_device_counter_;
    std::string id_;
    Time timer_;

public:
    static const std::string kPreIdentifier;

    PreSetDevice();
    PreSetDevice(std::string, double, Time&);

    Time get_timer();
    std::string get_id() const;
};

std::ostream& operator<<(std::ostream&, PreSetDevice&);

#endif // PRESET_DEVICE_H