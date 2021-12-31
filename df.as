;file df.as
.define sz=2
MAIN: mov r3,STR[3]
LOOP: jmp L1
prn #-5
mov STR[5],STR[3]
sub r1,r4,
cmp r3,#sz
L1: inc K
bne, LOOP
END: stop,
.define len=4
STR: .string "absde"
LIST: .data 6,-9,len
K: .data 22


