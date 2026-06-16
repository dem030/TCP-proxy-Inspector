#ifndef KEYWORDS_H
#define KEYWORDS_H
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* funzione per il caricamento del file contenente le keyword*/
int load_key(const char *path); 

/*funzione per il controllo del buffer su keyword potenzialmente malevole*/

int check_buf(const uint8_t *buf ,size_t len);


/*funzione per la pulizia di banlist*/
int free_banlist();
#endif