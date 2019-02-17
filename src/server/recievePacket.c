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
#include "messageReader.c"
#include <json.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>

#define BUFSIZE 1024


int socket_OK=0;


void sigpipe_handler()
{
    printf("SIGPIPE caught\n");
    socket_OK=0;
}

void close_socket(int sd){
  if(fd >= 0){
    if(shutdown(fd, SHUT_RDWR) < 0){
      error("shutdown socket");
    }
    if(close(fd) < 0){
      error("close");
    }
  }
}

void *recieve_packet(void *port) {
  int sockfd; /* socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buf */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */
  fd_set rfds;
  struct timeval tv;
  int retval;
  pthread_mutex_t lock;

  pthread_mutex_init(&lock, NULL);

  FD_ZERO(&rfds);

  tv.tv_sec = 3;
  tv.tv_usec = 0;

  portno = atoi((char*)port);

  /*
   * socket: create the parent socket
   */
   socket_OK = 1;
   pthread_mutex_lock(&lock);
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0){
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    signal(SIGPIPE,sigpipe_handler);
    error("ERROR opening socket");
  }
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
	   sizeof(serveraddr)) < 0){
       close_socket(sockfd);
       pthread_mutex_unlock(&lock);
       pthread_mutex_destroy(&lock);
       signal(SIGPIPE,sigpipe_handler);
       error("ERROR on binding");
     }

  /*
   * main loop: wait for a datagram, then echo it
   */
  clientlen = sizeof(clientaddr);

    /*
     * recvfrom: receive a UDP datagram from a client
     */
    bzero(buf, BUFSIZE);
    FD_SET(sockfd, &rfds);
    //pthread_mutex_lock(&lock);
    retval = select(sockfd +1 , &rfds, NULL, NULL, &tv);
    if(retval){
      n = recvfrom(sockfd, buf, BUFSIZE, 0,
  		 (struct sockaddr *) &clientaddr, &clientlen);
      //pthread_mutex_lock(&lock);
      enqueue(&packets, buf);
      //pthread_mutex_unlock(&lock);
      if (n < 0){
        close_socket(sockfd);
        pthread_mutex_unlock(&lock);
        pthread_mutex_destroy(&lock);
        signal(SIGPIPE,sigpipe_handler);
        error("ERROR in recvfrom");
      }

      /*
       * gethostbyaddr: determine who sent the datagram
       */
      hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
  			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
      if (hostp == NULL){
        close_socket(sockfd);
        pthread_mutex_unlock(&lock);
        pthread_mutex_destroy(&lock);
        signal(SIGPIPE,sigpipe_handler);
        error("ERROR on gethostbyaddr");
      }
      hostaddrp = inet_ntoa(clientaddr.sin_addr);
      if (hostaddrp == NULL){
        close_socket(sockfd);
        pthread_mutex_unlock(&lock);
        pthread_mutex_destroy(&lock);
        signal(SIGPIPE,sigpipe_handler);
        error("ERROR on inet_ntoa\n");
      }
      printf("server received datagram from %s (%s)\n",
  	   hostp->h_name, hostaddrp);
      printf("server received %d/%d bytes: %s\n", strlen(buf), n, buf);

      /*
       * sendto: echo the input back to the client
       */
      n = sendto(sockfd, buf, strlen(buf), 0,
  	       (struct sockaddr *) &clientaddr, clientlen);
      if (n < 0){
        close_socket(sockfd);
        pthread_mutex_unlock(&lock);
        pthread_mutex_destroy(&lock);
        signal(SIGPIPE,sigpipe_handler);
        error("ERROR in sendto");
      }
    }
    signal(SIGPIPE,sigpipe_handler);
    close_socket(sockfd);
    socket_OK = 0;
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
}
