	.file	1 "stoogesort.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	stooge_sort
	.ent	stooge_sort
stooge_sort:
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
	lw	$4,48($fp)
	lw	$2,52($fp)
	sll	$3,$2,2
	lw	$2,48($fp)
	addu	$2,$3,$2
	addu	$2,$2,-4
	lw	$4,0($4)
	lw	$5,0($2)
	la	$25,linecmp
	jal	$31,$25
	blez	$2,$L14
	lw	$2,52($fp)
	addu	$2,$2,-1
	lw	$4,48($fp)
	move	$5,$0
	move	$6,$2
	la	$25,swapLine
	jal	$31,$25
$L14:
	lw	$2,52($fp)
	sltu	$2,$2,3
	bne	$2,$0,$L15
	lw	$3,52($fp)
	li	$2,-1431699456			# 0xffffffffaaaa0000
	ori	$2,$2,0xaaab
	multu	$3,$2
	mfhi	$2
	srl	$2,$2,1
	sw	$2,24($fp)
	lw	$3,52($fp)
	lw	$2,24($fp)
	subu	$2,$3,$2
	lw	$4,48($fp)
	move	$5,$2
	la	$25,stooge_sort
	jal	$31,$25
	lw	$2,24($fp)
	sll	$3,$2,2
	lw	$2,48($fp)
	addu	$4,$3,$2
	lw	$3,52($fp)
	lw	$2,24($fp)
	subu	$2,$3,$2
	move	$5,$2
	la	$25,stooge_sort
	jal	$31,$25
	lw	$3,52($fp)
	lw	$2,24($fp)
	subu	$2,$3,$2
	lw	$4,48($fp)
	move	$5,$2
	la	$25,stooge_sort
	jal	$31,$25
$L15:
	lw	$2,48($fp)
	move	$sp,$fp
	lw	$31,40($sp)
	lw	$fp,36($sp)
	addu	$sp,$sp,48
	j	$31
	.end	stooge_sort
	.size	stooge_sort, .-stooge_sort
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
