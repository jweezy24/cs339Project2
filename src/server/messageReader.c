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
void init_all(){
  init_network(&AllDMs);
}
//parsing json to readable objects for the server boys
void parseJson(char* args){
  hardware thing;
  init_hardware(&thing);
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
  char* cleanOP;
  char* cleanIP;
  cleanIP = create_string_attr(cleanOP, ipBuffer);
  cleanOP = create_string_attr(cleanOP, opBuffer);
  if(strcmp(cleanOP, "add") == 0){
    set_object_dim(&thing, dim);
    set_object_type(&thing, typeBuffer);
    set_object_name(&thing, nameBuffer);
    set_object_color(&thing, colorBuffer);
    set_object_state(&thing, stateBuffer);
    if(check_if_DM(&AllDMs, ipBuffer) == 0){
      add_to_DM(get_DM_IP(&AllDMs, ipBuffer), &thing, ipBuffer);
    }else{
      DM newDM;
      init_DM(&newDM);
      newDM.size = 1;
      create_DM(&newDM, cleanIP, subnetBuffer);
      add_to_DM(&newDM, &thing, cleanIP);
      add_DM_to_net(newDM, &AllDMs);
    }
  }

  for(int i = 0; i < AllDMs.size; i++){
    printf("DM %s exists on network.\n", AllDMs.things[i].ip);
    for(int j = 0; j < AllDMs.things[i].size; j++){
      printf("\t Hardware %s exists on DM.\n", AllDMs.things[i].objects[j].name);
    }
  }


}
