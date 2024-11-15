# Simple array sum program. 
# Array = [1 2 3 4 5 ]; size = 5
# At the end x10 register == 15.
main: 
    addi x10, x0, 1
    addi x11, x0, 2
    addi x12, x0, 3
    addi x13, x0, 4
    addi x14, x0, 5
    addi x15, x0, 5 # size
    addi sp sp -20
    sw x10, 0(sp)
    sw x12, 8(sp)
    sw x11, 4(sp)
    sw x13, 12(sp)
    sw x14, 16(sp) 
    
    sw x15, 20(sp)
    lw x16, 0(sp)
    jal x1 arraysum
    ecall
arraysum:
    addi  x10, x0, 0    
    addi  x11, x0, 0  
    add   x12 x0 sp     
    lw    x13 20(sp)   
For: 
    bge   x11, x13, break    
    slli  x14, x11, 2      
    add   x14, x14, x12     
    lw    x14, 0(x14)      
    add   x10, x10, x14     
    addi  x11, x11, 1     
    j     For            
break:
    addi sp sp 20
    ret  
