// { dg-additional-options "-fmodules-ts" }
import Foo;

void One ()
{
  Frob (0, 0, 0L);
  Frob (0, 0L, 0);
  Frob (0L, 0, 0); // { dg-error "ambiguous" }
  // { dg-regexp {candidate 1: 'int Frob@Foo\(int, long int, int\)'} }
  // { dg-regexp {candidate 2: 'int Frob@Foo\(int, int, long int\)'} }
}

import Bar;

void Two ()
{
  Frob (0L, 0, 0);
  Frob (0, 0, 0); // { dg-error "ambiguous" }
  // { dg-regexp {candidate 1: 'int Frob@Foo\(int, long int, int\)'} }
  // { dg-regexp {candidate 2: 'int Frob@Foo\(int, int, long int\)'} }
  // { dg-regexp {candidate 3: 'int Frob@Bar\(long int, int, int\)'} }
}
