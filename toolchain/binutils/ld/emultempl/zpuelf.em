# This shell script emits a C file. -*- C -*-
#   Copyright 1991, 1993, 1996, 1997, 1998, 1999, 2000, 2002, 2003, 2004
#   Free Software Foundation, Inc.
#
# This file is part of GLD, the Gnu Linker.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#

# This file is sourced from elf32.em, and defines extra zpu-elf
# specific routines.
#
cat >>e${EMULATION_NAME}.c <<EOF

static int no_pipeline_knowledge = 0;

static void
gld${EMULATION_NAME}_before_parse (void)
{
#ifndef TARGET_			/* I.e., if not generic.  */
  ldfile_set_output_arch ("`echo ${ARCH}`", bfd_arch_unknown);
#endif /* not TARGET_ */
  config.dynamic_link = ${DYNAMIC_LINK-TRUE};
  config.has_shared = `if test -n "$GENERATE_SHLIB_SCRIPT" ; then echo TRUE ; else echo FALSE ; fi`;
}

static void
zpu_elf_after_open (void)
{
  if (strstr (bfd_get_target (output_bfd), "zpu") == NULL)
    {
      /* The zpu backend needs special fields in the output hash structure.
	 These will only be created if the output format is an zpu format,
	 hence we do not support linking and changing output formats at the
	 same time.  Use a link followed by objcopy to change output formats.  */
      einfo ("%F%X%P: error: cannot change output format whilst linking ZPU binaries\n");
      return;
    }


  /* Call the standard elf routine.  */
  gld${EMULATION_NAME}_after_open ();
}



static void
zpu_elf_finish (void)
{

  /* Call the elf32.em routine.  */
  gld${EMULATION_NAME}_finish ();

}

EOF

# Define some shell vars to insert bits of code into the standard elf
# parse_args and list_options functions.
#
PARSE_AND_LIST_PROLOGUE='
'

PARSE_AND_LIST_SHORTOPTS=p

PARSE_AND_LIST_LONGOPTS='
'

PARSE_AND_LIST_OPTIONS='
'

PARSE_AND_LIST_ARGS_CASES='
'

# We have our own after_open and before_allocation functions, but they call
# the standard routines, so give them a different name.
LDEMUL_AFTER_OPEN=zpu_elf_after_open

# Replace the elf before_parse function with our own.
LDEMUL_BEFORE_PARSE=gld"${EMULATION_NAME}"_before_parse

# Call the extra zpu-elf function
LDEMUL_FINISH=zpu_elf_finish
