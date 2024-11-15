# RISC-V Emulator

Basic RISC-V emulator written in C language. On the UI (terminal), after every instruction line, the corresponding instruction and  

## Supported Register names
   - x0 - x31
   - zero
   - sp
   - ra

## Supported Instructions
The emulator currently supports the following RISC-V instructions:

1. **Arithmetic Instructions**:
   - ADD
   - SUB
   - MUL
   - DIV

2. **Load and Store Instructions**:
   - LW (Load Word)
   - LH (Load Half Byte)
   - LB (Load Byte)
   - SW (Store Word)
   - SH (Store Half Byte)
   - SB (Store Byte)

3. **Control Transfer Instructions**:
   - BEQ    (Branch if Equal)
   - BNE    (Branch if Not Equal)
   - BGT    (Branch if Greater Than)
   - BGE    (Branch if Greater or Equal)
   - BLE    (Branch if Less or Equal)
   - BLT    (Branch if Less Than)
   - JAL    (Jump and Link)
   - JALR   (Jump and Link Register)
   - J      (Jump)
   - JR     (Jump Register)

4. **Immediate Instructions**:
   - ADDI (Add Immediate)
   - SLLI (Shift Left Logical Immediate)
   - SLAI (Shift Left Arithmetic Immediate)
   - SRLI (Shift Right Logical Immediate)
   - SRAI (Shift Right Arithmetic Immediate)

5. **Pseudo Instructions**:
   - J      (Jump)
   - JR     (Jump Register)
   - MV     (Move Register)
   - CALL   (Call Function)

## Getting Started

To run the RISC-V emulator, follow these steps:

1. Clone the repository:
```
https://github.com/freeuni-paradigms/bonus-ekvir21.git
```

2. Open this repository in your editor

3. Compile Files with this command:
```
gcc main.c src/FileParser.c src/Cpu.c src/Bus.c src/Memory.c src/LabelTable.c 
```

4. Run:
```
./a.out <fileName>.s
```


## Testing
Test files are given in the test Folder. 
