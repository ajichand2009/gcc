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
 * @file list_update_map_/find_fn_imps.hpp
 * Contains implementations of lu_map_.
 */

#ifdef PB_DS_CLASS_C_DEC

PB_DS_CLASS_T_DEC
inline typename PB_DS_CLASS_C_DEC::entry_pointer
PB_DS_CLASS_C_DEC::
find_imp(key_const_reference r_key) const
{
  if (m_p_l == 0)
    return 0;
  if (s_eq_fn(r_key, PB_DS_V2F(m_p_l->m_value)))
    {
      apply_update(m_p_l, s_metadata_type_indicator);
      PB_DS_CHECK_KEY_EXISTS(r_key)
      return m_p_l;
    }

  entry_pointer p_l = m_p_l;
  while (p_l->m_p_next != 0)
    {
      entry_pointer p_next = p_l->m_p_next;
      if (s_eq_fn(r_key, PB_DS_V2F(p_next->m_value)))
        {
	  if (apply_update(p_next, s_metadata_type_indicator))
            {
	      p_l->m_p_next = p_next->m_p_next;
	      p_next->m_p_next = m_p_l;
	      m_p_l = p_next;
	      return m_p_l;
            }
	  return p_next;
        }
      else
	p_l = p_next;
    }

  PB_DS_CHECK_KEY_DOES_NOT_EXIST(r_key)
  return 0;
}

PB_DS_CLASS_T_DEC
template<typename Metadata>
inline bool
PB_DS_CLASS_C_DEC::
apply_update(entry_pointer p_l, type_to_type<Metadata>)
{ return s_update_policy(p_l->m_update_metadata); }

PB_DS_CLASS_T_DEC
inline bool
PB_DS_CLASS_C_DEC::
apply_update(entry_pointer, type_to_type<null_type>)
{ return s_update_policy(s_null_type); }

#endif
