/* { dg-do compile { target { ! riscv_abi_e } } } */
/* { dg-options "-march=rv32gc_xtheadfmemidx" { target { rv32 } } } */
/* { dg-options "-march=rv64gc_xtheadfmemidx" { target { rv64 } } } */

#ifndef __riscv_xtheadfmemidx
#error "Feature macro not defined"
#endif

int
foo (int a)
{
  return a;
}

