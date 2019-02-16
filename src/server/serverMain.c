/*
 * udpserver.c - A simple UDP echo server
 * usage: udpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "queueUpPackets.c"
#include "recievePacket.c"
#include "threadHub.c"



int main(int argc, char **argv) {

  /*
   * check command line arguments
   */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  init_network(&AllDMs);
  init_queue(&packets);
  int count = 1;
  while(1){
    if(socket_OK == 0)
      create_recieve_thread(argv[1]);
    if(packets.elements > 0){
      parseJson(dequeue(&packets)->currentWord);
    }
  }
}
