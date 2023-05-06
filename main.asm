.gba
.thumb

.open "rom.gba", "test.gba", 0x08000000

.org allocation
.area allocation_size
    .word 0xFEFEFEFE
    .importobj "build/linked.o"
    .word 0xFEFEFEFE
.endarea

// // Player house PC script tile (for debugging)
// .org 0x083B977C
// .word WonderTradeScript

.org gSpecials + SPECIAL_WonderTradeGenerateMon * 4
.word WonderTradeGenerateMon |1

.close

.definelabel gSpecials, readu32("rom.gba", 0x08069F18 & 0x1FFFFFF)
