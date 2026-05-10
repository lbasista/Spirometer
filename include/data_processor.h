#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <systemc.h>
#include "types.h"
#include <unistd.h>

SC_MODULE(DataProcessor) {
    sc_port<sc_fifo_in_if<SpiroData>> in_sensor;
    sc_port<sc_fifo_in_if<SpiroData>> in_keyboard;

    int current_patient_id = 0;
    sc_time session_start_time = SC_ZERO_TIME;

    double suma_przeplywu = 0.0;
    double suma_objetosci = 0.0;
    int liczba_pomiarow = 0;
    double current_temp = 20.0; //Domyślna temperatura pokojowa

    bool is_measuring = false;

    double apply_btps_correction(double raw_value) {
        //BTPS: Body Temperature Pressure Saturated
        //Korekta na temperaturę z pominieciem cisnienia: (273 + 37) / (273 + T_ambient)
        double factor = 310.0 / (273.0 + current_temp);
        return raw_value * factor;
    }

    SC_CTOR(DataProcessor) {
        SC_THREAD(process_sensor_data);
        SC_THREAD(process_keyboard_cmd);
    }

    void process_keyboard_cmd() {
        SpiroData cmd;
        while(true) {
            in_keyboard->read(cmd);
            if (cmd.value == -1.0) {
                is_measuring = !is_measuring; //Przełącznik Start/Stop

                if (is_measuring) {
                    session_start_time = sc_time_stamp();
                    suma_objetosci = 0.0;
                    suma_przeplywu = 0.0;
                    liczba_pomiarow = 0;
                    cout << "\nPomiar rozpoczęty" << endl;
                } else {
                    cout << "\n\n===== Podsumowanie pomiaru =====" << endl;
                    cout << "Pomiar zakonczony w czasie " << (sc_time_stamp() - session_start_time).to_seconds() << "s" << endl;
                    cout << "Pacjent: " << current_patient_id << endl;
                    cout << "Temperatura: " << current_temp << "C" << endl;
                    if (liczba_pomiarow > 0) cout << "Sredni przeplyw: " << (suma_przeplywu / liczba_pomiarow) << "L/min" << endl;
                    else cout << "Sredni przeplyw: 0.0L/min - Brak danych pomiarowych" << endl;
                    
                    cout << "Calkowita objetosc: " << suma_objetosci << "L" << endl;
                    cout << "================================" << endl << endl;
                }
            } else if (cmd.temperature > 0) {
                current_temp = cmd.temperature;
            } else {
                current_patient_id = cmd.patient_id;
            }
        }
    }

    void process_sensor_data() {
        SpiroData data;
        while (true) {
            in_sensor->read(data);

            if (is_measuring) {            
                double corrected_flow = apply_btps_correction(data.value);
                double delta_t = 0.25; //Czas między pomiarami (250ms)

                //(L/min/60) * sekundy = Litry
                suma_objetosci += (corrected_flow / 60.0) * delta_t;
                suma_przeplywu += data.value;
                liczba_pomiarow++;

                double secs = (sc_time_stamp() - session_start_time).to_seconds();
                cout << "\rCzas pomiaru: " << secs << "s | Przeplyw: " << data.value << "L/min    " << flush;
            }
        }
    }
};

#endif