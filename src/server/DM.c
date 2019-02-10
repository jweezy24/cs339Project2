#include <stdio.h>
#include <stdlib.h>


typedef struct DM{
  hardware* objects;
  char* ip;
  char* subnet_mask;
  int size;
}DM;

void create_DM(DM* dungeonMaster, char* ip, char* subnet){
  char* tempIp = create_string_attr(dungeonMaster->ip, ip);
  dungeonMaster->ip = malloc(sizeof(char)*strlen(tempIp));
  strcpy(dungeonMaster->ip, tempIp);
  free(tempIp);
  char* tempSub = create_string_attr(dungeonMaster->subnet_mask, subnet);
  dungeonMaster->subnet_mask = malloc(sizeof(char)*strlen(tempSub));
  strcpy(dungeonMaster->subnet_mask, tempSub);
  free(tempSub);
}

DM* create_nullDM(){
  DM* nullDM = malloc(sizeof(DM));
  nullDM->ip = malloc(sizeof(char)*5);
  strcpy(nullDM->ip, "none");
  return nullDM;
}


void freeDM(*DM dm){
  for (int i =0; i < dm->size; i++){
    free_hardware(dm->objects[i]);
  }
  free(dm->ip);
  free(dm->subnet_mask);
}
