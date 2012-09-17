	.file	1 "parseManager.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	parseLineas
	.ent	parseLineas
parseLineas:
	.frame	$fp,48,$31		# vars= 8, regs= 4/0, args= 16, extra= 8
	.mask	0xd0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,48
	.cprestore 16
	sw	$31,44($sp)
	sw	$fp,40($sp)
	sw	$28,36($sp)
	sw	$16,32($sp)
	move	$fp,$sp
	sw	$4,48($fp)
	sw	$5,52($fp)
	sw	$6,56($fp)
	sw	$0,24($fp)
$L18:
	lw	$2,56($fp)
	lhu	$2,12($2)
	srl	$2,$2,5
	andi	$2,$2,0x1
	beq	$2,$0,$L20
	b	$L19
$L20:
	lw	$2,52($fp)
	addu	$2,$2,1
	sw	$2,52($fp)
	lw	$16,48($fp)
	lw	$3,48($fp)
	lw	$2,52($fp)
	sll	$2,$2,2
	lw	$4,0($3)
	move	$5,$2
	la	$25,realloc
	jal	$31,$25
	sw	$2,0($16)
	lw	$4,48($fp)
	lw	$2,52($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$2,$2,-4
	sw	$0,0($2)
	addu	$4,$fp,24
	lw	$5,56($fp)
	la	$25,cargarBuffer
	jal	$31,$25
	sw	$2,28($fp)
	lw	$4,48($fp)
	lw	$2,52($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$16,$2,-4
	lw	$4,48($fp)
	lw	$2,52($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$2,$2,-4
	lw	$4,0($2)
	lw	$5,28($fp)
	la	$25,realloc
	jal	$31,$25
	sw	$2,0($16)
	lw	$4,48($fp)
	lw	$2,52($fp)
	sll	$3,$2,2
	lw	$2,0($4)
	addu	$2,$3,$2
	addu	$2,$2,-4
	lw	$4,0($2)
	lw	$5,24($fp)
	lw	$6,28($fp)
	la	$25,memcpy
	jal	$31,$25
	b	$L18
$L19:
	lw	$4,24($fp)
	la	$25,free
	jal	$31,$25
	lw	$2,52($fp)
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	lw	$16,32($sp)
	addu	$sp,$sp,48
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
	li	$2,128			# 0x80
	sw	$2,24($fp)
	lw	$2,24($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
	sw	$0,32($fp)
$L22:
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
	beq	$2,$0,$L23
	lw	$2,64($fp)
	lw	$3,0($2)
	lw	$2,40($fp)
	addu	$2,$3,$2
	addu	$2,$2,-1
	lb	$3,0($2)
	li	$2,10			# 0xa
	bne	$3,$2,$L22
$L23:
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
