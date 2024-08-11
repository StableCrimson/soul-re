#include "common.h"
#include "Game/PIPE3D.h"
#include "Game/MATH3D.h"
#include "Game/HASM.h"
#include "Game/CAMERA.h"
#include "Game/GAMELOOP.h"
#include "Game/LIGHT3D.h"
#include "Game/STREAM.h"

void PIPE3D_AspectAdjustMatrix(MATRIX *matrix)
{
    int temp, temp2, temp3; // not from decls.h

    temp = matrix->m[1][0];
    temp2 = matrix->m[1][1];
    temp3 = matrix->m[1][2];

    matrix->m[1][0] = temp;
    matrix->m[1][1] = temp2;
    matrix->m[1][2] = temp3;

    matrix->m[0][0] = (matrix->m[0][0] * 512) / 320;
    matrix->m[0][1] = (matrix->m[0][1] * 512) / 320;
    matrix->m[0][2] = (matrix->m[0][2] * 512) / 320;
}

void PIPE3D_CalculateWCTransform(CameraCore *cameraCore)
{
    MATRIX user_rotation;
    MATRIX first;
    MATRIX *cam_wcTrans;
    SVECTOR v0;
    VECTOR v1;

    cam_wcTrans = cameraCore->wcTransform;

    v0.vx = -cameraCore->position.x;
    v0.vy = -cameraCore->position.y;
    v0.vz = -cameraCore->position.z;

    if (!(gameTrackerX.debugFlags & 0x8))
    {
        MATH3D_SetUnityMatrix(&user_rotation);

        RotMatrixZ(-cameraCore->rotation.z, &user_rotation);
        RotMatrixX(-cameraCore->rotation.x, &user_rotation);
        RotMatrixY(-cameraCore->rotation.y, &user_rotation);

        v0.vx = -cameraCore->position.x;
        v0.vy = -cameraCore->position.y;
        v0.vz = -cameraCore->position.z;
    }
    else
    {
        MATH3D_SetUnityMatrix(&user_rotation);

        RotMatrixZ(-cameraCore->debugRot.z, &user_rotation);
        RotMatrixY(-cameraCore->debugRot.y, &user_rotation);
        RotMatrixX(-cameraCore->debugRot.x, &user_rotation);

        v0.vx = -cameraCore->debugPos.x;
        v0.vy = -cameraCore->debugPos.y;
        v0.vz = -cameraCore->debugPos.z;

        cameraCore->nondebugPos.x = cameraCore->position.x;
        cameraCore->nondebugPos.y = cameraCore->position.y;
        cameraCore->nondebugPos.z = cameraCore->position.z;

        cameraCore->position.x = cameraCore->debugPos.x;
        cameraCore->position.y = cameraCore->debugPos.y;
        cameraCore->position.z = cameraCore->debugPos.z;
    }

    first.m[0][0] = 4096;
    first.m[0][1] = 0;
    first.m[0][2] = 0;

    first.m[1][0] = 0;
    first.m[1][1] = 0;
    first.m[1][2] = -4096;

    first.m[2][0] = 0;
    first.m[2][1] = 4096;
    first.m[2][2] = 0;

    MulMatrix0(&first, &user_rotation, cam_wcTrans);
    MulMatrix0(&first, &user_rotation, cameraCore->wcTransform2);

    PIPE3D_AspectAdjustMatrix(cam_wcTrans);

    cam_wcTrans->m[0][0] = (cam_wcTrans->m[0][0] * cameraCore->screenScale.x) >> 12;
    cam_wcTrans->m[0][1] = (cam_wcTrans->m[0][1] * cameraCore->screenScale.x) >> 12;
    cam_wcTrans->m[0][2] = (cam_wcTrans->m[0][2] * cameraCore->screenScale.x) >> 12;

    cam_wcTrans->m[1][0] = (cam_wcTrans->m[1][0] * cameraCore->screenScale.y) >> 12;
    cam_wcTrans->m[1][1] = (cam_wcTrans->m[1][1] * cameraCore->screenScale.y) >> 12;
    cam_wcTrans->m[1][2] = (cam_wcTrans->m[1][2] * cameraCore->screenScale.y) >> 12;

    cam_wcTrans->m[2][0] = (cam_wcTrans->m[2][0] * cameraCore->screenScale.z) >> 12;
    cam_wcTrans->m[2][1] = (cam_wcTrans->m[2][1] * cameraCore->screenScale.z) >> 12;
    cam_wcTrans->m[2][2] = (cam_wcTrans->m[2][2] * cameraCore->screenScale.z) >> 12;

    gte_SetRotMatrix(cam_wcTrans);
    gte_ldv0(&v0);
    gte_nrtv0();
    gte_stlvnl(&v1);

    TransMatrix(cam_wcTrans, &v1);

    gte_SetRotMatrix(cameraCore->wcTransform2);
    gte_ldv0(&v0);
    gte_nrtv0();
    gte_stlvnl(&v1);

    TransMatrix(cameraCore->wcTransform2, &v1);
}

void PIPE3D_InvertTransform(MATRIX *target, MATRIX *source)
{
    VECTOR sourceTrans;
    MATRIX normMat;

    if (((short *)&source->t)[-1] == 1)
    {
        PIPE3D_NormalizeMatrix(&normMat, source);

        TransposeMatrix(&normMat, target);
    }
    else
    {
        TransposeMatrix(source, target);
    }

    sourceTrans.vx = -source->t[0];
    sourceTrans.vy = -source->t[1];
    sourceTrans.vz = -source->t[2];

    ApplyMatrixLV(target, &sourceTrans, (VECTOR *)target->t);
}

long PIPE3D_MatrixColumnLength(MATRIX *transform, long column)
{
    return MATH3D_FastSqrt0(MATH3D_SquareLength(transform->m[0][column], transform->m[1][column], transform->m[2][column]));
}

void PIPE3D_NormalizeMatrix(MATRIX *target, MATRIX *source)
{
    VECTOR scalevec;
    long scale;
    typedef struct
    {
        long m[3];
    } tmm;
    typedef struct
    {
        long m[5];
    } cmm;

    scale = PIPE3D_MatrixColumnLength(source, 0);

    if (scale != 0)
    {
        scale = 16777216 / scale;
    }

    scalevec.vx = scale;

    scale = PIPE3D_MatrixColumnLength(source, 1);

    if (scale != 0)
    {
        scale = 16777216 / scale;
    }

    scalevec.vy = scale;

    scale = PIPE3D_MatrixColumnLength(source, 2);

    if (scale != 0)
    {
        scale = 16777216 / scale;
    }

    scalevec.vz = scale;

    *(tmm *)(target->t) = *(tmm *)(source->t);
    *(cmm *)(target->m) = *(cmm *)(source->m);

    ScaleMatrix(target, &scalevec);
}

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_TransformVerticesToWorld);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_InstanceTransformAndDraw);

void PIPE3D_InstanceListTransformAndDrawFunc(StreamUnit *unit, unsigned long **ot, CameraCore *cameraCore, Instance *instance)
{
    VertexPool *vertexPool;
    PrimPool *primPool;
    VECTOR dpv[2];
    long maxRad;
    Level *level;
    SVECTOR bsPos;

    level = unit->level;

    vertexPool = gameTrackerX.vertexPool;
    primPool = gameTrackerX.primPool;

    bsPos.vx = instance->position.x;
    bsPos.vy = instance->position.y;
    bsPos.vz = instance->position.z;

    if ((unit == NULL) || (!(unit->flags & 0x1)) || (unit->StreamUnitID == gameTrackerX.StreamUnitID) || (WARPGATE_IsObjectOnWarpSide(instance) != 0))
    {
        maxRad = instance->object->modelList[instance->currentModel]->maxRad;

        gte_SetRotMatrix(&cameraCore->vvNormalWorVecMat[0]);
        gte_ldv0(&bsPos);
        gte_nrtv0();
        gte_stlvnl(&dpv[0]);

        dpv[0].vx -= cameraCore->vvPlaneConsts[0];

        if ((-maxRad < dpv[0].vx) && (dpv[0].vx < (cameraCore->farPlane + maxRad)) && (-maxRad < (dpv[0].vy - cameraCore->vvPlaneConsts[1]))
        && (-maxRad < (dpv[0].vz - cameraCore->vvPlaneConsts[2])))
        {
            gte_SetRotMatrix(&cameraCore->vvNormalWorVecMat[1]);
            gte_ldv0(&bsPos);
            gte_nrtv0();
            gte_stlvnl(&dpv[1]);

            if ((-maxRad < (dpv[1].vx - cameraCore->vvPlaneConsts[3])) && (-maxRad < (dpv[1].vy - cameraCore->vvPlaneConsts[4])))
            {
                if ((instance->flags & 0x80))
                {
                    PIPE3D_AnimateTextures(instance->object->modelList[instance->currentModel]->aniTextures, instance->currentTextureAnimFrame);
                }
                else
                {
                    PIPE3D_AnimateTextures(instance->object->modelList[instance->currentModel]->aniTextures, gameTrackerX.frameCount);

                    instance->currentTextureAnimFrame++;
                }

                LIGHT_SetMatrixForLightGroupInstance(instance, level);

                if ((!(instance->halvePlane.flags & 0xB)) || ((instance->flags2 & 0x800000)))
                {
                    PIPE3D_InstanceTransformAndDraw(instance, cameraCore, vertexPool, primPool, ot, NULL);
                }
                else
                {
                    PIPE3D_HalvePlaneInstanceTransformAndDraw(instance, cameraCore->wcTransform, vertexPool, primPool, ot, NULL);
                }

                if ((instance->flags2 & 0x40))
                {
                    LIGHT_DrawShadow(cameraCore->wcTransform, instance, primPool, ot);
                }

                if (instance->additionalDrawFunc != NULL)
                {
                    instance->additionalDrawFunc(cameraCore->wcTransform, instance, vertexPool, primPool, ot);
                }

                gameTrackerX.visibleInstances++;

                instance->flags |= 0x200;
            }
            else
            {
                instance->flags &= ~0x200;
            }
        }
        else
        {
            instance->flags &= ~0x200;
        }
    }
    else
    {
        instance->flags &= ~0x200;
    }
}

void PIPE3D_InstanceListTransformAndDraw(StreamUnit *unit, GameTracker *gameTracker, unsigned long **ot, CameraCore *cameraCore)
{
    Instance *instance;
    int id;
    Instance *player;

    instance = gameTracker->instanceList->first;

    player = gameTracker->playerInstance;

    id = unit->StreamUnitID;

    if ((player->currentStreamUnitID == id) && (!(player->flags & 0x800)))
    {
        PIPE3D_InstanceListTransformAndDrawFunc(unit, ot, cameraCore, player);
    }

    for (; instance != NULL; instance = instance->next)
    {
        if ((!(instance->flags & 0x800)) && (!(instance->flags2 & 0x4000000)) && (instance->currentStreamUnitID == id) && (instance != player))
        {
            PIPE3D_InstanceListTransformAndDrawFunc(unit, ot, cameraCore, instance);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_TransformFromZAxis);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_CalcWorldToSplitPlaneTransform);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_TransformAnimatedSplitInstanceVertices);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_TransformSplitInstanceVertices);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_AnimateTextures);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_AnimateTerrainTextures);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_HalvePlaneInstanceTransformAndDraw);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_HalvePlaneGetRingPoints);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_DoGlow);

INCLUDE_ASM("asm/nonmatchings/Game/PIPE3D", PIPE3D_Segment2ScreenPt);
