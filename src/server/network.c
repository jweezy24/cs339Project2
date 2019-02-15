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
    printf("HERE\n" );
    printf("%s\n", net->things[i].ip);
    printf("%s\n", ip);
    printf("%d\n", net->size);
    if (strcmp(net->things[i].ip, ip) == 0){
      printf("HERE in\n");
      return &net->things[i];
    }
    printf("HERE in2\n");
  }
  return create_nullDM();
}

int get_DM_Index(network* net, char* ip){
  for(int i = 0; i < net->size; i++ ){
    if (strcmp(net->things[i].ip, ip) == 0){
      return i;
    }
  }
  return -1;
}

void update_DM_on_net(DM* dm, char* ip, network* net){
  int pos = get_DM_Index(net, ip);
  if(pos != -1){
    net->things[pos] = *dm;
  }
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
