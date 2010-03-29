MACHINE=
SCRIPT_NAME=zpu
OUTPUT_FORMAT="elf32-zpu"
TEXT_START_ADDR=0x0
TEMPLATE_NAME=elf32
EXTRA_EM_FILE=zpuelf
OTHER_TEXT_SECTIONS='*(.glue_7t) *(.glue_7)'
OTHER_BSS_SYMBOLS='__bss_start__ = .;'
OTHER_BSS_END_SYMBOLS='_bss_end__ = . ; __bss_end__ = . ; __end__ = . ;'
OTHER_SECTIONS='.note.gnu.zpu.ident 0 : { KEEP (*(.note.gnu.zpu.ident)) }'

DATA_START_SYMBOLS='__data_start = . ;';

GENERATE_SHLIB_SCRIPT=yes

ARCH=zpu
MACHINE=
MAXPAGESIZE=1
ENTRY=_start
EMBEDDED=yes

# ZPU does not support .s* sections.
NO_SMALL_DATA=yes

CTOR_START='___ctors = .;'
CTOR_END='___ctors_end = .;'
DTOR_START='___dtors = .;'
DTOR_END='___dtors_end = .;'

STACK_ADDR='(0x1000000-0x10000)'
