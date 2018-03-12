CC=g++
CFLAGS=-Wall 
LDFLAGS=
SOURCES=./src
LLIB=./lib
LDEFS=./defs
DBG=-g

all:	lib
	
lib: $(LLIB)/ADS1115.o $(LLIB)/Pied.o

$(LLIB)/ADS1115.o: $(SOURCES)/ADS1115.cpp $(LDEFS)/ADS1115.h
	$(CC) -c $(SOURCES)/ADS1115.cpp -o $@ $(CFLAGS)

$(LLIB)/Pied.o:  $(SOURCES)/Pied.cpp $(LDEFS)/Pied.h $(LDEFS)/GPIOSEIS.h
	$(CC) -c $(SOURCES)/Pied.cpp -o $@ $(CFLAGS)

$(LLIB)/gestionnaireAlarme.o:  $(SOURCES)/gestionnaireAlarme.cpp $(LDEFS)/gestionnaireAlarme.h $(LDEFS)/buzzer.h
        $(CC) -c $(SOURCES)/gestionnaireAlarme.cpp -o $@ $(CFLAGS)

Clean:
	rm -rf *.o

mrproper: clean
	rm -rf ADS1115
