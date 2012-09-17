	.file	1 "main.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	main
	.ent	main
main:
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
	lw	$3,48($fp)
	li	$2,1			# 0x1
	bne	$3,$2,$L18
	sw	$0,24($fp)
	b	$L19
$L18:
	lw	$2,52($fp)
	addu	$2,$2,4
	lw	$4,0($2)
	la	$25,check_param
	jal	$31,$25
	sw	$2,24($fp)
$L19:
	lw	$2,24($fp)
	sw	$2,28($fp)
	li	$2,1			# 0x1
	lw	$3,28($fp)
	beq	$3,$2,$L22
	lw	$3,28($fp)
	slt	$2,$3,2
	beq	$2,$0,$L27
	lw	$2,28($fp)
	beq	$2,$0,$L21
	b	$L20
$L27:
	li	$2,2			# 0x2
	lw	$3,28($fp)
	beq	$3,$2,$L23
	li	$2,3			# 0x3
	lw	$3,28($fp)
	beq	$3,$2,$L24
	b	$L20
$L21:
	la	$25,print_help
	jal	$31,$25
	b	$L20
$L22:
	la	$25,print_version
	jal	$31,$25
	b	$L20
$L23:
	lw	$2,48($fp)
	addu	$3,$2,-2
	lw	$2,52($fp)
	addu	$2,$2,8
	move	$4,$3
	move	$5,$2
	la	$6,quick_sort
	la	$25,sort
	jal	$31,$25
	b	$L20
$L24:
	lw	$2,48($fp)
	addu	$3,$2,-2
	lw	$2,52($fp)
	addu	$2,$2,8
	move	$4,$3
	move	$5,$2
	la	$6,stooge_sort
	la	$25,sort
	jal	$31,$25
$L20:
	move	$2,$0
	move	$sp,$fp
	lw	$31,40($sp)
	lw	$fp,36($sp)
	addu	$sp,$sp,48
	j	$31
	.end	main
	.size	main, .-main
	.rdata
	.align	2
$LC0:
	.ascii	"-q\000"
	.align	2
$LC1:
	.ascii	"--quick\000"
	.align	2
$LC2:
	.ascii	"-s\000"
	.align	2
$LC3:
	.ascii	"--stooge\000"
	.align	2
$LC4:
	.ascii	"-V\000"
	.align	2
$LC5:
	.ascii	"--version\000"
	.text
	.align	2
	.globl	check_param
	.ent	check_param
check_param:
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
	lw	$4,48($fp)
	la	$5,$LC0
	la	$25,strcmp
	jal	$31,$25
	beq	$2,$0,$L30
	lw	$4,48($fp)
	la	$5,$LC1
	la	$25,strcmp
	jal	$31,$25
	bne	$2,$0,$L29
$L30:
	li	$2,2			# 0x2
	sw	$2,24($fp)
	b	$L28
$L29:
	lw	$4,48($fp)
	la	$5,$LC2
	la	$25,strcmp
	jal	$31,$25
	beq	$2,$0,$L33
	lw	$4,48($fp)
	la	$5,$LC3
	la	$25,strcmp
	jal	$31,$25
	bne	$2,$0,$L32
$L33:
	li	$2,3			# 0x3
	sw	$2,24($fp)
	b	$L28
$L32:
	lw	$4,48($fp)
	la	$5,$LC4
	la	$25,strcmp
	jal	$31,$25
	beq	$2,$0,$L36
	lw	$4,48($fp)
	la	$5,$LC5
	la	$25,strcmp
	jal	$31,$25
	bne	$2,$0,$L35
$L36:
	li	$2,1			# 0x1
	sw	$2,24($fp)
	b	$L28
$L35:
	sw	$0,24($fp)
$L28:
	lw	$2,24($fp)
	move	$sp,$fp
	lw	$31,40($sp)
	lw	$fp,36($sp)
	addu	$sp,$sp,48
	j	$31
	.end	check_param
	.size	check_param, .-check_param
	.rdata
	.align	2
$LC6:
	.ascii	"tp0 [OPTIONS] [file...]\n"
	.ascii	"-h, --help\tdisplay this help and exit.\n"
	.ascii	"-V, --version\tdisplay version information and exit.\n"
	.ascii	"-q, --quick\tuse the quicksort algorithm.\n"
	.ascii	"-s, --stooge\tuse the stoogesort algorithm.\n\000"
	.text
	.align	2
	.globl	print_help
	.ent	print_help
print_help:
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
	la	$4,$LC6
	la	$25,printf
	jal	$31,$25
	move	$sp,$fp
	lw	$31,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$31
	.end	print_help
	.size	print_help, .-print_help
	.rdata
	.align	2
$LC7:
	.ascii	"Organizacion de Computadoras [6620] - TP0 \n\000"
	.align	2
$LC8:
	.ascii	"Version: 1.0\000"
	.align	2
$LC9:
	.ascii	"Alumnos: Bogado, Sebastian \n\000"
	.align	2
$LC10:
	.ascii	"         Garcia Marra, Alejandro\n\000"
	.text
	.align	2
	.globl	print_version
	.ent	print_version
print_version:
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
	la	$4,$LC7
	la	$25,printf
	jal	$31,$25
	la	$4,$LC8
	la	$25,printf
	jal	$31,$25
	la	$4,$LC9
	la	$25,printf
	jal	$31,$25
	la	$4,$LC10
	la	$25,printf
	jal	$31,$25
	move	$sp,$fp
	lw	$31,32($sp)
	lw	$fp,28($sp)
	addu	$sp,$sp,40
	j	$31
	.end	print_version
	.size	print_version, .-print_version
	.ident	"GCC: (GNU) 3.3.3 (NetBSD nb3 20040520)"
