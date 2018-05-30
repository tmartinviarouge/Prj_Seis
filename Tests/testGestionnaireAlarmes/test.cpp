#include <cstdlib>
#include "../../defs/gestionnaireAlarme.h"
#include "../../defs/GPIOSEIS.h"

int main() {

gestionnaireAlarme gestion;
int distance = 20;
gestion.signalerApproche(distance);


}
