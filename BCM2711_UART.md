BCM2711 SoC UART :
it has 6 UART (1 mini uart : UART1, 5 uart : UART0, UART2, UART3, UART4,  UART5)
it provides :
• Separate 32x8 transmit and 32x12 receive FIFO memory.
• Programmable baud rate generator.
• Standard asynchronous communication bits (start, stop and parity). These are added after transmission and removed on recv
• False start bit detection.
• Line break generation and detection.
• Support of the modem control functions CTS and RTS. However DCD, DSR, DTR, and RI are not supported.
• Programmable hardware flow control.
• Fully-programmable serial interface characteristics:
    ◦ data can be 5, 6, 7, or 8 bits.
    ◦ even, odd, stick, or no-parity bit generation and detection.
    ◦ 1 or 2 stop bit generation.
    ◦ baud rate generation, up to UARTCLK/16.

UART0: 0x7E20 1000

memory mapped registers :

+--------------------------------------------------------------------+
|Address Offset | Register Name |    Description              | Size |
+--------------------------------------------------------------------+
|      0x00     |DR             |Data Register                | 32   |
|      0x04     |RSRECR         |                             | 32   |
|      0x18     |FR             |Flag register                | 32   |
|      0x20     |ILPR           |not in use                   | 32   |
|      0x24     |IBRD           |Integer Baud rate divisor    | 32   |
|      0x28     |FBRD           |Fractional Baud rate divisor | 32   |
|      0x2C     |LCRH           |Line Control register        | 32   |
|      0x30     |CR             |Control register             | 32   |
|      0x34     |IFLS           |Interrupt FIFO Level Select  | 32   |
|      0x38     |IMSC           |Interrupt Mask Set Clear     | 32   |
|      0x3C     |RIS            |Raw Interrupt Status         | 32   |
|      0x40     |MIS            |Masked Interrupt Status      | 32   |
|      0x44     |ICR            |Interrupt Clear Register     | 32   |
|      0x48     |DMACR          |DMA Control Register         | 32   |
|      0x80     |ITCR           |Test Control register        | 32   |
|      0x84     |ITIP           |Integration test input reg   | 32   |
|      0x88     |ITOP           |Integration test output reg  | 32   |
|      0x8C     |TDR            |Test Data reg                | 32   |
+--------------------------------------------------------------------+
