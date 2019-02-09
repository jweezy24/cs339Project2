#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fnmatch.h>

typedef struct hardware{
  char* type;
  char* name;
  int dim;
  char* color;
  char* state;
}hardware;

typedef struct DM{
  hardware* objects;
  char* user;
}DM;

typedef struct networkObjects{
  DM* things;
  int size;
}network;

//mallocs memory for a hardware object
void init_hardware(hardware* object){
  object = malloc(sizeof(hardware));
}
//updates dim
void update_object_dim(hardware* object, int dim){
  object->dim = dim;
}

void update_object_type(hardware* object, char* type){
  object->type = malloc(sizeof(char)*strlen(type));
  int count = 0;
  int typeCount = 0;
  while(type[count] != '\0'){
    if (type[count] == '\'' || type[count] == ',' || type[count] == '}' || type[count] == '{'){
      count+=1;
    }else{
      object->type[typeCount] = type[count];
      type+=1;
      typeCount+=1;
    }
  }
}
//parsing json to readable code for the server boys
void parseJson(char* args){
  hardware thing;
  init_hardware(&thing);
  char typeBuffer[100];
  char nameBuffer[100];
  char stateBuffer[100];
  char colorBuffer[100];
  char opBuffer[100];
  char ipBuffer[100];
  int dim;
  sscanf( args, "{'ip': %s 'object': {'color': %s 'dim': %d, 'state': %s 'type': %s 'name': %s 'op': %s}",
         ipBuffer, colorBuffer, &dim, stateBuffer, typeBuffer, nameBuffer, opBuffer);
  printf("%s\n", typeBuffer);
  update_object_dim(&thing, dim);
  update_object_type(&thing, typeBuffer);
  printf("%s\n", thing.type);
}
