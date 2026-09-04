.global delay
.global load_word
.global store_word
; .global memcpy

delay : 
    subs x0, x0, #1
    bne delay
    ret

load_word :
    ldr w0, [x0] // value = load_word(addr)
    ret

store_word :
    str w1, [x0] // store(addr, value)
    ret

; bytes_aligned :


; memcpy :
;     // x0 is dest, x1 is src, x2 is count
;     orr x3, x1, x2
;     and x3, x3, #7
;     cmp x3, #0
;     beq bytes_aligned
    
