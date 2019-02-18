/*
 * udpserver.c - A simple UDP echo server
 * usage: udpserver <port>
 */

int thread_count=0;

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
<<<<<<< HEAD
#include <pthread.h>
#include "queueUpPackets.c"
#include "recievePacket.c"
#include "threadHub.c"
=======
#include "serverTranslate.h"
#include "messageReader.c"
#include <pthread.h>
>>>>>>> JackB



int main(int argc, char **argv) {

  /*
   * check command line arguments
   */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
<<<<<<< HEAD
  init_network(&AllDMs);
  init_queue(&packets);
  while(1){
    if(socket_OK == 0 && thread_count < 10){
      create_recieve_thread(argv[1]);
      if(packets.elements == 0){
        parseJson((char*)"none");
      }
    }
    if(packets.elements > 0){
      parseJson(dequeue(&packets)->currentWord);
    }
=======
  portno = atoi(argv[1]);

  /*
   * socket: create the parent socket
   */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");

  /* setsockopt: Handy debugging trick that lets
   * us rerun the server immediately after we kill it;
   * otherwise we have to wait about 20 secs.
   * Eliminates "ERROR on binding: Address already in use" error.
   */
  optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
	     (const void *)&optval , sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)portno);

  /*
   * bind: associate the parent socket with a port
   */
  if (bind(sockfd, (struct sockaddr *) &serveraddr,
	   sizeof(serveraddr)) < 0)
    error("ERROR on binding");

  /*
   * main loop: wait for a datagram, then echo it
   */
  clientlen = sizeof(clientaddr);
  // allocate space for threading
  pthread_t *tid = malloc( 20 * sizeof(pthread_t) );
  // for making correct thread number
  int threadnum = 0;
  // setting joinable attribute
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  while (1) {
    
    /*
     * recvfrom: receive a UDP datagram from a client
     */
    bzero(buf, BUFSIZE);
    n = recvfrom(sockfd, buf, BUFSIZE, 0,
		 (struct sockaddr *) &clientaddr, &clientlen);
    
    //create thread for updating, sending updates
    pthread_create( &tid[threadnum], &attr, parseJson,(void *)buf);
    threadnum++;
    if (n < 0)
      error("ERROR in recvfrom");

    /*
     * gethostbyaddr: determine who sent the datagram
     */
    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("ERROR on inet_ntoa\n");
    printf("server received datagram from %s (%s)\n",
	   hostp->h_name, hostaddrp);
    printf("server received %d/%d bytes: %s\n", strlen(buf), n, buf);

    /*
     * sendto: echo the input back to the client
     */
    n = sendto(sockfd, buf, strlen(buf), 0,
	       (struct sockaddr *) &clientaddr, clientlen);
    if (n < 0)
      error("ERROR in sendto");
>>>>>>> JackB
  }

  /* Wait for all threads to complete */
    for (int i=0; i<threadnum; i++) {
        pthread_join(tid[i], NULL);
    }
    printf ("Main(): Waited on %d  threads. Done.\n", threadnum);

}
