#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include <systemc.h>
#include "types.h"

SC_MODULE(PulseGenerator) {
    sc_port<sc_fifo_out_if<SpiroData>> out_port;

    SC_CTOR(PulseGenerator) {
        SC_THREAD(generate_pulses);
    }

    void generate_pulses() {
        SpiroData data;
        data.patient_id = 0;
        data.is_command = false;
        double fake_flow = 0.0;

        while (true) {
            //Symulowanie oddechu
            fake_flow += 0.1;
            if (fake_flow > 5.0) fake_flow = 0;
            
            data.value = fake_flow;
            out_port->write(data);

            wait(100, SC_MS);
        }
    }
};

#endif