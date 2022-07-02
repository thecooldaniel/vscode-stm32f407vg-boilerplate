.syntax unified
.cpu cortex-m4
.text

.global SignedMod
.thumb_func
.type SignedMod, %function
.align
SignedMod:
    sdiv r2,r0,r1
    mls  r0,r1,r2,r0
    adds r0,r0,r1
    sdiv r2,r0,r1
    mls  r0,r1,r2,r0
    bx lr

.global UnsignedMod
.thumb_func
.type UnsignedMod, %function
.align
UnsignedMod:
    sdiv r2,r0,r1
    mls  r0,r1,r2,r0
    bx lr
