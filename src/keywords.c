/*File per la gestione delle keyword */

#include "keywords.h"

#define MAX_KEYWORDS 100

static char *banlist[MAX_KEYWORDS];
static int kw_count = 0;
char line[256];
/*carica il file*/
int load_key(const char *path){
    FILE *fp = fopen(path, "r");
    /*controlla se vuoto/aperto correttamente*/
    if(fp == NULL){
        perror("Error opening file");
        return -1;
    }
    
    /*inizializza un contatore per tenere traccia delle parole */
    /*organizza il file in elementi di array*/
    while(fgets(line, sizeof(line), fp) && kw_count < MAX_KEYWORDS){
        banlist[kw_count] = strdup(line); // Duplica la stringa e la assegna alla banlist
        kw_count++;
    }
    fclose(fp);
    return kw_count; 
}


/*controlla il buffer e verifica che nella stringa non vi sia alcuna keyword*/
int check_buff(const uint8_t *buf, size_t len) {
    for (int i = 0; i < kw_count; i++) {
        const char *keyword = banlist[i];
        size_t key_len = strlen(keyword);
        
        if (key_len == 0 || key_len > len) {
            continue;  // parola vuota o troppo lunga per questo buffer
        }
        
        // Scansiona il buffer offset per offset
        for (size_t offset = 0; offset <= len - key_len; offset++) {
            int found = 1;
            for (size_t j = 0; j < key_len; j++) {
                if (buf[offset + j] != (uint8_t)keyword[j]) {
                    found = 0;
                    break;
                }
            }
        if (found) return 1;
        }
    }
    return 0;
}
/*una volta terminato l'utilizzo della banlist, la pulisce*/
int free_banlist() {
    for (int i = 0; i < kw_count; i++) {
        free(banlist[i]); 
    }
    kw_count = 0;
}