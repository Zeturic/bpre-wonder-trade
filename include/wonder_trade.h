#pragma once

#define MAX_WONDER_TRADE_ATTEMPTS 500

#define BLACKLIST_TRAINER(trainerNumber) [trainerNumber] 0xFF
#define IS_BLACKLISTED(trainerNumber) (gWonderTradeTrainerBlacklist[trainerNumber])

extern const u8 gWonderTradeTrainerBlacklist[];

u16 StringLength12(const u8 *str);
