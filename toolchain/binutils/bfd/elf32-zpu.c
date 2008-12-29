/* Zylin ZPU-specific support for 32-bit ELF
   Copyright 1999, 2000, 2001, 2002, 2003,2004 Free Software Foundation, Inc.
   Contributed by Oyvind Harboe (oyvind.harboe@zylin.com)

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

#include "bfd.h"
#include "sysdep.h"
#include "libbfd.h"
#include "elf-bfd.h"
#include "elf/zpu.h"
#include "libiberty.h"
#include <opcode/zpu.h>

static bfd_reloc_status_type
zpu_elf_ignore_reloc (bfd *abfd ATTRIBUTE_UNUSED,
                          arelent *reloc_entry,
                          asymbol *symbol ATTRIBUTE_UNUSED,
                          void *data ATTRIBUTE_UNUSED,
                          asection *input_section,
                          bfd *output_bfd,
                          char **error_message ATTRIBUTE_UNUSED);


/* This does not include any relocation information, but should be
   good enough for GDB or objdump to read the file.  */

static reloc_howto_type zpu_elf_howto_table [] =
{
	HOWTO (R_ZPU_NONE,			/* type */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 0,			/* bitsize */
	 FALSE,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 NULL,			/* special_function */
	 "ZPU_NONE",		/* name */
	 FALSE,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 FALSE),		/* pcrel_offset */
	 
  HOWTO (R_ZPU_32,		     /* type */
	 0,			     /* rightshift */
	 2,			     /* size (0 = byte, 1 = short, 2 = long) */
	 32,			     /* bitsize */
	 FALSE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_elf_generic_reloc,	     /* special_function */
	 "ZPU_32",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0xffffffff,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_8,		     /* type */
	 0,			     /* rightshift */
	 0,			     /* size (0 = byte, 1 = short, 2 = long) */
	 8,			     /* bitsize */
	 FALSE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_elf_generic_reloc,	     /* special_function */
	 "ZPU_8",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x000000ff,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_16,		     /* type */
	 0,			     /* rightshift */
	 1,			     /* size (0 = byte, 1 = short, 2 = long) */
	 16,			     /* bitsize */
	 FALSE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_elf_generic_reloc,	     /* special_function */
	 "ZPU_16",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x0000ffff,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_8_PCREL,		     /* type */
	 0,			     /* rightshift */
	 0,			     /* size (0 = byte, 1 = short, 2 = long) */
	 8,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_elf_generic_reloc,	     /* special_function */
	 "ZPU_8_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x000000ff,		     /* src_mask */
	 0x000000ff,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_16_PCREL,		     /* type */
	 0,			     /* rightshift */
	 1,			     /* size (0 = byte, 1 = short, 2 = long) */
	 16,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_elf_generic_reloc,	     /* special_function */
	 "ZPU_16_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x0000ffff,		     /* src_mask */
	 0x0000ffff,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_24_PCREL,		     /* type */
	 0,			     /* rightshift */
	 2,			     /* size (0 = byte, 1 = short, 2 = long) */
	 24,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_elf_generic_reloc,	     /* special_function */
	 "ZPU_24_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00ffffff,		     /* src_mask */
	 0x00ffffff,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_32_PCREL,		     /* type */
	 0,			     /* rightshift */
	 2,			     /* size (0 = byte, 1 = short, 2 = long) */
	 32,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 bfd_elf_generic_reloc,	     /* special_function */
	 "ZPU_32_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0xffffffff,		     /* src_mask */
	 0xffffffff,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_7_PCREL,		     /* type */
	 0,			     /* rightshift */
	 0,			     /* size (0 = byte, 1 = short, 2 = long) */
	 7,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_7_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x0000007f,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_14_PCREL,		     /* type */
	 0,			     /* rightshift */
	 1,			     /* size (0 = byte, 1 = short, 2 = long) */
	 14,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_14_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x00007f7f,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_21_PCREL,		     /* type */
	 0,			     /* rightshift */
	 2,			     /* size (0 = byte, 1 = short, 2 = long) */
	 21,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_21_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x007f7f7f,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_28_PCREL,		     /* type */
	 0,			     /* rightshift */
	 2,			     /* size (0 = byte, 1 = short, 2 = long) */
	 28,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_28_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x7f7f7f7f,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_32_PCREL,		     /* type */
	 0,			     /* rightshift */
	 3,			     /* size (0 = byte, 1 = short, 2 = long) */
	 32,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_32_PCREL",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x7f7f7f7f,		     /* dst_mask */
	 TRUE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_7,		     /* type */
	 0,			     /* rightshift */
	 0,			     /* size (0 = byte, 1 = short, 2 = long) */
	 7,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_7",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x0000007f,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_14,		     /* type */
	 0,			     /* rightshift */
	 1,			     /* size (0 = byte, 1 = short, 2 = long) */
	 14,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_14",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x00007f7f,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_21,		     /* type */
	 0,			     /* rightshift */
	 2,			     /* size (0 = byte, 1 = short, 2 = long) */
	 21,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_21",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x007f7f7f,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_28,		     /* type */
	 0,			     /* rightshift */
	 2,			     /* size (0 = byte, 1 = short, 2 = long) */
	 28,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_28",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x7f7f7f7f,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_32,		     /* type */
	 0,			     /* rightshift */
	 3,			     /* size (0 = byte, 1 = short, 2 = long) */
	 32,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_32",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x7f7f7f7f,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

  HOWTO (R_ZPU_IM_14_NONRELAX,		     /* type */
	 0,			     /* rightshift */
	 1,			     /* size (0 = byte, 1 = short, 2 = long) */
	 14,			     /* bitsize */
	 TRUE,			     /* pc_relative */
	 0,			     /* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 zpu_elf_ignore_reloc,	     /* special_function */
	 "ZPU_IM_14_NONRELAX",		     /* name */
	 FALSE,			     /* partial_inplace */
	 0x00000000,		     /* src_mask */
	 0x00007f7f,		     /* dst_mask */
	 FALSE),		     /* pcrel_offset */

};

static void elf_zpu_info_to_howto
  PARAMS ((bfd *, arelent *, Elf_Internal_Rela *));

static void
elf_zpu_info_to_howto (
     bfd *abfd ATTRIBUTE_UNUSED,
     arelent *bfd_reloc,
     Elf_Internal_Rela *elf_reloc ATTRIBUTE_UNUSED)
{
  unsigned int r_type;
  r_type = ELF32_R_TYPE (elf_reloc->r_info);
  bfd_reloc->howto = & zpu_elf_howto_table [r_type];
}


struct zpu_reloc_map
  {
    bfd_reloc_code_real_type bfd_reloc_val;
    unsigned char elf_reloc_val;
  };

static const struct zpu_reloc_map zpu_reloc_map[] =
  {
   {BFD_RELOC_NONE, R_ZPU_NONE},
   {BFD_RELOC_32, R_ZPU_32},
   {BFD_RELOC_8, R_ZPU_8},
   {BFD_RELOC_16, R_ZPU_16},
   {BFD_RELOC_8_PCREL, R_ZPU_8_PCREL},
   {BFD_RELOC_16_PCREL, R_ZPU_16_PCREL},
   {BFD_RELOC_24_PCREL, R_ZPU_24_PCREL},
   {BFD_RELOC_32_PCREL, R_ZPU_32_PCREL},
   {BFD_RELOC_ZPU_IM_7_PCREL, R_ZPU_IM_7_PCREL},
   {BFD_RELOC_ZPU_IM_14_PCREL, R_ZPU_IM_14_PCREL},
   {BFD_RELOC_ZPU_IM_21_PCREL, R_ZPU_IM_21_PCREL},
   {BFD_RELOC_ZPU_IM_28_PCREL, R_ZPU_IM_28_PCREL},
   {BFD_RELOC_ZPU_IM_32_PCREL, R_ZPU_IM_32_PCREL},
   {BFD_RELOC_ZPU_IM_7, R_ZPU_IM_7},
   {BFD_RELOC_ZPU_IM_14, R_ZPU_IM_14},
   {BFD_RELOC_ZPU_IM_21, R_ZPU_IM_21},
   {BFD_RELOC_ZPU_IM_28, R_ZPU_IM_28},
   {BFD_RELOC_ZPU_IM_32, R_ZPU_IM_32},
   {BFD_RELOC_ZPU_IM_14_NONRELAX, R_ZPU_IM_14_NONRELAX},
  };

static reloc_howto_type *
zpu_reloc_type_lookup (
     bfd *abfd ATTRIBUTE_UNUSED,
     bfd_reloc_code_real_type code)
{
  unsigned int i;

  for (i = 0;
       i < sizeof (zpu_reloc_map) / sizeof (struct zpu_reloc_map);
       i++)
    {
      if (zpu_reloc_map[i].bfd_reloc_val == code)
	return &zpu_elf_howto_table[zpu_reloc_map[i].elf_reloc_val];
    }

  return NULL;
}


static bfd_reloc_status_type
zpu_elf_ignore_reloc (bfd *abfd ATTRIBUTE_UNUSED,
                          arelent *reloc_entry,
                          asymbol *symbol ATTRIBUTE_UNUSED,
                          void *data ATTRIBUTE_UNUSED,
                          asection *input_section,
                          bfd *output_bfd,
                          char **error_message ATTRIBUTE_UNUSED)
{
  if (output_bfd != NULL)
    reloc_entry->address += input_section->output_offset;
  return bfd_reloc_ok;
}


static int checkRange(int val, int bits)
{
	int prevSign;
	prevSign=(val>>(bits-1))&1;
	if (prevSign)
	{
		return ((val>>bits)&0x7f)!=0x7f;
	} else
	{
		return ((val>>bits)&0x7f)!=0x00;
	}
}

static int emit7Bits(int val, int pos)
{
	return ((val>>pos)&0x7f)|0x80;
}

/* generate immediate sequence */
static int genImmediate(char *buffer, int val)
{
   	int first=1;
	int i,j;
	j=0;
	for (i=4; i>=0; i--)
	{
 		if (!first||(i==0)||checkRange(val, i*7))
 		{
 			buffer[j++]=emit7Bits(val, i*7);
 			first=0;
 		}
	}
	return j;
}





static int
compare_reloc (const void *e1, const void *e2)
{
  const Elf_Internal_Rela *i1 = (const Elf_Internal_Rela *) e1;
  const Elf_Internal_Rela *i2 = (const Elf_Internal_Rela *) e2;

  if (i1->r_offset == i2->r_offset)
    return 0;
  else
    return i1->r_offset < i2->r_offset ? -1 : 1;
}

/* Delete some bytes from a section while relaxing.  */

static void
zpu_elf_relax_delete_bytes (bfd *abfd, asection *sec,
                                bfd_vma addr, int count)
{
  Elf_Internal_Shdr *symtab_hdr;
  unsigned int sec_shndx;
  bfd_byte *contents;
  Elf_Internal_Rela *irel, *irelend;
  bfd_vma toaddr;
  Elf_Internal_Sym *isymbuf, *isym, *isymend;
  struct elf_link_hash_entry **sym_hashes;
  struct elf_link_hash_entry **end_hashes;
  unsigned int symcount;

  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  isymbuf = (Elf_Internal_Sym *) symtab_hdr->contents;

  sec_shndx = _bfd_elf_section_from_bfd_section (abfd, sec);

  contents = elf_section_data (sec)->this_hdr.contents;

  toaddr = sec->_cooked_size;

  irel = elf_section_data (sec)->relocs;
  irelend = irel + sec->reloc_count;

  /* Actually delete the bytes.  */
  memmove (contents + addr, contents + addr + count,
	   (size_t) (toaddr - addr - count));

  sec->_cooked_size -= count;

  /* Adjust all the relocs.  */
  for (irel = elf_section_data (sec)->relocs; irel < irelend; irel++)
    {
      /* Get the new reloc address.  */
      if ((irel->r_offset > addr
	   && irel->r_offset < toaddr))
	irel->r_offset -= count;

    }

  /* Adjust the local symbols defined in this section.  */
  isymend = isymbuf + symtab_hdr->sh_info;
  for (isym = isymbuf; isym < isymend; isym++)
    {
      if (isym->st_shndx == sec_shndx
	  && isym->st_value > addr
	  && isym->st_value <= toaddr)
	isym->st_value -= count;
    }

  /* Now adjust the global symbols defined in this section.  */
  symcount = (symtab_hdr->sh_size / sizeof (Elf32_External_Sym)
	      - symtab_hdr->sh_info);
  sym_hashes = elf_sym_hashes (abfd);
  end_hashes = sym_hashes + symcount;
  for (; sym_hashes < end_hashes; sym_hashes++)
    {
      struct elf_link_hash_entry *sym_hash = *sym_hashes;
      if ((sym_hash->root.type == bfd_link_hash_defined
	   || sym_hash->root.type == bfd_link_hash_defweak)
	  && sym_hash->root.u.def.section == sec
	  && sym_hash->root.u.def.value > addr
	  && sym_hash->root.u.def.value <= toaddr)
	{
	  sym_hash->root.u.def.value -= count;
	}
    }
}


static bfd_boolean
zpu_elf_relax_section (bfd *abfd, asection *sec,
                           struct bfd_link_info *link_info, bfd_boolean *again)
{
  Elf_Internal_Shdr *symtab_hdr;
  Elf_Internal_Shdr *shndx_hdr;
  Elf_Internal_Rela *internal_relocs;
  Elf_Internal_Rela *free_relocs = NULL;
  Elf_Internal_Rela *irel, *irelend;
  bfd_byte *contents = NULL;
  bfd_byte *free_contents = NULL;
  Elf32_External_Sym *free_extsyms = NULL;
  Elf_Internal_Sym *isymbuf = NULL;

  /* Assume nothing changes.  */
  *again = FALSE;


  /* We don't have to do anything for a relocatable link, if
     this section does not have relocs, or if this is not a
     code section.  */
  if (link_info->relocatable
      || (sec->flags & SEC_RELOC) == 0
      || sec->reloc_count == 0
      || (sec->flags & SEC_CODE) == 0)
    return TRUE;

  BFD_ASSERT (!link_info->relocatable);

  /* If this is the first time we have been called for this section,
     initialize the cooked size.  */
  if (sec->_cooked_size == 0)
    sec->_cooked_size = sec->_raw_size;

  symtab_hdr = &elf_tdata (abfd)->symtab_hdr;
  shndx_hdr = &elf_tdata (abfd)->symtab_shndx_hdr;

  /* Get a copy of the native relocations.  */
  internal_relocs = (_bfd_elf_link_read_relocs
		     (abfd, sec, (PTR) NULL, (Elf_Internal_Rela *) NULL,
		      link_info->keep_memory));
  if (internal_relocs == NULL)
    goto error_return;
  if (! link_info->keep_memory)
    free_relocs = internal_relocs;

#if 0
  /* Checking for branch relaxation relies on the relocations to
     be sorted on 'r_offset'.  This is not guaranteed so we must sort.  */
  qsort (internal_relocs, sec->reloc_count, sizeof (Elf_Internal_Rela),
         compare_reloc);
#endif

  /* Walk through them looking for relaxing opportunities.  */
  irelend = internal_relocs + sec->reloc_count;
  for (irel = internal_relocs; irel < irelend; irel++)
    {
      bfd_vma symval;
      bfd_vma value;
      Elf_Internal_Sym *isym;
      asection *sym_sec;
      int pcRel;
      int length;

      /* If this isn't something that can be relaxed, then ignore
	 this reloc.  */
	 switch (ELF32_R_TYPE (irel->r_info))
	 {
        case R_ZPU_IM_7_PCREL:
        case R_ZPU_IM_14_PCREL:
        case R_ZPU_IM_21_PCREL:
        case R_ZPU_IM_28_PCREL:
        case R_ZPU_IM_32_PCREL:
        pcRel=1;
        length=ELF32_R_TYPE (irel->r_info)-R_ZPU_IM_7_PCREL+1;
        break;
        
        case R_ZPU_IM_7:
        case R_ZPU_IM_14:
        case R_ZPU_IM_21:
        case R_ZPU_IM_28:
        case R_ZPU_IM_32:
        pcRel=0;
        length=ELF32_R_TYPE (irel->r_info)-R_ZPU_IM_7+1;
        break;
	 	default:
	 	/* not a relaxable symbol */
          continue;
	 }

      /* Get the section contents if we haven't done so already.  */
      if (contents == NULL)
	{
	  /* Get cached copy if it exists.  */
	  if (elf_section_data (sec)->this_hdr.contents != NULL)
	    contents = elf_section_data (sec)->this_hdr.contents;
	  else
	    {
	      /* Go get them off disk.  */
	      contents = (bfd_byte *) bfd_malloc (sec->_raw_size);
	      if (contents == NULL)
		goto error_return;
	      free_contents = contents;

	      if (! bfd_get_section_contents (abfd, sec, contents,
					      (file_ptr) 0, sec->_raw_size))
		goto error_return;
	    }
	}

	  /* Do nothing if this reloc is the last byte in the section.  */
	  if (irel->r_offset == sec->_cooked_size)
	  {
	    continue;
	  }

      /* Read this BFD's symbols if we haven't done so already.  */
      if (isymbuf == NULL && symtab_hdr->sh_info != 0)
	{
	  isymbuf = (Elf_Internal_Sym *) symtab_hdr->contents;
	  if (isymbuf == NULL)
	    isymbuf = bfd_elf_get_elf_syms (abfd, symtab_hdr,
					    symtab_hdr->sh_info, 0,
					    NULL, NULL, NULL);
	  if (isymbuf == NULL)
	    goto error_return;
	}




      /* Get the value of the symbol referred to by the reloc.  */
      if (ELF32_R_SYM (irel->r_info) < symtab_hdr->sh_info)
	{
	  /* A local symbol.  */
	  isym = isymbuf + ELF32_R_SYM (irel->r_info);
	  sym_sec = bfd_section_from_elf_index (abfd, isym->st_shndx);
	  
#if 1
	  /* KLUDGE!!! do not merge references to the first position in the section.
	   * 
	   * This has been observed to cause problems with rodata sections which
	   * are mergable.
	   * 
	   * The problem is that sym_sec->output_section->vma shows up as 0, which
	   * is wrong for this section.
	   */
	  if (!pcRel && (sym_sec->output_offset==0))
	  	continue;
#endif
	  symval = (isym->st_value
		    + sym_sec->output_section->vma
		    + sym_sec->output_offset);
	}
      else
	{
	  unsigned long indx;
	  struct elf_link_hash_entry *h;

	  /* An external symbol.  */
	  indx = ELF32_R_SYM (irel->r_info) - symtab_hdr->sh_info;
	  h = elf_sym_hashes (abfd)[indx];
	  BFD_ASSERT (h != NULL);
	  if (h->root.type != bfd_link_hash_defined
	      && h->root.type != bfd_link_hash_defweak)
	    {
	      continue;
	    }

          isym = 0;
          sym_sec = h->root.u.def.section;
	  symval = (h->root.u.def.value
		    + sym_sec->output_section->vma
		    + sym_sec->output_offset);
	}

      value = symval;
      
        {
        	int deleteNum;
        	int relocType;
        	int newLength;
			char buffer[10];
          if (pcRel)
          {
          	int size;
          	
			relocType=R_ZPU_IM_7_PCREL;
			value=symval + irel->r_addend;
   			  value -= (sec->output_section->vma
					+ sec->output_offset);
		      value -= irel->r_offset;
		      value += irel->r_addend;

			      /* this is tricky. We have to *precisely* figure out the reach backwards
			       * which depends on our size. Easiest is just to try all combinations.
			       */
			       size=1;
			       	for (;;)
					{
					newLength=genImmediate(buffer, value-size);
						if (size>=newLength)
						{
							/* Greater than or equal????? 
							 * 
							 * Consider 0x41. 
							 * 
							 * - With a single byte the total offset is 0x40, which is too
							 * big for a single byte immediate.
							 * 
							 * - With a two byte immediate, the total offset is 0x3f, which
							 * fits into a single byte immediate.
							 * 
							 * Remember that we are not inserting, but overwriting a fixed
							 * distance. 
							 * 
							 * On the second round these will shrink to their eventual
							 * single byte immediate pc relative size.
							 */
							break;
						}
						size++;
						if (size>5)
						{
							fprintf(stderr, "internal error: value %08x size %d newLength %d\n", value, size, newLength);
							abort();
						}
					}
          } else
          {
          	relocType=R_ZPU_IM_7;
				value=symval + irel->r_addend;
			newLength=genImmediate(buffer, value);
          }
          
          relocType+=newLength-1;
          deleteNum=length-newLength;
          /* we must never increase in size or the linker can go ga-ga */
#if 0
		/* KLUDGE!!! remove this assert for now as it causes false positives */
          BFD_ASSERT(deleteNum>=0);
#endif
			if (deleteNum>0)
			{
              /* Note that we've changed the relocation contents, etc.  */
              elf_section_data (sec)->relocs = internal_relocs;
              free_relocs = NULL;

              elf_section_data (sec)->this_hdr.contents = contents;
              free_contents = NULL;

              symtab_hdr->contents = (bfd_byte *) isymbuf;
              free_extsyms = NULL;
	
	          irel->r_info = ELF32_R_INFO (ELF32_R_SYM (irel->r_info), relocType);
	          zpu_elf_relax_delete_bytes (abfd, sec, irel->r_offset, deleteNum);
	          *again = TRUE;
			}
        }
        
        
    }


  if (free_relocs != NULL)
    {
      free (free_relocs);
      free_relocs = NULL;
    }

  if (free_contents != NULL)
    {
      if (! link_info->keep_memory)
	free (free_contents);
      else
	{
	  /* Cache the section contents for elf_link_input_bfd.  */
	  elf_section_data (sec)->this_hdr.contents = contents;
	}
      free_contents = NULL;
    }

  if (free_extsyms != NULL)
    {
      if (! link_info->keep_memory)
	free (free_extsyms);
      else
	{
	  /* Cache the symbols for elf_link_input_bfd.  */
	  symtab_hdr->contents = (unsigned char *) isymbuf;
	}
      free_extsyms = NULL;
    }

  return TRUE;

 error_return:
  if (free_relocs != NULL)
    free (free_relocs);
  if (free_contents != NULL)
    free (free_contents);
  if (free_extsyms != NULL)
    free (free_extsyms);
  return FALSE;
}


static bfd_boolean
zpu_get_relocation_value (bfd *input_bfd, struct bfd_link_info *info,
			      asection *input_section,
                              asection **local_sections,
                              Elf_Internal_Sym *local_syms,
                              Elf_Internal_Rela *rel,
                              const char **name,
                              bfd_vma *relocation)
{
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  unsigned long r_symndx;
  asection *sec;
  struct elf_link_hash_entry *h;
  Elf_Internal_Sym *sym;
  const char* stub_name = 0;

  symtab_hdr = &elf_tdata (input_bfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (input_bfd);

  r_symndx = ELF32_R_SYM (rel->r_info);

  /* This is a final link.  */
  h = NULL;
  sym = NULL;
  sec = NULL;
  if (r_symndx < symtab_hdr->sh_info)
    {
      sym = local_syms + r_symndx;
      sec = local_sections[r_symndx];
      *relocation = (sec->output_section->vma
                     + sec->output_offset
                     + sym->st_value);
    }
  else
    {
      bfd_boolean unresolved_reloc, warned;

      RELOC_FOR_GLOBAL_SYMBOL (info, input_bfd, input_section, rel,
			       r_symndx, symtab_hdr, sym_hashes,
			       h, sec, *relocation, unresolved_reloc, warned);

      stub_name = h->root.root.string;
    }

  if (h != NULL)
    *name = h->root.root.string;
  else
    {
      *name = (bfd_elf_string_from_elf_section
               (input_bfd, symtab_hdr->sh_link, sym->st_name));
      if (*name == NULL || **name == '\0')
        *name = bfd_section_name (input_bfd, sec);
    }

  return TRUE;
}


static bfd_boolean
elf32_zpu_relocate_section (bfd *output_bfd ATTRIBUTE_UNUSED,
                                struct bfd_link_info *info,
                                bfd *input_bfd, asection *input_section,
                                bfd_byte *contents, Elf_Internal_Rela *relocs,
                                Elf_Internal_Sym *local_syms,
                                asection **local_sections)
{
  Elf_Internal_Shdr *symtab_hdr;
  struct elf_link_hash_entry **sym_hashes;
  Elf_Internal_Rela *rel, *relend;
  const char *name;
  const struct elf_backend_data * const ebd = get_elf_backend_data (input_bfd);

  symtab_hdr = &elf_tdata (input_bfd)->symtab_hdr;
  sym_hashes = elf_sym_hashes (input_bfd);

  /* Get memory bank parameters.  */

  rel = relocs;
  relend = relocs + input_section->reloc_count;
  for (; rel < relend; rel++)
    {
      int r_type;
      arelent arel;
      reloc_howto_type *howto;
      unsigned long r_symndx;
      bfd_vma phys_addr;
      Elf_Internal_Sym *sym;
      asection *sec;
      bfd_vma relocation;
      bfd_reloc_status_type r = bfd_reloc_undefined;
      int pcrel;

      r_symndx = ELF32_R_SYM (rel->r_info);
      r_type = ELF32_R_TYPE (rel->r_info);


      if (info->relocatable)
	{
	  /* This is a relocatable link.  We don't have to change
	     anything, unless the reloc is against a section symbol,
	     in which case we have to adjust according to where the
	     section symbol winds up in the output section.  */
	  if (r_symndx < symtab_hdr->sh_info)
	    {
	      sym = local_syms + r_symndx;
	      if (ELF_ST_TYPE (sym->st_info) == STT_SECTION)
		{
		  sec = local_sections[r_symndx];
		  rel->r_addend += sec->output_offset + sym->st_value;
		}
	    }

	  continue;
	}
      (*ebd->elf_info_to_howto_rel) (input_bfd, &arel, rel);
      howto = arel.howto;

      zpu_get_relocation_value (input_bfd, info, input_section, 
				    local_sections, local_syms,
                                    rel, &name, &relocation);
	pcrel=0;
      switch (r_type)
        {
        case R_ZPU_IM_7_PCREL:
        case R_ZPU_IM_14_PCREL:
        case R_ZPU_IM_21_PCREL:
        case R_ZPU_IM_28_PCREL:
        case R_ZPU_IM_32_PCREL:
        pcrel=1;
        
        case R_ZPU_IM_7:
        case R_ZPU_IM_14:
        case R_ZPU_IM_21:
        case R_ZPU_IM_28:
        case R_ZPU_IM_32:
        case R_ZPU_IM_14_NONRELAX:
        {
        	char buffer[10];
        	int len;
        	int i;
        	int reserved;
        	if (pcrel)
        	{
        		reserved=r_type-R_ZPU_IM_7_PCREL+1;
				phys_addr=relocation + rel->r_addend;
    			  phys_addr -= (input_section->output_section->vma
					+ input_section->output_offset);
		      phys_addr -= rel->r_offset;
		      phys_addr += rel->r_addend;
		      phys_addr -= reserved;
        	} else
        	{
	        	if (r_type==R_ZPU_IM_14_NONRELAX)
	        	{
	        		reserved=2;
	        	} else
	        	{
	        		reserved=r_type-R_ZPU_IM_7+1;
	        	}
				phys_addr=relocation + rel->r_addend;
        	}
        	len=genImmediate(buffer, phys_addr);
        	
        	for (i=0; i<reserved-len; i++)
        	{
        		/* if we write 0, then execution will crash if we get this wrong
        		 */
	          bfd_put_8 (input_bfd, ZPU_nop,
                     (bfd_byte*) contents + rel->r_offset+i);
        	}
        	for (i=0; i<len; i++)
        	{
	          bfd_put_8 (input_bfd, buffer[i],
                     (bfd_byte*) contents + rel->r_offset+i+(reserved-len));
        	}
          r_type = R_ZPU_NONE;
          r = bfd_reloc_ok;
        }
          break;

        case R_ZPU_NONE:
          r = bfd_reloc_ok;
          break;

      default:
      break;
        }
        if (r_type!=R_ZPU_NONE)
        {
        	/* those that we did not handle ourselves */
	        r = _bfd_final_link_relocate (howto, input_bfd, input_section,
    	                                  contents, rel->r_offset,
        	                              relocation, rel->r_addend);
        }


      if (r != bfd_reloc_ok)
	{
	  const char * msg = (const char *) 0;

	  switch (r)
	    {
	    case bfd_reloc_overflow:
	      if (!((*info->callbacks->reloc_overflow)
		    (info, name, howto->name, (bfd_vma) 0,
		     input_bfd, input_section, rel->r_offset)))
		return FALSE;
	      break;

	    case bfd_reloc_undefined:
	      if (!((*info->callbacks->undefined_symbol)
		    (info, name, input_bfd, input_section,
		     rel->r_offset, TRUE)))
		return FALSE;
	      break;

	    case bfd_reloc_outofrange:
	      msg = _ ("internal error: out of range error");
	      goto common_error;

	    case bfd_reloc_notsupported:
	      msg = _ ("internal error: unsupported relocation error");
	      goto common_error;

	    case bfd_reloc_dangerous:
	      msg = _ ("internal error: dangerous error");
	      goto common_error;

	    default:
	      msg = _ ("internal error: unknown error");
	      /* fall through */

	    common_error:
	      if (!((*info->callbacks->warning)
		    (info, msg, name, input_bfd, input_section,
		     rel->r_offset)))
		return FALSE;
	      break;
	    }
	}
    }

  return TRUE;
}



static void
zpu_info_to_howto_rel (bfd *abfd ATTRIBUTE_UNUSED,
                           arelent *cache_ptr, Elf_Internal_Rela *dst)
{
  unsigned int r_type;

  r_type = ELF32_R_TYPE (dst->r_info);
  BFD_ASSERT (r_type < (unsigned int) R_ZPU_max);
  cache_ptr->howto = &zpu_elf_howto_table[r_type];
}

asection *
elf32_zpu_gc_mark_hook (asection *sec,
                            struct bfd_link_info *info ATTRIBUTE_UNUSED,
                            Elf_Internal_Rela *rel,
                            struct elf_link_hash_entry *h,
                            Elf_Internal_Sym *sym)
{
  if (h != NULL)
    {
      switch (ELF32_R_TYPE (rel->r_info))
	{
	default:
	  switch (h->root.type)
	    {
	    case bfd_link_hash_defined:
	    case bfd_link_hash_defweak:
	      return h->root.u.def.section;

	    case bfd_link_hash_common:
	      return h->root.u.c.p->section;

	    default:
	      break;
	    }
	}
    }
  else
    return bfd_section_from_elf_index (sec->owner, sym->st_shndx);

  return NULL;
}


bfd_boolean
elf32_zpu_gc_sweep_hook (bfd *abfd ATTRIBUTE_UNUSED,
                             struct bfd_link_info *info ATTRIBUTE_UNUSED,
                             asection *sec ATTRIBUTE_UNUSED,
                             const Elf_Internal_Rela *relocs ATTRIBUTE_UNUSED)
{
  /* We don't use got and plt entries for 68hc11/68hc12.  */
  return TRUE;
}

// only big in ZPU
#define TARGET_BIG_SYM			bfd_elf32_zpu_vec
#define TARGET_BIG_NAME			"elf32-zpu"
#define ELF_ARCH			bfd_arch_zpu
#define ELF_MACHINE_CODE		EM_ZPU
#define ELF_MAXPAGESIZE			0x1
#define bfd_elf32_bfd_reloc_type_lookup zpu_reloc_type_lookup
//#define bfd_elf32_bfd_link_add_symbols	elf32_zpu_link_add_symbols
#define elf_info_to_howto		elf_zpu_info_to_howto
#define bfd_elf32_bfd_relax_section  zpu_elf_relax_section
#define elf_backend_relocate_section elf32_zpu_relocate_section
#define elf_info_to_howto_rel	zpu_info_to_howto_rel
#define elf_backend_can_gc_sections		1
#define elf_backend_gc_mark_hook                elf32_zpu_gc_mark_hook
#define elf_backend_gc_sweep_hook               elf32_zpu_gc_sweep_hook


#include "elf32-target.h"
