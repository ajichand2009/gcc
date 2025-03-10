// -*- C++ -*-

// Copyright (C) 2005-2025 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation; either version 3, or (at your option) any later
// version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

// Copyright (C) 2004 Ami Tavory and Vladimir Dreizin, IBM-HRL.

// Permission to use, copy, modify, sell, and distribute this software
// is hereby granted without fee, provided that the above copyright
// notice appears in all copies, and that both that copyright notice
// and this permission notice appear in supporting documentation. None
// of the above authors, nor IBM Haifa Research Laboratories, make any
// representation about the suitability of this software for any
// purpose. It is provided "as is" without express or implied
// warranty.

/**
 * @file ov_tree_map_/insert_fn_imps.hpp
 * Contains an implementation class for ov_tree_.
 */

#ifdef PB_DS_CLASS_C_DEC

PB_DS_CLASS_T_DEC
void
PB_DS_CLASS_C_DEC::
reallocate_metadata(null_node_update_pointer, size_type)
{ }

PB_DS_CLASS_T_DEC
template<typename Node_Update_>
void
PB_DS_CLASS_C_DEC::
reallocate_metadata(Node_Update_* , size_type new_size)
{
  metadata_pointer a_new_metadata_vec =(new_size == 0) ? 0 : s_metadata_alloc.allocate(new_size);

  if (m_a_metadata != 0)
    {
      for (size_type i = 0; i < m_size; ++i)
	m_a_metadata[i].~metadata_type();
      s_metadata_alloc.deallocate(m_a_metadata, m_size);
    }
  std::swap(m_a_metadata, a_new_metadata_vec);
}

#endif
