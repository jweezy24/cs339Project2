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
  if(net->size > 0){
    for(int i = 0; i < net->size; i++ ){
      if (strcmp(net->things[i].ip, ip) == 0){
        return &net->things[i];
      }
    }
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
  printf("%d\n", net->size);
  net->things = realloc(net->things, sizeof(DM)*(net->size+1));
  net->things[net->size] = dm;
  net->size+=1;
}

network* remove_from_network(network* tmpNet, DM* badDM){
  network *newNet = malloc(sizeof(network));
  newNet->things = malloc(tmpNet->size * sizeof(DM));
  newNet->size = tmpNet->size;
  int netPos=0;
  for(int i = 0; i < (tmpNet)->size; i++){
    if(strcmp(badDM->ip, (tmpNet)->things[i].ip) != 0){
      DM *d;
      DM_copy_new(d, &(tmpNet)->things[i]);
      add_DM_to_net(d,newNet);
      netPos+=1;
    }
  }
  if(netPos == 0){
    newNet->size =0;
  }
  return newNet;
}

network* DM_status_watch(network* net, char* ip){
  for(int i = 0; i < net->size; i++){
    if(net->things[i].status <= -5){
     return remove_from_network(net, &net->things[i]);
    }else if(strcmp(net->things[i].ip, ip) != 0){
      net->things[i].status-=1;
    }else{
      net->things[i].status=0;
    }

  }
  return net;
}

void free_network(network* net){
  for (int i =0; i < net->size; i++){
    freeDM(&net->things[i]);
  }
}
