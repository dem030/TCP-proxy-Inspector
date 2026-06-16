#ifndef RELAY_H
#define RELAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>


/*funzione per lo smistamento dei messaggi*/
int sort_stream(int sockfdclient, int sockfdserver);
#endif