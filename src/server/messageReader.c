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
  printf("%d\n", dim);
  update_object_dim(&thing, dim);
  printf("%d\n", thing.dim);
}
