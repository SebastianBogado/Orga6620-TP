#include <mips/regdef.h>
#ifndef fp
#define fp $fp
#endif

#define TSF		8
#define D_SRA	((TSF) - 4)
#define D_FP	(D_SRA)
#define D_GP	((D_SRA) - 4)
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

	move t0, a0		# t0 = arg0
	move t1, a1		# t1 = arg1

	beqz t0, errorExit
	beqz t1, errorExit

loop:
	lbu t4, 0(t0)
	lbu t5, 0(t1)
	
	beqz t4, break 		# if t4 == null => byte 'i' is null (\0)
	beqz t5, break 		# if t5 == null => byte 'i' is null (\0)	
	
	bgt t4, t5, greater	# arr1[i] > arr2[i]
	blt t4, t5, lower	# arr1[i] < arr2[i]
	
	addiu t0, t0, 1  	# arr1 = arr1 + 1	
	addiu t1, t1, 1 	# arr2 = arr2 + 1	
	
	b loop	

break:	
	beq t4, t5, equals	# both null	
	beqz t4, lower		# arr1[i] == null, arr2[i] != null
	beqz t5, greater	#  arr1[i] != null, arr2[i] == null	
	b errorExit		# misplaced break

greater: 
	addiu v0, zero, 1
	b return

lower:
	addiu v0, zero, -1
	b return 

equals:
	addiu v0, zero, 0 
	b return

errorExit:
	addiu v0, zero, -2	
	
return:
	lw fp, D_FP(sp)
	lw gp, D_GP(sp)
	lw a0, D_ARG0(sp)
	lw a1, D_ARG1(sp)
	addu sp, sp, TSF
	move sp, fp    

	jr ra		
	
	.end strcmp
