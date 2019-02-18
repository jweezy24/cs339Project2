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

char* get_json_attr_object_server(char* attr, struct json_object *json){
  struct json_object  *tmp;
  struct json_object *tmp2;
  json_object_object_get_ex(json, (char*)"object", &tmp);
  tmp2 = json_tokener_parse(json_object_to_json_string_ext(tmp, JSON_C_TO_STRING_PRETTY));
  json_object_object_get_ex(tmp, attr, &tmp2);
  char* attr_got = (char*)malloc(sizeof(char)*strlen(json_object_to_json_string_ext(tmp2, JSON_C_TO_STRING_PRETTY)));
  char* temp_attr =  (char*)malloc(sizeof(char)*strlen(json_object_to_json_string_ext(tmp2, JSON_C_TO_STRING_PRETTY)));
  strcpy(temp_attr, json_object_to_json_string_ext(tmp2, JSON_C_TO_STRING_PRETTY));
  strcpy(attr_got, temp_attr);
  free(temp_attr);
  return attr_got;
}
<<<<<<< HEAD



char* get_json_attr_server(char* attr, struct json_object *json){
  struct json_object  *tmp;
  json_object_object_get_ex(json, attr, &tmp);
  char* attr_got = (char*) malloc(sizeof(char)*strlen(json_object_to_json_string_ext(tmp, JSON_C_TO_STRING_PRETTY))+1);
  char* temp_attr =  (char*)malloc(sizeof(char)*strlen(json_object_to_json_string_ext(tmp, JSON_C_TO_STRING_PRETTY))+1);
  strcpy(temp_attr, (char*)json_object_to_json_string_ext(tmp, JSON_C_TO_STRING_PRETTY));
  strcpy(attr_got, (char*)temp_attr);
  free(temp_attr);
  return attr_got;
}

void get_json_attr_routine_server(struct json_object *json){
  struct json_object *tmp2;
  hardware thing;
  char* ip = (char*)get_json_attr_server((char*)"ip", json);
  char* subnet = (char*)get_json_attr_server((char*)"sub", json);
  json_object_object_get_ex(json, (char*)"object", &tmp2);
  set_object_dim(&thing, atoi(get_json_attr_server((char*)"dim", tmp2)));
  set_object_color(&thing, (char*)get_json_attr_server((char*)"color",tmp2));
  set_object_name(&thing, (char*)get_json_attr_server((char*)"name",tmp2));
  set_object_state(&thing, (char*)get_json_attr_server ((char*)"state",tmp2));
  set_object_type(&thing, (char*)get_json_attr_server((char*)"type",tmp2));
  DM tmpDM1 = *get_DM_IP(&AllDMs, ip);
  printf("%s\n", tmpDM1.ip);
  if(strcmp(tmpDM1.ip, (char*)"none") == 0){
    DM tmpDM;
    init_DM(&tmpDM);
    tmpDM.size = 0;
    create_DM(&tmpDM, ip, subnet);
    add_DM_to_net(*add_to_DM(&tmpDM, &thing), &AllDMs);
  }else{
    if(name_check(&tmpDM1, thing.name) == 1){
      DM tmp = *get_DM_IP(&AllDMs,ip);
      add_to_DM(&tmp, &thing);
      update_DM_on_net(&tmp, ip, &AllDMs);
=======
//parsing json to readable objects for the server boys
void parseJson(void * genericparam){
  char* args = (char *)genericparam;
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
  char* cleanOP;
  char* cleanIP;
  cleanIP = create_string_attr(cleanOP, ipBuffer);
  cleanOP = create_string_attr(cleanOP, opBuffer);
  printf("%s\n", cleanOP);
  printf("%s\n", args);
  if(strcmp(cleanOP, "add") == 0){
    set_object_dim(&thing, dim);
    set_object_type(&thing, typeBuffer);
    set_object_name(&thing, nameBuffer);
    set_object_color(&thing, colorBuffer);
    set_object_state(&thing, stateBuffer);
    printf("%s\n", cleanIP);
    if(check_if_DM(&AllDMs, cleanIP) == 0){
      DM* placeHolder = add_to_DM(get_DM_IP(&AllDMs, cleanIP), &thing, cleanIP);
      printf("%s\n", placeHolder->ip);
      update_DM_on_net(placeHolder, cleanIP, &AllDMs);
    }else{
      DM newDM;
      init_DM(&newDM);
      newDM.size = 0;
      create_DM(&newDM, cleanIP, subnetBuffer);
      add_to_DM(&newDM, &thing, cleanIP);
      add_DM_to_net(newDM,&AllDMs);
>>>>>>> JackB
    }
  free(ip);
  free(subnet);
  }
}

void display_net(){
  for(int i = 0; i < AllDMs.size; i++){
    printf("DM %s exists on network.\n", AllDMs.things[i].ip);
    for(int j = 0; j < AllDMs.things[i].size; j++){
      printf("\t Hardware %s exists on DM.\n", AllDMs.things[i].objects[j].name);
    }
  }

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
		{ JSON_C_TO_STRING_PLAIN, (char*)"JSON_C_TO_STRING_PLAIN" },
		{ JSON_C_TO_STRING_SPACED, (char*)"JSON_C_TO_STRING_SPACED" },
		{ JSON_C_TO_STRING_PRETTY, (char*)"JSON_C_TO_STRING_PRETTY" },
		{ JSON_C_TO_STRING_NOZERO, (char*)"JSON_C_TO_STRING_NOZERO" },
		{ JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY, (char*)"JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY" },
		{ -1, NULL }
};
  jobj = json_tokener_parse(args);
  char *ip = (char*)get_json_attr_server((char*)"ip", jobj);
  char *subnet_mask = (char*)get_json_attr_server((char*)"sub", jobj);
  char* op = (char*)get_json_attr_server((char*)"op", jobj);
  if(strcmp(op,(char*)"\"add\"") == 0){
    set_object_dim(&thing, atoi(get_json_attr_object_server((char*)"dim", jobj)));
    set_object_color(&thing, (char*)get_json_attr_object_server((char*)"color",jobj));
    set_object_name(&thing, (char*)get_json_attr_object_server((char*)"name",jobj));
    set_object_state(&thing, (char*)get_json_attr_object_server ((char*)"state",jobj));
    set_object_type(&thing, (char*)get_json_attr_object_server((char*)"type",jobj));
    if(strcmp(get_DM_IP(&AllDMs, ip)->ip, (char*)"none") != 0){
      DM tmp = *get_DM_IP(&AllDMs,ip);
      add_to_DM(&tmp, &thing);
      update_DM_on_net(&tmp, ip, &AllDMs);
    }else{
      DM tmpDM;
      init_DM(&tmpDM);
      tmpDM.size = 0;
      tmpDM.status = 0;
      create_DM(&tmpDM, ip, subnet_mask);
      tmpDM = *add_to_DM(&tmpDM, &thing);
      add_DM_to_net(tmpDM, &AllDMs);
    }
    display_net();
  }
  if(strcmp(op,(char*)"\"delete\"") == 0){
    set_object_dim(&thing, atoi(get_json_attr_object_server((char*)"dim", jobj)));
    set_object_color(&thing, get_json_attr_object_server((char*)"color",jobj));
    set_object_name(&thing, get_json_attr_object_server((char*)"name",jobj));
    set_object_state(&thing, get_json_attr_object_server ((char*)"state",jobj));
    set_object_type(&thing, get_json_attr_object_server((char*)"type",jobj));
    if(strcmp(get_DM_IP(&AllDMs, ip)->ip, (char*)"none") != 0){
      DM tmpDM = *get_DM_IP(&AllDMs, ip);
      tmpDM.status = 0;
      DM newDM = *remove_from_dm(&tmpDM,&thing);
      newDM.size-=1;
      update_DM_on_net(&newDM, ip, &AllDMs);
    }else{
      no_exit_error((char*)"Id not Valid");
    }
    display_net();
  }

  if(strcmp(op, (char*)"\"routine\"") == 0){
    get_json_attr_routine_server(jobj);
    AllDMs = *DM_status_watch(&AllDMs, ip);
    display_net();
  }

  if(strcmp(args, (char*)"none") == 0){
    AllDMs = *DM_status_watch(&AllDMs, (char*)"none");
  }

  free(ip);
  free(subnet_mask);
  free(op);
  free(jobj);





}
