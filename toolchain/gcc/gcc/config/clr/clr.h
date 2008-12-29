/* clr.h (tm.h)
 * Jeremy Singer
 * 7 Jan 03
 */

/* This is the header file for the 
 * machine description for the
 * .NET Common Language Runtime (CLR).
 * It contains
 * C macros for machine fundamentals,
 * compiler environment,
 * machine description support and
 * application-binary interface.
 */

/* This file is adapted from the egcs-jvm source code, which came
 * with the following caveat:
 *
 *
 *     Note that this machine description is based on the CRIS
 *     architecture so some portions of this file may not be
 *     relevant to the JVM (I never really got around to triming 
 *     the fat).  The CRIS architecture was selected because the 
 *     machine description files were heavily documented, not 
 *     because of any similarity with the JVM.
 *
 *		  - Trent Waddington, 9/9/1999
 *
 *
 *
 */

/**********************************************************************
This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
**************************************************************************/


#include <stdio.h>

/* jvm specific stuff snipped */


/* After this comment lies all preprocessor directives and attached
   declarations described in the info files (or the "Using and Porting
   GNU CC" manual) in the same order as found in the "Target macros"
   section in the gcc-2.7.2 edition.
    First there is a comment with the same text as found in the info
   files, then one or more jvm-specific comments, then the
   definition/declarations (if applicable).  Every section is
   precluded with a `Section: Section name' comment.
   All preprocessor directives, including unused/undefined are
   represented here.  If an entire section is excluded, then only the
   section-comment is present. */


/* Section: Driver */

/*
  `SWITCH_TAKES_ARG (CHAR)'
       A C expression which determines whether the option `-CHAR' takes
       arguments.  The value should be the number of arguments that
       option takes-zero, for many options.

       By default, this macro is defined to handle the standard options
       properly.  You need not define it unless you wish to add additional
       options which take arguments.
*/
/* No definition */


/*
 `WORD_SWITCH_TAKES_ARG (NAME)'
      A C expression which determines whether the option `-NAME' takes
      arguments.  The value should be the number of arguments that
      option takes-zero, for many options.  This macro rather than
      `SWITCH_TAKES_ARG' is used for multi-character option names.

      By default, this macro is defined as
      `DEFAULT_WORD_SWITCH_TAKES_ARG', which handles the standard options
      properly.  You need not define `WORD_SWITCH_TAKES_ARG' unless you
      wish to add additional options which take arguments.  Any
      redefinition should call `DEFAULT_WORD_SWITCH_TAKES_ARG' and then
      check for additional options.
*/
/* No definition */


/*
 `SWITCHES_NEED_SPACES'
      A string-valued C expression which is nonempty if the linker needs
      a space between the `-L' or `-o' option and its argument.

      If this macro is not defined, the default value is 0.
*/
/* No definition */


/*
 `CPP_SPEC'
      A C string constant that tells the GNU CC driver program options to
      pass to CPP.  It can also specify how to translate options you
      give to GNU CC into options for GNU CC to pass to the CPP.
*/
/* No definition */


/*
 `NO_BUILTIN_SIZE_TYPE'
      If this macro is defined, the preprocessor will not define the
      builtin macro `__SIZE_TYPE__'.  The macro `__SIZE_TYPE__' must
      then be defined by `CPP_SPEC' instead.

      This should be defined if `SIZE_TYPE' depends on target dependent
      flags which are not accessible to the preprocessor.  Otherwise, it
      should not be defined.
*/
/* No definition */


/*
 `NO_BUILTIN_PTRDIFF_TYPE'
      If this macro is defined, the preprocessor will not define the
      builtin macro `__PTRDIFF_TYPE__'.  The macro `__PTRDIFF_TYPE__'
      must then be defined by `CPP_SPEC' instead.

      This should be defined if `PTRDIFF_TYPE' depends on target
      dependent flags which are not accessible to the preprocessor.
      Otherwise, it should not be defined.
*/
/* No definition */


/*
 `SIGNED_CHAR_SPEC'
      A C string constant that tells the GNU CC driver program options to
      pass to CPP.  By default, this macro is defined to pass the option
      `-D__CHAR_UNSIGNED__' to CPP if `char' will be treated as
      `unsigned char' by `cc1'.

      Do not define this macro unless you need to override the default
      definition.
*/
/* No definition */


/*
 `CC1_SPEC'
      A C string constant that tells the GNU CC driver program options to
      pass to `cc1'.  It can also specify how to translate options you
      give to GNU CC into options for GNU CC to pass to the `cc1'.

      Do not define this macro if it does not need to do anything.
*/
/* No definition */


/*
 `CC1PLUS_SPEC'
      A C string constant that tells the GNU CC driver program options to
      pass to `cc1plus'.  It can also specify how to translate options
      you give to GNU CC into options for GNU CC to pass to the
      `cc1plus'.

      Do not define this macro if it does not need to do anything.
*/
/* Use the same as for CC1. */
#define CC1PLUS_SPEC CC1_SPEC


/*
 `ASM_SPEC'
      A C string constant that tells the GNU CC driver program options to
      pass to the assembler.  It can also specify how to translate
      options you give to GNU CC into options for GNU CC to pass to the
      assembler.  See the file `sun3.h' for an example of this.

      Do not define this macro if it does not need to do anything.
*/
/* No definition */


/*
 `ASM_FINAL_SPEC'
      A C string constant that tells the GNU CC driver program how to
      run any programs which cleanup after the normal assembler.
      Normally, this is not needed.  See the file `mips.h' for an
      example of this.

      Do not define this macro if it does not need to do anything.
*/
/* No definition */


/*
 `LINK_SPEC'
      A C string constant that tells the GNU CC driver program options to
      pass to the linker.  It can also specify how to translate options
      you give to GNU CC into options for GNU CC to pass to the linker.

      Do not define this macro if it does not need to do anything.
*/
/* No definition */


/*
 `LIB_SPEC'
      Another C string constant used much like `LINK_SPEC'.  The
      difference between the two is that `LIB_SPEC' is used at the end
      of the command given to the linker.

      If this macro is not defined, a default is provided that loads the
      standard C library from the usual place.  See `gcc.c'.
*/
/* No definition */


/*
 `LIBGCC_SPEC'
      Another C string constant that tells the GNU CC driver program how
      and when to place a reference to `libgcc.a' into the linker
      command line.  This constant is placed both before and after the
      value of `LIB_SPEC'.

      If this macro is not defined, the GNU CC driver provides a default
      that passes the string `-lgcc' to the linker unless the `-shared'
      option is specified.
*/
/* No definition */


/*
 `STARTFILE_SPEC'
      Another C string constant used much like `LINK_SPEC'.  The
      difference between the two is that `STARTFILE_SPEC' is used at the
      very beginning of the command given to the linker.

      If this macro is not defined, a default is provided that loads the
      standard C startup file from the usual place.  See `gcc.c'.
*/
/* No definition */

/*
 `ENDFILE_SPEC'
      Another C string constant used much like `LINK_SPEC'.  The
      difference between the two is that `ENDFILE_SPEC' is used at the
      very end of the command given to the linker.

      Do not define this macro if it does not need to do anything.
*/
/* No definition */


/*
 `LINK_LIBGCC_SPECIAL'
      Define this macro if the driver program should find the library
      `libgcc.a' itself and should not pass `-L' options to the linker.
      If you do not define this macro, the driver program will pass the
      argument `-lgcc' to tell the linker to do the search and will pass
      `-L' options to it.
*/
/* No definition */


/*
 `LINK_LIBGCC_SPECIAL_1'
      Define this macro if the driver program should find the library
      `libgcc.a'.  If you do not define this macro, the driver program
      will pass the argument `-lgcc' to tell the linker to do the search.
      This macro is similar to `LINK_LIBGCC_SPECIAL', except that it does
      not affect `-L' options.
*/
/* No definition */


/*
 `MULTILIB_DEFAULTS'
      Define this macro as a C expression for the initializer of an
      array of string to tell the driver program which options are
      defaults for this target and thus do not need to be handled
      specially when using `MULTILIB_OPTIONS'.

      Do not define this macro if `MULTILIB_OPTIONS' is not defined in
      the target makefile fragment or if none of the options listed in
      `MULTILIB_OPTIONS' are set by default.  *Note Target Fragment::.
*/
/* No definition */


/*
 `RELATIVE_PREFIX_NOT_LINKDIR'
      Define this macro to tell `gcc' that it should only translate a
      `-B' prefix into a `-L' linker option if the prefix indicates an
      absolute file name.
*/
/* No definition */


/*
 `STANDARD_EXEC_PREFIX'
      Define this macro as a C string constant if you wish to override
      the standard choice of `/usr/local/lib/gcc-lib/' as the default
      prefix to try when searching for the executable files of the
      compiler.
*/
/* No definition */


/*
 `MD_EXEC_PREFIX'
      If defined, this macro is an additional prefix to try after
      `STANDARD_EXEC_PREFIX'.  `MD_EXEC_PREFIX' is not searched when the
      `-b' option is used, or the compiler is built as a cross compiler.
*/
/* No definition */


/*
 `STANDARD_STARTFILE_PREFIX'
      Define this macro as a C string constant if you wish to override
      the standard choice of `/usr/local/lib/' as the default prefix to
      try when searching for startup files such as `crt0.o'.
*/
/* No definition */


/*
 `MD_STARTFILE_PREFIX'
      If defined, this macro supplies an additional prefix to try after
      the standard prefixes.  `MD_EXEC_PREFIX' is not searched when the
      `-b' option is used, or when the compiler is built as a cross
      compiler.
*/
/* No definition */


/*
 `MD_STARTFILE_PREFIX_1'
      If defined, this macro supplies yet another prefix to try after the
      standard prefixes.  It is not searched when the `-b' option is
      used, or when the compiler is built as a cross compiler.
*/
/* No definition */


/*
 `INIT_ENVIRONMENT'
      Define this macro as a C string constant if you with to set
      environment variables for programs called by the driver, such as
      the assembler and loader.  The driver passes the value of this
      macro to `putenv' to initialize the necessary environment
      variables.
*/
/* No definition */


/*
 `LOCAL_INCLUDE_DIR'
      Define this macro as a C string constant if you wish to override
      the standard choice of `/usr/local/include' as the default prefix
      to try when searching for local header files.  `LOCAL_INCLUDE_DIR'
      comes before `SYSTEM_INCLUDE_DIR' in the search order.

      Cross compilers do not use this macro and do not search either
      `/usr/local/include' or its replacement.
*/
/* No definition */


/*
 `SYSTEM_INCLUDE_DIR'
      Define this macro as a C string constant if you wish to specify a
      system-specific directory to search for header files before the
      standard directory.  `SYSTEM_INCLUDE_DIR' comes before
      `STANDARD_INCLUDE_DIR' in the search order.

      Cross compilers do not use this macro and do not search the
      directory specified.
*/
/* No definition */


/*
 `STANDARD_INCLUDE_DIR'
      Define this macro as a C string constant if you wish to override
      the standard choice of `/usr/include' as the default prefix to try
      when searching for header files.

      Cross compilers do not use this macro and do not search either
      `/usr/include' or its replacement.
*/
/* No definition */


/*
 `INCLUDE_DEFAULTS'
      Define this macro if you wish to override the entire default
      search path for include files.  The default search path includes
      `GCC_INCLUDE_DIR', `LOCAL_INCLUDE_DIR', `SYSTEM_INCLUDE_DIR',
      `GPLUSPLUS_INCLUDE_DIR', and `STANDARD_INCLUDE_DIR'.  In addition,
      `GPLUSPLUS_INCLUDE_DIR' and `GCC_INCLUDE_DIR' are defined
      automatically by `Makefile', and specify private search areas for
      GCC.  The directory `GPLUSPLUS_INCLUDE_DIR' is used only for C++
      programs.

      The definition should be an initializer for an array of structures.
      Each array element should have two elements: the directory name (a
      string constant) and a flag for C++-only directories.  Mark the
      end of the array with a null element.  For example, here is the
      definition used for VMS:

           #define INCLUDE_DEFAULTS \
           {                                       \
             { "GNU_GXX_INCLUDE:", 1},             \
             { "GNU_CC_INCLUDE:", 0},              \
             { "SYS$SYSROOT:[SYSLIB.]", 0},        \
             { ".", 0},                            \
             { 0, 0}                               \
           }

    Here is the order of prefixes tried for exec files:

   1. Any prefixes specified by the user with `-B'.

   2. The environment variable `GCC_EXEC_PREFIX', if any.

   3. The directories specified by the environment variable
      `COMPILER_PATH'.

   4. The macro `STANDARD_EXEC_PREFIX'.

   5. `/usr/lib/gcc/'.

   6. The macro `MD_EXEC_PREFIX', if any.

    Here is the order of prefixes tried for startfiles:

   1. Any prefixes specified by the user with `-B'.

   2. The environment variable `GCC_EXEC_PREFIX', if any.

   3. The directories specified by the environment variable
      `LIBRARY_PATH' (native only, cross compilers do not use this).

   4. The macro `STANDARD_EXEC_PREFIX'.

   5. `/usr/lib/gcc/'.

   6. The macro `MD_EXEC_PREFIX', if any.

   7. The macro `MD_STARTFILE_PREFIX', if any.

   8. The macro `STANDARD_STARTFILE_PREFIX'.

   9. `/lib/'.

  10. `/usr/lib/'.
*/
/* All the same as the default, except we dont want anything from the
   tool-include-dir.  Yes, we keep the cross-include-dir; we may need
   some special place to keep any kludge sys-files (Ulf needed kludge
   include-files to compile libg++, so we may need it).
    (Also, the t-jvm part changes gxx_include_dir to start from the
   same directory as c-include: ".../jvm/GCC_VER/include" but being
   ".../jvm/GCC_VER/g++-include", instead of something down lower in
   the path.  But we dont see it here.)  */
#define INCLUDE_DEFAULTS                                         \
  {                                                              \
    /* Pick up GNU C++ specific include files.  */               \
    { GPLUSPLUS_INCLUDE_DIR, 1, 1 },                             \
    /* This is the dir for fixincludes.  Put it just before      \
       the files that we fix.  */                                \
    { GCC_INCLUDE_DIR, 0, 0 },                                   \
    /* For cross-compilation, this dir name is generated         \
       automatically in Makefile.in.  */                         \
    { CROSS_INCLUDE_DIR, 0, 0 },                                 \
  }

/* Section: Run-time Target */

/*
 `CPP_PREDEFINES'
      Define this to be a string constant containing `-D' options to
      define the predefined macros that identify this machine and system.
      These macros will be predefined unless the `-ansi' option is
      specified.

      In addition, a parallel set of macros are predefined, whose names
      are made by appending `__' at the beginning and at the end.  These
      `__' macros are permitted by the ANSI standard, so they are
      predefined regardless of whether `-ansi' is specified.

      For example, on the Sun, one can use the following value:

           "-Dmc68000 -Dsun -Dunix"

      The result is to define the macros `__mc68000__', `__sun__' and
      `__unix__' unconditionally, and the macros `mc68000', `sun' and
      `unix' provided `-ansi' is not specified.
*/
#define CPP_PREDEFINES  "-Dclr -DCLR -DGNU_CLR"


/*
 `extern int target_flags;'
      This declaration should be present.
*/
/* Lets just HOPE this is 32bit... else doom waits. */
extern int target_flags;


/*
 `TARGET_...'
      This series of macros is to allow compiler command arguments to
      enable or disable the use of optional features of the target
      machine.  For example, one machine description serves both the
      68000 and the 68020; a command argument tells the compiler whether
      it should use 68020-only instructions or not.  This command
      argument works by means of a macro `TARGET_68020' that tests a bit
      in `target_flags'.

      Define a macro `TARGET_FEATURENAME' for each such option.  Its
      definition should test a bit in `target_flags'; for example:

           #define TARGET_68020 (target_flags & 1)

      One place where these macros are used is in the
      condition-expressions of instruction patterns.  Note how
      `TARGET_68020' appears frequently in the 68000 machine description
      file, `m68k.md'.  Another place they are used is in the
      definitions of the other macros in the `MACHINE.h' file.
*/
/* Debug options.  NOT USED ANYMORE */
#define TARGET_GO_DEBUG (target_flags & 1)
#define TARGET_PO_DEBUG (target_flags & 2)

/* Just affects aligment. */
#define TARGET_SVINTO (target_flags & 4)

/* If to use condition-codes generated by insns other than the immediately
   preceding compare/test insn.
    Used to check for errors in notice_update_cc. */
#define TARGET_CCINIT (target_flags & 8)

/* If you change define_delay then this may be useful to test if
   there is any change in the delayed-branch sceduling.  NOT USED
   ANYMORE 
#define TARGET_SLOTALL (target_flags & 16)
*/

/* If to use 16-bit ints (not tested). DO NOT USE */
#define TARGET_SHORT (target_flags & 32)

/* Used when compiling library functions for modes > 32bit.
   USED ONLY WHEN MAKING libgcc2.a */
#define TARGET_LIBFUNC (target_flags & 64)

/* Debug option.  NOT USED ANYMORE */
#define TARGET_PDEBUG (target_flags & 128)

/* If to use side-effect patterns.  (Actually the opposite of the
   intuitive function.  Used to debug the [rx=ry+i] type patterns. */
#define TARGET_SPLIT (target_flags & 256)

/* If to patch non-optimal cse:ing of addresses.  NOT USED ANYMORE */
#define TARGET_EXTRA_CSE (target_flags & 512)

/* If to use the [rx+[ry].S] and [rx+[ry+].S] addressing modes.
   NOT USED ANYMORE */
#define TARGET_BDAP (target_flags & 1024)

/* If to use the [[rx+]] addressing mode.  NOT USED ANYMORE */
#define TARGET_DIPINC (target_flags & 2048)

/* If to expand mul into mstep.  ONLY USED WHEN MAKING libc.a */
#define TARGET_MUL (target_flags & 4096)

/* If to change add.w 65539,r9 into addq 3,r9.  NOT USED ANYMORE */
#define TARGET_MODIFY_OPERANDS (target_flags & 8192)

/* If to use add, sub, and, or in HImode && QImode.  NOT USED ANYMORE */
#define TARGET_SMALL_ARIT (target_flags & 16384)

/* If to KEEP (not force) alignment of stack at 16 bits. */
#define TARGET_STACK_ALIGN (target_flags & 32768)

/* If to do alignment on individual non-modifiable objects. */
#define TARGET_CONST_ALIGN (target_flags & 65536)

/* If to do alignment on individual modifiable objects. */
#define TARGET_DATA_ALIGN (target_flags & 131072)

/* If to remove unused constant strings. */
#define TARGET_USED_STRINGS (target_flags & 524288)

/* If not to omit funtion prologue and epilogue */
#define TARGET_PROLOGUE_EPILOGUE (target_flags & 1048576)


/*
 `TARGET_SWITCHES'
      This macro defines names of command options to set and clear bits
      in `target_flags'.  Its definition is an initializer with a
      subgrouping for each command option.

      Each subgrouping contains a string constant, that defines the
      option name, and a number, which contains the bits to set in
      `target_flags'.  A negative number says to clear bits instead; the
      negative of the number is which bits to clear.  The actual option
      name is made by appending `-m' to the specified name.

      One of the subgroupings should have a null string.  The number in
      this grouping is the default value for `target_flags'.  Any target
      options act starting with that value.

      Here is an example which defines `-m68000' and `-m68020' with
      opposite meanings, and picks the latter as the default:

           #define TARGET_SWITCHES \
             { { "68020", 1},      \
               { "68000", -1},     \
               { "", 1}}
*/
#define TARGET_SWITCHES  \
  { \
    { "go_debug",                                    1}, \
    { "nogo_debug",                                 -1}, \
    { "po_debug",                                    2}, \
    { "nopo_debug",                                 -2}, \
    { "svinto" ,                                     4}, \
    { "no-svinto",                                  -4}, \
    { "100" ,                                        4}, \
    { "no-100" ,                                    -4}, \
    { "32" ,                                         4}, \
    { "16" ,                                        -4}, \
    { "etrax100" ,                                   4}, \
    { "no-etrax100" ,                                4}, \
    { "etrax" ,                                     -4}, \
    { "no-etrax" ,                                  -4}, \
    { "cc-init",                                     8}, \
    { "no-cc-init",                                 -8}, \
    { "slot-all",                                   16}, \
    { "no-slot-all",                               -16}, \
    { "short",                                      32}, \
    { "no-short",                                  -32}, \
    { "libfunc",                                    64}, \
    { "no-libfunc",                                -64}, \
    { "pdebug",                                    128}, \
    { "no-pdebug",                                -128}, \
    { "split",                                     256}, \
    { "no-split",                                 -256}, \
    { "extra-cse",                                 512}, \
    { "no-extra-cse",                             -512}, \
    { "bdap",                                     1024}, \
    { "no-bdap",                                 -1024}, \
    { "dip-inc",                                  2048}, \
    { "no-dip-inc",                              -2048}, \
    { "mstep",                                    4096}, \
    { "step",                                     4096}, \
    { "no-mstep",                                -4096}, \
    { "ul",                                       4096}, \
    { "no-mul",                                  -4096}, \
    { "modify-operands",                          8192}, \
    { "odify-operands",                           8192}, \
    { "no-modify-operands",                      -8192}, \
    { "small-arit",                              16384}, \
    { "no-small-arit",                          -16384}, \
    { "align",         32768 + 65536 + 131072 + 262144}, \
    { "stack-align",                             32768}, \
    { "no-stack-align",                         -32768}, \
    { "data-align",                             131072}, \
    { "no-data-align",                         -131072}, \
    { "const-align",                             65536}, \
    { "no-const-align",                         -65536}, \
    { "used-strings-only",                      524288}, \
    { "no-used-strings-only",                  -524288}, \
    { "16-bit",                 32768 + 65536 + 131072}, \
    { "8-bit",               -(32768 + 65536 + 131072)}, \
    { "16bit",                  32768 + 65536 + 131072}, \
    { "8bit",                -(32768 + 65536 + 131072)}, \
    { "prologue-epilogue" ,                    1048576}, \
    { "no-prologue-epilogue" ,                -1048576}, \
    { "",                               TARGET_DEFAULT}}

/* Default target_flags if no switches specified.  */
#ifndef TARGET_DEFAULT
#define TARGET_DEFAULT (256+512+1024+2048+8192+16384+32768+65536+131072+262144+524288+1048576)
#endif


/*
 `TARGET_OPTIONS'
      This macro is similar to `TARGET_SWITCHES' but defines names of
      command options that have values.  Its definition is an
      initializer with a subgrouping for each command option.

      Each subgrouping contains a string constant, that defines the
      fixed part of the option name, and the address of a variable.  The
      variable, type `char *', is set to the variable part of the given
      option if the fixed part matches.  The actual option name is made
      by appending `-m' to the specified name.

      Here is an example which defines `-mshort-data-NUMBER'.  If the
      given option is `-mshort-data-512', the variable `m88k_short_data'
      will be set to the string `"512"'.

           extern char *m88k_short_data;
           #define TARGET_OPTIONS \
            { { "short-data-", &m88k_short_data } }
*/
/* No definition */


/*
 `TARGET_VERSION'
      This macro is a C statement to print on `stderr' a string
      describing the particular machine description choice.  Every
      machine description should define `TARGET_VERSION'.  For example:

           #ifdef MOTOROLA
           #define TARGET_VERSION \
             fprintf (stderr, " (68k, Motorola syntax)");
           #else
           #define TARGET_VERSION \
             fprintf (stderr, " (68k, MIT syntax)");
           #endif
*/
/* Print subsidiary information on the compiler version in use.
   Do not use VD.D syntax (D=digit), since this will cause confusion
   with the base gcc version among users, when we ask which version of
   gcc-jvm they are using.  Please use some flavor of "R<number>" for
   the version (no need for major.minor versions, I believe). */
#define TARGET_VERSION fprintf (stderr, ".NET CLR");


/*
 `OVERRIDE_OPTIONS'
      Sometimes certain combinations of command options do not make
      sense on a particular target machine.  You can define a macro
      `OVERRIDE_OPTIONS' to take account of this.  This macro, if
      defined, is executed once just after all the command options have
      been parsed.

      Don't use this macro to turn on various extra optimizations for
      `-O'.  That is what `OPTIMIZATION_OPTIONS' is for.
*/
/* FIXME  Do we need this?
 * #define OVERRIDE_OPTIONS override_options()
 * extern void override_options();
 */

/*
 `OPTIMIZATION_OPTIONS (LEVEL)'
      Some machines may desire to change what optimizations are
      performed for various optimization levels.   This macro, if
      defined, is executed once just after the optimization level is
      determined and before the remainder of the command options have
      been parsed.  Values set in this macro are used as the default
      values for the other command line options.

      LEVEL is the optimization level specified; 2 if `-O2' is
      specified, 1 if `-O' is specified, and 0 if neither is specified.

      You should not use this macro to change options that are not
      machine-specific.  These should uniformly selected by the same
      optimization level on all supported machines.  Use this macro to
      enable machbine-specific optimizations.

      *Do not examine `write_symbols' in this macro!* The debugging
      options are not supposed to alter the generated code.
*/
/* The following are found to give better (faster and smaller) code
   some time long ago.  This may have changed (test thorougly!) */

/* FIXME  Do we need this?
//#define OPTIMIZATION_OPTIONS(OPTIMIZE,unused)                   \
//{                                                               \
//  if (OPTIMIZE >= 2)                                            \
//  {                                                             \
//    // flag_unroll_loops =                                      \
//    flag_force_addr = flag_force_mem =                          \
//     flag_omit_frame_pointer = 1;                               \
//  }                                                             \
//}
*/


/*
 `CAN_DEBUG_WITHOUT_FP'
      Define this macro if debugging can be performed even without a
      frame pointer.  If this macro is defined, GNU CC will turn on the
      `-fomit-frame-pointer' option whenever `-O' is specified.
*/
/* No definition */


/* Section: Storage Layout */

/*
 `BITS_BIG_ENDIAN'
      Define this macro to have the value 1 if the most significant bit
      in a byte has the lowest number; otherwise define it to have the
      value zero.  This means that bit-field instructions count from the
      most significant bit.  If the machine has no bit-field
      instructions, then this must still be defined, but it doesn't
      matter which value it is defined to.  This macro need not be a
      constant.

      This macro does not affect the way structure fields are packed into
      bytes or words; that is controlled by `BYTES_BIG_ENDIAN'.
*/
#define BITS_BIG_ENDIAN 0


/*
 `BYTES_BIG_ENDIAN'
      Define this macro to have the value 1 if the most significant byte
      in a word has the lowest number.  This macro need not be a
      constant.
*/
#define BYTES_BIG_ENDIAN 0


/*
 `WORDS_BIG_ENDIAN'
      Define this macro to have the value 1 if, in a multiword object,
      the most significant word has the lowest number.  This applies to
      both memory locations and registers; GNU CC fundamentally assumes
      that the order of words in memory is the same as the order in
      registers.  This macro need not be a constant.
*/
/* FIXME  Is this right? */
#define WORDS_BIG_ENDIAN 0


/*
 `LIBGCC2_WORDS_BIG_ENDIAN'
      Define this macro if WORDS_BIG_ENDIAN is not constant.  This must
      be a constant value with the same meaning as WORDS_BIG_ENDIAN,
      which will be used only when compiling libgcc2.c.  Typically the
      value will be set based on preprocessor defines.
*/
/* No definition */


/*
 `FLOAT_WORDS_BIG_ENDIAN'
      Define this macro to have the value 1 if `DFmode', `XFmode' or
      `TFmode' floating point numbers are stored in memory with the word
      containing the sign bit at the lowest address; otherwise define it
      to have the value 0.  This macro need not be a constant.

      You need not define this macro if the ordering is the same as for
      multi-word integers.
*/
/* No definition (use WORDS_BIG_ENDIAN) */


/*
 `BITS_PER_UNIT'
      Define this macro to be the number of bits in an addressable
      storage unit (byte); normally 8.
*/
#define BITS_PER_UNIT 8


/*
 `BITS_PER_WORD'
      Number of bits in a word; normally 32.
*/
#define BITS_PER_WORD 32


/*
 `MAX_BITS_PER_WORD'
      Maximum number of bits in a word.  If this is undefined, the
      default is `BITS_PER_WORD'.  Otherwise, it is the constant value
      that is the largest value that `BITS_PER_WORD' can have at
      run-time.
*/
/* No definition */


/*
 `UNITS_PER_WORD'
      Number of storage units in a word; normally 4.
*/
#define UNITS_PER_WORD 4


/*
 `MIN_UNITS_PER_WORD'
      Minimum number of units in a word.  If this is undefined, the
      default is `UNITS_PER_WORD'.  Otherwise, it is the constant value
      that is the smallest value that `UNITS_PER_WORD' can have at
      run-time.
*/
/* No definition */


/*
 `POINTER_SIZE'
      Width of a pointer, in bits.  You must specify a value no wider
      than the width of `Pmode'.  If it is not equal to the width of
      `Pmode', you must define `POINTERS_EXTEND_UNSIGNED'.
*/
#define POINTER_SIZE 32


/*
 `POINTERS_EXTEND_UNSIGNED'
      A C expression whose value is nonzero if pointers that need to be
      extended from being `POINTER_SIZE' bits wide to `Pmode' are
      sign-extended and zero if they are zero-extended.

      You need not define this macro if the `POINTER_SIZE' is equal to
      the width of `Pmode'.
*/
/* No definition */


/*
 `PROMOTE_MODE (M, UNSIGNEDP, TYPE)'
      A macro to update M and UNSIGNEDP when an object whose type is
      TYPE and which has the specified mode and signedness is to be
      stored in a register.  This macro is only called when TYPE is a
      scalar type.

      On most RISC machines, which only have operations that operate on
      a full register, define this macro to set M to `word_mode' if M is
      an integer mode narrower than `BITS_PER_WORD'.  In most cases,
      only integer modes should be widened because wider-precision
      floating-point operations are usually more expensive than their
      narrower counterparts.

      For most machines, the macro definition does not change UNSIGNEDP.
      However, some machines, have instructions that preferentially
      handle either signed or unsigned quantities of certain modes.  For
      example, on the DEC Alpha, 32-bit loads from memory and 32-bit add
      instructions sign-extend the result to 64 bits.  On such machines,
      set UNSIGNEDP according to which kind of extension is more
      efficient.

      Do not define this macro if it would never modify M.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `PROMOTE_FUNCTION_ARGS'
      Define this macro if the promotion described by `PROMOTE_MODE'
      should also be done for outgoing function arguments.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `PROMOTE_FUNCTION_RETURN'
      Define this macro if the promotion described by `PROMOTE_MODE'
      should also be done for the return value of functions.

      If this macro is defined, `FUNCTION_VALUE' must perform the same
      promotions done by `PROMOTE_MODE'.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `PROMOTE_FOR_CALL_ONLY'
      Define this macro if the promotion described by `PROMOTE_MODE'
      should *only* be performed for outgoing function arguments or
      function return values, as specified by `PROMOTE_FUNCTION_ARGS'
      and `PROMOTE_FUNCTION_RETURN', respectively.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `PARM_BOUNDARY'
      Normal alignment required for function parameters on the stack, in
      bits.  All stack parameters receive at least this much alignment
      regardless of data type.  On most machines, this is the same as the
      size of an integer.
*/
/* We will be using prototype promotion, so they will be 32 bit. */
#define PARM_BOUNDARY 32


/*
 `STACK_BOUNDARY'
      Define this macro if you wish to preserve a certain alignment for
      the stack pointer.  The definition is a C expression for the
      desired alignment (measured in bits).

      If `PUSH_ROUNDING' is not defined, the stack will always be aligned
      to the specified boundary.  If `PUSH_ROUNDING' is defined and
      specifies a less strict alignment than `STACK_BOUNDARY', the stack
      may be momentarily unaligned while pushing arguments.
*/
/* Stack boundary is guided by -mstack-align, -mno-stack-align,
   -malign.
   Old comment: (2.1: still valid in 2.7.2?)
    Note that to make this macro affect the alignment of stack
   locals, a fix was required, and special precautions when handling
   the stack pointer in various other macros (FUNCTION_PROLOGUE et al)
   were required.  See file "function.c".  If you would just define
   this macro, it would only affect the builtin alloca() and variable
   local data (non-ANSI, non-K&R, Gnu C extension).
*/
#define STACK_BOUNDARY (TARGET_STACK_ALIGN ? (TARGET_SVINTO ? 32 : 16) : 8)


/*
 `FUNCTION_BOUNDARY'
      Alignment required for a function entry point, in bits.
*/
#define FUNCTION_BOUNDARY 16


/*
 `BIGGEST_ALIGNMENT'
      Biggest alignment that any data type can require on this machine,
      in bits.
*/
/* Do not change this (when optimizing), as it will affect strange
   places, at least in 2.1. */
#define BIGGEST_ALIGNMENT 8


/*
 `BIGGEST_FIELD_ALIGNMENT'
      Biggest alignment that any structure field can require on this
      machine, in bits.  If defined, this overrides `BIGGEST_ALIGNMENT'
      for structure fields only.
*/
/* No definition */


/*
 `MAX_OFILE_ALIGNMENT'
      Biggest alignment supported by the object file format of this
      machine.  Use this macro to limit the alignment which can be
      specified using the `__attribute__ ((aligned (N)))' construct.  If
      not defined, the default value is `BIGGEST_ALIGNMENT'.
*/
/* Cannot be defined because of restrictions in a.out; it's no use just
   to "#define MAX_OFILE_ALIGNMENT (32768*8)" since that will just be
   confusing, partly by shutting of the warning. */


/*
 `DATA_ALIGNMENT (TYPE, BASIC-ALIGN)'
      If defined, a C expression to compute the alignment for a static
      variable.  TYPE is the data type, and BASIC-ALIGN is the alignment
      that the object would ordinarily have.  The value of this macro is
      used instead of that alignment to align the object.

      If this macro is not defined, then BASIC-ALIGN is used.

      One use of this macro is to increase alignment of medium-size data
      to make it all fit in fewer cache lines.  Another is to cause
      character arrays to be word-aligned so that `strcpy' calls that
      copy constants to character arrays can be done inline.
*/
/* If -m16bit,  -m16-bit, -malign or -mdata-align,
   align everything to 16 bit. */
#define DATA_ALIGNMENT(TYPE, BASIC_ALIGN) \
  (TARGET_DATA_ALIGN ? (TARGET_SVINTO ? (BASIC_ALIGN < 32 ? 32 : BASIC_ALIGN) \
                        : (BASIC_ALIGN < 16 ? 16 : BASIC_ALIGN)) : BASIC_ALIGN)

/*
 `CONSTANT_ALIGNMENT (CONSTANT, BASIC-ALIGN)'
      If defined, a C expression to compute the alignment given to a
      constant that is being placed in memory.  CONSTANT is the constant
      and BASIC-ALIGN is the alignment that the object would ordinarily
      have.  The value of this macro is used instead of that alignment to
      align the object.

      If this macro is not defined, then BASIC-ALIGN is used.

      The typical use of this macro is to increase alignment for string
      constants to be word aligned so that `strcpy' calls that copy
      constants can be done inline.
*/
/* Note that this has the effect of making gcc believe that ALL
   references to constant stuff (in code segment, like strings) has
   this alignment.  That is a rather rushed assumption.  Luckily we do
   not care about the "alignment" operand to builtin memcpy (only
   place where it counts), so it doesnt affect us in any bad spots. */
#define CONSTANT_ALIGNMENT(CONSTANT, BASIC_ALIGN) \
  (TARGET_CONST_ALIGN ? (TARGET_SVINTO ? (BASIC_ALIGN < 32 ? 32 : BASIC_ALIGN) \
                         : (BASIC_ALIGN < 16 ? 16 : BASIC_ALIGN)) : BASIC_ALIGN)


/*
 `EMPTY_FIELD_BOUNDARY'
      Alignment in bits to be given to a structure bit field that
      follows an empty field such as `int : 0;'.

      Note that `PCC_BITFIELD_TYPE_MATTERS' also affects the alignment
      that results from an empty field.
*/
#define EMPTY_FIELD_BOUNDARY 8


/*
 `STRUCTURE_SIZE_BOUNDARY'
      Number of bits which any structure or union's size must be a
      multiple of.  Each structure or union's size is rounded up to a
      multiple of this.

      If you do not define this macro, the default is the same as
      `BITS_PER_UNIT'.
*/
#define STRUCTURE_SIZE_BOUNDARY 8


/*
 `STRICT_ALIGNMENT'
      Define this macro to be the value 1 if instructions will fail to
      work if given data not on the nominal alignment.  If instructions
      will merely go slower in that case, define this macro as 0.
*/
#define STRICT_ALIGNMENT 0


/*
 `PCC_BITFIELD_TYPE_MATTERS'
      Define this if you wish to imitate the way many other C compilers
      handle alignment of bitfields and the structures that contain them.

      The behavior is that the type written for a bitfield (`int',
      `short', or other integer type) imposes an alignment for the
      entire structure, as if the structure really did contain an
      ordinary field of that type.  In addition, the bitfield is placed
      within the structure so that it would fit within such a field, not
      crossing a boundary for it.

      Thus, on most machines, a bitfield whose type is written as `int'
      would not cross a four-byte boundary, and would force four-byte
      alignment for the whole structure.  (The alignment used may not be
      four bytes; it is controlled by the other alignment parameters.)

      If the macro is defined, its definition should be a C expression;
      a nonzero value for the expression enables this behavior.

      Note that if this macro is not defined, or its value is zero, some
      bitfields may cross more than one alignment boundary.  The
      compiler can support such references if there are `insv', `extv',
      and `extzv' insns that can directly reference memory.

      The other known way of making bitfields work is to define
      `STRUCTURE_SIZE_BOUNDARY' as large as `BIGGEST_ALIGNMENT'.  Then
      every structure can be accessed with fullwords.

      Unless the machine has bitfield instructions or you define
      `STRUCTURE_SIZE_BOUNDARY' that way, you must define
      `PCC_BITFIELD_TYPE_MATTERS' to have a nonzero value.

      If your aim is to make GNU CC use the same conventions for laying
      out bitfields as are used by another compiler, here is how to
      investigate what the other compiler does.  Compile and run this
      program:

           struct foo1
           {
             char x;
             char :0;
             char y;
           };

           struct foo2
           {
             char x;
             int :0;
             char y;
           };

           main ()
           {
             printf ("Size of foo1 is %d\n",
                     sizeof (struct foo1));
             printf ("Size of foo2 is %d\n",
                     sizeof (struct foo2));
             exit (0);
           }

      If this prints 2 and 5, then the compiler's behavior is what you
      would get from `PCC_BITFIELD_TYPE_MATTERS'.
*/
/* No definition */


/*
 `BITFIELD_NBYTES_LIMITED'
      Like PCC_BITFIELD_TYPE_MATTERS except that its effect is limited to
      aligning a bitfield within the structure.
*/
/* No definition */


/*
 `ROUND_TYPE_SIZE (STRUCT, SIZE, ALIGN)'
      Define this macro as an expression for the overall size of a
      structure (given by STRUCT as a tree node) when the size computed
      from the fields is SIZE and the alignment is ALIGN.

      The default is to round SIZE up to a multiple of ALIGN.
*/
/* No definition */


/*
 `ROUND_TYPE_ALIGN (STRUCT, COMPUTED, SPECIFIED)'
      Define this macro as an expression for the alignment of a structure
      (given by STRUCT as a tree node) if the alignment computed in the
      usual way is COMPUTED and the alignment explicitly specified was
      SPECIFIED.

      The default is to use SPECIFIED if it is larger; otherwise, use
      the smaller of COMPUTED and `BIGGEST_ALIGNMENT'
*/
/* No definition */


/*
 `MAX_FIXED_MODE_SIZE'
      An integer expression for the size in bits of the largest integer
      machine mode that should actually be used.  All integer machine
      modes of this size or smaller can be used for structures and
      unions with the appropriate sizes.  If this macro is undefined,
      `GET_MODE_BITSIZE (DImode)' is assumed.
*/
/* Strange stuff happens to structs if we use anything larger than
   largest actually used datum size, so lets make it 32. The type
   "long long" will still work (or not, if there are "other" bugs)... */
#define MAX_FIXED_MODE_SIZE 32


/*
 `CHECK_FLOAT_VALUE (MODE, VALUE, OVERFLOW)'
      A C statement to validate the value VALUE (of type `double') for
      mode MODE.  This means that you check whether VALUE fits within
      the possible range of values for mode MODE on this target machine.
      The mode MODE is always a mode of class `MODE_FLOAT'.  OVERFLOW
      is nonzero if the value is already known to be out of range.

      If VALUE is not valid or if OVERFLOW is nonzero, you should set
      OVERFLOW to 1 and then assign some valid value to VALUE.  Allowing
      an invalid value to go through the compiler can produce incorrect
      assembler code which may even cause Unix assemblers to crash.

      This macro need not be defined if there is no work for it to do.
*/
/* No definition */


/*
 `TARGET_FLOAT_FORMAT'
      A code distinguishing the floating point format of the target
      machine.  There are three defined values:

     `IEEE_FLOAT_FORMAT'
           This code indicates IEEE floating point.  It is the default;
           there is no need to define this macro when the format is IEEE.

     `VAX_FLOAT_FORMAT'
           This code indicates the peculiar format used on the Vax.

     `UNKNOWN_FLOAT_FORMAT'
           This code indicates any other format.

      The value of this macro is compared with `HOST_FLOAT_FORMAT'
      (*note Config::.) to determine whether the target machine has the
      same format as the host machine.  If any other formats are
      actually in use on supported machines, new codes should be defined
      for them.

      The ordering of the component words of floating point values
      stored in memory is controlled by `FLOAT_WORDS_BIG_ENDIAN' for the
      target machine and `HOST_FLOAT_WORDS_BIG_ENDIAN' for the host.
*/
/* No definition (use IEEE_FLOAT_FORMAT) */


/* Section: Type Layout */

/*
 `INT_TYPE_SIZE'
      A C expression for the size in bits of the type `int' on the
      target machine.  If you don't define this, the default is one word.
*/
/* No definition */


/*
 `MAX_INT_TYPE_SIZE'
      Maximum number for the size in bits of the type `int' on the target
      machine.  If this is undefined, the default is `INT_TYPE_SIZE'.
      Otherwise, it is the constant value that is the largest value that
      `INT_TYPE_SIZE' can have at run-time.  This is used in `cpp'.
*/
/* No definition */


/*
 `SHORT_TYPE_SIZE'
      A C expression for the size in bits of the type `short' on the
      target machine.  If you don't define this, the default is half a
      word.  (If this would be less than one storage unit, it is rounded
      up to one unit.)
*/
/* No definition */


/*
 `LONG_TYPE_SIZE'
      A C expression for the size in bits of the type `long' on the
      target machine.  If you don't define this, the default is one word.
*/
/* No definition */


/*
 `MAX_LONG_TYPE_SIZE'
      Maximum number for the size in bits of the type `long' on the
      target machine.  If this is undefined, the default is
      `LONG_TYPE_SIZE'.  Otherwise, it is the constant value that is the
      largest value that `LONG_TYPE_SIZE' can have at run-time.  This is
      used in `cpp'.
*/
/* No definition */


/*
 `LONG_LONG_TYPE_SIZE'
      A C expression for the size in bits of the type `long long' on the
      target machine.  If you don't define this, the default is two
      words.  If you want to support GNU Ada on your machine, the value
      of macro must be at least 64.
*/
/* No definition */


/*
 `CHAR_TYPE_SIZE'
      A C expression for the size in bits of the type `char' on the
      target machine.  If you don't define this, the default is one
      quarter of a word.  (If this would be less than one storage unit,
      it is rounded up to one unit.)
*/
/* No definition */


/*
 `MAX_CHAR_TYPE_SIZE'
      Maximum number for the size in bits of the type `char' on the
      target machine.  If this is undefined, the default is
      `CHAR_TYPE_SIZE'.  Otherwise, it is the constant value that is the
      largest value that `CHAR_TYPE_SIZE' can have at run-time.  This is
      used in `cpp'.
*/
/* No definition */


/*
 `FLOAT_TYPE_SIZE'
      A C expression for the size in bits of the type `float' on the
      target machine.  If you don't define this, the default is one word.
*/
/* No definition */


/*
 `DOUBLE_TYPE_SIZE'
      A C expression for the size in bits of the type `double' on the
      target machine.  If you don't define this, the default is two
      words.
*/
/* No definition */


/*
 `LONG_DOUBLE_TYPE_SIZE'
      A C expression for the size in bits of the type `long double' on
      the target machine.  If you don't define this, the default is two
      words.
*/
/* No definition */


/*
 `DEFAULT_SIGNED_CHAR'
      An expression whose value is 1 or 0, according to whether the type
      `char' should be signed or unsigned by default.  The user can
      always override this default with the options `-fsigned-char' and
      `-funsigned-char'.
*/
/* For compatibility && historical reasons, it should be signed.  */
#define DEFAULT_SIGNED_CHAR 1


/*
 `DEFAULT_SHORT_ENUMS'
      A C expression to determine whether to give an `enum' type only as
      many bytes as it takes to represent the range of possible values
      of that type.  A nonzero value means to do that; a zero value
      means all `enum' types should be allocated like `int'.

      If you don't define the macro, the default is 0.
*/
/* No definition */


/*
 `SIZE_TYPE'
      A C expression for a string describing the name of the data type
      to use for size values.  The typedef name `size_t' is defined
      using the contents of the string.

      The string can contain more than one keyword.  If so, separate
      them with spaces, and write first any length keyword, then
      `unsigned' if appropriate, and finally `int'.  The string must
      exactly match one of the data type names defined in the function
      `init_decl_processing' in the file `c-decl.c'.  You may not omit
      `int' or change the order--that would cause the compiler to crash
      on startup.

      If you don't define this macro, the default is `"long unsigned
      int"'.
*/
/* No definition */


/*
 `PTRDIFF_TYPE'
      A C expression for a string describing the name of the data type
      to use for the result of subtracting two pointers.  The typedef
      name `ptrdiff_t' is defined using the contents of the string.  See
      `SIZE_TYPE' above for more information.

      If you don't define this macro, the default is `"long int"'.
*/
/* No definition */


/*
 `WCHAR_TYPE'
      A C expression for a string describing the name of the data type
      to use for wide characters.  The typedef name `wchar_t' is defined
      using the contents of the string.  See `SIZE_TYPE' above for more
      information.

      If you don't define this macro, the default is `"int"'.
*/
/* Note that WCHAR_TYPE_SIZE is used in cexp.y,
   where TARGET_SHORT is not available.  */
#define WCHAR_TYPE "long int"


/*
 `WCHAR_TYPE_SIZE'
      A C expression for the size in bits of the data type for wide
      characters.  This is used in `cpp', which cannot make use of
      `WCHAR_TYPE'.
*/
#define WCHAR_TYPE_SIZE 32


/*
 `MAX_WCHAR_TYPE_SIZE'
      Maximum number for the size in bits of the data type for wide
      characters.  If this is undefined, the default is
      `WCHAR_TYPE_SIZE'.  Otherwise, it is the constant value that is the
      largest value that `WCHAR_TYPE_SIZE' can have at run-time.  This is
      used in `cpp'.
*/
/* No definition */


/*
 `OBJC_INT_SELECTORS'
      Define this macro if the type of Objective C selectors should be
      `int'.

      If this macro is not defined, then selectors should have the type
      `struct objc_selector *'.
*/
/* No definition */


/*
 `OBJC_SELECTORS_WITHOUT_LABELS'
      Define this macro if the compiler can group all the selectors
      together into a vector and use just one label at the beginning of
      the vector.  Otherwise, the compiler must give each selector its
      own assembler label.

      On certain machines, it is important to have a separate label for
      each selector because this enables the linker to eliminate
      duplicate selectors.
*/
/* No definition */


/*
 `TARGET_BELL'
      A C constant expression for the integer value for escape sequence
      `\a'.
*/
#define TARGET_BELL 007


/*
 `TARGET_BS'
 `TARGET_TAB'
 `TARGET_NEWLINE'
      C constant expressions for the integer values for escape sequences
      `\b', `\t' and `\n'.
*/
#define TARGET_BS 010
#define TARGET_TAB 011
#define TARGET_NEWLINE 012


/*
 `TARGET_VT'
 `TARGET_FF'
 `TARGET_CR'
      C constant expressions for the integer values for escape sequences
      `\v', `\f' and `\r'.
*/
#define TARGET_VT 013
#define TARGET_FF 014
#define TARGET_CR 015


/* Section: Registers::Register Basics */

/*
 `FIRST_PSEUDO_REGISTER'
      Number of hardware registers known to the compiler.  They receive
      numbers 0 through `FIRST_PSEUDO_REGISTER-1'; thus, the first
      pseudo register's number really is assigned the number
      `FIRST_PSEUDO_REGISTER'.
*/
/* Note that we count in all 16 non-special registers plus SRP */
#define FIRST_PSEUDO_REGISTER 32
/* Last register in main register bank r0..r15. (Jvm only).
   NOT USED BY GCC (other than by other macros in this file). */
#define LAST_GENERAL_REGISTER 31  /* JDS31 - should this be 26 ?? */

/* Descriptions of registers used for arguments. These are local to this
   file (and possibly aux-output-jvm.c as well). */
#define FIRST_ARG_REG 19
#define FIRST_ARG_REG_IN 11

#define MAX_ARGS_IN_REGS 8


/*
 `FIXED_REGISTERS'
      An initializer that says which registers are used for fixed
      purposes all throughout the compiled code and are therefore not
      available for general allocation.  These would include the stack
      pointer, the frame pointer (except on machines where that can be
      used as a general register when no frame pointer is needed), the
      program counter on machines where that is considered one of the
      addressable registers, and any other numbered register with a
      standard use.

      This information is expressed as a sequence of numbers, separated
      by commas and surrounded by braces.  The Nth number is 1 if
      register N is fixed, 0 otherwise.

      The table initialized from this macro, and the table initialized by
      the following one, may be overridden at run time either
      automatically, by the actions of the macro
      `CONDITIONAL_REGISTER_USAGE', or by the user with the command
      options `-ffixed-REG', `-fcall-used-REG' and `-fcall-saved-REG'.
*/
/* A 1 for registers that have pervasive standard uses
   and are not available for the register allocator.
   For Jvm, these are 15 (pc) and 14 (sp). r8 is used as an FP (not fixed).
    SRP is not included in general registers and will not be used
   automatically.  It is only used as an indicator for leaf-functions
   (now quite obsolete because of function leaf_function_p() ) */

/* --- jds31 --- CLR register file layout
 * These so-called registers are the first 32 entries in the
 * local variable table.
 *     r0-r10 are general purpose registers
 *     r11-r18 are incoming arguments registers
 *     r19-r26 are outgoing arguments registers
 *     r27 is static chain pointer
 *     r28 is stack frame pointer, also argument pointer
 *     r29 is stack pointer
 *     r30 is return address pointer (SRP) -- not quite sure about this??
 *     r31 is program counter
 *
 * 
 * Actually, I'm not really sure how many of r27-r31 are strictly 
 * necessary, but I put them in for good measure.
 */

#define FIXED_REGISTERS { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                          0, 0, 0, 0, 0, 0, 0, 0,          \
                          0, 0, 0, 0, 0, 0, 0, 0,          \
                          1, 1, 1, 1, 1 }




/*
 `CALL_USED_REGISTERS'
      Like `FIXED_REGISTERS' but has 1 for each register that is
      clobbered (in general) by function calls as well as for fixed
      registers.  This macro therefore identifies the registers that are
      not available for general allocation of values that must live
      across function calls.

      If a register has 0 in `CALL_USED_REGISTERS', the compiler
      automatically saves it on function entry and restores it on
      function exit, if the register is used within the function.
*/
/* JVM - was 
 * 9 for structure-address, 10-13 for parameters, 10- for return values
 */
/* CLR - is r0 for return value, and then r27-r31 for special regs */
/* --- jds31 --- Note!
 * We don't actually need to save any of the registers onto the stack
 * at function entry, and restore them at function exit, since
 * the CLR does this AUTOMATICALLY on a call instruction.
 * I hope we can convince GCC about this... FIXME????
 */
#define CALL_USED_REGISTERS { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                              0, 0, 0, 0, 0, 0, 0, 0,          \
                              0, 0, 0, 0, 0, 0, 0, 0,          \
                              1, 1, 1, 1, 1 }


/*
 `CONDITIONAL_REGISTER_USAGE'
      Zero or more C statements that may conditionally modify two
      variables `fixed_regs' and `call_used_regs' (both of type `char
      []') after they have been initialized from the two preceding
      macros.

      This is necessary in case the fixed or call-clobbered registers
      depend on target flags.

      You need not define this macro if it has no work to do.

      If the usage of an entire class of registers depends on the target
      flags, you may indicate this to GCC by using this macro to modify
      `fixed_regs' and `call_used_regs' to 1 for each of the registers
      in the classes which should not be used by GCC.  Also define the
      macro `REG_CLASS_FROM_LETTER' to return `NO_REGS' if it is called
      with a letter for a class that shouldn't be used.

      (However, if this class is not included in `GENERAL_REGS' and all
      of the insn patterns whose constraints permit this class are
      controlled by target switches, then GCC will automatically avoid
      using these registers when the target switches are opposed to
      them.)
*/
/* No definition */


/*
 `NON_SAVING_SETJMP'
      If this macro is defined and has a nonzero value, it means that
      `setjmp' and related functions fail to save the registers, or that
      `longjmp' fails to restore them.  To compensate, the compiler
      avoids putting variables in registers in functions that use
      `setjmp'.
*/
/* No definition */


/*
 `INCOMING_REGNO (OUT)'
      Define this macro if the target machine has register windows.
      This C expression returns the register number as seen by the
      called function corresponding to the register number OUT as seen
      by the calling function.  Return OUT if register number OUT is not
      an outbound register.
*/
/* No definition */


/*
 `OUTGOING_REGNO (IN)'
      Define this macro if the target machine has register windows.
      This C expression returns the register number as seen by the
      calling function corresponding to the register number IN as seen
      by the called function.  Return IN if register number IN is not an
      inbound register.
*/
/* No definition */


/* Section: Registers::Allocation Order */

/*
 `REG_ALLOC_ORDER'
      If defined, an initializer for a vector of integers, containing the
      numbers of hard registers in the order in which GNU CC should
      prefer to use them (from most preferred to least).

      If this macro is not defined, registers are used lowest numbered
      first (all else being equal).

      One use of this macro is on machines where the highest numbered
      registers must always be saved and the save-multiple-registers
      instruction supports only sequences of consecutive registers.  On
      such machines, define `REG_ALLOC_ORDER' to be an initializer that
      lists the highest numbered allocatable register first.
*/
/* We need this on jvm, because call-used regs should be used first,
   (so we dont need to push). Else start using registers from 0 and
   up.
    This preference is mainly because if we put call-used-regs from 0
   and up, then we cant use movem to push the rest, (who has to be pushed
   if we use them, and movem has to start with reg 0).
    NOTE: this is a place where register numbers have to be explicit
   (No macros).  Change here if you change which registers to use as
   call registers.
    Call-used-regs first, then 0 and up, last fp & sp & pc as fillers.
   Call-used in opposite order, so they will not conflict if a
   function has few args (<= 3) and it wants a scratch reg.
    Use struct-return address first, since very few functions use 
   structure return values.  (It is
   in fact quite unportable, and not re-entrant on some systems).
    The following is found to be quite optimal.  */
/*
 * #define REG_ALLOC_ORDER \
 * { 9, 13, 12, 11, 10, 1, 2, 3, 4, 5, 6, 7, 8, 14, 15, 16}
 */

/* --- jds31 ---
 * We will just keep the default values for the CLR
 */

/*
 `ORDER_REGS_FOR_LOCAL_ALLOC'
      A C statement (sans semicolon) to choose the order in which to
      allocate hard registers for pseudo-registers local to a basic
      block.

      Store the desired register order in the array `reg_alloc_order'.
      Element 0 should be the register to allocate first; element 1, the
      next register; and so on.

      The macro body should not assume anything about the contents of
      `reg_alloc_order' before execution of the macro.

      On most machines, it is not necessary to define this macro.
*/
/* No definition */


/* Section: Registers::Values in Registers */

/*
 `HARD_REGNO_NREGS (REGNO, MODE)'
      A C expression for the number of consecutive hard registers,
      starting at register number REGNO, required to hold a value of mode
      MODE.

      On a machine where all registers are exactly one word, a suitable
      definition of this macro is

           #define HARD_REGNO_NREGS(REGNO, MODE)            \
              ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1)  \
               / UNITS_PER_WORD))
*/
/* The VOIDmode test is so we can omit mode on anonymous insns.  */
#define HARD_REGNO_NREGS(REGNO, MODE)   \
 (MODE == VOIDmode \
  ? 1 : ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD))


/*
 `HARD_REGNO_MODE_OK (REGNO, MODE)'
      A C expression that is nonzero if it is permissible to store a
      value of mode MODE in hard register number REGNO (or in several
      registers starting with that one).  For a machine where all
      registers are equivalent, a suitable definition is

           #define HARD_REGNO_MODE_OK(REGNO, MODE) 1

      It is not necessary for this macro to check for the numbers of
      fixed registers, because the allocation mechanism considers them
      to be always occupied.

      On some machines, double-precision values must be kept in even/odd
      register pairs.  The way to implement that is to define this macro
      to reject odd register numbers for such modes.

      The minimum requirement for a mode to be OK in a register is that
      the `movMODE' instruction pattern support moves between the
      register and any other hard register for which the mode is OK; and
      that moving a value into the register and back out not alter it.

      Since the same instruction used to move `SImode' will work for all
      narrower integer modes, it is not necessary on any machine for
      `HARD_REGNO_MODE_OK' to distinguish between these modes, provided
      you define patterns `movhi', etc., to take advantage of this.  This
      is useful because of the interaction between `HARD_REGNO_MODE_OK'
      and `MODES_TIEABLE_P'; it is very desirable for all integer modes
      to be tieable.

      Many machines have special registers for floating point arithmetic.
      Often people assume that floating point machine modes are allowed
      only in floating point registers.  This is not true.  Any
      registers that can hold integers can safely *hold* a floating
      point machine mode, whether or not floating arithmetic can be done
      on it in those registers.  Integer move instructions can be used
      to move the values.

      On some machines, though, the converse is true: fixed-point machine
      modes may not go in floating registers.  This is true if the
      floating registers normalize any value stored in them, because
      storing a non-floating value there would garble it.  In this case,
      `HARD_REGNO_MODE_OK' should reject fixed-point machine modes in
      floating registers.  But if the floating registers do not
      automatically normalize, if you can store any bit pattern in one
      and retrieve it unchanged without a trap, then any machine mode
      may go in a floating register, so you can define this macro to say
      so.

      The primary significance of special floating registers is rather
      that they are the registers acceptable in floating point arithmetic
      instructions.  However, this is of no concern to
      `HARD_REGNO_MODE_OK'.  You handle it by writing the proper
      constraints for those instructions.

      On some machines, the floating registers are especially slow to
      access, so that it is better to store a value in a stack frame
      than in such a register if floating point arithmetic is not being
      done.  As long as the floating registers are not in class
      `GENERAL_REGS', they will not be used unless some pattern's
      constraint asks for one.
*/
/* Jvm permits all registers to hold all modes. */
#define HARD_REGNO_MODE_OK(REGNO, MODE) 1


/*
 `MODES_TIEABLE_P (MODE1, MODE2)'
      A C expression that is nonzero if it is desirable to choose
      register allocation so as to avoid move instructions between a
      value of mode MODE1 and a value of mode MODE2.

      If `HARD_REGNO_MODE_OK (R, MODE1)' and `HARD_REGNO_MODE_OK (R,
      MODE2)' are ever different for any R, then `MODES_TIEABLE_P (MODE1,
      MODE2)' must be zero.
*/
#define MODES_TIEABLE_P(MODE1, MODE2)  1


/* Section: Registers::Leaf Functions */
/* (no definitions) */

/* Section: Registers::Stack Registers */
/* (no definitions) */

/* Section: Registers::Obsolete Register Macros */
/* (no definitions) */


/* Section: Register Classes */

/*
 `enum reg_class'
      An enumeral type that must be defined with all the register class
      names as enumeral values.  `NO_REGS' must be first.  `ALL_REGS'
      must be the last register class, followed by one more enumeral
      value, `LIM_REG_CLASSES', which is not a register class but rather
      tells how many classes there are.

      Each register class has a number, which is the value of casting
      the class name to type `int'.  The number serves as an index in
      many of the tables described below.
*/
/* Jvm has only one kind of registers, so NO_REGS and ALL_REGS
   are the only classes.  */
/* NOTE: Because gcc 2.1 is broken when it comes to check reload operands
   strictly (i.e. it accepts 'r' if the operand is a stack slot), we
   use a fix to make !(GENERAL_REGS == ALL_REGS).
    The breaking part is that when constraints are checked strictly,
   and GENERAL_REGS == ALL_REGS, then instead of calling
   reg_fits_class_p (which includes a check to see if it really is a
   pseudo register) it assumes that everything is ok.
    It seems no other ports of gcc 2.1 have registers that are this
   general, and will not allow all types operands to all operators.
    (Vaxen has general registers, but allows any stack-relative operand
   for any register.)
   No other comments (than this one) is added.  The error is clearly
   in gcc, not this file.  You will find '#if 0':d lines below that
   reflects the fixes for this problem.

    It seems that 2.6.3 and later 2.7.2 has fixed this.  Try the
   correct definition later (may speed up compilation a little).
 */
enum reg_class { NO_REGS,
#if 0
#define GENERAL_REGS ALL_REGS
#else
                   GENERAL_REGS,
#endif
                   ALL_REGS,
                   LIM_REG_CLASSES };


/*
 `N_REG_CLASSES'
      The number of distinct register classes, defined as follows:

           #define N_REG_CLASSES (int) LIM_REG_CLASSES
*/
#define N_REG_CLASSES (int) LIM_REG_CLASSES


/*
 `REG_CLASS_NAMES'
      An initializer containing the names of the register classes as C
      string constants.  These names are used in writing some of the
      debugging dumps.
*/
#if 0
#define REG_CLASS_NAMES \
 {"NO_REGS", "ALL_REGS" }
#else
#define REG_CLASS_NAMES \
 {"NO_REGS", "GENERAL_REGS", "ALL_REGS" }
#endif


/*
 `REG_CLASS_CONTENTS'
      An initializer containing the contents of the register classes, as
      integers which are bit masks.  The Nth integer specifies the
      contents of class N.  The way the integer MASK is interpreted is
      that register R is in the class if `MASK & (1 << R)' is 1.

      When the machine has more than 32 registers, an integer does not
      suffice.  Then the integers are replaced by sub-initializers,
      braced groupings containing several integers.  Each
      sub-initializer must be suitable as an initializer for the type
      `HARD_REG_SET' which is defined in `hard-reg-set.h'.
*/
/* Don't put srp in here.  Keeping it out keeps gcc from using it.  */

#if 0
# define REG_CLASS_CONTENTS {0, 0xffff }
#else
# define REG_CLASS_CONTENTS {0, 0xffffffff, 0xffffffff }
#endif

/*
 `REGNO_REG_CLASS (REGNO)'
      A C expression whose value is a register class containing hard
      register REGNO.  In general there is more than one such class;
      choose a class which is "minimal", meaning that no smaller class
      also contains the register.
*/
#if 0
#define REGNO_REG_CLASS(REGNO) ALL_REGS
#else
#define REGNO_REG_CLASS(REGNO) GENERAL_REGS
#endif


/*
 `BASE_REG_CLASS'
      A macro whose definition is the name of the class to which a valid
      base register must belong.  A base register is one used in an
      address which is the register value plus a displacement.
*/
#if 0
#define BASE_REG_CLASS ALL_REGS
#else
#define BASE_REG_CLASS GENERAL_REGS
#endif


/*
 `INDEX_REG_CLASS'
      A macro whose definition is the name of the class to which a valid
      index register must belong.  An index register is one used in an
      address where its value is either multiplied by a scale factor or
      added to another register (as well as added to a displacement).
*/
#if 0
#define INDEX_REG_CLASS ALL_REGS
#else
#define INDEX_REG_CLASS GENERAL_REGS
#endif


/*
 `REG_CLASS_FROM_LETTER (CHAR)'
      A C expression which defines the machine-dependent operand
      constraint letters for register classes.  If CHAR is such a
      letter, the value should be the register class corresponding to
      it.  Otherwise, the value should be `NO_REGS'.  The register
      letter `r', corresponding to class `GENERAL_REGS', will not be
      passed to this macro; you do not need to handle it.
*/
/* Get reg_class from a letter such as appears in the machine description.
    No letters are used, since 'r' is used for any register. */
#define REG_CLASS_FROM_LETTER(C) NO_REGS


/*
 `REGNO_OK_FOR_BASE_P (NUM)'
      A C expression which is nonzero if register number NUM is suitable
      for use as a base register in operand addresses.  It may be either
      a suitable hard register or a pseudo register that has been
      allocated such a hard register.
*/
/* Since it uses reg_renumber, it is safe only once reg_renumber
   has been allocated, which happens in local-alloc.c.  */
#define REGNO_OK_FOR_BASE_P(REGNO) \
((REGNO) <= LAST_GENERAL_REGISTER || \
 (unsigned) reg_renumber[REGNO] <= LAST_GENERAL_REGISTER)


/*
 `REGNO_OK_FOR_INDEX_P (NUM)'
      A C expression which is nonzero if register number NUM is suitable
      for use as an index register in operand addresses.  It may be
      either a suitable hard register or a pseudo register that has been
      allocated such a hard register.

      The difference between an index register and a base register is
      that the index register may be scaled.  If an address involves the
      sum of two registers, neither one of them scaled, then either one
      may be labeled the "base" and the other the "index"; but whichever
      labeling is used must fit the machine's constraints of which
      registers may serve in each capacity.  The compiler will try both
      labelings, looking for one that is valid, and will reload one or
      both registers only if neither labeling works.
*/
/* Since it uses reg_renumber, it is safe only once reg_renumber
   has been allocated, which happens in local-alloc.c.  */
#define REGNO_OK_FOR_INDEX_P(REGNO) \
((REGNO) <= LAST_GENERAL_REGISTER || \
 (unsigned) reg_renumber[REGNO] <= LAST_GENERAL_REGISTER)


/*
 `PREFERRED_RELOAD_CLASS (X, CLASS)'
      A C expression that places additional restrictions on the register
      class to use when it is necessary to copy value X into a register
      in class CLASS.  The value is a register class; perhaps CLASS, or
      perhaps another, smaller class.  On many machines, the following
      definition is safe:

           #define PREFERRED_RELOAD_CLASS(X,CLASS) CLASS

      Sometimes returning a more restrictive class makes better code.
      For example, on the 68000, when X is an integer constant that is
      in range for a `moveq' instruction, the value of this macro is
      always `DATA_REGS' as long as CLASS includes the data registers.
      Requiring a data register guarantees that a `moveq' will be used.

      If X is a `const_double', by returning `NO_REGS' you can force X
      into a memory constant.  This is useful on certain machines where
      immediate floating values cannot be loaded into certain kinds of
      registers.
*/
/* It seems like gcc may send "NO_REGS" as the class.  Tho avoid
   forcing out a constant into the constant pool, we will trap this
   case and return something a bit more sane.  */
#define PREFERRED_RELOAD_CLASS(X,CLASS) \
 ((CLASS) == NO_REGS ? GENERAL_REGS : (CLASS))


/*
 `PREFERRED_OUTPUT_RELOAD_CLASS (X, CLASS)'
      Like `PREFERRED_RELOAD_CLASS', but for output reloads instead of
      input reloads.  If you don't define this macro, the default is to
      use CLASS, unchanged.
*/
/* No definition */


/*
 `LIMIT_RELOAD_CLASS (MODE, CLASS)'
      A C expression that places additional restrictions on the register
      class to use when it is necessary to be able to hold a value of
      mode MODE in a reload register for which class CLASS would
      ordinarily be used.

      Unlike `PREFERRED_RELOAD_CLASS', this macro should be used when
      there are certain modes that simply can't go in certain reload
      classes.

      The value is a register class; perhaps CLASS, or perhaps another,
      smaller class.

      Don't define this macro unless the target machine has limitations
      which require the macro to do something nontrivial.
*/
/* No definition */


/*
 `SECONDARY_RELOAD_CLASS (CLASS, MODE, X)'
 `SECONDARY_INPUT_RELOAD_CLASS (CLASS, MODE, X)'
 `SECONDARY_OUTPUT_RELOAD_CLASS (CLASS, MODE, X)'
      Many machines have some registers that cannot be copied directly
      to or from memory or even from other types of registers.  An
      example is the `MQ' register, which on most machines, can only be
      copied to or from general registers, but not memory.  Some
      machines allow copying all registers to and from memory, but
      require a scratch register for stores to some memory locations
      (e.g., those with symbolic address on the RT, and those with
      certain symbolic address on the Sparc when compiling PIC).  In
      some cases, both an intermediate and a scratch register are
      required.

      You should define these macros to indicate to the reload phase
      that it may need to allocate at least one register for a reload in
      addition to the register to contain the data.  Specifically, if
      copying X to a register CLASS in MODE requires an intermediate
      register, you should define `SECONDARY_INPUT_RELOAD_CLASS' to
      return the largest register class all of whose registers can be
      used as intermediate registers or scratch registers.

      If copying a register CLASS in MODE to X requires an intermediate
      or scratch register, `SECONDARY_OUTPUT_RELOAD_CLASS' should be
      defined to return the largest register class required.  If the
      requirements for input and output reloads are the same, the macro
      `SECONDARY_RELOAD_CLASS' should be used instead of defining both
      macros identically.

      The values returned by these macros are often `GENERAL_REGS'.
      Return `NO_REGS' if no spare register is needed; i.e., if X can be
      directly copied to or from a register of CLASS in MODE without
      requiring a scratch register.  Do not define this macro if it
      would always return `NO_REGS'.

      If a scratch register is required (either with or without an
      intermediate register), you should define patterns for
      `reload_inM' or `reload_outM', as required (*note Standard
      Names::..  These patterns, which will normally be implemented with
      a `define_expand', should be similar to the `movM' patterns,
      except that operand 2 is the scratch register.

      Define constraints for the reload register and scratch register
      that contain a single register class.  If the original reload
      register (whose class is CLASS) can meet the constraint given in
      the pattern, the value returned by these macros is used for the
      class of the scratch register.  Otherwise, two additional reload
      registers are required.  Their classes are obtained from the
      constraints in the insn pattern.

      X might be a pseudo-register or a `subreg' of a pseudo-register,
      which could either be in a hard register or in memory.  Use
      `true_regnum' to find out; it will return -1 if the pseudo is in
      memory and the hard register number if it is in a register.

      These macros should not be used in the case where a particular
      class of registers can only be copied to memory and not to another
      class of registers.  In that case, secondary reload registers are
      not needed and would not be helpful.  Instead, a stack location
      must be used to perform the copy and the `movM' pattern should use
      memory as a intermediate storage.  This case often occurs between
      floating-point and general registers.
*/
/* No definition */


/*
 `SECONDARY_MEMORY_NEEDED (CLASS1, CLASS2, M)'
      Certain machines have the property that some registers cannot be
      copied to some other registers without using memory.  Define this
      macro on those machines to be a C expression that is non-zero if
      objects of mode M in registers of CLASS1 can only be copied to
      registers of class CLASS2 by storing a register of CLASS1 into
      memory and loading that memory location into a register of CLASS2.

      Do not define this macro if its value would always be zero.
*/
/* No definition */


/*
 `SECONDARY_MEMORY_NEEDED_RTX (MODE)'
      Normally when `SECONDARY_MEMORY_NEEDED' is defined, the compiler
      allocates a stack slot for a memory location needed for register
      copies.  If this macro is defined, the compiler instead uses the
      memory location defined by this macro.

      Do not define this macro if you do not define
      `SECONDARY_MEMORY_NEEDED'.
*/
/* No definition */


/*
 `SECONDARY_MEMORY_NEEDED_MODE (MODE)'
      When the compiler needs a secondary memory location to copy
      between two registers of mode MODE, it normally allocates
      sufficient memory to hold a quantity of `BITS_PER_WORD' bits and
      performs the store and load operations in a mode that many bits
      wide and whose class is the same as that of MODE.

      This is right thing to do on most machines because it ensures that
      all bits of the register are copied and prevents accesses to the
      registers in a narrower mode, which some machines prohibit for
      floating-point registers.

      However, this default behavior is not correct on some machines,
      such as the DEC Alpha, that store short integers in floating-point
      registers differently than in integer registers.  On those
      machines, the default widening will not work correctly and you
      must define this macro to suppress that widening in some cases.
      See the file `alpha.h' for details.

      Do not define this macro if you do not define
      `SECONDARY_MEMORY_NEEDED' or if widening MODE to a mode that is
      `BITS_PER_WORD' bits wide is correct for your machine.
*/
/* No definition */


/*
 `SMALL_REGISTER_CLASSES'
      Normally the compiler avoids choosing registers that have been
      explicitly mentioned in the rtl as spill registers (these
      registers are normally those used to pass parameters and return
      values).  However, some machines have so few registers of certain
      classes that there would not be enough registers to use as spill
      registers if this were done.

      Define `SMALL_REGISTER_CLASSES' on these machines.  When it is
      defined, the compiler allows registers explicitly used in the rtl
      to be used as spill registers but avoids extending the lifetime of
      these registers.

      It is always safe to define this macro, but if you unnecessarily
      define it, you will reduce the amount of optimizations that can be
      performed in some cases.  If you do not define this macro when it
      is required, the compiler will run out of spill registers and
      print a fatal error message.  For most machines, you should not
      define this macro.
*/
/* No definition */


/*
 `CLASS_LIKELY_SPILLED_P (CLASS)'
      A C expression whose value is nonzero if pseudos that have been
      assigned to registers of class CLASS would likely be spilled
      because registers of CLASS are needed for spill registers.

      The default value of this macro returns 1 if CLASS has exactly one
      register and zero otherwise.  On most machines, this default
      should be used.  Only define this macro to some other expression
      if pseudo allocated by `local-alloc.c' end up in memory because
      their hard registers were needed for spill registers.  If this
      macro returns nonzero for those classes, those pseudos will only
      be allocated by `global.c', which knows how to reallocate the
      pseudo to another register.  If there would not be another
      register available for reallocation, you should not change the
      definition of this macro since the only effect of such a
      definition would be to slow down register allocation.
*/
/* No definition */


/*
 `CLASS_MAX_NREGS (CLASS, MODE)'
      A C expression for the maximum number of consecutive registers of
      class CLASS needed to hold a value of mode MODE.

      This is closely related to the macro `HARD_REGNO_NREGS'.  In fact,
      the value of the macro `CLASS_MAX_NREGS (CLASS, MODE)' should be
      the maximum value of `HARD_REGNO_NREGS (REGNO, MODE)' for all
      REGNO values in the class CLASS.

      This macro helps control the handling of multiple-word values in
      the reload pass.
*/
/* For Jvm, this is always the size of MODE in words,
   since all registers are the same size.  */
/* To use omitted modes in patterns with reload constraints, you
   must say widest size allowed for VOIDmode. */
#define CLASS_MAX_NREGS(CLASS, MODE)    \
 ((MODE) == VOIDmode \
  ? 1 : ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD))


/*
 `CLASS_CANNOT_CHANGE_SIZE'
      If defined, a C expression for a class that contains registers
      which the compiler must always access in a mode that is the same
      size as the mode in which it loaded the register.

      For the example, loading 32-bit integer or floating-point objects
      into floating-point registers on the Alpha extends them to 64-bits.
      Therefore loading a 64-bit object and then storing it as a 32-bit
      object does not store the low-order 32-bits, as would be the case
      for a normal register.  Therefore, `alpha.h' defines this macro as
      `FLOAT_REGS'.
*/
/* No definition */


/*
 `CONST_OK_FOR_LETTER_P (VALUE, C)'
      A C expression that defines the machine-dependent operand
      constraint letters that specify particular ranges of integer
      values.  If C is one of those letters, the expression should check
      that VALUE, an integer, is in the appropriate range and return 1
      if so, 0 otherwise.  If C is not one of those letters, the value
      should be 0 regardless of VALUE.
*/
/* The letters I, J, K, L and M in a register constraint string
   can be used to stand for particular ranges of immediate operands.
   This macro defines what the ranges are.
   C is the letter, and VALUE is a constant value.
   Return 1 if VALUE is in the range specified by C.
    We are actually out of letters (could use ten more),
   which makes us use C-code in the 'md' file. */

#define CONST_OK_FOR_LETTER_P(VALUE, C)                                       \
  ((C) == 'I' ? (VALUE) >= -32 && (VALUE) <= 31 : /* MOVEQ CMPQ ANDQ ORQ */   \
   (C) == 'J' ? (VALUE) >= 0 && (VALUE) <= 63 :   /* ADDQ SUBQ */             \
   (C) == 'K' ? (VALUE) >= 0 && (VALUE) <= 31 :   /* ASR BTST LSR LSL */      \
   (C) == 'L' ? (VALUE) >= -32768 && (VALUE) <= 32767 : /* 16bit signed */    \
   (C) == 'M' ? (VALUE) == 0 :                    /* constant 0 for CLEAR */  \
   (C) == 'N' ? (VALUE) >= -63 && (VALUE) < 0 :   /* negative ADDQ SUBQ */    \
   (C) == 'O' ? (VALUE) >= 0 && (VALUE) <= 65535  /* quick:d ints, QI && HI */\
                && ((VALUE) >= (65535-31)                                     \
                    || ((VALUE) >= (255-31)                                   \
                        && (VALUE) <= 255 )):                                 \
   (C) == 'P' ? (VALUE) >= -32768 && (VALUE) <= 65535 : /* 16-bits */         \
   0)


/*
 `CONST_DOUBLE_OK_FOR_LETTER_P (VALUE, C)'
      A C expression that defines the machine-dependent operand
      constraint letters that specify particular ranges of
      `const_double' values.

      If C is one of those letters, the expression should check that
      VALUE, an RTX of code `const_double', is in the appropriate range
      and return 1 if so, 0 otherwise.  If C is not one of those
      letters, the value should be 0 regardless of VALUE.

      `const_double' is used for all floating-point constants and for
      `DImode' fixed-point constants.  A given letter can accept either
      or both kinds of values.  It can use `GET_MODE' to distinguish
      between these kinds.
*/
/* It is really simple to make up a 0.0; it is the same as int-0 in IEEE754. */
#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C)                  \
 ((C) == 'G' && ((VALUE) == CONST0_RTX (DFmode)                 \
                 || (VALUE) == CONST0_RTX (SFmode)))


/*
 `EXTRA_CONSTRAINT (VALUE, C)'
      A C expression that defines the optional machine-dependent
      constraint letters that can be used to segregate specific types of
      operands, usually memory references, for the target machine.
      Normally this macro will not be defined.  If it is required for a
      particular target machine, it should return 1 if VALUE corresponds
      to the operand type represented by the constraint letter C.  If C
      is not defined as an extra constraint, the value returned should
      be 0 regardless of VALUE.

      For example, on the ROMP, load instructions cannot have their
      output in r0 if the memory reference contains a symbolic address.
      Constraint letter `Q' is defined as representing a memory address
      that does *not* contain a symbolic address.  An alternative is
      specified with a `Q' constraint on the input and `r' on the
      output.  The next alternative specifies `m' on the input and a
      register class that does not include r0 on the output.
*/
/* We need this on jvm to distinguish delay-slottable addressing modes. */
#define EXTRA_CONSTRAINT(X, C) \
   ((C) == 'Q' ? EXTRA_CONSTRAINT_Q(X) : /* Slottable address mode ?  */ \
    (C) == 'R' ? EXTRA_CONSTRAINT_R(X) : /* Operand to BDAP or BIAP ? */ \
    (C) == 'T' ? EXTRA_CONSTRAINT_T(X) : /* Three address addr mode ? */ \
    0)

#define EXTRA_CONSTRAINT_Q(X) \
   ((BASE_P(X) && REGNO(X) != PC_REGNUM)        /* reg */   \
    || (GET_CODE(X) == MEM && BASE_P(XEXP(X,0)) /* [reg] */ \
        && REGNO(XEXP(X,0)) != PC_REGNUM))

#define EXTRA_CONSTRAINT_R(X) \
   (BIAP_INDEX_P(X)         /* BIAP; r.S */ \
    || BDAP_INDEX_P(X)      /* [reg] or (int) [reg] maybe with post incr */ \
    || CONSTANT_INDEX_P(X))

#define EXTRA_CONSTRAINT_T(X) \
   (GET_CODE(X) == MEM          /* all are [...], of course */\
    && ((GET_CODE(XEXP(X, 0)) == MEM \
         && (BASE_OR_AUTOINCR_P(XEXP(XEXP(X, 0), 0)))) /*[[reg]] or [[reg+]]*/\
        || CONSTANT_P(XEXP(X,0))                       /* [const] */\
        || (GET_CODE(XEXP(X,0)) == PLUS /* some indexed; [... + ...] */\
            &&((BASE_P(XEXP(XEXP(X, 0), 0)) /* bdap: [reg+(8|16|32)bitoffs] */\
                && CONSTANT_INDEX_P(XEXP(XEXP(X, 0), 1)))\
               || (BASE_P(XEXP(XEXP(X, 0), 1)) /*(swap arguments to above) */\
                   && CONSTANT_INDEX_P(XEXP(XEXP(X, 0), 0)))\
               || (BASE_P(XEXP(XEXP(X, 0), 0)) /* bdap: [reg+[reg(+)].S] */\
                   && BDAP_INDEX_P(XEXP(XEXP(X, 0), 1)))\
               || (BASE_P(XEXP(XEXP(X, 0), 1)) /*(swap arguments to above) */\
                   && BDAP_INDEX_P(XEXP(XEXP(X, 0), 0)))\
               || (BASE_P(XEXP(XEXP(X, 0), 0)) /* biap: [reg+reg.s] */\
                   && BIAP_INDEX_P(XEXP(XEXP(X, 0), 1)))\
               || (BASE_P(XEXP(XEXP(X, 0), 1)) /* swap arguments to above */\
                   && BIAP_INDEX_P(XEXP(XEXP(X, 0), 0)))))\
        /* || (BASE_P(XEXP(X,0)))  / * is three-addr too; NONOPTIMAL [reg+0] */))


/* Section: Stack and Calling::Frame Layout */

/*
 `STACK_GROWS_DOWNWARD'
      Define this macro if pushing a word onto the stack moves the stack
      pointer to a smaller address.

      When we say, "define this macro if ...," it means that the
      compiler checks this macro only with `#ifdef' so the precise
      definition used does not matter.
*/
#define STACK_GROWS_DOWNWARD

/*
 `FRAME_GROWS_DOWNWARD'
      Define this macro if the addresses of local variable slots are at
      negative offsets from the frame pointer.
*/
#define FRAME_GROWS_DOWNWARD


/*
 `ARGS_GROW_DOWNWARD'
      Define this macro if successive arguments to a function occupy
      decreasing addresses on the stack.
*/
/* No definition */


/*
 `STARTING_FRAME_OFFSET'
      Offset from the frame pointer to the first local variable slot to
      be allocated.

      If `FRAME_GROWS_DOWNWARD', find the next slot's offset by
      subtracting the first slot's length from `STARTING_FRAME_OFFSET'.
      Otherwise, it is found by adding the length of the first slot to
      the value `STARTING_FRAME_OFFSET'.
*/
/* It seems to be indicated in the code (at least 2.1) that this is
   better a constant, and best 0. */
#define STARTING_FRAME_OFFSET 0


/*
 `STACK_POINTER_OFFSET'
      Offset from the stack pointer register to the first location at
      which outgoing arguments are placed.  If not specified, the
      default value of zero is used.  This is the proper value for most
      machines.

      If `ARGS_GROW_DOWNWARD', this is the offset to the location above
      the first location at which outgoing arguments are placed.
*/
/* No definition */


/*
 `FIRST_PARM_OFFSET (FUNDECL)'
      Offset from the argument pointer register to the first argument's
      address.  On some machines it may depend on the data type of the
      function.

      If `ARGS_GROW_DOWNWARD', this is the offset to the location above
      the first argument's address.
*/
/* Is saved-fp + saved-return-address (if not leaf function) */
/* We cannot use frame_pointer_needed here, so adjust stack in
   function_prologue() if needed.  Same goes for whether this is a
   leaf-function or not (if SRP is saved). */
/* --- jds31 --- FIXME
 * Not really sure about this, on CLR. Do we need to save return
 * address? CLR does this for us, automatically, I think.
 * I know we probably need to save fp, if we are using it ...
 */

#define FIRST_PARM_OFFSET(FNDECL) (4+4)


/*
 `STACK_DYNAMIC_OFFSET (FUNDECL)'
      Offset from the stack pointer register to an item dynamically
      allocated on the stack, e.g., by `alloca'.

      The default value for this macro is `STACK_POINTER_OFFSET' plus the
      length of the outgoing arguments.  The default is correct for most
      machines.  See `function.c' for details.
*/
/* No definition */


/*
 `DYNAMIC_CHAIN_ADDRESS (FRAMEADDR)'
      A C expression whose value is RTL representing the address in a
      stack frame where the pointer to the caller's frame is stored.
      Assume that FRAMEADDR is an RTL expression for the address of the
      stack frame itself.

      If you don't define this macro, the default is to return the value
      of FRAMEADDR--that is, the stack frame address is also the address
      of the stack word that points to the previous frame.
*/
/* No definition (seems like the default should be correct) */


/*
 `SETUP_FRAME_ADDRESSES ()'
      If defined, a C expression that produces the machine-specific code
      to setup the stack so that arbitrary frames can be accessed.  For
      example, on the Sparc, we must flush all of the register windows
      to the stack before we can access arbitrary stack frames.  This
      macro will seldom need to be defined.
*/
/* No definition */


/*
 `RETURN_ADDR_RTX (COUNT, FRAMEADDR)'
      A C expression whose value is RTL representing the value of the
      return address for the frame COUNT steps up from the current frame.
      fRAMEADDR is the frame pointer of the COUNT frame, or the frame
      pointer of the COUNT - 1 frame if `RETURN_ADDR_IN_PREVIOUS_FRAME'
      is defined.
*/
/* Not defined (should be if we want to use __builtin_return_address() ) */


/*
 `RETURN_ADDR_IN_PREVIOUS_FRAME'
      Define this if the return address of a particular stack frame is
      accessed from the frame pointer of the previous stack frame.
*/
/* Not defined */


/* Section: Stack and Calling::Frame Registers */

/* First a few convenience definitions that should fit into this section. */
/* Convenience for jvm (used above).  It used to be used by gcc, but no more. */
/* "pc" is 15  */
/* CLR program counter is r31 */
#define PC_REGNUM 31

/* Register used for return addresses (Jvm only) */
/* --- jds31 --- not sure about this,
 * but CLR srp is r30
 */
#define SRP_REGNUM 30


/*
 `STACK_POINTER_REGNUM'
      The register number of the stack pointer register, which must also
      be a fixed register according to `FIXED_REGISTERS'.  On most
      machines, the hardware determines which register this is.
*/
/* Register to use for pushing function arguments.  Not actually
   defined by the hardware, but it would not be so smart to put it
   somewhere else. */
/* CLR sp is r29 */
#define STACK_POINTER_REGNUM 29


/*
 `FRAME_POINTER_REGNUM'
      The register number of the frame pointer register, which is used to
      access automatic variables in the stack frame.  On some machines,
      the hardware determines which register this is.  On other
      machines, you can choose any register you wish for this purpose.
*/
/* Register used for frame pointer.  This is also the last of the saved
   registers, when a frame pointer is not used. */
/* CLR fp is r28 */
#define FRAME_POINTER_REGNUM 28


/*
 `HARD_FRAME_POINTER_REGNUM'
      On some machines the offset between the frame pointer and starting
      offset of the automatic variables is not known until after register
      allocation has been done (for example, because the saved registers
      are between these two locations).  On those machines, define
      `FRAME_POINTER_REGNUM' the number of a special, fixed register to
      be used internally until the offset is known, and define
      `HARD_FRAME_POINTER_REGNUM' to be actual the hard register number
      used for the frame pointer.

      You should define this macro only in the very rare circumstances
      when it is not possible to calculate the offset between the frame
      pointer and the automatic variables until after register
      allocation has been completed.  When this macro is defined, you
      must also indicate in your definition of `ELIMINABLE_REGS' how to
      eliminate `FRAME_POINTER_REGNUM' into either
      `HARD_FRAME_POINTER_REGNUM' or `STACK_POINTER_REGNUM'.

      Do not define this macro if it would be the same as
      `FRAME_POINTER_REGNUM'.
*/
/* Not defined */


/*
 `ARG_POINTER_REGNUM'
      The register number of the arg pointer register, which is used to
      access the function's argument list.  On some machines, this is
      the same as the frame pointer register.  On some machines, the
      hardware determines which register this is.  On other machines,
      you can choose any register you wish for this purpose.  If this is
      not the same register as the frame pointer register, then you must
      mark it as a fixed register according to `FIXED_REGISTERS', or
      arrange to be able to eliminate it (*note Elimination::.).
*/
#define ARG_POINTER_REGNUM FRAME_POINTER_REGNUM


/*
 `STATIC_CHAIN_REGNUM'
 `STATIC_CHAIN_INCOMING_REGNUM'
      Register numbers used for passing a function's static chain
      pointer.  If register windows are used, the register number as
      seen by the called function is `STATIC_CHAIN_INCOMING_REGNUM',
      while the register number as seen by the calling function is
      `STATIC_CHAIN_REGNUM'.  If these registers are the same,
      `STATIC_CHAIN_INCOMING_REGNUM' need not be defined.

      The static chain register need not be a fixed register.

      If the static chain is passed in memory, these macros should not be
      defined; instead, the next two macros should be defined.
*/
/* It is NOT TESTED if this definition is allright.  */
/* CLR staic chain ptr is r27 */
#define STATIC_CHAIN_REGNUM 27


/*
 `STATIC_CHAIN'
 `STATIC_CHAIN_INCOMING'
      If the static chain is passed in memory, these macros provide rtx
      giving `mem' expressions that denote where they are stored.
      `STATIC_CHAIN' and `STATIC_CHAIN_INCOMING' give the locations as
      seen by the calling and called functions, respectively.  Often the
      former will be at an offset from the stack pointer and the latter
      at an offset from the frame pointer.

      The variables `stack_pointer_rtx', `frame_pointer_rtx', and
      `arg_pointer_rtx' will have been initialized prior to the use of
      these macros and should be used to refer to those items.

      If the static chain is passed in a register, the two previous
      macros should be defined instead.
*/
/* Not defined */


/* Section: Stack and Calling::Elimination */

/*
 `FRAME_POINTER_REQUIRED'
      A C expression which is nonzero if a function must have and use a
      frame pointer.  This expression is evaluated  in the reload pass.
      If its value is nonzero the function will have a frame pointer.

      The expression can in principle examine the current function and
      decide according to the facts, but on most machines the constant 0
      or the constant 1 suffices.  Use 0 when the machine allows code to
      be generated with no frame pointer, and doing so saves some time
      or space.  Use 1 when there is no possible advantage to avoiding a
      frame pointer.

      In certain cases, the compiler does not know how to produce valid
      code without a frame pointer.  The compiler recognizes those cases
      and automatically gives the function a frame pointer regardless of
      what `FRAME_POINTER_REQUIRED' says.  You don't need to worry about
      them.

      In a function that does not require a frame pointer, the frame
      pointer register can be allocated for ordinary usage, unless you
      mark it as a fixed register.  See `FIXED_REGISTERS' for more
      information.
*/
/* Really only needed if the stack frame has variable length (alloca()
   or variable sized local arguments (Gnu extension). */
#define FRAME_POINTER_REQUIRED 0


/*
 `INITIAL_FRAME_POINTER_OFFSET (DEPTH-VAR)'
      A C statement to store in the variable DEPTH-VAR the difference
      between the frame pointer and the stack pointer values immediately
      after the function prologue.  The value would be computed from
      information such as the result of `get_frame_size ()' and the
      tables of registers `regs_ever_live' and `call_used_regs'.

      If `ELIMINABLE_REGS' is defined, this macro will be not be used and
      need not be defined.  Otherwise, it must be defined even if
      `FRAME_POINTER_REQUIRED' is defined to always be true; in that
      case, you may set DEPTH-VAR to anything.
*/
/* Note that if NON_SAVING_SETJMP then current_function_calls_setjmp
   must be considered. */
/* FIXME - not sure about this one */
#define INITIAL_FRAME_POINTER_OFFSET(DEPTH) \
    { (DEPTH) = initial_fp_sp_offset();}

extern int initial_fp_sp_offset(void);


/*
 `ELIMINABLE_REGS'
      If defined, this macro specifies a table of register pairs used to
      eliminate unneeded registers that point into the stack frame.  If
      it is not defined, the only elimination attempted by the compiler
      is to replace references to the frame pointer with references to
      the stack pointer.

      The definition of this macro is a list of structure
      initializations, each of which specifies an original and
      replacement register.

      On some machines, the position of the argument pointer is not
      known until the compilation is completed.  In such a case, a
      separate hard register must be used for the argument pointer.
      This register can be eliminated by replacing it with either the
      frame pointer or the argument pointer, depending on whether or not
      the frame pointer has been eliminated.

      In this case, you might specify:
           #define ELIMINABLE_REGS  \
           {{ARG_POINTER_REGNUM, STACK_POINTER_REGNUM}, \
            {ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM}, \
            {FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}}

      Note that the elimination of the argument pointer with the stack
      pointer is specified first since that is the preferred elimination.
*/
/* Not defined */


/*
 `CAN_ELIMINATE (FROM-REG, TO-REG)'
      A C expression that returns non-zero if the compiler is allowed to
      try to replace register number FROM-REG with register number
      TO-REG.  This macro need only be defined if `ELIMINABLE_REGS' is
      defined, and will usually be the constant 1, since most of the
      cases preventing register elimination are things that the compiler
      already knows about.
*/
/* Not defined */


/*
 `INITIAL_ELIMINATION_OFFSET (FROM-REG, TO-REG, OFFSET-VAR)'
      This macro is similar to `INITIAL_FRAME_POINTER_OFFSET'.  It
      specifies the initial difference between the specified pair of
      registers.  This macro must be defined if `ELIMINABLE_REGS' is
      defined.
*/
/* Not defined */


/*
 `LONGJMP_RESTORE_FROM_STACK'
      Define this macro if the `longjmp' function restores registers from
      the stack frames, rather than from those saved specifically by
      `setjmp'.  Certain quantities must not be kept in registers across
      a call to `setjmp' on such machines.
*/
/* Not defined */

/* Section: Stack and Calling::Stack Arguments */

/*
 `PROMOTE_PROTOTYPES'
      Define this macro if an argument declared in a prototype as an
      integral type smaller than `int' should actually be passed as an
      `int'.  In addition to avoiding errors in certain cases of
      mismatch, it also makes for better code on certain machines.
*/
/* Since many parameters take up one register each in any case, this
   seems like a good idea. */
#define PROMOTE_PROTOTYPES 1


/*
 `PUSH_ROUNDING (NPUSHED)'
      A C expression that is the number of bytes actually pushed onto the
      stack when an instruction attempts to push NPUSHED bytes.

      If the target machine does not have a push instruction, do not
      define this macro.  That directs GNU CC to use an alternate
      strategy: to allocate the entire argument block and then store the
      arguments into it.

      On some machines, the definition

           #define PUSH_ROUNDING(BYTES) (BYTES)

      will suffice.  But on other machines, instructions that appear to
      push one byte actually push two bytes in an attempt to maintain
      alignment.  Then the definition should be

           #define PUSH_ROUNDING(BYTES) (((BYTES) + 1) & ~1)
*/
/* Not defined */


/*
 `ACCUMULATE_OUTGOING_ARGS'
      If defined, the maximum amount of space required for outgoing
      arguments will be computed and placed into the variable
      `current_function_outgoing_args_size'.  No space will be pushed
      onto the stack for each call; instead, the function prologue should
      increase the stack frame size by this amount.

      Defining both `PUSH_ROUNDING' and `ACCUMULATE_OUTGOING_ARGS' is
      not proper.
*/
#define ACCUMULATE_OUTGOING_ARGS 1


/*
 `REG_PARM_STACK_SPACE (FNDECL)'
      Define this macro if functions should assume that stack space has
      been allocated for arguments even when their values are passed in
      registers.

      The value of this macro is the size, in bytes, of the area
      reserved for arguments passed in registers for the function
      represented by FNDECL.

      This space can be allocated by the caller, or be a part of the
      machine-dependent stack frame: `OUTGOING_REG_PARM_STACK_SPACE' says
      which.
*/
/* Not defined */


/*
 `MAYBE_REG_PARM_STACK_SPACE'
 `FINAL_REG_PARM_STACK_SPACE (CONST_SIZE, VAR_SIZE)'
      Define these macros in addition to the one above if functions might
      allocate stack space for arguments even when their values are
      passed in registers.  These should be used when the stack space
      allocated for arguments in registers is not a simple constant
      independent of the function declaration.

      The value of the first macro is the size, in bytes, of the area
      that we should initially assume would be reserved for arguments
      passed in registers.

      The value of the second macro is the actual size, in bytes, of the
      area that will be reserved for arguments passed in registers.
      This takes two arguments: an integer representing the number of
      bytes of fixed sized arguments on the stack, and a tree
      representing the number of bytes of variable sized arguments on
      the stack.

      When these macros are defined, `REG_PARM_STACK_SPACE' will only be
      called for libcall functions, the current function, or for a
      function being called when it is known that such stack space must
      be allocated.  In each case this value can be easily computed.

      When deciding whether a called function needs such stack space,
      and how much space to reserve, GNU CC uses these two macros
      instead of `REG_PARM_STACK_SPACE'.
*/
/* Not defined */


/*
 `OUTGOING_REG_PARM_STACK_SPACE'
      Define this if it is the responsibility of the caller to allocate
      the area reserved for arguments passed in registers.

      If `ACCUMULATE_OUTGOING_ARGS' is defined, this macro controls
      whether the space for these arguments counts in the value of
      `current_function_outgoing_args_size'.
*/
/* Not defined */


/*
 `STACK_PARMS_IN_REG_PARM_AREA'
      Define this macro if `REG_PARM_STACK_SPACE' is defined, but the
      stack parameters don't skip the area specified by it.

      Normally, when a parameter is not passed in registers, it is
      placed on the stack beyond the `REG_PARM_STACK_SPACE' area.
      Defining this macro suppresses this behavior and causes the
      parameter to be passed on the stack in its natural location.
*/
/* Not defined */


/*
 `RETURN_POPS_ARGS (FUNDECL, FUNTYPE, STACK-SIZE)'
      A C expression that should indicate the number of bytes of its own
      arguments that a function pops on returning, or 0 if the function
      pops no arguments and the caller must therefore pop them all after
      the function returns.

      FUNDECL is a C variable whose value is a tree node that describes
      the function in question.  Normally it is a node of type
      `FUNCTION_DECL' that describes the declaration of the function.
      From this it is possible to obtain the DECL_MACHINE_ATTRIBUTES of
      the function.

      FUNTYPE is a C variable whose value is a tree node that describes
      the function in question.  Normally it is a node of type
      `FUNCTION_TYPE' that describes the data type of the function.
      From this it is possible to obtain the data types of the value and
      arguments (if known).

      When a call to a library function is being considered, FUNTYPE
      will contain an identifier node for the library function.  Thus, if
      you need to distinguish among various library functions, you can
      do so by their names.  Note that "library function" in this
      context means a function used to perform arithmetic, whose name is
      known specially in the compiler and was not mentioned in the C
      code being compiled.

      STACK-SIZE is the number of bytes of arguments passed on the
      stack.  If a variable number of bytes is passed, it is zero, and
      argument popping will always be the responsibility of the calling
      function.

      On the Vax, all functions always pop their arguments, so the
      definition of this macro is STACK-SIZE.  On the 68000, using the
      standard calling convention, no functions pop their arguments, so
      the value of the macro is always 0 in this case.  But an
      alternative calling convention is available in which functions
      that take a fixed number of arguments pop them but other functions
      (such as `printf') pop nothing (the caller pops all).  When this
      convention is in use, FUNTYPE is examined to determine whether a
      function takes a fixed number of arguments.
*/
/* On Jvm, RET just restores PC */
#define RETURN_POPS_ARGS(FUNDECL,FUNTYPE,STACKSIZE) 0


/* Section: Stack and Calling::Register Arguments */

/*
 `FUNCTION_ARG (CUM, MODE, TYPE, NAMED)'
      A C expression that controls whether a function argument is passed
      in a register, and which register.

      The arguments are CUM, which summarizes all the previous
      arguments; MODE, the machine mode of the argument; TYPE, the data
      type of the argument as a tree node or 0 if that is not known
      (which happens for C support library functions); and NAMED, which
      is 1 for an ordinary argument and 0 for nameless arguments that
      correspond to `...' in the called function's prototype.

      The value of the expression should either be a `reg' RTX for the
      hard register in which to pass the argument, or zero to pass the
      argument on the stack.

      For machines like the Vax and 68000, where normally all arguments
      are pushed, zero suffices as a definition.

      The usual way to make the ANSI library `stdarg.h' work on a machine
      where some arguments are usually passed in registers, is to cause
      nameless arguments to be passed on the stack instead.  This is done
      by making `FUNCTION_ARG' return 0 whenever NAMED is 0.

      You may use the macro `MUST_PASS_IN_STACK (MODE, TYPE)' in the
      definition of this macro to determine if this argument is of a
      type that must be passed in the stack.  If `REG_PARM_STACK_SPACE'
      is not defined and `FUNCTION_ARG' returns non-zero for such an
      argument, the compiler will abort.  If `REG_PARM_STACK_SPACE' is
      defined, the argument will be computed in the stack and then
      loaded into a register.
*/

/* --- jds31 ---
 * To pass all arguments on the stack, use the following definition ...
 *
 */

/*
 * #define FUNCTION_ARG(CUM, MODE, TYPE, NAMED)  0
 */

/* --- jds31 ---
 * To pass first N args in registers, use the following definition ...
 * Note that N == MAX_ARGS_IN_REGS, and we can only pass args
 * in registers if they are not address-taken. Otherwise, args are
 * still passed on the stack.
 */


#define FUNCTION_ARG(CUM, MODE, TYPE, NAMED) \
         ((CUM).regs < MAX_ARGS_IN_REGS  \
           ? gen_rtx(REG, MODE, (FIRST_ARG_REG)+(CUM).regs) \
          : ((rtx) 0))


/*
**** --- jds31 --- this is orig version, from egcs-jvm ...
****               it doesn't work, I think that is because 
****               we haven't defined macro 
****               MUST_PASS_IN_STACK anywhere.

 #define FUNCTION_ARG(CUM, MODE, TYPE, NAMED) \
        ((CUM).regs < MAX_ARGS_IN_REGS && !MUST_PASS_IN_STACK (MODE, TYPE) \
         && (GET_MODE_BITSIZE(MODE) <= 32 || TARGET_LIBFUNC || (CUM).lib)  \
        ? gen_rtx(REG, MODE, (FIRST_ARG_REG)+(CUM).regs)                   \
        : ((rtx) 0))
*/

/*
 `FUNCTION_INCOMING_ARG (CUM, MODE, TYPE, NAMED)'
      Define this macro if the target machine has "register windows", so
      that the register in which a function sees an arguments is not
      necessarily the same as the one in which the caller passed the
      argument.

      For such machines, `FUNCTION_ARG' computes the register in which
      the caller passes the value, and `FUNCTION_INCOMING_ARG' should be
      defined in a similar fashion to tell the function being called
      where the arguments will arrive.

      If `FUNCTION_INCOMING_ARG' is not defined, `FUNCTION_ARG' serves
      both purposes.
*/
/* Note that the only difference between this and the previous, is
   that this one isnt ignoring the function definition or declaration. */
#define FUNCTION_INCOMING_ARG(CUM, MODE, TYPE, NAMED) \
           ((NAMED) && (CUM).regs < MAX_ARGS_IN_REGS \
            && !MUST_PASS_IN_STACK (MODE, TYPE)\
            && (GET_MODE_BITSIZE(MODE) <= 32 || TARGET_LIBFUNC || (CUM).lib)\
           ? gen_rtx(REG, MODE, FIRST_ARG_REG_IN+(CUM).regs) \
           : ((rtx) 0))

/*
 `FUNCTION_ARG_PARTIAL_NREGS (CUM, MODE, TYPE, NAMED)'
      A C expression for the number of words, at the beginning of an
      argument, must be put in registers.  The value must be zero for
      arguments that are passed entirely in registers or that are
      entirely pushed on the stack.

      On some machines, certain arguments must be passed partially in
      registers and partially in memory.  On these machines, typically
      the first N words of arguments are passed in registers, and the
      rest on the stack.  If a multi-word argument (a `double' or a
      structure) crosses that boundary, its first few words must be
      passed in registers and the rest must be pushed.  This macro tells
      the compiler when this occurs, and how many of the words should go
      in registers.

      `FUNCTION_ARG' for these arguments should return the first
      register to be used by the caller for this argument; likewise
      `FUNCTION_INCOMING_ARG', for the called function.
*/
/* Not defined */


/*
 `FUNCTION_ARG_PASS_BY_REFERENCE (CUM, MODE, TYPE, NAMED)'
      A C expression that indicates when an argument must be passed by
      reference.  If nonzero for an argument, a copy of that argument is
      made in memory and a pointer to the argument is passed instead of
      the argument itself.  The pointer is passed in whatever way is
      appropriate for passing a pointer to that type.

      On machines where `REG_PARM_STACK_SPACE' is not defined, a suitable
      definition of this macro might be
           #define FUNCTION_ARG_PASS_BY_REFERENCE\
           (CUM, MODE, TYPE, NAMED)  \
             MUST_PASS_IN_STACK (MODE, TYPE)
*/
/* Structs may be passed by value, but they must not be more than 4
   bytes long.
    Since we support long longs, we must be able to call a libfunc
   with an 8-byte entity (i.e. long long).  This will be safe if we
   know what we're doing when we use -mlibfunc.  No long long libfuncs
   take more than two parameters in, so it is ok if we have at least 4
   argregs.  */
#define FUNCTION_ARG_PASS_BY_REFERENCE(CUM, MODE, TYPE, NAMED) \
  (MUST_PASS_IN_STACK(MODE, TYPE) /* I'm not sure this one is necessary. */ \
   || (FUNCTION_ARG_SIZE(MODE,TYPE) > 4 && !TARGET_LIBFUNC && !(CUM).lib))

/* Good to have.  Not standard. */
#define FUNCTION_ARG_SIZE(MODE, TYPE)   \
  ((MODE) != BLKmode ? GET_MODE_SIZE (MODE) : int_size_in_bytes (TYPE))


/*
 `FUNCTION_ARG_CALLEE_COPIES (CUM, MODE, TYPE, NAMED)'
      If defined, a C expression that indicates when it is the called
      function's responsibility to make a copy of arguments passed by
      invisible reference.  Normally, the caller makes a copy and passes
      the address of the copy to the routine being called.  When
      FUNCTION_ARG_CALLEE_COPIES is defined and is nonzero, the caller
      does not make a copy.  Instead, it passes a pointer to the "live"
      value.  The called function must not modify this value.  If it can
      be determined that the value won't be modified, it need not make a
      copy; otherwise a copy must be made.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `CUMULATIVE_ARGS'
      A C type for declaring a variable that is used as the first
      argument of `FUNCTION_ARG' and other related values.  For some
      target machines, the type `int' suffices and can hold the number
      of bytes of argument so far.

      There is no need to record in `CUMULATIVE_ARGS' anything about the
      arguments that have been passed on the stack.  The compiler has
      other variables to keep track of that.  For target machines on
      which all arguments are passed on the stack, there is no need to
      store anything in `CUMULATIVE_ARGS'; however, the data structure
      must exist and should not be empty, so use `int'.
*/
#define CUMULATIVE_ARGS struct cumu_args

struct cumu_args {int regs; int lib;};


/*
 `INIT_CUMULATIVE_ARGS (CUM, FNTYPE, LIBNAME)'
      A C statement (sans semicolon) for initializing the variable CUM
      for the state at the beginning of the argument list.  The variable
      has type `CUMULATIVE_ARGS'.  The value of FNTYPE is the tree node
      for the data type of the function which will receive the args, or 0
      if the args are to a compiler support library function.

      When processing a call to a compiler support library function,
      LIBNAME identifies which one.  It is a `symbol_ref' rtx which
      contains the name of the function, as a string.  LIBNAME is 0 when
      an ordinary C function call is being processed.  Thus, each time
      this macro is called, either LIBNAME or FNTYPE is nonzero, but
      never both of them at once.
*/
/* This is an integer, which is the number of arguments got into registers so
   far, and if init_cumulative_args was found to generate a call to a
   library function.  The offset starts at 0.  */
#define INIT_CUMULATIVE_ARGS(CUM,FNTYPE,LIBNAME,unused)        \
 ((CUM).regs = 0, (CUM).lib = ((LIBNAME) != 0))

/* Add another (unused) parameter to the macro above and remove this
   macro and declaration, since there *is* a xstrdup() in post-2.7.2(.2) 
#define xstrdup strdup
extern char *strdup();
*/

/*
 `INIT_CUMULATIVE_INCOMING_ARGS (CUM, FNTYPE, LIBNAME)'
      Like `INIT_CUMULATIVE_ARGS' but overrides it for the purposes of
      finding the arguments for the function being compiled.  If this
      macro is undefined, `INIT_CUMULATIVE_ARGS' is used instead.

      The value passed for LIBNAME is always 0, since library routines
      with special calling conventions are never compiled with GNU CC.
      The argument LIBNAME exists for symmetry with
      `INIT_CUMULATIVE_ARGS'.
*/
/* Not defined */


/*
 `FUNCTION_ARG_ADVANCE (CUM, MODE, TYPE, NAMED)'
      A C statement (sans semicolon) to update the summarizer variable
      CUM to advance past an argument in the argument list.  The values
      MODE, TYPE and NAMED describe that argument.  Once this is done,
      the variable CUM is suitable for analyzing the *following*
      argument with `FUNCTION_ARG', etc.

      This macro need not do anything if the argument in question was
      passed on the stack.  The compiler knows how to track the amount
      of stack space used for arguments without any special help.
*/
#define FUNCTION_ARG_ADVANCE(CUM, MODE, TYPE, NAMED)    \
  ((CUM).regs = ((MUST_PASS_IN_STACK(MODE,TYPE)) \
          || (FUNCTION_ARG_SIZE(MODE,TYPE) > 4 && !TARGET_LIBFUNC && !(CUM).lib))\
   ? (MAX_ARGS_IN_REGS)+1 : (CUM).regs + (3+(FUNCTION_ARG_SIZE(MODE,TYPE)))/4)


/*
 `FUNCTION_ARG_PADDING (MODE, TYPE)'
      If defined, a C expression which determines whether, and in which
      direction, to pad out an argument with extra space.  The value
      should be of type `enum direction': either `upward' to pad above
      the argument, `downward' to pad below, or `none' to inhibit
      padding.

      The *amount* of padding is always just enough to reach the next
      multiple of `FUNCTION_ARG_BOUNDARY'; this macro does not control
      it.

      This macro has a default definition which is right for most
      systems.  For little-endian machines, the default is to pad
      upward.  For big-endian machines, the default is to pad downward
      for an argument of constant size shorter than an `int', and upward
      otherwise.
*/
/* Not defined */


/*
 `FUNCTION_ARG_BOUNDARY (MODE, TYPE)'
      If defined, a C expression that gives the alignment boundary, in
      bits, of an argument with the specified mode and type.  If it is
      not defined, `PARM_BOUNDARY' is used for all arguments.
*/
/* Not defined */


/*
 `FUNCTION_ARG_REGNO_P (REGNO)'
      A C expression that is nonzero if REGNO is the number of a hard
      register in which function arguments are sometimes passed.  This
      does *not* include implicit arguments such as the static chain and
      the structure-value address.  On many machines, no registers can be
      used for this purpose since all function arguments are pushed on
      the stack.
*/
#define FUNCTION_ARG_REGNO_P(REGNO) \
 ((REGNO) >= FIRST_ARG_REG && (REGNO) < FIRST_ARG_REG + (MAX_ARGS_IN_REGS))


/* Section: Stack and Calling::Scalar Return */

/*
 `TRADITIONAL_RETURN_FLOAT'
      Define this macro if `-traditional' should not cause functions
      declared to return `float' to convert the value to `double'.
*/
/* Not defined */


/*
 `FUNCTION_VALUE (VALTYPE, FUNC)'
      A C expression to create an RTX representing the place where a
      function returns a value of data type VALTYPE.  VALTYPE is a tree
      node representing a data type.  Write `TYPE_MODE (VALTYPE)' to get
      the machine mode used to represent that type.  On many machines,
      only the mode is relevant.  (Actually, on most machines, scalar
      values are returned in the same place regardless of mode).

      If `PROMOTE_FUNCTION_RETURN' is defined, you must apply the same
      promotion rules specified in `PROMOTE_MODE' if VALTYPE is a scalar
      type.

      If the precise function being called is known, FUNC is a tree node
      (`FUNCTION_DECL') for it; otherwise, FUNC is a null pointer.  This
      makes it possible to use a different value-returning convention
      for specific functions when all their calls are known.

      `FUNCTION_VALUE' is not used for return vales with aggregate data
      types, because these are returned in another way.  See
      `STRUCT_VALUE_REGNUM' and related macros, below.
*/
/* Let's assume all functions return in r[FIRST_ARG_REG] for the time being */
/*
 * #define FUNCTION_VALUE(VALTYPE, FUNC)  \
 *  gen_rtx (REG, TYPE_MODE (VALTYPE), FIRST_ARG_REG)
 */

/* --- jds31 --- 
 * we choose to return values in r0, on the CLR.
 */ 

#define RETURN_VALUE_REG 0

#define FUNCTION_VALUE(VALTYPE, FUNC) \
   gen_rtx (REG, TYPE_MODE (VALTYPE), RETURN_VALUE_REG)


/*
 `FUNCTION_OUTGOING_VALUE (VALTYPE, FUNC)'
      Define this macro if the target machine has "register windows" so
      that the register in which a function returns its value is not the
      same as the one in which the caller sees the value.

      For such machines, `FUNCTION_VALUE' computes the register in which
      the caller will see the value.  `FUNCTION_OUTGOING_VALUE' should be
      defined in a similar fashion to tell the function where to put the
      value.

      If `FUNCTION_OUTGOING_VALUE' is not defined, `FUNCTION_VALUE'
      serves both purposes.

      `FUNCTION_OUTGOING_VALUE' is not used for return vales with
      aggregate data types, because these are returned in another way.
      See `STRUCT_VALUE_REGNUM' and related macros, below.
*/
/* Not defined */


/*
 `LIBCALL_VALUE (MODE)'
      A C expression to create an RTX representing the place where a
      library function returns a value of mode MODE.  If the precise
      function being called is known, FUNC is a tree node
      (`FUNCTION_DECL') for it; otherwise, FUNC is a null pointer.  This
      makes it possible to use a different value-returning convention
      for specific functions when all their calls are known.

      Note that "library function" in this context means a compiler
      support routine, used to perform arithmetic, whose name is known
      specially by the compiler and was not mentioned in the C code being
      compiled.

      The definition of `LIBRARY_VALUE' need not be concerned aggregate
      data types, because none of the library functions returns such
      types.
*/
/* Let's assume all lib functions return in r[FIRST_ARG_REG]
   for the time being */
#define LIBCALL_VALUE(MODE)  gen_rtx (REG, MODE, FIRST_ARG_REG)


/*
 `FUNCTION_VALUE_REGNO_P (REGNO)'
      A C expression that is nonzero if REGNO is the number of a hard
      register in which the values of called function may come back.

      A register whose use for returning values is limited to serving as
      the second of a pair (for a value of type `double', say) need not
      be recognized by this macro.  So for most machines, this definition
      suffices:

           #define FUNCTION_VALUE_REGNO_P(N) ((N) == 0)

      If the machine has register windows, so that the caller and the
      called function use different registers for the return value, this
      macro should recognize only the caller's register numbers.
*/
#define FUNCTION_VALUE_REGNO_P(N) ((N) == FIRST_ARG_REG)


/*
 `APPLY_RESULT_SIZE'
      Define this macro if `untyped_call' and `untyped_return' need more
      space than is implied by `FUNCTION_VALUE_REGNO_P' for saving and
      restoring an arbitrary return value.
*/
/* Not defined */


/* Section: Stack and Calling::Aggregate Return */

/*
 `RETURN_IN_MEMORY (TYPE)'
      A C expression which can inhibit the returning of certain function
      values in registers, based on the type of value.  A nonzero value
      says to return the function value in memory, just as large
      structures are always returned.  Here TYPE will be a C expression
      of type `tree', representing the data type of the value.

      Note that values of mode `BLKmode' must be explicitly handled by
      this macro.  Also, the option `-fpcc-struct-return' takes effect
      regardless of this macro.  On most systems, it is possible to
      leave the macro undefined; this causes a default definition to be
      used, whose value is the constant 1 for `BLKmode' values, and 0
      otherwise.

      Do not use this macro to indicate that structures and unions
      should always be returned in memory.  You should instead use
      `DEFAULT_PCC_STRUCT_RETURN' to indicate this.
*/
#if 0
/* Dont foo around with this -- yet. */
/* Let's try this.  Cast int_size_in_bytes() to unsigned, so we will
   get a huge number for "structures" of variable size (-1). */
#define RETURN_IN_MEMORY(TYPE) \
  ((unsigned) int_size_in_bytes(TYPE) > MAX_ARGS_IN_REGS*UNITS_PER_WORD)
#endif


/*
 `DEFAULT_PCC_STRUCT_RETURN'
      Define this macro to be 1 if all structure and union return values
      must be in memory.  Since this results in slower code, this should
      be defined only if needed for compatibility with other compilers
      or with an ABI.  If you define this macro to be 0, then the
      conventions used for structure and union return values are decided
      by the `RETURN_IN_MEMORY' macro.

      If not defined, this defaults to the value 1.
*/
/* Not defined */


/*
 `STRUCT_VALUE_REGNUM'
      If the structure value address is passed in a register, then
      `STRUCT_VALUE_REGNUM' should be the number of that register.
*/
#define STRUCT_VALUE_REGNUM ((FIRST_ARG_REG) - 1)


/*
 `STRUCT_VALUE'
      If the structure value address is not passed in a register, define
      `STRUCT_VALUE' as an expression returning an RTX for the place
      where the address is passed.  If it returns 0, the address is
      passed as an "invisible" first argument.
*/
/* Not defined */


/*
 `STRUCT_VALUE_INCOMING_REGNUM'
      On some architectures the place where the structure value address
      is found by the called function is not the same place that the
      caller put it.  This can be due to register windows, or it could
      be because the function prologue moves it to a different place.

      If the incoming location of the structure value address is in a
      register, define this macro as the register number.
*/
/* Not defined */


/*
 `STRUCT_VALUE_INCOMING'
      If the incoming location is not a register, then you should define
      `STRUCT_VALUE_INCOMING' as an expression for an RTX for where the
      called function should find the value.  If it should find the
      value on the stack, define this to create a `mem' which refers to
      the frame pointer.  A definition of 0 means that the address is
      passed as an "invisible" first argument.
*/
/* Not defined */


/*
 `PCC_STATIC_STRUCT_RETURN'
      Define this macro if the usual system convention on the target
      machine for returning structures and unions is for the called
      function to return the address of a static variable containing the
      value.

      Do not define this if the usual system convention is for the
      caller to pass an address to the subroutine.

      This macro has effect in `-fpcc-struct-return' mode, but it does
      nothing when you use `-freg-struct-return' mode.
*/
/* Not defined */


/* Section: Stack and Calling::Caller Saves */
/* (no definitions) */

/* Section: Stack and Calling::Function entry */

/*
 `FUNCTION_PROLOGUE (FILE, SIZE)'
      A C compound statement that outputs the assembler code for entry
      to a function.  The prologue is responsible for setting up the
      stack frame, initializing the frame pointer register, saving
      registers that must be saved, and allocating SIZE additional bytes
      of storage for the local variables.  SIZE is an integer.  FILE is
      a stdio stream to which the assembler code should be output.

      The label for the beginning of the function need not be output by
      this macro.  That has already been done when the macro is run.

      To determine which registers to save, the macro can refer to the
      array `regs_ever_live': element R is nonzero if hard register R is
      used anywhere within the function.  This implies the function
      prologue should save register R, provided it is not one of the
      call-used registers.  (`FUNCTION_EPILOGUE' must likewise use
      `regs_ever_live'.)

      On machines that have "register windows", the function entry code
      does not save on the stack the registers that are in the windows,
      even if they are supposed to be preserved by function calls;
      instead it takes appropriate steps to "push" the register stack,
      if any non-call-used registers are used in the function.

      On machines where functions may or may not have frame-pointers, the
      function entry code must vary accordingly; it must set up the frame
      pointer if one is wanted, and not otherwise.  To determine whether
      a frame pointer is in wanted, the macro can refer to the variable
      `frame_pointer_needed'.  The variable's value will be 1 at run
      time in a function that needs a frame pointer.  *Note
      Elimination::.

      The function entry code is responsible for allocating any stack
      space required for the function.  This stack space consists of the
      regions listed below.  In most cases, these regions are allocated
      in the order listed, with the last listed region closest to the
      top of the stack (the lowest address if `STACK_GROWS_DOWNWARD' is
      defined, and the highest address if it is not defined).  You can
      use a different order for a machine if doing so is more convenient
      or required for compatibility reasons.  Except in cases where
      required by standard or by a debugger, there is no reason why the
      stack layout used by GCC need agree with that used by other
      compilers for a machine.

         * A region of `current_function_pretend_args_size' bytes of
           uninitialized space just underneath the first argument
           arriving on the stack.  (This may not be at the very start of
           the allocated stack region if the calling sequence has pushed
           anything else since pushing the stack arguments.  But
           usually, on such machines, nothing else has been pushed yet,
           because the function prologue itself does all the pushing.)
           This region is used on machines where an argument may be
           passed partly in registers and partly in memory, and, in some
           cases to support the features in `varargs.h' and `stdargs.h'.

         * An area of memory used to save certain registers used by the
           function.  The size of this area, which may also include
           space for such things as the return address and pointers to
           previous stack frames, is machine-specific and usually
           depends on which registers have been used in the function.
           Machines with register windows often do not require a save
           area.

         * A region of at least SIZE bytes, possibly rounded up to an
           allocation boundary, to contain the local variables of the
           function.  On some machines, this region and the save area
           may occur in the opposite order, with the save area closer to
           the top of the stack.

         * Optionally, when `ACCUMULATE_OUTGOING_ARGS' is defined, a
           region of `current_function_outgoing_args_size' bytes to be
           used for outgoing argument lists of the function.  *Note
           Stack Arguments::.

      Normally, it is necessary for the macros `FUNCTION_PROLOGUE' and
      `FUNCTION_EPILOGUE' to treat leaf functions specially.  The C
      variable `leaf_function' is nonzero for such a function.
*/
#define FUNCTION_PROLOGUE(FILE, SIZE) function_prologue(FILE, SIZE)

/* moved to protos.h extern void function_prologue(FILE *, int); */


/*
 `EXIT_IGNORE_STACK'
      Define this macro as a C expression that is nonzero if the return
      instruction or the function epilogue ignores the value of the stack
      pointer; in other words, if it is safe to delete an instruction to
      adjust the stack pointer before a return from the function.

      Note that this macro's value is relevant only for functions for
      which frame pointers are maintained.  It is never safe to delete a
      final stack adjustment in a function that has no frame pointer,
      and the compiler knows this regardless of `EXIT_IGNORE_STACK'.
*/
/* Not defined */


/*
 `FUNCTION_EPILOGUE (FILE, SIZE)'
      A C compound statement that outputs the assembler code for exit
      from a function.  The epilogue is responsible for restoring the
      saved registers and stack pointer to their values when the
      function was called, and returning control to the caller.  This
      macro takes the same arguments as the macro `FUNCTION_PROLOGUE',
      and the registers to restore are determined from `regs_ever_live'
      and `CALL_USED_REGISTERS' in the same way.

      On some machines, there is a single instruction that does all the
      work of returning from the function.  On these machines, give that
      instruction the name `return' and do not define the macro
      `FUNCTION_EPILOGUE' at all.

      Do not define a pattern named `return' if you want the
      `FUNCTION_EPILOGUE' to be used.  If you want the target switches
      to control whether return instructions or epilogues are used,
      define a `return' pattern with a validity condition that tests the
      target switches appropriately.  If the `return' pattern's validity
      condition is false, epilogues will be used.

      On machines where functions may or may not have frame-pointers, the
      function exit code must vary accordingly.  Sometimes the code for
      these two cases is completely different.  To determine whether a
      frame pointer is wanted, the macro can refer to the variable
      `frame_pointer_needed'.  The variable's value will be 1 when
      compiling a function that needs a frame pointer.

      Normally, `FUNCTION_PROLOGUE' and `FUNCTION_EPILOGUE' must treat
      leaf functions specially.  The C variable `leaf_function' is
      nonzero for such a function.  *Note Leaf Functions::.

      On some machines, some functions pop their arguments on exit while
      others leave that for the caller to do.  For example, the 68020
      when given `-mrtd' pops arguments in functions that take a fixed
      number of arguments.

      Your definition of the macro `RETURN_POPS_ARGS' decides which
      functions pop their own arguments.  `FUNCTION_EPILOGUE' needs to
      know what was decided.  The variable that is called
      `current_function_pops_args' is the number of bytes of its
      arguments that a function should pop.  *Note Scalar Return::.
*/
#define FUNCTION_EPILOGUE(FILE, SIZE) function_epilogue(FILE,SIZE)

/* moved to protos.h  extern void function_epilogue(FILE *, int); */


/*
 `DELAY_SLOTS_FOR_EPILOGUE'
      Define this macro if the function epilogue contains delay slots to
      which instructions from the rest of the function can be "moved".
      The definition should be a C expression whose value is an integer
      representing the number of delay slots there.
*/
/* If "ret" insns in the epilogue, we need to fill the
   delay slot. 
#define DELAY_SLOTS_FOR_EPILOGUE delay_slots_for_epilogue()

extern int delay_slots_for_epilogue();
*/


/*
 `ELIGIBLE_FOR_EPILOGUE_DELAY (INSN, N)'
      A C expression that returns 1 if INSN can be placed in delay slot
      number N of the epilogue.

      The argument N is an integer which identifies the delay slot now
      being considered (since different slots may have different rules of
      eligibility).  It is never negative and is always less than the
      number of epilogue delay slots (what `DELAY_SLOTS_FOR_EPILOGUE'
      returns).  If you reject a particular insn for a given delay slot,
      in principle, it may be reconsidered for a subsequent delay slot.
      Also, other insns may (at least in principle) be considered for
      the so far unfilled delay slot.

      The insns accepted to fill the epilogue delay slots are put in an
      RTL list made with `insn_list' objects, stored in the variable
      `current_function_epilogue_delay_list'.  The insn for the first
      delay slot comes first in the list.  Your definition of the macro
      `FUNCTION_EPILOGUE' should fill the delay slots by outputting the
      insns in this list, usually by calling `final_scan_insn'.

      You need not define this macro if you did not define
      `DELAY_SLOTS_FOR_EPILOGUE'.

#define ELIGIBLE_FOR_EPILOGUE_DELAY(INSN, N) \
  eligible_for_epilogue_delay(INSN)

extern int eligible_for_epilogue_delay();
*/

/* Section: Stack and Calling::Profiling */

/*
 `FUNCTION_PROFILER (FILE, LABELNO)'
      A C statement or compound statement to output to FILE some
      assembler code to call the profiling subroutine `mcount'.  Before
      calling, the assembler code must load the address of a counter
      variable into a register where `mcount' expects to find the
      address.  The name of this variable is `LP' followed by the number
      LABELNO, so you would generate the name using `LP%d' in a
      `fprintf'.

      The details of how the address should be passed to `mcount' are
      determined by your operating system environment, not by GNU CC.  To
      figure them out, compile a small program for profiling using the
      system's installed C compiler and look at the assembler code that
      results.
*/
#define FUNCTION_PROFILER(FILE, LABELNO)  \
  /* fprintf (FILE, "This should have been mcount(%d)\n", (LABELNO)); */;


/*
 `PROFILE_BEFORE_PROLOGUE'
      Define this macro if the code for function profiling should come
      before the function prologue.  Normally, the profiling code comes
      after.
*/
/* Not defined */


/*
 `FUNCTION_BLOCK_PROFILER (FILE, LABELNO)'
      A C statement or compound statement to output to FILE some
      assembler code to initialize basic-block profiling for the current
      object module.  This code should call the subroutine
      `__bb_init_func' once per object module, passing it as its sole
      argument the address of a block allocated in the object module.

      The name of the block is a local symbol made with this statement:

           ASM_GENERATE_INTERNAL_LABEL (BUFFER, "LPBX", 0);

      Of course, since you are writing the definition of
      `ASM_GENERATE_INTERNAL_LABEL' as well as that of this macro, you
      can take a short cut in the definition of this macro and use the
      name that you know will result.

      The first word of this block is a flag which will be nonzero if the
      object module has already been initialized.  So test this word
      first, and do not call `__bb_init_func' if the flag is nonzero.
*/
/* No profiling for the time being.  */
#define FUNCTION_BLOCK_PROFILER(FILE, LABELNO)  \
  /*   fprintf (FILE, "\tFunction block profiler %d:\n",  \
           LABELNO); \
 */;


/*
 `BLOCK_PROFILER (FILE, BLOCKNO)'
      A C statement or compound statement to increment the count
      associated with the basic block number BLOCKNO.  Basic blocks are
      numbered separately from zero within each compilation.  The count
      associated with block number BLOCKNO is at index BLOCKNO in a
      vector of words; the name of this array is a local symbol made
      with this statement:

           ASM_GENERATE_INTERNAL_LABEL (BUFFER, "LPBX", 2);

      Of course, since you are writing the definition of
      `ASM_GENERATE_INTERNAL_LABEL' as well as that of this macro, you
      can take a short cut in the definition of this macro and use the
      name that you know will result.
*/
/* No profiling for the time being.  */
#define BLOCK_PROFILER(FILE, BLOCKNO)   \
  /*   fprintf (FILE, "\tBlock profiler: %d\n", \
                BLOCKNO) */;


/*
 `BLOCK_PROFILER_CODE'
      A C function or functions which are needed in the library to
      support block profiling.
*/
/* No profiling for the time being.  */


/* Section: Varargs */

/*
 `EXPAND_BUILTIN_SAVEREGS (ARGS)'
      If defined, is a C expression that produces the machine-specific
      code for a call to `__builtin_saveregs'.  This code will be moved
      to the very beginning of the function, before any parameter access
      are made.  The return value of this function should be an RTX that
      contains the value to use as the return of `__builtin_saveregs'.

      The argument ARGS is a `tree_list' containing the arguments that
      were passed to `__builtin_saveregs'.

      If this macro is not defined, the compiler will output an ordinary
      call to the library function `__builtin_saveregs'.
*/
/* Not defined */


/*
 `SETUP_INCOMING_VARARGS (ARGS_SO_FAR, MODE, TYPE,'
      PRETEND_ARGS_SIZE, SECOND_TIME) This macro offers an alternative
      to using `__builtin_saveregs' and defining the macro
      `EXPAND_BUILTIN_SAVEREGS'.  Use it to store the anonymous register
      arguments into the stack so that all the arguments appear to have
      been passed consecutively on the stack.  Once this is done, you
      can use the standard implementation of varargs that works for
      machines that pass all their arguments on the stack.

      The argument ARGS_SO_FAR is the `CUMULATIVE_ARGS' data structure,
      containing the values that obtain after processing of the named
      arguments.  The arguments MODE and TYPE describe the last named
      argument--its machine mode and its data type as a tree node.

      The macro implementation should do two things: first, push onto the
      stack all the argument registers *not* used for the named
      arguments, and second, store the size of the data thus pushed into
      the `int'-valued variable whose name is supplied as the argument
      PRETEND_ARGS_SIZE.  The value that you store here will serve as
      additional offset for setting up the stack frame.

      Because you must generate code to push the anonymous arguments at
      compile time without knowing their data types,
      `SETUP_INCOMING_VARARGS' is only useful on machines that have just
      a single category of argument register and use it uniformly for
      all data types.

      If the argument SECOND_TIME is nonzero, it means that the
      arguments of the function are being analyzed for the second time.
      This happens for an inline function, which is not actually
      compiled until the end of the source file.  The macro
      `SETUP_INCOMING_VARARGS' should not generate any instructions in
      this case.
*/
/* We save the register number of the first anonymous argument in
   first_vararg_reg, and take care of this in the function prologue.
   This behaviour is used by at least one more port (the ARM?), but
   may be unsafe when compiling nested functions.  (With varargs? Hairy.)
    Note that nested-functions is a Gnu C extension.
 */

/* FIXME - jds31 - 6/12/01 - Do we need this?? */

   /* #define SETUP_INCOMING_VARARGS(ARGS_SO_FAR, MODE, TYPE, PRETEND_ARGS_SIZE, SECOND_TIME)\
  {                                                                           \
    if ((ARGS_SO_FAR).regs < (MAX_ARGS_IN_REGS))                              \
    {                                                                         \
      extern int first_vararg_reg;                                            \
      first_vararg_reg = (FIRST_ARG_REG)+(ARGS_SO_FAR).regs;                  \
      (PRETEND_ARGS_SIZE) = ((MAX_ARGS_IN_REGS) - (ARGS_SO_FAR).regs)*4;      \
    }                                                                         \
    if (TARGET_PDEBUG)                                                        \
    {                                                                         \
      fprintf(stderr,"\n VA:: %s: %d args before, anon @ #%d, %dtime\n",      \
              current_function_varargs ? "OLD" : "ANSI",                      \
              (ARGS_SO_FAR).regs, PRETEND_ARGS_SIZE,SECOND_TIME);             \
    }                                                                         \
  }
*/

/*
 `STRICT_ARGUMENT_NAMING'
      Define this macro if the location where a function argument is
      passed depends on whether or not it is a named argument.

      This macro controls how the NAMED argument to `FUNCTION_ARG' is
      set for varargs and stdarg functions.  With this macro defined,
      the NAMED argument is always true for named arguments, and false
      for unnamed arguments.  If this is not defined, but
      `SETUP_INCOMING_VARARGS' is defined, then all arguments are
      treated as named.  Otherwise, all named arguments except the last
      are treated as named.
*/
/* Not defined */


/* Section: Trampolines */

/*
 `TRAMPOLINE_TEMPLATE (FILE)'
      A C statement to output, on the stream FILE, assembler code for a
      block of data that contains the constant parts of a trampoline.
      This code should not include a label--the label is taken care of
      automatically.
*/
/* NOTE THAT TRAMPOLINES ARE NOT TESTED, SINCE WE DONT USE NESTED FUNCTIONS. */
#define TRAMPOLINE_TEMPLATE(FILE)                               \
  fprintf(FILE, "\tmove.d 0,r%d\n", STATIC_CHAIN_REGNUM);       \
  fprintf(FILE, "\tjump 0\n");


/*
 `TRAMPOLINE_SECTION'
      The name of a subroutine to switch to the section in which the
      trampoline template is to be placed (*note Sections::.).  The
      default is a value of `readonly_data_section', which places the
      trampoline in the section containing read-only data.
*/
/* Not defined */


/*
 `TRAMPOLINE_SIZE'
      A C expression for the size in bytes of the trampoline, as an
      integer.
*/
#define TRAMPOLINE_SIZE 12


/*
 `TRAMPOLINE_ALIGNMENT'
      Alignment required for trampolines, in bits.

      If you don't define this macro, the value of `BIGGEST_ALIGNMENT'
      is used for aligning trampolines.
*/
/* Jvm wants instructions on word-(16)-boundary.
   Note that due to a bug (reported) in 2.7.2 and earlier, this is
   actually treated as alignment in _bytes_, not _bits_.  (Obviously
   this is not fatal, only a slight waste of stack space). */
#define TRAMPOLINE_ALIGNMENT 16


/*
 `INITIALIZE_TRAMPOLINE (ADDR, FNADDR, STATIC_CHAIN)'
      A C statement to initialize the variable parts of a trampoline.
      aDDR is an RTX for the address of the trampoline; FNADDR is an RTX
      for the address of the nested function; STATIC_CHAIN is an RTX for
      the static chain value that should be passed to the function when
      it is called.
*/
#define INITIALIZE_TRAMPOLINE(TRAMP, FNADDR, CXT)                           \
{                                                                           \
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant (TRAMP, 2)), CXT);    \
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant (TRAMP, 8)), FNADDR); \
}


/*
 `ALLOCATE_TRAMPOLINE (FP)'
      A C expression to allocate run-time space for a trampoline.  The
      expression value should be an RTX representing a memory reference
      to the space for the trampoline.

      If this macro is not defined, by default the trampoline is
      allocated as a stack slot.  This default is right for most
      machines.  The exceptions are machines where it is impossible to
      execute instructions in the stack area.  On such machines, you may
      have to implement a separate stack, using this macro in
      conjunction with `FUNCTION_PROLOGUE' and `FUNCTION_EPILOGUE'.

      FP points to a data structure, a `struct function', which
      describes the compilation status of the immediate containing
      function of the function which the trampoline is for.  Normally
      (when `ALLOCATE_TRAMPOLINE' is not defined), the stack slot for the
      trampoline is in the stack frame of this containing function.
      Other allocation strategies probably must do something analogous
      with this information.
*/
/* Not defined */


/*
 `INSN_CACHE_SIZE'
      The total size in bytes of the cache.
*/
/* Not defined */


/*
 `INSN_CACHE_LINE_WIDTH'
      The length in bytes of each cache line.  The cache is divided into
      cache lines which are disjoint slots, each holding a contiguous
      chunk of data fetched from memory.  Each time data is brought into
      the cache, an entire line is read at once.  The data loaded into a
      cache line is always aligned on a boundary equal to the line size.
*/
/* Not defined */


/*
 `INSN_CACHE_DEPTH'
      The number of alternative cache lines that can hold any particular
      memory location.
*/
/* Not defined */


/*
 `CLEAR_INSN_CACHE (BEG, END)'
      If defined, expands to a C expression clearing the *instruction
      cache* in the specified interval.  If it is not defined, and the
      macro INSN_CACHE_SIZE is defined, some generic code is generated
      to clear the cache.  The definition of this macro would typically
      be a series of `asm' statements.  Both BEG and END are both pointer
      expressions.
*/
/* Not defined */


/*
 `TRANSFER_FROM_TRAMPOLINE'
      Define this macro if trampolines need a special subroutine to do
      their work.  The macro should expand to a series of `asm'
      statements which will be compiled with GNU CC.  They go in a
      library function named `__transfer_from_trampoline'.

      If you need to avoid executing the ordinary prologue code of a
      compiled C function when you jump to the subroutine, you can do so
      by placing a special label of your own in the assembler code.  Use
      one `asm' statement to generate an assembler label, and another to
      make the label global.  Then trampolines can use that label to
      jump directly to your special assembler code.
*/
/* Not defined */


/* Section: Library Calls */

/*
 `MULSI3_LIBCALL'
      A C string constant giving the name of the function to call for
      multiplication of one signed full-word by another.  If you do not
      define this macro, the default name is used, which is `__mulsi3',
      a function defined in `libgcc.a'.
*/
/* We have no real divsi3 udivsi3 modsi3 umodsi3 mulsi3 so
   we must have them in some library.
    Gcc makes __xx names for them, with "xx" one of the above, and
   defines them in libgcc1.  This causes a recursive definition if we
   do not have other names for them, and define them elsewhere.
    So lets do that.
*/
#define MULSI3_LIBCALL "__Mul"


/*
 `DIVSI3_LIBCALL'
      A C string constant giving the name of the function to call for
      division of one signed full-word by another.  If you do not define
      this macro, the default name is used, which is `__divsi3', a
      function defined in `libgcc.a'.
*/
#define DIVSI3_LIBCALL "__Div"


/*
 `UDIVSI3_LIBCALL'
      A C string constant giving the name of the function to call for
      division of one unsigned full-word by another.  If you do not
      define this macro, the default name is used, which is `__udivsi3',
      a function defined in `libgcc.a'.
*/
#define UDIVSI3_LIBCALL "__Udiv"


/*
 `MODSI3_LIBCALL'
      A C string constant giving the name of the function to call for the
      remainder in division of one signed full-word by another.  If you
      do not define this macro, the default name is used, which is
      `__modsi3', a function defined in `libgcc.a'.
*/
#define MODSI3_LIBCALL "__Mod"


/*
 `UMODSI3_LIBCALL'
      A C string constant giving the name of the function to call for the
      remainder in division of one unsigned full-word by another.  If
      you do not define this macro, the default name is used, which is
      `__umodsi3', a function defined in `libgcc.a'.
*/
#define UMODSI3_LIBCALL "__Umod"


/*
 `MULDI3_LIBCALL'
      A C string constant giving the name of the function to call for
      multiplication of one signed double-word by another.  If you do not
      define this macro, the default name is used, which is `__muldi3',
      a function defined in `libgcc.a'.
*/
/* Not defined */


/*
 `DIVDI3_LIBCALL'
      A C string constant giving the name of the function to call for
      division of one signed double-word by another.  If you do not
      define this macro, the default name is used, which is `__divdi3', a
      function defined in `libgcc.a'.
*/
/* Not defined */


/*
 `UDIVDI3_LIBCALL'
      A C string constant giving the name of the function to call for
      division of one unsigned full-word by another.  If you do not
      define this macro, the default name is used, which is `__udivdi3',
      a function defined in `libgcc.a'.
*/
/* Not defined */


/*
 `MODDI3_LIBCALL'
      A C string constant giving the name of the function to call for the
      remainder in division of one signed double-word by another.  If
      you do not define this macro, the default name is used, which is
      `__moddi3', a function defined in `libgcc.a'.
*/
/* Not defined */


/*
 `UMODDI3_LIBCALL'
      A C string constant giving the name of the function to call for the
      remainder in division of one unsigned full-word by another.  If
      you do not define this macro, the default name is used, which is
      `__umoddi3', a function defined in `libgcc.a'.
*/
/* Not defined */


/*
 `INIT_TARGET_OPTABS'
      Define this macro as a C statement that declares additional library
      routines renames existing ones. `init_optabs' calls this macro
      after initializing all the normal library routines.
*/
/* Not defined */


/*
 `TARGET_EDOM'
      The value of `EDOM' on the target machine, as a C integer constant
      expression.  If you don't define this macro, GNU CC does not
      attempt to deposit the value of `EDOM' into `errno' directly.
      Look in `/usr/include/errno.h' to find the value of `EDOM' on your
      system.

      If you do not define `TARGET_EDOM', then compiled code reports
      domain errors by calling the library function and letting it
      report the error.  If mathematical functions on your system use
      `matherr' when there is an error, then you should leave
      `TARGET_EDOM' undefined so that `matherr' is used normally.
*/
#define TARGET_EDOM 33          /* Dont go change the include files now! */


/*
 `GEN_ERRNO_RTX'
      Define this macro as a C expression to create an rtl expression
      that refers to the global "variable" `errno'.  (On certain systems,
      `errno' may not actually be a variable.)  If you don't define this
      macro, a reasonable default is used.
*/
/* Not defined */


/*
 `TARGET_MEM_FUNCTIONS'
      Define this macro if GNU CC should generate calls to the System V
      (and ANSI C) library functions `memcpy' and `memset' rather than
      the BSD functions `bcopy' and `bzero'.
*/
#define TARGET_MEM_FUNCTIONS


/*
 `LIBGCC_NEEDS_DOUBLE'
      Define this macro if only `float' arguments cannot be passed to
      library routines (so they must be converted to `double').  This
      macro affects both how library calls are generated and how the
      library routines in `libgcc1.c' accept their arguments.  It is
      useful on machines where floating and fixed point arguments are
      passed differently, such as the i860.
*/
/* Not defined */


/*
 `FLOAT_ARG_TYPE'
      Define this macro to override the type used by the library
      routines to pick up arguments of type `float'.  (By default, they
      use a union of `float' and `int'.)

      The obvious choice would be `float'--but that won't work with
      traditional C compilers that expect all arguments declared as
      `float' to arrive as `double'.  To avoid this conversion, the
      library routines ask for the value as some other type and then
      treat it as a `float'.

      On some systems, no other type will work for this.  For these
      systems, you must use `LIBGCC_NEEDS_DOUBLE' instead, to force
      conversion of the values `double' before they are passed.
*/
/* Not defined */


/*
 `FLOATIFY (PASSED-VALUE)'
      Define this macro to override the way library routines redesignate
      a `float' argument as a `float' instead of the type it was passed
      as.  The default is an expression which takes the `float' field of
      the union.
*/
/* Not defined */


/*
 `FLOAT_VALUE_TYPE'
      Define this macro to override the type used by the library
      routines to return values that ought to have type `float'.  (By
      default, they use `int'.)

      The obvious choice would be `float'--but that won't work with
      traditional C compilers gratuitously convert values declared as
      `float' into `double'.
*/
/* Only used in libgcc1.c which we do not use, but we let it in here
   to keep a complete description.  */
#define FLOAT_VALUE_TYPE float


/*
 `INTIFY (FLOAT-VALUE)'
      Define this macro to override the way the value of a
      `float'-returning library routine should be packaged in order to
      return it.  These functions are actually declared to return type
      `FLOAT_VALUE_TYPE' (normally `int').

      These values can't be returned as type `float' because traditional
      C compilers would gratuitously convert the value to a `double'.

      A local variable named `intify' is always available when the macro
      `INTIFY' is used.  It is a union of a `float' field named `f' and
      a field named `i' whose type is `FLOAT_VALUE_TYPE' or `int'.

      If you don't define this macro, the default definition works by
      copying the value through that union.
*/
/* See comment for FLOAT_VALUE_TYPE */
#define INTIFY(x) (x)


/*
 `nongcc_SI_type'
      Define this macro as the name of the data type corresponding to
      `SImode' in the system's own C compiler.

      You need not define this macro if that type is `long int', as it
      usually is.
*/
/* Not defined */


/*
 `nongcc_word_type'
      Define this macro as the name of the data type corresponding to the
      word_mode in the system's own C compiler.

      You need not define this macro if that type is `long int', as it
      usually is.
*/
/* Not defined */


/*
 `perform_...'
      Define these macros to supply explicit C statements to carry out
      various arithmetic operations on types `float' and `double' in the
      library routines in `libgcc1.c'.  See that file for a full list of
      these macros and their arguments.

      On most machines, you don't need to define any of these macros,
      because the C compiler that comes with the system takes care of
      doing them.
*/
/* Not defined */


/*
 `NEXT_OBJC_RUNTIME'
      Define this macro to generate code for Objective C message sending
      using the calling convention of the NeXT system.  This calling
      convention involves passing the object, the selector and the
      method arguments all at once to the method-lookup library function.

      The default calling convention passes just the object and the
      selector to the lookup function, which returns a pointer to the
      method.
*/
/* Not defined */


/* Section: Addressing Modes */

/*
 `HAVE_POST_INCREMENT'
      Define this macro if the machine supports post-increment
      addressing.

#define HAVE_POST_INCREMENT
*/

/*
 `HAVE_PRE_INCREMENT'
 `HAVE_POST_DECREMENT'
 `HAVE_PRE_DECREMENT'
      Similar for other kinds of addressing.
*/
/* Not defined */


/*
 `CONSTANT_ADDRESS_P (X)'
      A C expression that is 1 if the RTX X is a constant which is a
      valid address.  On most machines, this can be defined as
      `CONSTANT_P (X)', but a few machines are more restrictive in which
      constant addresses are supported.

      `CONSTANT_P' accepts integer-values expressions whose values are
      not explicitly known, such as `symbol_ref', `label_ref', and
      `high' expressions and `const' arithmetic expressions, in addition
      to `const_int' and `const_double' expressions.
*/
#define CONSTANT_ADDRESS_P(X) CONSTANT_P (X)
/* Not defined */


/*
 `MAX_REGS_PER_ADDRESS'
      A number, the maximum number of registers that can appear in a
      valid memory address.  Note that it is up to you to specify a
      value equal to the maximum number that `GO_IF_LEGITIMATE_ADDRESS'
      would ever accept.
*/
#define MAX_REGS_PER_ADDRESS 2


/*
 `GO_IF_LEGITIMATE_ADDRESS (MODE, X, LABEL)'
      A C compound statement with a conditional `goto LABEL;' executed
      if X (an RTX) is a legitimate memory address on the target machine
      for a memory operand of mode MODE.

      It usually pays to define several simpler macros to serve as
      subroutines for this one.  Otherwise it may be too complicated to
      understand.

      This macro must exist in two variants: a strict variant and a
      non-strict one.  The strict variant is used in the reload pass.  It
      must be defined so that any pseudo-register that has not been
      allocated a hard register is considered a memory reference.  In
      contexts where some kind of register is required, a pseudo-register
      with no hard register must be rejected.

      The non-strict variant is used in other passes.  It must be
      defined to accept all pseudo-registers in every context where some
      kind of register is required.

      Compiler source files that want to use the strict variant of this
      macro define the macro `REG_OK_STRICT'.  You should use an `#ifdef
      REG_OK_STRICT' conditional to define the strict variant in that
      case and the non-strict variant otherwise.

      Subroutines to check for acceptable registers for various purposes
      (one for base registers, one for index registers, and so on) are
      typically among the subroutines used to define
      `GO_IF_LEGITIMATE_ADDRESS'.  Then only these subroutine macros
      need have two variants; the higher levels of macros may be the
      same whether strict or not.

      Normally, constant addresses which are the sum of a `symbol_ref'
      and an integer are stored inside a `const' RTX to mark them as
      constant.  Therefore, there is no need to recognize such sums
      specifically as legitimate addresses.  Normally you would simply
      recognize any `const' as legitimate.

      Usually `PRINT_OPERAND_ADDRESS' is not prepared to handle constant
      sums that are not marked with  `const'.  It assumes that a naked
      `plus' indicates indexing.  If so, then you *must* reject such
      naked constant sums as illegitimate addresses, so that none of
      them will be given to `PRINT_OPERAND_ADDRESS'.

      On some machines, whether a symbolic address is legitimate depends
      on the section that the address refers to.  On these machines,
      define the macro `ENCODE_SECTION_INFO' to store the information
      into the `symbol_ref', and then check for it here.  When you see a
      `const', you will have to look inside it to find the `symbol_ref'
      in order to determine the section.  *Note Assembler Format::.

      The best way to modify the name string is by adding text to the
      beginning, with suitable punctuation to prevent any ambiguity.
      Allocate the new name in `saveable_obstack'.  You will have to
      modify `ASM_OUTPUT_LABELREF' to remove and decode the added text
      and output the name accordingly, and define `STRIP_NAME_ENCODING'
      to access the original name string.

      You can check the information stored here into the `symbol_ref' in
      the definitions of the macros `GO_IF_LEGITIMATE_ADDRESS' and
      `PRINT_OPERAND_ADDRESS'.
*/
/*
   The other macros defined here are used only in GO_IF_LEGITIMATE_ADDRESS,
   except for CONSTANT_ADDRESS_P which is actually machine-independent.

   Note that you HAVE TO reject illegal addressing modes for mode
   MODE, even if it is legal for normal addressing modes.  You cannot
   rely on the constraints to do this work.  They can only be used to
   doublecheck your intentions.  One example is that you HAVE TO reject
   (mem:DI (plus:SI (reg:SI x) (reg:SI y))) because for some reason
   this cannot be reloaded.  (Which of course you can argue that gcc
   should have done.)
*/
#define GO_PRINTF(foo) if (TARGET_GO_DEBUG) printf(foo) /* was debug_printf*/
#define GO_RTX(foo) if (TARGET_GO_DEBUG) debug_rtx(foo)

#define CONSTANT_INDEX_P(X) CONSTANT_P(X)

/* True if X is a valid base register */
#define BASE_P(X)                                                             \
  (REG_P(X) && REG_OK_FOR_BASE_P(X))

/* True if X is a valid base register with or without autoincrement */
#define BASE_OR_AUTOINCR_P(X)                                                 \
  (BASE_P(X) || (GET_CODE(X) == POST_INC && BASE_P(XEXP(X, 0))))

/* True if X is a valid (register) index for BDAP, i.e. (Rs) or (Rs+) */
/* Now 8 and 16 bit sign extend + 32bit! HP 930428. */
#define BDAP_INDEX_P(X)                                                       \
  (TARGET_BDAP                                                                \
   && ((GET_CODE(X) == MEM && GET_MODE(X) == SImode                           \
        && BASE_OR_AUTOINCR_P(XEXP(X,0)))                                     \
       || (GET_CODE(X) == SIGN_EXTEND                                         \
           && GET_CODE(XEXP(X, 0)) == MEM                                     \
           && (GET_MODE(XEXP(X, 0)) == HImode                                 \
               || GET_MODE(XEXP(X, 0)) == QImode)                             \
           && BASE_OR_AUTOINCR_P(XEXP(XEXP(X,0), 0)))))

/* True if X is a valid (register) index for BIAP, i.e. Rd.m */
#define BIAP_INDEX_P(X)                                                       \
  ((BASE_P(X) && REG_OK_FOR_INDEX_P(X)) ||                                    \
   (GET_CODE(X) == MULT &&                                                    \
    BASE_P(XEXP(X, 0)) && REG_OK_FOR_INDEX_P(XEXP(X, 0)) &&                   \
    GET_CODE(XEXP(X, 1)) == CONST_INT &&                                      \
    (INTVAL(XEXP(X, 1)) == 2 || INTVAL(XEXP(X, 1)) == 4)))

/* True if X is an address that doesn't need a prefix i.e.
   (reg), (reg+). */
#define SIMPLE_ADDRESS_P(X)                                                   \
   (BASE_P(X) || /* earlier versions used REG_P. Not strict enough! */        \
   (GET_CODE(X) == POST_INC &&                                                \
    BASE_P(XEXP(X, 0))))

#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, ADDR)                               \
{                                                                             \
  register rtx foo, foo1, foo2;                                               \
  GO_PRINTF("GO_IF_LEGIT_ADDR:\n");                                           \
  GO_RTX(X);                                                                  \
  if (SIMPLE_ADDRESS_P(X))                                                    \
    goto ADDR;                                                                \
  if (CONSTANT_P(X))                                                          \
    goto ADDR;                                                                \
  if (GET_CODE(X) == PLUS) /* indexed */                                      \
  {                                                                           \
    GO_PRINTF("Indexed...");                                                  \
    foo1 = XEXP(X, 0);                                                        \
    foo2 = XEXP(X, 1);                                                        \
    if ((BASE_P(foo1) && CONSTANT_INDEX_P(foo2)) || /* BDAP o, Rd */          \
        (BASE_P(foo2) && CONSTANT_INDEX_P(foo1)) ||                           \
        (GET_MODE_SIZE(MODE) <= UNITS_PER_WORD                                \
         && ((BASE_P(foo1) && BDAP_INDEX_P(foo2)) /* BDAP (Rs[+]), Rd */      \
             || (BASE_P(foo2) && BDAP_INDEX_P(foo1))                          \
             || (BASE_P(foo1) && BIAP_INDEX_P(foo2))  /* BIAP.m Rs, Rd */     \
             || (BASE_P(foo2) && BIAP_INDEX_P(foo1)))))                       \
    goto ADDR;                                                                \
  }                                                                           \
  else if (GET_CODE(X) == MEM)   /* DIP (Rs) */                               \
  { /* Reject [[reg+]] and [[reg]] for long long */                           \
    if (GET_MODE_SIZE(MODE) <= UNITS_PER_WORD                                 \
        && (BASE_P(XEXP(X,0))   /* [[reg+]] not implemented in jvm 1.0. */  \
            || TARGET_DIPINC && BASE_OR_AUTOINCR_P(XEXP(X, 0))))              \
      goto ADDR;                                                              \
  }                                                                           \
  else                                                                        \
    GO_PRINTF("Bad address\n"); \
}


/*
 `REG_OK_FOR_BASE_P (X)'
      A C expression that is nonzero if X (assumed to be a `reg' RTX) is
      valid for use as a base register.  For hard registers, it should
      always accept those which the hardware permits and reject the
      others.  Whether the macro accepts or rejects pseudo registers
      must be controlled by `REG_OK_STRICT' as described above.  This
      usually requires two variant definitions, of which `REG_OK_STRICT'
      controls the one actually used.
*/
#ifndef REG_OK_STRICT

/* Nonzero if X is a hard reg that can be used as a base reg
   or if it is a pseudo reg.  */
# define REG_OK_FOR_BASE_P(X) \
  (REGNO(X) <= LAST_GENERAL_REGISTER || REGNO(X) >= FIRST_PSEUDO_REGISTER)

#else

/* Nonzero if X is a hard reg that can be used as a base reg.  */
# define REG_OK_FOR_BASE_P(X) REGNO_OK_FOR_BASE_P (REGNO (X))

#endif


/*
 `REG_OK_FOR_INDEX_P (X)'
      A C expression that is nonzero if X (assumed to be a `reg' RTX) is
      valid for use as an index register.

      The difference between an index register and a base register is
      that the index register may be scaled.  If an address involves the
      sum of two registers, neither one of them scaled, then either one
      may be labeled the "base" and the other the "index"; but whichever
      labeling is used must fit the machine's constraints of which
      registers may serve in each capacity.  The compiler will try both
      labelings, looking for one that is valid, and will reload one or
      both registers only if neither labeling works.
*/
#ifndef REG_OK_STRICT

/* Nonzero if X is a hard reg that can be used as an index
   or if it is a pseudo reg.  */
# define REG_OK_FOR_INDEX_P(X) \
  (REGNO(X) <= LAST_GENERAL_REGISTER || REGNO(X) >= FIRST_PSEUDO_REGISTER)

#else

/* Nonzero if X is a hard reg that can be used as an index.  */
# define REG_OK_FOR_INDEX_P(X) REGNO_OK_FOR_INDEX_P (REGNO (X))

#endif


/*
 `LEGITIMIZE_ADDRESS (X, OLDX, MODE, WIN)'
      A C compound statement that attempts to replace X with a valid
      memory address for an operand of mode MODE.  WIN will be a C
      statement label elsewhere in the code; the macro definition may use

           GO_IF_LEGITIMATE_ADDRESS (MODE, X, WIN);

      to avoid further processing if the address has become legitimate.

      X will always be the result of a call to `break_out_memory_refs',
      and OLDX will be the operand that was given to that function to
      produce X.

      The code generated by this macro should not alter the substructure
      of X.  If it transforms X into a more legitimate form, it should
      assign X (which will always be a C variable) a new value.

      It is not necessary for this macro to come up with a legitimate
      address.  The compiler has standard ways of doing so in all cases.
      In fact, it is safe for this macro to do nothing.  But often a
      machine-dependent strategy can generate better code.
*/
/*
   For now, don't do anything.  Gcc does quite a good job most often.

    Maybe we could do something about gcc:s misbahaviour when it
   recalculates frame offsets for local variables, from fp+offs to
   sp+offs.  The resulting address expression gets screwed up
   sometimes, but I'm not sure that it may be fixed here, since it is
   already split up in several instructions (Is this still true?) */
#define LEGITIMIZE_ADDRESS(X,OLDX,MODE,WIN)  {}


/*
 `GO_IF_MODE_DEPENDENT_ADDRESS (ADDR, LABEL)'
      A C statement or compound statement with a conditional `goto
      LABEL;' executed if memory address X (an RTX) can have different
      meanings depending on the machine mode of the memory reference it
      is used for or if the address is valid for some modes but not
      others.

      Autoincrement and autodecrement addresses typically have
      mode-dependent effects because the amount of the increment or
      decrement is the size of the operand being addressed.  Some
      machines have other mode-dependent addresses.  Many RISC machines
      have no mode-dependent addresses.

      You may assume that ADDR is a valid address for the machine.
*/
/* In Jvm, only the postincrement address mode depends thus,
   since the increment depends on the size of the operand. */

#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR,LABEL)        \
 { if (GET_CODE (ADDR) == POST_INC)                     \
     goto LABEL; }


/*
 `LEGITIMATE_CONSTANT_P (X)'
      A C expression that is nonzero if X is a legitimate constant for
      an immediate operand on the target machine.  You can assume that X
      satisfies `CONSTANT_P', so you need not check this.  In fact, `1'
      is a suitable definition for this macro on machines where anything
      `CONSTANT_P' is valid.
*/
#define LEGITIMATE_CONSTANT_P(X) 1


/* Section: Condition Code */

/*
 `CC_STATUS_MDEP'
      C code for a data type which is used for declaring the `mdep'
      component of `cc_status'.  It defaults to `int'.

      This macro is not used on machines that do not use `cc0'.
*/
/* Not defined */


/*
 `CC_STATUS_MDEP_INIT'
      A C expression to initialize the `mdep' field to "empty".  The
      default definition does nothing, since most machines don't use the
      field anyway.  If you want to use the field, you should probably
      define this macro to initialize it.

      This macro is not used on machines that do not use `cc0'.
*/
/* Not defined */


/*
 `NOTICE_UPDATE_CC (EXP, INSN)'
      A C compound statement to set the components of `cc_status'
      appropriately for an insn INSN whose body is EXP.  It is this
      macro's responsibility to recognize insns that set the condition
      code as a byproduct of other activity as well as those that
      explicitly set `(cc0)'.

      This macro is not used on machines that do not use `cc0'.

      If there are insns that do not set the condition code but do alter
      other machine registers, this macro must check to see whether they
      invalidate the expressions that the condition code is recorded as
      reflecting.  For example, on the 68000, insns that store in address
      registers do not set the condition code, which means that usually
      `NOTICE_UPDATE_CC' can leave `cc_status' unaltered for such insns.
      But suppose that the previous insn set the condition code based
      on location `a4@(102)' and the current insn stores a new value in
      `a4'.  Although the condition code is not changed by this, it will
      no longer be true that it reflects the contents of `a4@(102)'.
      Therefore, `NOTICE_UPDATE_CC' must alter `cc_status' in this case
      to say that nothing is known about the condition code value.

      The definition of `NOTICE_UPDATE_CC' must be prepared to deal with
      the results of peephole optimization: insns whose patterns are
      `parallel' RTXs containing various `reg', `mem' or constants which
      are just the operands.  The RTL structure of these insns is not
      sufficient to indicate what the insns actually do.  What
      `NOTICE_UPDATE_CC' should do when it sees one is just to run
      `CC_STATUS_INIT'.

      A possible definition of `NOTICE_UPDATE_CC' is to call a function
      that looks at an attribute (*note Insn Attributes::.) named, for
      example, `cc'.  This avoids having detailed information about
      patterns in two places, the `md' file and in `NOTICE_UPDATE_CC'.
*/
#define NOTICE_UPDATE_CC(EXP, INSN) notice_update_cc(EXP, INSN)

/*  moved to protos.h   extern void notice_update_cc(rtx, rtx); */


/*
 `EXTRA_CC_MODES'
      A list of names to be used for additional modes for condition code
      values in registers (*note Jump Patterns::.).  These names are
      added to `enum machine_mode' and all have class `MODE_CC'.  By
      convention, they should start with `CC' and end with `mode'.

      You should only define this macro if your machine does not use
      `cc0' and only if additional modes are required.
*/
/* Not defined */


/*
 `EXTRA_CC_NAMES'
      A list of C strings giving the names for the modes listed in
      `EXTRA_CC_MODES'.  For example, the Sparc defines this macro and
      `EXTRA_CC_MODES' as

           #define EXTRA_CC_MODES CC_NOOVmode, CCFPmode, CCFPEmode
           #define EXTRA_CC_NAMES "CC_NOOV", "CCFP", "CCFPE"

      This macro is not required if `EXTRA_CC_MODES' is not defined.
*/
/* Not defined */


/*
 `SELECT_CC_MODE (OP, X, Y)'
      Returns a mode from class `MODE_CC' to be used when comparison
      operation code OP is applied to rtx X and Y.  For example, on the
      Sparc, `SELECT_CC_MODE' is defined as (see *note Jump Patterns::.
      for a description of the reason for this definition)

           #define SELECT_CC_MODE(OP,X,Y) \
             (GET_MODE_CLASS (GET_MODE (X)) == MODE_FLOAT          \
              ? ((OP == EQ || OP == NE) ? CCFPmode : CCFPEmode)    \
              : ((GET_CODE (X) == PLUS || GET_CODE (X) == MINUS    \
                  || GET_CODE (X) == NEG) \
                 ? CC_NOOVmode : CCmode))

      You need not define this macro if `EXTRA_CC_MODES' is not defined.
*/
/* Not defined */


/*
 `CANONICALIZE_COMPARISON (CODE, OP0, OP1)'
      One some machines not all possible comparisons are defined, but
      you can convert an invalid comparison into a valid one.  For
      example, the Alpha does not have a `GT' comparison, but you can
      use an `LT' comparison instead and swap the order of the operands.

      On such machines, define this macro to be a C statement to do any
      required conversions.  CODE is the initial comparison code and OP0
      and OP1 are the left and right operands of the comparison,
      respectively.  You should modify CODE, OP0, and OP1 as required.

      GNU CC will not assume that the comparison resulting from this
      macro is valid but will see if the resulting insn matches a
      pattern in the `md' file.

      You need not define this macro if it would never change the
      comparison code or operands.
*/
/* Maybe define this later, when we play with optimizations.
   It is needed; currently we do this with instruction patterns and
   NOTICE_UPDATE_CC() */


/*
 `REVERSIBLE_CC_MODE (MODE)'
      A C expression whose value is one if it is always safe to reverse a
      comparison whose mode is MODE.  If `SELECT_CC_MODE' can ever
      return MODE for a floating-point inequality comparison, then
      `REVERSIBLE_CC_MODE (MODE)' must be zero.

      You need not define this macro if it would always returns zero or
      if the floating-point format is anything other than
      `IEEE_FLOAT_FORMAT'.  For example, here is the definition used on
      the Sparc, where floating-point inequality comparisons are always
      given `CCFPEmode':

           #define REVERSIBLE_CC_MODE(MODE)  ((MODE) != CCFPEmode)
*/
/* Not defined */


/* Section: Costs */

/*
 `CONST_COSTS (X, CODE, OUTER_CODE)'
      A part of a C `switch' statement that describes the relative costs
      of constant RTL expressions.  It must contain `case' labels for
      expression codes `const_int', `const', `symbol_ref', `label_ref'
      and `const_double'.  Each case must ultimately reach a `return'
      statement to return the relative cost of the use of that kind of
      constant value in an expression.  The cost may depend on the
      precise value of the constant, which is available for examination
      in X, and the rtx code of the expression in which it is contained,
      found in OUTER_CODE.

      CODE is the expression code--redundant, since it can be obtained
      with `GET_CODE (X)'.
*/
#define CONST_COSTS(RTX,CODE, OUTER_CODE)                           \
  case CONST_INT:                                                   \
    if (INTVAL(RTX) == 0) return 0;                                 \
    if (INTVAL (RTX) < 32 && INTVAL(RTX) >= -32) return 1;          \
  /* 8 or 16 bits */                                                \
    if (INTVAL (RTX) <= 32767 && INTVAL (RTX) >= -32768) return 2;  \
    return 4;  /* 32 bits (or very seldom, unsigned 16 bits) */     \
  case CONST:                                                       \
  case LABEL_REF:                                                   \
  case SYMBOL_REF:                                                  \
    return 6;                                                       \
  case CONST_DOUBLE:                                                \
    if (RTX != CONST0_RTX(GET_MODE(RTX) == VOIDmode ? DImode :      \
                          GET_MODE(RTX)))                           \
       return 12;                                                   \
    return 0; /* Make 0 cheap, else test-insns will not be used. */


/*
 `RTX_COSTS (X, CODE, OUTER_CODE)'
      Like `CONST_COSTS' but applies to nonconstant RTL expressions.
      This can be used, for example, to indicate how costly a multiply
      instruction is.  In writing this macro, you can use the construct
      `COSTS_N_INSNS (N)' to specify a cost equal to N fast
      instructions.  OUTER_CODE is the code of the expression in which X
      is contained.

      This macro is optional; do not define it if the default cost
      assumptions are adequate for the target machine.
*/
/* In 2.1, 2.7.2 you may return rtx_cost(X) for operands.  If you use
   a later version, check first that this is ok.  Used in cse.c
   ONLY. (2.1, 2.7.2) */
#define RTX_COSTS(X,CODE, OUTER_CODE)                                  \
        case MULT:                                                     \
          /* Identify values that are no powers of two. Powers of 2 */ \
          /* are taken care of already. */                             \
          if (GET_CODE(XEXP(X,1)) != CONST_INT                         \
              || exact_log2(INTVAL(XEXP(X,1)) < 0))                    \
            return COSTS_N_INSNS(132); /* Estimate as 4+4*#ofbits */   \
          break;                                                       \
        case UDIV:                                                     \
        case MOD:                                                      \
        case UMOD:                                                     \
        case DIV:                                                      \
          if (GET_CODE(XEXP(X,1)) != CONST_INT                         \
              || exact_log2(INTVAL(XEXP(X,1)) < 0))                    \
            return COSTS_N_INSNS(260); /* Estimate as 4+8*#ofbits */   \
        case AND:                                                      \
          if (GET_CODE(XEXP(X,1)) == CONST_INT                         \
              /* Two constants may actually happen before optimization */ \
              && GET_CODE(XEXP(X,0)) != CONST_INT                      \
              && !CONST_OK_FOR_LETTER_P(INTVAL(XEXP(X,1)),'I'))        \
            return rtx_cost(XEXP(X,0),SET)			       \
                   + 2 + 2*GET_MODE_NUNITS(GET_MODE(XEXP(X,0)));       \
        case ZERO_EXTEND: case SIGN_EXTEND:                            \
            /* Same as move. If embedded in other insn, cost is 0. */  \
            return rtx_cost(XEXP(X,0),SET);


/*
 `ADDRESS_COST (ADDRESS)'
      An expression giving the cost of an addressing mode that contains
      ADDRESS.  If not defined, the cost is computed from the ADDRESS
      expression and the `CONST_COSTS' values.

      For most CISC machines, the default cost is a good approximation
      of the true cost of the addressing mode.  However, on RISC
      machines, all instructions normally have the same length and
      execution time.  Hence all addresses will have equal costs.

      In cases where more than one form of an address is known, the form
      with the lowest cost will be used.  If multiple forms have the
      same, lowest, cost, the one that is the most complex will be used.

      For example, suppose an address that is equal to the sum of a
      register and a constant is used twice in the same basic block.
      When this macro is not defined, the address will be computed in a
      register and memory references will be indirect through that
      register.  On machines where the cost of the addressing mode
      containing the sum is no higher than that of a simple indirect
      reference, this will produce an additional instruction and
      possibly require an additional register.  Proper specification of
      this macro eliminates this overhead for such machines.

      Similar use of this macro is made in strength reduction of loops.

      ADDRESS need not be valid as an address.  In such a case, the cost
      is not relevant and can be any value; invalid addresses need not be
      assigned a different cost.

      On machines where an address involving more than one register is as
      cheap as an address computation involving only one register,
      defining `ADDRESS_COST' to reflect this can cause two registers to
      be live over a region of code where only one would have been if
      `ADDRESS_COST' were not defined in that manner.  This effect should
      be considered in the definition of this macro.  Equivalent costs
      should probably only be given to addresses with different numbers
      of registers on machines with lots of registers.

      This macro will normally either not be defined or be defined as a
      constant.
*/
/* Not defined */


/*
 `REGISTER_MOVE_COST (FROM, TO)'
      A C expression for the cost of moving data from a register in class
      FROM to one in class TO.  The classes are expressed using the
      enumeration values such as `GENERAL_REGS'.  A value of 4 is the
      default; other values are interpreted relative to that.

      It is not required that the cost always equal 2 when FROM is the
      same as TO; on some machines it is expensive to move between
      registers if they are not general registers.

      If reload sees an insn consisting of a single `set' between two
      hard registers, and if `REGISTER_MOVE_COST' applied to their
      classes returns a value of 2, reload does not check to ensure that
      the constraints of the insn are met.  Setting a cost of other than
      2 will allow reload to verify that the constraints are met.  You
      should do this if the `movM' pattern's constraints do not allow
      such copying.
*/
/* Not defined */


/*
 `MEMORY_MOVE_COST (M)'
      A C expression for the cost of moving data of mode M between a
      register and memory.  A value of 2 is the default; this cost is
      relative to those in `REGISTER_MOVE_COST'.

      If moving between registers and memory is more expensive than
      between two registers, you should define this macro to express the
      relative cost.
*/
/* Not defined */



/*
 `BRANCH_COST'
      A C expression for the cost of a branch instruction.  A value of 1
      is the default; other values are interpreted relative to that.
*/
/* Since we get a delay slot to fill, a branch may be considered expensive. 
#define BRANCH_COST 3
*/

/*
 `SLOW_BYTE_ACCESS'
      Define this macro as a C expression which is nonzero if accessing
      less than a word of memory (i.e. a `char' or a `short') is no
      faster than accessing a word of memory, i.e., if such access
      require more than one instruction or if there is no difference in
      cost between byte and (aligned) word loads.

      When this macro is not defined, the compiler will access a field by
      finding the smallest containing object; when it is defined, a
      fullword load will be used if alignment permits.  Unless bytes
      accesses are faster than word accesses, using word accesses is
      preferable since it may eliminate subsequent memory access if
      subsequent accesses occur to other fields in the same word of the
      structure, but to different bytes.
*/
#define SLOW_BYTE_ACCESS 0


/*
 `SLOW_ZERO_EXTEND'
      Define this macro if zero-extension (of a `char' or `short' to an
      `int') can be done faster if the destination is a register that is
      known to be zero.

      If you define this macro, you must have instruction patterns that
      recognize RTL structures like this:

           (set (strict_low_part (subreg:QI (reg:SI ...) 0)) ...)

      and likewise for `HImode'.
*/
/* Not defined */


/*
 `SLOW_UNALIGNED_ACCESS'
      Define this macro to be the value 1 if unaligned accesses have a
      cost many times greater than aligned accesses, for example if they
      are emulated in a trap handler.

      When this macro is non-zero, the compiler will act as if
      `STRICT_ALIGNMENT' were non-zero when generating code for block
      moves.  This can cause significantly more instructions to be
      produced.  Therefore, do not set this macro non-zero if unaligned
      accesses only add a cycle or two to the time for a memory access.

      If the value of this macro is always zero, it need not be defined.
*/
/* Not defined */


/*
 `DONT_REDUCE_ADDR'
      Define this macro to inhibit strength reduction of memory
      addresses.  (On some machines, such strength reduction seems to do
      harm rather than good.)
*/
/* Not defined */


/*
 `MOVE_RATIO'
      The number of scalar move insns which should be generated instead
      of a string move insn or a library call.  Increasing the value
      will always make code faster, but eventually incurs high cost in
      increased code size.

      If you don't define this, a reasonable default is used.
*/
/* Must be something to make gcc refrain from using blkmove insns.
    Due to a bug in gcc, it cannot see that a machine lacks "move mem,mem"
   instructions. */
/* ??? Define if code breaks (not defined in 2.6.3) */
#if 0
#define MOVE_RATIO -1
#endif


/*
 `NO_FUNCTION_CSE'
      Define this macro if it is as good or better to call a constant
      function address than to call an address kept in a register.
*/
/* Not defined */


/*
 `NO_RECURSIVE_FUNCTION_CSE'
      Define this macro if it is as good or better for a function to call
      itself with an explicit address than to call an address kept in a
      register.
*/
/* Not defined */


/*
 `ADJUST_COST (INSN, LINK, DEP_INSN, COST)'
      A C statement (sans semicolon) to update the integer variable COST
      based on the relationship between INSN that is dependent on
      DEP_INSN through the dependence LINK.  The default is to make no
      adjustment to COST.  This can be used for example to specify to
      the scheduler that an output- or anti-dependence does not incur
      the same cost as a data-dependence.
*/
/* Maybe define this later, when we play with optimizations. */


/* Section: Sections */

/*
 `TEXT_SECTION_ASM_OP'
      A C expression whose value is a string containing the assembler
      operation that should precede instructions and read-only data.
      Normally `".text"' is right.
*/
#define TEXT_SECTION_ASM_OP "//\t.text"


/*
 `DATA_SECTION_ASM_OP'
      A C expression whose value is a string containing the assembler
      operation to identify the following data as writable initialized
      data.  Normally `".data"' is right.

*/
#define DATA_SECTION_ASM_OP "//\t.data"


/*
 `SHARED_SECTION_ASM_OP'
      if defined, a C expression whose value is a string containing the
      assembler operation to identify the following data as shared data.
      If not defined, `DATA_SECTION_ASM_OP' will be used.
*/
/* Not defined */


/*
 `INIT_SECTION_ASM_OP'
      if defined, a C expression whose value is a string containing the
      assembler operation to identify the following data as
      initialization code.  If not defined, GNU CC will assume such a
      section does not exist.
*/
/* Not defined */


/*
 `EXTRA_SECTIONS'
      A list of names for sections other than the standard two, which are
      `in_text' and `in_data'.  You need not define this macro on a
      system with no other sections (that GCC needs to use).
*/
/* Not defined */


/*
 `EXTRA_SECTION_FUNCTIONS'
      One or more functions to be defined in `varasm.c'.  These
      functions should do jobs analogous to those of `text_section' and
      `data_section', for your additional sections.  Do not define this
      macro if you do not define `EXTRA_SECTIONS'.
*/
/* Not defined */


/*
 `READONLY_DATA_SECTION'
      On most machines, read-only variables, constants, and jump tables
      are placed in the text section.  If this is not the case on your
      machine, this macro should be defined to be the name of a function
      (either `data_section' or a function defined in `EXTRA_SECTIONS')
      that switches to the section to be used for read-only items.

      If these items should be placed in the text section, this macro
      should not be defined.
*/
/*#define READONLY_DATA_SECTION data_section*/
/* Not defined */


/*
 `SELECT_SECTION (EXP, RELOC)'
      A C statement or statements to switch to the appropriate section
      for output of EXP.  You can assume that EXP is either a `VAR_DECL'
      node or a constant of some sort.  RELOC indicates whether the
      initial value of EXP requires link-time relocations.  Select the
      section by calling `text_section' or one of the alternatives for
      other sections.

      Do not define this macro if you put all read-only variables and
      constants in the read-only data section (usually the text section).
*/
/*#define SELECT_SECTION(EXP, RELOC) data_section()*/
/* Not defined */


/*
 `SELECT_RTX_SECTION (MODE, RTX)'
      A C statement or statements to switch to the appropriate section
      for output of RTX in mode MODE.  You can assume that RTX is some
      kind of constant in RTL.  The argument MODE is redundant except in
      the case of a `const_int' rtx.  Select the section by calling
      `text_section' or one of the alternatives for other sections.

      Do not define this macro if you put all constants in the read-only
      data section.
*/
/* Not defined */


/* This was an attempt to deal with case statements.. real pain on JVM 
     - tw */
#undef HAVE_tablejump 


/*
 `JUMP_TABLES_IN_TEXT_SECTION'
      Define this macro if jump tables (for `tablejump' insns) should be
      output in the text section, along with the assembler instructions.
      Otherwise, the readonly data section is used.

      This macro is irrelevant if there is no separate readonly data
      section.
*/
/* Not defined */


/*
 `ENCODE_SECTION_INFO (DECL)'
      Define this macro if references to a symbol must be treated
      differently depending on something about the variable or function
      named by the symbol (such as what section it is in).

      The macro definition, if any, is executed immediately after the
      rtl for DECL has been created and stored in `DECL_RTL (DECL)'.
      The value of the rtl will be a `mem' whose address is a
      `symbol_ref'.

      The usual thing for this macro to do is to record a flag in the
      `symbol_ref' (such as `SYMBOL_REF_FLAG') or to store a modified
      name string in the `symbol_ref' (if one bit is not enough
      information).
*/
/* Not defined */

/*
 `STRIP_NAME_ENCODING (VAR, SYM_NAME)'
      Decode SYM_NAME and store the real name part in VAR, sans the
      characters that encode section info.  Define this macro if
      `ENCODE_SECTION_INFO' alters the symbol's name string.
*/
/* Unused-string-removal support for the JVM port (not in gcc-2.7.2)
   handled here.  No real name un-encoding done.  Name changed to "0"
   (the local multiple-definable macro) if string should not be
   output.  Default stripping done ('*' removed).
    Do not inhibit string output in *uses* of the label, only when the
   label (and the string) is to be output. */
/* Not defined */

/* Section: PIC */
/* (no definitions) */

/* Section: Assembler Format::File Framework */

/*
 `ASM_FILE_START (STREAM)'
      A C expression which outputs to the stdio stream STREAM some
      appropriate text to go at the start of an assembler file.

      Normally this macro is defined to output a line containing
      `#NO_APP', which is a comment that has no effect on most
      assemblers but tells the GNU assembler that it can save time by not
      checking for certain assembler constructs.

      On systems that use SDB, it is necessary to output certain
      commands; see `attasm.h'.
*/
/*
   NO_APP means faster assembly.
   It also means comments are not allowed.
   In some cases comments will be output for debugging purposes.
   Make sure they are allowed then. */
#define ASM_FILE_START(FILE)    \
    fprintf(FILE, "// gcc .net generated il asm code\n\n")

/*
 `ASM_FILE_END (STREAM)'
      A C expression which outputs to the stdio stream STREAM some
      appropriate text to go at the end of an assembler file.

      If this macro is not defined, the default is to output nothing
      special at the end of the file.  Most systems don't require any
      definition.

      On systems that use SDB, it is necessary to output certain
      commands; see `attasm.h'.
*/
/* Unused-string-removal support for the JVM port (not in gcc-2.7.2)
   Strings output here. */
/* Not defined */

/*
 `ASM_IDENTIFY_GCC (FILE)'
      A C statement to output assembler commands which will identify the
      object file as having been compiled with GNU CC (or another GNU
      compiler).

      If you don't define this macro, the string `gcc_compiled.:' is
      output.  This string is calculated to define a symbol which, on
      BSD systems, will never be defined for any other reason.  GDB
      checks for the presence of this symbol when reading the symbol
      table of an executable.

      On non-BSD systems, you must arrange communication with GDB in
      some other fashion.  If GDB is not used on your system, you can
      define this macro with an empty body.
*/
#define ASM_IDENTIFY_GCC(FILE) ;
/* Not defined */


/*
 `ASM_COMMENT_START'
      A C string constant describing how to begin a comment in the target
      assembler language.  The compiler assumes that the comment will
      end at the end of the line.
*/
/* Not defined */


/*
 `ASM_APP_ON'
      A C string constant for text to be output before each `asm'
      statement or group of consecutive ones.  Normally this is
      `"#APP"', which is a comment that has no effect on most assemblers
      but tells the GNU assembler that it must check the lines that
      follow for all valid assembler constructs.
*/
#define ASM_APP_ON "#APP\n"


/*
 `ASM_APP_OFF'
      A C string constant for text to be output after each `asm'
      statement or group of consecutive ones.  Normally this is
      `"#NO_APP"', which tells the GNU assembler to resume making the
      time-saving assumptions that are valid for ordinary compiler
      output.
*/
#define ASM_APP_OFF "" 
/*"#NO_APP\n"*/


/*
 `ASM_OUTPUT_SOURCE_FILENAME (STREAM, NAME)'
      A C statement to output COFF information or DWARF debugging
      information which indicates that filename NAME is the current
      source file to the stdio stream STREAM.

      This macro need not be defined if the standard form of output for
      the file format in use is appropriate.
*/
/* Not defined */


/*
 `ASM_OUTPUT_SOURCE_LINE (STREAM, LINE)'
      A C statement to output DBX or SDB debugging information before
      code for line number LINE of the current source file to the stdio
      stream STREAM.

      This macro need not be defined if the standard form of debugging
      information for the debugger in use is appropriate.
*/
/* Not defined */


/*
 `ASM_OUTPUT_IDENT (STREAM, STRING)'
      A C statement to output something to the assembler file to handle a
      `#ident' directive containing the text STRING.  If this macro is
      not defined, nothing is output for a `#ident' directive.
*/
/* Not defined */


/*
 `ASM_OUTPUT_SECTION_NAME (STREAM, DECL, NAME)'
      A C statement to output something to the assembler file to switch
      to section NAME for object DECL which is either a `FUNCTION_DECL',
      a `VAR_DECL' or `NULL_TREE'.  Some target formats do not support
      arbitrary sections.  Do not define this macro in such cases.

      At present this macro is only used to support section attributes.
      When this macro is undefined, section attributes are disabled.
*/
/* Not defined */


/*
 `OBJC_PROLOGUE'
      A C statement to output any assembler statements which are
      required to precede any Objective C object definitions or message
      sending.  The statement is executed only when compiling an
      Objective C program.
*/
/* Not defined */


/* Section: Assembler Format::Data Output */

/*
 `ASM_OUTPUT_LONG_DOUBLE (STREAM, VALUE)'
 `ASM_OUTPUT_DOUBLE (STREAM, VALUE)'
 `ASM_OUTPUT_FLOAT (STREAM, VALUE)'
 `ASM_OUTPUT_THREE_QUARTER_FLOAT (STREAM, VALUE)'
 `ASM_OUTPUT_SHORT_FLOAT (STREAM, VALUE)'
 `ASM_OUTPUT_BYTE_FLOAT (STREAM, VALUE)'
      A C statement to output to the stdio stream STREAM an assembler
      instruction to assemble a floating-point constant of `TFmode',
      `DFmode', `SFmode', `TQFmode', `HFmode', or `QFmode',
      respectively, whose value is VALUE.  VALUE will be a C expression
      of type `REAL_VALUE_TYPE'.  Macros such as
      `REAL_VALUE_TO_TARGET_DOUBLE' are useful for writing these
      definitions.
*/
/*
 * The GNU assembler, which we use, really should behave when doing
 * float numbers.  Unfortunalely it seems broken.
 *  There does not seem to be any use in fixing it, since
 * printing/parsing a float is much more expensize (takes time) than
 * to print/parse a hexnumber.  We may have to do it anyway, if we use
 * a host that does not have IEEE floating point.
 */

/* Note:  Floats have _not_ been implimented - tw */ /* Hurrah! I'm not going
                                                      * to bother either!
						      */ 

#ifndef JVM_FLOAT_NOT_BROKEN_ANY_MORE

# define ASM_OUTPUT_DOUBLE(FILE,VALUE)                              \
   do { union { float f; long l;} tem;                              \
          tem.f = (VALUE);                                          \
          fprintf (FILE, "\t.uaword 0x%x ; BOGUS double?\n", tem.l); \
      } while (0)

# define ASM_OUTPUT_FLOAT(FILE,VALUE)                                \
   do { union { float f; long l;} tem;                              \
          tem.f = (VALUE);                                          \
          fprintf (FILE, "\t.dword 0x%x\n", tem.l);                 \
      } while (0)

#else /* i.e. ! JVM_FLOAT_BROKEN... */

# define ASM_OUTPUT_DOUBLE(FILE,VALUE) \
   fprintf (FILE, "\t.float 0s%.10g ; BOGUS double?\n", (VALUE))

# define ASM_OUTPUT_FLOAT(FILE,VALUE)  \
   fprintf (FILE, "\t.float 0s%.10g\n", (VALUE))

#endif /*  JVM_FLOAT_NOT_BROKEN_ANY_MORE */

/* The oters are not deined, since they are not used. */


/*
 `ASM_OUTPUT_QUADRUPLE_INT (STREAM, EXP)'
 `ASM_OUTPUT_DOUBLE_INT (STREAM, EXP)'
 `ASM_OUTPUT_INT (STREAM, EXP)'
 `ASM_OUTPUT_SHORT (STREAM, EXP)'
 `ASM_OUTPUT_CHAR (STREAM, EXP)'
      A C statement to output to the stdio stream STREAM an assembler
      instruction to assemble an integer of 16, 8, 4, 2 or 1 bytes,
      respectively, whose value is VALUE.  The argument EXP will be an
      RTL expression which represents a constant value.  Use
      `output_addr_const (STREAM, EXP)' to output this value as an
      assembler expression.

      For sizes larger than `UNITS_PER_WORD', if the action of a macro
      would be identical to repeatedly calling the macro corresponding to
      a size of `UNITS_PER_WORD', once for each word, you need not define
      the macro.
*/

/* Very important.  When we are compiling C programs with global data the
   data definitions do not go into the jasmin file.  The definitions are
   dumped into a "global.s" file which is linked during the build process
   to an object file and then objdump'd to resolve symbol references to
   integers.  The object file is then objcopy'd and loaded into memory at
   run time. - tw */
extern FILE *datasection;

/* output the integer to the global.s file, regardless of what FILE is.
   All references to symbols are preceded with "symref" and proceded with
   "end" to make them easy to find in the jasmin output. - tw  
*/
/* jds31 - undo all of tw's work - get back to simple data sections */

#define ASM_OUTPUT_INT(FILE,VALUE)     \
  fprintf(FILE, "\t.int32 ");            \
  output_addr_const(FILE, VALUE);      \
  fprintf(FILE, "\n")

/*
#define ASM_OUTPUT_INT(FILE,VALUE)   \
( (my_string_label_referenced = 1),  \
   setup_datasection_now(), \
  fprintf (datasection, "\t.uaword "),       \
  output_addr_const (datasection, (VALUE)), \
  (my_string_label_referenced = 0),  \
  fprintf (datasection, "\n"))
*/

#define ASM_OUTPUT_SHORT(FILE,VALUE) \
  fprintf(FILE, "<SHORT OUTPUT - %d>", VALUE);

#define ASM_OUTPUT_CHAR(FILE,VALUE)  \
  fprintf(FILE, "<CHAR OUTPUT - %d>", VALUE);


/*
 `ASM_OUTPUT_BYTE (STREAM, VALUE)'
      A C statement to output to the stdio stream STREAM an assembler
      instruction to assemble a single byte containing the number VALUE.
*/
#define ASM_OUTPUT_BYTE(FILE,VALUE)  \
  fprintf (FILE, "\t.byte 0x%x\n", (VALUE))

/*
 `ASM_BYTE_OP'
      A C string constant giving the pseudo-op to use for a sequence of
      single-byte constants.  If this macro is not defined, the default
      is `"byte"'.
*/
/* Not defined */


/*
 `ASM_OUTPUT_ASCII (STREAM, PTR, LEN)'
      A C statement to output to the stdio stream STREAM an assembler
      instruction to assemble a string constant containing the LEN bytes
      at PTR.  PTR will be a C expression of type `char *' and LEN a C
      expression of type `int'.

      If the assembler has a `.ascii' pseudo-op as found in the Berkeley
      Unix assembler, do not define the macro `ASM_OUTPUT_ASCII'.
*/
/* Used to defer output of local constant strings until we know they
   are used.  The rest is copied from the defaults.h in gcc 2.7.2 */
/*#define ASM_OUTPUT_ASCII(MYFILE, MYSTRING, MYLENGTH) { \
  data_section(); \
  fprintf(MYFILE,".ascii \"%s\"\n",MYSTRING); \
}*/
/* Not defined */

/*
 `ASM_OUTPUT_POOL_PROLOGUE (FILE FUNNAME FUNDECL SIZE)'
      A C statement to output assembler commands to define the start of
      the constant pool for a function.  FUNNAME is a string giving the
      name of the function.  Should the return type of the function be
      required, it can be obtained via FUNDECL.  SIZE is the size, in
      bytes, of the constant pool that will be written immediately after
      this call.

      If no constant-pool prefix is required, the usual case, this macro
      need not be defined.
*/
/* 2.6.3 (and 2.7.2) has some bug causing it to create a constant pool
   when failing to match certain operand constraints.  This is a way to
   assert that our fix is valid. */
#define ASM_OUTPUT_POOL_PROLOGUE(FILE, FUNNAME, FUNDECL, SIZE)        \
  do                                                                  \
    {                                                                 \
      if (current_function_uses_const_pool)                           \
        {                                                             \
                fprintf(stderr, "FATAL! %s ``%s''\n",                 \
                        "Constant pool unsupported; used in function",\
                        FUNNAME);                                     \
                abort();                                              \
        }                                                             \
    }                                                                 \
  while (0)

/*
 `ASM_OUTPUT_SPECIAL_POOL_ENTRY (FILE, X, MODE, ALIGN, LABELNO, JUMPTO)'
      A C statement (with or without semicolon) to output a constant in
      the constant pool, if it needs special treatment.  (This macro
      need not do anything for RTL expressions that can be output
      normally.)

      The argument FILE is the standard I/O stream to output the
      assembler code on.  X is the RTL expression for the constant to
      output, and MODE is the machine mode (in case X is a `const_int').
      ALIGN is the required alignment for the value X; you should
      output an assembler directive to force this much alignment.

      The argument LABELNO is a number to use in an internal label for
      the address of this pool entry.  The definition of this macro is
      responsible for outputting the label definition at the proper
      place.  Here is how to do this:

           ASM_OUTPUT_INTERNAL_LABEL (FILE, "LC", LABELNO);

      When you output a pool entry specially, you should end with a
      `goto' to the label JUMPTO.  This will prevent the same pool entry
      from being output a second time in the usual manner.

      You need not define this macro if it would do nothing.
*/
/* Not defined */


/*
 `IS_ASM_LOGICAL_LINE_SEPARATOR (C)'
      Define this macro as a C expression which is nonzero if C is used
      as a logical line separator by the assembler.

      If you do not define this macro, the default is that only the
      character `;' is treated as a logical line separator.
*/
/* Not defined */


/*
 `ASM_OPEN_PAREN'
 `ASM_CLOSE_PAREN'
      These macros are defined as C string constant, describing the
      syntax in the assembler for grouping arithmetic expressions.  The
      following definitions are correct for most assemblers:

           #define ASM_OPEN_PAREN "("
           #define ASM_CLOSE_PAREN ")"
*/
#define ASM_OPEN_PAREN "("
#define ASM_CLOSE_PAREN ")"


/*
 `REAL_VALUE_TO_TARGET_SINGLE (X, L)'
 `REAL_VALUE_TO_TARGET_DOUBLE (X, L)'
 `REAL_VALUE_TO_TARGET_LONG_DOUBLE (X, L)'
      These translate X, of type `REAL_VALUE_TYPE', to the target's
      floating point representation, and store its bit pattern in the
      array of `long int' whose address is L.  The number of elements in
      the output array is determined by the size of the desired target
      floating point data type: 32 bits of it go in each `long int' array
      element.  Each array element holds 32 bits of the result, even if
      `long int' is wider than 32 bits on the host machine.

      The array element values are designed so that you can print them
      out using `fprintf' in the order they should appear in the target
      machine's memory.
*/
/* Not defined */


/*
 `REAL_VALUE_TO_DECIMAL (X, FORMAT, STRING)'
      This macro converts X, of type `REAL_VALUE_TYPE', to a decimal
      number and stores it as a string into STRING.  You must pass, as
      STRING, the address of a long enough block of space to hold the
      result.

      The argument FORMAT is a `printf'-specification that serves as a
      suggestion for how to format the output string.
*/
/* Not defined */


/* Section: Assembler Format::Uninitialized Data */

/*
 `ASM_OUTPUT_COMMON (STREAM, NAME, SIZE, ROUNDED)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM the assembler definition of a common-label named NAME whose
      size is SIZE bytes.  The variable ROUNDED is the size rounded up
      to whatever alignment the caller wants.

      Use the expression `assemble_name (STREAM, NAME)' to output the
      name itself; before and after that, output the additional
      assembler syntax for defining the name, and a newline.

      This macro controls how the assembler definitions of uninitialized
      global variables are output.
*/
#define ASM_OUTPUT_COMMON(FILE, NAME, SIZE, ROUNDED)                      \
( fputs ("\t.field public static valuetype vt_", (FILE)),                 \
  assemble_name ((FILE), (NAME)),                                         \
  fputs(" ", (FILE)),                                                     \
  assemble_name((FILE), (NAME)),                                          \
  fputs (" at d_", (FILE)),                                               \
  assemble_name ((FILE), (NAME)),                                         \
  fputs("\n\t.data d_", (FILE)),                                          \
  assemble_name ((FILE), (NAME)),                                         \
  fprintf((FILE), " = int32(0)[%d]\n",                                    \
	  (TARGET_DATA_ALIGN ? ((ROUNDED)+1)&~1 : (ROUNDED))/4),          \
  fputs("\t.class public explicit sealed serializable ansi vt_", (FILE)), \
  assemble_name ((FILE), (NAME)),                                         \
  fputs(" extends [mscorlib]System.ValueType\n", (FILE)),                 \
  fputs("\t{\n", (FILE)),                                                 \
  fputs("\t\t.pack 4\n", (FILE)),                                         \
  fprintf((FILE), "\t\t.size %d\n",                                       \
	  (TARGET_DATA_ALIGN ? ((ROUNDED)+1)&~1 : (ROUNDED))),            \
  fputs("\t\t.field [0] public specialname int32 elem__\n", (FILE)),      \
  fputs("\t}\n\n", (FILE)))


/*
 `ASM_OUTPUT_ALIGNED_COMMON (STREAM, NAME, SIZE, ALIGNMENT)'
      Like `ASM_OUTPUT_COMMON' except takes the required alignment as a
      separate, explicit argument.  If you define this macro, it is used
      in place of `ASM_OUTPUT_COMMON', and gives you more flexibility in
      handling the required alignment of the variable.  The alignment is
      specified as the number of bits.
*/
/* Not defined */


/*
 `ASM_OUTPUT_SHARED_COMMON (STREAM, NAME, SIZE, ROUNDED)'
      If defined, it is similar to `ASM_OUTPUT_COMMON', except that it
      is used when NAME is shared.  If not defined, `ASM_OUTPUT_COMMON'
      will be used.
*/
/* Not defined */


/*
 `ASM_OUTPUT_LOCAL (STREAM, NAME, SIZE, ROUNDED)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM the assembler definition of a local-common-label named NAME
      whose size is SIZE bytes.  The variable ROUNDED is the size
      rounded up to whatever alignment the caller wants.

      Use the expression `assemble_name (STREAM, NAME)' to output the
      name itself; before and after that, output the additional
      assembler syntax for defining the name, and a newline.

      This macro controls how the assembler definitions of uninitialized
      static variables are output.
*/
  /* jds31 - we can get away with making these the same (local and
   * common, on the CLR.
   */
#define ASM_OUTPUT_LOCAL(FILE, NAME, SIZE, ROUNDED)            \
       ASM_OUTPUT_COMMON(FILE, NAME, SIZE, ROUNDED)

/*
 `ASM_OUTPUT_ALIGNED_LOCAL (STREAM, NAME, SIZE, ALIGNMENT)'
      Like `ASM_OUTPUT_LOCAL' except takes the required alignment as a
      separate, explicit argument.  If you define this macro, it is used
      in place of `ASM_OUTPUT_LOCAL', and gives you more flexibility in
      handling the required alignment of the variable.  The alignment is
      specified as the number of bits.
*/
/* Not defined */


/*
 `ASM_OUTPUT_SHARED_LOCAL (STREAM, NAME, SIZE, ROUNDED)'
      If defined, it is similar to `ASM_OUTPUT_LOCAL', except that it is
      used when NAME is shared.  If not defined, `ASM_OUTPUT_LOCAL' will
      be used.
*/
/* Not defined */


/* Section: Assembler Format::Label Output */

/*
 `ASM_OUTPUT_LABEL (STREAM, NAME)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM the assembler definition of a label named NAME.  Use the
      expression `assemble_name (STREAM, NAME)' to output the name
      itself; before and after that, output the additional assembler
      syntax for defining the name, and a newline.
*/
#define ASM_OUTPUT_LABEL(FILE,NAME)  \
  assemble_name(FILE, NAME);         \
  fprintf(FILE, ":\n")


/*
 `ASM_DECLARE_FUNCTION_NAME (STREAM, NAME, DECL)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM any text necessary for declaring the name NAME of a
      function which is being defined.  This macro is responsible for
      outputting the label definition (perhaps using
      `ASM_OUTPUT_LABEL').  The argument DECL is the `FUNCTION_DECL'
      tree node representing the function.

      If this macro is not defined, then the function name is defined in
      the usual manner as a label (by means of `ASM_OUTPUT_LABEL').
*/
/* It seems like this is the only valid place to get the name of the current
   function; current_function_name is not valid during assembly output. */
#define ASM_DECLARE_FUNCTION_NAME(STREAM, NAME, DECL)  \
  fprintf(STREAM, "// <function decl - %s>\n.method public static int32 %s(", NAME, NAME)


/*
 `ASM_DECLARE_FUNCTION_SIZE (STREAM, NAME, DECL)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM any text necessary for declaring the size of a function
      which is being defined.  The argument NAME is the name of the
      function.  The argument DECL is the `FUNCTION_DECL' tree node
      representing the function.

      If this macro is not defined, then the function size is not
      defined.
*/
/* Not defined */


/*
 `ASM_DECLARE_OBJECT_NAME (STREAM, NAME, DECL)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM any text necessary for declaring the name NAME of an
      initialized variable which is being defined.  This macro must
      output the label definition (perhaps using `ASM_OUTPUT_LABEL').
      The argument DECL is the `VAR_DECL' tree node representing the
      variable.

      If this macro is not defined, then the variable name is defined in
      the usual manner as a label (by means of `ASM_OUTPUT_LABEL').
*/
/* Not defined */


/*
 `ASM_FINISH_DECLARE_OBJECT (STREAM, DECL, TOPLEVEL, ATEND)'
      A C statement (sans semicolon) to finish up declaring a variable
      name once the compiler has processed its initializer fully and
      thus has had a chance to determine the size of an array when
      controlled by an initializer.  This is used on systems where it's
      necessary to declare something about the size of the object.

      If you don't define this macro, that is equivalent to defining it
      to do nothing.
*/
/* Not defined */


/*
 `ASM_GLOBALIZE_LABEL (STREAM, NAME)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM some commands that will make the label NAME global; that
      is, available for reference from other files.  Use the expression
      `assemble_name (STREAM, NAME)' to output the name itself; before
      and after that, output the additional assembler syntax for making
      that name global, and a newline.
*/
#define ASM_GLOBALIZE_LABEL(FILE,NAME)   ;                             
/*  do { fputs ("\t.global ", FILE); assemble_name (FILE, NAME);        \
       fputs ("\n", FILE);} while (0)*/


/*
 `ASM_WEAKEN_LABEL'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM some commands that will make the label NAME weak; that is,
      available for reference from other files but only used if no other
      definition is available.  Use the expression `assemble_name
      (STREAM, NAME)' to output the name itself; before and after that,
      output the additional assembler syntax for making that name weak,
      and a newline.

      If you don't define this macro, GNU CC will not support weak
      symbols and you should not define the `SUPPORTS_WEAK' macro.
*/
/* Not defined */


/*
 `SUPPORTS_WEAK'
      A C expression which evaluates to true if the target supports weak
      symbols.

      If you don't define this macro, `defaults.h' provides a default
      definition.  If `ASM_WEAKEN_LABEL' is defined, the default
      definition is `1'; otherwise, it is `0'.  Define this macro if you
      want to control weak symbol support with a compiler flag such as
      `-melf'.
*/
/* Not defined */


/*
 `ASM_OUTPUT_EXTERNAL (STREAM, DECL, NAME)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM any text necessary for declaring the name of an external
      symbol named NAME which is referenced in this compilation but not
      defined.  The value of DECL is the tree node for the declaration.

      This macro need not be defined if it does not need to output
      anything.  The GNU assembler and most Unix assemblers don't
      require anything.
*/
/* Not defined */


/*
 `ASM_OUTPUT_EXTERNAL_LIBCALL (STREAM, SYMREF)'
      A C statement (sans semicolon) to output on STREAM an assembler
      pseudo-op to declare a library function name external.  The name
      of the library function is given by SYMREF, which has type `rtx'
      and is a `symbol_ref'.

      This macro need not be defined if it does not need to output
      anything.  The GNU assembler and most Unix assemblers don't
      require anything.
*/
/* Not defined */


/*
 `ASM_OUTPUT_LABELREF (STREAM, NAME)'
      A C statement (sans semicolon) to output to the stdio stream
      STREAM a reference in assembler syntax to a label named NAME.
      This should add `_' to the front of the name, if that is customary
      on your operating system, as it is in most Berkeley Unix systems.
      This macro is used in `assemble_name'.
*/
/* jds31 - on CLR, we don't want a leading _ */
/* #define ASM_OUTPUT_LABELREF(FILE,NAME)  \
     fprintf (FILE, "_%s", NAME)
*/
#define ASM_OUTPUT_LABELREF(FILE,NAME)  \
    fprintf (FILE, "%s", NAME)


/*
 `ASM_OUTPUT_INTERNAL_LABEL (STREAM, PREFIX, NUM)'
      A C statement to output to the stdio stream STREAM a label whose
      name is made from the string PREFIX and the number NUM.

      It is absolutely essential that these labels be distinct from the
      labels used for user-level functions and variables.  Otherwise,
      certain programs will have name conflicts with internal labels.

      It is desirable to exclude internal labels from the symbol table
      of the object file.  Most assemblers have a naming convention for
      labels that should be excluded; on many systems, the letter `L' at
      the beginning of a label has this effect.  You should find out what
      convention your system uses, and follow it.

      The usual definition of this macro is as follows:

           fprintf (STREAM, "L%s%d:\n", PREFIX, NUM)
*/
/* Unused-string-removal support for the JVM port (not in gcc-2.7.2)
   Do not output the label if it is in the list.  All strings *seem* to
   be defined before used, so if this label is *not* in the table,
   then no string has been defined (it might be a struct or vector). */ 
#define ASM_OUTPUT_INTERNAL_LABEL(FILE,PREFIX,NUM)   \
  fprintf (FILE, "%s%d:\n", PREFIX, NUM)

/*#define ASM_OUTPUT_INTERNAL_LABEL(FILE,PREFIX,NUM) \
 do                                                                          \
 { int _num = (NUM); char *_prefix = (PREFIX);                               \
   data_section(); \
   if (!TARGET_USED_STRINGS                                                  \
       || _prefix[0] != 'L' || _prefix[1] != 'C' || _prefix[2] != 0          \
       || !my_deferred_string_added(_num,NULL,0,0,0))                        \
     fprintf (FILE, "%s%d:\n", _prefix, _num);                               \
   else                                                                      \
   {                                                                         \
     my_deferred_string_added(_num,NULL,0,0,1);                              \
     my_inhibit_stringout = 1;   			                     \
     if (TARGET_PDEBUG || flag_print_asm_name)                               \
       fprintf (FILE, "; Not outputting %s%d:\n", _prefix, _num);            \
   }                                                                         \
 } while (0)
*/

/*
 `ASM_GENERATE_INTERNAL_LABEL (STRING, PREFIX, NUM)'
      A C statement to store into the string STRING a label whose name
      is made from the string PREFIX and the number NUM.

      This string, when output subsequently by `assemble_name', should
      produce the output that `ASM_OUTPUT_INTERNAL_LABEL' would produce
      with the same PREFIX and NUM.

      If the string begins with `*', then `assemble_name' will output
      the rest of the string unchanged.  It is often convenient for
      `ASM_GENERATE_INTERNAL_LABEL' to use `*' in this way.  If the
      string doesn't start with `*', then `ASM_OUTPUT_LABELREF' gets to
      output the string, and may change it.  (Of course,
      `ASM_OUTPUT_LABELREF' is also part of your machine description, so
      you should know what it does on your machine.)
*/
#define ASM_GENERATE_INTERNAL_LABEL(LABEL,PREFIX,NUM)   \
  sprintf (LABEL, "*%s%d", PREFIX, NUM)


/*
 `ASM_FORMAT_PRIVATE_NAME (OUTVAR, NAME, NUMBER)'
      A C expression to assign to OUTVAR (which is a variable of type
      `char *') a newly allocated string made from the string NAME and
      the number NUMBER, with some suitable punctuation added.  Use
      `alloca' to get space for the string.

      The string will be used as an argument to `ASM_OUTPUT_LABELREF' to
      produce an assembler label for an internal static variable whose
      name is NAME.  Therefore, the string must be such as to result in
      valid assembler code.  The argument NUMBER is different each time
      this macro is executed; it prevents conflicts between
      similarly-named internal static variables in different scopes.

      Ideally this string should not be a valid C identifier, to prevent
      any conflict with the user's own symbols.  Most assemblers allow
      periods or percent signs in assembler symbols; putting at least
      one of these between the name and the number will suffice.
*/
#define ASM_FORMAT_PRIVATE_NAME(OUTPUT, NAME, LABELNO)  \
( (OUTPUT) = (char *) alloca (strlen ((NAME)) + 10),    \
  sprintf ((OUTPUT), "%s.%d", (NAME), (LABELNO)))


/*
 `ASM_OUTPUT_DEF (STREAM, NAME, VALUE)'
      A C statement to output to the stdio stream STREAM assembler code
      which defines (equates) the symbol NAME to have the value VALUE.

      If SET_ASM_OP is defined, a default definition is provided which is
      correct for most systems.
*/
/* Maybe define this later, to support "alias" definitions. */


/*
 `OBJC_GEN_METHOD_LABEL (BUF, IS_INST, CLASS_NAME, CAT_NAME, SEL_NAME)'
      Define this macro to override the default assembler names used for
      Objective C methods.

      The default name is a unique method number followed by the name of
      the class (e.g. `_1_Foo').  For methods in categories, the name of
      the category is also included in the assembler name (e.g.
      `_1_Foo_Bar').

      These names are safe on most systems, but make debugging difficult
      since the method's selector is not present in the name.
      Therefore, particular systems define other ways of computing names.

      BUF is an expression of type `char *' which gives you a buffer in
      which to store the name; its length is as long as CLASS_NAME,
      CAT_NAME and SEL_NAME put together, plus 50 characters extra.

      The argument IS_INST specifies whether the method is an instance
      method or a class method; CLASS_NAME is the name of the class;
      CAT_NAME is the name of the category (or NULL if the method is not
      in a category); and SEL_NAME is the name of the selector.

      On systems where the assembler can handle quoted names, you can
      use this macro to provide more human-readable names.
*/
/* Not defined */


/* Section: Assembler Format::Initialization */
/* (no definitions) */

/* Section: Assembler Format::Macros for Initialization */
/* (no definitions since the defaults work; the gnu linker will
   understand the default magic) */

/* Section: Assembler Format::Instruction Output */

/*
 `REGISTER_NAMES'
      A C initializer containing the assembler's names for the machine
      registers, each one as a C string constant.  This is what
      translates register numbers in the compiler into assembler
      language.
*/
/* --- jds31 --- undefine this ---
 * #define REGISTER_NAMES                                         \
 * {"16", "1", "2", "3", "4", "5", "6", "7", "8",         \
 *  "9", "10", "11", "12", "13", "14", "pc", "srp"}
 */

/*
 `ADDITIONAL_REGISTER_NAMES'
      If defined, a C initializer for an array of structures containing
      a name and a register number.  This macro defines additional names
      for hard registers, thus allowing the `asm' option in declarations
      to refer to registers using alternate names.
*/
/* Not defined */


/*
 `ASM_OUTPUT_OPCODE (STREAM, PTR)'
      Define this macro if you are using an unusual assembler that
      requires different names for the machine instructions.

      The definition is a C statement or statements which output an
      assembler instruction opcode to the stdio stream STREAM.  The
      macro-operand PTR is a variable of type `char *' which points to
      the opcode name in its "internal" form--the form that is written
      in the machine description.  The definition should output the
      opcode name to STREAM, performing any translation you desire, and
      increment the variable PTR to point at the end of the opcode so
      that it will not be output twice.

      In fact, your macro definition may process less than the entire
      opcode name, or more than the opcode name; but if you want to
      process text that includes `%'-sequences to substitute operands,
      you must take care of the substitution yourself.  Just be sure to
      increment PTR over whatever text should not be output normally.

      If you need to look at the operand values, they can be found as the
      elements of `recog_operand'.

      If the macro definition does nothing, the instruction is output in
      the usual way.
*/
/* Not defined */


/*
 `FINAL_PRESCAN_INSN (INSN, OPVEC, NOPERANDS)'
      If defined, a C statement to be executed just prior to the output
      of assembler code for INSN, to modify the extracted operands so
      they will be output differently.

      Here the argument OPVEC is the vector containing the operands
      extracted from INSN, and NOPERANDS is the number of elements of
      the vector which contain meaningful data for this insn.  The
      contents of this vector are what will be used to convert the insn
      template into assembler code, so you can change the assembler
      output by changing the contents of the vector.

      This macro is useful when various assembler syntaxes share a single
      file of instruction patterns; by defining this macro differently,
      you can cause a large class of instructions to be output
      differently (such as with rearranged operands).  Naturally,
      variations in assembler syntax affecting individual insn patterns
      ought to be handled by writing conditional output routines in
      those patterns.

      If this macro is not defined, it is equivalent to a null statement.
*/
/* Not defined */


/*
 `PRINT_OPERAND (STREAM, X, CODE)'
      A C compound statement to output to stdio stream STREAM the
      assembler syntax for an instruction operand X.  X is an RTL
      expression.

      CODE is a value that can be used to specify one of several ways of
      printing the operand.  It is used when identical operands must be
      printed differently depending on the context.  CODE comes from the
      `%' specification that was used to request printing of the
      operand.  If the specification was just `%DIGIT' then CODE is 0;
      if the specification was `%LTR DIGIT' then CODE is the ASCII code
      for LTR.

      If X is a register, this macro should print the register's name.
      The names can be found in an array `reg_names' whose type is `char
      *[]'.  `reg_names' is initialized from `REGISTER_NAMES'.

      When the machine description has a specification `%PUNCT' (a `%'
      followed by a punctuation character), this macro is called with a
      null pointer for X and the punctuation character for CODE.
*/
#define PRINT_OPERAND(FILE, X, CODE)       \
       print_operand(FILE, X, CODE)

/* moved to protos.h   extern void print_operand(FILE *, rtx, int); */


/*
 `PRINT_OPERAND_PUNCT_VALID_P (CODE)'
      A C expression which evaluates to true if CODE is a valid
      punctuation character for use in the `PRINT_OPERAND' macro.  If
      `PRINT_OPERAND_PUNCT_VALID_P' is not defined, it means that no
      punctuation characters (except for the standard one, `%') are used
      in this way.
*/
#define PRINT_OPERAND_PUNCT_VALID_P(CODE) (CODE == '#') /* for "nop" in slot */


/*
 `PRINT_OPERAND_ADDRESS (STREAM, X)'
      A C compound statement to output to stdio stream STREAM the
      assembler syntax for an instruction operand that is a memory
      reference whose address is X.  X is an RTL expression.

      On some machines, the syntax for a symbolic address depends on the
      section that the address refers to.  On these machines, define the
      macro `ENCODE_SECTION_INFO' to store the information into the
      `symbol_ref', and then check for it here.  *Note Assembler
      Format::.
*/
#define PRINT_OPERAND_ADDRESS(FILE, ADDR)  \
       print_operand_address(FILE, ADDR)


/* moved to protos.h  extern void print_operand_address(FILE *, rtx); */


/*
 `DBR_OUTPUT_SEQEND(FILE)'
      A C statement, to be executed after all slot-filler instructions
      have been output.  If necessary, call `dbr_sequence_length' to
      determine the number of slots filled in a sequence (zero if not
      currently outputting a sequence), to decide how many no-ops to
      output, or whatever.

      Don't define this macro if it has nothing to do, but it is helpful
      in reading assembly output if the extent of the delay sequence is
      made explicit (e.g. with white space).

      Note that output routines for instructions with delay slots must be
      prepared to deal with not being output as part of a sequence (i.e.
      when the scheduling pass is not run, or when no slot fillers could
      be found.)  The variable `final_sequence' is null when not
      processing a sequence, otherwise it contains the `sequence' rtx
      being output.
*/
#define DBR_OUTPUT_SEQEND(FILE) \
  fprintf(FILE,"\n") /* Empty line to illustrate. */


/*
 `REGISTER_PREFIX'
 `LOCAL_LABEL_PREFIX'
 `USER_LABEL_PREFIX'
 `IMMEDIATE_PREFIX'
      If defined, C string expressions to be used for the `%R', `%L',
      `%U', and `%I' options of `asm_fprintf' (see `final.c').  These
      are useful when a single `md' file must support multiple assembler
      formats.  In that case, the various `tm.h' files can define these
      macros differently.
*/
/* Not defined */


/*
 `ASSEMBLER_DIALECT'
      If your target supports multiple dialects of assembler language
      (such as different opcodes), define this macro as a C expression
      that gives the numeric index of the assembler language dialect to
      use, with zero as the first variant.

      If this macro is defined, you may use
      `{option0|option1|option2...}' constructs in the output templates
      of patterns (*note Output Template::.) or in the first argument of
      `asm_fprintf'.  This construct outputs `option0', `option1' or
      `option2', etc., if the value of `ASSEMBLER_DIALECT' is zero, one
      or two, etc.  Any special characters within these strings retain
      their usual meaning.

      If you do not define this macro, the characters `{', `|' and `}'
      do not have any special meaning when used in templates or operands
      to `asm_fprintf'.

      Define the macros `REGISTER_PREFIX', `LOCAL_LABEL_PREFIX',
      `USER_LABEL_PREFIX' and `IMMEDIATE_PREFIX' if you can express the
      variations in assemble language syntax with that mechanism.  Define
      `ASSEMBLER_DIALECT' and use the `{option0|option1}' syntax if the
      syntax variant are larger and involve such things as different
      opcodes or operand order.
*/
/* Not defined */


/*
 `ASM_OUTPUT_REG_PUSH (STREAM, REGNO)'
      A C expression to output to STREAM some assembler code which will
      push hard register number REGNO onto the stack.  The code need not
      be optimal, since this macro is used only when profiling.
*/
#define ASM_OUTPUT_REG_PUSH(FILE,REGNO)                      \
  fprintf (FILE, "\tpush %s\n", reg_names[REGNO])


/*
 `ASM_OUTPUT_REG_POP (STREAM, REGNO)'
      A C expression to output to STREAM some assembler code which will
      pop hard register number REGNO off of the stack.  The code need
      not be optimal, since this macro is used only when profiling.
*/
#define ASM_OUTPUT_REG_POP(FILE,REGNO)                      \
  fprintf (FILE, "\tpop %s\n", reg_names[REGNO])


/* Section: Assembler Format::Dispatch Tables */

/*
 `ASM_OUTPUT_ADDR_DIFF_ELT (STREAM, VALUE, REL)'
      This macro should be provided on machines where the addresses in a
      dispatch table are relative to the table's own address.

      The definition should be a C statement to output to the stdio
      stream STREAM an assembler pseudo-instruction to generate a
      difference between two labels.  VALUE and REL are the numbers of
      two internal labels.  The definitions of these labels are output
      using `ASM_OUTPUT_INTERNAL_LABEL', and they must be printed in the
      same way here.  For example,

           fprintf (STREAM, "\t.word L%d-L%d\n",
                    VALUE, REL)
*/
#define ASM_OUTPUT_ADDR_DIFF_ELT(FILE, VALUE, REL,unused)  \
  fprintf (FILE, "\t.word L%d-L%d\n", VALUE, REL)


/*
 `ASM_OUTPUT_ADDR_VEC_ELT (STREAM, VALUE)'
      This macro should be provided on machines where the addresses in a
      dispatch table are absolute.

      The definition should be a C statement to output to the stdio
      stream STREAM an assembler pseudo-instruction to generate a
      reference to a label.  VALUE is the number of an internal label
      whose definition is output using `ASM_OUTPUT_INTERNAL_LABEL'.  For
      example,

           fprintf (STREAM, "\t.word L%d\n", VALUE)
*/
#define ASM_OUTPUT_ADDR_VEC_ELT(FILE, VALUE)  \
  fprintf (FILE, "\t.dword L%d\n", VALUE)


/*
 `ASM_OUTPUT_CASE_LABEL (STREAM, PREFIX, NUM, TABLE)'
      Define this if the label before a jump-table needs to be output
      specially.  The first three arguments are the same as for
      `ASM_OUTPUT_INTERNAL_LABEL'; the fourth argument is the jump-table
      which follows (a `jump_insn' containing an `addr_vec' or
      `addr_diff_vec').

      This feature is used on system V to output a `swbeg' statement for
      the table.

      If this macro is not defined, these labels are output with
      `ASM_OUTPUT_INTERNAL_LABEL'.
*/
/* Not defined */


/*
 `ASM_OUTPUT_CASE_END (STREAM, NUM, TABLE)'
      Define this if something special must be output at the end of a
      jump-table.  The definition should be a C statement to be executed
      after the assembler code for the table is written.  It should write
      the appropriate code to stdio stream STREAM.  The argument TABLE
      is the jump-table insn, and NUM is the label-number of the
      preceding label.

      If this macro is not defined, nothing special is output at the end
      of the jump-table.
*/
/* Since the "bound" insn loads the comparison value if the compared
   value (register) is out of bounds (0..comparison value-1), we need
   to output another case to catch it.
   The way to find it is to look after the "use" note inside the
   dummy-jump.  (It could be stored somewhere by the casesi expand,
   but that storage-position would have to be in a list, it cannot be
   stored in a scalar.)
    Check this construct when changing to new version of gcc.
    *//*
#define ASM_OUTPUT_CASE_END(STREAM, NUM, TABLE)                       \
  {                                                                   \
    fprintf(STREAM,"\t.word L%d-L%d%s\n",                             \
            CODE_LABEL_NUMBER(                                        \
              XEXP(XEXP(XVECEXP(PATTERN(PREV_INSN(PREV_INSN(TABLE))), \
                                                0,2),0),0)), NUM,     \
            (TARGET_PDEBUG ? "; default" : ""));                      \
  }
*/

/* Section: Assembler Format::Alignment Output */

/*
 `ASM_OUTPUT_ALIGN_CODE (FILE)'
      A C expression to output text to align the location counter in the
      way that is desirable at a point in the code that is reached only
      by jumping.

      This macro need not be defined if you don't want any special
      alignment to be done at such a time.  Most machine descriptions do
      not currently define the macro.
*/
/* Not defined */


/*
 `ASM_OUTPUT_LOOP_ALIGN (FILE)'
      A C expression to output text to align the location counter in the
      way that is desirable at the beginning of a loop.

      This macro need not be defined if you don't want any special
      alignment to be done at such a time.  Most machine descriptions do
      not currently define the macro.
*/
/* Not defined */


/*
 `ASM_OUTPUT_SKIP (STREAM, NBYTES)'
      A C statement to output to the stdio stream STREAM an assembler
      instruction to advance the location counter by NBYTES bytes.
      Those bytes should be zero when loaded.  NBYTES will be a C
      expression of type `int'.
*/
#define ASM_OUTPUT_SKIP(FILE,SIZE) ;
/* \
  fprintf (FILE, "\t.space %u\n", (SIZE))
*/

/*
 `ASM_NO_SKIP_IN_TEXT'
      Define this macro if `ASM_OUTPUT_SKIP' should not be used in the
      text section because it fails put zeros in the bytes that are
      skipped.  This is true on many Unix systems, where the pseudo-op
      to skip bytes produces no-op instructions rather than zeros when
      used in the text section.
*/
/* Not defined */


/*
 `ASM_OUTPUT_ALIGN (STREAM, POWER)'
      A C statement to output to the stdio stream STREAM an assembler
      command to advance the location counter to a multiple of 2 to the
      POWER bytes.  POWER will be a C expression of type `int'.
*/
#define ASM_OUTPUT_ALIGN(FILE,LOG)        \
  fprintf (FILE, "// \t.align %d\n", (LOG))


/* Section: Debugging Info::All Debuggers */

/*
 `DBX_REGISTER_NUMBER (REGNO)'
      A C expression that returns the DBX register number for the
      compiler register number REGNO.  In simple cases, the value of this
      expression may be REGNO itself.  But sometimes there are some
      registers that the compiler knows about and DBX does not, or vice
      versa.  In such cases, some register may need to have one number in
      the compiler and another for DBX.

      If two registers have consecutive numbers inside GNU CC, and they
      can be used as a pair to hold a multiword value, then they *must*
      have consecutive numbers after renumbering with
      `DBX_REGISTER_NUMBER'.  Otherwise, debuggers will be unable to
      access such a pair, because they expect register pairs to be
      consecutive in their own numbering scheme.

      If you find yourself defining `DBX_REGISTER_NUMBER' in way that
      does not preserve register pairs, then what you must do instead is
      redefine the actual register numbering scheme.
*/
/* Jvm needs no change in the numeration, I guess.  */
#define DBX_REGISTER_NUMBER(REGNO) (REGNO)


/*
 `DEBUGGER_AUTO_OFFSET (X)'
      A C expression that returns the integer offset value for an
      automatic variable having address X (an RTL expression).  The
      default computation assumes that X is based on the frame-pointer
      and gives the offset from the frame-pointer.  This is required for
      targets that produce debugging output for DBX or COFF-style
      debugging output for SDB and allow the frame-pointer to be
      eliminated when the `-g' options is used.
*/
/* Not defined */


/*
 `DEBUGGER_ARG_OFFSET (OFFSET, X)'
      A C expression that returns the integer offset value for an
      argument having address X (an RTL expression).  The nominal offset
      is OFFSET.
*/
/* Not defined */


/*
 `PREFERRED_DEBUGGING_TYPE'
      A C expression that returns the type of debugging output GNU CC
      produces when the user specifies `-g' or `-ggdb'.  Define this if
      you have arranged for GNU CC to support more than one format of
      debugging output.  Currently, the allowable values are `DBX_DEBUG',
      `SDB_DEBUG', `DWARF_DEBUG', and `XCOFF_DEBUG'.

      The value of this macro only affects the default debugging output;
      the user can always get a specific type of output by using
      `-gstabs', `-gcoff', `-gdwarf', or `-gxcoff'.
*/
/* Not defined */


/* Section: Debugging Info::DBX Options */

/*
 `DBX_DEBUGGING_INFO'
      Define this macro if GNU CC should produce debugging output for DBX
      in response to the `-g' option.
*/
/* Well, it seems to work nicely; the default stuff for the assembler
   and linker is to look like a BSD system, which uses DBX format. */
#define DBX_DEBUGGING_INFO


/*
 `XCOFF_DEBUGGING_INFO'
      Define this macro if GNU CC should produce XCOFF format debugging
      output in response to the `-g' option.  This is a variant of DBX
      format.
*/
/* Not defined */


/*
 `DEFAULT_GDB_EXTENSIONS'
      Define this macro to control whether GNU CC should by default
      generate GDB's extended version of DBX debugging information
      (assuming DBX-format debugging information is enabled at all).  If
      you don't define the macro, the default is 1: always generate the
      extended information if there is any occasion to.
*/
/* Not defined */


/*
 `DEBUG_SYMS_TEXT'
      Define this macro if all `.stabs' commands should be output while
      in the text section.
*/
/* Not defined */


/*
 `ASM_STABS_OP'
      A C string constant naming the assembler pseudo op to use instead
      of `.stabs' to define an ordinary debugging symbol.  If you don't
      define this macro, `.stabs' is used.  This macro applies only to
      DBX debugging information format.
*/
/* Not defined */


/*
 `ASM_STABD_OP'
      A C string constant naming the assembler pseudo op to use instead
      of `.stabd' to define a debugging symbol whose value is the current
      location.  If you don't define this macro, `.stabd' is used.  This
      macro applies only to DBX debugging information format.
*/
/* Not defined */


/*
 `ASM_STABN_OP'
      A C string constant naming the assembler pseudo op to use instead
      of `.stabn' to define a debugging symbol with no name.  If you
      don't define this macro, `.stabn' is used.  This macro applies
      only to DBX debugging information format.
*/
/* Not defined */


/*
 `DBX_NO_XREFS'
      Define this macro if DBX on your system does not support the
      construct `xsTAGNAME'.  On some systems, this construct is used to
      describe a forward reference to a structure named TAGNAME.  On
      other systems, this construct is not supported at all.
*/
/* Is this correct? Check later. */
#define DBX_NO_XREFS


/*
 `DBX_CONTIN_LENGTH'
      A symbol name in DBX-format debugging information is normally
      continued (split into two separate `.stabs' directives) when it
      exceeds a certain length (by default, 80 characters).  On some
      operating systems, DBX requires this splitting; on others,
      splitting must not be done.  You can inhibit splitting by defining
      this macro with the value zero.  You can override the default
      splitting-length by defining this macro as an expression for the
      length you desire.
*/
#define DBX_CONTIN_LENGTH 0


/*
 `DBX_CONTIN_CHAR'
      Normally continuation is indicated by adding a `\' character to
      the end of a `.stabs' string when a continuation follows.  To use
      a different character instead, define this macro as a character
      constant for the character you want to use.  Do not define this
      macro if backslash is correct for your system.
*/
#define DBX_CONTIN_CHAR '?'


/*
 `DBX_STATIC_STAB_DATA_SECTION'
      Define this macro if it is necessary to go to the data section
      before outputting the `.stabs' pseudo-op for a non-global static
      variable.
*/
#define DBX_STATIC_STAB_DATA_SECTION


/*
 `DBX_TYPE_DECL_STABS_CODE'
      The value to use in the "code" field of the `.stabs' directive for
      a typedef.  The default is `N_LSYM'.
*/
/* Not defined */


/*
 `DBX_STATIC_CONST_VAR_CODE'
      The value to use in the "code" field of the `.stabs' directive for
      a static variable located in the text section.  DBX format does not
      provide any "right" way to do this.  The default is `N_FUN'.
*/
/* Not defined */


/*
 `DBX_REGPARM_STABS_CODE'
      The value to use in the "code" field of the `.stabs' directive for
      a parameter passed in registers.  DBX format does not provide any
      "right" way to do this.  The default is `N_RSYM'.
*/
/* Not defined */


/*
 `DBX_REGPARM_STABS_LETTER'
      The letter to use in DBX symbol data to identify a symbol as a
      parameter passed in registers.  DBX format does not customarily
      provide any way to do this.  The default is `'P''.
*/
/* Not defined */


/*
 `DBX_MEMPARM_STABS_LETTER'
      The letter to use in DBX symbol data to identify a symbol as a
      stack parameter.  The default is `'p''.
*/
/* Not defined */


/*
 `DBX_FUNCTION_FIRST'
      Define this macro if the DBX information for a function and its
      arguments should precede the assembler code for the function.
      Normally, in DBX format, the debugging information entirely
      follows the assembler code.
*/
/* Not defined */


/*
 `DBX_LBRAC_FIRST'
      Define this macro if the `N_LBRAC' symbol for a block should
      precede the debugging information for variables and functions
      defined in that block.  Normally, in DBX format, the `N_LBRAC'
      symbol comes first.
*/
/* Not defined */


/*
 `DBX_BLOCKS_FUNCTION_RELATIVE'
      Define this macro if the value of a symbol describing the scope of
      a block (`N_LBRAC' or `N_RBRAC') should be relative to the start
      of the enclosing function.  Normally, GNU C uses an absolute
      address.
*/
/* Not defined */


/* Section: Debugging Info::DBX Hooks */
/* (no definitions) */

/* Section: Debugging Info::File names and DBX */
/* (no definitions) */

/* Section: Debugging Info::SDB and DWARF */
/* (no definitions) */

/* Section: Cross-compilation */
/* (no definitions) */

/* Section: Misc */

/*
 `PREDICATE_CODES'
      Define this if you have defined special-purpose predicates in the
      file `MACHINE.c'.  This macro is called within an initializer of an
      array of structures.  The first field in the structure is the name
      of a predicate and the second field is an array of rtl codes.  For
      each predicate, list all rtl codes that can be in expressions
      matched by the predicate.  The list should have a trailing comma.
      Here is an example of two entries in the list for a typical RISC
      machine:

           #define PREDICATE_CODES \
             {"gen_reg_rtx_operand", {SUBREG, REG}},  \
             {"reg_or_short_cint_operand", {SUBREG, REG, CONST_INT}},

      Defining this macro does not affect the generated code (however,
      incorrect definitions that omit an rtl code that may be matched by
      the predicate can cause the compiler to malfunction).  Instead, it
      allows the table built by `genrecog' to be more compact and
      efficient, thus speeding up the compiler.  The most important
      predicates to include in the list specified by this macro are
      thoses used in the most insn patterns.
*/
#if 0
/* DONT define this if there is ANY
   possibility that you will change them */
# define PREDICATE_CODES                                                  \
 { "index_operand",       { CONST_INT, REG, MULT, /* LSHIFT, ASHIFT */ }},\
 { "shift_operand",       { REG, MULT, /*LSHIFT, ASHIFT*/ }},             \
 { "orthogonal_operator", { PLUS, MINUS, IOR, AND, UMIN }},               \
 { "commutative_orth_op", { PLUS, IOR, AND, UMIN }},                      \
 { "extend_operator",     { ZERO_EXTEND, SIGN_EXTEND }},                  \
 { "add_sub_operator",    { PLUS, MINUS }},                               \
 { "zero_extend_op",      { ZERO_EXTEND }},                               \
 { "const_ref_operand",   { CONST, LABEL_REF, SYMBOL_REF }},
#endif


/*
 `CASE_VECTOR_MODE'
      An alias for a machine mode name.  This is the machine mode that
      elements of a jump-table should have.
*/
/* A combination of the bound (umin) insn together with a
   sign-extended add via the table to PC seems optimal.  If the
   table overflows, the assembler will take care of it. */
#define CASE_VECTOR_MODE HImode


/*
 `CASE_VECTOR_PC_RELATIVE'
      Define this macro if jump-tables should contain relative addresses.
*/
/*#define CASE_VECTOR_PC_RELATIVE*/


/*
 `CASE_DROPS_THROUGH'
      Define this if control falls through a `case' insn when the index
      value is out of range.  This means the specified default-label is
      actually ignored by the `case' insn proper.
*/
/* Not defined */


/*
 `CASE_VALUES_THRESHOLD'
      Define this to be the smallest number of different values for
      which it is best to use a jump-table instead of a tree of
      conditional branches.  The default is four for machines with a
      `casesi' instruction and five otherwise.  This is best for most
      machines.
*/
/* set this to some high value so we don't try to generate case/jump tables */
#define CASE_VALUES_THRESHOLD 1024
/* Not defined */


/*
 `WORD_REGISTER_OPERATIONS'
      Define this macro if operations between registers with integral
      mode smaller than a word are always performed on the entire
      register.  Most RISC machines have this property and most CISC
      machines do not.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `LOAD_EXTEND_OP (MODE)'
      Define this macro to be a C expression indicating when insns that
      read memory in MODE, an integral mode narrower than a word, set the
      bits outside of MODE to be either the sign-extension or the
      zero-extension of the data read.  Return `SIGN_EXTEND' for values
      of MODE for which the insn sign-extends, `ZERO_EXTEND' for which
      it zero-extends, and `NIL' for other modes.

      This macro is not called with MODE non-integral or with a width
      greater than or equal to `BITS_PER_WORD', so you may return any
      value in this case.  Do not define this macro if it would always
      return `NIL'.  On machines where this macro is defined, you will
      normally define it as the constant `SIGN_EXTEND' or `ZERO_EXTEND'.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `IMPLICIT_FIX_EXPR'
      An alias for a tree code that should be used by default for
      conversion of floating point values to fixed point.  Normally,
      `FIX_ROUND_EXPR' is used.
*/
#define IMPLICIT_FIX_EXPR FIX_ROUND_EXPR


/*
 `FIXUNS_TRUNC_LIKE_FIX_TRUNC'
      Define this macro if the same instructions that convert a floating
      point number to a signed fixed point number also convert validly
      to an unsigned one.
*/
#define FIXUNS_TRUNC_LIKE_FIX_TRUNC


/*
 `EASY_DIV_EXPR'
      An alias for a tree code that is the easiest kind of division to
      compile code for in the general case.  It may be `TRUNC_DIV_EXPR',
      `FLOOR_DIV_EXPR', `CEIL_DIV_EXPR' or `ROUND_DIV_EXPR'.  These four
      division operators differ in how they round the result to an
      integer.  `EASY_DIV_EXPR' is used when it is permissible to use
      any of those kinds of division and the choice should be made on
      the basis of efficiency.
*/
#define EASY_DIV_EXPR TRUNC_DIV_EXPR


/*
 `MOVE_MAX'
      The maximum number of bytes that a single instruction can move
      quickly from memory to memory.
*/
/* Conversation between UA (Ulf Andersson) and Richard Kenner (?)
   indicates that "one reasonably fast instruction" actually is "one
   reasonably fast instruction SEQUENCE" (that is, two instructions --
   mem => reg, reg => mem -- for jvm). */
/* ??? Change back to 0 if code breaks. */
#define MOVE_MAX 4


/*
 `MAX_MOVE_MAX'
      The maximum number of bytes that a single instruction can move
      quickly from memory to memory.  If this is undefined, the default
      is `MOVE_MAX'.  Otherwise, it is the constant value that is the
      largest value that `MOVE_MAX' can have at run-time.
*/
/* Not defined */


/*
 `SHIFT_COUNT_TRUNCATED'
      A C expression that is nonzero if on this machine the number of
      bits actually used for the count of a shift operation is equal to
      the number of bits needed to represent the size of the object
      being shifted.  When this macro is non-zero, the compiler will
      assume that it is safe to omit a sign-extend, zero-extend, and
      certain bitwise `and' instructions that truncates the count of a
      shift operation.  On machines that have instructions that act on
      bitfields at variable positions, which may include `bit test'
      instructions, a nonzero `SHIFT_COUNT_TRUNCATED' also enables
      deletion of truncations of the values that serve as arguments to
      bitfield instructions.

      If both types of instructions truncate the count (for shifts) and
      position (for bitfield operations), or if no variable-position
      bitfield instructions exist, you should define this macro.

      However, on some machines, such as the 80386 and the 680x0,
      truncation only applies to shift operations and not the (real or
      pretended) bitfield operations.  Define `SHIFT_COUNT_TRUNCATED' to
      be zero on such machines.  Instead, add patterns to the `md' file
      that include the implied truncation of the shift instructions.

      You need not define this macro if it would always have the value
      of zero.
*/
/* Maybe this should be defined?  Check later. */


/*
 `TRULY_NOOP_TRUNCATION (OUTPREC, INPREC)'
      A C expression which is nonzero if on this machine it is safe to
      "convert" an integer of INPREC bits to one of OUTPREC bits (where
      OUTPREC is smaller than INPREC) by merely operating on it as if it
      had only OUTPREC bits.

      On many machines, this expression can be 1.

      When `TRULY_NOOP_TRUNCATION' returns 1 for a pair of sizes for
      modes for which `MODES_TIEABLE_P' is 0, suboptimal code can result.
      If this is the case, making `TRULY_NOOP_TRUNCATION' return 0 in
      such cases may improve things.
*/
#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1


/*
 `STORE_FLAG_VALUE'
      A C expression describing the value returned by a comparison
      operator with an integral mode and stored by a store-flag
      instruction (`sCOND') when the condition is true.  This
      description must apply to *all* the `sCOND' patterns and all the
      comparison operators whose results have a `MODE_INT' mode.

      A value of 1 or -1 means that the instruction implementing the
      comparison operator returns exactly 1 or -1 when the comparison is
      true and 0 when the comparison is false.  Otherwise, the value
      indicates which bits of the result are guaranteed to be 1 when the
      comparison is true.  This value is interpreted in the mode of the
      comparison operation, which is given by the mode of the first
      operand in the `sCOND' pattern.  Either the low bit or the sign
      bit of `STORE_FLAG_VALUE' be on.  Presently, only those bits are
      used by the compiler.

      If `STORE_FLAG_VALUE' is neither 1 or -1, the compiler will
      generate code that depends only on the specified bits.  It can also
      replace comparison operators with equivalent operations if they
      cause the required bits to be set, even if the remaining bits are
      undefined.  For example, on a machine whose comparison operators
      return an `SImode' value and where `STORE_FLAG_VALUE' is defined as
      `0x80000000', saying that just the sign bit is relevant, the
      expression

           (ne:SI (and:SI X (const_int POWER-OF-2)) (const_int 0))

      can be converted to

           (ashift:SI X (const_int N))

      where N is the appropriate shift count to move the bit being
      tested into the sign bit.

      There is no way to describe a machine that always sets the
      low-order bit for a true value, but does not guarantee the value
      of any other bits, but we do not know of any machine that has such
      an instruction.  If you are trying to port GNU CC to such a
      machine, include an instruction to perform a logical-and of the
      result with 1 in the pattern for the comparison operators and let
      us know (*note How to Report Bugs: Bug Reporting.).

      Often, a machine will have multiple instructions that obtain a
      value from a comparison (or the condition codes).  Here are rules
      to guide the choice of value for `STORE_FLAG_VALUE', and hence the
      instructions to be used:

         * Use the shortest sequence that yields a valid definition for
           `STORE_FLAG_VALUE'.  It is more efficient for the compiler to
           "normalize" the value (convert it to, e.g., 1 or 0) than for
           the comparison operators to do so because there may be
           opportunities to combine the normalization with other
           operations.

         * For equal-length sequences, use a value of 1 or -1, with -1
           being slightly preferred on machines with expensive jumps and
           1 preferred on other machines.

         * As a second choice, choose a value of `0x80000001' if
           instructions exist that set both the sign and low-order bits
           but do not define the others.

         * Otherwise, use a value of `0x80000000'.

      Many machines can produce both the value chosen for
      `STORE_FLAG_VALUE' and its negation in the same number of
      instructions.  On those machines, you should also define a pattern
      for those cases, e.g., one matching

           (set A (neg:M (ne:M B C)))

      Some machines can also perform `and' or `plus' operations on
      condition code values with less instructions than the corresponding
      `sCOND' insn followed by `and' or `plus'.  On those machines,
      define the appropriate patterns.  Use the names `incscc' and
      `decscc', respectively, for the the patterns which perform `plus'
      or `minus' operations on condition code values.  See `rs6000.md'
      for some examples.  The GNU Superoptizer can be used to find such
      instruction sequences on other machines.

      You need not define `STORE_FLAG_VALUE' if the machine has no
      store-flag instructions.
*/
#define STORE_FLAG_VALUE 1


/*
 `FLOAT_STORE_FLAG_VALUE'
      A C expression that gives a non-zero floating point value that is
      returned when comparison operators with floating-point results are
      true.  Define this macro on machine that have comparison
      operations that return floating-point values.  If there are no
      such operations, do not define this macro.
*/
/* Not defined */


/*
 `Pmode'
      An alias for the machine mode for pointers.  On most machines,
      define this to be the integer mode corresponding to the width of a
      hardware pointer; `SImode' on 32-bit machine or `DImode' on 64-bit
      machines.  On some machines you must define this to be one of the
      partial integer modes, such as `PSImode'.

      The width of `Pmode' must be at least as large as the value of
      `POINTER_SIZE'.  If it is not equal, you must define the macro
      `POINTERS_EXTEND_UNSIGNED' to specify how pointers are extended to
      `Pmode'.
*/
#define Pmode SImode


/*
 `FUNCTION_MODE'
      An alias for the machine mode used for memory references to
      functions being called, in `call' RTL expressions.  On most
      machines this should be `QImode'.
*/
#define FUNCTION_MODE QImode


/*
 `INTEGRATE_THRESHOLD (DECL)'
      A C expression for the maximum number of instructions above which
      the function DECL should not be inlined.  DECL is a
      `FUNCTION_DECL' node.

      The default definition of this macro is 64 plus 8 times the number
      of arguments that the function accepts.  Some people think a larger
      threshold should be used on RISC machines.
*/
/* Maybe define this later, when we play with optimizations. */


/*
 `SCCS_DIRECTIVE'
      Define this if the preprocessor should ignore `#sccs' directives
      and print no error message.
*/
/* Not defined */


/*
 `NO_IMPLICIT_EXTERN_C'
      Define this macro if the system header files support C++ as well
      as C.  This macro inhibits the usual method of using system header
      files in C++, which is to pretend that the file's contents are
      enclosed in `extern "C" {...}'.
*/
/* Not defined */


/*
 `HANDLE_PRAGMA (STREAM)'
      Define this macro if you want to implement any pragmas.  If
      defined, it should be a C statement to be executed when `#pragma'
      is seen.  The argument STREAM is the stdio input stream from which
      the source text can be read.

      It is generally a bad idea to implement new uses of `#pragma'.  The
      only reason to define this macro is for compatibility with other
      compilers that do support `#pragma' for the sake of any user
      programs which already use it.
*/
/* Not defined */


/*
 `VALID_MACHINE_DECL_ATTRIBUTE (DECL, ATTRIBUTES, IDENTIFIER, ARGS)'
      If defined, a C expression whose value is nonzero if IDENTIFIER
      with arguments ARGS is a valid machine specific attribute for DECL.
      The attributes in ATTRIBUTES have previously been assigned to DECL.
*/
/* Not defined */


/*
 `VALID_MACHINE_TYPE_ATTRIBUTE (TYPE, ATTRIBUTES, IDENTIFIER, ARGS)'
      If defined, a C expression whose value is nonzero if IDENTIFIER
      with arguments ARGS is a valid machine specific attribute for TYPE.
      The attributes in ATTRIBUTES have previously been assigned to TYPE.
*/
/* Not defined */


/*
 `COMP_TYPE_ATTRIBUTES (TYPE1, TYPE2)'
      If defined, a C expression whose value is zero if the attributes on
      TYPE1 and TYPE2 are incompatible, one if they are compatible, and
      two if they are nearly compatible (which causes a warning to be
      generated).
*/
/* Not defined */


/*
 `SET_DEFAULT_TYPE_ATTRIBUTES (TYPE)'
      If defined, a C statement that assigns default attributes to newly
      defined TYPE.
*/
/* Not defined */


/*
 `DOLLARS_IN_IDENTIFIERS'
      Define this macro to control use of the character `$' in identifier
      names.  The value should be 0, 1, or 2.  0 means `$' is not allowed
      by default; 1 means it is allowed by default if `-traditional' is
      used; 2 means it is allowed by default provided `-ansi' is not
      used.  1 is the default; there is no need to define this macro in
      that case.
*/
/* Not defined */


/*
 `NO_DOLLAR_IN_LABEL'
      Define this macro if the assembler does not accept the character
      `$' in label names.  By default constructors and destructors in
      G++ have `$' in the identifiers.  If this macro is defined, `.' is
      used instead.
*/
/* Not defined */


/*
 `NO_DOT_IN_LABEL'
      Define this macro if the assembler does not accept the character
      `.' in label names.  By default constructors and destructors in G++
      have names that use `.'.  If this macro is defined, these names
      are rewritten to avoid `.'.
*/
/* Not defined */


/*
 `DEFAULT_MAIN_RETURN'
      Define this macro if the target system expects every program's
      `main' function to return a standard "success" value by default
      (if no other value is explicitly returned).

      The definition should be a C statement (sans semicolon) to
      generate the appropriate rtl instructions.  It is used only when
      compiling the end of `main'.
*/
/* Not defined */


/*
 `HAVE_ATEXIT'
      Define this if the target system supports the function `atexit'
      from the ANSI C standard.  If this is not defined, and
      `INIT_SECTION_ASM_OP' is not defined, a default `exit' function
      will be provided to support C++.
*/
/* Not defined */


/*
 `EXIT_BODY'
      Define this if your `exit' function needs to do something besides
      calling an external function `_cleanup' before terminating with
      `_exit'.  The `EXIT_BODY' macro is only needed if netiher
      `HAVE_ATEXIT' nor `INIT_SECTION_ASM_OP' are defined.
*/
/* Not defined */


/*
 `INSN_SETS_ARE_DELAYED (INSN)'
      Define this macro as a C expression that is nonzero if it is safe
      for the delay slot scheduler to place instructions in the delay
      slot of INSN, even if they appear to use a resource set or
      clobbered in INSN.  INSN is always a `jump_insn' or an `insn'; GNU
      CC knows that every `call_insn' has this behavior.  On machines
      where some `insn' or `jump_insn' is really a function call and
      hence has this behavior, you should define this macro.

      You need not define this macro if it would always return zero.
*/
/* Not defined */


/*
 `INSN_REFERENCES_ARE_DELAYED (INSN)'
      Define this macro as a C expression that is nonzero if it is safe
      for the delay slot scheduler to place instructions in the delay
      slot of INSN, even if they appear to set or clobber a resource
      referenced in INSN.  INSN is always a `jump_insn' or an `insn'.
      On machines where some `insn' or `jump_insn' is really a function
      call and its operands are registers whose use is actually in the
      subroutine it calls, you should define this macro.  Doing so
      allows the delay slot scheduler to move instructions which copy
      arguments into the argument registers into the delay slot of INSN.

      You need not define this macro if it would always return zero.
*/
/* Not defined */


/*
 `MACHINE_DEPENDENT_REORG (INSN)'
      In rare cases, correct code generation requires extra machine
      dependent processing between the second jump optimization pass and
      delayed branch scheduling.  On those machines, define this macro
      as a C statement to act on the code starting at INSN.
*/
/* Not defined */

/* END of tm.h */


/* end of clr.h */
