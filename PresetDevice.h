// Giovanni Cerin 2111532

#ifndef PRESET_DEVICE_H
#define PRESET_DEVICE_H
#include "DomoticDevice.h"
#include "Time.h"

class PresetDevice : public DomoticDevice
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
    PresetDevice();

    // costruttore di copia
    PresetDevice(const PresetDevice&);
    
    // costruttore ricevente tre argomenti:
    // (nome del dispositivo, produzione/consumo di potenza, durata del ciclo)
    PresetDevice(std::string, double, Time&);

    // funzioni di accesso ai membri privati
    Time get_timer();
    std::string get_id() const;

    // operatore di copia
    PresetDevice& operator=(const PresetDevice&);
};

// overloading operatore <<
std::ostream& operator<<(std::ostream&, PresetDevice&);

#endif // PRESET_DEVICE_H