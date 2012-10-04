	.file	1 "quicksort.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	particionar
	.ent	particionar
particionar:
	.frame	$fp,56,$31		# vars= 16, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,56
	.cprestore 16
	sw	$31,48($sp)
	sw	$fp,44($sp)
	sw	$28,40($sp)
	move	$fp,$sp
	sw	$4,56($fp)
	sw	$5,60($fp)
	sw	$6,64($fp)
	sw	$7,68($fp)
	lw	$2,68($fp)
	sll	$3,$2,2
	lw	$2,56($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	sw	$2,24($fp)
	lw	$2,60($fp)
	sw	$2,28($fp)
	lw	$4,56($fp)
	lw	$5,68($fp)
	lw	$6,64($fp)
	la	$25,swapLine
	jal	$31,$25
	sw	$0,32($fp)
	lw	$2,60($fp)
	sw	$2,32($fp)
$L18:
	lw	$2,32($fp)
	lw	$3,64($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L21
	b	$L19
$L21:
	lw	$2,32($fp)
	sll	$3,$2,2
	lw	$2,56($fp)
	addu	$2,$3,$2
	lw	$4,0($2)
	lw	$5,24($fp)
	la	$25,linecmp
	jal	$31,$25
	bgez	$2,$L20
	lw	$4,56($fp)
	lw	$5,32($fp)
	lw	$6,28($fp)
	la	$25,swapLine
	jal	$31,$25
	lw	$2,28($fp)
	addu	$2,$2,1
	sw	$2,28($fp)
$L20:
	lw	$2,32($fp)
	addu	$2,$2,1
	sw	$2,32($fp)
	b	$L18
$L19:
	lw	$4,56($fp)
	lw	$5,28($fp)
	lw	$6,64($fp)
	la	$25,swapLine
	jal	$31,$25
	lw	$2,28($fp)
	move	$sp,$fp
	lw	$31,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$31
	.end	particionar
	.size	particionar, .-particionar
	.align	2
	.globl	quickSort_r
	.ent	quickSort_r
quickSort_r:
	.frame	$fp,56,$31		# vars= 16, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,56
	.cprestore 16
	sw	$31,48($sp)
	sw	$fp,44($sp)
	sw	$28,40($sp)
	move	$fp,$sp
	sw	$4,56($fp)
	sw	$5,60($fp)
	sw	$6,64($fp)
	lw	$2,56($fp)
	beq	$2,$0,$L24
	lw	$2,60($fp)
	lw	$3,64($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L24
	lw	$3,60($fp)
	lw	$2,64($fp)
	addu	$3,$3,$2
	sra	$2,$3,31
	srl	$2,$2,31
	addu	$2,$3,$2
	sra	$2,$2,1
	sw	$2,24($fp)
	lw	$4,56($fp)
	lw	$5,60($fp)
	lw	$6,64($fp)
	lw	$7,24($fp)
	la	$25,particionar
	jal	$31,$25
	sw	$2,28($fp)
	lw	$2,28($fp)
	addu	$2,$2,-1
	lw	$4,56($fp)
	lw	$5,60($fp)
	move	$6,$2
	la	$25,quickSort_r
	jal	$31,$25
	lw	$2,28($fp)
	addu	$2,$2,1
	lw	$4,56($fp)
	move	$5,$2
	lw	$6,64($fp)
	la	$25,quickSort_r
	jal	$31,$25
	lw	$2,56($fp)
	sw	$2,32($fp)
	b	$L23
$L24:
	lw	$2,56($fp)
	sw	$2,32($fp)
$L23:
	lw	$2,32($fp)
	move	$sp,$fp
	lw	$31,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$31
	.end	quickSort_r
	.size	quickSort_r, .-quickSort_r
	.align	2
	.globl	quick_sort
	.ent	quick_sort
quick_sort:
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
	sw	$5,44($fp)
	lw	$2,44($fp)
	addu	$2,$2,-1
	lw	$4,40($fp)
	move	$5,$0
	move	$6,$2
	la	$25,quickSort_r
	jal	$31,$25
	move	$sp,$fp
	lw	$31,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$31
	.end	quick_sort
	.size	quick_sort, .-quick_sort
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
