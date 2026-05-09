SYSTEMC_INC = /usr/local/include
SYSTEMC_LIB = /usr/local/lib

all:
	g++ hello_systemc.cpp -I$(SYSTEMC_INC) -L$(SYSTEMC_LIB) -lsystemc -o hello

clean:
	rm -f hello