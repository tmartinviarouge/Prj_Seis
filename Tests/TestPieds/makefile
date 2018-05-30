CC=g++
CFLAGS=-std=c++11
LDFLAGS=
SOURCES=../../src
LLIB=../../lib
LDEFS=../../defs
DBG=-g

all:	lib
	 $(CC) $(CFLAGS) testPied.cpp -lm $(LLIB)/ADS1115.o $(LLIB)/Pied.o -o testPied -lwiringPi -lpthread

lib: $(LLIB)/ADS1115.o  $(LLIB)/Pied.o

$(LLIB)/ADS1115.o: $(SOURCES)/ADS1115.cpp       $(LDEFS)/ADS1115.h  
	$(CC) -c $(SOURCES)/ADS1115.cpp -o $@ $(CFLAGS)

$(LLIB)/Pied.o:  $(SOURCES)/Pied.cpp $(LDEFS)/Pied.h $(LDEFS)/GPIOSEIS.h
	$(CC) -c $(SOURCES)/Pied.cpp -o $@ $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ADS1115
