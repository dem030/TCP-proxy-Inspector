#ifndef SERVER_H
#define SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
/*funzione che aspetta la connessione*/
int wait_conn(int port);
/*funzione che accetta la connessione*/
int acc_conn(int sockfd);
/*funzione che stabilisce la connessione*/
int conn(const char *ip, int port);


#endif