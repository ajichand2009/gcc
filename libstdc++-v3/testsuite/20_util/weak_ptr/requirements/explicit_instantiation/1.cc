// { dg-do compile { target c++11 } }
// { dg-require-effective-target hosted }

// Copyright (C) 2006-2025 Free Software Foundation, Inc.
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

// 20.6.6.2 Template class shared_ptr [util.smartptr.shared]

#include <memory>
#include <testsuite_tr1.h>

using namespace __gnu_test;
template class std::weak_ptr<int>;
template class std::weak_ptr<void>;
template class std::weak_ptr<ClassType>;
template class std::weak_ptr<IncompleteClass>;

#if __cpp_lib_shared_ptr_arrays >= 201611L
template class std::weak_ptr<ClassType []>;
template class std::weak_ptr<ClassType [42]>;
template class std::weak_ptr<ClassType const []>;
template class std::weak_ptr<ClassType const [42]>;

template class std::weak_ptr<IncompleteClass []>;
template class std::weak_ptr<IncompleteClass [42]>;
template class std::weak_ptr<IncompleteClass const []>;
template class std::weak_ptr<IncompleteClass const [42]>;
#endif
