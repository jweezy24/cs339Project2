#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fnmatch.h>
#include "utils.c"
#include "hardware.c"
#include "DM.c"
#include "network.c"


//every machine tied to the server
network AllDMs;

//parsing json to readable code for the server boys
void parseJson(char* args){
  hardware thing;
  init_hardware(&thing);
  init_network(&AllDMs);
  set_network_null(&AllDMs);
  char typeBuffer[100];
  char nameBuffer[100];
  char stateBuffer[100];
  char colorBuffer[100];
  char opBuffer[100];
  char ipBuffer[100];
  char subnetBuffer[100];
  int dim;
  sscanf( args, "{'ip': %s 'object': {'color': %s 'dim': %d, 'state': %s 'type': %s 'name': %s 'sub': %s 'op': %s}",
         ipBuffer, colorBuffer, &dim, stateBuffer, typeBuffer, nameBuffer, subnetBuffer, opBuffer);
  set_object_dim(&thing, dim);
  set_object_type(&thing, typeBuffer);
  set_object_name(&thing, nameBuffer);
  set_object_color(&thing, colorBuffer);
  set_object_state(&thing, stateBuffer);
}
