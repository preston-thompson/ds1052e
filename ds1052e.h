#ifndef _DS1052E_H
#define _DS1052E_H

#include <stddef.h>

/* instr.c */
int instr_open(char *);
size_t instr_read(char *, size_t);
size_t instr_readstr(char *, size_t);
void instr_writestr(char *);

/* capture.c */
int capture();

/* measure.c */
int measure();

#endif
