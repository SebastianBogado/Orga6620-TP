#include <mips/regdef.h>
#ifndef fp
#define fp $fp
#endif

#define TSF		8
#define D_SRA	((TSF) - 4)
#define D_FP	(D_SRA)
#define D_GP	((D_SRA - 4)
#define D_ARG0	(TSF)
#define D_ARG1	((TSF) + 4)

	.text
	.align 2
	.globl strcmp
	.ent strcmp
strcmp:
	.frame fp, TSF, ra  # Reservar TSF bytes desde return address
	.set noreorder  
	.cpload t9 
	.set reorder   
	subu sp, sp, TSF
	.cprestore 20
	sw fp, D_FP(sp)
	sw gp, D_GP(sp)
	move fp, sp

	sw a0, D_ARG0(sp) 	# Array 1
	sw a1, D_ARG1(sp) 	# Array 2

	move t0, a0			# t0 = arg0
	move t1, a1			# t1 = arg1

	beqz t0, errorExit
	beqz t1, errorExit

	move t2, zero	 	# t2 = i

loop:
	sll t3, t2, 2		# t3 = 4*i -> avanza de a cuatro bytes para ahorrar accesos a memoria
	addu t0, t0, t3  	# arr1 = arr1 + i	
	addu t1, t1, t3 	# arr2 = arr2 + i	
	
 	la t4, 0(t0) 		# t4 = address arr1+i
	la t5, 0(t1) 		# t5 = address arr2+i
	
	beqz t4, break 		# if t4 == null => el byte es null
	beqz t5, break 		# if t5 == null => el byte es null	

	lw t4, 0(t0) 		# t4 = arr1[i]
	lw t5, 0(t1) 		# t5 = arr2[i]
	
	srl t6, t4, 24		# solo el primer caracter leido
	srl t7, t5, 24		# solo el primer caracter leido

	bgt t4, t5, greater
	blt t4, t5, lower
	
	srl t6, t4, 16
	srl t7, t5, 16

	bgt t4, t5, greater
	blt t4, t5, lower

	srl t6, t4, 8		# solo el primer caracter leido
	srl t7, t5, 8		# solo el primer caracter leido

	bgt t4, t5, greater
	blt t4, t5, lower
	
	addiu t2, t2, 1 	# i = i++
	b loop	

break:	
	beq t4, t5, equals	# both null	
	beqz t4, lower		# arr1+4i == null, arr2+4i != null
	beqz t5, greater	# arr1+4i != null, arr2+4i == null	
	b errorExit			# misplaced breaki

greater: 
	addiu v0, zero, 1
	b return

lower:
	addi v0, zero, -1	# ni idea si existe el "-1" como tal
	b return 

equals:
	addiu v0, zero, 0 
	b return

errorExit:
	addiu v0, zero, -2	
	
return:
	lw fp, D_FP(sp)
	lw gp, D_GP(sp)
	addu sp, sp, TSF
	move sp, fp    

	jr ra		
	
	.end strcmp
