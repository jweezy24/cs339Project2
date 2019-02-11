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
  printf("%s\n", cleanOP);
  printf("%s\n", args);
  if(strcmp(cleanOP, "add") == 0){
    set_object_dim(&thing, dim);
    set_object_type(&thing, typeBuffer);
    set_object_name(&thing, nameBuffer);
    set_object_color(&thing, colorBuffer);
    set_object_state(&thing, stateBuffer);
    printf("%s\n", cleanIP);
    if(check_if_DM(&AllDMs, cleanIP) == 0){
      DM* placeHolder = add_to_DM(get_DM_IP(&AllDMs, cleanIP), &thing, cleanIP);
      printf("%s\n", placeHolder->ip);
      update_DM_on_net(placeHolder, cleanIP, &AllDMs);
    }else{
      DM newDM;
      init_DM(&newDM);
      newDM.size = 0;
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

  free(cleanIP);
  free(cleanOP);


}
