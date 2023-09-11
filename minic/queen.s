.text
.globl print
print:
	st.d $r22, $r3, -16
	st.d $r1, $r3, -8
	addi.d $r22, $r3, -16
	addi.d $r3, $r3, -32
	st.d $r23, $r3, 0
	st.d $r24, $r3, 8
	li.w $r12, 0
	addi.w $r24, $r12, 0
.L2:
	la.global $r21, glo1
	ld.w $r12, $r21, 0
	slt $r12, $r24, $r12
	beqz $r12, .L11
	li.w $r12, 0
	addi.w $r23, $r12, 0
.L5:
	la.global $r21, glo1
	ld.w $r12, $r21, 0
	slt $r12, $r23, $r12
	beqz $r12, .L10
	la.global $r21, glo3
	ld.d $r12, $r21, 0
	addi.w $r14, $r23, 0
	li.w $r13, 8
	mul.d $r13, $r13, $r14
	add.d $r12, $r12, $r13
	ld.d $r12, $r12, 0
	addi.w $r14, $r24, 0
	li.w $r13, 4
	mul.d $r13, $r13, $r14
	add.d $r12, $r12, $r13
	ld.w $r12, $r12, 0
	bnez $r12, .L8
	la.global $r4, glo5
	bl printf
	b .L9
.L8:
	la.global $r4, glo4
	bl printf
.L9:
	addi.w $r23, $r23, 1
	b .L5
.L10:
	la.global $r4, glo6
	bl printf
	addi.w $r24, $r24, 1
	b .L2
.L11:
	la.global $r4, glo7
	bl printf
	li.w $r4, 0
	ld.d $r23, $r3, 0
	ld.d $r24, $r3, 8
	addi.d $r3, $r22, 16
	ld.d $r1, $r22, 8
	ld.d $r22, $r22, 0
	jirl $r0, $r1, 0
/* end function print */

.text
.globl chk
chk:
	st.d $r22, $r3, -16
	st.d $r1, $r3, -8
	addi.d $r22, $r3, -16
	addi.d $r3, $r3, -16
	li.w $r13, 0
	li.w $r12, 0
.L14:
	la.global $r21, glo1
	ld.w $r17, $r21, 0
	slt $r14, $r13, $r17
	beqz $r14, .L24
	la.global $r21, glo3
	ld.d $r14, $r21, 0
	addi.w $r16, $r4, 0
	li.w $r15, 8
	mul.d $r15, $r15, $r16
	add.d $r15, $r14, $r15
	ld.d $r15, $r15, 0
	addi.w $r18, $r13, 0
	li.w $r16, 4
	mul.d $r16, $r16, $r18
	add.d $r15, $r15, $r16
	ld.w $r15, $r15, 0
	add.w $r12, $r12, $r15
	addi.w $r16, $r13, 0
	li.w $r15, 8
	mul.d $r15, $r15, $r16
	add.d $r15, $r14, $r15
	ld.d $r15, $r15, 0
	addi.w $r18, $r5, 0
	li.w $r16, 4
	mul.d $r16, $r16, $r18
	add.d $r15, $r15, $r16
	ld.w $r15, $r15, 0
	add.w $r12, $r12, $r15
	add.w $r15, $r4, $r13
	slt $r15, $r15, $r17
	add.w $r16, $r5, $r13
	slt $r16, $r16, $r17
	and $r15, $r15, $r16
	beqz $r15, .L17
	add.w $r15, $r4, $r13
	addi.w $r16, $r15, 0
	li.w $r15, 8
	mul.d $r15, $r15, $r16
	add.d $r15, $r14, $r15
	ld.d $r15, $r15, 0
	add.w $r16, $r5, $r13
	addi.w $r18, $r16, 0
	li.w $r16, 4
	mul.d $r16, $r16, $r18
	add.d $r15, $r15, $r16
	ld.w $r15, $r15, 0
	add.w $r12, $r12, $r15
.L17:
	add.w $r15, $r4, $r13
	slt $r15, $r15, $r17
	sub.w $r16, $r5, $r13
	slti $r16, $r16, 0
	xori $r16, $r16, 1
	and $r15, $r15, $r16
	beqz $r15, .L19
	add.w $r15, $r4, $r13
	addi.w $r16, $r15, 0
	li.w $r15, 8
	mul.d $r15, $r15, $r16
	add.d $r15, $r14, $r15
	ld.d $r15, $r15, 0
	sub.w $r16, $r5, $r13
	addi.w $r18, $r16, 0
	li.w $r16, 4
	mul.d $r16, $r16, $r18
	add.d $r15, $r15, $r16
	ld.w $r15, $r15, 0
	add.w $r12, $r12, $r15
.L19:
	sub.w $r15, $r4, $r13
	slti $r15, $r15, 0
	xori $r15, $r15, 1
	add.w $r16, $r5, $r13
	slt $r16, $r16, $r17
	and $r15, $r15, $r16
	beqz $r15, .L21
	sub.w $r15, $r4, $r13
	addi.w $r16, $r15, 0
	li.w $r15, 8
	mul.d $r15, $r15, $r16
	add.d $r15, $r14, $r15
	ld.d $r15, $r15, 0
	add.w $r16, $r5, $r13
	addi.w $r17, $r16, 0
	li.w $r16, 4
	mul.d $r16, $r16, $r17
	add.d $r15, $r15, $r16
	ld.w $r15, $r15, 0
	add.w $r12, $r12, $r15
.L21:
	sub.w $r15, $r4, $r13
	slti $r15, $r15, 0
	xori $r15, $r15, 1
	sub.w $r16, $r5, $r13
	slti $r16, $r16, 0
	xori $r16, $r16, 1
	and $r15, $r15, $r16
	beqz $r15, .L23
	sub.w $r15, $r4, $r13
	addi.w $r16, $r15, 0
	li.w $r15, 8
	mul.d $r15, $r15, $r16
	add.d $r14, $r14, $r15
	ld.d $r14, $r14, 0
	sub.w $r15, $r5, $r13
	addi.w $r16, $r15, 0
	li.w $r15, 4
	mul.d $r15, $r15, $r16
	add.d $r14, $r14, $r15
	ld.w $r14, $r14, 0
	add.w $r12, $r12, $r14
.L23:
	addi.w $r13, $r13, 1
	b .L14
.L24:
	addi.w $r4, $r12, 0
	addi.d $r3, $r22, 16
	ld.d $r1, $r22, 8
	ld.d $r22, $r22, 0
	jirl $r0, $r1, 0
/* end function chk */

.text
.globl go
go:
	st.d $r22, $r3, -16
	st.d $r1, $r3, -8
	addi.d $r22, $r3, -16
	addi.d $r3, $r3, -32
	st.d $r23, $r3, 0
	st.d $r24, $r3, 8
	la.global $r21, glo1
	ld.w $r12, $r21, 0
	xor $r12, $r4, $r12
	sltui $r12, $r12, 1
	bnez $r12, .L34
	li.w $r12, 0
	addi.w $r23, $r12, 0
.L29:
	la.global $r21, glo1
	ld.w $r12, $r21, 0
	slt $r12, $r23, $r12
	beqz $r12, .L33
	addi.w $r5, $r4, 0
	addi.w $r24, $r4, 0
	addi.w $r4, $r23, 0
	bl chk
	addi.w $r12, $r4, 0
	addi.w $r4, $r24, 0
	xori $r12, $r12, 0
	sltui $r12, $r12, 1
	beqz $r12, .L32
	la.global $r21, glo3
	ld.d $r12, $r21, 0
	addi.w $r14, $r23, 0
	li.w $r13, 8
	mul.d $r13, $r13, $r14
	add.d $r12, $r12, $r13
	ld.d $r12, $r12, 0
	addi.w $r14, $r4, 0
	li.w $r13, 4
	mul.d $r13, $r13, $r14
	add.d $r13, $r12, $r13
	ld.w $r12, $r13, 0
	addi.w $r12, $r12, 1
	st.w $r12, $r13, 0
	addi.w $r24, $r4, 0
	addi.w $r4, $r4, 1
	bl go
	addi.w $r4, $r24, 0
	la.global $r21, glo3
	ld.d $r12, $r21, 0
	addi.w $r14, $r23, 0
	li.w $r13, 8
	mul.d $r13, $r13, $r14
	add.d $r12, $r12, $r13
	ld.d $r12, $r12, 0
	addi.w $r14, $r4, 0
	li.w $r13, 4
	mul.d $r13, $r13, $r14
	add.d $r13, $r12, $r13
	ld.w $r12, $r13, 0
	li.w $r14, 1
	sub.w $r12, $r12, $r14
	st.w $r12, $r13, 0
.L32:
	addi.w $r23, $r23, 1
	b .L29
.L33:
	li.w $r4, 0
	b .L35
.L34:
	bl print
	la.global $r21, glo2
	ld.w $r12, $r21, 0
	addi.w $r12, $r12, 1
	la.global $r21, glo2
	st.w $r12, $r21, 0
	li.w $r4, 0
.L35:
	ld.d $r23, $r3, 0
	ld.d $r24, $r3, 8
	addi.d $r3, $r22, 16
	ld.d $r1, $r22, 8
	ld.d $r22, $r22, 0
	jirl $r0, $r1, 0
/* end function go */

.text
.globl main
main:
	st.d $r22, $r3, -16
	st.d $r1, $r3, -8
	addi.d $r22, $r3, -16
	addi.d $r3, $r3, -32
	st.d $r23, $r3, 0
	li.w $r12, 8
	la.global $r21, glo1
	st.w $r12, $r21, 0
	slti $r12, $r4, 2
	xori $r13, $r12, 1
	li.w $r12, 8
	bnez $r13, .L38
	addi.w $r4, $r12, 0
	b .L39
.L38:
	addi.d $r12, $r5, 8
	ld.d $r4, $r12, 0
	bl atoi
	la.global $r21, glo1
	st.w $r4, $r21, 0
.L39:
	li.w $r5, 8
	bl calloc
	addi.d $r12, $r4, 0
	la.global $r21, glo3
	st.d $r12, $r21, 0
	li.w $r12, 0
	addi.w $r23, $r12, 0
.L41:
	la.global $r21, glo1
	ld.w $r4, $r21, 0
	slt $r12, $r23, $r4
	beqz $r12, .L43
	li.w $r5, 4
	bl calloc
	addi.d $r12, $r4, 0
	la.global $r21, glo3
	ld.d $r13, $r21, 0
	addi.w $r15, $r23, 0
	li.w $r14, 8
	mul.d $r14, $r14, $r15
	add.d $r13, $r13, $r14
	st.d $r12, $r13, 0
	addi.w $r23, $r23, 1
	b .L41
.L43:
	li.w $r4, 0
	bl go
	la.global $r21, glo2
	ld.w $r5, $r21, 0
	la.global $r4, glo8
	bl printf
	li.w $r4, 0
	ld.d $r23, $r3, 0
	addi.d $r3, $r22, 16
	ld.d $r1, $r22, 8
	ld.d $r22, $r22, 0
	jirl $r0, $r1, 0
/* end function main */

.data
.balign 8
glo1:
	.int 0
/* end data */

.data
.balign 8
glo2:
	.int 0
/* end data */

.data
.balign 8
glo3:
	.quad 0
/* end data */

.data
.balign 8
glo4:
	.ascii " Q"
	.byte 0
/* end data */

.data
.balign 8
glo5:
	.ascii " ."
	.byte 0
/* end data */

.data
.balign 8
glo6:
	.ascii "\n"
	.byte 0
/* end data */

.data
.balign 8
glo7:
	.ascii "\n"
	.byte 0
/* end data */

.data
.balign 8
glo8:
	.ascii "found %d solutions\n"
	.byte 0
/* end data */

.section .note.GNU-stack,"",@progbits
