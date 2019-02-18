#include <stdio.h>
#include <stdlib.h>

typedef struct networkObjects{
  DM* things;
  int size;
}network;

void init_network(network* net){
  net = (network*)malloc(sizeof(network));
  net->things = (DM*)malloc(sizeof(DM));
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
  int pos = (int)get_DM_Index(net, ip);
  if(pos != -1){
    net->things[pos] = *dm;
  }
}

void add_DM_to_net(DM dm, network* net){
<<<<<<< HEAD
  printf("%d\n", net->size);
  net->things = (DM*)realloc(net->things, sizeof(DM)*(net->size+1));
=======
  net->things = realloc(net->things, sizeof(DM)*(net->size+1));
>>>>>>> 22d0dd9d3a2eed4ff37eb2418826e5e794eb7a81
  net->things[net->size] = dm;
  net->size+=1;
}
void add_DM_to_net_new(DM dm, network* net){
  net->things = malloc(sizeof(DM));
  net->things[0] = dm;
  net->size +=1;
}

<<<<<<< HEAD
network* remove_from_network(network* tmpNet, DM* badDM){
  network *newNet = (network*)malloc(sizeof(network));
  newNet->things = (DM*)malloc(sizeof(DM));
  newNet->size = 0;
=======
network remove_from_network(network* tmpNet, DM* badDM){
  network newNet;
  init_network(&newNet);
  newNet.size = 0;
>>>>>>> 22d0dd9d3a2eed4ff37eb2418826e5e794eb7a81
  int netPos=0;
  printf("NAME OF BAD DM: %s", badDM->ip);
  for(int i = 0; i < tmpNet->size; i++){
    if(strcmp(badDM->ip, tmpNet->things[i].ip) != 0){
      if(newNet.size == 0){
        add_DM_to_net_new(tmpNet->things[i],&newNet);
        netPos+=1;
      }else{
        add_DM_to_net(tmpNet->things[i], &newNet);
        netPos+=1;
      }
    }
  }
  if(netPos == 0){
    newNet.size =0;
  }else{
    newNet.size = netPos;
  }
  return newNet;
}

network* DM_status_watch(network* net, char* ip){
  for(int i = 0; i < net->size; i++){
    //printf("%d SIZE  %s IP NET SHIT\n", net->size, net->things[0].ip);
    if(net->things[i].status <= -10){
     network newNet = remove_from_network(net, &net->things[i]);
     net = &newNet;
     //printf("%d SIZE  %s IP NET SHIT\n", newNet.size, newNet.things[0].ip);
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
