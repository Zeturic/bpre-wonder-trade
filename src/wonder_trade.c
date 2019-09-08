#include "global.h"
#include "battle_main.h"
#include "battle.h"
#include "data.h"
#include "pokemon.h"
#include "random.h"
#include "text.h"
#include "wonder_trade.h"
#include "constants/battle.h"
#include "constants/opponents.h"

void GenerateRandomPokemon(void)
{
    u16 len;
    u16 trainerNum;
    u8 slot;
    
    // pick an NPC trainer slot
    do {
        trainerNum = Random() % TRAINERS_COUNT;
        len = StringLength12(gTrainers[trainerNum].trainerName);
    } while(len == 0 || PLAYER_NAME_LENGTH < len || gTrainers[trainerNum].partySize == 0 || IS_BLACKLISTED(trainerNum));

    // load that NPC trainer's Pokemon
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    CreateNPCTrainerParty(gEnemyParty, trainerNum);

    // pick a Pokemon in that trainers team and move it to the first position
    slot = Random() % gTrainers[trainerNum].partySize;
    if (slot)
        gEnemyParty[0] = gEnemyParty[slot];

    // weirdly, the game leaves your name as the OT Name of NPC trainer's Pokemon
    SetMonData(&gEnemyParty[0], MON_DATA_OT_NAME, gTrainers[trainerNum].trainerName);

    u8 metLocation = 0xFE;
    SetMonData(&gEnemyParty[0], MON_DATA_MET_LOCATION, &metLocation);
}

u16 StringLength12(const u8 *str)
{
    u32 limit = 12;
    u16 len = 0;

    while (str[len] != EOS && len <= limit)
        ++len;

    return len;
}
