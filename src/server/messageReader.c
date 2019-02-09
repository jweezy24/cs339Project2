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

void initHardware(hardware* object){
  object = malloc(sizeof(hardware));
  object->type = malloc(sizeof(char)+1);
  object->name = malloc(sizeof(char)+1);
  object->state = malloc(sizeof(char)+1);
  object->color = malloc(sizeof(char)+1);
}
//parsing json to readable code for the server boys
void parseJson(char* args){
  hardware* object;
  initHardware(object);
  char typeBuffer[100];
  char nameBuffer[100];
  char stateBuffer[100];
  char colorBuffer[100];
  char opBuffer[100];
  char ipBuffer[100];
  int dim;
  sscanf( args, "{'ip': %s 'object': {'color': %s 'dim': %d, 'state': %s 'type': %s 'name': %s 'op': %s}",
         ipBuffer, colorBuffer, &dim, stateBuffer, typeBuffer, nameBuffer, opBuffer);
  printf("%s\n", nameBuffer);
  printf("%s\n", colorBuffer);
  printf("%s\n", typeBuffer);
  printf("%s\n", stateBuffer);
  printf("%s\n", opBuffer);
  printf("%s\n", ipBuffer);
}
