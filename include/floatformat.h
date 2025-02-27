/* IEEE floating point support declarations, for GDB, the GNU Debugger.
   Copyright (C) 1991-2025 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

#if !defined (FLOATFORMAT_H)
#define FLOATFORMAT_H 1

#include "ansidecl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* A floatformat consists of a sign bit, an exponent and a mantissa.  Once the
   bytes are concatenated according to the byteorder flag, then each of those
   fields is contiguous.  We number the bits with 0 being the most significant
   (i.e. BITS_BIG_ENDIAN type numbering), and specify which bits each field
   contains with the *_start and *_len fields.  */

/* What is the order of the bytes?  */

enum floatformat_byteorders {
  /* Standard little endian byte order.
     EX: 1.2345678e10 => 00 00 80 c5 e0 fe 06 42 */
  floatformat_little,

  /* Standard big endian byte order.
     EX: 1.2345678e10 => 42 06 fe e0 c5 80 00 00 */
  floatformat_big,

  /* Little endian byte order but big endian word order.
     EX: 1.2345678e10 => e0 fe 06 42 00 00 80 c5 */
  floatformat_littlebyte_bigword,

  /* VAX byte order.  Little endian byte order with 16-bit words.  The
     following example is an illustration of the byte order only; VAX
     doesn't have a fully IEEE compliant floating-point format.
     EX: 1.2345678e10 => 80 c5 00 00 06 42 e0 fe */
  floatformat_vax
};

enum floatformat_intbit { floatformat_intbit_yes, floatformat_intbit_no };

struct floatformat
{
  enum floatformat_byteorders byteorder;
  unsigned int totalsize;	/* Total size of number in bits */

  /* Sign bit is always one bit long.  1 means negative, 0 means positive.  */
  unsigned int sign_start;

  unsigned int exp_start;
  unsigned int exp_len;
  /* Bias added to a "true" exponent to form the biased exponent.  It
     is intentionally signed as, otherwize, -exp_bias can turn into a
     very large number (e.g., given the exp_bias of 0x3fff and a 64
     bit long, the equation (long)(1 - exp_bias) evaluates to
     4294950914) instead of -16382).  */
  int exp_bias;
  /* Exponent value which indicates NaN.  This is the actual value stored in
     the float, not adjusted by the exp_bias.  This usually consists of all
     one bits.  */
  unsigned int exp_nan;

  unsigned int man_start;
  unsigned int man_len;

  /* Is the integer bit explicit or implicit?  */
  enum floatformat_intbit intbit;

  /* Internal name for debugging. */
  const char *name;

  /* Validator method.  */
  int (*is_valid) (const struct floatformat *fmt, const void *from);

  /* Is the format actually the sum of two smaller floating point
     formats (IBM long double, as described in
     libgcc/config/rs6000/ibm-ldouble-format)?  If so, this is the
     smaller format in question, and the fields sign_start through
     intbit describe the first half.  If not, this is NULL.  */
  const struct floatformat *split_half;
};

/* floatformats for IEEE half, single, double and quad, big and little endian.  */

extern const struct floatformat floatformat_ieee_half_big;
extern const struct floatformat floatformat_ieee_half_little;
extern const struct floatformat floatformat_ieee_single_big;
extern const struct floatformat floatformat_ieee_single_little;
extern const struct floatformat floatformat_ieee_double_big;
extern const struct floatformat floatformat_ieee_double_little;
extern const struct floatformat floatformat_ieee_quad_big;
extern const struct floatformat floatformat_ieee_quad_little;

/* floatformat for ARM IEEE double, little endian bytes and big endian words */

extern const struct floatformat floatformat_ieee_double_littlebyte_bigword;

/* floatformats for VAX.  */

extern const struct floatformat floatformat_vax_f;
extern const struct floatformat floatformat_vax_d;
extern const struct floatformat floatformat_vax_g;

/* floatformats for various extendeds.  */

extern const struct floatformat floatformat_i387_ext;
extern const struct floatformat floatformat_m68881_ext;
extern const struct floatformat floatformat_i960_ext;
extern const struct floatformat floatformat_m88110_ext;
extern const struct floatformat floatformat_m88110_harris_ext;
extern const struct floatformat floatformat_arm_ext_big;
extern const struct floatformat floatformat_arm_ext_littlebyte_bigword;
/* IA-64 Floating Point register spilt into memory.  */
extern const struct floatformat floatformat_ia64_spill_big;
extern const struct floatformat floatformat_ia64_spill_little;
/* IBM long double (double+double).  */
extern const struct floatformat floatformat_ibm_long_double_big;
extern const struct floatformat floatformat_ibm_long_double_little;
/* bfloat16.  */
extern const struct floatformat floatformat_bfloat16_big;
extern const struct floatformat floatformat_bfloat16_little;

/* Convert from FMT to a double.
   FROM is the address of the extended float.
   Store the double in *TO.  */

extern void
floatformat_to_double (const struct floatformat *, const void *, double *);

/* The converse: convert the double *FROM to FMT
   and store where TO points.  */

extern void
floatformat_from_double (const struct floatformat *, const double *, void *);

/* Return non-zero iff the data at FROM is a valid number in format FMT.  */

extern int
floatformat_is_valid (const struct floatformat *fmt, const void *from);

#ifdef __cplusplus
}
#endif

#endif	/* defined (FLOATFORMAT_H) */
