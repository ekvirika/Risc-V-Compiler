# Binary search (answer in x10, should be 4)
# bin_search(int[] arr, int l, int r, int x)
# int[] arr: memory address of 'arr'. Assumes each element is size 4.
# l: left boundary.
# r: right boundary.
# x: element being searched for.
# Requires: r >= l. Returns -1 otherwise. 'arr' is in sequential order.
#           l >= 0.
#           r < length(arr).
# we search x = 40;
main:
    addi sp, sp, -24
    addi x10, x0, 0 # hardcode the memory address to begin at 0.
    addi x11, x0, 0 # hardcode l = 0.
    addi x12, x0, 6 # hardcore r = 6.
    addi x13, x0, 4 # hardcode x = 40.
# Store array values in contiguous memory:
# {2, 3, 4, 10, 40, 50, 1000}
    addi x5, x0, 2
    sw x5, 0(x10) 
    addi x5, x0, 3
    sw x5, 4(x10)
    addi x5, x0, 4
    sw x5, 8(x10)
    addi x5, x0, 10
    sw x5, 12(x10)
    addi x5, x0, 40
    sw x5, 16(x10)
    addi x5, x0, 50
    sw x5, 20(x10)
    addi x5, x0, 1000
    sw x5, 24(x10)
    addi x11 x0 1
    jal x1, BIN_SEARCH
    jal x1, EXIT

BIN_SEARCH:
    addi sp, sp, -4
    sw x1, 0(sp)
    bne x5, x13, NOT_FOUND # if (arr[mid] == x) return mid.
    add x10, x0, x7
    jalr x0, x1, 0

NOT_FOUND:
    blt x12, x11, INCORRECT_BOUNDS # if (r < l) return -1.

    sub x5, x12, x11 # store r-l.
    srai x6, x5, 1 # store (r-l)/2.
    add x7, x6, x11 # store l + (r-l)/2.

    # Get the 'mid' element in 'arr'.
    slli x28, x7, 2 # mid * sizeof(int)
    add x28, x28, x10 # pointer to arr[mid].
    lw x5, 0(x28)   # get value at arr[mid].

    bne x5, x13, NOT_EQ # if (arr[mid] == x) return mid.
    add x10, x0, x7
    jalr x0, ra, 0

NOT_EQ:
    bge x13, x5, GREATER_THAN # if (x > arr[mid]) bin_search(arr, mid+1, r, x).
    addi x12, x7, -1 # r = mid - 1 # bin_search(arr, l, mid-1, x);
    jal ra, BIN_SEARCH

GREATER_THAN:
    addi x11, x7, 1 # l = mid + 1
    jal ra, BIN_SEARCH

RET:
    lw ra, 0(sp)
    addi sp, sp, 4
    jalr x0, ra, 0

INCORRECT_BOUNDS:
    addi x10, x0, -1
    lw ra, 0(sp)
    addi sp, sp, 4
    jalr x0, ra, 0

EXIT: