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

.close
