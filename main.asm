.gba
.thumb

.open "rom.gba", "test.gba", 0x08000000

.org allocation
.area allocation_size
    .importobj "build/linked.o"
.endarea

// // Player house PC script tile (for debugging)
// .org 0x083B977C
// .word WonderTradeScript

.org gSpecials + SPECIAL_GenerateRandomPokemon * 4
.word GenerateRandomPokemon |1

.close

.definelabel gSpecials, readu32("rom.gba", 0x08069F18 & 0x1FFFFFF)
