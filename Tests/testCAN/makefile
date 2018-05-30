CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=
SOURCES=../../src
LLIB=../../lib
LDEFS=../../defs
DBG=-g

all:	lib
	 $(CC) $(CFLAGS) testADS1115.cpp -lm $(LLIB)/ADS1115.o -o testADS1115 -lwiringPi 
	 $(CC) $(CFLAGS) testHomogeneSurEntrees.cpp -lm $(LLIB)/ADS1115.o -o testHomogeneSurEntrees -lwiringPi

lib: $(LLIB)/ADS1115.o

$(LLIB)/ADS1115.o: $(SOURCES)/ADS1115.cpp $(LDEFS)/ADS1115.h
	$(CC) -c $(SOURCES)/ADS1115.cpp -o $@ $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf ADS1115





