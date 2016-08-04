/* C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds1052e.h"

#define BUF_SIZE 256

struct measurement {
    char *name;
    char *cmd;
};

static const struct measurement measurements[] = {
    {"Vptp", "VPP"},
    {"Vmax", "VMAX"},
    {"Vmin", "VMIN"},
    {"Vavg", "VAV"},
    {"Vrms", "VRMS"},
    {"f", "FREQ"},
    {"T", "PER"}
};

int measure() {
    int chan, i;            /* loop iterators */
    char buf[BUF_SIZE];     /* buffer for storing SCPI commands/responses */
    float m;                /* measurement retrieved */

    for (i = 0; i < sizeof(measurements) / sizeof(struct measurement); i++) {
        printf("%s\t", measurements[i].name);

        for (chan = 1; chan <= 2; chan++) {
            sprintf(buf, ":CHAN%d:DISP?", chan);
            instr_writestr(buf);
            instr_readstr(buf, BUF_SIZE);

            if (!strcmp(buf, "1")) {
                sprintf(buf, ":MEAS:%s? CHAN%d", measurements[i].cmd, chan);
                instr_writestr(buf);
                instr_readstr(buf, BUF_SIZE);

                m = atof(buf);
                printf("%e\t", m);
            }
        }

        printf("\n");
    }

    /* After the program exits the scope stays in RMT (remote) mode.
       The front panel is locked in remote mode. Unlock it. */
    instr_writestr(":KEY:LOCK DIS");

    return 0;
}
