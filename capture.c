/* C */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ds1052e.h"

/* The DS1052E seems to return bad datapoints at the end of the capture. */
#define BAD_DATAPOINTS 10

#define BUF_SIZE 256

struct channel {
    char *name;     /* name of the channel in SCPI commands */
    uint8_t *data;  /* pointer to buffer for capture data */
    float scale;    /* vertical scale */
};

size_t download_capture(    /* returns number of bytes in capture */
    uint8_t **data          /* pointer to the pointer to the buffer to store data */
) {
    char buf[11];   /* first 10 bytes are a header */
    size_t bytes;   /* number of bytes received */

    instr_readstr(buf, sizeof(buf));

    /* First byte is '#', second byte is '8', the next 8 bytes are how many
       datapoints are in the scope capture. */
    bytes = atoi(&buf[2]);
    *data = malloc(bytes);
    instr_read(*data, bytes);

    return bytes;
}

float get_datapoint(        /* returns the datapoint value, converted from
                               0-255 */
    struct channel *chan,   /* channel */
    unsigned i              /* which datapoint */
) {
    /* The datapoint has to be inverted, hence the subtraction from 255. */
    return ((float)(255 - chan->data[i]) / 255.0) * chan->scale;
}

int capture() {
    int i, j;           /* loop iterators */
    char buf[BUF_SIZE]; /* buffer for storing SCPI commands/responses */
    size_t len = 0;     /* number of datapoints captured */
    float timescale;    /* horizontal timescale (entire capture) */
    float time_offset;  /* time offset of first datapoint from trigger */
    float timestep;     /* timestep per datapoint */
    struct channel chan[] = {
        {"CHAN1", NULL, 0},
        {"CHAN2", NULL, 0}
    };
    int num_chans = sizeof(chan) / sizeof(chan[0]);

    /* Tell the scope we want normal sized (600 pts) captures. */
    instr_writestr(":WAV:POIN:MODE NOR");

    /* Get the horizontal timescale from the scope. */
    instr_writestr(":TIM:SCAL?");
    instr_readstr(buf, BUF_SIZE);
    /* Value comes in as V/div and there's 12 divs on the display. */
    timescale = atof(buf) * 12.0;

    /* Find out when the trigger happened. */
    instr_writestr(":TIM:OFFS?");
    instr_readstr(buf, BUF_SIZE);
    time_offset = atof(buf) - timescale / 2;

    for (i = 0; i < num_chans; i++) {
        /* Is this channel on? */
        sprintf(buf, ":%s:DISP?", chan[i].name);
        instr_writestr(buf);
        instr_readstr(buf, BUF_SIZE);
        if (!strcmp(buf, "1")) {
            /* Get the vertical scale. */
            sprintf(buf, ":%s:SCAL?", chan[i].name);
            instr_writestr(buf);
            instr_readstr(buf, BUF_SIZE);
            chan[i].scale = atof(buf) * 8;

            /* Grab the capture. */
            sprintf(buf, ":WAV:DATA? %s", chan[i].name);
            instr_writestr(buf);
            len = download_capture(&chan[i].data);
        }
    }

    /* After the program exits the scope stays in RMT (remote) mode.
       The front panel is locked in remote mode. Unlock it. */
    instr_writestr(":KEY:LOCK DIS");

    /* If we didn't grab any points from any channels, exit. */
    if (!len)
        return 1;

    timestep = timescale / (float)len;

    /* Print the CSV. Skip the last datapoints because they're bad. */
    for (i = 0; i < len - BAD_DATAPOINTS; i++) {
        /* Print the timestamp. */
        printf("%e", (i * timestep) + time_offset);

        /* Print the datapoints for each channel. */
        for (j = 0; j < num_chans; j++) {
            if (chan[j].data)
                printf(",%e", get_datapoint(&chan[j], i));
        }

        printf("\n");
    }

    return 0;
}
