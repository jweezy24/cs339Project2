#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fnmatch.h>
#include "utils.c"
#include "hardware.c"
#include "DM.c"
#include "network.c"
#include <json.h>


//every machine tied to the server
network AllDMs;
void init_all(){
  init_network(&AllDMs);
}

char* get_json_attr_object_server(char* attr, struct json_object *json){
  struct json_object  *tmp;
  struct json_object *tmp2;
  json_object_object_get_ex(json, "object", &tmp);
  tmp2 = json_tokener_parse(json_object_to_json_string_ext(json, "object", &tmp));
  char* attr_got = malloc(sizeof(char)*strlen(json_object_to_json_string_ext(tmp2, JSON_C_TO_STRING_PLAIN)));
  char* temp_attr =  json_object_to_json_string_ext(tmp2, JSON_C_TO_STRING_PLAIN);
  char* place_holder = create_string_attr(attr_got,temp_attr);
  strcpy(attr_got, place_holder);
  return attr_got;
}

char* get_json_attr_server(char* attr, struct json_object *json){
  struct json_object  *tmp;
  json_object_object_get_ex(json, attr, &tmp);
  char* attr_got = malloc(sizeof(char)*strlen(json_object_to_json_string_ext(tmp, JSON_C_TO_STRING_PLAIN)));
  char* temp_attr =  json_object_to_json_string_ext(tmp, JSON_C_TO_STRING_PLAIN);
  char* place_holder = create_string_attr(attr_got,temp_attr);
  strcpy(attr_got, place_holder);
  return attr_got;
}
//parsing json to readable objects for the server boys
void parseJson(char* args){
  struct json_object *jobj;
  hardware thing;
  init_hardware(&thing);
  struct {
		int flag;
		const char *flag_str;
	} json_flags[] = {
		{ JSON_C_TO_STRING_PLAIN, "JSON_C_TO_STRING_PLAIN" },
		{ JSON_C_TO_STRING_SPACED, "JSON_C_TO_STRING_SPACED" },
		{ JSON_C_TO_STRING_PRETTY, "JSON_C_TO_STRING_PRETTY" },
		{ JSON_C_TO_STRING_NOZERO, "JSON_C_TO_STRING_NOZERO" },
		{ JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY, "JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY" },
		{ -1, NULL }
};
  jobj = json_tokener_parse(args);
  char *ip = get_json_attr_server("ip", jobj);
  char *subnet_mask = get_json_attr_server("sub", jobj);
  char *object_name = get_json_attr_object_server("name", jobj);
  printf("%s", object_name);
  for(int i = 0; i < AllDMs.size; i++){
    printf("DM %s exists on network.\n", AllDMs.things[i].ip);
    for(int j = 0; j < AllDMs.things[i].size; j++){
      printf("\t Hardware %s exists on DM.\n", AllDMs.things[i].objects[j].name);
    }
  }




}
