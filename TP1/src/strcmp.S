#include <mips/regdef.h>

	.data
	.text
	.align 2
	.globl strcmp
	.ent strcmp
strcmp:
	.frame $fp, 32, ra  # Reservar 32 bytes desde return address?
	.set noreorder # ni 
	.cpload t9	   # idea 
	.set reorder   # si van
	subu sp, sp, 32
	.cprestore 20
	sw ra, 28(sp)
	sw $fp, 24(sp)
	sw gp, 20(sp)
	addu $fp, sp, 32

	sw a0, 16(sp) 		# Array 1
	sw a1, 12(sp) 		# Array 2

	ld t0, 16(sp) 		# arr1
	ld t1, 12(sp) 		# arr2

	beqz t0, errorExit
	beqz t1, errorExit
	
	sw zero, 8(sp)
	ld t2, 8(sp)  		# i = 0
	
loop:
	addu t0, t0, t3  # arr1 = arr1 + i	
	addu t1, t1, t3  # arr2 = arr2 + i	
	
 	la t4, 0(t0) 		# t4 = address arr1+i
	la t5, 0(t1) 		# t4 = address arr2+i
	
	srl t4, t4, 24		# conservo solo el primer byte
	srl t5, t5, 24		# conservo solo el primer byte
	
	beqz t4, break 		# if t4 == null => el byte es null
	beqz t5, break 		# if t4 == null => el byte es null

	lw t4, 0(t0) #ERROR ERROR ERROR		# t4 = arr1[i]
	srl t4, t4, 24		# solo el primer caracter leido
	lw t5, 0(t1) 		# t5 = arr2[i]
	srl t5, t5, 24		# solo el primer caracter leido

	bgt t4, t5, greater
	blt t4, t5, lower
	addiu t2, t2, 1 	# i = i++
	b loop	

break:	
	beq t4, t5, equals	# both null	
	beqz t4, lower		# arr1+4i == null, arr2+4i != null
	beqz t5, greater	# arr1+4i != null, arr2+4i == null	
	b errorExit		# misplaced breaki

greater: 
	addiu v0, zero, 1
	b return

lower:
	addiu v0, zero, -1	# ni idea si existe el "-1" como tal
	b return 

equals:
	addiu v0, zero, 0 
	b return

errorExit:
	addiu v0, zero, -2	
	
return:
	move sp, $fp
	lw ra, 28(sp)
	lw $fp, 24(sp)
	lw gp, 20(sp)
	addu sp, sp, 32
    
	jr ra		
	
	.end strcmp
