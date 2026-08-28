after boot process succeeds (from GPU) the kernel is loaded from address 0x80000, so it should be loaded to that exact location.
should be like this :
0x80000
   |
   v
+-------------------------+
| .text                   |
| assembly + C code       |
+-------------------------+
| .rodata                 |
| constants / strings     |
+-------------------------+
| padding for ALIGN(16)   |
+-------------------------+
| .data                   |
| initialized variables   |
+-------------------------+
| .bss                    |
| zero-init variables     |
+-------------------------+