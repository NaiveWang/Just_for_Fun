@@ gen_asm.s :
@@ Generated ASM (-O2 -mthumb -mthumb-interwork -S)
@@ Applied a little extra formatting and comments for easier reading.
@@ Standard comments use by @; my comments use @@

@@ Oh, and DON'T PANIC! :)

    .code   16
    .file   "gen_asm.c"     @@ - Source filename (not required)
    .text                   @@ - Code section (text -> ROM)

@@ <function block>
    .align  2               @@ - 2^n alignment (n=2)
    .global PlotPixel3      @@ - Symbol name for function
    .code   16              @@ - 16bit THUMB code (BOTH are required!)
    .thumb_func             @@ /
    .type   PlotPixel3, %function   @@ - symbol type (not req)
@@ Declaration : void PlotPixel3(int x, int y, u16 clr)
@@ Uses r0-r3 for params 0-3, and stack for param 4 and over
@@   r0: x
@@   r1: y
@@   r2: clr
PlotPixel3:
    lsl     r3, r1, #4      @@ \
    sub     r3, r3, r1      @@ - (y*16-1)*16 = y*240
    lsl     r3, r3, #4      @@ /
    add     r3, r3, r0      @@ - (y*240+x)
    mov     r1, #192        @@ - 192<<19 = 0600:0000
    lsl     r1, r1, #19     @@ /
    lsl     r3, r3, #1      @@ - *2 for halfword, not byte, offset
    add     r3, r3, r1
    @ lr needed for prologue
    strh    r2, [r3]        @@ store halfword at vid_mem[y*240+x]
    @ sp needed for prologue
    bx  lr
    .size   PlotPixel3, .-PlotPixel3    @@ - symbol size (not req)
@@ </ function block>

    .align  2
    .global main
    .global _exit
    .code   16
    .thumb_func
    .type   main, %function
    .type   _exit, %function
main:
    push    {r4, lr}            @@ Save regs r4, lr
    @ --- using function ---    @@ Comment from ASM_CMT, indicating
    .code   16                  @@   the PlotPixel3() loop
    mov     r4, #0              @@ r4: ii=0
.L4:
        mov     r2, #248        @@ - r2: clr= 248*4= 0x03E0= CLR_LIME
        lsl     r2, r2, #2      @@ /
        mov     r0, r4          @@ r0: x= ii
        mov     r1, #16         @@ r1: y= 16
        add     r4, r4, #1      @@ ii++
        bl      PlotPixel3      @@ Call PlotPixel3 (params in r0,r1,r2)
        cmp     r4, #240        @@ - loop while(ii<240)
        bne .L4                 @@ /
    @ --- using inline ---      @@ Comment from ASM_CMT, indicating
    .code   16                  @@   the m3_plot() loop
    ldr     r3, .L14            @@ r3: starting/current address (vid_mem[12*240])
    ldr     r2, .L14+4          @@ r2: terminating address (vid_mem[13*240])
    mov     r1, #31             @@ r1: clr (CLR_RED)
.L6:
        strh    r1, [r3]        @@ - *r3++ = clr
        add     r3, r3, #2      @@ /
        cmp     r3, r2          @@ - loop while(r3<r2)
        bne .L6                 @@ /
.L12:
    b   .L12
.L15:
    .align  2
.L14:
    .word   100669056       @@ 0600:1680 =&vid_mem[12*240]
    .word   100669536       @@ 0600:1886 =&vid_mem[13*240]
    .size   main, .-main

    .ident  "GCC: (GNU) 4.1.0 (devkitARM release 18)"
_exit:
  push    {r4, lr}            @@ Save regs r4, lr
  @ --- using function ---    @@ Comment from ASM_CMT, indicating
  .code   16                  @@   the PlotPixel3() loop
  mov     r4, #0              @@ r4: ii=0
