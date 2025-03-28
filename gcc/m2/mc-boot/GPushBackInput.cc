/* do not edit automatically generated by mc from PushBackInput.  */
/* PushBackInput.mod provides a method for pushing back and consuming input.

Copyright (C) 2001-2025 Free Software Foundation, Inc.
Contributed by Gaius Mulley <gaius.mulley@southwales.ac.uk>.

This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GNU Modula-2 is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include <stdbool.h>
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#if defined(__cplusplus)
#   undef NULL
#   define NULL 0
#endif
#define _PushBackInput_C

#include "GPushBackInput.h"
#   include "GFIO.h"
#   include "GDynamicStrings.h"
#   include "GASCII.h"
#   include "GDebug.h"
#   include "GStrLib.h"
#   include "GNumberIO.h"
#   include "GStrIO.h"
#   include "GStdIO.h"
#   include "Glibc.h"

#   define MaxPushBackStack 8192
#   define MaxFileName 4096
typedef struct PushBackInput__T2_a PushBackInput__T2;

typedef struct PushBackInput__T3_a PushBackInput__T3;

struct PushBackInput__T2_a { char array[MaxFileName+1]; };
struct PushBackInput__T3_a { char array[MaxPushBackStack+1]; };
static PushBackInput__T2 FileName;
static PushBackInput__T3 CharStack;
static unsigned int ExitStatus;
static unsigned int Column;
static unsigned int StackPtr;
static unsigned int LineNo;
static bool Debugging;

/*
   Open - opens a file for reading.
*/

extern "C" FIO_File PushBackInput_Open (const char *a_, unsigned int _a_high);

/*
   GetCh - gets a character from either the push back stack or
           from file, f.
*/

extern "C" char PushBackInput_GetCh (FIO_File f);

/*
   PutCh - pushes a character onto the push back stack, it also
           returns the character which has been pushed.
*/

extern "C" char PushBackInput_PutCh (char ch);

/*
   PutString - pushes a string onto the push back stack.
*/

extern "C" void PushBackInput_PutString (const char *a_, unsigned int _a_high);

/*
   PutStr - pushes a dynamic string onto the push back stack.
            The string, s, is not deallocated.
*/

extern "C" void PushBackInput_PutStr (DynamicStrings_String s);

/*
   Error - emits an error message with the appropriate file, line combination.
*/

extern "C" void PushBackInput_Error (const char *a_, unsigned int _a_high);

/*
   WarnError - emits an error message with the appropriate file, line combination.
               It does not terminate but when the program finishes an exit status of
               1 will be issued.
*/

extern "C" void PushBackInput_WarnError (const char *a_, unsigned int _a_high);

/*
   WarnString - emits an error message with the appropriate file, line combination.
                It does not terminate but when the program finishes an exit status of
                1 will be issued.
*/

extern "C" void PushBackInput_WarnString (DynamicStrings_String s);

/*
   Close - closes the opened file.
*/

extern "C" void PushBackInput_Close (FIO_File f);

/*
   GetExitStatus - returns the exit status which will be 1 if any warnings were issued.
*/

extern "C" unsigned int PushBackInput_GetExitStatus (void);

/*
   SetDebug - sets the debug flag on or off.
*/

extern "C" void PushBackInput_SetDebug (bool d);

/*
   GetColumnPosition - returns the column position of the current character.
*/

extern "C" unsigned int PushBackInput_GetColumnPosition (void);

/*
   GetCurrentLine - returns the current line number.
*/

extern "C" unsigned int PushBackInput_GetCurrentLine (void);

/*
   ErrChar - writes a char, ch, to stderr.
*/

static void ErrChar (char ch);

/*
   Init - initialize global variables.
*/

static void Init (void);


/*
   ErrChar - writes a char, ch, to stderr.
*/

static void ErrChar (char ch)
{
  FIO_WriteChar (FIO_StdErr, ch);
}


/*
   Init - initialize global variables.
*/

static void Init (void)
{
  ExitStatus = 0;
  StackPtr = 0;
  LineNo = 1;
  Column = 0;
}


/*
   Open - opens a file for reading.
*/

extern "C" FIO_File PushBackInput_Open (const char *a_, unsigned int _a_high)
{
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  Init ();
  StrLib_StrCopy ((const char *) a, _a_high, (char *) &FileName.array[0], MaxFileName);
  return FIO_OpenToRead ((const char *) a, _a_high);
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   GetCh - gets a character from either the push back stack or
           from file, f.
*/

extern "C" char PushBackInput_GetCh (FIO_File f)
{
  char ch;

  if (StackPtr > 0)
    {
      StackPtr -= 1;
      if (Debugging)
        {
          StdIO_Write (CharStack.array[StackPtr]);
        }
      return CharStack.array[StackPtr];
    }
  else
    {
      if ((FIO_EOF (f)) || (! (FIO_IsNoError (f))))
        {
          ch = ASCII_nul;
        }
      else
        {
          do {
            ch = FIO_ReadChar (f);
          } while (! (((ch != ASCII_cr) || (FIO_EOF (f))) || (! (FIO_IsNoError (f)))));
          if (ch == ASCII_lf)
            {
              Column = 0;
              LineNo += 1;
            }
          else
            {
              Column += 1;
            }
        }
      if (Debugging)
        {
          StdIO_Write (ch);
        }
      return ch;
    }
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   PutCh - pushes a character onto the push back stack, it also
           returns the character which has been pushed.
*/

extern "C" char PushBackInput_PutCh (char ch)
{
  if (StackPtr < MaxPushBackStack)
    {
      CharStack.array[StackPtr] = ch;
      StackPtr += 1;
    }
  else
    {
      Debug_Halt ((const char *) "max push back stack exceeded, increase MaxPushBackStack", 55, (const char *) "../../gcc/m2/gm2-libs/PushBackInput.mod", 39, (const char *) "PutCh", 5, 151);
    }
  return ch;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   PutString - pushes a string onto the push back stack.
*/

extern "C" void PushBackInput_PutString (const char *a_, unsigned int _a_high)
{
  unsigned int l;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  l = StrLib_StrLen ((const char *) a, _a_high);
  while (l > 0)
    {
      l -= 1;
      if ((PushBackInput_PutCh (a[l])) != a[l])
        {
          Debug_Halt ((const char *) "assert failed", 13, (const char *) "../../gcc/m2/gm2-libs/PushBackInput.mod", 39, (const char *) "PutString", 9, 132);
        }
    }
}


/*
   PutStr - pushes a dynamic string onto the push back stack.
            The string, s, is not deallocated.
*/

extern "C" void PushBackInput_PutStr (DynamicStrings_String s)
{
  unsigned int i;

  i = DynamicStrings_Length (s);
  while (i > 0)
    {
      i -= 1;
      if ((PushBackInput_PutCh (DynamicStrings_char (s, static_cast<int> (i)))) != (DynamicStrings_char (s, static_cast<int> (i))))
        {
          Debug_Halt ((const char *) "assert failed", 13, (const char *) "../../gcc/m2/gm2-libs/PushBackInput.mod", 39, (const char *) "PutStr", 6, 113);
        }
    }
}


/*
   Error - emits an error message with the appropriate file, line combination.
*/

extern "C" void PushBackInput_Error (const char *a_, unsigned int _a_high)
{
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  StdIO_PushOutput ((StdIO_ProcWrite) {(StdIO_ProcWrite_t) ErrChar});
  StrIO_WriteString ((const char *) &FileName.array[0], MaxFileName);
  StdIO_Write (':');
  NumberIO_WriteCard (LineNo, 0);
  StdIO_Write (':');
  StrIO_WriteString ((const char *) a, _a_high);
  StrIO_WriteLn ();
  StdIO_PopOutput ();
  FIO_Close (FIO_StdErr);
  libc_exit (1);
}


/*
   WarnError - emits an error message with the appropriate file, line combination.
               It does not terminate but when the program finishes an exit status of
               1 will be issued.
*/

extern "C" void PushBackInput_WarnError (const char *a_, unsigned int _a_high)
{
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  StdIO_PushOutput ((StdIO_ProcWrite) {(StdIO_ProcWrite_t) ErrChar});
  StrIO_WriteString ((const char *) &FileName.array[0], MaxFileName);
  StdIO_Write (':');
  NumberIO_WriteCard (LineNo, 0);
  StdIO_Write (':');
  StrIO_WriteString ((const char *) a, _a_high);
  StrIO_WriteLn ();
  StdIO_PopOutput ();
  ExitStatus = 1;
}


/*
   WarnString - emits an error message with the appropriate file, line combination.
                It does not terminate but when the program finishes an exit status of
                1 will be issued.
*/

extern "C" void PushBackInput_WarnString (DynamicStrings_String s)
{
  typedef char *WarnString__T1;

  WarnString__T1 p;

  p = static_cast<WarnString__T1> (DynamicStrings_string (s));
  StrIO_WriteString ((const char *) &FileName.array[0], MaxFileName);
  StdIO_Write (':');
  NumberIO_WriteCard (LineNo, 0);
  StdIO_Write (':');
  do {
    if (p != NULL)
      {
        if ((*p) == ASCII_lf)
          {
            StrIO_WriteLn ();
            StrIO_WriteString ((const char *) &FileName.array[0], MaxFileName);
            StdIO_Write (':');
            NumberIO_WriteCard (LineNo, 0);
            StdIO_Write (':');
          }
        else
          {
            StdIO_Write ((*p));
          }
        p += 1;
      }
  } while (! ((p == NULL) || ((*p) == ASCII_nul)));
  ExitStatus = 1;
}


/*
   Close - closes the opened file.
*/

extern "C" void PushBackInput_Close (FIO_File f)
{
  FIO_Close (f);
}


/*
   GetExitStatus - returns the exit status which will be 1 if any warnings were issued.
*/

extern "C" unsigned int PushBackInput_GetExitStatus (void)
{
  return ExitStatus;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   SetDebug - sets the debug flag on or off.
*/

extern "C" void PushBackInput_SetDebug (bool d)
{
  Debugging = d;
}


/*
   GetColumnPosition - returns the column position of the current character.
*/

extern "C" unsigned int PushBackInput_GetColumnPosition (void)
{
  if (StackPtr > Column)
    {
      return 0;
    }
  else
    {
      return Column-StackPtr;
    }
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}


/*
   GetCurrentLine - returns the current line number.
*/

extern "C" unsigned int PushBackInput_GetCurrentLine (void)
{
  return LineNo;
  /* static analysis guarentees a RETURN statement will be used before here.  */
  __builtin_unreachable ();
}

extern "C" void _M2_PushBackInput_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], __attribute__((unused)) char *envp[])
{
  PushBackInput_SetDebug (false);
  Init ();
}

extern "C" void _M2_PushBackInput_fini (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], __attribute__((unused)) char *envp[])
{
}
