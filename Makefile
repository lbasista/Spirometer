# Ścieżki do SystemC (zgodnie z Twoją konfiguracją na RPi 5)
SYSTEMC_INC = /opt/systemc/include
SYSTEMC_LIB = /opt/systemc/lib-linux64

# Kompilator i flagi
CXX = g++
CXXFLAGS = -I. -I$(SYSTEMC_INC) -L$(SYSTEMC_LIB) -lsystemc

# Cel główny
all:
	$(CXX) main.cpp $(CXXFLAGS) -o spirometer

# Czyszczenie śmieci
clean:
	rm -f spirometer