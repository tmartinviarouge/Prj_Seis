/*#include "../../defs/Buzzer.h"

using namespace std; 

int main() {

Buzzer buzz;
while(1) {
buzz.arretBeep();

}

}
*/
#include "../../defs/Buzzer.h"
#include <iostream>
using namespace std; 

int main() {

Buzzer buzz;
buzz.beeper();
usleep(500000); 
buzz.arretBeep();
usleep(200000); 
buzz.beeper();
usleep(500000); 
buzz.arretBeep();
usleep(200000); 
buzz.arretBeep();

}

