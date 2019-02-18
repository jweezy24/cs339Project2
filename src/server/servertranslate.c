#include "serverTranslate.h"

extern void objupdate(hardware* thingtobeupdated, char * ip){
// I think what would happen here is the updated object being recieved would replace the current one in the tree

 hardware_copy_replace(findByName(findDMbyip(ip),thingtobeupdated->name),thingtobeupdated);
};

hardware* findByName(DM* tempDM, char* name){
  hardware* found = malloc(sizeof(hardware*));
  for(int i = 0; i < tempDM->size; i++){
    if(strcmp(tempDM->objects[i].name, name) == 0){
      found = &tempDM->objects[i];
      return found;
    }
  }
  return;
}