#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void create_recieve_thread(char* port){
  pthread_t tid;
  void* ret;

  pthread_create(&tid, NULL, recieve_packet, (void *)port);
  thread_count +=1;
  pthread_join(tid, &ret);
  //pthread_exit(NULL);
}

void create_send_thread(char* port){
  pthread_t tid;
  void* ret;

  pthread_create(&tid, NULL, recieve_packet, (void *)port);
  threadsend_count +=1;
  pthread_join(tid, &ret);
}
