/* C */
#include <stdio.h>
#include <string.h>

#include "ds1052e.h"

int main(
    int argc,
    char **argv
) {
    if (argc < 2) {
        fprintf(stderr, "missing path to device file\n");
        return 1;
    }

    if (argc < 3) {
        fprintf(stderr, "missing command\n");
        return 1;
    }

    if (!instr_open(argv[1]))
        return 1;

    if (!strcmp(argv[2], "capture"))
        return capture();

    fprintf(stderr, "unrecognized command\n");
    return 1;
}
