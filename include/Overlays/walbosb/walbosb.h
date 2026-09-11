#ifndef _WALBOSB_H_
#define _WALBOSB_H_

#include "common.h"

// size: 0x10
typedef struct _WalbosbVars
{
    // offset: 0x0000
    int tauntTimer;
    // offset: 0x0004
    short tauntState;
    // offset: 0x0006
    short pitch;
    // offset: 0x0008
    short abortedAttacks;
    // offset: 0x000A
    short junk;
    // offset: 0x000C
    Instance *autofaceInst;
} WalbosbVars;

#endif
