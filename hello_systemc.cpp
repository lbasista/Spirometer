#include <systemc.h>

SC_MODULE(HELLO) {
    SC_CTOR(HELLO) {
        SC_THREAD(main_thread);
    }
    void main_thread() {
        cout << "SystemC dziala na RPi 5! Czekam na sensor..." << endl;
    }
};

int sc_main(int argc, char* argv[]) {
    HELLO hello("hello");
    sc_start();
    return 0;
}