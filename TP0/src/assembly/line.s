	.file	1 "line.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	getSize
	.ent	getSize
getSize:
	.frame	$fp,16,$31		# vars= 0, regs= 2/0, args= 0, extra= 8
	.mask	0x50000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,16
	.cprestore 0
	sw	$fp,12($sp)
	sw	$28,8($sp)
	move	$fp,$sp
	sw	$4,16($fp)
	lw	$2,16($fp)
	lw	$2,4($2)
	move	$sp,$fp
	lw	$fp,12($sp)
	addu	$sp,$sp,16
	j	$31
	.end	getSize
	.size	getSize, .-getSize
	.align	2
	.globl	createLine
	.ent	createLine
createLine:
	.frame	$fp,48,$31		# vars= 8, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,48
	.cprestore 16
	sw	$31,40($sp)
	sw	$fp,36($sp)
	sw	$28,32($sp)
	move	$fp,$sp
	sw	$4,48($fp)
	sw	$5,52($fp)
	li	$4,8			# 0x8
	la	$25,malloc
	jal	$31,$25
	sw	$2,24($fp)
	lw	$3,24($fp)
	lw	$2,48($fp)
	sw	$2,0($3)
	lw	$3,24($fp)
	lw	$2,52($fp)
	sw	$2,4($3)
	lw	$2,24($fp)
	move	$sp,$fp
	lw	$31,40($sp)
	lw	$fp,36($sp)
	addu	$sp,$sp,48
	j	$31
	.end	createLine
	.size	createLine, .-createLine
	.align	2
	.globl	linecmp
	.ent	linecmp
linecmp:
	.frame	$fp,32,$31		# vars= 16, regs= 2/0, args= 0, extra= 8
	.mask	0x50000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,32
	.cprestore 0
	sw	$fp,28($sp)
	sw	$28,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	sw	$0,8($fp)
	sw	$0,12($fp)
	sw	$0,16($fp)
$L20:
	lw	$2,16($fp)
	bne	$2,$0,$L21
	lw	$2,32($fp)
	lw	$2,4($2)
	addu	$3,$2,-1
	lw	$2,8($fp)
	sltu	$2,$2,$3
	beq	$2,$0,$L21
	lw	$2,36($fp)
	lw	$2,4($2)
	addu	$3,$2,-1
	lw	$2,12($fp)
	sltu	$2,$2,$3
	bne	$2,$0,$L22
	b	$L21
$L22:
	lw	$2,32($fp)
	lw	$5,8($fp)
	move	$3,$5
	lw	$2,0($2)
	addu	$2,$3,$2
	lb	$7,0($2)
	lw	$2,36($fp)
	addu	$6,$fp,12
	lw	$3,0($6)
	move	$4,$3
	lw	$2,0($2)
	addu	$2,$4,$2
	lb	$2,0($2)
	subu	$2,$7,$2
	sw	$2,16($fp)
	addu	$3,$3,1
	sw	$3,0($6)
	addu	$5,$5,1
	sw	$5,8($fp)
	b	$L20
$L21:
	lw	$2,16($fp)
	bne	$2,$0,$L24
	lw	$2,32($fp)
	lw	$3,36($fp)
	lw	$4,4($2)
	lw	$2,4($3)
	subu	$2,$4,$2
	sw	$2,20($fp)
	b	$L19
$L24:
	lw	$2,16($fp)
	sw	$2,20($fp)
$L19:
	lw	$2,20($fp)
	move	$sp,$fp
	lw	$fp,28($sp)
	addu	$sp,$sp,32
	j	$31
	.end	linecmp
	.size	linecmp, .-linecmp
	.align	2
	.globl	printLine
	.ent	printLine
printLine:
	.frame	$fp,40,$31		# vars= 0, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,40
	.cprestore 16
	sw	$31,32($sp)
	sw	$fp,28($sp)
	sw	$28,24($sp)
	move	$fp,$sp
	sw	$4,40($fp)
	lw	$2,40($fp)
	lw	$3,40($fp)
	lw	$4,0($2)
	li	$5,1			# 0x1
	lw	$6,4($3)
	la	$7,__sF+88
	la	$25,fwrite
	jal	$31,$25
	move	$sp,$fp
	lw	$31,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$31
	.end	printLine
	.size	printLine, .-printLine
	.align	2
	.globl	swapLine
	.ent	swapLine
swapLine:
	.frame	$fp,24,$31		# vars= 8, regs= 2/0, args= 0, extra= 8
	.mask	0x50000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,24
	.cprestore 0
	sw	$fp,20($sp)
	sw	$28,16($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	sw	$5,28($fp)
	sw	$6,32($fp)
	lw	$2,28($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	sw	$2,8($fp)
	lw	$2,28($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$4,$3,$2
	lw	$2,32($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	sw	$2,0($4)
	lw	$2,32($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$3,$3,$2
	lw	$2,8($fp)
	sw	$2,0($3)
	move	$sp,$fp
	lw	$fp,20($sp)
	addu	$sp,$sp,24
	j	$31
	.end	swapLine
	.size	swapLine, .-swapLine
	.align	2
	.globl	freeLine
	.ent	freeLine
freeLine:
	.frame	$fp,40,$31		# vars= 0, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,40
	.cprestore 16
	sw	$31,32($sp)
	sw	$fp,28($sp)
	sw	$28,24($sp)
	move	$fp,$sp
	sw	$4,40($fp)
	lw	$2,40($fp)
	lw	$2,0($2)
	bne	$2,$0,$L29
	b	$L28
$L29:
	lw	$2,40($fp)
	lw	$2,0($2)
	lw	$4,0($2)
	la	$25,free
	jal	$31,$25
	lw	$2,40($fp)
	lw	$4,0($2)
	la	$25,free
	jal	$31,$25
	lw	$2,40($fp)
	sw	$0,0($2)
$L28:
	move	$sp,$fp
	lw	$31,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$31
	.end	freeLine
	.size	freeLine, .-freeLine
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
