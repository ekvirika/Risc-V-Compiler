main:
    addi x10, x0, 10  
    jal x1, func        
    addi x11, x1, 5      
func:
    addi x12, x10, 20     
    jr ra       
