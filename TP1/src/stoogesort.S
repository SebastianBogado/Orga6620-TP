# a0 = array
# a1 = array begin
# a2 = array end

	.data
	#algo algo algo
	.text
	.align 2
	.globl stoogesort
	.ent stoogesort #  <= no se para que es

stoogesort:
	.frame $fp, 32, ra
	.set noreorder #este y los 2 de abajo, no se si van
	.cpload $t9
	.set reorder

        subu $sp, $sp, 32
        sw $ra, 28(sp)
        sw $fp, 24(sp)
        sw $gp, 20(sp)
        addu $fp, $sp, 32
	
	sw $a0, 16(sp) 	# array address
	sw $a1, 12(sp)  # begin position
	sw $a2, 8(sp) 	# end position
	
	ld $t0, 16(sp)  # array in temp
	ld $t1, 12(sp)  # begin in temp
	ld $t2, 8(sp) 	# end in temp
	
	bleu $t2, $t1, exitError # End <= Begin
	
	lw $t3, 




	lw $t3, zero		# t3 = 0
	subu $t3, $t2, $t1 	# t3 = end - begin 
	# HAY QUE SUMAR 1 ????
	li $t4, 3
	divu $t3, $t3, $t4	# t3 = (end-begin)/3
	
	
	











