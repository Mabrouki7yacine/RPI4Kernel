# BCM2711 SoC UART

The BCM2711 has **6 UARTs**:

* **1 Mini UART:** UART1
* **5 PL011 UARTs:** UART0, UART2, UART3, UART4, UART5

## UART Features

The PL011 UART provides:

* Separate **32 × 8-bit transmit FIFO** and **32 × 12-bit receive FIFO**.
* Programmable baud-rate generator.
* Standard asynchronous communication bits:

  * Start bit
  * Stop bit
  * Parity bit
* These bits are automatically added during transmission and removed during reception.
* False start-bit detection.
* Line break generation and detection.
* Modem control support:

  * CTS
  * RTS
* DCD, DSR, DTR and RI are not supported.
* Programmable hardware flow control.
* Fully programmable serial-interface characteristics:

  * 5, 6, 7 or 8 data bits.
  * Even, odd, stick or no parity.
  * 1 or 2 stop bits.
  * Baud rate up to `UARTCLK / 16`.

---

# UART0

UART0 bus address:

```text
0x7E201000
```

## Memory-Mapped Registers

| Address Offset | Register | Description                           | Size |
| -------------: | -------- | ------------------------------------- | ---: |
|         `0x00` | DR       | Data Register                         |   32 |
|         `0x04` | RSRECR   | Receive Status / Error Clear Register |   32 |
|         `0x18` | FR       | Flag Register                         |   32 |
|         `0x20` | ILPR     | Not used                              |   32 |
|         `0x24` | IBRD     | Integer Baud Rate Divisor             |   32 |
|         `0x28` | FBRD     | Fractional Baud Rate Divisor          |   32 |
|         `0x2C` | LCRH     | Line Control Register                 |   32 |
|         `0x30` | CR       | Control Register                      |   32 |
|         `0x34` | IFLS     | Interrupt FIFO Level Select           |   32 |
|         `0x38` | IMSC     | Interrupt Mask Set/Clear              |   32 |
|         `0x3C` | RIS      | Raw Interrupt Status                  |   32 |
|         `0x40` | MIS      | Masked Interrupt Status               |   32 |
|         `0x44` | ICR      | Interrupt Clear Register              |   32 |
|         `0x48` | DMACR    | DMA Control Register                  |   32 |
|         `0x80` | ITCR     | Test Control Register                 |   32 |
|         `0x84` | ITIP     | Integration Test Input Register       |   32 |
|         `0x88` | ITOP     | Integration Test Output Register      |   32 |
|         `0x8C` | TDR      | Test Data Register                    |   32 |

---

# DR Register

The `UART_DR` register is used to **send and receive data**.

## Transmission

If FIFOs are enabled:

* Data written to `DR` is pushed into the **transmit FIFO**.

If FIFOs are disabled:

* Data is stored in the **transmit holding register**.

Writing data to `DR` starts transmission.

The UART automatically adds:

```text
Start bit → Data → Parity (if enabled) → Stop bit
```

## Reception

If FIFOs are enabled:

* The received 8-bit data and 4 error/status bits are pushed into the **12-bit receive FIFO**.

If FIFOs are disabled:

* They are stored in the receive holding register.

## DR Bits

### Bit 11 — OE: Overrun Error

```text
0 = No overrun
1 = Data arrived while the receive FIFO was already full
```

---

### Bit 10 — BE: Break Error

```text
1 = Break condition detected
```

A break happens when the RX input stays **LOW longer than a complete frame transmission time**:

```text
Start + Data + Parity + Stop
```

---

### Bit 9 — PE: Parity Error

```text
0 = Correct parity
1 = Wrong parity
```

When FIFO mode is enabled, the error belongs to the character at the top of the FIFO.

---

### Bit 8 — FE: Framing Error

```text
0 = Correct frame
1 = Invalid stop bit
```

When FIFO mode is enabled, the error belongs to the character at the top of the FIFO.

---

### Bits 7–0 — DATA

```text
Read  → received character
Write → character to transmit
```

---

# LCRH Register

`UART_LCRH` is the **Line Control Register**.

It configures the UART frame format.

## Bit 7 — SPS: Stick Parity Select

```text
0 = Stick parity disabled
1 = Stick parity enabled
```

Stick parity forces the parity bit to a fixed value.

We do not need it for our basic UART configuration.

---

## Bits 6–5 — WLEN: Word Length

```text
00 = 5 bits
01 = 6 bits
10 = 7 bits
11 = 8 bits
```

For an 8-bit UART:

```text
WLEN = 0b11
```

---

## Bit 4 — FEN: FIFO Enable

```text
0 = FIFOs disabled
1 = FIFOs enabled
```

---

## Bit 3 — STP2: Two Stop Bits

```text
0 = 1 stop bit
1 = 2 stop bits
```

---

## Bit 2 — EPS: Even Parity Select

Used when parity is enabled.

```text
0 = Odd parity
1 = Even parity
```

---

## Bit 1 — PEN: Parity Enable

```text
0 = Parity disabled
1 = Parity generation and checking enabled
```

---

## Bit 0 — BRK: Send Break

```text
0 = Normal operation
1 = TXD is forced LOW after the current transmission
```

---

# CR Register

`UART_CR` is the **UART Control Register**.

To transmit:

```text
UARTEN = 1
TXE    = 1
```

To receive:

```text
UARTEN = 1
RXE    = 1
```

## Recommended Reconfiguration Sequence

1. Disable the UART.
2. Wait for the current transmission/reception to finish.
3. Flush the transmit FIFO by setting `FEN = 0` in `UART_LCRH`.
4. Reprogram the UART configuration.
5. Enable the UART again.

## CR Bits

### Bit 15 — CTSEN

CTS hardware flow control:

```text
0 = Disabled
1 = Enabled
```

---

### Bit 14 — RTSEN

RTS hardware flow control:

```text
0 = Disabled
1 = Enabled
```

---

### Bits 13–12

Do not care.

Write as:

```text
0
```

---

### Bit 11 — RTS

Request To Send.

The physical signal is active LOW:

```text
RTS = 1 → nUARTRTS = LOW
RTS = 0 → nUARTRTS = HIGH
```

---

### Bit 10 — DTR

Do not care.

Write as:

```text
0
```

---

### Bit 9 — RXE

Receiver enable:

```text
0 = Disabled
1 = Enabled
```

---

### Bit 8 — TXE

Transmitter enable:

```text
0 = Disabled
1 = Enabled
```

---

### Bit 7 — LBE

Loopback enable:

```text
0 = Disabled
1 = Enabled
```

---

### Bits 6–1

Do not care.

Write as:

```text
0
```

---

### Bit 0 — UARTEN

UART enable:

```text
0 = UART disabled
1 = UART enabled
```

---

# FR Register

`UART_FR` is the **Flag Register**.

It gives information about the current state of the UART.

## Bit 8 — RI

Do not care.

Write as:

```text
0
```

---

## Bit 7 — TXFE: Transmit FIFO Empty

If FIFO is disabled:

```text
1 = Transmit holding register is empty
```

If FIFO is enabled:

```text
1 = Transmit FIFO is empty
```

---

## Bit 6 — RXFF: Receive FIFO Full

If FIFO is disabled:

```text
1 = Receive holding register is full
```

If FIFO is enabled:

```text
1 = Receive FIFO is full
```

---

## Bit 5 — TXFF: Transmit FIFO Full

If FIFO is disabled:

```text
1 = Transmit holding register is full
```

If FIFO is enabled:

```text
1 = Transmit FIFO is full
```

This bit is useful before sending data:

```text
TXFF = 1 → wait
TXFF = 0 → we can write to DR
```

---

## Bit 4 — RXFE: Receive FIFO Empty

If FIFO is disabled:

```text
1 = Receive holding register is empty
```

If FIFO is enabled:

```text
1 = Receive FIFO is empty
```

This bit is useful when receiving data:

```text
RXFE = 1 → nothing received
RXFE = 0 → data available in DR
```

---

## Bit 3 — BUSY

```text
0 = UART is idle
1 = UART is busy transmitting
```

---

## Bits 2–1

Do not care.

---

## Bit 0 — CTS

Clear To Send.

It represents the inverse of the physical `nUARTCTS` signal.

---

# IBRD Register

`UART_IBRD` contains the **integer part of the baud-rate divisor**.

```text
Bits 15–0 = Integer baud-rate divisor
```

---

# FBRD Register

`UART_FBRD` contains the **fractional part of the baud-rate divisor**.

```text
Bits 5–0 = Fractional baud-rate divisor
```

The fractional divisor uses increments of:

```text
1 / 64
```

---

# Baud Rate Configuration

The baud-rate divisor is:

```text
BAUDDIV = FUARTCLK / (16 × Baud rate)
```

For:

```text
FUARTCLK = 48 MHz
Baud rate = 115200 Bd
```

We get:

```text
BAUDDIV = (48 × 1000 × 1000) / (16 × 115200)

BAUDDIV = 26.041666...
```

The integer part is:

```text
IBRD = 26
```

The fractional part is:

```text
0.041666...
```

`FBRD` uses 1/64 steps:

```text
FBRD = round(0.041666 × 64)

FBRD = round(2.6666)

FBRD = 3
```

Therefore:

```c
IBRD = 26;
FBRD = 3;
```

For a **48 MHz UART clock and 115200 Bd**:

```text
IBRD = 26
FBRD = 3
```
