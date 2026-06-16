#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
typedef enum { UPSTREAM, DOWNSTREAM } log_direction;
/*funzione per aprire il file di log*/
FILE * openfile(const char *path);

/*funzione per scrivere sul file di log*/
void write_log(FILE *fop, log_direction dir, const uint8_t *buf, size_t len);

/*funzione di chiusura del file*/

void closefile(FILE *fop);


#endif