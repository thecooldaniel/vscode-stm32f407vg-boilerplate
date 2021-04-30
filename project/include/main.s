.syntax unified
.cpu cortex-m4
.text

.global playground
.thumb_func
.type playground, %function
.align 

playground:
    push {r4-r12}

    mov r2, #2
    mov r3, #3
    mov r5, #4

    mov r2, #3
    adds r3, r2, #4
    # Result: r3 = 7

    mov r2, #3
    mov r3, #0
    add r3, r2, #4
    # result: r3 = 7

    @@@@ Test Flags
    @ cmp #4, #5
    @ mov r2, le
    @ result: moves 4 into r2

    mov r2, #1
    subs r2, r2, #10
    @ result: r2 = 9, N flag = 1
    IT  MI
    addmi r2, #10
    @ result: r2 set to 1 if N = 1

    mov r2, #100
    mov r3, #10
    udiv r4, r2, r3
    @ resut: r4 = 10

    @ movw, movt
    @ Immediate values have severe resitrctions. movw moves any 16 bits into upper half 
    @ movt moves any 16 bits into lower half without modyfying upper half https://stackoverflow.com/questions/10261300/invalid-constant-after-fixup
    movw r2, #0xbeef 
    movt r2, #0xdead 
    mov r3, #4
    push {r2, r3}
    @ LDR
    @ Load Register (immediate) calculates an address from a base register value and an immediate offset, loads a word
    @ from memory, and writes it to a register. It can use offset, post-indexed, or pre-indexed addressing
    @ LDR<c> <Rt>, [<Rn>{,#<imm5>}]
    ldr r4, [SP, #4]    @ Loads r3 = 4 into r4
    ldr r4, [SP]        @ loads r2 = 0xdeadbeef into r4
    
    pop {r4-r12}
    bx lr

.global swap
.thumb_func
.type swap, %function
.align
swap:
	push {r4-r11}
	ldr r2, [r0]
	ldr r3, [r1]
	str r3, [r0]
	str r2, [r1]
	pop {r4-r11}
	
	bx lr

.global foo
.thumb_func
.type foo, %function
.align
foo:
    LDR R1,=0x00000100 @Assembler creates a constant in flash memory with =0x0...
	LDR R0,=0x00000000
	STR R0,[R1]
	
	LDR R0,=0x1234BCDE


.global Mult64x64
.thumb_func
.type Mult64x64, %function
.align
Mult64x64:  // R0 = bits A31..A00 (Alo)
            // R1 = bits A63..A32 (Ahi)
            // R2 = bits B31..B00 (Blo)
            // R3 = bits B63..B32 (Bhi)
            muls.N  r1,r1,r2            // R1       = Ahi * Blo
            mla     r1,r0,r3,r1         // R1      += Alo * Bhi  r0 <- r1 + (r0 * r3)
            umull   r0,r2,r0,r2         // R0.R2    = Alo * Blo (64-bit) (MSH in R2, considered Rhi. Little endian)
            adds.N  r1,r1,r2            // R1      += MSHalf of Alo * Blo
            bx lr

.global ComputeDiscriminant
.thumb_func
.type ComputeDiscriminant, %function
.align
ComputeDiscriminant:
    // r0 = a
    // r1 = b
    // r2 = c
	ldr     r3,=4 			// constant
	muls 	r3,r0		// 4 * a
	muls	r1,r1 		// b^2
	
	mls		r0,r0,r2,r1		// b^2 - 4a * c
	
	bx lr

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
    

.global square
.type square, %function
square:
    mul r0, r0, r0
    bx lr
