/* { dg-do compile } */
/* { dg-options "-O -fno-stack-clash-protection -g" } */
/* { dg-final { check-function-bodies "**" "" "" { target lp64 } } } */

#include <arm_sve.h>

/*
** callee_int:
**	ptrue	p3\.b, all
**	ld1b	(z(?:2[4-9]|3[0-1]).b), p3/z, \[x4\]
**	st1b	\1, p2, \[x0\]
**	st1b	z4\.b, p1, \[x0\]
**	st1h	z5\.h, p1, \[x1\]
**	st1w	z6\.s, p1, \[x2\]
**	st1d	z7\.d, p1, \[x3\]
**	st1b	z0\.b, p0, \[x0\]
**	st1h	z1\.h, p0, \[x1\]
**	st1w	z2\.s, p0, \[x2\]
**	st1d	z3\.d, p0, \[x3\]
**	ret
*/
void __attribute__((noipa))
callee_int (int8_t *x0, int16_t *x1, int32_t *x2, int64_t *x3,
	    svint8_t z0, svint16_t z1, svint32_t z2, svint64_t z3,
	    svint8_t z4, svint16_t z5, svint32_t z6, svint64_t z7,
	    svint8_t z8,
	    svbool_t p0, svbool_t p1, svbool_t p2)
{
  svst1 (p2, x0, z8);
  svst1 (p1, x0, z4);
  svst1 (p1, x1, z5);
  svst1 (p1, x2, z6);
  svst1 (p1, x3, z7);
  svst1 (p0, x0, z0);
  svst1 (p0, x1, z1);
  svst1 (p0, x2, z2);
  svst1 (p0, x3, z3);
}

void __attribute__((noipa))
caller_int (int8_t *x0, int16_t *x1, int32_t *x2, int64_t *x3)
{
  callee_int (x0, x1, x2, x3,
	      svdup_s8 (0),
	      svdup_s16 (1),
	      svdup_s32 (2),
	      svdup_s64 (3),
	      svdup_s8 (4),
	      svdup_s16 (5),
	      svdup_s32 (6),
	      svdup_s64 (7),
	      svdup_s8 (8),
	      svptrue_pat_b8 (SV_VL1),
	      svptrue_pat_b16 (SV_VL2),
	      svptrue_pat_b32 (SV_VL3));
}

/* { dg-final { scan-assembler {\tmov(\tz0\.b|i\td0), #0\n} } } */
/* { dg-final { scan-assembler {\tmov\tz1\.h, #1\n} } } */
/* { dg-final { scan-assembler {\tmov\tz2\.s, #2\n} } } */
/* { dg-final { scan-assembler {\tmov\tz3\.d, #3\n} } } */
/* { dg-final { scan-assembler {\tmov\tz4\.b, #4\n} } } */
/* { dg-final { scan-assembler {\tmov\tz5\.h, #5\n} } } */
/* { dg-final { scan-assembler {\tmov\tz6\.s, #6\n} } } */
/* { dg-final { scan-assembler {\tmov\tz7\.d, #7\n} } } */
/* { dg-final { scan-assembler {\tmov\tx4, sp\n} } } */
/* { dg-final { scan-assembler {\tmov\t(z[0-9]+\.b), #8\n.*\tst1b\t\1, p[0-7], \[(?:x4|sp)\]\n} } } */
/* { dg-final { scan-assembler {\tptrue\tp0\.b, vl1\n} } } */
/* { dg-final { scan-assembler {\tptrue\tp1\.h, vl2\n} } } */
/* { dg-final { scan-assembler {\tptrue\tp2\.s, vl3\n} } } */
