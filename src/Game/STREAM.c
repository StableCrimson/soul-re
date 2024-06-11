#include "common.h"
#include "Game/STREAM.h"
#include "Game/STRMLOAD.h"
#include "Game/GAMELOOP.h"
#include "Game/MEMPACK.h"
#include "Game/INSTANCE.h"
#include "Game/OBTABLE.h"
#include "Game/PSX/AADLIB.h"

void STREAM_FillOutFileNames(char *baseAreaName, char *dramName, char *vramName, char *sfxName);
INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_FillOutFileNames);

void STREAM_AbortAreaLoad(char *baseAreaName)
{
    char vramName[80];

    STREAM_FillOutFileNames(baseAreaName, NULL, vramName, NULL);

    LOAD_AbortDirectoryChange(baseAreaName);

    LOAD_AbortFileLoad(vramName, (void *)VRAM_LoadReturn);
}

void STREAM_Init()
{
    int i;

    for (i = 0; i < 16; i++)
    {
        StreamTracker.StreamList[i].used = 0;

        StreamTracker.StreamList[i].flags = 0;

        StreamTracker.StreamList[i].StreamUnitID = 0;
    }
}

int FindObjectName(char *name)
{
    int i;
    ObjectTracker *otr;

    otr = gameTrackerX.GlobalObjects;

    for (i = 0; i < 48; i++, otr++)
    {
        if ((otr->objectStatus != 0) && (strcmpi(otr->name, name) == 0))
        {
            return i;
        }
    }

    return -1;
}

ObjectTracker *FindObjectInTracker(Object *object)
{
    int i;
    ObjectTracker *otr;

    otr = gameTrackerX.GlobalObjects;

    for (i = 0; i < 48; i++, otr++)
    {
        if ((otr->objectStatus != 0) && (otr->object == object))
        {
            return otr;
        }
    }

    return NULL;
}

StreamUnit *FindStreamUnitFromLevel(Level *level)
{
    StreamUnit *ret;
    long i;

    ret = NULL;

    for (i = 0; i < 16; i++)
    {
        if ((StreamTracker.StreamList[i].used == 2) && (StreamTracker.StreamList[i].level == level))
        {
            ret = &StreamTracker.StreamList[i];
            break;
        }
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_LoadObjectReturn);

void STREAM_DumpMonster(ObjectTracker *dumpee)
{
    Object *object;
    Instance *instance;

    object = dumpee->object;

    if (dumpee->vramBlock != NULL)
    {
        VRAM_ClearVramBlock((BlockVramEntry *)dumpee->vramBlock);
    }

    OBTABLE_RemoveObjectEntry(object);

    if (((object->oflags2 & 0x800000)) && (object->sfxFileHandle != 0))
    {
        aadFreeDynamicSfx(object->sfxFileHandle);
    }

    instance = gameTrackerX.instanceList->first;

    if (instance != NULL)
    {
        Instance *next;

        while (instance != NULL)
        {
            next = instance->next;

            if (object == instance->object)
            {
                INSTANCE_ReallyRemoveInstance(gameTrackerX.instanceList, instance, 0);
            }

            instance = next;
        }
    }

    MEMPACK_Free((char *)object);

    dumpee->object = NULL;
}

int STREAM_InList(char *name, char **nameList)
{
    char **mon;

    for (mon = nameList; *mon != NULL; mon++)
    {
        if (strcmpi(name, *mon) == 0)
        {
            return 1;
        }
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_IsSpecialMonster);

void STREAM_DumpSomeMonsters()
{
    ObjectTracker *otr;
    int i;

    otr = gameTrackerX.GlobalObjects;

    for (i = 0; i < 48; i++, otr++)
    {
        if (((otr->objectStatus == 2) && (otr->object != NULL)) && (STREAM_IsSpecialMonster((char *)otr) != 0))
        {
            STREAM_DumpMonster(otr);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_NoMonsters);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_YesMonsters);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_IsMonster);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_TryAndDumpANonResidentObject);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", InsertGlobalObject);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_GetObjectTracker);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", LoadLevelObjects);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_IsAnInstanceUsingObject);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_StreamLoadObjectAbort);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_DumpLoadingObjects);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_DumpObject);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_IsObjectInAnyUnit);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_RemoveAllObjectsNotInUse);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RemoveAllObjects);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_GetLevelWithID);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_GetStreamUnitWithID);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_CalculateWaterLevel);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_IsMorphInProgress);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_GetWaterZLevel);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_SetMainFog);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_SetStreamFog);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_ConnectStream);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_StreamLoadLevelAbort);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_DoObjectLoadAndDump);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_FinishLoad);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_LoadLevelReturn);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_StreamLoadLevelReturn);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_UpdateLevelPointer);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_WhichUnitPointerIsIn);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_UpdateObjectPointer);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_UpdateInstanceCollisionInfo);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_LoadMainVram);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_MoveIntoNewStreamUnit);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_LoadLevel);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RemoveIntroducedLights);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_RemoveInstancesWithIDInInstanceList);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_MarkUnitNeeded);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_DumpUnit);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_DumpAllUnitsNotNeeded);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_DumpAllLevels);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_LoadCurrentWarpRoom);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_RelocateLoadedWarpRooms);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_GetWarpRoomIndex);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_UpdateAddToArray);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_RemoveFromArray);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_Init);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_StartUsingWarpgate);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_EndUsingWarpgate);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsWarpgateInUse);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsWarpgateActive);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsWarpgateUsable);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsWarpgateReady);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsWarpgateSpectral);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsObjectOnWarpSide);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsItActive);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IsUnitWarpRoom);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_FixUnit);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_MarkWarpUnitsNeeded);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_IncrementIndex);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_CalcWarpFade);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_DecrementIndex);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", PreloadAllConnectedUnits);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateLevel);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateCameras);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateSavedCameras);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateLevelWithInstances);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateTerrain);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateVMObjects);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateBGObjects);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocatePlanPool);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocatePlanMarkers);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateSFXMarkers);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_AdjustMultiSpline);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_RelocateInstance);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_OffsetInstancePosition);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_SetInstancePosition);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateInstances);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", RelocateStreamPortals);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_PackVRAMObject);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_SetupInstanceFlags);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_SetupInstanceListFlags);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_InMorphInstanceListFlags);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_InMorphDoFadeValues);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_UpdateTimeMult);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_UpdateNormals);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_BringBackNormals);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_AddOffsets);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_SubtractOffsets);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_GetComponentsForTrackingPoint);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_AveragePoint);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_UpdateTrackingPoint);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_ToggleMorph);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_DoStep);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_SetFog);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_UpdateTextures);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", MORPH_Continue);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_MORPH_Relocate);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", AddVertex);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", GetPlaneDist);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", CalcVert);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", AddClippedTri);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_GetClipRect);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", GetFogColor);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", DrawFogRectangle);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_RenderAdjacantUnit);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_GetBspTree);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_BlockWarpGateEntrance);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_DrawWarpGateRim);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_HideAllCloudCovers);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_UnHideCloudCoverInUnit);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_RenderWarpGate);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", WARPGATE_RenderWarpUnit);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_DumpNonResidentObjects);

INCLUDE_ASM("asm/nonmatchings/Game/STREAM", STREAM_TryAndDumpNonResident);
