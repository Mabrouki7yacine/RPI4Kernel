Execution state : 
the core can execute aarch64 or aarch32 its up to you to select the execution

Execution can move between Exception levels only on taking an exception, or on returning from an exception:
On taking an exception, the Exception level either increases or remains the same. The Exception level cannot decrease on taking an exception.
On returning from an exception, the Exception level either decreases or remains the same. The Exception level cannot increase on returning from an exception.

SCR_EL3, Secure Configuration Register purpose : 
- define security state of EL0, EL1, EL2 possible states are : Secure, Non-Secure, Realm
- Execution state of lewer levels
- EL3 can monitor or restrict certain operations performed by EL2/EL1/EL0
- Whether IRQ, FIQ, SError exceptions, and External abort exceptions are taken to EL3.
this register is only present when EL3 and aarch64 is implemented
For a bare-metal kernel we need :EL1
AArch64
Non-secure
IRQs/FIQs not routed to EL3
Then the important SCR_EL3 bits are:
RW bit [10] = 1   → lower EL uses AArch64
NS bit [0]  = 1   → lower EL is Non-secure
IRQ bit [1] = 0   → don't route IRQ to EL3
FIQ bit [2] = 0   → don't route FIQ to EL3
EA bit [3]  = 0   → don't route SError to EL3

ELR_EL3 stores the return address that ERET will use when returning from EL3.
this register is only present when EL3 and aarch64 is implemented.
address should be Kernel_Entry

SPSR_EL3, Saved Program Status Register (EL3)
Holds the saved process state when an exception is taken to EL3.
ELR_EL3 stores the return address that ERET will use when returning from EL3.
This register is a Special-purpose register.
we should set bit 4 = 0 to make exec state aarch64
bit[3..0] = 0b0101 -> use EL1 and its own sp

HCR_EL2, Hypervisor Configuration Register, EL2
The HCR_EL2 provides configuration control for virtualization, including whether various Non-secure operations are trapped to EL2.
