/* C */
#include <stdio.h>
#include <string.h>

/* POSIX */
#include <unistd.h>
#include <fcntl.h>

#include "ds1052e.h"

static int fd;

int instr_open(
    char *p     /* path to instrument */
) {
    fd = open(p, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "could not open %s: ", p);
        perror("");
        return 0;
    }
    return 1;
}

size_t instr_read(  /* returns number of bytes read */
    char *s,        /* buffer to read into */
    size_t len      /* how many bytes to read */
) {
    return read(fd, s, len);
}

size_t instr_readstr(   /* returns number of bytes read */
    char *s,            /* buffer to read into */
    size_t len          /* how many bytes to read */
) {
    size_t bytes = read(fd, s, len - 1);
    s[bytes] = '\0';
    return bytes;
}

void instr_writestr(
    char *s         /* string to write to instrument */
) {
    write(fd, s, strlen(s));
}
