	.file	1 "sort.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"rb\000"
	.align	2
$LC1:
	.ascii	"%s\000"
	.text
	.align	2
	.globl	sort
	.ent	sort
sort:
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
	sw	$0,24($fp)
	sw	$0,28($fp)
	lw	$2,56($fp)
	beq	$2,$0,$L18
	sw	$0,36($fp)
$L19:
	lw	$2,36($fp)
	lw	$3,56($fp)
	sltu	$2,$2,$3
	bne	$2,$0,$L22
	b	$L25
$L22:
	lw	$2,36($fp)
	sll	$3,$2,2
	lw	$2,60($fp)
	addu	$2,$3,$2
	lw	$4,0($2)
	la	$5,$LC0
	la	$25,fopen
	jal	$31,$25
	sw	$2,32($fp)
	lw	$2,32($fp)
	beq	$2,$0,$L23
	addu	$4,$fp,24
	lw	$5,28($fp)
	lw	$6,32($fp)
	la	$25,parseLineas
	jal	$31,$25
	sw	$2,28($fp)
	lw	$4,32($fp)
	la	$25,fclose
	jal	$31,$25
	b	$L21
$L23:
	lw	$2,36($fp)
	sll	$3,$2,2
	lw	$2,60($fp)
	addu	$2,$3,$2
	lw	$4,0($2)
	la	$25,perror
	jal	$31,$25
$L21:
	lw	$2,36($fp)
	addu	$2,$2,1
	sw	$2,36($fp)
	b	$L19
$L18:
	addu	$4,$fp,24
	lw	$5,28($fp)
	la	$6,__sF
	la	$25,parseLineas
	jal	$31,$25
	sw	$2,28($fp)
$L25:
	lw	$2,64($fp)
	lw	$4,24($fp)
	lw	$5,28($fp)
	move	$25,$2
	jal	$31,$25
	sw	$2,24($fp)
	sw	$0,36($fp)
$L26:
	lw	$2,36($fp)
	lw	$3,28($fp)
	sltu	$2,$2,$3
	bne	$2,$0,$L29
	b	$L27
$L29:
	lw	$2,36($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$2,$3,$2
	la	$4,$LC1
	lw	$5,0($2)
	la	$25,printf
	jal	$31,$25
	lw	$2,36($fp)
	addu	$2,$2,1
	sw	$2,36($fp)
	b	$L26
$L27:
	sw	$0,36($fp)
$L30:
	lw	$2,36($fp)
	lw	$3,28($fp)
	sltu	$2,$2,$3
	bne	$2,$0,$L33
	b	$L31
$L33:
	lw	$2,36($fp)
	sll	$3,$2,2
	lw	$2,24($fp)
	addu	$2,$3,$2
	lw	$4,0($2)
	la	$25,free
	jal	$31,$25
	lw	$2,36($fp)
	addu	$2,$2,1
	sw	$2,36($fp)
	b	$L30
$L31:
	lw	$4,24($fp)
	la	$25,free
	jal	$31,$25
	move	$sp,$fp
	lw	$31,48($sp)
	lw	$fp,44($sp)
	addu	$sp,$sp,56
	j	$31
	.end	sort
	.size	sort, .-sort
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
