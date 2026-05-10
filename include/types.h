#ifndef TYPES_H
#define TYPES_H

#include <systemc.h>
#include <string>

struct SpiroData {
    int patient_id = 0;
    double value = 0.0; //Częstotliwość impulsów lub litraż
    bool is_command = false; //Dane z sensora czy z klawiatury
    double temperature = 0.0; //Temperatura otoczenia

    SpiroData() {} //Zerowanie danych

    bool operator==(const SpiroData& rhs) const {
        return (patient_id == rhs.patient_id && value == rhs.value && is_command == rhs.is_command);
    }
};

inline std::ostream& operator<<(std::ostream& os, const SpiroData& sd) {
        os << "[ID: " << sd.patient_id
            << "| Wartosc: " << sd.value
            << "| Cmd: " << (sd.is_command ? "TAK" : "NIE")
            << "]";
        return os;
    }

#endif