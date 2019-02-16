#include <stdio.h>
#include <stdlib.h>

typedef struct hardware{
  char* type;
  char* name;
  int dim;
  char* color;
  char* state;
}hardware;

void init_hardware(hardware* object){
  object = malloc(sizeof(hardware));
}


//updates dim
void set_object_dim(hardware* object, int dim){
  object->dim = dim;
}

void set_object_type(hardware* object, char* type){
  object->type = malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->type, type);
}

void set_object_state(hardware* object, char* type){
  object->state = malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->state, type);
}

void set_object_name(hardware* object, char* type){
  object->name = malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->name, type);
}

void set_object_color(hardware* object, char* type){
  object->color = malloc(sizeof(char)*strlen(type)+1);
  strcpy(object->color, type);
}

void hardware_copy_new(hardware* dest, hardware* new){
  dest->type = malloc(sizeof(char)*strlen(new->type)+1);
  strcpy(dest->type,new->type);
  dest->name = malloc(sizeof(char)*strlen(new->name)+1);
  strcpy(dest->name, new->name);
  dest->dim = new->dim;
  dest->color = malloc(sizeof(char)*strlen(new->color)+1);
  strcpy(dest->color, new->color);
  dest->state = malloc(sizeof(char)*strlen(new->state)+1);
  strcpy(dest->state, new->state);
}

void hardware_cmp(hardware* old, hardware* new){
  
}

void free_hardware(hardware* obj){
  free(obj->type);
  free(obj->name);
  free(obj->color);
  free(obj->state);
  free(obj);
}
