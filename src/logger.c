#include "logger.h"




FILE * openfile(const char *path){
    FILE *fop = fopen(path, "a");
    if (fop == NULL) {
        perror("Error opening file");
        return NULL;
    }
    return fop;
}

void write_log(FILE *fop, log_direction dir, const uint8_t *buf, size_t len){
    if(fop == NULL) {
        perror("Error: File not opened");
        return;
    }
    time_t now = time(NULL);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(fop, "[%s] %s: ", time_str, (dir == UPSTREAM) ? "UPSTREAM" : "DOWNSTREAM");
    for(size_t i = 0; i < len && i < 64; i++) {
        fprintf(fop, "%02X ", buf[i]);
    }
    fprintf(fop, "\n");
}

void closefile(FILE *fop){
    if(fop != NULL) {
        fclose(fop);
    }
}