# Fibonacci Recursive function.
# Answer in x10 register.
# fib(10) == 55;
main:                          # initial value
        addi  x10, x0, 10     # n = 10
        addi  x8, x0, 1            # for comparison with n (n <= 1)
        jal   ra, fib          # call fib(10)

        j     exit             # go to exit

fib:
        ble   x10, x8, L1       # if(n <= 1)
        addi  sp, sp, -12      # push the stack
        sw    ra, 8(sp)        # store return address
        sw    x10, 4(sp)        # store argument n
        addi  x10, x10, -1       # argument = n - 1
        jal   ra, fib          # call fib(n - 1)
        sw    x10, 0(sp)        # store return value of fib(n - 1)
        lw    x10, 4(sp)        # load argument n
        addi  x10, x10, -2       # argument = n - 2
        jal   ra, fib          # call fib(n - 2)
        lw    x5, 0(sp)        # load return value of fib(n - 1)
        add   x10, x10, x5       # fib(n - 1) + fib(n - 2)
        lw    ra, 8(sp)        # load return address
        addi  sp, sp, 12       # pop the stack
        ret                    # return
L1:
        ret                    # return

exit:
        ecall                  # exit