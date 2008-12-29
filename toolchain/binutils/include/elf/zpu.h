/* ZPU ELF support for BFD.
   Copyright 1995, 1997, 1998, 2000, 2001 Free Software Foundation, Inc.
   Contributed by Doug Evans, (dje@cygnus.com)

This file is part of BFD, the Binary File Descriptor library.

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
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* This file holds definitions specific to the ZPU ELF ABI.  */

#ifndef _ELF_ZPU_H
#define _ELF_ZPU_H

#include "elf/reloc-macros.h"

/* Relocations.  */

START_RELOC_NUMBERS (elf_zpu_reloc_type)
  RELOC_NUMBER (R_ZPU_NONE, 0)
  RELOC_NUMBER (R_ZPU_32, 1)
  RELOC_NUMBER (R_ZPU_8, 2)
  RELOC_NUMBER (R_ZPU_16, 3)
  RELOC_NUMBER (R_ZPU_8_PCREL, 4)
  RELOC_NUMBER (R_ZPU_16_PCREL, 5)
  RELOC_NUMBER (R_ZPU_24_PCREL, 6)
  RELOC_NUMBER (R_ZPU_32_PCREL, 7)
  RELOC_NUMBER (R_ZPU_IM_7_PCREL, 8)
  RELOC_NUMBER (R_ZPU_IM_14_PCREL, 9)
  RELOC_NUMBER (R_ZPU_IM_21_PCREL, 10)
  RELOC_NUMBER (R_ZPU_IM_28_PCREL, 11)
  RELOC_NUMBER (R_ZPU_IM_32_PCREL, 12)
  RELOC_NUMBER (R_ZPU_IM_7, 13)
  RELOC_NUMBER (R_ZPU_IM_14, 14)
  RELOC_NUMBER (R_ZPU_IM_21, 15)
  RELOC_NUMBER (R_ZPU_IM_28, 16)
  RELOC_NUMBER (R_ZPU_IM_32, 17)
  RELOC_NUMBER (R_ZPU_IM_14_NONRELAX, 18)
END_RELOC_NUMBERS (R_ZPU_max)

/* Processor specific flags for the ELF header e_flags field.  */

/* ABI identification.  */
#define EF_ZPU_ABI  0x00000000F


/* Four bit ZPU machine type field.  */

#define EF_ZPU_MACH 0x00000001

/* Various CPU types.  */

#define E_ZPU_MACH_ZPU 0

/* Leave bits 0xf0 alone in case we ever have more than 16 cpu types.  */


#endif /* _ELF_ZPU_H */
