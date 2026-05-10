SYSTEMC_INC = /opt/systemc/include
SYSTEMC_LIB = /opt/systemc/lib-linux64

CXX = g++
CXXFLAGS = -I. -I$(SYSTEMC_INC) -L$(SYSTEMC_LIB) -lsystemc

all:
	$(CXX) main.cpp $(CXXFLAGS) -o spirometer

clean:
	rm -f spirometer