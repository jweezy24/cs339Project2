#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void create_recieve_thread(char* port){
  pthread_t tid;
  void* ret;

  pthread_create(&tid, NULL, recieve_packet, (void *)port);
  pthread_join(tid, &ret);
  //pthread_exit(NULL);
}


// void get_most_recent_from_DM(char* dest_port, char* server_port){
//   pthread_t tid;
//   void* ret;
// 
//   //pthread_create(&tid, NULL, recieve_packet, (void *)port);
//   //pthread_join(tid, &ret);
// }
