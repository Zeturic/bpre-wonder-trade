#pragma once

#define MON_DATA_OT_NAME            7
#define MON_DATA_MET_LOCATION      35

struct PACKED Pokemon
{
    u8 unk_0[100];
};

extern struct Pokemon gEnemyParty[];

void SetMonData(struct Pokemon *mon, s32 field, const void *dataArg);
