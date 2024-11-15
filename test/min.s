# This program decides which is the 
# minimum between x10 and x11

addi x10, x0 30
addi  x11, x0 -15
addi sp, sp, -8
sw x10, 0(sp)
sw x11, 4(sp)
jal ra min
addi sp, sp, 8
addi   x10, x0, 1
mv   x10, x20
ecall

min:
lw x10, 0(sp)
lw x11, 4(sp)
bge x10, x11, else
lw x20, 0(sp)
ret
else:
lw x20, 4(sp)
ret

#   in the end there should be x10 == 30;