#include <systemc.h>
#include "include/types.h"
#include "include/sensor_subsystem.h"
#include "include/data_processor.h"
#include "include/keyboard_interface.h"

int sc_main(int argc, char* argv[]) {
    srand(time(NULL)); //Generator losowego pomiaru [PLACEHOLDER]

    //Bufory
    sc_fifo<SpiroData> sensor_pipe(20);
    sc_fifo<SpiroData> keyboard_pipe(10);

    //Moduły
    SensorSubsystem hardware("hardware_subsystem");
    DataProcessor processor("data_processor_unit");
    KeyboardInterface keyboard("keyboard_unit");

    //Porty
    hardware.out_to_system(sensor_pipe);
    keyboard.out_port(keyboard_pipe);

    //2 porty wejściowe procesora
    processor.in_sensor(sensor_pipe);
    processor.in_keyboard(keyboard_pipe);

    sc_start();

    return 0;
}