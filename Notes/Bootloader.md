# Kernel Memory Layout

After the Raspberry Pi boot process succeeds, the firmware loads `kernel8.img` into RAM at:

```text
0x80000
```

So the kernel should also be linked to start at:

```ld
. = 0x80000;
```

Memory layout:

text
0x80000
   |
   v
| Section     | Content                       |
| ----------- | ----------------------------- |
| `.text`     | Assembly + C code             |
| `.rodata`   | Constants / strings           |
| `ALIGN(16)` | Padding for 16-byte alignment |
| `.data`     | Initialized variables         |
| `.bss`      | Zero-initialized variables    |


* `.text` → executable code
* `.rodata` → read-only data
* `.data` → initialized variables
* `.bss` → zero-initialized variables
