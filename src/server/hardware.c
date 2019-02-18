#include <stdio.h>
#include <stdlib.h>

typedef struct hardware{
  char* type;
  char* name;
  int dim;
  char* color;
  char* state;
}hardware;

hardware* init_hardware(hardware* object){
  object = (hardware*)malloc(sizeof(hardware));
  object->dim = 0;
  return object;
}


//updates dim
void set_object_dim(hardware* object, int dim){
  object->dim = dim;
}

void set_object_type(hardware* object, char* type){
  object->type = (char*)malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->type, type);
}

void set_object_state(hardware* object, char* type){
  object->state = (char*)malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->state, type);
}

void set_object_name(hardware* object, char* type){
  object->name = (char*)malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->name, type);
}

void set_object_color(hardware* object, char* type){
  object->color = (char*)malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->color, type);
}
// these methods will overwrite previous values instead of initializing them
void set_new_object_type(hardware* object, char* type){
  object->type = (char*)calloc(sizeof(char)*strlen(type)+1);
  strcpy(object->type, type);
}

void set_new_object_state(hardware* object, char* type){
  object->state = (char*)calloc(sizeof(char)*strlen(type)+1);
  strcpy(object->state, type);
}

void set_new_object_name(hardware* object, char* type){
  object->name = (char*)calloc(sizeof(char)*strlen(type)+1);
  strcpy(object->name, type);
}

void set_new_object_color(hardware* object, char* type){
  object->color = (char*)calloc(sizeof(char)*strlen(type)+1);
  strcpy(object->color, type);
}

void hardware_copy_new(hardware* dest, hardware* newHardware){
  dest->type = (char*)malloc(sizeof(char)*strlen(newHardware->type)+1);
  strcpy(dest->type,newHardware->type);
  dest->name = (char*)malloc(sizeof(char)*strlen(newHardware->name)+1);
  strcpy(dest->name, newHardware->name);
  dest->dim = newHardware->dim;
  dest->color = (char*)malloc(sizeof(char)*strlen(newHardware->color)+1);
  strcpy(dest->color, newHardware->color);
  dest->state = (char*)malloc(sizeof(char)*strlen(newHardware->state)+1);
  strcpy(dest->state, newHardware->state);
}

void hardware_copy_replace(hardware* dest, hardware* newHardware){
  dest->type = (char*)calloc(sizeof(char)*strlen(newHardware->type)+1);
  strcpy(dest->type,newHardware->type);
  dest->name = (char*)calloc(sizeof(char)*strlen(newHardware->name)+1);
  strcpy(dest->name, newHardware->name);
  dest->dim = newHardware->dim;
  dest->color = (char*)calloc(sizeof(char)*strlen(newHardware->color)+1);
  strcpy(dest->color, newHardware->color);
  dest->state = (char*)calloc(sizeof(char)*strlen(newHardware->state)+1);
  strcpy(dest->state, newHardware->state);
}

void free_hardware(hardware* obj){
  free(obj->type);
  free(obj->name);
  free(obj->color);
  free(obj->state);
  free(obj);
}
