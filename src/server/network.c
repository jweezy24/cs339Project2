#include <stdio.h>
#include <stdlib.h>

typedef struct networkObjects{
  DM* things;
  int size;
}network;

void init_network(network* net){
  net = malloc(sizeof(network));
  net->things = malloc(sizeof(DM));
  net->size = 0;
}

int check_if_DM(network* net, char* ip){
  for(int i = 0; i < net->size; i++ ){
    if (strcmp(net->things[i].ip, ip) == 0){
      return 0;
    }
  }
  return 1;

}

DM* get_DM_IP(network* net, char* ip){
  for(int i = 0; i < net->size; i++ ){
    if (strcmp(net->things[i].ip, ip) == 0){
      return &net->things[i];
    }
  }
  return create_nullDM();
}

void add_DM_to_net(DM dm, network* net){
  net->things = realloc(net->things, sizeof(DM)*(net->size+1));
  net->things[net->size] = dm;
  net->size+=1;
}

void free_network(network* net){
  for (int i =0; i < net->size; i++){
    freeDM(&net->things[i]);
  }
}
