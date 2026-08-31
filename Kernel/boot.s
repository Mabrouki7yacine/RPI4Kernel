.section .text
.global start

start:
    // check which core is running
    mrs x0, MPIDR_EL1
    and x0, x0, #3 // cuz we have 4 cores 0b11
    cmp x0, #0
    beq Kernel_Entry

End :
    b End

Kernel_Entry :
    mov sp, #0x80000
    bl kernel_main
    b End