// Giovanni Cerin 2111532

#ifndef MANUAL_DEVICE_H
#define MANUAL_DEVICE_H
#include "DomoticDevice.h"

class ManualDevice : public DomoticDevice
{
private:
    // variabile statica che indica il numero di dispositivi manuali presenti nel sistema
    static int manual_device_counter_;
    
    // ID univoco per ogni dispositivo
    // composto da un identificatore di tipo (MAN per i dispositivi manuali)
    // e da un intero che aumenta all'aumentare del numero di dispositivi presenti nel sistema
    std::string id_;

public:
    // tripletta di caratteri (MAN) che identifica i dispositivi manuali
    static const std::string kManIdentifier;
    
    // COSTRUTTORI
    // costruttore di default
    ManualDevice();

    // costruttore di copia
    ManualDevice(const ManualDevice&);

    // costruttore ricevente due argomenti:
    // (nome del dispositivo, produzione/consumo di potenza)
    ManualDevice(std::string, double);

    // funzione di accesso al membro privato id_
    std::string get_id() const;

    // operatore di copia
    ManualDevice& operator=(const ManualDevice&);
};

// overloading operatore <<
std::ostream& operator<<(std::ostream&, ManualDevice&);

#endif // MANUAL_DEVICE_H