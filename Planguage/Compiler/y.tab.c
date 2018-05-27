/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "proc.y" /* yacc.c:339  */

void yyerror (char const *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include "symbol.h"
#include "y.tab.h"
#include "codegen.h"
//#define SIZE_NAME 128

extern char* yytext;
extern int currentScope;
void typeCheck(int,int);
void typeErrNotFound();
void typeErrRedeclared();
void typeErrMismatch();
id* temp;

#line 85 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROCESSOR = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    FOR = 262,
    CONTINUE = 263,
    BREAK = 264,
    _REBOOT = 265,
    RETURN = 266,
    _HALT = 267,
    _SUSPEND = 268,
    INT = 269,
    REAL = 270,
    CHAR = 271,
    STRING = 272,
    STATIC = 273,
    VOID = 274,
    EQUAL = 275,
    DIFF = 276,
    GRTEQU = 277,
    LESEQU = 278,
    RAND = 279,
    ROR = 280,
    CONSTANT_REAL = 281,
    CONSTANT_CHAR = 282,
    CONSTANT_STRING = 283,
    CONSTANT_HEX = 284,
    CONSTANT_OCT = 285,
    SHL = 286,
    SHR = 287,
    SAR = 288,
    INC = 289,
    DEC = 290,
    ASSAR = 291,
    ASSHL = 292,
    ASSHR = 293,
    ASADD = 294,
    ASSUB = 295,
    ASDIV = 296,
    ASMOD = 297,
    ASMUL = 298,
    ASAND = 299,
    ASOR = 300,
    ASEOR = 301,
    CONSTANT_INT = 302,
    ID = 303
  };
#endif
/* Tokens.  */
#define PROCESSOR 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define FOR 262
#define CONTINUE 263
#define BREAK 264
#define _REBOOT 265
#define RETURN 266
#define _HALT 267
#define _SUSPEND 268
#define INT 269
#define REAL 270
#define CHAR 271
#define STRING 272
#define STATIC 273
#define VOID 274
#define EQUAL 275
#define DIFF 276
#define GRTEQU 277
#define LESEQU 278
#define RAND 279
#define ROR 280
#define CONSTANT_REAL 281
#define CONSTANT_CHAR 282
#define CONSTANT_STRING 283
#define CONSTANT_HEX 284
#define CONSTANT_OCT 285
#define SHL 286
#define SHR 287
#define SAR 288
#define INC 289
#define DEC 290
#define ASSAR 291
#define ASSHL 292
#define ASSHR 293
#define ASADD 294
#define ASSUB 295
#define ASDIV 296
#define ASMOD 297
#define ASMUL 298
#define ASAND 299
#define ASOR 300
#define ASEOR 301
#define CONSTANT_INT 302
#define ID 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "proc.y" /* yacc.c:355  */

char name[128];
struct value_and_type
{
	int type;
	char isID;
	long vali;
	double valr;
	char valc;
} vt;

#line 233 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 250 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   515

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,     2,     2,    60,    53,     2,
      49,    50,    54,    55,    66,    56,     2,    59,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    67,
      61,    65,    62,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,    64,    69,    57,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    76,    77,    78,    79,    80,    84,    86,
      88,    90,    96,    98,   100,   102,   107,   108,   109,   110,
     111,   112,   116,   118,   123,   125,   127,   129,   134,   136,
     138,   143,   145,   147,   152,   154,   156,   158,   160,   165,
     167,   169,   174,   176,   181,   183,   188,   190,   195,   197,
     202,   204,   209,   211,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   230,   231,   235,   242,   243,
     246,   248,   253,   254,   259,   260,   261,   266,   272,   273,
     276,   278,   279,   280,   281,   282,   283,   286,   287,   288,
     292,   292,   296,   297,   301,   302,   306,   307,   312,   311,
     323,   329,   330,   331,   335,   336,   337,   338,   342,   343,
     348,   347
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROCESSOR", "IF", "ELSE", "WHILE",
  "FOR", "CONTINUE", "BREAK", "_REBOOT", "RETURN", "_HALT", "_SUSPEND",
  "INT", "REAL", "CHAR", "STRING", "STATIC", "VOID", "EQUAL", "DIFF",
  "GRTEQU", "LESEQU", "RAND", "ROR", "CONSTANT_REAL", "CONSTANT_CHAR",
  "CONSTANT_STRING", "CONSTANT_HEX", "CONSTANT_OCT", "SHL", "SHR", "SAR",
  "INC", "DEC", "ASSAR", "ASSHL", "ASSHR", "ASADD", "ASSUB", "ASDIV",
  "ASMOD", "ASMUL", "ASAND", "ASOR", "ASEOR", "CONSTANT_INT", "ID", "'('",
  "')'", "'['", "']'", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'",
  "'%'", "'<'", "'>'", "'^'", "'|'", "'='", "','", "';'", "'{'", "'}'",
  "$accept", "primary_expression", "postfix_expression",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "assignment_expression", "assignment_operator", "expression",
  "declaration", "declaration_specifiers", "init_declarator_list",
  "init_declarator", "type_specifier", "direct_declarator", "statement",
  "control_statement", "compound_statement", "$@1", "block_item_list",
  "block_item", "expression_statement", "selection_statement", "$@2",
  "iteration_statement", "jump_statement", "translation_unit",
  "processor_declaration", "$@3", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,    40,
      41,    91,    93,    38,    42,    43,    45,   126,    33,    47,
      37,    60,    62,    94,   124,    61,    44,    59,   123,   125
};
# endif

#define YYPACT_NINF -98

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-98)))

#define YYTABLE_NINF -81

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,   -31,    70,   -98,   -25,   -98,   -98,   -19,   -30,     3,
       8,    46,    76,   -98,    72,   -98,   -98,   167,    93,   113,
     114,    86,    97,    98,   -14,    99,   100,   -98,   -98,   -98,
     -98,   106,   -98,   -98,   432,   432,   -98,   -98,   358,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,    -4,    58,   457,
     -98,    -5,     5,    40,   -16,   104,   119,   123,   124,   163,
     164,   -98,    65,   -98,   142,   -98,   -98,   -98,   -98,   101,
     -98,   -98,   -98,   -98,   -98,   457,   457,   313,   -98,   -98,
     -98,   -98,    67,   -98,   -98,   -98,   457,   -98,   -98,   -40,
     141,   -98,   -98,   457,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   457,   -98,   -98,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   457,
     457,   457,   457,   457,   457,   457,   457,   -98,   -98,    71,
     -98,   -46,   -98,   -98,   -39,   -28,   313,   -98,   -98,   457,
     -29,   -98,   -98,   -98,   -98,    -5,    -5,     5,     5,    40,
      40,    40,    40,   -16,   -16,   104,   119,   123,   124,   163,
     -98,   142,   -98,   374,   457,   232,   297,   407,   -98,   -98,
     -98,   -98,   140,   -98,   190,   297,   -98,   297,   -18,   -98,
     297,   -98,   -98,   297,   -98,   -98
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   108,     0,     1,   109,     0,     0,     0,
       0,     0,     0,   110,     0,    90,   111,    80,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    75,    74,
       6,     0,     4,     5,     0,     0,     3,     2,     0,    16,
      17,    18,    19,    20,    21,    96,     8,    12,    22,     0,
      24,    28,    31,    34,    39,    42,    44,    46,    48,    50,
      52,    65,     0,    94,     0,    69,    95,    86,    81,     0,
      92,    82,    83,    84,    85,     0,     0,     0,   104,   105,
      88,   106,     0,    87,    89,    68,     0,    13,    14,     0,
       0,    10,    11,     0,    60,    61,    58,    59,    56,    57,
      55,    62,    64,    63,    54,     0,    22,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    77,     0,
      70,    72,    91,    93,     0,     0,     0,   107,     7,     0,
       0,    53,    25,    26,    27,    29,    30,    32,    33,    38,
      37,    35,    36,    40,    41,    43,    45,    47,    49,    51,
      66,     0,    67,     0,     0,    98,    80,     0,    23,     9,
      71,    79,     0,    73,     0,    80,   101,    80,     0,    78,
      80,    99,   102,    80,   100,   103
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -98,   -98,   -98,   -33,   -98,   -45,    34,    38,   -59,    41,
      75,    77,    74,    79,    73,   -98,   -97,   -98,   -24,   -98,
     -98,   -98,    39,   -13,   -98,   -36,   -98,   191,   -98,   -98,
     135,   -68,   -98,   -98,   -98,   -98,   -98,   204,   -98
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,   105,    62,    63,
      64,   129,   130,    65,   131,    66,    67,    68,    17,    69,
      70,    71,    72,   175,    73,    74,     2,     3,    14
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      82,    87,    88,    30,   107,   163,   115,   116,   141,   136,
     138,   165,    32,    33,    89,     1,   106,     4,    85,   164,
      34,    35,   166,   169,     7,    90,   126,   126,     8,   160,
      91,    92,   183,    36,    37,    38,     9,   126,   126,    39,
      40,    41,    42,    43,    44,   117,   118,    93,   126,   108,
      10,   134,   135,    81,   109,   110,   149,   150,   151,   152,
     111,   112,    89,   142,   143,   144,   172,   173,   167,   140,
       5,   113,   114,     1,    11,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,    12,   168,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    18,   106,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      27,    28,    29,   104,   119,   120,    13,    32,    33,   174,
     176,   126,   127,   126,   137,    34,    35,   161,   162,   181,
      15,   182,    75,   178,   184,   145,   146,   185,    36,    37,
      38,   147,   148,    78,    39,    40,    41,    42,    43,    44,
     153,   154,    76,    77,    79,    80,    83,    84,    45,    15,
     132,    18,   121,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   122,   124,   123,   125,
     128,   139,   179,    32,    33,   180,   155,   157,   159,   156,
     170,    34,    35,   158,   133,    16,     6,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,     0,     0,     0,
      39,    40,    41,    42,    43,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    15,    18,   -80,    19,    20,
      21,    22,    23,    24,    25,    26,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    33,
       0,     0,     0,     0,     0,     0,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,     0,     0,     0,    39,    40,    41,    42,    43,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
      15,    18,     0,    19,    20,    21,    22,    23,    24,    25,
      26,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,     0,     0,     0,     0,     0,
      30,    34,    35,     0,     0,     0,     0,     0,     0,    32,
      33,     0,     0,     0,    36,    37,    38,    34,    35,     0,
      39,    40,    41,    42,    43,    44,     0,     0,     0,     0,
      36,    37,    38,     0,    45,    15,    39,    40,    41,    42,
      43,    44,    27,    28,    29,    30,     0,     0,     0,     0,
      45,     0,     0,     0,    32,    33,     0,     0,     0,     0,
       0,    30,    34,    35,     0,     0,     0,     0,     0,     0,
      32,    33,     0,     0,     0,    36,    37,    38,    34,    35,
       0,    39,    40,    41,    42,    43,    44,     0,     0,     0,
       0,    36,    37,    38,    30,     0,   171,    39,    40,    41,
      42,    43,    44,    32,    33,     0,     0,     0,     0,     0,
       0,    34,    35,     0,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,    36,    37,    38,   177,    32,    33,
      39,    40,    41,    42,    43,    44,    34,    35,     0,     0,
       0,     0,     0,     0,    30,     0,     0,     0,     0,    36,
      37,    86,     0,    32,    33,    39,    40,    41,    42,    43,
      44,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,     0,     0,     0,
      39,    40,    41,    42,    43,    44
};

static const yytype_int16 yycheck[] =
{
      24,    34,    35,    17,    49,    51,    22,    23,   105,    77,
      50,    50,    26,    27,    38,     3,    49,    48,    31,    65,
      34,    35,    50,    52,    49,    38,    66,    66,    47,   126,
      34,    35,    50,    47,    48,    49,    66,    66,    66,    53,
      54,    55,    56,    57,    58,    61,    62,    51,    66,    54,
      47,    75,    76,    67,    59,    60,   115,   116,   117,   118,
      55,    56,    86,   108,   109,   110,   163,   164,   136,    93,
       0,    31,    32,     3,    66,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    47,   139,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,     4,   139,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      14,    15,    16,    65,    20,    21,    50,    26,    27,   165,
     166,    66,    67,    66,    67,    34,    35,    66,    67,   175,
      68,   177,    49,   167,   180,   111,   112,   183,    47,    48,
      49,   113,   114,    67,    53,    54,    55,    56,    57,    58,
     119,   120,    49,    49,    67,    67,    67,    67,    67,    68,
      69,     4,    53,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    63,    24,    64,    25,
      48,    50,    52,    26,    27,     5,   121,   123,   125,   122,
     161,    34,    35,   124,    69,    14,     2,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    67,    68,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,     4,    -1,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,
      17,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    -1,    -1,    -1,    47,    48,    49,    34,    35,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      47,    48,    49,    -1,    67,    68,    53,    54,    55,    56,
      57,    58,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      67,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,
      -1,    17,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    47,    48,    49,    34,    35,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    47,    48,    49,    17,    -1,    52,    53,    54,    55,
      56,    57,    58,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    26,    27,
      53,    54,    55,    56,    57,    58,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    26,    27,    53,    54,    55,    56,    57,
      58,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   106,   107,    48,     0,   107,    49,    47,    66,
      47,    66,    47,    50,   108,    68,    97,    98,     4,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    26,    27,    34,    35,    47,    48,    49,    53,
      54,    55,    56,    57,    58,    67,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    88,    89,    90,    93,    95,    96,    97,    99,
     100,   101,   102,   104,   105,    49,    49,    49,    67,    67,
      67,    67,    88,    67,    67,    93,    49,    73,    73,    88,
      93,    34,    35,    51,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    65,    87,    73,    75,    54,    59,
      60,    55,    56,    31,    32,    22,    23,    61,    62,    20,
      21,    53,    63,    64,    24,    25,    66,    67,    48,    91,
      92,    94,    69,   100,    88,    88,   101,    67,    50,    50,
      88,    86,    75,    75,    75,    76,    76,    77,    77,    78,
      78,    78,    78,    79,    79,    80,    81,    82,    83,    84,
      86,    66,    67,    51,    65,    50,    50,   101,    75,    52,
      92,    52,    86,    86,    95,   103,    95,    50,    88,    52,
       5,    95,    95,    50,    95,    95
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    71,    71,    71,    71,    71,    72,    72,
      72,    72,    73,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    75,    75,    76,    76,    76,    76,    77,    77,
      77,    78,    78,    78,    79,    79,    79,    79,    79,    80,
      80,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    88,    88,    89,    90,    90,
      91,    91,    92,    92,    93,    93,    93,    94,    94,    94,
      95,    95,    95,    95,    95,    95,    95,    96,    96,    96,
      98,    97,    99,    99,   100,   100,   101,   101,   103,   102,
     102,   104,   104,   104,   105,   105,   105,   105,   106,   106,
     108,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     1,     4,
       2,     2,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     4,     3,
       0,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       0,     4,     1,     2,     1,     1,     1,     2,     0,     6,
       7,     5,     6,     7,     2,     2,     2,     3,     1,     2,
       0,    11
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 64 "proc.y" /* yacc.c:1646  */
    {
			temp=findID((yyvsp[0].name));
			if(temp)
			{
			(yyval.vt).type=temp->type;
			(yyval.vt).isID=1;
			}
			else
			{
			typeErrNotFound();
			}
		}
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 85 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 87 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[-3].vt);}
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 89 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[-1].vt);gen2OP("INC",(yyvsp[-1].vt).type);}
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 91 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[-1].vt);gen2OP("DEC",(yyvsp[-1].vt).type);}
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 97 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 99 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 101 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 103 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);gen2OP_1((yyvsp[0].vt).type);}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 107 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("AND");}
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 108 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("MUL");}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 109 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("ADD");}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 110 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("SUB");}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 111 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("NOT");}
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 112 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("?");}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 117 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 119 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[-2].vt);}
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 124 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 126 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("MUL",(yyvsp[-2].vt).type);}
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 128 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("DIV",(yyvsp[-2].vt).type);}
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 130 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("DIV",(yyvsp[-2].vt).type);}
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 135 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 137 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("ADD",(yyvsp[-2].vt).type);}
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 139 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("SUB",(yyvsp[-2].vt).type);}
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 144 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 146 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("SHL",(yyvsp[-2].vt).type);}
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 148 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("SHR",(yyvsp[-2].vt).type);}
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 153 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 155 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 157 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 159 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 161 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 166 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 168 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 170 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 175 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 177 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("AND",(yyvsp[-2].vt).type);}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 182 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 184 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("XOR",(yyvsp[-2].vt).type);}
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 189 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 191 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);gen2OP("OR",(yyvsp[-2].vt).type);}
#line 1792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 196 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 198 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 203 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 205 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 210 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 212 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt);}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 236 "proc.y" /* yacc.c:1646  */
    {
		typeCheck((yyvsp[-2].vt).type,(yyvsp[-1].vt).type);
		setMetaType((yyvsp[-2].vt).type);
		}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 242 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 243 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 247 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 249 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt).type,(yyvsp[0].vt).type);(yyval.vt)=(yyvsp[-2].vt).type>(yyvsp[0].vt).type?(yyvsp[-2].vt):(yyvsp[0].vt);}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 253 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_META;}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 254 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 259 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_CHAR;}
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 260 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_REAL;}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 261 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_INT;}
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 267 "proc.y" /* yacc.c:1646  */
    {
		temp=addID(TYP_META,(yyvsp[0].name));
		if(!temp)
			typeErrRedeclared();
		}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 272 "proc.y" /* yacc.c:1646  */
    {if((yyvsp[-1].vt).type!=TYP_INT) typeErrMismatch();}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 286 "proc.y" /* yacc.c:1646  */
    {gen2(_HALT);}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 287 "proc.y" /* yacc.c:1646  */
    {gen2(_REBOOT);}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 288 "proc.y" /* yacc.c:1646  */
    {gen2(_SUSPEND);}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 292 "proc.y" /* yacc.c:1646  */
    {currentScope++;}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 292 "proc.y" /* yacc.c:1646  */
    {leaveScope();}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 312 "proc.y" /* yacc.c:1646  */
    {
	//here is the branch operation section
	genFlagRelated("JMPC <flag> ",flagMarker);
	fStackPush(flagMarker,TYP_BRANCH_FALSE);
	flagMarker++;
	}
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 319 "proc.y" /* yacc.c:1646  */
    {
	//recover the flag
	genFlagRelated("#",fStackPop());
	}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 348 "proc.y" /* yacc.c:1646  */
    {
		//check first
		temp = addID(TYP_PROC,(yyvsp[-7].name));
		if(!temp)
			typeErrRedeclared();
		genPHeader((yyvsp[-7].name),(yyvsp[-5].vt).vali,(yyvsp[-3].vt).vali,(yyvsp[-1].vt).vali);
		gen(".code;start\n");
		}
#line 1970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 357 "proc.y" /* yacc.c:1646  */
    {
		gen(";ended");
		}
#line 1978 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1982 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 362 "proc.y" /* yacc.c:1906  */

#include <stdio.h>
//#include "symbol.h"
//extern char yytext[];
extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
void typeCheck(int l,int r)
{
printf("$%d#%d$",l,r);
if(l==TYP_META || r==TYP_META || l==r) return;
	printf("type checking failure:%d/%d/",l,r);
	yyerror(yytext);
	exit(-1);
}

void typeErrNotFound()
{
	printf("type error : cannot find declaration.");
	yyerror(yytext);
	exit(-1);
}
void typeErrRedeclared()
{
	printf("type error : identifier name override.");
	yyerror(yytext);
	exit(-1);
}
void typeErrMismatch()
{
	printf("type error : type mismatch.");
	yyerror(yytext);
	exit(-1);
}
