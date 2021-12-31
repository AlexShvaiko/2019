;file ps.as
.entry LIST
 .extern W
 .define sz=2
  MAIN: mov r3,LIST[sz]
LOOP: jmp W
prn #-5
mov STR[3],STR[5]
sub r1,r4
cmp  #sz,K
bne W
L1: inc L3
  .entry LOOP
 bne LOOP
END: stop
.define len=4
STR: .string "abcdef"
LIST: .data 6,-9,len
K: .data 22
.extern L3


