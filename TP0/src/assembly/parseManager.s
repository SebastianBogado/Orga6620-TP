	.file	1 "parseManager.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	parseLineas
	.ent	parseLineas
parseLineas:
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
	sw	$6,72($fp)
	sw	$0,24($fp)
	sw	$0,32($fp)
	addu	$4,$fp,24
	lw	$5,72($fp)
	la	$25,cargarBuffer
	jal	$31,$25
	sw	$2,28($fp)
	sw	$0,36($fp)
$L18:
	lw	$2,36($fp)
	lw	$3,28($fp)
	sltu	$2,$3,$2
	beq	$2,$0,$L21
	b	$L19
$L21:
	lw	$2,32($fp)
	addu	$2,$2,1
	sw	$2,32($fp)
	lw	$3,24($fp)
	lw	$2,36($fp)
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,10			# 0xa
	bne	$3,$2,$L20
	lw	$4,32($fp)
	la	$25,malloc
	jal	$31,$25
	sw	$2,40($fp)
	lw	$3,24($fp)
	lw	$2,36($fp)
	addu	$3,$3,$2
	lw	$2,32($fp)
	subu	$2,$3,$2
	addu	$2,$2,1
	lw	$4,40($fp)
	move	$5,$2
	lw	$6,32($fp)
	la	$25,memcpy
	jal	$31,$25
	lw	$2,68($fp)
	addu	$2,$2,1
	sw	$2,68($fp)
	lw	$16,64($fp)
	lw	$3,64($fp)
	lw	$2,68($fp)
	sll	$2,$2,2
	lw	$4,0($3)
	move	$5,$2
	la	$25,realloc
	jal	$31,$25
	sw	$2,0($16)
	lw	$4,40($fp)
	lw	$5,32($fp)
	la	$25,createLine
	jal	$31,$25
	move	$5,$2
	lw	$4,64($fp)
	lw	$2,68($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$2,$2,-4
	sw	$5,0($2)
	sw	$0,32($fp)
$L20:
	lw	$2,36($fp)
	addu	$2,$2,1
	sw	$2,36($fp)
	b	$L18
$L19:
	lw	$4,24($fp)
	la	$25,free
	jal	$31,$25
	lw	$2,68($fp)
	move	$sp,$fp
	lw	$31,60($sp)
	lw	$fp,56($sp)
	lw	$16,48($sp)
	addu	$sp,$sp,64
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
	sw	$0,28($fp)
	sw	$0,32($fp)
	sw	$0,36($fp)
	sw	$0,40($fp)
	lw	$2,28($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
	lw	$3,28($fp)
	lw	$2,24($fp)
	mult	$3,$2
	mflo	$2
	sw	$2,32($fp)
$L24:
	lw	$16,64($fp)
	lw	$2,64($fp)
	lw	$4,0($2)
	lw	$5,32($fp)
	la	$25,realloc
	jal	$31,$25
	sw	$2,0($16)
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,32($fp)
	addu	$3,$3,$2
	lw	$2,24($fp)
	subu	$2,$3,$2
	move	$4,$2
	li	$5,1			# 0x1
	lw	$6,24($fp)
	lw	$7,68($fp)
	la	$25,fread
	jal	$31,$25
	sw	$2,40($fp)
	lw	$3,36($fp)
	lw	$2,40($fp)
	addu	$2,$3,$2
	sw	$2,36($fp)
	lw	$2,28($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
	lw	$3,28($fp)
	lw	$2,24($fp)
	mult	$3,$2
	mflo	$2
	sw	$2,32($fp)
	lw	$2,68($fp)
	lhu	$2,12($2)
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$L24
	lw	$2,36($fp)
	beq	$2,$0,$L28
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,36($fp)
	addu	$2,$3,$2
	addu	$2,$2,-1
	lb	$3,0($2)
	li	$2,10			# 0xa
	beq	$3,$2,$L28
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,36($fp)
	addu	$3,$3,$2
	li	$2,10			# 0xa
	sb	$2,0($3)
$L28:
	lw	$2,36($fp)
	move	$sp,$fp
	lw	$31,60($sp)
	lw	$fp,56($sp)
	lw	$16,48($sp)
	addu	$sp,$sp,64
	j	$31
	.end	cargarBuffer
	.size	cargarBuffer, .-cargarBuffer
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
