CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=
SOURCES=../../src
LLIB=../../lib
LDEFS=../../defs
DBG=-g

all:	lib
	 $(CC) $(CFLAGS) main.cpp -lm $(LLIB)/MPU6050.o -o main -lwiringPi
lib: $(LLIB)/MPU6050.o 

$(LLIB)/MPU6050.o: $(SOURCES)/MPU6050.cpp $(LDEFS)/MPU6050.h
	$(CC) -c $(SOURCES)/MPU6050.cpp -o $@ $(CFLAGS)

#$(LLIB)/Seis.o: $(SOURCES)/Seis.cpp $(LDEFS)/Seis.h
#	$(CC) -c $(SOURCES)/Seis.cpp -o $@ $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf MPU6050
#	rm -rf Seis
