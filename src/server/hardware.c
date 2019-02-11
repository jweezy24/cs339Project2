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

void hardware_copy_new(hardware* dest, hardware* new){
  dest->type = malloc(sizeof(char)*strlen(new->type));
  strcpy(dest->type,new->type);
  dest->name = malloc(sizeof(char)*strlen(new->name));
  strcpy(dest->name, new->name);
  dest->dim = new->dim;
  dest->color = malloc(sizeof(char)*strlen(new->color));
  strcpy(dest->color, new->color);
  dest->state = malloc(sizeof(char)*strlen(new->state));
  strcpy(dest->state, new->state);
}

void free_hardware(hardware* obj){
  free(obj->type);
  free(obj->name);
  free(obj->color);
  free(obj->state);
  free(obj);
}
