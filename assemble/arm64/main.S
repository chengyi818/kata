.text
.file "main.c"
.globl main  // -- Begin function main
.p2align 2

.typemain,@function
main:                                   // @main
// %bb.0:
sub sp, sp, #32                     // =32
stp x29, x30, [sp, #16]             // 16-byte Folded Spill
addx29, sp, #16                    // =16
movw8, wzr
sturwzr, [x29, #-4]
adrpx0, .L.str
addx0, x0, :lo12:.L.str
strw8, [sp, #8]                    // 4-byte Folded Spill
blprintf
ldrw8, [sp, #8]                    // 4-byte Folded Reload
movw0, w8
ldpx29, x30, [sp, #16]             // 16-byte Folded Reload
addsp, sp, #32                     // =32
ret
