#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include <systemc.h>
#include "types.h"
#include <cstdlib>

SC_MODULE(PulseGenerator) {
    sc_port<sc_fifo_out_if<SpiroData>> out_port;

    SC_CTOR(PulseGenerator) {
        SC_THREAD(generate_pulses);
    }

    void generate_pulses() {
        SpiroData data;
        data.is_command = false;

        while (true) {
            //Symulowanie oddechu (placeholder: losowy przepływ 0-6L/min)
            double fake_flow = static_cast<double>(rand() % 600) / 100.0;
            
            data.value = fake_flow;
            out_port->write(data);

            wait(1, SC_SEC); //Odczyt co 1sek
        }
    }
};

#endif