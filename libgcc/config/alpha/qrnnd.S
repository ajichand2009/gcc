 # Alpha 21064 __udiv_qrnnd
 # Copyright (C) 1992-2025 Free Software Foundation, Inc.

 # This file is part of GCC.

 # The GNU MP Library is free software; you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation; either version 3 of the License, or (at your
 # option) any later version.

 # This file is distributed in the hope that it will be useful, but
 # WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 # or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 # License for more details.

 # Under Section 7 of GPL version 3, you are granted additional
 # permissions described in the GCC Runtime Library Exception, version
 # 3.1, as published by the Free Software Foundation.

 # You should have received a copy of the GNU General Public License and
 # a copy of the GCC Runtime Library Exception along with this program;
 # see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
 # <http://www.gnu.org/licenses/>.

#ifdef __ELF__
.section .note.GNU-stack,""
#endif

        .set noreorder
        .set noat

	.text

	.globl __udiv_qrnnd
	.ent __udiv_qrnnd
#ifdef __VMS__
__udiv_qrnnd..en:
	.frame $29,0,$26,0
	.prologue
#else
__udiv_qrnnd:
	.frame $30,0,$26,0
	.prologue 0
#endif

#define cnt	$2
#define tmp	$3
#define rem_ptr	$16
#define n1	$17
#define n0	$18
#define d	$19
#define qb	$20
#define AT	$at

	ldiq	cnt,16
	blt	d,$largedivisor

$loop1:	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	d,n1,qb
	subq	n1,d,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	d,n1,qb
	subq	n1,d,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	d,n1,qb
	subq	n1,d,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	d,n1,qb
	subq	n1,d,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	subq	cnt,1,cnt
	bgt	cnt,$loop1
	stq	n1,0(rem_ptr)
	bis	$31,n0,$0
	ret	$31,($26),1

$largedivisor:
	and	n0,1,$4

	srl	n0,1,n0
	sll	n1,63,tmp
	or	tmp,n0,n0
	srl	n1,1,n1

	and	d,1,$6
	srl	d,1,$5
	addq	$5,$6,$5

$loop2:	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	$5,n1,qb
	subq	n1,$5,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	$5,n1,qb
	subq	n1,$5,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	$5,n1,qb
	subq	n1,$5,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	cmplt	n0,0,tmp
	addq	n1,n1,n1
	bis	n1,tmp,n1
	addq	n0,n0,n0
	cmpule	$5,n1,qb
	subq	n1,$5,tmp
	cmovne	qb,tmp,n1
	bis	n0,qb,n0
	subq	cnt,1,cnt
	bgt	cnt,$loop2

	addq	n1,n1,n1
	addq	$4,n1,n1
	bne	$6,$Odd
	stq	n1,0(rem_ptr)
	bis	$31,n0,$0
	ret	$31,($26),1

$Odd:
	/* q' in n0. r' in n1 */
	addq	n1,n0,n1

	cmpult	n1,n0,tmp	# tmp := carry from addq
	subq	n1,d,AT
	addq	n0,tmp,n0
	cmovne	tmp,AT,n1

	cmpult	n1,d,tmp
	addq	n0,1,AT
	cmoveq	tmp,AT,n0
	subq	n1,d,AT
	cmoveq	tmp,AT,n1

	stq	n1,0(rem_ptr)
	bis	$31,n0,$0
	ret	$31,($26),1

#ifdef __VMS__
	.link
	.align 3
__udiv_qrnnd:
	.pdesc	__udiv_qrnnd..en,null
#endif
	.end	__udiv_qrnnd
