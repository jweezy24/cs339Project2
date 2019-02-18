#include "hardware.c"
#include "DM.c"
#include <stdio.h>
#include <string.h>
#include "network.c"

void objupdate(hardware* thingtobeupdated, char* ip);

hardware* findByName(DM* tempDM, char* name);
