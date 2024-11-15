# This test involves more complex branching and a looping construct.
# It calculates the sum of numbers from 1 to n;
# Answer in x10. 
main:
    addi x10, x0, 10 # target number n = 10
    addi x9, x0, 1   # begin with 1
    addi x5, x0, 0   # sum goes here

loop:
    add x5, x5, x9   # sum += current number
    addi x9, x9, 1   # increment current number
    ble x9, x10, loop

    # x5 should now be 55 (for n = 10)
    mv x10 x5
    ret
