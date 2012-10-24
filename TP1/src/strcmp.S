# $a0 = first array
# $a1 = second array
	.data
	# blablablabla
	.text
	.align 2
	.globl strcmp
	.ent strcmp # <= no se para que es
strcmp:
	.frame $fp, 32, ra  # Reservar 32 bytes desde return address?
	.set noreorder # ni 
	.cpload $t9	   # idea 
	.set reorder   # si van
	subu $sp, $sp, 32
	sw $ra, 28(sp)
	sw $fp, 24(sp)
	sw $gp, 20(sp)
	addu $fp, $sp, 32
	#guardar alguno mas?

	sw $a0, 16(sp) 		# Array 1
	sw $a1, 12(sp) 		# Array 2

	ld $t0, 16(sp) 		# arr1
	ld $t1, 12(sp) 		# arr2

	beqz $t0, errorExit
	beqz $t1, errorExit
	
	sw zero, 8(sp)
	ld $t2, 8(sp)  		# i = 0
	
loop:
	sll $t3, $t2, 2     # t3 = 4xi
	addu $t0, $t0, $t3  # arr1 = arr1 + 4xi	
	addu $t1, $t1, $t3  # arr2 = arr2 + 4xi	
	
	# if arr1+4i != null
 	la $t4, 0(t0) 		# t4 = address arr1+4i
	la $t5, 0(t1) 		# t4 = address arr2+4i
	beqz $t4, break 	# if t4 == null 
	beqz $t5, break 	# if t4 == null

	# load array content
	lw $t4, 0(t0) 		# t4 = arr1[i]
	lw $t5, 0(t1) 		# t5 = arr2[i]

	# if arr1[i] > arr2[i]
	bgt $t4, $t5, greater
	# if arra1[i] < arr2[i]
	blt $t4, $t5, lower
	# arr1[i] == arr2[i], continue
	addiu $t2, $t2, 1 	# i = i++
	b loop

break:	
	beq $t4, $t5, equals	# both null	
	beqz $t4, lower			# arr1+4i == null, arr2+4i != null
	beqz $t5, greater		# arr1+4i != null, arr2+4i == null	
	b errorExit				# misplaced breaki

greater: 
	addiu $v0, zero, 1
	b return

lower:
	addiu $v0, zero, -1	# ni idea si existe el "-1" como tal
	b return 

equals:
	addiu $v0, zero, zero
	b return

exitErro:
	addiu $v0, zero, -2	
	
return:
	move sp, $fp
	lw $ra, 28(sp)
	lw $fp, 24(sp)
	lw $gp, 20(sp)
	addu $sp, $sp, 32
    
	jr $ra		
