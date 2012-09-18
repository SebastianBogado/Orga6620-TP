	.file	1 "parseManager.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	parseLineas
	.ent	parseLineas
parseLineas:
	.frame	$fp,56,$31		# vars= 16, regs= 4/0, args= 16, extra= 8
	.mask	0xd0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,56
	.cprestore 16
	sw	$31,52($sp)
	sw	$fp,48($sp)
	sw	$28,44($sp)
	sw	$16,40($sp)
	move	$fp,$sp
	sw	$4,56($fp)
	sw	$5,60($fp)
	sw	$6,64($fp)
	sw	$0,24($fp)
$L18:
	lw	$2,64($fp)
	lhu	$2,12($2)
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$L20
	b	$L19
$L20:
	addu	$4,$fp,24
	lw	$5,64($fp)
	la	$25,cargarBuffer
	jal	$31,$25
	sw	$2,28($fp)
	lw	$2,28($fp)
	bne	$2,$0,$L22
	lw	$4,56($fp)
	lw	$2,60($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$2,$2,-4
	lw	$4,24($fp)
	lw	$5,0($2)
	la	$25,strcmp
	jal	$31,$25
	bne	$2,$0,$L22
	b	$L18
$L22:
	lw	$4,24($fp)
	la	$25,strlen
	jal	$31,$25
	sw	$2,32($fp)
	lw	$2,60($fp)
	addu	$2,$2,1
	sw	$2,60($fp)
	lw	$16,56($fp)
	lw	$3,56($fp)
	lw	$2,60($fp)
	sll	$2,$2,2
	lw	$4,0($3)
	move	$5,$2
	la	$25,realloc
	jal	$31,$25
	sw	$2,0($16)
	lw	$4,56($fp)
	lw	$2,60($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$2,$2,-4
	sw	$0,0($2)
	lw	$4,56($fp)
	lw	$2,60($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$16,$2,-4
	lw	$4,56($fp)
	lw	$2,60($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$3,$2,-4
	lw	$2,32($fp)
	addu	$2,$2,1
	lw	$4,0($3)
	move	$5,$2
	la	$25,realloc
	jal	$31,$25
	sw	$2,0($16)
	lw	$4,56($fp)
	lw	$2,60($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$2,$2,-4
	lw	$4,0($2)
	lw	$5,24($fp)
	la	$25,strcpy
	jal	$31,$25
	b	$L18
$L19:
	lw	$4,24($fp)
	la	$25,free
	jal	$31,$25
	lw	$2,60($fp)
	move	$sp,$fp
	lw	$31,52($sp)
	lw	$fp,48($sp)
	lw	$16,40($sp)
	addu	$sp,$sp,56
	j	$31
	.end	parseLineas
	.size	parseLineas, .-parseLineas
	.align	2
	.globl	cargarBuffer
	.ent	cargarBuffer
cargarBuffer:
	.frame	$fp,64,$31		# vars= 24, regs= 4/0, args= 16, extra= 8
	.mask	0xd0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,64
	.cprestore 16
	sw	$31,60($sp)
	sw	$fp,56($sp)
	sw	$28,52($sp)
	sw	$16,48($sp)
	move	$fp,$sp
	sw	$4,64($fp)
	sw	$5,68($fp)
	li	$2,1024			# 0x400
	sw	$2,24($fp)
	lw	$2,24($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
	sw	$0,32($fp)
$L24:
	lw	$2,32($fp)
	addu	$2,$2,1
	sw	$2,32($fp)
	lw	$3,32($fp)
	lw	$2,24($fp)
	mult	$3,$2
	mflo	$2
	addu	$2,$2,1
	sw	$2,36($fp)
	lw	$16,64($fp)
	lw	$2,64($fp)
	lw	$4,0($2)
	lw	$5,36($fp)
	la	$25,realloc
	jal	$31,$25
	sw	$2,0($16)
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,36($fp)
	addu	$3,$3,$2
	lw	$2,28($fp)
	subu	$2,$3,$2
	move	$4,$2
	lw	$5,28($fp)
	lw	$6,68($fp)
	la	$25,fgets
	jal	$31,$25
	sw	$2,44($fp)
	lw	$2,64($fp)
	lw	$4,0($2)
	la	$25,strlen
	jal	$31,$25
	sw	$2,40($fp)
	lw	$2,44($fp)
	beq	$2,$0,$L25
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,40($fp)
	addu	$2,$3,$2
	addu	$2,$2,-1
	lb	$3,0($2)
	li	$2,10			# 0xa
	bne	$3,$2,$L24
$L25:
	lw	$2,44($fp)
	bne	$2,$0,$L29
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,40($fp)
	addu	$2,$3,$2
	addu	$2,$2,-1
	lb	$3,0($2)
	li	$2,10			# 0xa
	beq	$3,$2,$L30
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,40($fp)
	addu	$3,$3,$2
	li	$2,10			# 0xa
	sb	$2,0($3)
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,40($fp)
	addu	$2,$3,$2
	addu	$2,$2,1
	sb	$0,0($2)
$L30:
	sw	$0,40($fp)
$L29:
	lw	$2,40($fp)
	move	$sp,$fp
	lw	$31,60($sp)
	lw	$fp,56($sp)
	lw	$16,48($sp)
	addu	$sp,$sp,64
	j	$31
	.end	cargarBuffer
	.size	cargarBuffer, .-cargarBuffer
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
