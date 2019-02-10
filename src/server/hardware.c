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

void free_hardware(hardware* obj){
  free(obj->type);
  free(obj->name);
  free(obj->color);
  free(obj->start);
  free(obj);
}
