#ifndef KEYBOARD_INTERFACE_H
#define KEYBOARD_INTERFACE_H

#include <systemc.h>
#include "types.h"
#include <iostream>
#include <thread>

SC_MODULE(KeyboardInterface) {
    sc_port<sc_fifo_out_if<SpiroData>> out_port;

    SC_CTOR(KeyboardInterface) {
        std::thread([this]() {
            bool is_measuring_kb = false; //Flaga do ukrywania menu

            while (true) {
                char action;

                if (!is_measuring_kb) {
                    cout << "[I] - Wprowadz ID pacjenta" << endl;
                    cout << "[T] - Ustaw temperature otoczenia" << endl;
                    cout << "[S] - START" << endl;
                    cout << "Wybierz opcje: " << flush;
                }
                
                if(!(std::cin >> action)) break;

                SpiroData cmd_packet;
                cmd_packet.is_command = true;

                if (action == 'i' || action == 'I') {
                    if (is_measuring_kb) continue;
                    cout << "Podaj ID: ";
                    cin >> cmd_packet.patient_id;
                    out_port->write(cmd_packet);
                } else if (action == 't' || action == 'T') {
                    if (is_measuring_kb) continue;
                    cout << "Podaj temperature otoczenia [C]: ";
                    cin >> cmd_packet.temperature;
                    out_port->write(cmd_packet);
                } else if (action == 's' || action == 'S') {
                    is_measuring_kb = !is_measuring_kb; //Przełącznik Start/Stop
                    cmd_packet.value = -1.0;
                    out_port->write(cmd_packet);

                    if (is_measuring_kb) {
                        cout << "\nPomiar rozpoczęty. Aby zatrzymać, wciśnij S i potwierdź ENTER." << endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    } else std::this_thread::sleep_for(std::chrono::milliseconds(300));
                } else {
                    if (!is_measuring_kb) cout << "Nieprawidlowa opcja";
                }
            }
        }).detach();
    }
};

#endif