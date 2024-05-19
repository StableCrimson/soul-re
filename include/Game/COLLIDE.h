#ifndef _COLIDE_H_
#define _COLIDE_H_

#include "Game/TYPES.h"
#include "Game/FX.h"

// size: 0xC
typedef struct _TFace {
    // offset: 0000 (6 bytes)
    struct _Face face;
    // offset: 0006
    unsigned char attr;
    // offset: 0007
    char sortPush;
    // offset: 0008
    unsigned short normal;
    // offset: 000A
    unsigned short textoff;
} TFace;

// size: 0x8
typedef struct _Normal {
    // offset: 0000
    short x;
    // offset: 0002
    short y;
    // offset: 0004
    short z;
    // offset: 0006
    short pad;
} Normal;

// size: 0x30
typedef struct _CollideInfo {
    // offset: 0000
    void *level;
    // offset: 0004
    char flags;
    // offset: 0005
    char segment;
    // offset: 0006
    char type0;
    // offset: 0007
    char type1;
    // offset: 0008
    void *prim0;
    // offset: 000C
    void *prim1;
    // offset: 0010
    void *inst0;
    // offset: 0014
    void *inst1;
    // offset: 0018 (8 bytes)
    struct SVECTOR point0;
    // offset: 0020 (8 bytes)
    struct SVECTOR point1;
    // offset: 0028 (6 bytes)
    struct _Position offset;
    // offset: 002E
    short bspID;
} CollideInfo;

// size: 0xC
typedef struct _Triangle2D {
    // offset: 0000
    short x0;
    // offset: 0002
    short y0;
    // offset: 0004
    short x1;
    // offset: 0006
    short y1;
    // offset: 0008
    short x2;
    // offset: 000A
    short y2;
} Triangle2D;

// size: 0x1C
typedef struct _HBox {
    // offset: 0000
    short flags;
    // offset: 0002
    unsigned char id;
    // offset: 0003
    unsigned char rank;
    // offset: 0004
    short minX;
    // offset: 0006
    short minY;
    // offset: 0008
    short minZ;
    // offset: 000A
    short maxX;
    // offset: 000C
    short maxY;
    // offset: 000E
    short maxZ;
    // offset: 0010
    short refMinX;
    // offset: 0012
    short refMinY;
    // offset: 0014
    short refMinZ;
    // offset: 0016
    short refMaxX;
    // offset: 0018
    short refMaxY;
    // offset: 001A
    short refMaxZ;
} HBox;

// size: 0x2C
typedef struct _PCollideInfo {
    // offset: 0000
    short type;
    // offset: 0002
    short segment;
    // offset: 0004
    void *prim;
    // offset: 0008
    struct _Instance *inst;
    // offset: 000C (8 bytes)
    struct SVECTOR wNormal;
    // offset: 0014 (8 bytes)
    struct SVECTOR *newPoint;
    // offset: 0018 (8 bytes)
    struct SVECTOR *oldPoint;
    // offset: 001C (8 bytes)
    struct SVECTOR cldPoint;
    // offset: 0024
    long collideType;
    // offset: 0028
    struct _Instance *instance;
} PCollideInfo;

int COLLIDE_PointInTriangle(struct _SVector *v0, struct _SVector *v1, struct _SVector *v2, struct _SVector *point, struct _SVector *normal);
int COLLIDE_PointInTriangle2DPub(short *v0, short *v1, short *v2, short *point);
void COLLIDE_SetBSPTreeFlag(struct _CollideInfo *collideInfo, short flag);

#endif
