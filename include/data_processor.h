#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <systemc.h>
#include "types.h"

SC_MODULE(DataProcessor) {
    sc_port<sc_fifo_in_if<SpiroData>> in_port;

    SC_CTOR(DataProcessor) {
        SC_THREAD(process_data);
    }

    void process_data() {
        SpiroData received_packet;

        while (true) {
            in_port->read(received_packet);

            cout << "Odebrane dane:" << endl;
            cout << "Czas symulacji: " << sc_time_stamp() << endl;
            cout << "Dane: " << received_packet << endl << endl;

            wait(50, SC_MS);
        }
    }
};

#endif