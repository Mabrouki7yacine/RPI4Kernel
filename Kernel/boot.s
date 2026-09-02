.section .text
.global start

start:
    // check which core is running
    mrs x0, MPIDR_EL1
    and x0, x0, #3 // cuz we have 4 cores 0b11
    cmp x0, #0
    beq EnterPrivMode

Park_Core :
    wfe
    b Park_Core

EnterPrivMode :
    mrs x0, CurrentEL
    lsr x0, x0, #2 // check current exception level
    and x0, x0, #3 // mask
    cmp x0, #3 // compare with 3 drop to 1
    beq fromEL3toEL1
    cmp x0, #2 // compare with 2 (to make sure we're in OS kernel priviledged mode)
    beq fromEL2toEL1
    cmp x0, #1
    beq AlreadyEL1
    b Park_Core
    
fromEL3toEL1 : 
    mov x1, #0b00101
    orr x1, x1, #0x3C0 // mask exceptions
    msr SPSR_EL3, x1 // use EL1 and its own sp in Aarch64

    adr x1, Kernel_Entry
    msr ELR_EL3, x1 // the return address that ERET will use

    mov x1, #0x0401
    msr SCR_EL3, x1 // Non-secure lower world, AArch64 EL2, don't route IRQ/FIQ to EL3

    mov x1, #0x80000
    msr SP_EL1, x1 // set stack pointer

    mov x1, #0x80000000
    msr HCR_EL2, x1 // set : AArch64

    ISB // Ensure subsequent instructions observe updated system state
    ERET

fromEL2toEL1 : 
    mov x1, #0b00101
    orr x1, x1, #0x3C0 // mask exceptions
    msr SPSR_EL2, x1 // use EL1 and its own sp in Aarch64

    adr x1, Kernel_Entry
    msr ELR_EL2, x1 // the return address that ERET will use

    mov x1, #0x80000
    msr SP_EL1, x1 // set stack pointer

    mov x1, #0x80000000
    msr HCR_EL2, x1 // config EL1 : AArch64

    ISB // Ensure subsequent instructions observe updated system state
    ERET

AlreadyEL1 : 
    mov x1, #0b00101
    orr x1, x1, #0x3C0 // mask exceptions
    msr SPSR_EL1, x1 // use EL1 and its own sp in Aarch64

    mov x1, #0x80000
    msr SP_EL1, x1 // set stack pointer

    mov x1, #1
    msr SPSel , x1 // set stack pointer to use SP_EL1

    ISB // Ensure subsequent instructions observe updated system state
    b Kernel_Entry

Kernel_Entry :
    bl kernel_main
    b Park_Core