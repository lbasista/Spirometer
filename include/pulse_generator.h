#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include <systemc.h>
#include "types.h"
#include <cstdlib>
#include <thread>
#include <chrono>

SC_MODULE(PulseGenerator) {
    sc_port<sc_fifo_out_if<SpiroData>> out_port;

    SC_CTOR(PulseGenerator) {
        SC_THREAD(generate_pulses);
    }

    void generate_pulses() {
        SpiroData data;
        data.is_command = false;

        while (true) {
            //Symulowanie oddechu (placeholder: losowy mocny wydech do 250L/min)
            double fake_flow = static_cast<double>(rand() % 25000) / 100.0;
            
            data.value = fake_flow;
            out_port->write(data);

            wait(250, SC_MS); //Przesunięcie zegara SystemC
            std::this_thread::sleep_for(std::chrono::milliseconds(250)); //Symulacja czasu rzeczywistego
        }
    }
};

#endif