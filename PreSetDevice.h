#ifndef PRESET_DEVICE_H
#define PRESET_DEVICE_H
#include "DomoticDevice.h"
#include "Time.h"

class PreSetDevice : public DomoticDevice
{
private:
    // variabile statica che indica il numero di dispositivi a ciclo prefissato presenti nel sistema
    static int preset_device_counter_;
    
    // ID univoco per ogni dispositivo
    // composto da un identificatore di tipo (PRE per i dispositivi a ciclo prefissato)
    // e da un intero che aumenta all'aumentare del numero di dispositivi presenti nel sistema
    std::string id_;
    
    // durata di accensione del dispositivo a ciclo prefissato
    Time timer_;

public:
    // tripletta di caratteri (PRE) che identifica i dispositivi a ciclo prefissato
    static const std::string kPreIdentifier;

    // COSTRUTTORI
    // costruttore di default
    PreSetDevice();

    // costruttore di copia
    PreSetDevice(const PreSetDevice&);
    
    // costruttore ricevente tre argomenti:
    // (nome del dispositivo, produzione/consumo di potenza, durata del ciclo)
    PreSetDevice(std::string, double, Time&);

    // funzione di accesso ai membri privati
    Time get_timer();
    std::string get_id() const;

    // operatore di copia
    PreSetDevice& operator=(const PreSetDevice&);
};

// overloading operatore <<
std::ostream& operator<<(std::ostream&, PreSetDevice&);

#endif // PRESET_DEVICE_H