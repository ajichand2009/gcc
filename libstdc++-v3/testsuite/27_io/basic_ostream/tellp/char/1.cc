// 2000-06-29 bkoz

// Copyright (C) 2000-2025 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// 27.6.2.4 basic_ostream seek members

// { dg-require-fileio "" }

#include <ostream>
#include <sstream>
#include <fstream>
#include <testsuite_hooks.h>

void test01()
{
  using namespace std;
  typedef ios::off_type off_type;
  typedef ios::pos_type pos_type;

  const char str_lit01[] = "ostream_seeks-1.txt";

  // out
  ostringstream ost1;
  pos_type p1 = ost1.tellp();

  ofstream ofs1;
  pos_type p2 = ofs1.tellp();

  // N.B. We implement the resolution of DR 453 and
  // ostringstream::tellp() doesn't fail.
  VERIFY( p1 == pos_type(off_type(0)) );
  VERIFY( p2 == pos_type(off_type(-1)) );

  // out
  // test ctors leave things in the same positions...
  ostringstream ost2("bob_marley:kaya");
  p1 = ost2.tellp();

  ofstream ofs2(str_lit01);
  p2 = ofs2.tellp();
 
  VERIFY( p1 == p2 );
}

int main()
{
  test01();
  return 0;
}
