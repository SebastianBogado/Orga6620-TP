#include <mips/regdef.h>
#ifndef fp
#define fp $fp
#endif

#define TSF		56
#define D_SRA	((TSF) - 4)
#define D_RA	(D_SRA)
#define D_FP	((D_SRA) - 4)
#define D_GP	((D_SRA) - 8)
#define D_S6	((D_SRA) - 12)
#define D_S5	((D_SRA) - 16)
#define D_S4	((D_SRA) - 20)
#define D_S3	((D_SRA) - 24)
#define D_S2	((D_SRA) - 28)
#define D_S1	((D_SRA) - 32)
#define D_S0	((D_SRA) - 36)
#define D_ARG0	(TSF)
#define D_ARG1	((TSF) + 4)
#define D_ARG2	((TSF) + 8)

	.text
	.align 2
	.globl stoogesort
	.ent stoogesort 
	.extern strcmp

stoogesort:
	.frame fp, TSF, ra
	.set noreorder
	.cpload t9
	.set reorder

	subu sp, sp, TSF
	.cprestore D_S6
	sw ra, D_RA(sp)
	sw fp, D_FP(sp)
	sw gp, D_GP(sp)
	move fp, sp
	sw s0, D_S0(sp)
	sw s1, D_S1(sp)
	sw s2, D_S2(sp)
	sw s3, D_S3(sp)
	sw s4, D_S4(sp)
	sw s5, D_S5(sp)
	sw s6, D_S6(sp)
	
	sw a0, D_ARG0(sp) 		# array address
	sw a1, D_ARG1(sp)  		# begin position
	sw a2, D_ARG2(sp) 		# end position
	
	move s0, a0				# s0 = array
	move s1, a1				# s1 = begin
	move s2, a2				# s2 = end
	
	ble t2, t1, return		# End <= Begin
	
	sll t0, s1, 2			# t0 = begin x 4
	sub t1, s2, 1			# t1 = end - 1
	sll t1, t1, 2 			# t1 = (end - 1) x 4
	addu s3, s0, t0			# s3 = &array[begin]
	addu s4, s0, t1			# s4 = &array[end - 1]
	lw s5, 0(s3)			# s5 = array[begin]
	lw s6, 0(s4)			# s6 = array[end - 1]
	
	move a0, s5				# a0 = array[begin]
	move a1, s6				# a1 = array[end - 1]
	jal strcmp
	li t0, 1
	blt v0, t0, no_swap		# no hay intercambio si strcmp retornó menor a 1
	sw s3, 0(s5)				# array[begin] = array[end - 1]
	sw s4, 0(s6)				# array[end - 1] = array[begin]
	
no_swap:	
	subu t0, s2, s1			# t0 = end - begin = size 
	li t1, 3
	blt t0, t1, return		# if size < 3, return
	div t2, t0, t1			# t2 = size/3
	sub s3, s2, t2			# s3 = end - t2 = end - n/3
	
	move a0, s0				# a0 = array
	move a1, s1				# a1 = begin
	move a2, s3				# a2 = end - n/3
	jal stoogesort			# stoogesort(array, begin, end - tercio)
	
	move a0, s0				# a0 = array
	addu a1, s1, t2			# a1 = begin + n/3
	move a2, s2				# a2 = end
	jal stoogesort			# stoogesort(array, begin + tercio, end)
	
	move a0, s0				# a0 = array
	move a1, s1				# a1 = begin
	move a2, s3				# a2 = end - n/3
	jal stoogesort			# stoogesort(array, begin, end - tercio)
	
return:
	lw ra, D_RA(sp)
	lw fp, D_FP(sp)
	lw gp, D_GP(sp)
	move sp, fp
	lw s0, D_S0(sp)
	lw s1, D_S1(sp)
	lw s2, D_S2(sp)
	lw s3, D_S3(sp)
	lw s4, D_S4(sp)
	lw s5, D_S5(sp)
	lw s6, D_S6(sp)
	addiu sp, sp, TSF
	
	jr ra
	.end stoogesort
	
	
	











