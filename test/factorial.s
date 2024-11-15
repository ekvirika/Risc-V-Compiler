# Simple Factorial Function to calculate fact(n).
# Answer in x10 register.
addi x10, x0 5 # adjust n = 5;
addi sp, sp, -4
sw x10, 0(sp)
call fact
addi sp, sp, 4
mv x10, x20
ecall

fact:
    lw x10, 0(sp)       # Load the value from the stack
    bne x10, x0, abovezero  # Check if the value is above zero
    addi x20, x0, 1     # If x10 == 0, return 1
    ret                 # Return from the function

abovezero:
    addi x10, x10, -1   # Decrement x10
    addi sp, sp, -8     # Adjust the stack pointer to make space for the next function call
    sw x10, 0(sp)       # Store the decremented value of x10 on the stack
    sw ra, 4(sp)        # Store the return address (ra) on the stack
    call fact           # Recursive call to fact function
    lw ra, 4(sp)        # Restore the return address
    addi sp, sp, 8      # Restore the stack pointer
    lw x10, 0(sp)       # Load the value of x10 from the stack
    mul x20, x20, x10   # Multiply the accumulated result (x20) by the current value of x10
    ret                 # Return from the function
