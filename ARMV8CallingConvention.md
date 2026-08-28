Calling convention is a way to let diff piece of codes to communicate between each other in the same manner
wanna pass an arg to a func ? which register to use? in which reg we return? who cleans stack?

passing params to func :fisrt 8 params x0 --> x7, others on the stack
retval passed on x0
Caller saved registers x0 --> x18 : the caller func is responsible for saving reg values on the stack and restore them after it ret
Caller saved registers x19 --> x30 : the called func is responsible for saving reg values on the stack and restore them before it ret
the caller is responsible on stack cleaning