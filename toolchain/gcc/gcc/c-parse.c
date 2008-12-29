/* A Bison parser, made from c-parse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	IDENTIFIER	257
# define	TYPENAME	258
# define	SCSPEC	259
# define	STATIC	260
# define	TYPESPEC	261
# define	TYPE_QUAL	262
# define	CONSTANT	263
# define	STRING	264
# define	ELLIPSIS	265
# define	SIZEOF	266
# define	ENUM	267
# define	STRUCT	268
# define	UNION	269
# define	IF	270
# define	ELSE	271
# define	WHILE	272
# define	DO	273
# define	FOR	274
# define	SWITCH	275
# define	CASE	276
# define	DEFAULT	277
# define	BREAK	278
# define	CONTINUE	279
# define	RETURN	280
# define	GOTO	281
# define	ASM_KEYWORD	282
# define	TYPEOF	283
# define	ALIGNOF	284
# define	ATTRIBUTE	285
# define	EXTENSION	286
# define	LABEL	287
# define	REALPART	288
# define	IMAGPART	289
# define	VA_ARG	290
# define	CHOOSE_EXPR	291
# define	TYPES_COMPATIBLE_P	292
# define	PTR_VALUE	293
# define	PTR_BASE	294
# define	PTR_EXTENT	295
# define	FUNC_NAME	296
# define	ASSIGN	297
# define	OROR	298
# define	ANDAND	299
# define	EQCOMPARE	300
# define	ARITHCOMPARE	301
# define	LSHIFT	302
# define	RSHIFT	303
# define	UNARY	304
# define	PLUSPLUS	305
# define	MINUSMINUS	306
# define	HYPERUNARY	307
# define	POINTSAT	308
# define	INTERFACE	309
# define	IMPLEMENTATION	310
# define	END	311
# define	SELECTOR	312
# define	DEFS	313
# define	ENCODE	314
# define	CLASSNAME	315
# define	PUBLIC	316
# define	PRIVATE	317
# define	PROTECTED	318
# define	PROTOCOL	319
# define	OBJECTNAME	320
# define	CLASS	321
# define	ALIAS	322
# define	AT_THROW	323
# define	AT_TRY	324
# define	AT_CATCH	325
# define	AT_FINALLY	326
# define	AT_SYNCHRONIZED	327
# define	OBJC_STRING	328

#line 34 "c-parse.y"

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "tree.h"
#include "input.h"
#include "cpplib.h"
#include "intl.h"
#include "timevar.h"
#include "c-pragma.h"		/* For YYDEBUG definition, and parse_in.  */
#include "c-tree.h"
#include "flags.h"
#include "varray.h"
#include "output.h"
#include "toplev.h"
#include "ggc.h"


/* Like YYERROR but do call yyerror.  */
#define YYERROR1 { yyerror ("syntax error"); YYERROR; }

/* Like the default stack expander, except (1) use realloc when possible,
   (2) impose no hard maxiumum on stack size, (3) REALLY do not use alloca.

   Irritatingly, YYSTYPE is defined after this %{ %} block, so we cannot
   give malloced_yyvs its proper type.  This is ok since all we need from
   it is to be able to free it.  */

static short *malloced_yyss;
static void *malloced_yyvs;

#define yyoverflow(MSG, SS, SSSIZE, VS, VSSIZE, YYSSZ)			\
do {									\
  size_t newsize;							\
  short *newss;								\
  YYSTYPE *newvs;							\
  newsize = *(YYSSZ) *= 2;						\
  if (malloced_yyss)							\
    {									\
      newss = really_call_realloc (*(SS), newsize * sizeof (short));	\
      newvs = really_call_realloc (*(VS), newsize * sizeof (YYSTYPE));	\
    }									\
  else									\
    {									\
      newss = really_call_malloc (newsize * sizeof (short));		\
      newvs = really_call_malloc (newsize * sizeof (YYSTYPE));		\
      if (newss)							\
        memcpy (newss, *(SS), (SSSIZE));				\
      if (newvs)							\
        memcpy (newvs, *(VS), (VSSIZE));				\
    }									\
  if (!newss || !newvs)							\
    {									\
      yyerror (MSG);							\
      return 2;								\
    }									\
  *(SS) = newss;							\
  *(VS) = newvs;							\
  malloced_yyss = newss;						\
  malloced_yyvs = (void *) newvs;					\
} while (0)

#line 100 "c-parse.y"
#ifndef YYSTYPE
typedef union {long itype; tree ttype; enum tree_code code;
	location_t location; } yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#line 234 "c-parse.y"

/* Number of statements (loosely speaking) and compound statements
   seen so far.  */
static int stmt_count;
static int compstmt_count;

/* Input location of the end of the body of last simple_if;
   used by the stmt-rule immediately after simple_if returns.  */
static location_t if_stmt_locus;


/* List of types and structure classes of the current declaration.  */
static GTY(()) tree current_declspecs;
static GTY(()) tree prefix_attributes;

/* List of all the attributes applying to the identifier currently being
   declared; includes prefix_attributes and possibly some more attributes
   just after a comma.  */
static GTY(()) tree all_prefix_attributes;

/* Stack of saved values of current_declspecs, prefix_attributes and
   all_prefix_attributes.  */
static GTY(()) tree declspec_stack;

/* PUSH_DECLSPEC_STACK is called from setspecs; POP_DECLSPEC_STACK
   should be called from the productions making use of setspecs.  */
#define PUSH_DECLSPEC_STACK						 \
  do {									 \
    declspec_stack = tree_cons (build_tree_list (prefix_attributes,	 \
						 all_prefix_attributes), \
				current_declspecs,			 \
				declspec_stack);			 \
  } while (0)

#define POP_DECLSPEC_STACK						\
  do {									\
    current_declspecs = TREE_VALUE (declspec_stack);			\
    prefix_attributes = TREE_PURPOSE (TREE_PURPOSE (declspec_stack));	\
    all_prefix_attributes = TREE_VALUE (TREE_PURPOSE (declspec_stack));	\
    declspec_stack = TREE_CHAIN (declspec_stack);			\
  } while (0)

/* For __extension__, save/restore the warning flags which are
   controlled by __extension__.  */
#define SAVE_EXT_FLAGS()		\
	(pedantic			\
	 | (warn_pointer_arith << 1)	\
	 | (warn_traditional << 2)	\
	 | (flag_iso << 3))

#define RESTORE_EXT_FLAGS(val)			\
  do {						\
    pedantic = val & 1;				\
    warn_pointer_arith = (val >> 1) & 1;	\
    warn_traditional = (val >> 2) & 1;		\
    flag_iso = (val >> 3) & 1;			\
  } while (0)


#define OBJC_NEED_RAW_IDENTIFIER(VAL)	/* nothing */

static bool parsing_iso_function_signature;

/* Tell yyparse how to print a token's value, if yydebug is set.  */

#define YYPRINT(FILE,YYCHAR,YYLVAL) yyprint(FILE,YYCHAR,YYLVAL)

static void yyprint (FILE *, int, YYSTYPE);
static void yyerror (const char *);
static int yylexname (void);
static inline int _yylex (void);
static int  yylex (void);
static void init_reswords (void);

  /* Initialisation routine for this file.  */
void
c_parse_init (void)
{
  init_reswords ();
}

#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		881
#define	YYFLAG		-32768
#define	YYNTBASE	97

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 328 ? yytranslate[x] : 297)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,     2,     2,    60,    51,     2,
      67,    89,    58,    56,    94,    57,    66,    59,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    90,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    96,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    95,    49,    91,    92,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    47,    48,
      52,    53,    54,    55,    61,    62,    63,    64,    65,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     3,     4,     7,     8,    12,    14,    16,
      18,    24,    27,    31,    36,    41,    44,    47,    50,    52,
      53,    54,    63,    68,    69,    70,    79,    84,    85,    86,
      94,    98,   100,   102,   104,   106,   108,   110,   112,   114,
     116,   118,   119,   121,   123,   127,   129,   132,   135,   138,
     141,   144,   149,   152,   157,   160,   163,   165,   167,   169,
     171,   176,   178,   182,   186,   190,   194,   198,   202,   206,
     210,   214,   218,   222,   226,   227,   232,   233,   238,   239,
     240,   248,   249,   255,   259,   263,   265,   267,   269,   271,
     272,   280,   284,   288,   292,   296,   301,   308,   317,   324,
     329,   333,   337,   340,   343,   345,   346,   348,   351,   353,
     355,   358,   361,   366,   371,   374,   377,   380,   381,   383,
     388,   393,   397,   401,   404,   407,   409,   412,   415,   418,
     421,   424,   426,   429,   431,   434,   437,   440,   443,   446,
     449,   451,   454,   457,   460,   463,   466,   469,   472,   475,
     478,   481,   484,   487,   490,   493,   496,   499,   501,   504,
     507,   510,   513,   516,   519,   522,   525,   528,   531,   534,
     537,   540,   543,   546,   549,   552,   555,   558,   561,   564,
     567,   570,   573,   576,   579,   582,   585,   588,   591,   594,
     597,   600,   603,   606,   609,   612,   615,   618,   621,   624,
     627,   630,   633,   635,   637,   639,   641,   643,   645,   647,
     649,   651,   653,   655,   657,   659,   661,   663,   665,   667,
     669,   671,   673,   675,   677,   679,   681,   683,   685,   687,
     689,   691,   693,   695,   697,   699,   701,   703,   705,   707,
     709,   711,   713,   715,   717,   719,   721,   723,   725,   727,
     729,   731,   733,   735,   737,   739,   741,   743,   745,   746,
     748,   750,   752,   754,   756,   758,   760,   762,   767,   772,
     774,   779,   781,   786,   787,   792,   793,   800,   804,   805,
     812,   816,   817,   819,   821,   824,   831,   833,   837,   838,
     840,   845,   852,   857,   859,   861,   863,   865,   867,   869,
     871,   872,   877,   879,   880,   883,   885,   889,   893,   896,
     897,   902,   904,   905,   910,   912,   914,   916,   919,   922,
     928,   932,   933,   934,   941,   942,   943,   950,   952,   954,
     959,   963,   966,   970,   972,   974,   976,   980,   983,   985,
     989,   992,   996,  1000,  1005,  1009,  1014,  1018,  1021,  1023,
    1025,  1028,  1030,  1033,  1035,  1038,  1039,  1047,  1053,  1054,
    1062,  1068,  1069,  1078,  1079,  1087,  1090,  1093,  1096,  1097,
    1099,  1100,  1102,  1104,  1107,  1108,  1112,  1115,  1119,  1122,
    1126,  1128,  1130,  1133,  1135,  1140,  1142,  1147,  1150,  1155,
    1159,  1162,  1167,  1171,  1173,  1177,  1179,  1181,  1185,  1186,
    1190,  1191,  1193,  1194,  1196,  1199,  1201,  1203,  1205,  1209,
    1212,  1216,  1221,  1225,  1228,  1231,  1233,  1238,  1242,  1247,
    1253,  1259,  1261,  1263,  1265,  1267,  1269,  1272,  1275,  1278,
    1281,  1283,  1286,  1289,  1292,  1294,  1297,  1300,  1303,  1306,
    1308,  1311,  1313,  1315,  1317,  1319,  1322,  1323,  1324,  1325,
    1326,  1327,  1329,  1331,  1334,  1338,  1340,  1343,  1345,  1347,
    1353,  1355,  1357,  1360,  1363,  1366,  1369,  1370,  1376,  1377,
    1382,  1383,  1385,  1388,  1392,  1395,  1398,  1399,  1404,  1406,
    1410,  1411,  1412,  1420,  1426,  1429,  1430,  1431,  1432,  1433,
    1446,  1447,  1454,  1457,  1459,  1461,  1464,  1468,  1471,  1474,
    1477,  1481,  1488,  1497,  1508,  1521,  1525,  1530,  1532,  1536,
    1542,  1545,  1550,  1551,  1553,  1554,  1556,  1557,  1559,  1561,
    1565,  1570,  1578,  1580,  1584,  1585,  1589,  1592,  1593,  1594,
    1601,  1604,  1605,  1607,  1609,  1613,  1615,  1619,  1624,  1629,
    1633,  1638,  1642,  1647,  1652,  1656,  1661,  1665,  1667,  1668,
    1672,  1674,  1677,  1679,  1683,  1685,  1689
};
static const short yyrhs[] =
{
      -1,    98,     0,     0,    99,   101,     0,     0,    98,   100,
     101,     0,   102,     0,   104,     0,   103,     0,    28,    67,
     113,    89,    90,     0,   296,   101,     0,   135,   169,    90,
       0,   155,   135,   169,    90,     0,   154,   135,   168,    90,
       0,   161,    90,     0,     1,    90,     0,     1,    91,     0,
      90,     0,     0,     0,   154,   135,   198,   105,   129,   258,
     106,   247,     0,   154,   135,   198,     1,     0,     0,     0,
     155,   135,   203,   107,   129,   258,   108,   247,     0,   155,
     135,   203,     1,     0,     0,     0,   135,   203,   109,   129,
     258,   110,   247,     0,   135,   203,     1,     0,     3,     0,
       4,     0,    51,     0,    57,     0,    56,     0,    62,     0,
      63,     0,    92,     0,    93,     0,   115,     0,     0,   115,
       0,   121,     0,   115,    94,   121,     0,   127,     0,    58,
     120,     0,   296,   120,     0,   112,   120,     0,    48,   111,
       0,   117,   116,     0,   117,    67,   224,    89,     0,   118,
     116,     0,   118,    67,   224,    89,     0,    34,   120,     0,
      35,   120,     0,    12,     0,    30,     0,    29,     0,   116,
       0,    67,   224,    89,   120,     0,   120,     0,   121,    56,
     121,     0,   121,    57,   121,     0,   121,    58,   121,     0,
     121,    59,   121,     0,   121,    60,   121,     0,   121,    54,
     121,     0,   121,    55,   121,     0,   121,    53,   121,     0,
     121,    52,   121,     0,   121,    51,   121,     0,   121,    49,
     121,     0,   121,    50,   121,     0,     0,   121,    48,   122,
     121,     0,     0,   121,    47,   123,   121,     0,     0,     0,
     121,    45,   124,   113,    46,   125,   121,     0,     0,   121,
      45,   126,    46,   121,     0,   121,    44,   121,     0,   121,
      43,   121,     0,     3,     0,     9,     0,    10,     0,    42,
       0,     0,    67,   224,    89,    95,   128,   184,    91,     0,
      67,   113,    89,     0,    67,     1,    89,     0,   251,   249,
      89,     0,   251,     1,    89,     0,   127,    67,   114,    89,
       0,    36,    67,   121,    94,   224,    89,     0,    37,    67,
     121,    94,   121,    94,   121,    89,     0,    38,    67,   224,
      94,   224,    89,     0,   127,    68,   113,    96,     0,   127,
      66,   111,     0,   127,    65,   111,     0,   127,    62,     0,
     127,    63,     0,   130,     0,     0,   132,     0,   258,   133,
       0,   131,     0,   239,     0,   132,   131,     0,   131,   239,
       0,   156,   135,   168,    90,     0,   157,   135,   169,    90,
       0,   156,    90,     0,   157,    90,     0,   258,   137,     0,
       0,   175,     0,   154,   135,   168,    90,     0,   155,   135,
     169,    90,     0,   154,   135,   192,     0,   155,   135,   195,
       0,   161,    90,     0,   296,   137,     0,     8,     0,   138,
       8,     0,   139,     8,     0,   138,   176,     0,   140,     8,
       0,   141,     8,     0,   176,     0,   140,   176,     0,   163,
       0,   142,     8,     0,   143,     8,     0,   142,   165,     0,
     143,   165,     0,   138,   163,     0,   139,   163,     0,   164,
       0,   142,   176,     0,   142,   166,     0,   143,   166,     0,
     138,   164,     0,   139,   164,     0,   144,     8,     0,   145,
       8,     0,   144,   165,     0,   145,   165,     0,   140,   163,
       0,   141,   163,     0,   144,   176,     0,   144,   166,     0,
     145,   166,     0,   140,   164,     0,   141,   164,     0,   181,
       0,   146,     8,     0,   147,     8,     0,   138,   181,     0,
     139,   181,     0,   146,   181,     0,   147,   181,     0,   146,
     176,     0,   148,     8,     0,   149,     8,     0,   140,   181,
       0,   141,   181,     0,   148,   181,     0,   149,   181,     0,
     148,   176,     0,   150,     8,     0,   151,     8,     0,   150,
     165,     0,   151,   165,     0,   146,   163,     0,   147,   163,
       0,   142,   181,     0,   143,   181,     0,   150,   181,     0,
     151,   181,     0,   150,   176,     0,   150,   166,     0,   151,
     166,     0,   146,   164,     0,   147,   164,     0,   152,     8,
       0,   153,     8,     0,   152,   165,     0,   153,   165,     0,
     148,   163,     0,   149,   163,     0,   144,   181,     0,   145,
     181,     0,   152,   181,     0,   153,   181,     0,   152,   176,
       0,   152,   166,     0,   153,   166,     0,   148,   164,     0,
     149,   164,     0,   142,     0,   143,     0,   144,     0,   145,
       0,   150,     0,   151,     0,   152,     0,   153,     0,   138,
       0,   139,     0,   140,     0,   141,     0,   146,     0,   147,
       0,   148,     0,   149,     0,   142,     0,   143,     0,   150,
       0,   151,     0,   138,     0,   139,     0,   146,     0,   147,
       0,   142,     0,   143,     0,   144,     0,   145,     0,   138,
       0,   139,     0,   140,     0,   141,     0,   142,     0,   143,
       0,   144,     0,   145,     0,   138,     0,   139,     0,   140,
       0,   141,     0,   138,     0,   139,     0,   140,     0,   141,
       0,   142,     0,   143,     0,   144,     0,   145,     0,   146,
       0,   147,     0,   148,     0,   149,     0,   150,     0,   151,
       0,   152,     0,   153,     0,     0,   159,     0,   165,     0,
     167,     0,   166,     0,     7,     0,   212,     0,   207,     0,
       4,     0,   119,    67,   113,    89,     0,   119,    67,   224,
      89,     0,   171,     0,   168,    94,   136,   171,     0,   173,
       0,   169,    94,   136,   173,     0,     0,    28,    67,    10,
      89,     0,     0,   198,   170,   175,    44,   172,   182,     0,
     198,   170,   175,     0,     0,   203,   170,   175,    44,   174,
     182,     0,   203,   170,   175,     0,     0,   176,     0,   177,
       0,   176,   177,     0,    31,    67,    67,   178,    89,    89,
       0,   179,     0,   178,    94,   179,     0,     0,   180,     0,
     180,    67,     3,    89,     0,   180,    67,     3,    94,   115,
      89,     0,   180,    67,   114,    89,     0,   111,     0,   181,
       0,     7,     0,     8,     0,     6,     0,     5,     0,   121,
       0,     0,    95,   183,   184,    91,     0,     1,     0,     0,
     185,   213,     0,   186,     0,   185,    94,   186,     0,   190,
      44,   188,     0,   191,   188,     0,     0,   111,    46,   187,
     188,     0,   188,     0,     0,    95,   189,   184,    91,     0,
     121,     0,     1,     0,   191,     0,   190,   191,     0,    66,
     111,     0,    68,   121,    11,   121,    96,     0,    68,   121,
      96,     0,     0,     0,   198,   193,   129,   258,   194,   252,
       0,     0,     0,   203,   196,   129,   258,   197,   252,     0,
     199,     0,   203,     0,    67,   175,   199,    89,     0,   199,
      67,   291,     0,   199,   232,     0,    58,   162,   199,     0,
       4,     0,   201,     0,   202,     0,   201,    67,   291,     0,
     201,   232,     0,     4,     0,   202,    67,   291,     0,   202,
     232,     0,    58,   162,   201,     0,    58,   162,   202,     0,
      67,   175,   202,    89,     0,   203,    67,   291,     0,    67,
     175,   203,    89,     0,    58,   162,   203,     0,   203,   232,
       0,     3,     0,    14,     0,    14,   176,     0,    15,     0,
      15,   176,     0,    13,     0,    13,   176,     0,     0,   204,
     111,    95,   208,   215,    91,   175,     0,   204,    95,   215,
      91,   175,     0,     0,   205,   111,    95,   209,   215,    91,
     175,     0,   205,    95,   215,    91,   175,     0,     0,   206,
     111,    95,   210,   222,   214,    91,   175,     0,     0,   206,
      95,   211,   222,   214,    91,   175,     0,   204,   111,     0,
     205,   111,     0,   206,   111,     0,     0,    94,     0,     0,
      94,     0,   216,     0,   216,   217,     0,     0,   216,   217,
      90,     0,   216,    90,     0,   158,   135,   218,     0,   158,
     135,     0,   159,   135,   219,     0,   159,     0,     1,     0,
     296,   217,     0,   220,     0,   218,    94,   136,   220,     0,
     221,     0,   219,    94,   136,   221,     0,   198,   175,     0,
     198,    46,   121,   175,     0,    46,   121,   175,     0,   203,
     175,     0,   203,    46,   121,   175,     0,    46,   121,   175,
       0,   223,     0,   222,    94,   223,     0,     1,     0,   111,
       0,   111,    44,   121,     0,     0,   160,   225,   226,     0,
       0,   228,     0,     0,   228,     0,   229,   176,     0,   230,
       0,   229,     0,   231,     0,    58,   162,   229,     0,    58,
     162,     0,    58,   162,   230,     0,    67,   175,   228,    89,
       0,   231,    67,   281,     0,   231,   232,     0,    67,   281,
       0,   232,     0,    68,   162,   121,    96,     0,    68,   162,
      96,     0,    68,   162,    58,    96,     0,    68,     6,   162,
     121,    96,     0,    68,   159,     6,   121,    96,     0,   234,
       0,   235,     0,   236,     0,   237,     0,   261,     0,   234,
     261,     0,   235,   261,     0,   236,   261,     0,   237,   261,
       0,   134,     0,   234,   134,     0,   235,   134,     0,   237,
     134,     0,   262,     0,   234,   262,     0,   235,   262,     0,
     236,   262,     0,   237,   262,     0,   239,     0,   238,   239,
       0,   234,     0,   235,     0,   236,     0,   237,     0,     1,
      90,     0,     0,     0,     0,     0,     0,   245,     0,   246,
       0,   245,   246,     0,    33,   295,    90,     0,   252,     0,
       1,   252,     0,    95,     0,    91,     0,   240,   244,   250,
      91,   241,     0,   233,     0,     1,     0,    67,    95,     0,
     248,   249,     0,   254,   260,     0,   254,     1,     0,     0,
      16,   255,    67,   113,    89,     0,     0,    19,   257,   260,
      18,     0,     0,   261,     0,   262,   259,     0,   242,   259,
     243,     0,   258,   273,     0,   258,   274,     0,     0,   253,
      17,   264,   260,     0,   253,     0,   253,    17,     1,     0,
       0,     0,    18,   265,    67,   113,    89,   266,   260,     0,
     256,    67,   113,    89,    90,     0,   256,     1,     0,     0,
       0,     0,     0,    20,   267,    67,   272,   268,   276,    90,
     269,   276,    89,   270,   260,     0,     0,    21,    67,   113,
      89,   271,   260,     0,   276,    90,     0,   137,     0,   252,
       0,   113,    90,     0,   242,   263,   243,     0,    24,    90,
       0,    25,    90,     0,    26,    90,     0,    26,   113,    90,
       0,    28,   275,    67,   113,    89,    90,     0,    28,   275,
      67,   113,    46,   277,    89,    90,     0,    28,   275,    67,
     113,    46,   277,    46,   277,    89,    90,     0,    28,   275,
      67,   113,    46,   277,    46,   277,    46,   280,    89,    90,
       0,    27,   111,    90,     0,    27,    58,   113,    90,     0,
      90,     0,    22,   121,    46,     0,    22,   121,    11,   121,
      46,     0,    23,    46,     0,   111,   258,    46,   175,     0,
       0,     8,     0,     0,   113,     0,     0,   278,     0,   279,
       0,   278,    94,   279,     0,    10,    67,   113,    89,     0,
      68,   111,    96,    10,    67,   113,    89,     0,    10,     0,
     280,    94,    10,     0,     0,   175,   282,   283,     0,   286,
      89,     0,     0,     0,   287,    90,   284,   175,   285,   283,
       0,     1,    89,     0,     0,    11,     0,   287,     0,   287,
      94,    11,     0,   289,     0,   287,    94,   288,     0,   154,
     135,   200,   175,     0,   154,   135,   203,   175,     0,   154,
     135,   227,     0,   155,   135,   203,   175,     0,   155,   135,
     227,     0,   156,   290,   200,   175,     0,   156,   290,   203,
     175,     0,   156,   290,   227,     0,   157,   290,   203,   175,
       0,   157,   290,   227,     0,   135,     0,     0,   175,   292,
     293,     0,   283,     0,   294,    89,     0,     3,     0,   294,
      94,     3,     0,   111,     0,   295,    94,   111,     0,    32,
       0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   318,   322,   329,   329,   331,   331,   334,   339,   341,
     342,   350,   354,   362,   364,   366,   368,   369,   370,   375,
     375,   375,   387,   389,   389,   389,   400,   402,   402,   402,
     413,   417,   419,   422,   424,   426,   431,   433,   435,   437,
     441,   445,   448,   451,   454,   458,   460,   463,   466,   470,
     472,   478,   481,   484,   487,   489,   493,   497,   501,   505,
     507,   511,   513,   515,   517,   519,   521,   523,   525,   527,
     529,   531,   533,   535,   537,   537,   544,   544,   551,   551,
     551,   561,   561,   572,   579,   590,   597,   598,   599,   601,
     601,   614,   619,   621,   635,   641,   643,   646,   656,   666,
     668,   672,   678,   680,   684,   691,   702,   712,   717,   719,
     720,   721,   728,   731,   733,   736,   744,   753,   763,   768,
     771,   773,   775,   777,   779,   835,   839,   842,   847,   853,
     857,   862,   866,   871,   875,   878,   881,   884,   887,   890,
     895,   899,   902,   905,   908,   911,   916,   920,   923,   926,
     929,   932,   937,   941,   944,   947,   950,   955,   959,   962,
     965,   971,   977,   983,   991,   997,  1001,  1004,  1010,  1016,
    1022,  1030,  1036,  1040,  1043,  1046,  1049,  1052,  1055,  1061,
    1067,  1073,  1081,  1085,  1088,  1091,  1094,  1099,  1103,  1106,
    1109,  1112,  1115,  1118,  1124,  1130,  1136,  1144,  1148,  1151,
    1154,  1157,  1163,  1165,  1166,  1167,  1168,  1169,  1170,  1171,
    1174,  1176,  1177,  1178,  1179,  1180,  1181,  1182,  1185,  1187,
    1188,  1189,  1192,  1194,  1195,  1196,  1199,  1201,  1202,  1203,
    1206,  1208,  1209,  1210,  1213,  1215,  1216,  1217,  1218,  1219,
    1220,  1221,  1224,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,  1244,  1247,
    1272,  1274,  1277,  1281,  1284,  1287,  1291,  1296,  1302,  1308,
    1310,  1313,  1315,  1318,  1321,  1325,  1325,  1334,  1341,  1341,
    1350,  1357,  1360,  1364,  1367,  1371,  1376,  1379,  1383,  1386,
    1388,  1390,  1392,  1399,  1401,  1402,  1403,  1406,  1408,  1413,
    1415,  1415,  1419,  1424,  1428,  1431,  1433,  1438,  1442,  1445,
    1445,  1451,  1454,  1454,  1459,  1461,  1464,  1466,  1469,  1472,
    1476,  1480,  1480,  1480,  1511,  1511,  1511,  1545,  1547,  1552,
    1555,  1560,  1562,  1564,  1571,  1573,  1576,  1582,  1584,  1587,
    1593,  1595,  1597,  1599,  1606,  1612,  1614,  1616,  1618,  1621,
    1624,  1628,  1631,  1635,  1638,  1648,  1648,  1656,  1660,  1660,
    1665,  1669,  1669,  1674,  1674,  1681,  1684,  1686,  1694,  1696,
    1699,  1701,  1718,  1721,  1726,  1728,  1730,  1735,  1739,  1749,
    1752,  1757,  1759,  1764,  1766,  1770,  1772,  1776,  1781,  1785,
    1791,  1796,  1800,  1809,  1811,  1816,  1821,  1824,  1828,  1828,
    1836,  1839,  1842,  1847,  1851,  1857,  1859,  1862,  1864,  1868,
    1871,  1875,  1878,  1880,  1882,  1884,  1890,  1893,  1895,  1897,
    1900,  1910,  1912,  1913,  1917,  1920,  1922,  1923,  1924,  1925,
    1928,  1930,  1936,  1937,  1940,  1942,  1943,  1944,  1945,  1948,
    1950,  1953,  1955,  1956,  1957,  1960,  1963,  1970,  1977,  1993,
    2008,  2010,  2015,  2017,  2020,  2034,  2037,  2040,  2044,  2046,
    2053,  2055,  2058,  2076,  2083,  2089,  2092,  2092,  2113,  2113,
    2136,  2142,  2144,  2148,  2154,  2168,  2177,  2177,  2186,  2198,
    2208,  2208,  2208,  2220,  2223,  2225,  2225,  2225,  2225,  2225,
    2242,  2242,  2251,  2254,  2259,  2262,  2265,  2269,  2278,  2287,
    2290,  2293,  2297,  2301,  2306,  2310,  2322,  2328,  2336,  2339,
    2342,  2345,  2360,  2363,  2367,  2370,  2375,  2377,  2380,  2382,
    2386,  2389,  2395,  2398,  2407,  2407,  2416,  2418,  2418,  2418,
    2425,  2431,  2433,  2444,  2448,  2454,  2457,  2463,  2469,  2474,
    2477,  2483,  2490,  2496,  2501,  2504,  2510,  2515,  2524,  2524,
    2533,  2535,  2552,  2555,  2560,  2563,  2567
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "IDENTIFIER", "TYPENAME", "SCSPEC", "STATIC", 
  "TYPESPEC", "TYPE_QUAL", "CONSTANT", "STRING", "ELLIPSIS", "SIZEOF", 
  "ENUM", "STRUCT", "UNION", "IF", "ELSE", "WHILE", "DO", "FOR", "SWITCH", 
  "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "GOTO", "ASM_KEYWORD", 
  "TYPEOF", "ALIGNOF", "ATTRIBUTE", "EXTENSION", "LABEL", "REALPART", 
  "IMAGPART", "VA_ARG", "CHOOSE_EXPR", "TYPES_COMPATIBLE_P", "PTR_VALUE", 
  "PTR_BASE", "PTR_EXTENT", "FUNC_NAME", "ASSIGN", "'='", "'?'", "':'", 
  "OROR", "ANDAND", "'|'", "'^'", "'&'", "EQCOMPARE", "ARITHCOMPARE", 
  "LSHIFT", "RSHIFT", "'+'", "'-'", "'*'", "'/'", "'%'", "UNARY", 
  "PLUSPLUS", "MINUSMINUS", "HYPERUNARY", "POINTSAT", "'.'", "'('", "'['", 
  "INTERFACE", "IMPLEMENTATION", "END", "SELECTOR", "DEFS", "ENCODE", 
  "CLASSNAME", "PUBLIC", "PRIVATE", "PROTECTED", "PROTOCOL", "OBJECTNAME", 
  "CLASS", "ALIAS", "AT_THROW", "AT_TRY", "AT_CATCH", "AT_FINALLY", 
  "AT_SYNCHRONIZED", "OBJC_STRING", "')'", "';'", "'}'", "'~'", "'!'", 
  "','", "'{'", "']'", "program", "extdefs", "@1", "@2", "extdef", 
  "extdef_1", "datadef", "fndef", "@3", "@4", "@5", "@6", "@7", "@8", 
  "identifier", "unop", "expr", "exprlist", "nonnull_exprlist", 
  "unary_expr", "sizeof", "alignof", "typeof", "cast_expr", 
  "expr_no_commas", "@9", "@10", "@11", "@12", "@13", "primary", "@14", 
  "old_style_parm_decls", "old_style_parm_decls_1", "lineno_datadecl", 
  "datadecls", "datadecl", "lineno_decl", "setspecs", "maybe_resetattrs", 
  "decl", "declspecs_nosc_nots_nosa_noea", "declspecs_nosc_nots_nosa_ea", 
  "declspecs_nosc_nots_sa_noea", "declspecs_nosc_nots_sa_ea", 
  "declspecs_nosc_ts_nosa_noea", "declspecs_nosc_ts_nosa_ea", 
  "declspecs_nosc_ts_sa_noea", "declspecs_nosc_ts_sa_ea", 
  "declspecs_sc_nots_nosa_noea", "declspecs_sc_nots_nosa_ea", 
  "declspecs_sc_nots_sa_noea", "declspecs_sc_nots_sa_ea", 
  "declspecs_sc_ts_nosa_noea", "declspecs_sc_ts_nosa_ea", 
  "declspecs_sc_ts_sa_noea", "declspecs_sc_ts_sa_ea", "declspecs_ts", 
  "declspecs_nots", "declspecs_ts_nosa", "declspecs_nots_nosa", 
  "declspecs_nosc_ts", "declspecs_nosc_nots", "declspecs_nosc", 
  "declspecs", "maybe_type_quals_attrs", "typespec_nonattr", 
  "typespec_attr", "typespec_reserved_nonattr", "typespec_reserved_attr", 
  "typespec_nonreserved_nonattr", "initdecls", "notype_initdecls", 
  "maybeasm", "initdcl", "@15", "notype_initdcl", "@16", 
  "maybe_attribute", "attributes", "attribute", "attribute_list", 
  "attrib", "any_word", "scspec", "init", "@17", "initlist_maybe_comma", 
  "initlist1", "initelt", "@18", "initval", "@19", "designator_list", 
  "designator", "nested_function", "@20", "@21", "notype_nested_function", 
  "@22", "@23", "declarator", "after_type_declarator", "parm_declarator", 
  "parm_declarator_starttypename", "parm_declarator_nostarttypename", 
  "notype_declarator", "struct_head", "union_head", "enum_head", 
  "structsp_attr", "@24", "@25", "@26", "@27", "structsp_nonattr", 
  "maybecomma", "maybecomma_warn", "component_decl_list", 
  "component_decl_list2", "component_decl", "components", 
  "components_notype", "component_declarator", 
  "component_notype_declarator", "enumlist", "enumerator", "typename", 
  "@28", "absdcl", "absdcl_maybe_attribute", "absdcl1", "absdcl1_noea", 
  "absdcl1_ea", "direct_absdcl1", "array_declarator", "stmts_and_decls", 
  "lineno_stmt_decl_or_labels_ending_stmt", 
  "lineno_stmt_decl_or_labels_ending_decl", 
  "lineno_stmt_decl_or_labels_ending_label", 
  "lineno_stmt_decl_or_labels_ending_error", "lineno_stmt_decl_or_labels", 
  "errstmt", "pushlevel", "poplevel", "c99_block_start", "c99_block_end", 
  "maybe_label_decls", "label_decls", "label_decl", "compstmt_or_error", 
  "compstmt_start", "compstmt_nostart", "compstmt_contents_nonempty", 
  "compstmt_primary_start", "compstmt", "simple_if", "if_prefix", "@29", 
  "do_stmt_start", "@30", "save_location", "lineno_labeled_stmt", 
  "c99_block_lineno_labeled_stmt", "lineno_stmt", "lineno_label", 
  "select_or_iter_stmt", "@31", "@32", "@33", "@34", "@35", "@36", "@37", 
  "@38", "for_init_stmt", "stmt", "label", "maybe_type_qual", "xexpr", 
  "asm_operands", "nonnull_asm_operands", "asm_operand", "asm_clobbers", 
  "parmlist", "@39", "parmlist_1", "@40", "@41", "parmlist_2", "parms", 
  "parm", "firstparm", "setspecs_fp", "parmlist_or_identifiers", "@42", 
  "parmlist_or_identifiers_1", "identifiers", "identifiers_or_typenames", 
  "extension", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    97,    97,    99,    98,   100,    98,   101,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   105,
     106,   104,   104,   107,   108,   104,   104,   109,   110,   104,
     104,   111,   111,   112,   112,   112,   112,   112,   112,   112,
     113,   114,   114,   115,   115,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   118,   119,   120,
     120,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   122,   121,   123,   121,   124,   125,
     121,   126,   121,   121,   121,   127,   127,   127,   127,   128,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   129,   130,   130,   131,   132,   132,
     132,   132,   133,   133,   133,   133,   134,   135,   136,   137,
     137,   137,   137,   137,   137,   138,   138,   138,   139,   140,
     140,   141,   141,   142,   142,   142,   142,   142,   142,   142,
     143,   143,   143,   143,   143,   143,   144,   144,   144,   144,
     144,   144,   145,   145,   145,   145,   145,   146,   146,   146,
     146,   146,   146,   146,   147,   148,   148,   148,   148,   148,
     148,   149,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   151,   151,   151,   151,   151,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   153,   153,   153,
     153,   153,   154,   154,   154,   154,   154,   154,   154,   154,
     155,   155,   155,   155,   155,   155,   155,   155,   156,   156,
     156,   156,   157,   157,   157,   157,   158,   158,   158,   158,
     159,   159,   159,   159,   160,   160,   160,   160,   160,   160,
     160,   160,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   162,   162,
     163,   163,   164,   165,   165,   166,   167,   167,   167,   168,
     168,   169,   169,   170,   170,   172,   171,   171,   174,   173,
     173,   175,   175,   176,   176,   177,   178,   178,   179,   179,
     179,   179,   179,   180,   180,   180,   180,   181,   181,   182,
     183,   182,   182,   184,   184,   185,   185,   186,   186,   187,
     186,   186,   189,   188,   188,   188,   190,   190,   191,   191,
     191,   193,   194,   192,   196,   197,   195,   198,   198,   199,
     199,   199,   199,   199,   200,   200,   201,   201,   201,   202,
     202,   202,   202,   202,   203,   203,   203,   203,   203,   204,
     204,   205,   205,   206,   206,   208,   207,   207,   209,   207,
     207,   210,   207,   211,   207,   212,   212,   212,   213,   213,
     214,   214,   215,   215,   216,   216,   216,   217,   217,   217,
     217,   217,   217,   218,   218,   219,   219,   220,   220,   220,
     221,   221,   221,   222,   222,   222,   223,   223,   225,   224,
     226,   226,   227,   227,   227,   228,   228,   229,   229,   230,
     230,   231,   231,   231,   231,   231,   232,   232,   232,   232,
     232,   233,   233,   233,   233,   234,   234,   234,   234,   234,
     235,   235,   235,   235,   236,   236,   236,   236,   236,   237,
     237,   238,   238,   238,   238,   239,   240,   241,   242,   243,
     244,   244,   245,   245,   246,   247,   247,   248,   249,   249,
     250,   250,   251,   252,   253,   253,   255,   254,   257,   256,
     258,   259,   259,   260,   261,   262,   264,   263,   263,   263,
     265,   266,   263,   263,   263,   267,   268,   269,   270,   263,
     271,   263,   272,   272,   273,   273,   273,   273,   273,   273,
     273,   273,   273,   273,   273,   273,   273,   273,   274,   274,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     279,   279,   280,   280,   282,   281,   283,   284,   285,   283,
     283,   286,   286,   286,   286,   287,   287,   288,   288,   288,
     288,   288,   289,   289,   289,   289,   289,   290,   292,   291,
     293,   293,   294,   294,   295,   295,   296
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     1,     0,     2,     0,     3,     1,     1,     1,
       5,     2,     3,     4,     4,     2,     2,     2,     1,     0,
       0,     8,     4,     0,     0,     8,     4,     0,     0,     7,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     1,     3,     1,     2,     2,     2,     2,
       2,     4,     2,     4,     2,     2,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     0,     0,
       7,     0,     5,     3,     3,     1,     1,     1,     1,     0,
       7,     3,     3,     3,     3,     4,     6,     8,     6,     4,
       3,     3,     2,     2,     1,     0,     1,     2,     1,     1,
       2,     2,     4,     4,     2,     2,     2,     0,     1,     4,
       4,     3,     3,     2,     2,     1,     2,     2,     2,     2,
       2,     1,     2,     1,     2,     2,     2,     2,     2,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     1,
       4,     1,     4,     0,     4,     0,     6,     3,     0,     6,
       3,     0,     1,     1,     2,     6,     1,     3,     0,     1,
       4,     6,     4,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     2,     1,     3,     3,     2,     0,
       4,     1,     0,     4,     1,     1,     1,     2,     2,     5,
       3,     0,     0,     6,     0,     0,     6,     1,     1,     4,
       3,     2,     3,     1,     1,     1,     3,     2,     1,     3,
       2,     3,     3,     4,     3,     4,     3,     2,     1,     1,
       2,     1,     2,     1,     2,     0,     7,     5,     0,     7,
       5,     0,     8,     0,     7,     2,     2,     2,     0,     1,
       0,     1,     1,     2,     0,     3,     2,     3,     2,     3,
       1,     1,     2,     1,     4,     1,     4,     2,     4,     3,
       2,     4,     3,     1,     3,     1,     1,     3,     0,     3,
       0,     1,     0,     1,     2,     1,     1,     1,     3,     2,
       3,     4,     3,     2,     2,     1,     4,     3,     4,     5,
       5,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       1,     2,     2,     2,     1,     2,     2,     2,     2,     1,
       2,     1,     1,     1,     1,     2,     0,     0,     0,     0,
       0,     1,     1,     2,     3,     1,     2,     1,     1,     5,
       1,     1,     2,     2,     2,     2,     0,     5,     0,     4,
       0,     1,     2,     3,     2,     2,     0,     4,     1,     3,
       0,     0,     7,     5,     2,     0,     0,     0,     0,    12,
       0,     6,     2,     1,     1,     2,     3,     2,     2,     2,
       3,     6,     8,    10,    12,     3,     4,     1,     3,     5,
       2,     4,     0,     1,     0,     1,     0,     1,     1,     3,
       4,     7,     1,     3,     0,     3,     2,     0,     0,     6,
       2,     0,     1,     1,     3,     1,     3,     4,     4,     3,
       4,     3,     4,     4,     3,     4,     3,     1,     0,     3,
       1,     2,     1,     3,     1,     3,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       3,     5,     0,     0,     0,   266,   298,   297,   263,   125,
     353,   349,   351,     0,    58,     0,   556,    18,     4,     7,
       9,     8,     0,     0,   210,   211,   212,   213,   202,   203,
     204,   205,   214,   215,   216,   217,   206,   207,   208,   209,
     117,   117,     0,   133,   140,   260,   262,   261,   131,   283,
     157,     0,     0,     0,   265,   264,     0,     6,    16,    17,
     354,   350,   352,     0,     0,     0,   348,   258,   281,     0,
     271,     0,   126,   138,   144,   128,   160,   127,   139,   145,
     161,   129,   150,   155,   132,   167,   130,   151,   156,   168,
     134,   136,   142,   141,   178,   135,   137,   143,   179,   146,
     148,   153,   152,   193,   147,   149,   154,   194,   158,   176,
     185,   164,   162,   159,   177,   186,   163,   165,   191,   200,
     171,   169,   166,   192,   201,   170,   172,   174,   183,   182,
     180,   173,   175,   184,   181,   187,   189,   198,   197,   195,
     188,   190,   199,   196,     0,     0,    15,   284,    31,    32,
     374,   365,   374,   366,   363,   367,    11,    85,    86,    87,
      56,    57,     0,     0,     0,     0,     0,    88,     0,    33,
      35,    34,     0,    36,    37,     0,    38,    39,     0,     0,
      40,    59,     0,     0,    61,    43,    45,     0,     0,   288,
       0,   238,   239,   240,   241,   234,   235,   236,   237,   398,
       0,   230,   231,   232,   233,   259,     0,     0,   282,    12,
     281,    30,     0,   281,   258,     0,   281,   347,   333,   258,
     281,     0,   269,     0,   327,   328,     0,     0,     0,     0,
     355,     0,   358,     0,   361,    54,    55,     0,     0,     0,
      49,    46,     0,   462,     0,     0,    48,     0,     0,     0,
      50,     0,    52,     0,     0,    78,    76,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     102,   103,     0,     0,    41,     0,     0,   458,   450,     0,
      47,   295,   296,   293,     0,   286,   289,   294,   267,   400,
     268,   346,     0,     0,   118,     0,   548,   344,   258,   259,
       0,     0,   470,   104,     0,   470,   109,     0,   280,     0,
       0,    14,   281,    22,     0,   281,   281,   331,    13,    26,
       0,   281,   381,   376,   230,   231,   232,   233,   226,   227,
     228,   229,   117,   117,   373,     0,   374,   281,   374,   395,
     396,   370,   393,     0,     0,     0,     0,    92,    91,     0,
      10,    44,     0,     0,    84,    83,     0,     0,     0,     0,
      72,    73,    71,    70,    69,    67,    68,    62,    63,    64,
      65,    66,   101,   100,     0,    42,     0,    94,     0,     0,
     451,   452,    93,     0,   288,    41,   258,   281,   399,   401,
     406,   405,   407,   415,   345,   272,   273,     0,     0,     0,
       0,     0,   417,     0,   445,    28,   111,   110,   107,   222,
     223,   218,   219,   224,   225,   220,   221,   117,   117,   278,
     332,     0,     0,   470,   277,   330,   470,   357,   378,     0,
     375,   382,     0,   360,     0,     0,   371,     0,   370,     0,
       0,     0,    89,    60,    51,    53,     0,     0,    77,    75,
      95,    99,   554,     0,   461,   430,   460,   470,   470,   470,
     470,     0,   439,     0,   448,   425,   434,   453,   285,   287,
      85,     0,   409,   524,   414,   281,   413,   274,     0,   552,
     532,   117,   117,   550,     0,   533,   535,   549,     0,     0,
       0,   418,   416,     0,   114,     0,   115,     0,     0,   329,
     270,   273,    20,   275,    24,     0,   281,   377,   383,     0,
     281,   379,   385,   281,   281,   397,   394,   281,     0,     0,
       0,     0,     0,    79,    82,   454,     0,   431,   426,   435,
     432,   427,   436,   448,   428,   437,   433,   429,   438,   440,
     447,    85,   266,     0,     0,     0,     0,     0,     0,   512,
     507,   457,   470,     0,   116,   117,   117,     0,     0,   446,
     494,   474,   475,     0,   290,     0,   292,   408,   410,     0,
       0,   524,   412,   530,   547,   402,   402,   526,   527,     0,
     551,     0,   419,   420,     0,    29,   455,     0,     0,   302,
     300,   299,   279,     0,     0,     0,   281,     0,   387,   281,
     281,     0,   390,   281,   356,   359,   364,   281,    96,     0,
      98,   315,     0,     0,   312,     0,   314,     0,   368,   305,
     311,     0,     0,     0,   555,   459,     0,   510,   497,   498,
     499,     0,     0,     0,   513,     0,     0,   495,     0,     0,
     123,   466,   480,   468,   485,     0,   478,     0,     0,   449,
     463,   124,     0,   411,   525,   338,   258,   281,   281,   334,
     335,   281,   544,   403,   406,   258,   281,   281,   546,   281,
     534,   210,   211,   212,   213,   202,   203,   204,   205,   214,
     215,   216,   217,   206,   207,   208,   209,   117,   117,   536,
     553,   456,   112,   113,     0,    21,   276,    25,   389,   281,
       0,   392,   281,     0,   362,     0,   318,     0,     0,   309,
      90,     0,   304,     0,   317,   308,    80,     0,   508,   500,
       0,   505,     0,   281,     0,   121,   321,     0,   122,   324,
       0,     0,   448,     0,     0,     0,   465,   470,   464,   484,
       0,   496,   291,   409,   524,   542,   281,   337,   281,   340,
     543,   404,   409,   524,   545,   528,   402,   402,     0,   388,
     384,   391,   386,    97,     0,   320,     0,     0,   306,   307,
       0,   506,     0,   511,   119,     0,   120,     0,     0,     0,
       0,   514,     0,   479,   448,   449,   471,   470,     0,   341,
     342,     0,   336,   339,     0,   281,   281,   539,   281,   541,
     301,     0,   313,   310,   509,   516,     0,   470,   470,     0,
       0,   469,   515,   493,   486,     0,   490,   477,   473,   472,
       0,   343,   529,   537,   538,   540,   319,     0,     0,     0,
     517,   518,   501,   322,   325,   467,   481,   514,   492,   448,
     483,     0,     0,   516,     0,     0,     0,     0,   448,     0,
     491,     0,     0,     0,   502,   519,   323,   326,   482,   487,
     520,     0,     0,     0,   514,     0,   522,     0,   503,     0,
       0,     0,     0,   488,   521,   504,   523,   448,   489,     0,
       0,     0
};

static const short yydefgoto[] =
{
     879,     1,     2,     3,    18,    19,    20,    21,   314,   593,
     320,   595,   215,   493,   615,   178,   244,   374,   180,   181,
     182,   183,    22,   184,   185,   359,   358,   356,   623,   357,
     186,   522,   302,   303,   304,   305,   408,   455,    23,   293,
     554,   191,   192,   193,   194,   195,   196,   197,   198,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,   481,
     482,   332,   205,   199,    42,   206,    43,    44,    45,    46,
      47,   221,    69,   216,   222,   594,    70,   498,   294,   208,
      49,   284,   285,   286,    50,   592,   694,   617,   618,   619,
     767,   620,   708,   621,   622,   725,   775,   846,   728,   777,
     847,   501,   224,   658,   659,   660,   225,    51,    52,    53,
      54,   336,   338,   343,   233,    55,   712,   437,   228,   229,
     334,   507,   511,   508,   512,   341,   342,   200,   289,   388,
     662,   663,   390,   391,   392,   217,   456,   457,   458,   459,
     460,   461,   306,   278,   625,   737,   741,   379,   380,   381,
     585,   559,   279,   463,   187,   586,   646,   647,   730,   648,
     732,   307,   785,   738,   786,   787,   649,   784,   731,   848,
     733,   837,   864,   877,   839,   814,   561,   562,   635,   815,
     829,   830,   831,   867,   474,   570,   483,   669,   794,   484,
     485,   689,   486,   575,   297,   398,   487,   488,   453,   188
};

static const short yypact[] =
{
      73,    94,  2813,  2813,   291,-32768,-32768,-32768,-32768,-32768,
      88,    88,    88,    35,-32768,    56,-32768,-32768,-32768,-32768,
  -32768,-32768,    70,    92,   612,  1168,  1296,  2041,  1008,   390,
    1300,   898,  1603,  2103,  1696,  2214,  1607,   958,  2010,  1329,
  -32768,-32768,   105,-32768,-32768,-32768,-32768,-32768,    88,-32768,
  -32768,    48,    50,    63,-32768,-32768,  2813,-32768,-32768,-32768,
      88,    88,    88,  2601,    90,  2496,-32768,    62,    88,   186,
  -32768,  1202,-32768,-32768,-32768,    88,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    88,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,    88,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    88,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    88,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
      88,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    88,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    88,-32768,
  -32768,-32768,-32768,-32768,   327,    92,-32768,-32768,-32768,-32768,
  -32768,    74,-32768,   119,-32768,   136,-32768,-32768,-32768,-32768,
  -32768,-32768,  2601,  2601,   134,   199,   202,-32768,   526,-32768,
  -32768,-32768,  2601,-32768,-32768,  1787,-32768,-32768,  2601,   164,
     190,-32768,  2641,  2706,-32768,  3219,   641,  1345,  2601,   952,
     207,   807,  2232,  1471,  3214,   615,   682,   741,   924,-32768,
     209,   100,   312,   147,   315,-32768,    92,    92,    88,-32768,
      88,-32768,   273,    88,   349,   894,    88,-32768,-32768,    62,
      88,   343,-32768,   939,   115,   356,   368,  2070,   279,   851,
  -32768,   281,-32768,   532,-32768,-32768,-32768,  2601,  2601,  2167,
  -32768,-32768,   302,-32768,   311,   317,-32768,   340,  2601,  1787,
  -32768,  1787,-32768,  2601,  2601,   410,-32768,-32768,  2601,  2601,
    2601,  2601,  2601,  2601,  2601,  2601,  2601,  2601,  2601,  2601,
  -32768,-32768,   526,   526,  2601,  2601,   350,-32768,   442,   407,
  -32768,-32768,-32768,-32768,    32,-32768,   322,-32768,-32768,   107,
  -32768,   356,   299,    92,-32768,   510,-32768,-32768,    62,   543,
    2110,   461,-32768,-32768,  1039,    43,-32768,   421,   488,   327,
     327,-32768,    88,-32768,   894,    88,    88,-32768,-32768,-32768,
     894,    88,-32768,-32768,   807,  2232,  1471,  3214,   615,   682,
     741,   924,-32768,   433,   483,  3095,-32768,    88,-32768,-32768,
     524,   484,-32768,   532,  2934,  2961,   487,-32768,-32768,  2364,
  -32768,  3219,   496,   535,  3219,  3219,  2601,   541,  2601,  2601,
    2462,  1857,  2395,  2892,   673,   503,   503,   481,   481,-32768,
  -32768,-32768,-32768,-32768,   546,   190,   501,-32768,   526,  1534,
     442,-32768,-32768,   547,   952,  2746,    62,    88,-32768,-32768,
  -32768,-32768,   498,-32768,-32768,-32768,   179,   551,  1234,  2601,
    2601,  2175,-32768,  2834,-32768,-32768,-32768,-32768,-32768,  2120,
     990,  1700,  1453,  3142,  1666,  2074,  1759,   552,   554,-32768,
     115,   375,   327,-32768,   601,-32768,-32768,-32768,   374,   193,
  -32768,-32768,   557,-32768,   560,  2601,   526,   561,   484,  2167,
    2601,  2167,-32768,-32768,   558,   558,   608,  2601,  3248,  2994,
  -32768,-32768,-32768,   373,   461,-32768,-32768,    71,    79,    80,
      81,   655,-32768,   567,  2250,-32768,-32768,-32768,-32768,-32768,
     165,   572,   107,   107,-32768,    88,-32768,-32768,   573,-32768,
  -32768,-32768,-32768,-32768,   574,   387,-32768,-32768,   168,  2861,
    2884,-32768,-32768,    44,-32768,   327,-32768,    92,  1935,-32768,
  -32768,   636,-32768,-32768,-32768,  2601,   203,   576,-32768,  2601,
     239,   578,-32768,    88,    88,  3219,-32768,    88,   577,   584,
    2982,   585,  1414,-32768,  3235,-32768,   526,-32768,-32768,-32768,
  -32768,-32768,-32768,  2324,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   629,   630,  2601,   632,   590,   596,  2536,   103,   679,
  -32768,-32768,-32768,   603,-32768,-32768,-32768,   604,   575,   600,
  -32768,-32768,-32768,  2431,-32768,  2601,-32768,-32768,-32768,   609,
    1116,-32768,-32768,-32768,-32768,   325,   301,-32768,-32768,  2716,
  -32768,   696,-32768,-32768,   605,-32768,-32768,   395,   396,-32768,
  -32768,  3219,-32768,    44,  1935,    44,  3085,  2601,-32768,    88,
    3085,  2601,-32768,    88,-32768,-32768,-32768,    88,-32768,  2601,
  -32768,-32768,   526,  2601,-32768,   664,  3219,   626,   625,-32768,
  -32768,   251,  1895,  2601,-32768,-32768,  3013,-32768,-32768,-32768,
  -32768,   631,  2601,   634,-32768,   653,   690,-32768,   327,    92,
  -32768,-32768,-32768,-32768,-32768,   670,   723,  1627,    77,-32768,
  -32768,-32768,   254,-32768,-32768,-32768,    62,    88,    88,   508,
     533,   142,-32768,-32768,    88,    62,    88,   142,-32768,    88,
  -32768,  2120,   990,  3154,  3185,  1700,  1453,  2470,  2316,  3142,
    1666,  3173,  3202,  2074,  1759,  2609,  2817,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,  1414,-32768,-32768,-32768,-32768,  3085,
     374,-32768,  3085,   193,-32768,  3034,-32768,  2804,  1414,-32768,
  -32768,  1827,-32768,  2002,-32768,-32768,  3235,  2601,-32768,-32768,
     651,-32768,  2601,    88,   398,-32768,   188,   404,-32768,   196,
     676,   685,-32768,   691,  2601,  1720,-32768,-32768,-32768,-32768,
    2601,-32768,-32768,   325,   307,-32768,    88,-32768,    88,-32768,
  -32768,    88,   301,   301,-32768,-32768,   325,   301,   669,-32768,
  -32768,-32768,-32768,-32768,  2601,-32768,   671,  2002,-32768,-32768,
    3201,-32768,    28,-32768,-32768,   894,-32768,   894,  2601,  2601,
     746,  2431,   677,-32768,-32768,-32768,-32768,-32768,   681,   508,
     533,   393,-32768,-32768,  1116,    88,   142,-32768,   142,-32768,
  -32768,  2911,-32768,-32768,-32768,    67,   678,-32768,-32768,   684,
     686,-32768,-32768,-32768,-32768,   687,-32768,-32768,-32768,-32768,
     689,-32768,-32768,-32768,-32768,-32768,-32768,   713,   526,    41,
     695,-32768,-32768,-32768,-32768,-32768,-32768,  2601,-32768,-32768,
  -32768,  2601,   688,    67,   693,    67,   605,   605,-32768,   701,
  -32768,   692,   782,    58,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   727,   786,   707,  2601,  2601,-32768,   319,-32768,   710,
     716,   717,   796,-32768,-32768,-32768,-32768,-32768,-32768,   809,
     816,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,    53,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    -5,-32768,   -63,   427,  -256,   422,
  -32768,-32768,-32768,    14,   819,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,  -301,-32768,   514,-32768,-32768,    -9,   305,  -250,
    -540,     1,     4,    23,    36,     9,    19,    27,    29,  -257,
    -252,   246,   247,  -246,  -238,   248,   258,  -431,  -430,   549,
     556,-32768,  -171,-32768,  -429,  -199,   420,   520,   812,   840,
  -32768,  -453,  -121,  -207,   417,-32768,   579,-32768,   318,    86,
     106,-32768,   469,-32768,   478,   260,-32768,  -608,-32768,   162,
  -32768,  -573,-32768,-32768,   253,-32768,-32768,-32768,-32768,-32768,
  -32768,  -116,   300,   125,   132,  -112,   -18,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   446,  -125,-32768,
     550,-32768,-32768,   197,   183,   553,   474,  -138,-32768,-32768,
    -535,  -275,  -396,  -455,-32768,   529,-32768,-32768,-32768,-32768,
  -32768,-32768,  -264,-32768,-32768,  -405,   130,-32768,-32768,   536,
    -350,-32768,   358,-32768,-32768,  -428,-32768,-32768,-32768,-32768,
  -32768,   224,   133,  -648,  -254,  -186,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -773,
      76,-32768,    82,-32768,   447,-32768,  -569,-32768,-32768,-32768,
  -32768,-32768,-32768,   444,  -308,-32768,-32768,-32768,-32768,     7
};


#define	YYLAST		3308


static const short yytable[] =
{
     179,   654,   190,    24,    24,    71,    25,    25,   425,    56,
      56,    28,    28,   423,   389,   300,   315,   568,   375,   426,
     309,    29,    29,   651,   226,    26,    26,   231,   223,    30,
      30,    31,    31,   555,   556,   557,   560,   245,    27,    27,
     406,   668,   587,   299,  -106,   584,   151,   153,   155,   715,
     413,   148,   149,   148,   149,   414,    57,    24,   333,   558,
      25,   415,   422,    56,   849,    28,   148,   149,   201,   416,
       9,   202,  -441,    -1,   805,    29,   567,   827,   739,    26,
    -442,  -443,  -444,    30,   780,    31,   758,   843,    48,    48,
     203,   869,    27,    15,    -2,    66,    60,    61,    62,   399,
     766,   346,    63,   204,   862,   560,   148,   149,    72,   156,
      75,   352,    84,   353,    93,   462,   102,   806,   111,    15,
     120,   383,   129,    64,   138,   465,   384,   227,   558,   375,
     844,    15,   555,   556,   557,   828,   817,    65,  -106,   551,
     769,   413,    48,   150,   740,   152,   414,   863,   687,   688,
      67,    48,   415,    48,   147,    81,   691,   189,   154,    68,
     416,   632,  -421,   240,   333,   386,   147,   147,   147,   230,
    -422,  -423,  -424,    15,   387,   214,   235,   236,    15,   664,
     664,   147,   316,   214,   283,   724,   241,   472,   291,   292,
     147,   850,   246,   466,   803,   146,    66,   539,   569,   147,
     858,   237,   280,   528,   531,   534,   537,   212,   147,   213,
     214,   432,   376,   434,   232,   201,   212,   147,   202,  -273,
     201,   797,   799,   202,   212,   822,   147,  -273,   340,   878,
     324,   234,  -273,   325,    15,   147,   335,   203,   328,   509,
    -273,   813,   203,   695,   147,   697,   213,   214,   329,   597,
     204,    67,   326,   247,   564,   204,   330,   580,   331,   565,
      68,    48,   581,   213,   214,   327,   238,   372,   373,   239,
      15,   529,   532,   535,   538,   396,   209,    75,  -273,    84,
     210,    93,  -273,   102,   248,   601,  -273,    75,   568,    84,
    -273,   291,   292,   446,   315,   713,   288,   568,   290,   201,
      48,   519,   202,   521,    66,    48,   213,   214,   409,   652,
      66,   410,   506,   413,   147,    48,   411,   612,   414,   613,
      77,   203,   679,    86,   415,    48,   412,   680,    66,   655,
      66,   218,   416,   683,   204,    48,   324,    48,   340,   325,
     295,   684,   335,   742,   328,   144,   145,   567,   248,   700,
     555,   556,   557,   703,   329,   298,   567,     9,   326,   665,
     664,   664,   330,   443,   331,   656,   213,   214,   666,   214,
     321,   327,   337,   452,   657,   214,   588,    66,   218,   283,
      15,    58,    59,   656,    48,   219,   207,   201,   394,   385,
     202,   347,   657,   214,   220,     6,     7,     8,    95,   409,
     348,   553,   410,    10,    11,    12,   349,   411,   871,   203,
      75,   510,    84,   872,    93,   241,   102,   412,   856,   857,
     505,    48,   204,   213,   214,     5,     6,     7,     8,     9,
     350,   340,   219,   311,    10,    11,    12,   312,   792,   377,
     793,   220,   316,   214,    73,    78,    82,    87,   527,   530,
      14,   536,   109,   114,   118,   123,   -81,   743,   318,   552,
     748,   214,   210,   525,   499,    24,   752,   526,    25,   569,
     553,   563,    48,    28,   807,   378,   808,   578,   569,   396,
    -247,   579,   821,    29,   631,   692,   693,    26,   774,   312,
     210,    30,   312,    31,   776,    75,   382,    93,   210,   111,
      27,   129,    76,    80,    85,    89,    94,    98,   103,   107,
     112,   116,   121,   125,   130,   134,   139,   143,   727,   315,
     397,   624,   726,  -380,  -380,    48,   405,    48,   552,   148,
     149,   296,   419,   339,   308,   148,   149,   413,   310,   267,
     268,   269,   414,   633,    74,    79,    83,    88,   415,   400,
      48,   404,   110,   115,   119,   124,   416,   661,   667,   265,
     266,   267,   268,   269,    24,   475,   214,    25,   435,   720,
     563,   409,    28,   430,   410,   746,   214,   280,   436,   411,
     671,   441,    29,   672,   506,   444,    26,   447,   675,   412,
      30,   641,    31,   642,   643,   644,   645,   451,   676,    27,
     748,   214,   673,   464,   250,   252,   677,   706,   678,   420,
     421,    73,    78,    82,    87,   674,     5,     6,     7,     8,
      72,   729,     8,    90,   445,    10,    11,    12,    10,    11,
      12,   790,   791,   424,   296,   450,   468,   428,   429,   427,
     477,    14,   494,    15,   496,   503,    15,   502,   513,    48,
     504,   514,   517,   442,   523,   433,   301,   201,   540,   772,
     202,   566,   573,   577,   212,    48,   201,   287,   607,   202,
     599,   782,   603,   608,   610,   -31,   -32,   788,   627,   203,
     628,   464,   464,   533,   464,   510,   629,   634,   203,     8,
      95,   277,   204,   637,   640,    10,    11,    12,   653,   690,
     551,   204,  -242,   270,   271,   473,   272,   273,   274,   275,
     709,    74,    79,    83,    88,   809,   810,   710,   812,   711,
     722,   719,   495,   497,   721,   291,   292,   263,   264,   265,
     266,   267,   268,   269,   291,   292,   723,   734,   796,   798,
     735,   771,    48,   778,    73,    78,    82,    87,     8,    99,
     751,    48,   779,   317,    10,    11,    12,    75,   781,    84,
     800,    93,   802,   102,   811,   111,   816,   120,   832,   129,
     820,   138,    15,   835,   812,   836,   636,   838,   851,   840,
     841,   860,    24,   854,   852,    25,   574,   574,   563,   845,
      28,   859,   861,   571,   865,   409,   866,   868,   410,   873,
      29,   812,   870,   411,    26,   874,   876,   875,    30,   880,
      31,     5,   471,   412,     8,    72,   881,    27,   393,   407,
      10,    11,    12,   842,   598,   681,   682,   685,   602,    73,
      78,   604,   605,   109,   114,   606,    14,   686,    15,   500,
      91,    96,   100,   105,    74,    79,    83,    88,   127,   132,
     136,   141,   322,   469,   696,     5,   417,   147,     8,     9,
     638,   639,   287,   418,    10,    11,    12,    48,    92,    97,
     101,   106,   395,   768,   714,   789,   128,   133,   137,   142,
      14,   795,    15,    16,   518,   431,   762,    76,    80,    94,
      98,   112,   116,   130,   134,   301,   438,   760,  -470,  -470,
    -470,  -470,  -470,     6,     7,     8,   104,  -470,  -470,  -470,
     516,    10,    11,    12,   698,   818,   467,   650,   701,   853,
     819,   476,   572,  -470,     0,   704,   576,   855,     0,    74,
      79,     8,   104,   110,   115,     0,     0,    10,    11,    12,
     313,   323,  -372,   -19,   -19,   -19,   -19,   -19,     0,   317,
     317,     0,   -19,   -19,   -19,   148,   149,     6,     7,   281,
     282,   533,     0,     6,     7,     8,   131,   212,   -19,     0,
    -273,    10,    11,    12,     0,   744,   745,     0,     0,   750,
       0,     0,     0,  -273,   753,   754,     0,   755,  -249,  -105,
       0,     0,   756,   757,     5,     6,     7,     8,    77,     0,
       0,   393,   393,    10,    11,    12,     0,    91,    96,   100,
     105,   533,     0,     6,     7,     8,    90,   759,     0,    14,
     761,    10,    11,    12,     0,     0,     0,     0,     0,  -273,
       0,   833,   834,  -273,   -19,    92,    97,   101,   106,    15,
     301,   773,     0,  -108,  -108,  -108,  -108,  -108,  -255,     0,
       0,     0,  -108,  -108,  -108,     0,   344,   345,     0,     0,
       0,     0,     0,     0,   296,     0,   296,   351,  -108,     0,
       0,     0,   354,   355,     0,     0,     0,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,     0,
       0,    73,    78,    82,    87,     0,     0,     0,  -246,   109,
     114,   118,   123,     0,   393,   393,     0,     0,     0,     0,
       0,     0,     0,   823,   824,     0,   825,   478,     0,   403,
       5,     6,     7,     8,     9,     0,     0,   480,     0,    10,
      11,    12,     0,     0,  -108,     0,     0,     0,     0,     0,
      91,    96,   100,   105,     0,    14,     0,     0,     0,    76,
      80,    85,    89,    94,    98,   103,   107,   112,   116,   121,
     125,   130,   134,   139,   143,     0,     0,     0,    92,    97,
     101,   106,     5,     6,     7,     8,    77,   448,   449,     0,
       0,    10,    11,    12,     0,     0,     0,     0,   747,   749,
       0,    74,    79,    83,    88,     0,     0,    14,     0,   110,
     115,   119,   124,   211,     0,  -531,   -27,   -27,   -27,   -27,
     -27,     0,     0,     0,     0,   -27,   -27,   -27,   489,   490,
       0,     0,     0,    91,    96,     0,     0,   127,   132,     0,
     212,   -27,     0,  -273,     0,   478,     0,   479,     5,     6,
       7,     8,     9,     0,     0,   480,  -273,    10,    11,    12,
       0,    92,    97,     0,   515,   128,   133,     0,  -243,   520,
       0,     0,     0,    14,     0,     0,   524,     0,     0,   213,
     214,     0,   393,   393,     0,     0,     0,     0,     0,     0,
       0,   393,   393,     0,     0,   393,   393,     0,     0,     0,
       0,     0,  -273,     0,     0,     0,  -273,   -27,     0,     0,
       5,     6,     7,     8,    81,     6,     7,     8,    99,    10,
      11,    12,     0,    10,    11,    12,     0,   591,   747,   749,
     749,     0,     0,  -531,   596,    14,     0,    15,   600,     0,
       0,    15,     0,     0,     6,     7,     8,   140,     0,     0,
       0,   616,    10,    11,    12,     0,   276,     0,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,  -446,     0,  -446,  -446,  -446,
    -446,  -446,   626,  -446,  -446,  -446,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,  -446,     0,     0,  -244,  -446,     0,     0,
    -248,     0,     0,  -446,     0,     0,  -446,     0,     0,     0,
       0,  -446,  -446,  -446,     0,     0,     0,  -446,  -446,     0,
       0,     0,  -446,   591,     0,   611,   699,   541,   149,  -257,
     702,     0,     0,   158,   159,     0,   160,     0,   705,     0,
       0,     0,   707,     0,     0,  -446,   277,  -446,  -446,     0,
    -446,   616,   716,     0,   161,     0,    16,     0,   162,   163,
     164,   165,   166,     0,     0,     0,   167,     0,     6,     7,
       8,    95,   168,     0,     0,   169,    10,    11,    12,     0,
     170,   171,   172,     0,     0,     5,   173,   174,     8,    81,
     612,   175,   613,     0,    10,    11,    12,    91,    96,   100,
     105,     0,     0,     0,     0,   127,   132,   136,   141,     0,
      14,     0,    15,     0,     0,  -303,   176,   177,     0,   614,
       0,     0,     0,   616,     0,    92,    97,   101,   106,     0,
       0,     0,     0,   128,   133,   137,   142,   616,     0,     0,
     616,     0,   616,     0,     0,   454,   770,  -470,  -470,  -470,
    -470,  -470,  -470,  -470,  -470,     0,  -470,  -470,  -470,  -470,
    -470,     0,  -470,  -470,  -470,  -470,  -470,  -470,  -470,  -470,
    -470,  -470,  -470,  -470,  -470,  -470,  -470,     0,  -470,  -470,
    -470,  -470,  -470,     0,     0,     0,  -470,     0,     0,     0,
       0,     0,  -470,   801,     0,  -470,   616,     0,     0,     0,
    -470,  -470,  -470,     0,     0,     0,  -470,  -470,     0,     0,
       0,  -470,     0,     0,     0,     0,     0,     5,     6,     7,
       8,   108,     6,     7,     8,   126,    10,    11,    12,     0,
      10,    11,    12,     0,  -470,     0,  -470,  -470,   736,  -470,
    -448,  -448,    14,     0,    15,     0,  -448,  -448,    15,  -448,
       0,     0,     0,  -448,     0,  -448,  -448,  -448,  -448,  -448,
    -448,  -448,  -448,  -448,  -448,  -448,     0,  -448,     0,  -448,
       0,  -448,  -448,  -448,  -448,  -448,     0,     0,     0,  -448,
       5,     6,     7,     8,   113,  -448,     0,     0,  -448,    10,
      11,    12,     0,  -448,  -448,  -448,     0,     0,     0,  -448,
    -448,     0,     0,  -250,  -448,    14,     0,  -254,     0,     0,
       5,     6,     7,     8,   117,     6,     7,     8,    90,    10,
      11,    12,     0,    10,    11,    12,     0,  -448,     0,  -448,
    -448,   783,  -448,  -476,  -476,    14,     0,    15,     0,  -476,
    -476,    15,  -476,     0,     0,     0,  -476,     0,  -476,  -476,
    -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,  -476,     0,
    -476,     0,  -476,     0,  -476,  -476,  -476,  -476,  -476,     0,
       0,     0,  -476,     0,     6,     7,     8,   131,  -476,     0,
       0,  -476,    10,    11,    12,     0,  -476,  -476,  -476,     0,
       0,     0,  -476,  -476,     0,     0,  -252,  -476,   242,     0,
     157,     5,     0,     0,     8,     9,   158,   159,     0,   160,
      10,    11,    12,     0,     0,     0,     0,     0,     0,     0,
    -476,     0,  -476,  -476,     0,  -476,    14,   161,    15,    16,
       0,   162,   163,   164,   165,   166,     0,     0,   611,   167,
     541,   149,     0,     0,     0,   168,   158,   159,   169,   160,
       0,     0,     0,   170,   171,   172,     0,     0,     0,   173,
     174,     0,     0,     0,   175,     0,     0,   161,     0,    16,
       0,   162,   163,   164,   165,   166,     0,     0,     0,   167,
       0,     0,     0,     0,     0,   168,     0,     0,   169,   176,
     177,     0,   243,   170,   171,   172,     0,     0,     0,   173,
     174,     0,     0,   612,   175,   613,   611,     0,   157,     0,
       0,     0,     0,     0,   158,   159,     0,   160,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,  -369,   176,
     177,     0,   614,     0,     0,   161,     0,    16,     0,   162,
     163,   164,   165,   166,     0,     0,   589,   167,   157,  -316,
       0,     0,     0,   168,   158,   159,   169,   160,     0,     0,
       0,   170,   171,   172,     0,     0,     0,   173,   174,     0,
       0,  -316,   175,  -316,     0,   161,     0,    16,     0,   162,
     163,   164,   165,   166,     0,     0,     0,   167,     0,     0,
       0,     0,     0,   168,     0,     0,   169,   176,   177,     0,
     614,   170,   171,   172,     0,     0,     0,   173,   174,     0,
       0,     0,   175,   611,     0,   157,     0,     0,     0,     0,
       0,   158,   159,     0,   160,     6,     7,     8,   135,     0,
       0,     0,     0,    10,    11,    12,     0,   176,   177,     0,
     590,     0,   161,     0,    16,     0,   162,   163,   164,   165,
     166,    15,     0,     0,   167,     5,     6,     7,     8,    86,
     168,     0,     0,   169,    10,    11,    12,     0,   170,   171,
     172,     0,     0,     0,   173,   174,     0,     0,     0,   175,
      14,   319,     0,     0,   -23,   -23,   -23,   -23,   -23,     6,
       7,     8,   126,   -23,   -23,   -23,     0,    10,    11,    12,
       0,     0,     0,     0,   176,   177,     0,   614,   212,   -23,
    -256,  -273,     0,     0,     0,    15,     0,     5,     6,     7,
       8,   113,     0,   157,  -273,     0,    10,    11,    12,   158,
     159,     0,   160,     0,     5,     6,     7,     8,    72,     0,
       0,  -245,    14,    10,    11,    12,     0,   213,   214,     0,
     161,     0,    16,     0,   162,   163,   164,   165,   166,    14,
       0,    15,   167,     0,     0,     0,     0,     0,   168,     0,
    -273,   169,     0,     0,  -273,   -23,   170,   171,   401,     0,
       0,     5,   173,   174,     8,     9,     0,   175,   157,     0,
      10,    11,    12,     0,   158,   159,     0,   160,     0,     0,
       0,     0,     0,  -251,     0,     0,    14,     0,    15,     0,
       0,     0,   176,   177,     0,   161,   402,    16,     0,   162,
     163,   164,   165,   166,     0,     0,     0,   167,     5,     6,
       7,     8,   122,   168,     0,     0,   169,    10,    11,    12,
       0,   170,   171,   172,     0,     0,     5,   173,   174,     8,
      77,     0,   175,    14,     0,    10,    11,    12,     0,     0,
       0,     0,     0,   541,   542,     6,     7,     8,     9,   158,
     159,    14,   160,    10,    11,    12,     0,   176,   177,     0,
       0,   491,   543,   544,   545,   546,   547,   548,   549,    14,
     161,    15,    16,     0,   162,   163,   164,   165,   166,     0,
       0,     0,   167,     0,     0,     0,     0,     0,   168,     0,
       0,   169,     0,     0,  -253,     0,   170,   171,   172,     0,
       0,     0,   173,   174,     0,     0,     0,   175,     0,     0,
       0,     6,     7,     8,   104,     0,     0,   541,   149,    10,
      11,    12,     0,   158,   159,     0,   160,     0,     0,     0,
     550,     0,   176,   177,     0,   551,   543,   544,   545,   546,
     547,   548,   549,     0,   161,     0,    16,     0,   162,   163,
     164,   165,   166,     0,     0,     0,   167,   157,     0,     0,
       0,     0,   168,   158,   159,   169,   160,     0,     0,     0,
     170,   171,   172,     0,     0,     0,   173,   174,     0,     0,
       0,   175,     0,     0,   161,     0,    16,     0,   162,   163,
     164,   165,   166,     0,     0,     0,   167,     0,     0,     0,
       0,     0,   168,     0,   550,   169,   176,   177,     0,   551,
     170,   171,   172,     0,     0,     0,   173,   174,     0,     0,
       0,   175,     0,     0,   157,     5,     6,     7,     8,     9,
     158,   159,     0,   160,    10,    11,    12,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   176,   177,     0,   442,
      14,   161,    15,    16,     0,   162,   163,   164,   165,   166,
       0,     0,     0,   167,     0,     6,     7,     8,    99,   168,
       0,     0,   169,    10,    11,    12,     0,   170,   171,   172,
       0,     0,     0,   173,   174,     0,     0,     0,   175,   157,
       5,    15,     0,     8,     9,   158,   159,     0,   160,    10,
      11,    12,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   176,   177,    14,   161,    15,    16,     0,
     162,   163,   164,   165,   166,     0,     0,     0,   167,   157,
       0,     0,     0,     0,   168,   158,   159,   169,   160,     0,
       0,     0,   170,   171,   172,     0,     0,     0,   173,   174,
       0,     0,     0,   175,     0,     0,   161,     0,    16,     0,
     162,   163,   164,   165,   166,     0,     0,     0,   167,     0,
       0,     0,     0,     0,   168,     0,     0,   169,   176,   177,
       0,     0,   170,   171,   172,     0,     0,     0,   173,   174,
       0,     0,     0,   175,   157,     0,     0,     0,     0,     0,
     158,   159,     0,   160,     6,     7,     8,   135,     0,     0,
       0,     0,    10,    11,    12,     0,   630,     0,   176,   177,
       0,   161,     0,    16,     0,   162,   163,   164,   165,   166,
      15,     0,     0,   167,   157,     0,     0,     0,     0,   168,
     158,   159,   169,   160,     0,     0,     0,   170,   171,   172,
       0,     0,     0,   173,   174,     0,     0,     0,   175,     0,
       0,   161,     0,    16,     0,   162,   163,   164,   165,   166,
       0,     0,     0,   167,     0,     0,     0,     0,     0,   168,
       0,     0,   169,   176,   177,     0,     0,   170,   171,   172,
       0,     0,     0,   173,   174,     0,     0,     0,   249,   157,
       0,     0,     0,     0,     0,   158,   159,     0,   160,     0,
       5,     6,     7,     8,     9,     0,     0,   670,     0,    10,
      11,    12,     0,   176,   177,     0,   161,     0,    16,     0,
     162,   163,   164,   165,   166,    14,     0,    15,   167,   470,
       0,     0,     0,     0,   168,   158,   159,   169,   160,     0,
       0,     0,   170,   171,   172,     0,     0,     0,   173,   174,
       0,     0,     0,   251,     0,     0,   161,     0,    16,     0,
     162,   163,   164,   165,   166,     0,     0,     0,   167,     0,
       0,     0,     0,     0,   168,     0,     0,   169,   176,   177,
       0,     0,   170,   171,   172,     0,     0,     0,   173,   174,
       0,     0,     0,   175,     4,   764,  -117,     5,     6,     7,
       8,     9,     6,     7,     8,   140,    10,    11,    12,     0,
      10,    11,    12,     0,     0,     0,     0,     0,   176,   177,
       0,    13,    14,     0,    15,    16,     0,   253,   254,   255,
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,     0,     0,     0,     0,     0,
       0,  -117,     0,     0,     0,     0,     0,   253,   254,   255,
    -117,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,     0,     0,     0,     0,     0,
     765,     0,     0,    17,   253,   254,   255,     0,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,     0,     0,     0,     0,     0,   253,   254,   255,
     492,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   262,   263,   264,   265,   266,
     267,   268,   269,     0,   253,   254,   255,   582,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,     0,     0,     0,     0,     0,   253,   254,   255,
     583,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   253,   254,   255,   826,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,     0,     0,   717,   253,   254,   255,   439,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   440,   253,   254,   255,   718,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,     0,     0,   609,   253,   254,   255,
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,     0,   322,     0,     0,     5,
       0,     0,     8,     9,     0,     0,     0,     0,    10,    11,
      12,     0,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,     0,   763,    14,     0,    15,    16,   253,   254,
     255,     0,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,     5,     6,     7,     8,
     108,     0,     0,     0,     0,    10,    11,    12,     5,     6,
       7,     8,    81,     0,     0,     0,     0,    10,    11,    12,
       0,    14,     0,    15,     0,     0,     0,     5,     6,     7,
       8,   117,     0,    14,     0,    15,    10,    11,    12,     5,
       6,     7,     8,    86,     0,     0,     0,     0,    10,    11,
      12,     0,    14,     0,    15,     0,     5,     6,     7,     8,
     122,     0,     0,     0,    14,    10,    11,    12,     5,     0,
       0,     8,    86,     0,     0,     0,     0,    10,    11,    12,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,   253,   254,   255,   804,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   253,   254,   255,     0,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     255,     0,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269
};

static const short yycheck[] =
{
      63,   570,    65,     2,     3,    23,     2,     3,   316,     2,
       3,     2,     3,   314,   289,   214,   223,   472,   274,   320,
     219,     2,     3,   563,   145,     2,     3,   152,   144,     2,
       3,     2,     3,   464,   464,   464,   464,   175,     2,     3,
     304,   576,   495,   214,     1,     1,    51,    52,    53,   622,
     307,     3,     4,     3,     4,   307,     3,    56,   229,   464,
      56,   307,   312,    56,   837,    56,     3,     4,    67,   307,
       8,    67,     1,     0,    46,    56,   472,    10,     1,    56,
       1,     1,     1,    56,   732,    56,   694,    46,     2,     3,
      67,   864,    56,    31,     0,     3,    10,    11,    12,   298,
     708,   239,    67,    67,    46,   533,     3,     4,     8,    56,
      24,   249,    26,   251,    28,   379,    30,    89,    32,    31,
      34,    89,    36,    67,    38,   379,    94,   145,   533,   385,
      89,    31,   563,   563,   563,    68,   784,    67,    95,    95,
     713,   398,    56,    95,    67,    95,   398,    89,   579,   579,
      58,    65,   398,    67,    48,     8,   584,    67,    95,    67,
     398,    58,    91,   168,   335,    58,    60,    61,    62,    95,
      91,    91,    91,    31,    67,    68,   162,   163,    31,   575,
     576,    75,    67,    68,   189,   638,   172,   386,   206,   207,
      84,   839,   178,   379,   767,    90,     3,   461,   473,    93,
     848,    67,   188,   457,   458,   459,   460,    28,   102,    67,
      68,   336,   275,   338,    95,   214,    28,   111,   214,    31,
     219,   756,   757,   219,    28,   794,   120,    31,   233,   877,
     229,    95,    44,   229,    31,   129,   229,   214,   229,    46,
      44,   781,   219,   593,   138,   595,    67,    68,   229,    46,
     214,    58,   229,    89,    89,   219,   229,    89,   229,    94,
      67,   175,    94,    67,    68,   229,    67,   272,   273,    67,
      31,   457,   458,   459,   460,   293,    90,   191,    90,   193,
      94,   195,    94,   197,    94,    46,    90,   201,   743,   203,
      94,   309,   310,   356,   501,    44,    89,   752,    89,   298,
     214,   439,   298,   441,     3,   219,    67,    68,   307,   565,
       3,   307,   428,   570,   208,   229,   307,    66,   570,    68,
       8,   298,   579,     8,   570,   239,   307,   579,     3,     4,
       3,     4,   570,   579,   298,   249,   335,   251,   343,   335,
      67,   579,   335,    89,   335,    40,    41,   743,    94,   599,
     781,   781,   781,   603,   335,     6,   752,     8,   335,    58,
     756,   757,   335,   349,   335,    58,    67,    68,    67,    68,
      91,   335,    91,   378,    67,    68,   497,     3,     4,   384,
      31,    90,    91,    58,   298,    58,    68,   386,    89,    67,
     386,    89,    67,    68,    67,     5,     6,     7,     8,   398,
      89,   464,   398,    13,    14,    15,    89,   398,    89,   386,
     324,   429,   326,    94,   328,   401,   330,   398,   846,   847,
      46,   335,   386,    67,    68,     4,     5,     6,     7,     8,
      90,   436,    58,    90,    13,    14,    15,    94,   746,    89,
     748,    67,    67,    68,    24,    25,    26,    27,   457,   458,
      29,   460,    32,    33,    34,    35,    46,   656,    90,   464,
      67,    68,    94,    90,    89,   464,   665,    94,   464,   744,
     533,   464,   386,   464,   775,    33,   777,    90,   753,   497,
      90,    94,    89,   464,   547,    90,    90,   464,    90,    94,
      94,   464,    94,   464,    90,   409,    89,   411,    94,   413,
     464,   415,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,   639,   726,
      10,   526,   638,    90,    91,   439,   302,   441,   533,     3,
       4,   213,    44,     1,   216,     3,     4,   794,   220,    58,
      59,    60,   794,   548,    24,    25,    26,    27,   794,     6,
     464,    90,    32,    33,    34,    35,   794,   575,   576,    56,
      57,    58,    59,    60,   563,    67,    68,   563,    44,   632,
     563,   570,   563,    90,   570,    67,    68,   563,    94,   570,
     579,    94,   563,   579,   700,    89,   563,    46,   579,   570,
     563,    16,   563,    18,    19,    20,    21,    96,   579,   563,
      67,    68,   579,   379,   182,   183,   579,   612,   579,   309,
     310,   191,   192,   193,   194,   579,     4,     5,     6,     7,
       8,   639,     7,     8,    89,    13,    14,    15,    13,    14,
      15,   743,   744,   315,   316,    89,    89,   332,   333,   321,
      89,    29,    90,    31,    90,    44,    31,   423,    91,   563,
     426,    91,    91,    95,    46,   337,     1,   656,    91,   722,
     656,    89,    89,    89,    28,   579,   665,   189,    91,   665,
      94,   734,    94,    89,    89,    46,    46,   740,    46,   656,
      90,   457,   458,   459,   460,   703,    90,     8,   665,     7,
       8,    91,   656,    90,    90,    13,    14,    15,    89,     3,
      95,   665,    90,    62,    63,   387,    65,    66,    67,    68,
      46,   191,   192,   193,   194,   778,   779,    91,   781,    94,
      67,    90,   417,   418,    90,   743,   744,    54,    55,    56,
      57,    58,    59,    60,   752,   753,    46,    67,   756,   757,
      17,    90,   656,    67,   324,   325,   326,   327,     7,     8,
     664,   665,    67,   224,    13,    14,    15,   671,    67,   673,
      91,   675,    91,   677,    18,   679,    89,   681,    90,   683,
      89,   685,    31,    89,   837,    89,   552,    90,   841,    90,
      67,    89,   781,    90,    96,   781,   481,   482,   781,    94,
     781,    90,    10,   475,    67,   794,    10,    90,   794,    89,
     781,   864,   865,   794,   781,    89,    10,    90,   781,     0,
     781,     4,   385,   794,     7,     8,     0,   781,   289,   305,
      13,    14,    15,   828,   506,   579,   579,   579,   510,   409,
     410,   513,   514,   413,   414,   517,    29,   579,    31,   422,
      28,    29,    30,    31,   324,   325,   326,   327,    36,    37,
      38,    39,     1,   384,   594,     4,   307,   751,     7,     8,
     555,   556,   384,   307,    13,    14,    15,   781,    28,    29,
      30,    31,   293,   711,   621,   743,    36,    37,    38,    39,
      29,   756,    31,    32,   438,   335,   703,   409,   410,   411,
     412,   413,   414,   415,   416,     1,   343,   700,     4,     5,
       6,     7,     8,     5,     6,     7,     8,    13,    14,    15,
     436,    13,    14,    15,   596,   785,   380,   559,   600,   843,
     787,   392,   475,    29,    -1,   607,   482,   845,    -1,   409,
     410,     7,     8,   413,   414,    -1,    -1,    13,    14,    15,
       1,    90,    91,     4,     5,     6,     7,     8,    -1,   420,
     421,    -1,    13,    14,    15,     3,     4,     5,     6,     7,
       8,   737,    -1,     5,     6,     7,     8,    28,    29,    -1,
      31,    13,    14,    15,    -1,   657,   658,    -1,    -1,   661,
      -1,    -1,    -1,    44,   666,   667,    -1,   669,    90,    95,
      -1,    -1,   687,   688,     4,     5,     6,     7,     8,    -1,
      -1,   472,   473,    13,    14,    15,    -1,   195,   196,   197,
     198,   787,    -1,     5,     6,     7,     8,   699,    -1,    29,
     702,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    90,
      -1,   807,   808,    94,    95,   195,   196,   197,   198,    31,
       1,   723,    -1,     4,     5,     6,     7,     8,    90,    -1,
      -1,    -1,    13,    14,    15,    -1,   237,   238,    -1,    -1,
      -1,    -1,    -1,    -1,   746,    -1,   748,   248,    29,    -1,
      -1,    -1,   253,   254,    -1,    -1,    -1,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,    -1,
      -1,   671,   672,   673,   674,    -1,    -1,    -1,    90,   679,
     680,   681,   682,    -1,   575,   576,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   795,   796,    -1,   798,     1,    -1,   300,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    13,
      14,    15,    -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,
     328,   329,   330,   331,    -1,    29,    -1,    -1,    -1,   671,
     672,   673,   674,   675,   676,   677,   678,   679,   680,   681,
     682,   683,   684,   685,   686,    -1,    -1,    -1,   328,   329,
     330,   331,     4,     5,     6,     7,     8,   358,   359,    -1,
      -1,    13,    14,    15,    -1,    -1,    -1,    -1,   659,   660,
      -1,   671,   672,   673,   674,    -1,    -1,    29,    -1,   679,
     680,   681,   682,     1,    -1,    89,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,   399,   400,
      -1,    -1,    -1,   411,   412,    -1,    -1,   415,   416,    -1,
      28,    29,    -1,    31,    -1,     1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    44,    13,    14,    15,
      -1,   411,   412,    -1,   435,   415,   416,    -1,    90,   440,
      -1,    -1,    -1,    29,    -1,    -1,   447,    -1,    -1,    67,
      68,    -1,   743,   744,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   752,   753,    -1,    -1,   756,   757,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    94,    95,    -1,    -1,
       4,     5,     6,     7,     8,     5,     6,     7,     8,    13,
      14,    15,    -1,    13,    14,    15,    -1,   498,   789,   790,
     791,    -1,    -1,    89,   505,    29,    -1,    31,   509,    -1,
      -1,    31,    -1,    -1,     5,     6,     7,     8,    -1,    -1,
      -1,   522,    13,    14,    15,    -1,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,   543,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    90,    42,    -1,    -1,
      90,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,   594,    -1,     1,   597,     3,     4,    90,
     601,    -1,    -1,     9,    10,    -1,    12,    -1,   609,    -1,
      -1,    -1,   613,    -1,    -1,    90,    91,    92,    93,    -1,
      95,   622,   623,    -1,    30,    -1,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    42,    -1,     5,     6,
       7,     8,    48,    -1,    -1,    51,    13,    14,    15,    -1,
      56,    57,    58,    -1,    -1,     4,    62,    63,     7,     8,
      66,    67,    68,    -1,    13,    14,    15,   675,   676,   677,
     678,    -1,    -1,    -1,    -1,   683,   684,   685,   686,    -1,
      29,    -1,    31,    -1,    -1,    91,    92,    93,    -1,    95,
      -1,    -1,    -1,   694,    -1,   675,   676,   677,   678,    -1,
      -1,    -1,    -1,   683,   684,   685,   686,   708,    -1,    -1,
     711,    -1,   713,    -1,    -1,     1,   717,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    48,   764,    -1,    51,   767,    -1,    -1,    -1,
      56,    57,    58,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,     8,     5,     6,     7,     8,    13,    14,    15,    -1,
      13,    14,    15,    -1,    90,    -1,    92,    93,     1,    95,
       3,     4,    29,    -1,    31,    -1,     9,    10,    31,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    32,
      -1,    34,    35,    36,    37,    38,    -1,    -1,    -1,    42,
       4,     5,     6,     7,     8,    48,    -1,    -1,    51,    13,
      14,    15,    -1,    56,    57,    58,    -1,    -1,    -1,    62,
      63,    -1,    -1,    90,    67,    29,    -1,    90,    -1,    -1,
       4,     5,     6,     7,     8,     5,     6,     7,     8,    13,
      14,    15,    -1,    13,    14,    15,    -1,    90,    -1,    92,
      93,     1,    95,     3,     4,    29,    -1,    31,    -1,     9,
      10,    31,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      30,    -1,    32,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    42,    -1,     5,     6,     7,     8,    48,    -1,
      -1,    51,    13,    14,    15,    -1,    56,    57,    58,    -1,
      -1,    -1,    62,    63,    -1,    -1,    90,    67,     1,    -1,
       3,     4,    -1,    -1,     7,     8,     9,    10,    -1,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    92,    93,    -1,    95,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    -1,    -1,     1,    42,
       3,     4,    -1,    -1,    -1,    48,     9,    10,    51,    12,
      -1,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,
      63,    -1,    -1,    -1,    67,    -1,    -1,    30,    -1,    32,
      -1,    34,    35,    36,    37,    38,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    92,
      93,    -1,    95,    56,    57,    58,    -1,    -1,    -1,    62,
      63,    -1,    -1,    66,    67,    68,     1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,     9,    10,    -1,    12,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    91,    92,
      93,    -1,    95,    -1,    -1,    30,    -1,    32,    -1,    34,
      35,    36,    37,    38,    -1,    -1,     1,    42,     3,    44,
      -1,    -1,    -1,    48,     9,    10,    51,    12,    -1,    -1,
      -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,    -1,
      -1,    66,    67,    68,    -1,    30,    -1,    32,    -1,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    51,    92,    93,    -1,
      95,    56,    57,    58,    -1,    -1,    -1,    62,    63,    -1,
      -1,    -1,    67,     1,    -1,     3,    -1,    -1,    -1,    -1,
      -1,     9,    10,    -1,    12,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    13,    14,    15,    -1,    92,    93,    -1,
      95,    -1,    30,    -1,    32,    -1,    34,    35,    36,    37,
      38,    31,    -1,    -1,    42,     4,     5,     6,     7,     8,
      48,    -1,    -1,    51,    13,    14,    15,    -1,    56,    57,
      58,    -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,
      29,     1,    -1,    -1,     4,     5,     6,     7,     8,     5,
       6,     7,     8,    13,    14,    15,    -1,    13,    14,    15,
      -1,    -1,    -1,    -1,    92,    93,    -1,    95,    28,    29,
      90,    31,    -1,    -1,    -1,    31,    -1,     4,     5,     6,
       7,     8,    -1,     3,    44,    -1,    13,    14,    15,     9,
      10,    -1,    12,    -1,     4,     5,     6,     7,     8,    -1,
      -1,    90,    29,    13,    14,    15,    -1,    67,    68,    -1,
      30,    -1,    32,    -1,    34,    35,    36,    37,    38,    29,
      -1,    31,    42,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      90,    51,    -1,    -1,    94,    95,    56,    57,    58,    -1,
      -1,     4,    62,    63,     7,     8,    -1,    67,     3,    -1,
      13,    14,    15,    -1,     9,    10,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    29,    -1,    31,    -1,
      -1,    -1,    92,    93,    -1,    30,    96,    32,    -1,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    42,     4,     5,
       6,     7,     8,    48,    -1,    -1,    51,    13,    14,    15,
      -1,    56,    57,    58,    -1,    -1,     4,    62,    63,     7,
       8,    -1,    67,    29,    -1,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    29,    12,    13,    14,    15,    -1,    92,    93,    -1,
      -1,    96,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    90,    -1,    56,    57,    58,    -1,
      -1,    -1,    62,    63,    -1,    -1,    -1,    67,    -1,    -1,
      -1,     5,     6,     7,     8,    -1,    -1,     3,     4,    13,
      14,    15,    -1,     9,    10,    -1,    12,    -1,    -1,    -1,
      90,    -1,    92,    93,    -1,    95,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    42,     3,    -1,    -1,
      -1,    -1,    48,     9,    10,    51,    12,    -1,    -1,    -1,
      56,    57,    58,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    -1,    -1,    30,    -1,    32,    -1,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    90,    51,    92,    93,    -1,    95,
      56,    57,    58,    -1,    -1,    -1,    62,    63,    -1,    -1,
      -1,    67,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    12,    13,    14,    15,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    92,    93,    -1,    95,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    42,    -1,     5,     6,     7,     8,    48,
      -1,    -1,    51,    13,    14,    15,    -1,    56,    57,    58,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,     3,
       4,    31,    -1,     7,     8,     9,    10,    -1,    12,    13,
      14,    15,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    92,    93,    29,    30,    31,    32,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    42,     3,
      -1,    -1,    -1,    -1,    48,     9,    10,    51,    12,    -1,
      -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    -1,    -1,    30,    -1,    32,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    92,    93,
      -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,     3,    -1,    -1,    -1,    -1,    -1,
       9,    10,    -1,    12,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    13,    14,    15,    -1,    90,    -1,    92,    93,
      -1,    30,    -1,    32,    -1,    34,    35,    36,    37,    38,
      31,    -1,    -1,    42,     3,    -1,    -1,    -1,    -1,    48,
       9,    10,    51,    12,    -1,    -1,    -1,    56,    57,    58,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,    -1,
      -1,    30,    -1,    32,    -1,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    51,    92,    93,    -1,    -1,    56,    57,    58,
      -1,    -1,    -1,    62,    63,    -1,    -1,    -1,    67,     3,
      -1,    -1,    -1,    -1,    -1,     9,    10,    -1,    12,    -1,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    13,
      14,    15,    -1,    92,    93,    -1,    30,    -1,    32,    -1,
      34,    35,    36,    37,    38,    29,    -1,    31,    42,     3,
      -1,    -1,    -1,    -1,    48,     9,    10,    51,    12,    -1,
      -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,    -1,    -1,    30,    -1,    32,    -1,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    92,    93,
      -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    67,     1,    11,     3,     4,     5,     6,
       7,     8,     5,     6,     7,     8,    13,    14,    15,    -1,
      13,    14,    15,    -1,    -1,    -1,    -1,    -1,    92,    93,
      -1,    28,    29,    -1,    31,    32,    -1,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      67,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    90,    43,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      96,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    43,    44,    45,    96,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      96,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    45,    96,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    11,    43,    44,    45,    94,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    94,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    94,    43,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,     1,    -1,    -1,     4,
      -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    29,    -1,    31,    32,    43,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      -1,    29,    -1,    31,    -1,    -1,    -1,     4,     5,     6,
       7,     8,    -1,    29,    -1,    31,    13,    14,    15,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    -1,    29,    -1,    31,    -1,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    29,    13,    14,    15,     4,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    43,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 319 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids an empty source file");
		;
    break;}
case 3:
#line 330 "c-parse.y"
{yyval.ttype = NULL_TREE; ;
    break;}
case 5:
#line 331 "c-parse.y"
{yyval.ttype = NULL_TREE; ggc_collect(); ;
    break;}
case 7:
#line 336 "c-parse.y"
{ parsing_iso_function_signature = false; ;
    break;}
case 10:
#line 343 "c-parse.y"
{ STRIP_NOPS (yyvsp[-2].ttype);
		  if ((TREE_CODE (yyvsp[-2].ttype) == ADDR_EXPR
		       && TREE_CODE (TREE_OPERAND (yyvsp[-2].ttype, 0)) == STRING_CST)
		      || TREE_CODE (yyvsp[-2].ttype) == STRING_CST)
		    assemble_asm (yyvsp[-2].ttype);
		  else
		    error ("argument of `asm' is not a constant string"); ;
    break;}
case 11:
#line 351 "c-parse.y"
{ RESTORE_EXT_FLAGS (yyvsp[-1].itype); ;
    break;}
case 12:
#line 356 "c-parse.y"
{ if (pedantic)
		    error ("ISO C forbids data definition with no type or storage class");
		  else
		    warning ("data definition has no type or storage class");

		  POP_DECLSPEC_STACK; ;
    break;}
case 13:
#line 363 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 14:
#line 365 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 15:
#line 367 "c-parse.y"
{ shadow_tag (yyvsp[-1].ttype); ;
    break;}
case 18:
#line 371 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C does not allow extra `;' outside of a function"); ;
    break;}
case 19:
#line 377 "c-parse.y"
{ if (! start_function (current_declspecs, yyvsp[0].ttype,
					all_prefix_attributes))
		    YYERROR1;
		;
    break;}
case 20:
#line 382 "c-parse.y"
{ DECL_SOURCE_LOCATION (current_function_decl) = yyvsp[0].location;
		  store_parm_decls (); ;
    break;}
case 21:
#line 385 "c-parse.y"
{ finish_function ();
		  POP_DECLSPEC_STACK; ;
    break;}
case 22:
#line 388 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 23:
#line 390 "c-parse.y"
{ if (! start_function (current_declspecs, yyvsp[0].ttype,
					all_prefix_attributes))
		    YYERROR1;
		;
    break;}
case 24:
#line 395 "c-parse.y"
{ DECL_SOURCE_LOCATION (current_function_decl) = yyvsp[0].location;
		  store_parm_decls (); ;
    break;}
case 25:
#line 398 "c-parse.y"
{ finish_function ();
		  POP_DECLSPEC_STACK; ;
    break;}
case 26:
#line 401 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 27:
#line 403 "c-parse.y"
{ if (! start_function (NULL_TREE, yyvsp[0].ttype,
					all_prefix_attributes))
		    YYERROR1;
		;
    break;}
case 28:
#line 408 "c-parse.y"
{ DECL_SOURCE_LOCATION (current_function_decl) = yyvsp[0].location;
		  store_parm_decls (); ;
    break;}
case 29:
#line 411 "c-parse.y"
{ finish_function ();
		  POP_DECLSPEC_STACK; ;
    break;}
case 30:
#line 414 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 33:
#line 423 "c-parse.y"
{ yyval.code = ADDR_EXPR; ;
    break;}
case 34:
#line 425 "c-parse.y"
{ yyval.code = NEGATE_EXPR; ;
    break;}
case 35:
#line 427 "c-parse.y"
{ yyval.code = CONVERT_EXPR;
  if (warn_traditional && !in_system_header)
    warning ("traditional C rejects the unary plus operator");
		;
    break;}
case 36:
#line 432 "c-parse.y"
{ yyval.code = PREINCREMENT_EXPR; ;
    break;}
case 37:
#line 434 "c-parse.y"
{ yyval.code = PREDECREMENT_EXPR; ;
    break;}
case 38:
#line 436 "c-parse.y"
{ yyval.code = BIT_NOT_EXPR; ;
    break;}
case 39:
#line 438 "c-parse.y"
{ yyval.code = TRUTH_NOT_EXPR; ;
    break;}
case 40:
#line 442 "c-parse.y"
{ yyval.ttype = build_compound_expr (yyvsp[0].ttype); ;
    break;}
case 41:
#line 447 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 43:
#line 453 "c-parse.y"
{ yyval.ttype = build_tree_list (NULL_TREE, yyvsp[0].ttype); ;
    break;}
case 44:
#line 455 "c-parse.y"
{ chainon (yyvsp[-2].ttype, build_tree_list (NULL_TREE, yyvsp[0].ttype)); ;
    break;}
case 46:
#line 461 "c-parse.y"
{ yyval.ttype = build_indirect_ref (yyvsp[0].ttype, "unary *"); ;
    break;}
case 47:
#line 464 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  RESTORE_EXT_FLAGS (yyvsp[-1].itype); ;
    break;}
case 48:
#line 467 "c-parse.y"
{ yyval.ttype = build_unary_op (yyvsp[-1].code, yyvsp[0].ttype, 0);
		  overflow_warning (yyval.ttype); ;
    break;}
case 49:
#line 471 "c-parse.y"
{ yyval.ttype = finish_label_address_expr (yyvsp[0].ttype); ;
    break;}
case 50:
#line 473 "c-parse.y"
{ skip_evaluation--;
		  if (TREE_CODE (yyvsp[0].ttype) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (TREE_OPERAND (yyvsp[0].ttype, 1)))
		    error ("`sizeof' applied to a bit-field");
		  yyval.ttype = c_sizeof (TREE_TYPE (yyvsp[0].ttype)); ;
    break;}
case 51:
#line 479 "c-parse.y"
{ skip_evaluation--;
		  yyval.ttype = c_sizeof (groktypename (yyvsp[-1].ttype)); ;
    break;}
case 52:
#line 482 "c-parse.y"
{ skip_evaluation--;
		  yyval.ttype = c_alignof_expr (yyvsp[0].ttype); ;
    break;}
case 53:
#line 485 "c-parse.y"
{ skip_evaluation--;
		  yyval.ttype = c_alignof (groktypename (yyvsp[-1].ttype)); ;
    break;}
case 54:
#line 488 "c-parse.y"
{ yyval.ttype = build_unary_op (REALPART_EXPR, yyvsp[0].ttype, 0); ;
    break;}
case 55:
#line 490 "c-parse.y"
{ yyval.ttype = build_unary_op (IMAGPART_EXPR, yyvsp[0].ttype, 0); ;
    break;}
case 56:
#line 494 "c-parse.y"
{ skip_evaluation++; ;
    break;}
case 57:
#line 498 "c-parse.y"
{ skip_evaluation++; ;
    break;}
case 58:
#line 502 "c-parse.y"
{ skip_evaluation++; ;
    break;}
case 60:
#line 508 "c-parse.y"
{ yyval.ttype = c_cast_expr (yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 62:
#line 514 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 63:
#line 516 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 64:
#line 518 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 65:
#line 520 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 66:
#line 522 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 67:
#line 524 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 68:
#line 526 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 69:
#line 528 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 70:
#line 530 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 71:
#line 532 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 72:
#line 534 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 73:
#line 536 "c-parse.y"
{ yyval.ttype = parser_build_binary_op (yyvsp[-1].code, yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 74:
#line 538 "c-parse.y"
{ yyvsp[-1].ttype = c_common_truthvalue_conversion
		    (default_conversion (yyvsp[-1].ttype));
		  skip_evaluation += yyvsp[-1].ttype == truthvalue_false_node; ;
    break;}
case 75:
#line 542 "c-parse.y"
{ skip_evaluation -= yyvsp[-3].ttype == truthvalue_false_node;
		  yyval.ttype = parser_build_binary_op (TRUTH_ANDIF_EXPR, yyvsp[-3].ttype, yyvsp[0].ttype); ;
    break;}
case 76:
#line 545 "c-parse.y"
{ yyvsp[-1].ttype = c_common_truthvalue_conversion
		    (default_conversion (yyvsp[-1].ttype));
		  skip_evaluation += yyvsp[-1].ttype == truthvalue_true_node; ;
    break;}
case 77:
#line 549 "c-parse.y"
{ skip_evaluation -= yyvsp[-3].ttype == truthvalue_true_node;
		  yyval.ttype = parser_build_binary_op (TRUTH_ORIF_EXPR, yyvsp[-3].ttype, yyvsp[0].ttype); ;
    break;}
case 78:
#line 552 "c-parse.y"
{ yyvsp[-1].ttype = c_common_truthvalue_conversion
		    (default_conversion (yyvsp[-1].ttype));
		  skip_evaluation += yyvsp[-1].ttype == truthvalue_false_node; ;
    break;}
case 79:
#line 556 "c-parse.y"
{ skip_evaluation += ((yyvsp[-4].ttype == truthvalue_true_node)
				      - (yyvsp[-4].ttype == truthvalue_false_node)); ;
    break;}
case 80:
#line 559 "c-parse.y"
{ skip_evaluation -= yyvsp[-6].ttype == truthvalue_true_node;
		  yyval.ttype = build_conditional_expr (yyvsp[-6].ttype, yyvsp[-3].ttype, yyvsp[0].ttype); ;
    break;}
case 81:
#line 562 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids omitting the middle term of a ?: expression");
		  /* Make sure first operand is calculated only once.  */
		  yyvsp[0].ttype = save_expr (yyvsp[-1].ttype);
		  yyvsp[-1].ttype = c_common_truthvalue_conversion
		    (default_conversion (yyvsp[0].ttype));
		  skip_evaluation += yyvsp[-1].ttype == truthvalue_true_node; ;
    break;}
case 82:
#line 570 "c-parse.y"
{ skip_evaluation -= yyvsp[-4].ttype == truthvalue_true_node;
		  yyval.ttype = build_conditional_expr (yyvsp[-4].ttype, yyvsp[-3].ttype, yyvsp[0].ttype); ;
    break;}
case 83:
#line 573 "c-parse.y"
{ char class;
		  yyval.ttype = build_modify_expr (yyvsp[-2].ttype, NOP_EXPR, yyvsp[0].ttype);
		  class = TREE_CODE_CLASS (TREE_CODE (yyval.ttype));
		  if (IS_EXPR_CODE_CLASS (class))
		    C_SET_EXP_ORIGINAL_CODE (yyval.ttype, MODIFY_EXPR);
		;
    break;}
case 84:
#line 580 "c-parse.y"
{ char class;
		  yyval.ttype = build_modify_expr (yyvsp[-2].ttype, yyvsp[-1].code, yyvsp[0].ttype);
		  /* This inhibits warnings in
		     c_common_truthvalue_conversion.  */
		  class = TREE_CODE_CLASS (TREE_CODE (yyval.ttype));
		  if (IS_EXPR_CODE_CLASS (class))
		    C_SET_EXP_ORIGINAL_CODE (yyval.ttype, ERROR_MARK);
		;
    break;}
case 85:
#line 592 "c-parse.y"
{
		  if (yychar == YYEMPTY)
		    yychar = YYLEX;
		  yyval.ttype = build_external_ref (yyvsp[0].ttype, yychar == '(');
		;
    break;}
case 88:
#line 600 "c-parse.y"
{ yyval.ttype = fname_decl (C_RID_CODE (yyval.ttype), yyval.ttype); ;
    break;}
case 89:
#line 602 "c-parse.y"
{ start_init (NULL_TREE, NULL, 0);
		  yyvsp[-2].ttype = groktypename (yyvsp[-2].ttype);
		  really_start_incremental_init (yyvsp[-2].ttype); ;
    break;}
case 90:
#line 606 "c-parse.y"
{ tree constructor = pop_init_level (0);
		  tree type = yyvsp[-5].ttype;
		  finish_init ();

		  if (pedantic && ! flag_isoc99)
		    pedwarn ("ISO C90 forbids compound literals");
		  yyval.ttype = build_compound_literal (type, constructor);
		;
    break;}
case 91:
#line 615 "c-parse.y"
{ char class = TREE_CODE_CLASS (TREE_CODE (yyvsp[-1].ttype));
		  if (IS_EXPR_CODE_CLASS (class))
		    C_SET_EXP_ORIGINAL_CODE (yyvsp[-1].ttype, ERROR_MARK);
		  yyval.ttype = yyvsp[-1].ttype; ;
    break;}
case 92:
#line 620 "c-parse.y"
{ yyval.ttype = error_mark_node; ;
    break;}
case 93:
#line 622 "c-parse.y"
{ tree saved_last_tree;

		   if (pedantic)
		     pedwarn ("ISO C forbids braced-groups within expressions");
		  saved_last_tree = COMPOUND_BODY (yyvsp[-2].ttype);
		  RECHAIN_STMTS (yyvsp[-2].ttype, COMPOUND_BODY (yyvsp[-2].ttype));
		  last_tree = saved_last_tree;
		  TREE_CHAIN (last_tree) = NULL_TREE;
		  if (!last_expr_type)
		    last_expr_type = void_type_node;
		  yyval.ttype = build1 (STMT_EXPR, last_expr_type, yyvsp[-2].ttype);
		  TREE_SIDE_EFFECTS (yyval.ttype) = 1;
		;
    break;}
case 94:
#line 636 "c-parse.y"
{
		  last_tree = COMPOUND_BODY (yyvsp[-2].ttype);
		  TREE_CHAIN (last_tree) = NULL_TREE;
		  yyval.ttype = error_mark_node;
		;
    break;}
case 95:
#line 642 "c-parse.y"
{ yyval.ttype = build_function_call (yyvsp[-3].ttype, yyvsp[-1].ttype); ;
    break;}
case 96:
#line 644 "c-parse.y"
{ yyval.ttype = build_va_arg (yyvsp[-3].ttype, groktypename (yyvsp[-1].ttype)); ;
    break;}
case 97:
#line 647 "c-parse.y"
{
                  tree c;

                  c = fold (yyvsp[-5].ttype);
                  STRIP_NOPS (c);
                  if (TREE_CODE (c) != INTEGER_CST)
                    error ("first argument to __builtin_choose_expr not a constant");
                  yyval.ttype = integer_zerop (c) ? yyvsp[-1].ttype : yyvsp[-3].ttype;
		;
    break;}
case 98:
#line 657 "c-parse.y"
{
		  tree e1, e2;

		  e1 = TYPE_MAIN_VARIANT (groktypename (yyvsp[-3].ttype));
		  e2 = TYPE_MAIN_VARIANT (groktypename (yyvsp[-1].ttype));

		  yyval.ttype = comptypes (e1, e2, COMPARE_STRICT)
		    ? build_int_2 (1, 0) : build_int_2 (0, 0);
		;
    break;}
case 99:
#line 667 "c-parse.y"
{ yyval.ttype = build_array_ref (yyvsp[-3].ttype, yyvsp[-1].ttype); ;
    break;}
case 100:
#line 669 "c-parse.y"
{
		      yyval.ttype = build_component_ref (yyvsp[-2].ttype, yyvsp[0].ttype);
		;
    break;}
case 101:
#line 673 "c-parse.y"
{
                  tree expr = build_indirect_ref (yyvsp[-2].ttype, "->");

			yyval.ttype = build_component_ref (expr, yyvsp[0].ttype);
		;
    break;}
case 102:
#line 679 "c-parse.y"
{ yyval.ttype = build_unary_op (POSTINCREMENT_EXPR, yyvsp[-1].ttype, 0); ;
    break;}
case 103:
#line 681 "c-parse.y"
{ yyval.ttype = build_unary_op (POSTDECREMENT_EXPR, yyvsp[-1].ttype, 0); ;
    break;}
case 104:
#line 686 "c-parse.y"
{
	  parsing_iso_function_signature = false; /* Reset after decls.  */
	;
    break;}
case 105:
#line 693 "c-parse.y"
{
	  if (warn_traditional && !in_system_header
	      && parsing_iso_function_signature)
	    warning ("traditional C rejects ISO C style function definitions");
	  if (warn_old_style_definition && !in_system_header
	      && !parsing_iso_function_signature)
	    warning ("old-style parameter declaration");
	  parsing_iso_function_signature = false; /* Reset after warning.  */
	;
    break;}
case 106:
#line 703 "c-parse.y"
{
	  if (warn_old_style_definition && !in_system_header)
	    warning ("old-style parameter declaration");
	;
    break;}
case 107:
#line 714 "c-parse.y"
{ ;
    break;}
case 112:
#line 730 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 113:
#line 732 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 114:
#line 734 "c-parse.y"
{ shadow_tag_warned (yyvsp[-1].ttype, 1);
		  pedwarn ("empty declaration"); ;
    break;}
case 115:
#line 737 "c-parse.y"
{ pedwarn ("empty declaration"); ;
    break;}
case 116:
#line 746 "c-parse.y"
{ ;
    break;}
case 117:
#line 754 "c-parse.y"
{ pending_xref_error ();
		  PUSH_DECLSPEC_STACK;
		  split_specs_attrs (yyvsp[0].ttype,
				     &current_declspecs, &prefix_attributes);
		  all_prefix_attributes = prefix_attributes; ;
    break;}
case 118:
#line 765 "c-parse.y"
{ all_prefix_attributes = chainon (yyvsp[0].ttype, prefix_attributes); ;
    break;}
case 119:
#line 770 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 120:
#line 772 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 121:
#line 774 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 122:
#line 776 "c-parse.y"
{ POP_DECLSPEC_STACK; ;
    break;}
case 123:
#line 778 "c-parse.y"
{ shadow_tag (yyvsp[-1].ttype); ;
    break;}
case 124:
#line 780 "c-parse.y"
{ RESTORE_EXT_FLAGS (yyvsp[-1].itype); ;
    break;}
case 125:
#line 837 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, NULL_TREE);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 126:
#line 840 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 127:
#line 843 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 128:
#line 849 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 129:
#line 855 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 130:
#line 858 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 131:
#line 864 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, NULL_TREE);
		  TREE_STATIC (yyval.ttype) = 0; ;
    break;}
case 132:
#line 867 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 133:
#line 873 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, NULL_TREE);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 134:
#line 876 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 135:
#line 879 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 136:
#line 882 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 137:
#line 885 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 138:
#line 888 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 139:
#line 891 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 140:
#line 897 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, NULL_TREE);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 141:
#line 900 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 142:
#line 903 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 143:
#line 906 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 144:
#line 909 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 145:
#line 912 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 146:
#line 918 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 147:
#line 921 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 148:
#line 924 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 149:
#line 927 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 150:
#line 930 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 151:
#line 933 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 152:
#line 939 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 153:
#line 942 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 154:
#line 945 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 155:
#line 948 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 156:
#line 951 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 157:
#line 957 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, NULL_TREE);
		  TREE_STATIC (yyval.ttype) = 0; ;
    break;}
case 158:
#line 960 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 159:
#line 963 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 160:
#line 966 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 161:
#line 972 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 162:
#line 978 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 163:
#line 984 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 164:
#line 993 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 165:
#line 999 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 166:
#line 1002 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 167:
#line 1005 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 168:
#line 1011 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 169:
#line 1017 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 170:
#line 1023 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 171:
#line 1032 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 172:
#line 1038 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 173:
#line 1041 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 174:
#line 1044 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 175:
#line 1047 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 176:
#line 1050 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 177:
#line 1053 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 178:
#line 1056 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 179:
#line 1062 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 180:
#line 1068 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 181:
#line 1074 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 182:
#line 1083 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 183:
#line 1086 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 184:
#line 1089 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 185:
#line 1092 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 186:
#line 1095 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 187:
#line 1101 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 188:
#line 1104 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 189:
#line 1107 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 190:
#line 1110 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 191:
#line 1113 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 192:
#line 1116 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 193:
#line 1119 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 194:
#line 1125 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 195:
#line 1131 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 196:
#line 1137 "c-parse.y"
{ if (extra_warnings && TREE_STATIC (yyvsp[-1].ttype))
		    warning ("`%s' is not at beginning of declaration",
			     IDENTIFIER_POINTER (yyvsp[0].ttype));
		  yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 197:
#line 1146 "c-parse.y"
{ yyval.ttype = tree_cons (yyvsp[0].ttype, NULL_TREE, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = TREE_STATIC (yyvsp[-1].ttype); ;
    break;}
case 198:
#line 1149 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 199:
#line 1152 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 200:
#line 1155 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 201:
#line 1158 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-1].ttype);
		  TREE_STATIC (yyval.ttype) = 1; ;
    break;}
case 258:
#line 1246 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 259:
#line 1248 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 263:
#line 1283 "c-parse.y"
{ OBJC_NEED_RAW_IDENTIFIER (1);	;
    break;}
case 266:
#line 1293 "c-parse.y"
{ /* For a typedef name, record the meaning, not the name.
		     In case of `foo foo, bar;'.  */
		  yyval.ttype = lookup_name (yyvsp[0].ttype); ;
    break;}
case 267:
#line 1297 "c-parse.y"
{ skip_evaluation--;
		  if (TREE_CODE (yyvsp[-1].ttype) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (TREE_OPERAND (yyvsp[-1].ttype, 1)))
		    error ("`typeof' applied to a bit-field");
		  yyval.ttype = TREE_TYPE (yyvsp[-1].ttype); ;
    break;}
case 268:
#line 1303 "c-parse.y"
{ skip_evaluation--; yyval.ttype = groktypename (yyvsp[-1].ttype); ;
    break;}
case 273:
#line 1320 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 274:
#line 1322 "c-parse.y"
{ yyval.ttype = yyvsp[-1].ttype; ;
    break;}
case 275:
#line 1327 "c-parse.y"
{ yyval.ttype = start_decl (yyvsp[-3].ttype, current_declspecs, 1,
					  chainon (yyvsp[-1].ttype, all_prefix_attributes));
		  start_init (yyval.ttype, yyvsp[-2].ttype, global_bindings_p ()); ;
    break;}
case 276:
#line 1332 "c-parse.y"
{ finish_init ();
		  finish_decl (yyvsp[-1].ttype, yyvsp[0].ttype, yyvsp[-4].ttype); ;
    break;}
case 277:
#line 1335 "c-parse.y"
{ tree d = start_decl (yyvsp[-2].ttype, current_declspecs, 0,
				       chainon (yyvsp[0].ttype, all_prefix_attributes));
		  finish_decl (d, NULL_TREE, yyvsp[-1].ttype);
                ;
    break;}
case 278:
#line 1343 "c-parse.y"
{ yyval.ttype = start_decl (yyvsp[-3].ttype, current_declspecs, 1,
					  chainon (yyvsp[-1].ttype, all_prefix_attributes));
		  start_init (yyval.ttype, yyvsp[-2].ttype, global_bindings_p ()); ;
    break;}
case 279:
#line 1348 "c-parse.y"
{ finish_init ();
		  finish_decl (yyvsp[-1].ttype, yyvsp[0].ttype, yyvsp[-4].ttype); ;
    break;}
case 280:
#line 1351 "c-parse.y"
{ tree d = start_decl (yyvsp[-2].ttype, current_declspecs, 0,
				       chainon (yyvsp[0].ttype, all_prefix_attributes));
		  finish_decl (d, NULL_TREE, yyvsp[-1].ttype); ;
    break;}
case 281:
#line 1359 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 282:
#line 1361 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 283:
#line 1366 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 284:
#line 1368 "c-parse.y"
{ yyval.ttype = chainon (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 285:
#line 1373 "c-parse.y"
{ yyval.ttype = yyvsp[-2].ttype; ;
    break;}
case 286:
#line 1378 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 287:
#line 1380 "c-parse.y"
{ yyval.ttype = chainon (yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 288:
#line 1385 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 289:
#line 1387 "c-parse.y"
{ yyval.ttype = build_tree_list (yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 290:
#line 1389 "c-parse.y"
{ yyval.ttype = build_tree_list (yyvsp[-3].ttype, build_tree_list (NULL_TREE, yyvsp[-1].ttype)); ;
    break;}
case 291:
#line 1391 "c-parse.y"
{ yyval.ttype = build_tree_list (yyvsp[-5].ttype, tree_cons (NULL_TREE, yyvsp[-3].ttype, yyvsp[-1].ttype)); ;
    break;}
case 292:
#line 1393 "c-parse.y"
{ yyval.ttype = build_tree_list (yyvsp[-3].ttype, yyvsp[-1].ttype); ;
    break;}
case 300:
#line 1416 "c-parse.y"
{ really_start_incremental_init (NULL_TREE); ;
    break;}
case 301:
#line 1418 "c-parse.y"
{ yyval.ttype = pop_init_level (0); ;
    break;}
case 302:
#line 1420 "c-parse.y"
{ yyval.ttype = error_mark_node; ;
    break;}
case 303:
#line 1426 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids empty initializer braces"); ;
    break;}
case 307:
#line 1440 "c-parse.y"
{ if (pedantic && ! flag_isoc99)
		    pedwarn ("ISO C90 forbids specifying subobject to initialize"); ;
    break;}
case 308:
#line 1443 "c-parse.y"
{ if (pedantic)
		    pedwarn ("obsolete use of designated initializer without `='"); ;
    break;}
case 309:
#line 1446 "c-parse.y"
{ set_init_label (yyvsp[-1].ttype);
		  if (pedantic)
		    pedwarn ("obsolete use of designated initializer with `:'"); ;
    break;}
case 310:
#line 1450 "c-parse.y"
{;
    break;}
case 312:
#line 1456 "c-parse.y"
{ push_init_level (0); ;
    break;}
case 313:
#line 1458 "c-parse.y"
{ process_init_element (pop_init_level (0)); ;
    break;}
case 314:
#line 1460 "c-parse.y"
{ process_init_element (yyvsp[0].ttype); ;
    break;}
case 318:
#line 1471 "c-parse.y"
{ set_init_label (yyvsp[0].ttype); ;
    break;}
case 319:
#line 1473 "c-parse.y"
{ set_init_index (yyvsp[-3].ttype, yyvsp[-1].ttype);
		  if (pedantic)
		    pedwarn ("ISO C forbids specifying range of elements to initialize"); ;
    break;}
case 320:
#line 1477 "c-parse.y"
{ set_init_index (yyvsp[-1].ttype, NULL_TREE); ;
    break;}
case 321:
#line 1482 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids nested functions");

		  push_function_context ();
		  if (! start_function (current_declspecs, yyvsp[0].ttype,
					all_prefix_attributes))
		    {
		      pop_function_context ();
		      YYERROR1;
		    }
		  parsing_iso_function_signature = false; /* Don't warn about nested functions.  */
		;
    break;}
case 322:
#line 1495 "c-parse.y"
{ tree decl = current_function_decl;
		  DECL_SOURCE_LOCATION (decl) = yyvsp[0].location;
		  store_parm_decls (); ;
    break;}
case 323:
#line 1505 "c-parse.y"
{ tree decl = current_function_decl;
		  finish_function ();
		  pop_function_context ();
		  add_decl_stmt (decl); ;
    break;}
case 324:
#line 1513 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids nested functions");

		  push_function_context ();
		  if (! start_function (current_declspecs, yyvsp[0].ttype,
					all_prefix_attributes))
		    {
		      pop_function_context ();
		      YYERROR1;
		    }
		  parsing_iso_function_signature = false; /* Don't warn about nested functions.  */
		;
    break;}
case 325:
#line 1526 "c-parse.y"
{ tree decl = current_function_decl;
		  DECL_SOURCE_LOCATION (decl) = yyvsp[0].location;
		  store_parm_decls (); ;
    break;}
case 326:
#line 1536 "c-parse.y"
{ tree decl = current_function_decl;
		  finish_function ();
		  pop_function_context ();
		  add_decl_stmt (decl); ;
    break;}
case 329:
#line 1554 "c-parse.y"
{ yyval.ttype = yyvsp[-2].ttype ? tree_cons (yyvsp[-2].ttype, yyvsp[-1].ttype, NULL_TREE) : yyvsp[-1].ttype; ;
    break;}
case 330:
#line 1556 "c-parse.y"
{ yyval.ttype = build_nt (CALL_EXPR, yyvsp[-2].ttype, yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 331:
#line 1561 "c-parse.y"
{ yyval.ttype = set_array_declarator_type (yyvsp[0].ttype, yyvsp[-1].ttype, 0); ;
    break;}
case 332:
#line 1563 "c-parse.y"
{ yyval.ttype = make_pointer_declarator (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 336:
#line 1578 "c-parse.y"
{ yyval.ttype = build_nt (CALL_EXPR, yyvsp[-2].ttype, yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 337:
#line 1583 "c-parse.y"
{ yyval.ttype = set_array_declarator_type (yyvsp[0].ttype, yyvsp[-1].ttype, 0); ;
    break;}
case 339:
#line 1589 "c-parse.y"
{ yyval.ttype = build_nt (CALL_EXPR, yyvsp[-2].ttype, yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 340:
#line 1594 "c-parse.y"
{ yyval.ttype = set_array_declarator_type (yyvsp[0].ttype, yyvsp[-1].ttype, 0); ;
    break;}
case 341:
#line 1596 "c-parse.y"
{ yyval.ttype = make_pointer_declarator (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 342:
#line 1598 "c-parse.y"
{ yyval.ttype = make_pointer_declarator (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 343:
#line 1600 "c-parse.y"
{ yyval.ttype = yyvsp[-2].ttype ? tree_cons (yyvsp[-2].ttype, yyvsp[-1].ttype, NULL_TREE) : yyvsp[-1].ttype; ;
    break;}
case 344:
#line 1608 "c-parse.y"
{ yyval.ttype = build_nt (CALL_EXPR, yyvsp[-2].ttype, yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 345:
#line 1613 "c-parse.y"
{ yyval.ttype = yyvsp[-2].ttype ? tree_cons (yyvsp[-2].ttype, yyvsp[-1].ttype, NULL_TREE) : yyvsp[-1].ttype; ;
    break;}
case 346:
#line 1615 "c-parse.y"
{ yyval.ttype = make_pointer_declarator (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 347:
#line 1617 "c-parse.y"
{ yyval.ttype = set_array_declarator_type (yyvsp[0].ttype, yyvsp[-1].ttype, 0); ;
    break;}
case 349:
#line 1623 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 350:
#line 1625 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 351:
#line 1630 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 352:
#line 1632 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 353:
#line 1637 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 354:
#line 1639 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 355:
#line 1650 "c-parse.y"
{ yyval.ttype = start_struct (RECORD_TYPE, yyvsp[-1].ttype);
		  /* Start scope of tag before parsing components.  */
		;
    break;}
case 356:
#line 1654 "c-parse.y"
{ yyval.ttype = finish_struct (yyvsp[-3].ttype, nreverse (yyvsp[-2].ttype),
				      chainon (yyvsp[-6].ttype, yyvsp[0].ttype)); ;
    break;}
case 357:
#line 1657 "c-parse.y"
{ yyval.ttype = finish_struct (start_struct (RECORD_TYPE, NULL_TREE),
				      nreverse (yyvsp[-2].ttype), chainon (yyvsp[-4].ttype, yyvsp[0].ttype));
		;
    break;}
case 358:
#line 1661 "c-parse.y"
{ yyval.ttype = start_struct (UNION_TYPE, yyvsp[-1].ttype); ;
    break;}
case 359:
#line 1663 "c-parse.y"
{ yyval.ttype = finish_struct (yyvsp[-3].ttype, nreverse (yyvsp[-2].ttype),
				      chainon (yyvsp[-6].ttype, yyvsp[0].ttype)); ;
    break;}
case 360:
#line 1666 "c-parse.y"
{ yyval.ttype = finish_struct (start_struct (UNION_TYPE, NULL_TREE),
				      nreverse (yyvsp[-2].ttype), chainon (yyvsp[-4].ttype, yyvsp[0].ttype));
		;
    break;}
case 361:
#line 1670 "c-parse.y"
{ yyval.ttype = start_enum (yyvsp[-1].ttype); ;
    break;}
case 362:
#line 1672 "c-parse.y"
{ yyval.ttype = finish_enum (yyvsp[-4].ttype, nreverse (yyvsp[-3].ttype),
				    chainon (yyvsp[-7].ttype, yyvsp[0].ttype)); ;
    break;}
case 363:
#line 1675 "c-parse.y"
{ yyval.ttype = start_enum (NULL_TREE); ;
    break;}
case 364:
#line 1677 "c-parse.y"
{ yyval.ttype = finish_enum (yyvsp[-4].ttype, nreverse (yyvsp[-3].ttype),
				    chainon (yyvsp[-6].ttype, yyvsp[0].ttype)); ;
    break;}
case 365:
#line 1683 "c-parse.y"
{ yyval.ttype = xref_tag (RECORD_TYPE, yyvsp[0].ttype); ;
    break;}
case 366:
#line 1685 "c-parse.y"
{ yyval.ttype = xref_tag (UNION_TYPE, yyvsp[0].ttype); ;
    break;}
case 367:
#line 1687 "c-parse.y"
{ yyval.ttype = xref_tag (ENUMERAL_TYPE, yyvsp[0].ttype);
		  /* In ISO C, enumerated types can be referred to
		     only if already defined.  */
		  if (pedantic && !COMPLETE_TYPE_P (yyval.ttype))
		    pedwarn ("ISO C forbids forward references to `enum' types"); ;
    break;}
case 371:
#line 1702 "c-parse.y"
{ if (pedantic && ! flag_isoc99)
		    pedwarn ("comma at end of enumerator list"); ;
    break;}
case 372:
#line 1720 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 373:
#line 1722 "c-parse.y"
{ yyval.ttype = chainon (yyvsp[0].ttype, yyvsp[-1].ttype);
		  pedwarn ("no semicolon at end of struct or union"); ;
    break;}
case 374:
#line 1727 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 375:
#line 1729 "c-parse.y"
{ yyval.ttype = chainon (yyvsp[-1].ttype, yyvsp[-2].ttype); ;
    break;}
case 376:
#line 1731 "c-parse.y"
{ if (pedantic)
		    pedwarn ("extra semicolon in struct or union specified"); ;
    break;}
case 377:
#line 1737 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  POP_DECLSPEC_STACK; ;
    break;}
case 378:
#line 1740 "c-parse.y"
{
		  /* Support for unnamed structs or unions as members of
		     structs or unions (which is [a] useful and [b] supports
		     MS P-SDK).  */
		  if (pedantic)
		    pedwarn ("ISO C doesn't support unnamed structs/unions");

		  yyval.ttype = grokfield(NULL, current_declspecs, NULL_TREE);
		  POP_DECLSPEC_STACK; ;
    break;}
case 379:
#line 1750 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  POP_DECLSPEC_STACK; ;
    break;}
case 380:
#line 1753 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids member declarations with no members");
		  shadow_tag_warned (yyvsp[0].ttype, pedantic);
		  yyval.ttype = NULL_TREE; ;
    break;}
case 381:
#line 1758 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 382:
#line 1760 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  RESTORE_EXT_FLAGS (yyvsp[-1].itype); ;
    break;}
case 384:
#line 1767 "c-parse.y"
{ TREE_CHAIN (yyvsp[0].ttype) = yyvsp[-3].ttype; yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 386:
#line 1773 "c-parse.y"
{ TREE_CHAIN (yyvsp[0].ttype) = yyvsp[-3].ttype; yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 387:
#line 1778 "c-parse.y"
{ yyval.ttype = grokfield (yyvsp[-1].ttype, current_declspecs, NULL_TREE);
		  decl_attributes (&yyval.ttype,
				   chainon (yyvsp[0].ttype, all_prefix_attributes), 0); ;
    break;}
case 388:
#line 1782 "c-parse.y"
{ yyval.ttype = grokfield (yyvsp[-3].ttype, current_declspecs, yyvsp[-1].ttype);
		  decl_attributes (&yyval.ttype,
				   chainon (yyvsp[0].ttype, all_prefix_attributes), 0); ;
    break;}
case 389:
#line 1786 "c-parse.y"
{ yyval.ttype = grokfield (NULL_TREE, current_declspecs, yyvsp[-1].ttype);
		  decl_attributes (&yyval.ttype,
				   chainon (yyvsp[0].ttype, all_prefix_attributes), 0); ;
    break;}
case 390:
#line 1793 "c-parse.y"
{ yyval.ttype = grokfield (yyvsp[-1].ttype, current_declspecs, NULL_TREE);
		  decl_attributes (&yyval.ttype,
				   chainon (yyvsp[0].ttype, all_prefix_attributes), 0); ;
    break;}
case 391:
#line 1797 "c-parse.y"
{ yyval.ttype = grokfield (yyvsp[-3].ttype, current_declspecs, yyvsp[-1].ttype);
		  decl_attributes (&yyval.ttype,
				   chainon (yyvsp[0].ttype, all_prefix_attributes), 0); ;
    break;}
case 392:
#line 1801 "c-parse.y"
{ yyval.ttype = grokfield (NULL_TREE, current_declspecs, yyvsp[-1].ttype);
		  decl_attributes (&yyval.ttype,
				   chainon (yyvsp[0].ttype, all_prefix_attributes), 0); ;
    break;}
case 394:
#line 1812 "c-parse.y"
{ if (yyvsp[-2].ttype == error_mark_node)
		    yyval.ttype = yyvsp[-2].ttype;
		  else
		    TREE_CHAIN (yyvsp[0].ttype) = yyvsp[-2].ttype, yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 395:
#line 1817 "c-parse.y"
{ yyval.ttype = error_mark_node; ;
    break;}
case 396:
#line 1823 "c-parse.y"
{ yyval.ttype = build_enumerator (yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 397:
#line 1825 "c-parse.y"
{ yyval.ttype = build_enumerator (yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 398:
#line 1830 "c-parse.y"
{ pending_xref_error ();
		  yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 399:
#line 1833 "c-parse.y"
{ yyval.ttype = build_tree_list (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 400:
#line 1838 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 402:
#line 1844 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 NULL_TREE),
					all_prefix_attributes); ;
    break;}
case 403:
#line 1848 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[0].ttype),
					all_prefix_attributes); ;
    break;}
case 404:
#line 1852 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[-1].ttype),
					chainon (yyvsp[0].ttype, all_prefix_attributes)); ;
    break;}
case 408:
#line 1865 "c-parse.y"
{ yyval.ttype = make_pointer_declarator (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 409:
#line 1870 "c-parse.y"
{ yyval.ttype = make_pointer_declarator (yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 410:
#line 1872 "c-parse.y"
{ yyval.ttype = make_pointer_declarator (yyvsp[-1].ttype, yyvsp[0].ttype); ;
    break;}
case 411:
#line 1877 "c-parse.y"
{ yyval.ttype = yyvsp[-2].ttype ? tree_cons (yyvsp[-2].ttype, yyvsp[-1].ttype, NULL_TREE) : yyvsp[-1].ttype; ;
    break;}
case 412:
#line 1879 "c-parse.y"
{ yyval.ttype = build_nt (CALL_EXPR, yyvsp[-2].ttype, yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 413:
#line 1881 "c-parse.y"
{ yyval.ttype = set_array_declarator_type (yyvsp[0].ttype, yyvsp[-1].ttype, 1); ;
    break;}
case 414:
#line 1883 "c-parse.y"
{ yyval.ttype = build_nt (CALL_EXPR, NULL_TREE, yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 415:
#line 1885 "c-parse.y"
{ yyval.ttype = set_array_declarator_type (yyvsp[0].ttype, NULL_TREE, 1); ;
    break;}
case 416:
#line 1892 "c-parse.y"
{ yyval.ttype = build_array_declarator (yyvsp[-1].ttype, yyvsp[-2].ttype, 0, 0); ;
    break;}
case 417:
#line 1894 "c-parse.y"
{ yyval.ttype = build_array_declarator (NULL_TREE, yyvsp[-1].ttype, 0, 0); ;
    break;}
case 418:
#line 1896 "c-parse.y"
{ yyval.ttype = build_array_declarator (NULL_TREE, yyvsp[-2].ttype, 0, 1); ;
    break;}
case 419:
#line 1898 "c-parse.y"
{ yyval.ttype = build_array_declarator (yyvsp[-1].ttype, yyvsp[-2].ttype, 1, 0); ;
    break;}
case 420:
#line 1901 "c-parse.y"
{ yyval.ttype = build_array_declarator (yyvsp[-1].ttype, yyvsp[-3].ttype, 1, 0); ;
    break;}
case 423:
#line 1914 "c-parse.y"
{
		  error ("label at end of compound statement");
		;
    break;}
case 431:
#line 1931 "c-parse.y"
{
		  if ((pedantic && !flag_isoc99)
		      || warn_declaration_after_statement)
		    pedwarn_c90 ("ISO C90 forbids mixed declarations and code");
		;
    break;}
case 446:
#line 1964 "c-parse.y"
{ pushlevel (0);
		  clear_last_expr ();
		  add_scope_stmt (/*begin_p=*/1, /*partial_p=*/0);
		;
    break;}
case 447:
#line 1971 "c-parse.y"
{
		  yyval.ttype = add_scope_stmt (/*begin_p=*/0, /*partial_p=*/0);
		;
    break;}
case 448:
#line 1978 "c-parse.y"
{ if (flag_isoc99)
		    {
		      yyval.ttype = c_begin_compound_stmt ();
		      pushlevel (0);
		      clear_last_expr ();
		      add_scope_stmt (/*begin_p=*/1, /*partial_p=*/0);
		    }
		  else
		    yyval.ttype = NULL_TREE;
		;
    break;}
case 449:
#line 1994 "c-parse.y"
{ if (flag_isoc99)
		    {
		      tree scope_stmt = add_scope_stmt (/*begin_p=*/0, /*partial_p=*/0);
		      yyval.ttype = poplevel (KEEP_MAYBE, 0, 0);
		      SCOPE_STMT_BLOCK (TREE_PURPOSE (scope_stmt))
			= SCOPE_STMT_BLOCK (TREE_VALUE (scope_stmt))
			= yyval.ttype;
		    }
		  else
		    yyval.ttype = NULL_TREE; ;
    break;}
case 451:
#line 2011 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids label declarations"); ;
    break;}
case 454:
#line 2022 "c-parse.y"
{ tree link;
		  for (link = yyvsp[-1].ttype; link; link = TREE_CHAIN (link))
		    {
		      tree label = declare_label (TREE_VALUE (link));
		      C_DECLARED_LABEL_FLAG (label) = 1;
		      add_decl_stmt (label);
		    }
		;
    break;}
case 455:
#line 2036 "c-parse.y"
{;
    break;}
case 457:
#line 2040 "c-parse.y"
{ compstmt_count++;
                      yyval.ttype = c_begin_compound_stmt (); ;
    break;}
case 458:
#line 2045 "c-parse.y"
{ yyval.ttype = convert (void_type_node, integer_zero_node); ;
    break;}
case 459:
#line 2047 "c-parse.y"
{ yyval.ttype = poplevel (KEEP_MAYBE, 0, 0);
		  SCOPE_STMT_BLOCK (TREE_PURPOSE (yyvsp[0].ttype))
		    = SCOPE_STMT_BLOCK (TREE_VALUE (yyvsp[0].ttype))
		    = yyval.ttype; ;
    break;}
case 462:
#line 2060 "c-parse.y"
{ if (current_function_decl == 0)
		    {
		      error ("braced-group within expression allowed only inside a function");
		      YYERROR;
		    }
		  /* We must force a BLOCK for this level
		     so that, if it is not expanded later,
		     there is a way to turn off the entire subtree of blocks
		     that are contained in it.  */
		  keep_next_level ();
		  compstmt_count++;
		  yyval.ttype = add_stmt (build_stmt (COMPOUND_STMT, last_tree));
		  last_expr_type = NULL_TREE;
		;
    break;}
case 463:
#line 2077 "c-parse.y"
{ RECHAIN_STMTS (yyvsp[-1].ttype, COMPOUND_BODY (yyvsp[-1].ttype));
		  last_expr_type = NULL_TREE;
                  yyval.ttype = yyvsp[-1].ttype; ;
    break;}
case 464:
#line 2085 "c-parse.y"
{ c_finish_then (); ;
    break;}
case 466:
#line 2102 "c-parse.y"
{ yyval.ttype = c_begin_if_stmt (); ;
    break;}
case 467:
#line 2104 "c-parse.y"
{ c_expand_start_cond (c_common_truthvalue_conversion (yyvsp[-1].ttype),
				       compstmt_count,yyvsp[-3].ttype);
		  yyval.itype = stmt_count;
		  if_stmt_locus = yyvsp[-6].location; ;
    break;}
case 468:
#line 2115 "c-parse.y"
{ stmt_count++;
		  compstmt_count++;
		  c_in_iteration_stmt++;
		  yyval.ttype
		    = add_stmt (build_stmt (DO_STMT, NULL_TREE,
					    NULL_TREE));
		  /* In the event that a parse error prevents
		     parsing the complete do-statement, set the
		     condition now.  Otherwise, we can get crashes at
		     RTL-generation time.  */
		  DO_COND (yyval.ttype) = error_mark_node; ;
    break;}
case 469:
#line 2127 "c-parse.y"
{ yyval.ttype = yyvsp[-2].ttype;
		  RECHAIN_STMTS (yyval.ttype, DO_BODY (yyval.ttype));
		  c_in_iteration_stmt--; ;
    break;}
case 470:
#line 2137 "c-parse.y"
{ if (yychar == YYEMPTY)
		    yychar = YYLEX;
		  yyval.location = input_location; ;
    break;}
case 473:
#line 2150 "c-parse.y"
{ if (flag_isoc99)
		    RECHAIN_STMTS (yyvsp[-2].ttype, COMPOUND_BODY (yyvsp[-2].ttype)); ;
    break;}
case 474:
#line 2156 "c-parse.y"
{ if (yyvsp[0].ttype)
		    {
		      STMT_LINENO (yyvsp[0].ttype) = yyvsp[-1].location.line;
		      /* ??? We currently have no way of recording
			 the filename for a statement.  This probably
			 matters little in practice at the moment,
			 but I suspect that problems will occur when
			 doing inlining at the tree level.  */
		    }
		;
    break;}
case 475:
#line 2170 "c-parse.y"
{ if (yyvsp[0].ttype)
		    {
		      STMT_LINENO (yyvsp[0].ttype) = yyvsp[-1].location.line;
		    }
		;
    break;}
case 476:
#line 2179 "c-parse.y"
{ c_expand_start_else ();
		  yyvsp[-1].itype = stmt_count; ;
    break;}
case 477:
#line 2182 "c-parse.y"
{ c_finish_else ();
		  c_expand_end_cond ();
		  if (extra_warnings && stmt_count == yyvsp[-3].itype)
		    warning ("empty body in an else-statement"); ;
    break;}
case 478:
#line 2187 "c-parse.y"
{ c_expand_end_cond ();
		  /* This warning is here instead of in simple_if, because we
		     do not want a warning if an empty if is followed by an
		     else statement.  Increment stmt_count so we don't
		     give a second error if this is a nested `if'.  */
		  if (extra_warnings && stmt_count++ == yyvsp[0].itype)
		    warning ("%Hempty body in an if-statement",
                             &if_stmt_locus); ;
    break;}
case 479:
#line 2199 "c-parse.y"
{ c_expand_end_cond (); ;
    break;}
case 480:
#line 2209 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = c_begin_while_stmt (); ;
    break;}
case 481:
#line 2212 "c-parse.y"
{ c_in_iteration_stmt++;
		  yyvsp[-1].ttype = c_common_truthvalue_conversion (yyvsp[-1].ttype);
		  c_finish_while_stmt_cond
		    (c_common_truthvalue_conversion (yyvsp[-1].ttype), yyvsp[-3].ttype);
		  yyval.ttype = add_stmt (yyvsp[-3].ttype); ;
    break;}
case 482:
#line 2218 "c-parse.y"
{ c_in_iteration_stmt--;
		  RECHAIN_STMTS (yyvsp[-1].ttype, WHILE_BODY (yyvsp[-1].ttype)); ;
    break;}
case 483:
#line 2222 "c-parse.y"
{ DO_COND (yyvsp[-4].ttype) = c_common_truthvalue_conversion (yyvsp[-2].ttype); ;
    break;}
case 484:
#line 2224 "c-parse.y"
{ ;
    break;}
case 485:
#line 2226 "c-parse.y"
{ yyval.ttype = build_stmt (FOR_STMT, NULL_TREE, NULL_TREE,
					  NULL_TREE, NULL_TREE);
		  add_stmt (yyval.ttype); ;
    break;}
case 486:
#line 2230 "c-parse.y"
{ stmt_count++;
		  RECHAIN_STMTS (yyvsp[-2].ttype, FOR_INIT_STMT (yyvsp[-2].ttype)); ;
    break;}
case 487:
#line 2233 "c-parse.y"
{ if (yyvsp[-1].ttype)
		    FOR_COND (yyvsp[-5].ttype)
		      = c_common_truthvalue_conversion (yyvsp[-1].ttype); ;
    break;}
case 488:
#line 2237 "c-parse.y"
{ c_in_iteration_stmt++;
		  FOR_EXPR (yyvsp[-8].ttype) = yyvsp[-1].ttype; ;
    break;}
case 489:
#line 2240 "c-parse.y"
{ RECHAIN_STMTS (yyvsp[-10].ttype, FOR_BODY (yyvsp[-10].ttype));
		  c_in_iteration_stmt--;;
    break;}
case 490:
#line 2243 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = c_start_case (yyvsp[-1].ttype);
		  c_in_case_stmt++; ;
    break;}
case 491:
#line 2247 "c-parse.y"
{ c_finish_case ();
		  c_in_case_stmt--; ;
    break;}
case 492:
#line 2253 "c-parse.y"
{ add_stmt (build_stmt (EXPR_STMT, yyvsp[-1].ttype)); ;
    break;}
case 493:
#line 2255 "c-parse.y"
{ check_for_loop_decls (); ;
    break;}
case 494:
#line 2261 "c-parse.y"
{ stmt_count++; yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 495:
#line 2263 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = c_expand_expr_stmt (yyvsp[-1].ttype); ;
    break;}
case 496:
#line 2266 "c-parse.y"
{ if (flag_isoc99)
		    RECHAIN_STMTS (yyvsp[-2].ttype, COMPOUND_BODY (yyvsp[-2].ttype));
		  yyval.ttype = NULL_TREE; ;
    break;}
case 497:
#line 2270 "c-parse.y"
{ stmt_count++;
		if (!(c_in_iteration_stmt || c_in_case_stmt))
		  {
		    error ("break statement not within loop or switch");
		    yyval.ttype = NULL_TREE;
		  }
		else
		  yyval.ttype = add_stmt (build_break_stmt ()); ;
    break;}
case 498:
#line 2279 "c-parse.y"
{ stmt_count++;
		if (!c_in_iteration_stmt)
		  {
		    error ("continue statement not within a loop");
		    yyval.ttype = NULL_TREE;
		  }
		else
		  yyval.ttype = add_stmt (build_continue_stmt ()); ;
    break;}
case 499:
#line 2288 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = c_expand_return (NULL_TREE); ;
    break;}
case 500:
#line 2291 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = c_expand_return (yyvsp[-1].ttype); ;
    break;}
case 501:
#line 2294 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = simple_asm_stmt (yyvsp[-2].ttype); ;
    break;}
case 502:
#line 2298 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = build_asm_stmt (yyvsp[-6].ttype, yyvsp[-4].ttype, yyvsp[-2].ttype, NULL_TREE, NULL_TREE); ;
    break;}
case 503:
#line 2303 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = build_asm_stmt (yyvsp[-8].ttype, yyvsp[-6].ttype, yyvsp[-4].ttype, yyvsp[-2].ttype, NULL_TREE); ;
    break;}
case 504:
#line 2308 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = build_asm_stmt (yyvsp[-10].ttype, yyvsp[-8].ttype, yyvsp[-6].ttype, yyvsp[-4].ttype, yyvsp[-2].ttype); ;
    break;}
case 505:
#line 2311 "c-parse.y"
{ tree decl;
		  stmt_count++;
		  decl = lookup_label (yyvsp[-1].ttype);
		  if (decl != 0)
		    {
		      TREE_USED (decl) = 1;
		      yyval.ttype = add_stmt (build_stmt (GOTO_STMT, decl));
		    }
		  else
		    yyval.ttype = NULL_TREE;
		;
    break;}
case 506:
#line 2323 "c-parse.y"
{ if (pedantic)
		    pedwarn ("ISO C forbids `goto *expr;'");
		  stmt_count++;
		  yyvsp[-1].ttype = convert (ptr_type_node, yyvsp[-1].ttype);
		  yyval.ttype = add_stmt (build_stmt (GOTO_STMT, yyvsp[-1].ttype)); ;
    break;}
case 507:
#line 2329 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 508:
#line 2337 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = do_case (yyvsp[-1].ttype, NULL_TREE); ;
    break;}
case 509:
#line 2340 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = do_case (yyvsp[-3].ttype, yyvsp[-1].ttype); ;
    break;}
case 510:
#line 2343 "c-parse.y"
{ stmt_count++;
		  yyval.ttype = do_case (NULL_TREE, NULL_TREE); ;
    break;}
case 511:
#line 2346 "c-parse.y"
{ tree label = define_label (yyvsp[-2].location, yyvsp[-3].ttype);
		  stmt_count++;
		  if (label)
		    {
		      decl_attributes (&label, yyvsp[0].ttype, 0);
		      yyval.ttype = add_stmt (build_stmt (LABEL_STMT, label));
		    }
		  else
		    yyval.ttype = NULL_TREE;
		;
    break;}
case 512:
#line 2362 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 513:
#line 2364 "c-parse.y"
{ ;
    break;}
case 514:
#line 2369 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 516:
#line 2376 "c-parse.y"
{ yyval.ttype = NULL_TREE; ;
    break;}
case 519:
#line 2383 "c-parse.y"
{ yyval.ttype = chainon (yyvsp[-2].ttype, yyvsp[0].ttype); ;
    break;}
case 520:
#line 2388 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (NULL_TREE, yyvsp[-3].ttype), yyvsp[-1].ttype); ;
    break;}
case 521:
#line 2390 "c-parse.y"
{ yyvsp[-5].ttype = build_string (IDENTIFIER_LENGTH (yyvsp[-5].ttype),
				     IDENTIFIER_POINTER (yyvsp[-5].ttype));
		  yyval.ttype = build_tree_list (build_tree_list (yyvsp[-5].ttype, yyvsp[-3].ttype), yyvsp[-1].ttype); ;
    break;}
case 522:
#line 2397 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, NULL_TREE); ;
    break;}
case 523:
#line 2399 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, yyvsp[0].ttype, yyvsp[-2].ttype); ;
    break;}
case 524:
#line 2409 "c-parse.y"
{ pushlevel (0);
		  declare_parm_level (); ;
    break;}
case 525:
#line 2412 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  poplevel (0, 0, 0); ;
    break;}
case 527:
#line 2419 "c-parse.y"
{ mark_forward_parm_decls (); ;
    break;}
case 528:
#line 2421 "c-parse.y"
{ /* Dummy action so attributes are in known place
		     on parser stack.  */ ;
    break;}
case 529:
#line 2424 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype; ;
    break;}
case 530:
#line 2426 "c-parse.y"
{ yyval.ttype = tree_cons (NULL_TREE, NULL_TREE, NULL_TREE); ;
    break;}
case 531:
#line 2432 "c-parse.y"
{ yyval.ttype = get_parm_info (0); ;
    break;}
case 532:
#line 2434 "c-parse.y"
{ yyval.ttype = get_parm_info (0);
		  /* Gcc used to allow this as an extension.  However, it does
		     not work for all targets, and thus has been disabled.
		     Also, since func (...) and func () are indistinguishable,
		     it caused problems with the code in expand_builtin which
		     tries to verify that BUILT_IN_NEXT_ARG is being used
		     correctly.  */
		  error ("ISO C requires a named argument before `...'");
		  parsing_iso_function_signature = true;
		;
    break;}
case 533:
#line 2445 "c-parse.y"
{ yyval.ttype = get_parm_info (1);
		  parsing_iso_function_signature = true;
		;
    break;}
case 534:
#line 2449 "c-parse.y"
{ yyval.ttype = get_parm_info (0);
		  parsing_iso_function_signature = true;
		;
    break;}
case 535:
#line 2456 "c-parse.y"
{ push_parm_decl (yyvsp[0].ttype); ;
    break;}
case 536:
#line 2458 "c-parse.y"
{ push_parm_decl (yyvsp[0].ttype); ;
    break;}
case 537:
#line 2465 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[-1].ttype),
					chainon (yyvsp[0].ttype, all_prefix_attributes));
		  POP_DECLSPEC_STACK; ;
    break;}
case 538:
#line 2470 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[-1].ttype),
					chainon (yyvsp[0].ttype, all_prefix_attributes));
		  POP_DECLSPEC_STACK; ;
    break;}
case 539:
#line 2475 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  POP_DECLSPEC_STACK; ;
    break;}
case 540:
#line 2478 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[-1].ttype),
					chainon (yyvsp[0].ttype, all_prefix_attributes));
		  POP_DECLSPEC_STACK; ;
    break;}
case 541:
#line 2484 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  POP_DECLSPEC_STACK; ;
    break;}
case 542:
#line 2492 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[-1].ttype),
					chainon (yyvsp[0].ttype, all_prefix_attributes));
		  POP_DECLSPEC_STACK; ;
    break;}
case 543:
#line 2497 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[-1].ttype),
					chainon (yyvsp[0].ttype, all_prefix_attributes));
		  POP_DECLSPEC_STACK; ;
    break;}
case 544:
#line 2502 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  POP_DECLSPEC_STACK; ;
    break;}
case 545:
#line 2505 "c-parse.y"
{ yyval.ttype = build_tree_list (build_tree_list (current_declspecs,
							 yyvsp[-1].ttype),
					chainon (yyvsp[0].ttype, all_prefix_attributes));
		  POP_DECLSPEC_STACK; ;
    break;}
case 546:
#line 2511 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  POP_DECLSPEC_STACK; ;
    break;}
case 547:
#line 2517 "c-parse.y"
{ prefix_attributes = chainon (prefix_attributes, yyvsp[-3].ttype);
		  all_prefix_attributes = prefix_attributes; ;
    break;}
case 548:
#line 2526 "c-parse.y"
{ pushlevel (0);
		  declare_parm_level (); ;
    break;}
case 549:
#line 2529 "c-parse.y"
{ yyval.ttype = yyvsp[0].ttype;
		  poplevel (0, 0, 0); ;
    break;}
case 551:
#line 2536 "c-parse.y"
{ tree t;
		  for (t = yyvsp[-1].ttype; t; t = TREE_CHAIN (t))
		    if (TREE_VALUE (t) == NULL_TREE)
		      error ("`...' in old-style identifier list");
		  yyval.ttype = tree_cons (NULL_TREE, NULL_TREE, yyvsp[-1].ttype);

		  /* Make sure we have a parmlist after attributes.  */
		  if (yyvsp[-3].ttype != 0
		      && (TREE_CODE (yyval.ttype) != TREE_LIST
			  || TREE_PURPOSE (yyval.ttype) == 0
			  || TREE_CODE (TREE_PURPOSE (yyval.ttype)) != PARM_DECL))
		    YYERROR1;
		;
    break;}
case 552:
#line 2554 "c-parse.y"
{ yyval.ttype = build_tree_list (NULL_TREE, yyvsp[0].ttype); ;
    break;}
case 553:
#line 2556 "c-parse.y"
{ yyval.ttype = chainon (yyvsp[-2].ttype, build_tree_list (NULL_TREE, yyvsp[0].ttype)); ;
    break;}
case 554:
#line 2562 "c-parse.y"
{ yyval.ttype = build_tree_list (NULL_TREE, yyvsp[0].ttype); ;
    break;}
case 555:
#line 2564 "c-parse.y"
{ yyval.ttype = chainon (yyvsp[-2].ttype, build_tree_list (NULL_TREE, yyvsp[0].ttype)); ;
    break;}
case 556:
#line 2569 "c-parse.y"
{ yyval.itype = SAVE_EXT_FLAGS();
		  pedantic = 0;
		  warn_pointer_arith = 0;
		  warn_traditional = 0;
		  flag_iso = 0; ;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 2576 "c-parse.y"


/* yylex() is a thin wrapper around c_lex(), all it does is translate
   cpplib.h's token codes into yacc's token codes.  */

static enum cpp_ttype last_token;

/* The reserved keyword table.  */
struct resword
{
  const char *word;
  ENUM_BITFIELD(rid) rid : 16;
  unsigned int disable   : 16;
};

/* Disable mask.  Keywords are disabled if (reswords[i].disable & mask) is
   _true_.  */
#define D_C89	0x01	/* not in C89 */
#define D_EXT	0x02	/* GCC extension */
#define D_EXT89	0x04	/* GCC extension incorporated in C99 */
#define D_OBJC	0x08	/* Objective C only */

static const struct resword reswords[] =
{
  { "_Bool",		RID_BOOL,	0 },
  { "_Complex",		RID_COMPLEX,	0 },
  { "__FUNCTION__",	RID_FUNCTION_NAME, 0 },
  { "__PRETTY_FUNCTION__", RID_PRETTY_FUNCTION_NAME, 0 },
  { "__alignof",	RID_ALIGNOF,	0 },
  { "__alignof__",	RID_ALIGNOF,	0 },
  { "__asm",		RID_ASM,	0 },
  { "__asm__",		RID_ASM,	0 },
  { "__attribute",	RID_ATTRIBUTE,	0 },
  { "__attribute__",	RID_ATTRIBUTE,	0 },
  { "__builtin_choose_expr", RID_CHOOSE_EXPR, 0 },
  { "__builtin_types_compatible_p", RID_TYPES_COMPATIBLE_P, 0 },
  { "__builtin_va_arg",	RID_VA_ARG,	0 },
  { "__complex",	RID_COMPLEX,	0 },
  { "__complex__",	RID_COMPLEX,	0 },
  { "__const",		RID_CONST,	0 },
  { "__const__",	RID_CONST,	0 },
  { "__extension__",	RID_EXTENSION,	0 },
  { "__func__",		RID_C99_FUNCTION_NAME, 0 },
  { "__imag",		RID_IMAGPART,	0 },
  { "__imag__",		RID_IMAGPART,	0 },
  { "__inline",		RID_INLINE,	0 },
  { "__inline__",	RID_INLINE,	0 },
  { "__label__",	RID_LABEL,	0 },
  { "__ptrbase",	RID_PTRBASE,	0 },
  { "__ptrbase__",	RID_PTRBASE,	0 },
  { "__ptrextent",	RID_PTREXTENT,	0 },
  { "__ptrextent__",	RID_PTREXTENT,	0 },
  { "__ptrvalue",	RID_PTRVALUE,	0 },
  { "__ptrvalue__",	RID_PTRVALUE,	0 },
  { "__real",		RID_REALPART,	0 },
  { "__real__",		RID_REALPART,	0 },
  { "__restrict",	RID_RESTRICT,	0 },
  { "__restrict__",	RID_RESTRICT,	0 },
  { "__signed",		RID_SIGNED,	0 },
  { "__signed__",	RID_SIGNED,	0 },
  { "__thread",		RID_THREAD,	0 },
  { "__typeof",		RID_TYPEOF,	0 },
  { "__typeof__",	RID_TYPEOF,	0 },
  { "__volatile",	RID_VOLATILE,	0 },
  { "__volatile__",	RID_VOLATILE,	0 },
  { "asm",		RID_ASM,	D_EXT },
  { "auto",		RID_AUTO,	0 },
  { "break",		RID_BREAK,	0 },
  { "case",		RID_CASE,	0 },
  { "char",		RID_CHAR,	0 },
  { "const",		RID_CONST,	0 },
  { "continue",		RID_CONTINUE,	0 },
  { "default",		RID_DEFAULT,	0 },
  { "do",		RID_DO,		0 },
  { "double",		RID_DOUBLE,	0 },
  { "else",		RID_ELSE,	0 },
  { "enum",		RID_ENUM,	0 },
  { "extern",		RID_EXTERN,	0 },
  { "float",		RID_FLOAT,	0 },
  { "for",		RID_FOR,	0 },
  { "goto",		RID_GOTO,	0 },
  { "if",		RID_IF,		0 },
  { "inline",		RID_INLINE,	D_EXT89 },
  { "int",		RID_INT,	0 },
  { "long",		RID_LONG,	0 },
  { "register",		RID_REGISTER,	0 },
  { "restrict",		RID_RESTRICT,	D_C89 },
  { "return",		RID_RETURN,	0 },
  { "short",		RID_SHORT,	0 },
  { "signed",		RID_SIGNED,	0 },
  { "sizeof",		RID_SIZEOF,	0 },
  { "static",		RID_STATIC,	0 },
  { "struct",		RID_STRUCT,	0 },
  { "switch",		RID_SWITCH,	0 },
  { "typedef",		RID_TYPEDEF,	0 },
  { "typeof",		RID_TYPEOF,	D_EXT },
  { "union",		RID_UNION,	0 },
  { "unsigned",		RID_UNSIGNED,	0 },
  { "void",		RID_VOID,	0 },
  { "volatile",		RID_VOLATILE,	0 },
  { "while",		RID_WHILE,	0 },
};
#define N_reswords (sizeof reswords / sizeof (struct resword))

/* Table mapping from RID_* constants to yacc token numbers.
   Unfortunately we have to have entries for all the keywords in all
   three languages.  */
static const short rid_to_yy[RID_MAX] =
{
  /* RID_STATIC */	STATIC,
  /* RID_UNSIGNED */	TYPESPEC,
  /* RID_LONG */	TYPESPEC,
  /* RID_CONST */	TYPE_QUAL,
  /* RID_EXTERN */	SCSPEC,
  /* RID_REGISTER */	SCSPEC,
  /* RID_TYPEDEF */	SCSPEC,
  /* RID_SHORT */	TYPESPEC,
  /* RID_INLINE */	SCSPEC,
  /* RID_VOLATILE */	TYPE_QUAL,
  /* RID_SIGNED */	TYPESPEC,
  /* RID_AUTO */	SCSPEC,
  /* RID_RESTRICT */	TYPE_QUAL,

  /* C extensions */
  /* RID_COMPLEX */	TYPESPEC,
  /* RID_THREAD */	SCSPEC,

  /* C++ */
  /* RID_FRIEND */	0,
  /* RID_VIRTUAL */	0,
  /* RID_EXPLICIT */	0,
  /* RID_EXPORT */	0,
  /* RID_MUTABLE */	0,

  /* ObjC */
  /* RID_IN */		TYPE_QUAL,
  /* RID_OUT */		TYPE_QUAL,
  /* RID_INOUT */	TYPE_QUAL,
  /* RID_BYCOPY */	TYPE_QUAL,
  /* RID_BYREF */	TYPE_QUAL,
  /* RID_ONEWAY */	TYPE_QUAL,

  /* C */
  /* RID_INT */		TYPESPEC,
  /* RID_CHAR */	TYPESPEC,
  /* RID_FLOAT */	TYPESPEC,
  /* RID_DOUBLE */	TYPESPEC,
  /* RID_VOID */	TYPESPEC,
  /* RID_ENUM */	ENUM,
  /* RID_STRUCT */	STRUCT,
  /* RID_UNION */	UNION,
  /* RID_IF */		IF,
  /* RID_ELSE */	ELSE,
  /* RID_WHILE */	WHILE,
  /* RID_DO */		DO,
  /* RID_FOR */		FOR,
  /* RID_SWITCH */	SWITCH,
  /* RID_CASE */	CASE,
  /* RID_DEFAULT */	DEFAULT,
  /* RID_BREAK */	BREAK,
  /* RID_CONTINUE */	CONTINUE,
  /* RID_RETURN */	RETURN,
  /* RID_GOTO */	GOTO,
  /* RID_SIZEOF */	SIZEOF,

  /* C extensions */
  /* RID_ASM */		ASM_KEYWORD,
  /* RID_TYPEOF */	TYPEOF,
  /* RID_ALIGNOF */	ALIGNOF,
  /* RID_ATTRIBUTE */	ATTRIBUTE,
  /* RID_VA_ARG */	VA_ARG,
  /* RID_EXTENSION */	EXTENSION,
  /* RID_IMAGPART */	IMAGPART,
  /* RID_REALPART */	REALPART,
  /* RID_LABEL */	LABEL,
  /* RID_PTRBASE */	PTR_BASE,
  /* RID_PTREXTENT */	PTR_EXTENT,
  /* RID_PTRVALUE */	PTR_VALUE,

  /* RID_CHOOSE_EXPR */			CHOOSE_EXPR,
  /* RID_TYPES_COMPATIBLE_P */		TYPES_COMPATIBLE_P,

  /* RID_FUNCTION_NAME */		FUNC_NAME,
  /* RID_PRETTY_FUNCTION_NAME */	FUNC_NAME,
  /* RID_C99_FUNCTION_NAME */		FUNC_NAME,

  /* C++ */
  /* RID_BOOL */	TYPESPEC,
  /* RID_WCHAR */	0,
  /* RID_CLASS */	0,
  /* RID_PUBLIC */	0,
  /* RID_PRIVATE */	0,
  /* RID_PROTECTED */	0,
  /* RID_TEMPLATE */	0,
  /* RID_NULL */	0,
  /* RID_CATCH */	0,
  /* RID_DELETE */	0,
  /* RID_FALSE */	0,
  /* RID_NAMESPACE */	0,
  /* RID_NEW */		0,
  /* RID_OFFSETOF */    0,
  /* RID_OPERATOR */	0,
  /* RID_THIS */	0,
  /* RID_THROW */	0,
  /* RID_TRUE */	0,
  /* RID_TRY */		0,
  /* RID_TYPENAME */	0,
  /* RID_TYPEID */	0,
  /* RID_USING */	0,

  /* casts */
  /* RID_CONSTCAST */	0,
  /* RID_DYNCAST */	0,
  /* RID_REINTCAST */	0,
  /* RID_STATCAST */	0,

  /* Objective C */
  /* RID_ID */			OBJECTNAME,
  /* RID_AT_ENCODE */		ENCODE,
  /* RID_AT_END */		END,
  /* RID_AT_CLASS */		CLASS,
  /* RID_AT_ALIAS */		ALIAS,
  /* RID_AT_DEFS */		DEFS,
  /* RID_AT_PRIVATE */		PRIVATE,
  /* RID_AT_PROTECTED */	PROTECTED,
  /* RID_AT_PUBLIC */		PUBLIC,
  /* RID_AT_PROTOCOL */		PROTOCOL,
  /* RID_AT_SELECTOR */		SELECTOR,
  /* RID_AT_THROW */		AT_THROW,
  /* RID_AT_TRY */		AT_TRY,
  /* RID_AT_CATCH */		AT_CATCH,
  /* RID_AT_FINALLY */		AT_FINALLY,
  /* RID_AT_SYNCHRONIZED */	AT_SYNCHRONIZED,
  /* RID_AT_INTERFACE */	INTERFACE,
  /* RID_AT_IMPLEMENTATION */	IMPLEMENTATION
};

static void
init_reswords (void)
{
  unsigned int i;
  tree id;
  int mask = (flag_isoc99 ? 0 : D_C89)
	      | (flag_no_asm ? (flag_isoc99 ? D_EXT : D_EXT|D_EXT89) : 0);

  if (!c_dialect_objc ())
     mask |= D_OBJC;

  ridpointers = ggc_calloc ((int) RID_MAX, sizeof (tree));
  for (i = 0; i < N_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      if (reswords[i].disable & mask)
	continue;

      id = get_identifier (reswords[i].word);
      C_RID_CODE (id) = reswords[i].rid;
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(int) reswords[i].rid] = id;
    }
}

#define NAME(type) cpp_type2name (type)

static void
yyerror (const char *msgid)
{
  c_parse_error (msgid, last_token, yylval.ttype);
}

static int
yylexname (void)
{
  tree decl;


  if (C_IS_RESERVED_WORD (yylval.ttype))
    {
      enum rid rid_code = C_RID_CODE (yylval.ttype);

      {
	/* Return the canonical spelling for this keyword.  */
	yylval.ttype = ridpointers[(int) rid_code];
	return rid_to_yy[(int) rid_code];
      }
    }

  decl = lookup_name (yylval.ttype);
  if (decl)
    {
      if (TREE_CODE (decl) == TYPE_DECL)
	return TYPENAME;
    }

  return IDENTIFIER;
}

static inline int
_yylex (void)
{
 get_next:
  last_token = c_lex (&yylval.ttype);
  switch (last_token)
    {
    case CPP_EQ:					return '=';
    case CPP_NOT:					return '!';
    case CPP_GREATER:	yylval.code = GT_EXPR;		return ARITHCOMPARE;
    case CPP_LESS:	yylval.code = LT_EXPR;		return ARITHCOMPARE;
    case CPP_PLUS:	yylval.code = PLUS_EXPR;	return '+';
    case CPP_MINUS:	yylval.code = MINUS_EXPR;	return '-';
    case CPP_MULT:	yylval.code = MULT_EXPR;	return '*';
    case CPP_DIV:	yylval.code = TRUNC_DIV_EXPR;	return '/';
    case CPP_MOD:	yylval.code = TRUNC_MOD_EXPR;	return '%';
    case CPP_AND:	yylval.code = BIT_AND_EXPR;	return '&';
    case CPP_OR:	yylval.code = BIT_IOR_EXPR;	return '|';
    case CPP_XOR:	yylval.code = BIT_XOR_EXPR;	return '^';
    case CPP_RSHIFT:	yylval.code = RSHIFT_EXPR;	return RSHIFT;
    case CPP_LSHIFT:	yylval.code = LSHIFT_EXPR;	return LSHIFT;

    case CPP_COMPL:					return '~';
    case CPP_AND_AND:					return ANDAND;
    case CPP_OR_OR:					return OROR;
    case CPP_QUERY:					return '?';
    case CPP_OPEN_PAREN:				return '(';
    case CPP_EQ_EQ:	yylval.code = EQ_EXPR;		return EQCOMPARE;
    case CPP_NOT_EQ:	yylval.code = NE_EXPR;		return EQCOMPARE;
    case CPP_GREATER_EQ:yylval.code = GE_EXPR;		return ARITHCOMPARE;
    case CPP_LESS_EQ:	yylval.code = LE_EXPR;		return ARITHCOMPARE;

    case CPP_PLUS_EQ:	yylval.code = PLUS_EXPR;	return ASSIGN;
    case CPP_MINUS_EQ:	yylval.code = MINUS_EXPR;	return ASSIGN;
    case CPP_MULT_EQ:	yylval.code = MULT_EXPR;	return ASSIGN;
    case CPP_DIV_EQ:	yylval.code = TRUNC_DIV_EXPR;	return ASSIGN;
    case CPP_MOD_EQ:	yylval.code = TRUNC_MOD_EXPR;	return ASSIGN;
    case CPP_AND_EQ:	yylval.code = BIT_AND_EXPR;	return ASSIGN;
    case CPP_OR_EQ:	yylval.code = BIT_IOR_EXPR;	return ASSIGN;
    case CPP_XOR_EQ:	yylval.code = BIT_XOR_EXPR;	return ASSIGN;
    case CPP_RSHIFT_EQ:	yylval.code = RSHIFT_EXPR;	return ASSIGN;
    case CPP_LSHIFT_EQ:	yylval.code = LSHIFT_EXPR;	return ASSIGN;

    case CPP_OPEN_SQUARE:				return '[';
    case CPP_CLOSE_SQUARE:				return ']';
    case CPP_OPEN_BRACE:				return '{';
    case CPP_CLOSE_BRACE:				return '}';
    case CPP_ELLIPSIS:					return ELLIPSIS;

    case CPP_PLUS_PLUS:					return PLUSPLUS;
    case CPP_MINUS_MINUS:				return MINUSMINUS;
    case CPP_DEREF:					return POINTSAT;
    case CPP_DOT:					return '.';

      /* The following tokens may affect the interpretation of any
	 identifiers following, if doing Objective-C.  */
    case CPP_COLON:		OBJC_NEED_RAW_IDENTIFIER (0);	return ':';
    case CPP_COMMA:		OBJC_NEED_RAW_IDENTIFIER (0);	return ',';
    case CPP_CLOSE_PAREN:	OBJC_NEED_RAW_IDENTIFIER (0);	return ')';
    case CPP_SEMICOLON:		OBJC_NEED_RAW_IDENTIFIER (0);	return ';';

    case CPP_EOF:
      return 0;

    case CPP_NAME:
      return yylexname ();

    case CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      return rid_to_yy [(int) C_RID_CODE (yylval.ttype)];

    case CPP_NUMBER:
    case CPP_CHAR:
    case CPP_WCHAR:
      return CONSTANT;

    case CPP_STRING:
    case CPP_WSTRING:
      return STRING;

    case CPP_OBJC_STRING:
      return OBJC_STRING;

      /* These tokens are C++ specific (and will not be generated
         in C mode, but let's be cautious).  */
    case CPP_SCOPE:
    case CPP_DEREF_STAR:
    case CPP_DOT_STAR:
    case CPP_MIN_EQ:
    case CPP_MAX_EQ:
    case CPP_MIN:
    case CPP_MAX:
      /* These tokens should not survive translation phase 4.  */
    case CPP_HASH:
    case CPP_PASTE:
      error ("syntax error at '%s' token", NAME(last_token));
      goto get_next;

    default:
      abort ();
    }
  /* NOTREACHED */
}

static int
yylex (void)
{
  int r;
  timevar_push (TV_LEX);
  r = _yylex();
  timevar_pop (TV_LEX);
  return r;
}

/* Function used when yydebug is set, to print a token in more detail.  */

static void
yyprint (FILE *file, int yychar, YYSTYPE yyl)
{
  tree t = yyl.ttype;

  fprintf (file, " [%s]", NAME(last_token));

  switch (yychar)
    {
    case IDENTIFIER:
    case TYPENAME:
    case OBJECTNAME:
    case TYPESPEC:
    case TYPE_QUAL:
    case SCSPEC:
    case STATIC:
      if (IDENTIFIER_POINTER (t))
	fprintf (file, " `%s'", IDENTIFIER_POINTER (t));
      break;

    case CONSTANT:
      fprintf (file, " %s", GET_MODE_NAME (TYPE_MODE (TREE_TYPE (t))));
      if (TREE_CODE (t) == INTEGER_CST)
	{
	  fputs (" ", file);
	  fprintf (file, HOST_WIDE_INT_PRINT_DOUBLE_HEX,
		   TREE_INT_CST_HIGH (t), TREE_INT_CST_LOW (t));
	}
      break;
    }
}

/* This is not the ideal place to put these, but we have to get them out
   of c-lex.c because cp/lex.c has its own versions.  */

/* Parse the file.  */
void
c_parse_file (void)
{
  yyparse ();
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  while (! global_bindings_p ())
    poplevel (0, 0, 0);
  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  finish_fname_decls ();

  if (malloced_yyss)
    {
      free (malloced_yyss);
      free (malloced_yyvs);
      malloced_yyss = 0;
    }
}

#include "gt-c-parse.h"
