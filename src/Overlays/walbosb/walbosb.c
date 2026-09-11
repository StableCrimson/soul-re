#include "Overlays/walbosb/walbosb.h"
#include "Game/SOUND.h"
#include "Game/MONSTER/MONAPI.h"
#include "Game/MONSTER/MONLIB.h"

// this conditional is for the objdiff report
#ifndef SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_WalbossMessage);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", D_88000000);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", D_88000020);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_AutofaceMarker);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_SetAutofacePos);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_ResetSetAutofacePos);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Collide);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Query);

void WALBOSB_Message(Instance *instance, unsigned long message, unsigned long data)
{

    MonsterVars *mv; // not from debug symbols

    mv = (MonsterVars *)instance->extraData;

    switch (message)
    {
    case 0x400000:
        if (data != 0)
        {
            SOUND_Play3dSound(&instance->position, 21, 650, 80, 15500);
        }
        MonsterMessage(instance, message, data);
        break;
    case 0x100001F:
    case 0x1000021:
        ((evMonsterHitData *)data)->power = 4096;
        MonsterMessage(instance, message, data);
        break;
    case 0x1000020:
        if (!(mv->mvFlags & 4))
        {
            if (instance->currentMainState != MONSTER_STATE_DEAD && instance->currentMainState != MONSTER_STATE_GENERALDEATH)
            {
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_IDLE);
                break;
            }
        }
        break;
    case 0x1000017:
        switch (data)
        {
        case 0:
            if (instance->currentMainState != MONSTER_STATE_GENERALDEATH && instance->currentMainState != MONSTER_STATE_DEAD)
            {
                mv->auxFlags |= 4;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_DEAD);
            }
            break;
        case 1:
            if (instance->currentMainState != MONSTER_STATE_GENERALDEATH && instance->currentMainState != MONSTER_STATE_DEAD)
            {
                mv->auxFlags |= 1;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_HIT);
            }
            break;
        case 2:
            if (instance->currentMainState != MONSTER_STATE_GENERALDEATH && instance->currentMainState != MONSTER_STATE_DEAD)
            {
                mv->auxFlags &= ~1;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_COMBAT);
            }
            break;
        case 3:
            if (!(mv->auxFlags & 2))
            {
                mv->auxFlags |= 2;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_IDLE);
            }
            else
            {
                mv->auxFlags &= ~2;
            }
            break;
        case 4:
            mv->auxFlags &= ~2;
            break;
        default:
            break;
        }
        break;
    case 0x40009:
    case 0x80001:
    case 0x80002:
    case 0x80003:
    case 0x80004:
    case 0x80005:
    case 0x80006:
        break;
    default:
        MonsterMessage(instance, message, data);
    }
}

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Init);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_CleanUp);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_IdleEntry);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_HandleFade);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Idle);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_CombatEntry);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Combat);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_AttackEntry);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Attack);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_HitEntry);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Hit);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_DoNothingEntry);

void WALBOSB_DoNothing() {};

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_GeneralDeathEntry);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_GeneralDeath);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_DeadEntry);

INCLUDE_ASM("asm/nonmatchings/Overlays/walbosb/walbosb", WALBOSB_Dead);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000068);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000088);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_880000D8);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000140);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000204);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000324);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000390);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000488);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_88000508);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_880005A0);

INCLUDE_RODATA("asm/nonmatchings/Overlays/walbosb/walbosb", func_880006DC);

#else 

void WALBOSB_WalbossMessage(void) {};

void WALBOSB_AutofaceMarker(void) {};

void WALBOSB_SetAutofacePos(void) {};

void WALBOSB_ResetSetAutofacePos(void) {};

void WALBOSB_Collide(void) {};

void WALBOSB_Query(void) {};

void WALBOSB_Message(Instance *instance, unsigned long message, unsigned long data)
{

    MonsterVars *mv; // not from debug symbols

    mv = (MonsterVars *)instance->extraData;

    switch (message)
    {
    case 0x400000:
        if (data != 0)
        {
            SOUND_Play3dSound(&instance->position, 21, 650, 80, 15500);
        }
        MonsterMessage(instance, message, data);
        break;
    case 0x100001F:
    case 0x1000021:
        ((evMonsterHitData *)data)->power = 4096;
        MonsterMessage(instance, message, data);
        break;
    case 0x1000020:
        if (!(mv->mvFlags & 4))
        {
            if (instance->currentMainState != MONSTER_STATE_DEAD && instance->currentMainState != MONSTER_STATE_GENERALDEATH)
            {
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_IDLE);
                break;
            }
        }
        break;
    case 0x1000017:
        switch (data)
        {
        case 0:
            if (instance->currentMainState != MONSTER_STATE_GENERALDEATH && instance->currentMainState != MONSTER_STATE_DEAD)
            {
                mv->auxFlags |= 4;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_DEAD);
            }
            break;
        case 1:
            if (instance->currentMainState != MONSTER_STATE_GENERALDEATH && instance->currentMainState != MONSTER_STATE_DEAD)
            {
                mv->auxFlags |= 1;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_HIT);
            }
            break;
        case 2:
            if (instance->currentMainState != MONSTER_STATE_GENERALDEATH && instance->currentMainState != MONSTER_STATE_DEAD)
            {
                mv->auxFlags &= ~1;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_COMBAT);
            }
            break;
        case 3:
            if (!(mv->auxFlags & 2))
            {
                mv->auxFlags |= 2;
                MON_SwitchStateDoEntry(instance, MONSTER_STATE_IDLE);
            }
            else
            {
                mv->auxFlags &= ~2;
            }
            break;
        case 4:
            mv->auxFlags &= ~2;
            break;
        default:
            break;
        }
        break;
    case 0x40009:
    case 0x80001:
    case 0x80002:
    case 0x80003:
    case 0x80004:
    case 0x80005:
    case 0x80006:
        break;
    default:
        MonsterMessage(instance, message, data);
    }
}

void WALBOSB_Init(void) {};

void WALBOSB_CleanUp(void) {};

void WALBOSB_IdleEntry(void) {};

void WALBOSB_HandleFade(void) {};

void WALBOSB_Idle(void) {};

void WALBOSB_CombatEntry(void) {};

void WALBOSB_Combat(void) {};

void WALBOSB_AttackEntry(void) {};

void WALBOSB_Attack(void) {};

void WALBOSB_HitEntry(void) {};

void WALBOSB_Hit(void) {};

void WALBOSB_DoNothingEntry(void) {};

void WALBOSB_DoNothing(void) {};

void WALBOSB_GeneralDeathEntry(void) {};

void WALBOSB_GeneralDeath(void) {};

void WALBOSB_DeadEntry(void) {};

void WALBOSB_Dead(void) {};

#endif
