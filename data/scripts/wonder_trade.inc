WonderTradeScript::
    lock
    faceplayer

    @ if they don't want to WT, bail
    msgbox sText_WantToStartWonderTrade MSGBOX_YESNO
    compare VAR_RESULT 1
    goto_if_ne WonderTradeScript_EarlyEnd

    @ show party menu to choose Pokemon
    msgbox sText_ChoosePokemonToTrade MSGBOX_AUTOCLOSE
    special ChoosePokemonFromParty
    waitstate

    @ if they pressed B to cancel, bail
    compare VAR_0x8004 6
    goto_if_ge WonderTradeScript_EarlyEnd

    @ if the chosen Pokémon is an egg, bail
    specialvar VAR_RESULT ScriptGetPartyMonSpecies
    compare VAR_RESULT SPECIES_EGG
    goto_if_eq WonderTradeScript_PlayerChoseEgg

    msgbox sText_SearchForTradePartner MSGBOX_AUTOCLOSE

    @ try to find a Pokemon to WT to the player
    specialvar VAR_RESULT GenerateRandomPokemon
    compare VAR_RESULT 0
    goto_if_eq WonderTradeScript_TimedOut

    msgbox sText_TradePartnerWasFound MSGBOX_AUTOCLOSE

    @ DoInGameTradeScene needs the player's Pokemon to be on 0x8005
    copyvar VAR_0x8005, VAR_0x8004
    @ actually do the trade animation
    special DoInGameTradeScene
    waitstate

    @ intentional fallthrough

WonderTradeScript_EarlyEnd:
    msgbox sText_ComeBackToWonderTrade MSGBOX_AUTOCLOSE
    release
    end

WonderTradeScript_PlayerChoseEgg:
    msgbox sText_EggsCantBeTraded MSGBOX_AUTOCLOSE
    goto WonderTradeScript_EarlyEnd

WonderTradeScript_TimedOut:
    msgbox sText_TradePartnerCouldntBeFound MSGBOX_AUTOCLOSE
    goto WonderTradeScript_EarlyEnd

sText_WantToStartWonderTrade:
    .string "Would you like to start a\nWONDER TRADE?$"
sText_ComeBackToWonderTrade:
    .string "Please come back whenever you\nwant to make a WONDER TRADE.$"
sText_ChoosePokemonToTrade:
    .string "Please choose the POKéMON you\nwish to trade.$"
sText_EggsCantBeTraded:
    .string "I'm sorry, but EGGs cannot be\ntraded.$"
sText_SearchForTradePartner:
    .string "Searching for a trade partner...\nPlease wait.$"
sText_TradePartnerWasFound:
    .string "A trade partner has been found!\nThe trade will now start.$"
sText_TradePartnerCouldntBeFound:
    .string "A trade partner could not be found.\nPlease try again later.$"
