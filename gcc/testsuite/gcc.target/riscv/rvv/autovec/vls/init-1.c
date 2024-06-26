/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_zvfh -mabi=lp64d -O3 -mrvv-max-lmul=m8" } */

#include "def.h"

DEF_INIT (v2qi, int8_t, 2, 0, 1)
DEF_INIT (v4qi, int8_t, 4, 0, 1, 2, 3)
DEF_INIT (v8qi, int8_t, 8, 0, 1, 2, 3, 4, 5, 6, 7)
DEF_INIT (v16qi, int8_t, 16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	  15)
DEF_INIT (v32qi, int8_t, 32, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
DEF_INIT (v64qi, int8_t, 64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63)
DEF_INIT (v128qi, int8_t, 128, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
	  66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82,
	  83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
	  100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
	  114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127)
DEF_INIT (v2uqi, uint8_t, 2, 0, 1)
DEF_INIT (v4uqi, uint8_t, 4, 0, 1, 2, 3)
DEF_INIT (v8uqi, uint8_t, 8, 0, 1, 2, 3, 4, 5, 6, 7)
DEF_INIT (v16uqi, uint8_t, 16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	  15)
DEF_INIT (v32uqi, uint8_t, 32, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
DEF_INIT (v64uqi, uint8_t, 64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63)
DEF_INIT (v128uqi, uint8_t, 128, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	  14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
	  31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
	  65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81,
	  82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98,
	  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
	  113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,
	  127)

/* { dg-final { scan-assembler-times {vid\.v} 14 } } */
