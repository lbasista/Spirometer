#ifndef SENSOR_SUBSYSTEM_H
#define SENSOR_SUBSYSTEM_H

#include <systemc.h>
#include "pulse_generator.h"
#include "types.h"

SC_MODULE(SensorSubsystem) {
    sc_port<sc_fifo_out_if<SpiroData>> out_to_system;
    PulseGenerator *pulser;

    SC_CTOR(SensorSubsystem) {
        pulser = new PulseGenerator("internal_pulser");
        pulser->out_port(out_to_system);
    }

    ~SensorSubsystem() { delete pulser; }
};

#endif