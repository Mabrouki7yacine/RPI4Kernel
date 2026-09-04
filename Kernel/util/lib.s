.global delay
.global load_word
.global store_word

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