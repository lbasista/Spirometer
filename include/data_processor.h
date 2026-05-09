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

    SC_CTOR(DataProcessor) {
        SC_THREAD(process_sensor_data);
        SC_THREAD(process_keyboard_cmd);
    }

    void process_keyboard_cmd() {
        SpiroData cmd;
        while(true) {
            in_keyboard->read(cmd);
            current_patient_id = cmd.patient_id;
            session_start_time = sc_time_stamp();
            cout<< "\nSesja pacjenta " << current_patient_id << " rozpoczeta" << endl;
        }
    }

    void process_sensor_data() {
        SpiroData data;
        while (true) {
            in_sensor->read(data);
            sc_time session_time = sc_time_stamp() - session_start_time;
            cout << "[ODCZYT] Czas: " << session_time << endl;
            cout << "Pacjent: " << current_patient_id << endl;
            cout << "Przeplyw: " << data.value << "L/min" << endl << endl;

            //Wyświetlanie pomiarów co sekunde
            usleep(1000000);

            wait (1, SC_MS);
        }
    }
};

#endif