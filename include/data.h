#pragma once

struct PACKED Trainer
{
    u8 unk_0[4];
    u8 trainerName[12];
    u8 unk_10[16];
    u8 partySize;
    u8 unk_24[7];
};

// extern const struct Trainer gTrainers[];

typedef const struct Trainer TrainerArray[];
extern const TrainerArray * const gTrainersPtr;
#define gTrainers (*gTrainersPtr)
