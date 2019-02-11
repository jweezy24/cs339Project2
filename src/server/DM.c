#include <stdio.h>
#include <stdlib.h>


typedef struct DM{
  hardware* objects;
  char* ip;
  char* subnet_mask;
  int size;
}DM;

void init_DM(DM* tempDM){
  tempDM = malloc(sizeof(DM));
  tempDM->objects = malloc(sizeof(hardware));
  tempDM->size = 0;
}

void create_DM(DM* dungeonMaster, char* ip, char* subnet){
  char* tempIp = create_string_attr(dungeonMaster->ip, ip);
  dungeonMaster->ip = malloc(sizeof(char)*strlen(tempIp));
  strcpy(dungeonMaster->ip, tempIp);
  free(tempIp);
  char* tempSub = create_string_attr(dungeonMaster->subnet_mask, subnet);
  dungeonMaster->subnet_mask = malloc(sizeof(char)*strlen(tempSub));
  strcpy(dungeonMaster->subnet_mask, tempSub);
  free(tempSub);
  dungeonMaster->objects = malloc(sizeof(hardware));
}

DM* create_nullDM(){
  DM* nullDM = malloc(sizeof(DM));
  nullDM->ip = malloc(sizeof(char)*5);
  strcpy(nullDM->ip, "none");
  return nullDM;
}

int name_check(DM* tempDM, char* name){
  for(int i = 0; i < tempDM->size; i++){
    if(strcmp(tempDM->objects[i].name, name) == 0){
      return 0;
    }
  }
  return 1;
}

DM* add_to_DM(DM* requested_DM, hardware* newWare, char* ip){
  if(strcmp(requested_DM->ip, "none") == 0){
    return create_nullDM();
  }else{
    requested_DM->objects = realloc(requested_DM->objects, sizeof(hardware)*(requested_DM->size+1));
    requested_DM->objects[requested_DM->size] = *newWare;
    requested_DM->size+=1;
    return requested_DM;
  }
}



void freeDM(DM* dm){
  for (int i =0; i < dm->size; i++){
    free_hardware(&dm->objects[i]);
  }
  free(dm->ip);
  free(dm->subnet_mask);
}
