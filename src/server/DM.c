#include <stdio.h>
#include <stdlib.h>


typedef struct DM{
  hardware* objects;
  char* ip;
  char* subnet_mask;
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
  }
