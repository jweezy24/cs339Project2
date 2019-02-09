#include <stdio.h>
#include <stdlib.h>

typedef struct networkObjects{
  DM* things;
  int size;
}network;

void init_network(network* net){
  net = malloc(sizeof(network));
}

void set_network_null(network* net){
  net->things = malloc(sizeof(DM));
  net->things->ip = malloc(sizeof(char)*5);
  strcpy(net->things->ip,"none");
}
