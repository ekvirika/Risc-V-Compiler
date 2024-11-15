# test along real risc-v emulator
_start:
    addi x10, x0, 15    # x10 = 15
    slli x12, x10, 1     # x12 = x10 * 2 (left shift)
    srai x13, x12, 2     # x13 = x12 / 4 (right arithmetic shift)

    mul x14, x10, x13     # x14 = x10 * x13
    div x15, x14, x10     # x15 = x14 / x10, should be x13

    # Inspect registers to verify operations
