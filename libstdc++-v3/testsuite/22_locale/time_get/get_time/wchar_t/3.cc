// 2001-09-21 Benjamin Kosnik  <bkoz@redhat.com>

// Copyright (C) 2001-2025 Free Software Foundation, Inc.
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

// 22.2.5.1.1 time_get members

#include <locale>
#include <sstream>
#include <testsuite_hooks.h>

void test03()
{
  using namespace std;

  // Check time_get works with other iterators besides streambuf
  // input iterators.
  typedef wstring::const_iterator iter_type;
  typedef time_get<wchar_t, iter_type> time_get_type;
  const ios_base::iostate goodbit = ios_base::goodbit;
  ios_base::iostate err = goodbit;
  const locale loc_c = locale::classic();

  // Create "C" time objects
  const tm time_sanity = __gnu_test::test_tm(0, 0, 12, 26, 5, 97, 2, 0, 0);
  tm tm1;

  wistringstream iss; 
  iss.imbue(locale(loc_c, new time_get_type));

  // Iterator advanced, state, output.
  const time_get_type& tg = use_facet<time_get_type>(iss.getloc());

  // Cindy Sherman's Untitled Film Stills
  // June 26-September 2, 1997
  const wstring str = L"12:00:00 06/26/97 Tuesday September 1997 Cindy Sherman";
 
  // 01 get_time
  wstring res1;
  err = goodbit;
  iter_type end1 = tg.get_time(str.begin(), str.end(), iss, err, &tm1);
  wstring rem1(end1, str.end());
  VERIFY( err == goodbit );
  VERIFY( tm1.tm_sec == time_sanity.tm_sec );
  VERIFY( tm1.tm_min == time_sanity.tm_min );
  VERIFY( tm1.tm_hour == time_sanity.tm_hour );
  VERIFY( rem1 ==  L" 06/26/97 Tuesday September 1997 Cindy Sherman" );
}

int main()
{
  test03();
  return 0;
}
