# store String "Hello, world!" and count its length.
# Answer in x10 register, should be 13

# Manually write each ASCII value to memory using addi and sb instructions
addi sp sp -13
# 'H'
mv x11 sp
addi x5, x0, 72
sb x5, 0(sp)
addi sp, sp, 1

# 'e'
addi x5, x0, 101
sb x5, 0(sp)
addi sp, sp, 1

# 'l'
addi x5, x0, 108
sb x5, 0(sp)
addi sp, sp, 1

# 'l'
addi x5, x0, 108
sb x5, 0(sp)
addi sp, sp, 1

# 'o'
addi x5, x0, 111
sb x5, 0(sp)
addi sp, sp, 1

# ','
addi x5, x0, 44
sb x5, 0(sp)
addi sp, sp, 1

# ' '
addi x5, x0, 32
sb x5, 0(sp)
addi sp, sp, 1

# 'w'
addi x5, x0, 119
sb x5, 0(sp)
addi sp, sp, 1

# 'o'
addi x5, x0, 111
sb x5, 0(sp)
addi sp, sp, 1

# 'r'
addi x5, x0, 114
sb x5, 0(sp)
addi sp, sp, 1

# 'l'
addi x5, x0, 108
sb x5, 0(sp)
addi sp, sp, 1

# 'd'
addi x5, x0, 100
sb x5, 0(sp)
addi sp, sp, 1

# '!'
addi x5, x0, 33
sb x5, 0(sp)
addi sp, sp, 1

main:
    addi x12, x0, 0   # x12 is our counter set to 0

loop:
    lb x13, 0(x11)     # Load byte from string address into x13
    beq x13, x0, end  # If byte is 0, end of string
    addi x12, x12, 1   # Increment counter
    addi x11, x11, 1   # Move to the next character
    jal x0, loop     # Jump back to loop

end:
    mv x10 x12
    ret
