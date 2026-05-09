#ifndef KEYBOARD_INTERFACE_H
#define KEYBOARD_INTERFACE_H

#include <systemc.h>
#include "types.h"
#include <iostream>

SC_MODULE(KeyboardInterface) {
    sc_port<sc_fifo_out_if<SpiroData>> out_port;

    SC_CTOR(KeyboardInterface) {
        SC_THREAD(keyboard_task);
    }

    void keyboard_task() {
        SpiroData cmd_packet;
        cmd_packet.is_command = true;

        while (true) {
            int new_id;
            std::cout << "\nWprowadz nowe ID pacjenta: " << std::flush;
            std::cin >> new_id;

            cmd_packet.patient_id = new_id;
            cmd_packet.value = 0.0;

            out_port->write(cmd_packet);

            std::cout << "Odbywa sie pomiar [10sek]" << std::endl;
            wait(10, SC_SEC);
        }
    }
};

#endif