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
  char* subnet_mask;
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
void set_object_dim(hardware* object, int dim){
  object->dim = dim;
}

//Pretty much a copy str method except it filters out unwanted characters from the json parse
char* create_string_attr(char* attr, char* type){
  attr = malloc(sizeof(char)*strlen(type)+1);
  int count = 0;
  int attrCount = 0;
  while(type[count] != '\0'){
    if (type[count] == '\'' || type[count] == ',' || type[count] == '}' || type[count] == '{'){
      count+=1;
    }else{
      attr[attrCount] = type[count];
      type+=1;
      attrCount+=1;
    }
  }
  return attr;
}

void set_object_type(hardware* object, char* type){
  char* temp = create_string_attr(object->type, type);
  object->type = malloc(sizeof(char)*strlen(temp));
  strcpy(object->type, temp);
  free(temp);
}

void set_object_state(hardware* object, char* type){
  char* temp = create_string_attr(object->state, type);
  object->state = malloc(sizeof(char)*strlen(temp));
  strcpy(object->state, temp);
  free(temp);
}

void set_object_name(hardware* object, char* type){
  char* temp = create_string_attr(object->name, type);
  object->name = malloc(sizeof(char)*strlen(temp));
  strcpy(object->name, temp);
  free(temp);
}

void set_object_color(hardware* object, char* type){
  char* temp = create_string_attr(object->color, type);
  object->color = malloc(sizeof(char)*strlen(temp));
  strcpy(object->color, temp);
  free(temp);
}



void create_DM(){

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
