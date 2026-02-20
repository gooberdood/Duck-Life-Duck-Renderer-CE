#include "ducks.h"
#include <fileioc.h>

#define ducks_HEADER_SIZE 0

unsigned char *ducks_appvar[3] =
{
    (unsigned char*)0,
    (unsigned char*)28,
    (unsigned char*)108,
};

unsigned char ducks_init(void)
{
    unsigned int data, i;
    uint8_t appvar;

    appvar = ti_Open("ducks", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)ducks_appvar[0] + ducks_HEADER_SIZE;
    for (i = 0; i < 3; i++)
    {
        ducks_appvar[i] += data;
    }

    ti_Close(appvar);

    return 1;
}

