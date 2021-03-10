/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "y.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char scope[MAX_STR] = "STRUCTURES";
int var_in_func = 0;

extern FILE* yyin;
extern char* yytext;
extern int yylineno;

/* Line 371 of yacc.c  */
#line 82 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EVAL = 258,
     ID = 259,
     TIP = 260,
     VARCONST = 261,
     SIR = 262,
     ATRIBUIRE = 263,
     DIMENSIUNE = 264,
     NUMAR = 265,
     STRUCT = 266,
     SELECTOR = 267,
     STRUCTURI = 268,
     FUNCTII = 269,
     GLOBAL = 270,
     MAIN = 271,
     IF = 272,
     ELSE = 273,
     WHILE = 274,
     FOR = 275,
     FOR_START = 276,
     FOR_STOP = 277,
     FOR_STEP = 278,
     FUNC = 279,
     RETURN = 280,
     ADD = 281,
     SUB = 282,
     DIV = 283,
     MUL = 284,
     AND = 285,
     OR = 286,
     XOR = 287,
     NOT = 288,
     EQ = 289,
     GT = 290,
     GE = 291,
     LT = 292,
     LE = 293,
     PRINT = 294,
     CONCAT = 295,
     COPY = 296
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 15 "y.y"

	int intval;
	float numval;
	char charval;
	char* strval;

	struct Symbol* symbol;


/* Line 387 of yacc.c  */
#line 176 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 204 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   696

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNRULES -- Number of states.  */
#define YYNSTATES  268

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    49,    53,     2,     2,     2,
      42,    43,     2,     2,    51,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    47,    50,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    12,    17,    21,    26,    30,    35,
      39,    44,    47,    51,    58,    64,    70,    74,    79,    82,
      86,    88,    91,   103,   114,   127,   139,   144,   150,   152,
     156,   158,   162,   166,   171,   174,   178,   181,   185,   189,
     195,   200,   209,   211,   215,   217,   219,   222,   224,   226,
     228,   230,   234,   236,   238,   240,   242,   244,   246,   250,
     254,   258,   262,   266,   270,   274,   278,   282,   286,   290,
     294,   298,   301,   303,   306,   309,   312,   315,   318,   321,
     324,   327,   330,   332,   334,   336,   341,   345,   350,   354,
     360,   364,   368,   374,   379,   383,   387,   394,   401,   409,
     415,   427,   437,   447,   455,   463
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    56,    57,    58,    59,    -1,    13,    46,
      47,    -1,    13,    46,    60,    47,    -1,    14,    46,    47,
      -1,    14,    46,    64,    47,    -1,    15,    46,    47,    -1,
      15,    46,    70,    47,    -1,    16,    46,    47,    -1,    16,
      46,    75,    47,    -1,    61,    48,    -1,    60,    61,    48,
      -1,    11,     4,    46,    63,    64,    47,    -1,    11,     4,
      46,    63,    47,    -1,    11,     4,    46,    64,    47,    -1,
      49,     4,     4,    -1,    49,     4,     9,     4,    -1,    71,
      48,    -1,    63,    71,    48,    -1,    65,    -1,    64,    65,
      -1,    24,     5,     4,    42,    43,    46,    75,    25,    73,
      48,    47,    -1,    24,     5,     4,    42,    43,    46,    25,
      73,    48,    47,    -1,    24,     5,     4,    42,    68,    43,
      46,    75,    25,    73,    48,    47,    -1,    24,     5,     4,
      42,    68,    43,    46,    25,    73,    48,    47,    -1,    50,
       4,    42,    43,    -1,    50,     4,    42,    67,    43,    -1,
      73,    -1,    67,    51,    73,    -1,    69,    -1,    68,    51,
      69,    -1,     6,     5,     4,    -1,     6,     5,     9,     4,
      -1,    71,    48,    -1,    70,    71,    48,    -1,    62,    48,
      -1,    70,    62,    48,    -1,     6,     5,     4,    -1,     6,
       5,     4,     8,    73,    -1,     6,     5,     9,     4,    -1,
       6,     5,     9,     4,     8,    44,    72,    45,    -1,    73,
      -1,    72,    51,    73,    -1,     7,    -1,    10,    -1,    52,
      10,    -1,     4,    -1,    80,    -1,    81,    -1,    66,    -1,
      53,    74,    53,    -1,     4,    -1,    10,    -1,     7,    -1,
      80,    -1,    81,    -1,    66,    -1,    42,    74,    43,    -1,
      74,    26,    74,    -1,    74,    27,    74,    -1,    74,    29,
      74,    -1,    74,    28,    74,    -1,    74,    34,    74,    -1,
      74,    35,    74,    -1,    74,    37,    74,    -1,    74,    36,
      74,    -1,    74,    38,    74,    -1,    74,    30,    74,    -1,
      74,    31,    74,    -1,    74,    32,    74,    -1,    33,    74,
      -1,    76,    -1,    75,    76,    -1,    77,    48,    -1,    78,
      48,    -1,    71,    48,    -1,    61,    48,    -1,    62,    48,
      -1,    79,    48,    -1,    66,    48,    -1,    82,    48,    -1,
      83,    -1,    84,    -1,    85,    -1,     3,    42,    73,    43,
      -1,    39,    42,    43,    -1,    39,    42,    73,    43,    -1,
       4,     8,    73,    -1,     4,     8,    44,    72,    45,    -1,
      80,     8,    73,    -1,    81,     8,    73,    -1,    81,     8,
      44,    72,    45,    -1,     4,    44,    73,    45,    -1,     4,
      12,     4,    -1,     4,    12,    80,    -1,    40,    42,     4,
      51,    73,    43,    -1,    41,    42,     4,    51,    73,    43,
      -1,    17,    42,    73,    43,    46,    75,    47,    -1,    17,
      42,    73,    43,    48,    -1,    17,    42,    73,    43,    46,
      75,    47,    18,    46,    75,    47,    -1,    17,    42,    73,
      43,    46,    75,    47,    18,    48,    -1,    17,    42,    73,
      43,    48,    18,    46,    75,    47,    -1,    17,    42,    73,
      43,    48,    18,    48,    -1,    19,    42,    73,    43,    46,
      75,    47,    -1,    20,    42,    21,     8,    73,    51,    22,
       8,    73,    51,    23,     8,    73,    43,    46,    75,    47,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    64,    64,    73,    76,    81,    84,    89,    92,    97,
      98,   102,   103,   106,   126,   147,   170,   187,   207,   208,
     212,   213,   216,   248,   280,   314,   350,   360,   372,   378,
     386,   394,   404,   426,   452,   453,   454,   455,   458,   481,
     506,   529,   556,   562,   570,   582,   592,   602,   611,   616,
     621,   626,   633,   642,   652,   664,   669,   674,   679,   685,
     693,   701,   709,   717,   725,   734,   742,   750,   758,   766,
     774,   782,   793,   794,   797,   798,   799,   800,   801,   802,
     803,   806,   807,   808,   809,   813,   823,   827,   834,   845,
     863,   876,   882,   898,   911,   923,   939,   952,   967,   972,
     977,   982,   987,   992,   999,  1006
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EVAL", "ID", "TIP", "VARCONST", "SIR",
  "ATRIBUIRE", "DIMENSIUNE", "NUMAR", "STRUCT", "SELECTOR", "STRUCTURI",
  "FUNCTII", "GLOBAL", "MAIN", "IF", "ELSE", "WHILE", "FOR", "FOR_START",
  "FOR_STOP", "FOR_STEP", "FUNC", "RETURN", "ADD", "SUB", "DIV", "MUL",
  "AND", "OR", "XOR", "NOT", "EQ", "GT", "GE", "LT", "LE", "PRINT",
  "CONCAT", "COPY", "'('", "')'", "'['", "']'", "'{'", "'}'", "';'", "'#'",
  "'~'", "','", "'-'", "'$'", "$accept", "limbaj", "blocStructuri",
  "blocFunctii", "blocGlobal", "blocMain", "listaStructuri",
  "constructieStruct", "declarareStruct", "listaVar", "listaFunctii",
  "declarareFunctie", "apelFunctie", "listaParam", "declarareParam",
  "parametru", "listaDeclarari", "declarareVar", "listaValori", "valoare",
  "expresie", "blocCod", "linieCod", "evaluare", "printare", "asignare",
  "accesArray", "accesStruct", "controlString", "controlIfElse",
  "controlWhile", "controlFor", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,    40,    41,    91,    93,   123,   125,    59,    35,
     126,    44,    45,    36
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    65,    66,    66,    67,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    71,    71,
      71,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    78,    78,    79,    79,
      79,    79,    79,    80,    81,    81,    82,    82,    83,    83,
      83,    83,    83,    83,    84,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     4,     3,     4,     3,     4,     3,
       4,     2,     3,     6,     5,     5,     3,     4,     2,     3,
       1,     2,    11,    10,    12,    11,     4,     5,     1,     3,
       1,     3,     3,     4,     2,     3,     2,     3,     3,     5,
       4,     8,     1,     3,     1,     1,     2,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     4,     3,     4,     3,     5,
       3,     3,     5,     4,     3,     3,     6,     6,     7,     5,
      11,     9,     9,     7,     7,    17
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     4,     0,    11,     0,
       5,     0,    20,     0,     0,     2,     0,    12,     0,     6,
      21,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     8,     0,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     9,     0,     0,
       0,     0,     0,     0,    72,     0,     0,     0,     0,     0,
       0,    82,    83,    84,    14,     0,     0,    15,    18,     0,
      38,     0,    16,     0,    37,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    78,    80,
      76,    10,    73,    74,    75,    79,     0,     0,    81,    13,
      19,     0,     0,     0,    30,     0,    40,    17,    47,    44,
      45,     0,     0,    50,     0,    48,    49,     0,    88,    94,
      95,     0,     0,     0,     0,    86,     0,     0,     0,     0,
      90,     0,    91,     0,     0,     0,     0,    39,     0,    46,
      52,    54,    53,     0,     0,    57,     0,    55,    56,    85,
       0,    42,    93,     0,     0,     0,    87,     0,     0,    26,
       0,    28,     0,    32,     0,     0,     0,     0,    31,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    89,     0,     0,    99,     0,
       0,     0,     0,    27,     0,    92,    33,     0,     0,     0,
       0,     0,    58,    59,    60,    62,    61,    68,    69,    70,
      63,    64,    66,    65,    67,    43,     0,     0,     0,     0,
      96,    97,    29,     0,     0,     0,     0,    41,    98,     0,
     103,   104,     0,    23,     0,     0,     0,     0,     0,     0,
      22,    25,     0,     0,   101,   102,     0,    24,     0,     0,
     100,     0,     0,     0,     0,     0,     0,   105
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,    14,    25,    10,    59,    60,    38,
      21,    22,   123,   170,   113,   114,    35,    62,   160,   161,
     156,    63,    64,    65,    66,    67,   125,   126,    70,    71,
      72,    73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -144
static const yytype_int16 yypact[] =
{
       4,    30,    84,    16,     0,  -144,    65,   104,    93,  -144,
      17,    75,   -16,    88,   116,    95,  -144,    96,  -144,   160,
    -144,   -14,  -144,    -3,   122,  -144,    12,  -144,   165,  -144,
    -144,   171,  -144,   194,   151,     3,   153,   247,    57,   -10,
     158,   163,    51,    70,  -144,  -144,   164,   166,  -144,   175,
      59,   176,   177,   180,   181,   182,   183,  -144,   209,   172,
     196,   197,   198,   334,  -144,   200,   204,   206,   222,   223,
     207,  -144,  -144,  -144,  -144,    46,   208,  -144,  -144,    -4,
     249,   257,  -144,   258,  -144,  -144,    76,     9,   259,    76,
      76,    76,   244,    25,   264,   265,   228,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,    76,    38,  -144,  -144,
    -144,   266,   226,   -36,  -144,    76,   267,  -144,    -6,  -144,
    -144,   263,    85,  -144,   231,  -144,  -144,    76,  -144,   233,
    -144,   234,   237,   239,   275,  -144,   241,   242,   248,    62,
    -144,    76,  -144,   162,   388,   246,   279,  -144,   251,  -144,
      -6,  -144,  -144,    85,    85,  -144,   627,  -144,  -144,  -144,
      86,  -144,  -144,    52,   254,    76,  -144,    76,    76,  -144,
      14,  -144,   112,  -144,   297,    76,   406,   446,  -144,    76,
     658,   640,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,  -144,  -144,    76,   338,   284,   338,
     253,   262,   268,  -144,    76,  -144,  -144,   261,    76,    76,
     458,   113,  -144,   150,   150,   384,   384,  -144,  -144,  -144,
     178,   178,   178,   178,   178,  -144,   498,   144,   510,   285,
    -144,  -144,  -144,   270,   283,   287,    76,  -144,   288,   338,
    -144,  -144,   302,  -144,   271,   286,   291,   147,   550,    76,
    -144,  -144,   296,   338,  -144,  -144,   281,  -144,   562,   289,
    -144,   340,    76,   303,   304,   338,   602,  -144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,  -144,  -144,  -144,  -144,   157,    71,  -144,
      82,   -17,    50,  -144,  -144,   210,  -144,    98,  -136,   -66,
     441,  -143,   -51,  -144,  -144,  -144,   -37,   137,  -144,  -144,
    -144,  -144
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      68,   176,   111,    31,    30,   172,    88,   145,    19,    31,
      19,     8,   102,   118,    19,   146,   119,     1,    31,   120,
     124,   128,    30,   131,   132,   133,    68,   136,     8,   118,
       6,    20,   119,    29,   210,   120,    19,    77,    89,   112,
     140,   142,   118,   211,    32,   119,    33,     9,   120,   147,
      45,   130,    33,   127,   226,    80,   228,   203,    30,    58,
      81,   121,   122,    31,    16,   204,   118,    87,   135,   119,
      19,    88,   120,   171,    82,    58,     4,   121,   122,    83,
     118,    19,   141,   119,     5,   157,   120,    61,    58,   150,
     121,   122,   151,   109,    34,   152,   248,    15,   197,   200,
     198,   201,   202,    89,    74,   169,    46,    68,    39,   207,
     258,    12,    58,    61,   121,   122,   157,   157,   153,    13,
      75,    36,   266,    18,    40,   102,    58,   154,   121,   122,
     225,   195,    24,    47,    23,    58,    76,   196,   232,    68,
      68,    26,   234,   235,    27,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   205,   237,   102,
      68,    11,    68,   196,   196,    28,   173,    17,    37,    41,
     246,   174,   155,    68,    69,   102,    42,   102,   184,   185,
     186,   187,   188,   256,   189,   190,   191,   192,   193,    68,
     239,    68,   240,   253,    61,   254,   263,   102,    43,    44,
      69,    48,    68,   155,   155,    79,    78,   102,   186,   187,
     188,    68,    84,    96,    85,   102,    68,    86,    90,    91,
      97,    68,    92,    93,    94,    95,    61,    61,    68,    68,
     106,   107,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,    98,    99,   100,    61,   103,    61,
      49,    50,   104,    31,   105,   108,   110,   115,     8,   158,
      61,   116,   117,   129,    51,   134,    52,    53,   137,   138,
     139,   143,   144,   149,   159,   148,    61,    89,    61,   162,
     163,    69,   164,   165,   166,   111,    54,    55,    56,    61,
     158,   158,   177,   167,    57,   179,    33,    58,    61,   168,
     199,   206,   227,    61,   229,   230,   247,   242,    61,   233,
     249,   231,   261,    69,    69,    61,    61,   243,   250,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   244,   259,   251,    69,   245,    69,    49,    50,   252,
      31,    49,    50,   257,    31,     8,   264,    69,   262,     8,
     265,    51,     0,    52,    53,    51,   178,    52,    53,     0,
       0,     0,     0,    69,     0,    69,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    56,    69,    54,    55,    56,
       0,   101,     0,    33,    58,    69,     0,    33,    58,     0,
      69,    49,    50,     0,    31,    69,     0,     0,     0,     8,
       0,     0,    69,    69,     0,    51,     0,    52,    53,    49,
      50,     0,    31,   175,   186,   187,   188,     8,   189,   190,
     191,   192,   193,    51,     0,    52,    53,    54,    55,    56,
       0,   208,     0,     0,     0,     0,     0,    33,    58,     0,
       0,     0,     0,     0,     0,    54,    55,    56,     0,    49,
      50,     0,    31,     0,     0,    33,    58,     8,     0,     0,
       0,    49,    50,    51,    31,    52,    53,     0,     0,     8,
       0,   209,     0,     0,     0,    51,     0,    52,    53,     0,
       0,     0,     0,   236,     0,    54,    55,    56,     0,     0,
       0,     0,     0,     0,     0,    33,    58,    54,    55,    56,
       0,    49,    50,     0,    31,     0,     0,    33,    58,     8,
       0,     0,     0,    49,    50,    51,    31,    52,    53,     0,
       0,     8,     0,     0,     0,     0,     0,    51,     0,    52,
      53,     0,     0,     0,     0,     0,     0,    54,    55,    56,
       0,     0,     0,     0,     0,   238,     0,    33,    58,    54,
      55,    56,     0,    49,    50,     0,    31,   241,     0,    33,
      58,     8,     0,     0,     0,    49,    50,    51,    31,    52,
      53,     0,     0,     8,     0,     0,     0,     0,     0,    51,
       0,    52,    53,     0,     0,     0,     0,     0,     0,    54,
      55,    56,     0,     0,   180,   181,     0,   255,     0,    33,
      58,    54,    55,    56,     0,    49,    50,     0,    31,   260,
       0,    33,    58,     8,     0,     0,     0,     0,     0,    51,
       0,    52,    53,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,     0,     0,     0,     0,     0,
       0,    54,    55,    56,     0,     0,     0,     0,     0,   267,
       0,    33,    58,   182,   183,   184,   185,   186,   187,   188,
       0,   189,   190,   191,   192,   193,   182,   183,   184,   185,
     186,   187,   188,     0,   189,   190,   191,   192,   193,     0,
     194,     0,     0,   212,   182,   183,   184,   185,   186,   187,
     188,     0,   189,   190,   191,   192,   193
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-144)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      37,   144,     6,     6,    21,   141,    12,    43,    24,     6,
      24,    11,    63,     4,    24,    51,     7,    13,     6,    10,
      86,    87,    39,    89,    90,    91,    63,    93,    11,     4,
      14,    47,     7,    47,   177,    10,    24,    47,    44,    43,
     106,   107,     4,   179,    47,     7,    49,    47,    10,   115,
      47,    88,    49,    44,   197,     4,   199,    43,    75,    50,
       9,    52,    53,     6,    47,    51,     4,     8,    43,     7,
      24,    12,    10,   139,     4,    50,    46,    52,    53,     9,
       4,    24,    44,     7,     0,   122,    10,    37,    50,     4,
      52,    53,     7,    47,    23,    10,   239,     4,    46,   165,
      48,   167,   168,    44,    47,    43,    35,   144,    26,   175,
     253,    46,    50,    63,    52,    53,   153,   154,    33,    15,
      38,    23,   265,    48,    26,   176,    50,    42,    52,    53,
     196,    45,    16,    35,    46,    50,    38,    51,   204,   176,
     177,    46,   208,   209,    48,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,    45,    45,   210,
     197,     4,   199,    51,    51,     5,     4,    10,    46,     4,
     236,     9,   122,   210,    37,   226,     5,   228,    28,    29,
      30,    31,    32,   249,    34,    35,    36,    37,    38,   226,
      46,   228,    48,    46,   144,    48,   262,   248,     4,    48,
      63,    48,   239,   153,   154,    42,    48,   258,    30,    31,
      32,   248,    48,     4,    48,   266,   253,    42,    42,    42,
      48,   258,    42,    42,    42,    42,   176,   177,   265,   266,
       8,     8,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,    48,    48,    48,   197,    48,   199,
       3,     4,    48,     6,    48,    48,    48,     8,    11,   122,
     210,     4,     4,     4,    17,    21,    19,    20,     4,     4,
      42,     5,    46,    10,    43,     8,   226,    44,   228,    45,
      43,   144,    43,     8,    43,     6,    39,    40,    41,   239,
     153,   154,    46,    51,    47,    44,    49,    50,   248,    51,
      46,     4,    18,   253,    51,    43,    18,    22,   258,    48,
       8,    43,    23,   176,   177,   265,   266,    47,    47,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,    48,    51,    47,   197,    48,   199,     3,     4,    48,
       6,     3,     4,    47,     6,    11,    43,   210,     8,    11,
      46,    17,    -1,    19,    20,    17,   146,    19,    20,    -1,
      -1,    -1,    -1,   226,    -1,   228,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,   239,    39,    40,    41,
      -1,    47,    -1,    49,    50,   248,    -1,    49,    50,    -1,
     253,     3,     4,    -1,     6,   258,    -1,    -1,    -1,    11,
      -1,    -1,   265,   266,    -1,    17,    -1,    19,    20,     3,
       4,    -1,     6,    25,    30,    31,    32,    11,    34,    35,
      36,    37,    38,    17,    -1,    19,    20,    39,    40,    41,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,     3,
       4,    -1,     6,    -1,    -1,    49,    50,    11,    -1,    -1,
      -1,     3,     4,    17,     6,    19,    20,    -1,    -1,    11,
      -1,    25,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    25,    -1,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    39,    40,    41,
      -1,     3,     4,    -1,     6,    -1,    -1,    49,    50,    11,
      -1,    -1,    -1,     3,     4,    17,     6,    19,    20,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    49,    50,    39,
      40,    41,    -1,     3,     4,    -1,     6,    47,    -1,    49,
      50,    11,    -1,    -1,    -1,     3,     4,    17,     6,    19,
      20,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    -1,    -1,   153,   154,    -1,    47,    -1,    49,
      50,    39,    40,    41,    -1,     3,     4,    -1,     6,    47,
      -1,    49,    50,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    19,    20,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    49,    50,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    35,    36,    37,    38,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    35,    36,    37,    38,    -1,
      53,    -1,    -1,    43,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    35,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    55,    56,    46,     0,    14,    57,    11,    47,
      60,    61,    46,    15,    58,     4,    47,    61,    48,    24,
      47,    64,    65,    46,    16,    59,    46,    48,     5,    47,
      65,     6,    47,    49,    62,    70,    71,    46,    63,    64,
      71,     4,     5,     4,    48,    47,    62,    71,    48,     3,
       4,    17,    19,    20,    39,    40,    41,    47,    50,    61,
      62,    66,    71,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    47,    64,    71,    47,    48,    42,
       4,     9,     4,     9,    48,    48,    42,     8,    12,    44,
      42,    42,    42,    42,    42,    42,     4,    48,    48,    48,
      48,    47,    76,    48,    48,    48,     8,     8,    48,    47,
      48,     6,    43,    68,    69,     8,     4,     4,     4,     7,
      10,    52,    53,    66,    73,    80,    81,    44,    73,     4,
      80,    73,    73,    73,    21,    43,    73,     4,     4,    42,
      73,    44,    73,     5,    46,    43,    51,    73,     8,    10,
       4,     7,    10,    33,    42,    66,    74,    80,    81,    43,
      72,    73,    45,    43,    43,     8,    43,    51,    51,    43,
      67,    73,    72,     4,     9,    25,    75,    46,    69,    44,
      74,    74,    26,    27,    28,    29,    30,    31,    32,    34,
      35,    36,    37,    38,    53,    45,    51,    46,    48,    46,
      73,    73,    73,    43,    51,    45,     4,    73,    25,    25,
      75,    72,    43,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    73,    75,    18,    75,    51,
      43,    43,    73,    48,    73,    73,    25,    45,    47,    46,
      48,    47,    22,    47,    48,    48,    73,    18,    75,     8,
      47,    47,    48,    46,    48,    47,    73,    47,    75,    51,
      47,    23,     8,    73,    43,    46,    75,    47
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

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
/* Line 1792 of yacc.c  */
#line 64 "y.y"
    {
	// TODO: construieste blocul de cod

	printf("program corect sintactic\n");
	print_symbol_table();
	}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 73 "y.y"
    {
		update_scope(scope, "FUNCTIONS");
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 76 "y.y"
    {
		update_scope(scope, "FUNCTIONS");
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 81 "y.y"
    {
		update_scope(scope, "GLOBAL");
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 84 "y.y"
    {
		update_scope(scope, "GLOBAL");
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 89 "y.y"
    {
		update_scope(scope, "MAIN");
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 92 "y.y"
    {
		update_scope(scope, "MAIN");
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 106 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(2) - (6)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(2) - (6)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(2) - (6)].strval), IS_STRUCT, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_STRUCT, symbol);

		update_symbol_scope("STRUCTURES", (yyvsp[(2) - (6)].strval), IS_VARCONST);
		update_symbol_scope("STRUCTURES", (yyvsp[(2) - (6)].strval), IS_FUNC);
		update_temp_scope((yyvsp[(2) - (6)].strval));
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 126 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(2) - (5)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(2) - (5)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(2) - (5)].strval), IS_STRUCT, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_STRUCT, symbol);

		update_symbol_scope("STRUCTURES", (yyvsp[(2) - (5)].strval), IS_VARCONST);
		update_symbol_scope("STRUCTURES", (yyvsp[(2) - (5)].strval), IS_FUNC);
		update_temp_scope((yyvsp[(2) - (5)].strval));
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 147 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(2) - (5)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(2) - (5)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(2) - (5)].strval), IS_STRUCT, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_STRUCT, symbol);

		update_symbol_scope("STRUCTURES", (yyvsp[(2) - (5)].strval), IS_VARCONST);
		update_symbol_scope("STRUCTURES", (yyvsp[(2) - (5)].strval), IS_FUNC);
		update_temp_scope((yyvsp[(2) - (5)].strval));
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 170 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (3)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(3) - (3)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (3)].strval), IS_VAR, TYPE_STRUCT, DIM_UNI, scope, (yyvsp[(2) - (3)].strval), 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_VARCONST, symbol);
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 187 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(4) - (4)].strval), MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size((yyvsp[(3) - (4)].intval), MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(4) - (4)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(4) - (4)].strval), IS_VAR, TYPE_STRUCT, DIM_ARR, scope, (yyvsp[(2) - (4)].strval), 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, (yyvsp[(3) - (4)].intval), NONE_E
			);
		add_symbol(IS_VARCONST, symbol);
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 216 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (11)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(3) - (11)].strval), scope, IS_FUNC, 0, NONE_PT);
		check_value(0, (yyvsp[(3) - (11)].strval), (yyvsp[(2) - (11)].strval), (yyvsp[(9) - (11)].symbol));
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int((yyvsp[(2) - (11)].strval));

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (11)].strval), IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);

		update_symbol_scope("FUNCTIONS", (yyvsp[(3) - (11)].strval), IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, (yyvsp[(3) - (11)].strval));
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free((yyvsp[(9) - (11)].symbol));
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 248 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (10)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(3) - (10)].strval), scope, IS_FUNC, 0, NONE_PT);
		check_value(0, (yyvsp[(3) - (10)].strval), (yyvsp[(2) - (10)].strval), (yyvsp[(8) - (10)].symbol));
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int((yyvsp[(2) - (10)].strval));

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (10)].strval), IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);

		update_symbol_scope("FUNCTIONS", (yyvsp[(3) - (10)].strval), IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, (yyvsp[(3) - (10)].strval));
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free((yyvsp[(8) - (10)].symbol));
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 280 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (12)].strval), MAX_ID);
		check_value(0, (yyvsp[(3) - (12)].strval), (yyvsp[(2) - (12)].strval), (yyvsp[(10) - (12)].symbol));
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int((yyvsp[(2) - (12)].strval));
		int n_params = (yyvsp[(5) - (12)].symbol)->n_params;
		char paramtypes[MAX_PARAMS][MAX_TYPE] = {0}; copy_params(paramtypes, (yyvsp[(5) - (12)].symbol)->paramtypes, n_params);

		check_duplicate((yyvsp[(3) - (12)].strval), scope, IS_FUNC, n_params, paramtypes);
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (12)].strval), IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, n_params, NONE_PV, paramtypes, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);

		update_symbol_scope("FUNCTIONS", (yyvsp[(3) - (12)].strval), IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, (yyvsp[(3) - (12)].strval));
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free((yyvsp[(5) - (12)].symbol)); free((yyvsp[(10) - (12)].symbol));
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 314 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (11)].strval), MAX_ID);
		check_value(0, (yyvsp[(3) - (11)].strval), (yyvsp[(2) - (11)].strval), (yyvsp[(9) - (11)].symbol));
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica d	aca valoarea din dreapta = are acelasi tip ca var din stanga =

		int type = get_type_int((yyvsp[(2) - (11)].strval));
		int n_params = (yyvsp[(5) - (11)].symbol)->n_params;
		char paramtypes[MAX_PARAMS][MAX_TYPE] = {0}; copy_params(paramtypes, (yyvsp[(5) - (11)].symbol)->paramtypes, n_params);

		check_duplicate((yyvsp[(3) - (11)].strval), scope, IS_FUNC, n_params, paramtypes);
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (11)].strval), IS_FUNC, type, 0, scope, NONE_S, 0, 0, 0, NONE_S, n_params, NONE_PV, paramtypes, 0, NONE_E
			);
		add_symbol(IS_FUNC, symbol);
		
		update_symbol_scope("FUNCTIONS", (yyvsp[(3) - (11)].strval), IS_VARCONST);
		if(!strcmp(scope, "STRUCTURES")) {
			char newscope[MAX_STR];
			strcpy(newscope, scope);
			strcat(newscope, " TEMP ");
			strcat(newscope, (yyvsp[(3) - (11)].strval));
			update_lastn_scope(var_in_func, newscope);
		}
		var_in_func = 0;

		free((yyvsp[(5) - (11)].symbol)); free((yyvsp[(9) - (11)].symbol));
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 350 "y.y"
    {
		check_length((yyvsp[(2) - (4)].strval), MAX_ID);
		// TODO: verifica daca func apelata a fost definita
		check_defined((yyvsp[(2) - (4)].strval), scope);
		// TODO: verifica daca func apelata are parametrii valizi

		struct Symbol* symbol = get_function((yyvsp[(2) - (4)].strval), 0, NONE_PT);

		(yyval.symbol) = copy_symbol(symbol);
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 360 "y.y"
    {
		check_length((yyvsp[(2) - (5)].strval), MAX_ID);
		// TODO: verifica daca func apelata a fost definita
		// TODO: verifica daca func apelata are parametrii valizi

		struct Symbol* symbol = get_function((yyvsp[(2) - (5)].strval), (yyvsp[(4) - (5)].symbol)->n_params, (yyvsp[(4) - (5)].symbol)->paramtypes);

		(yyval.symbol) = copy_symbol(symbol);
		free((yyvsp[(4) - (5)].symbol));
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 372 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		append_param((yyval.symbol), (yyvsp[(1) - (1)].symbol));

		free((yyvsp[(1) - (1)].symbol));
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 378 "y.y"
    {
		append_param((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));
		
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 386 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		append_param((yyval.symbol), (yyvsp[(1) - (1)].symbol));

		free((yyvsp[(1) - (1)].symbol));

		var_in_func++;
		}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 394 "y.y"
    {
		append_param((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));
		
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
			
		var_in_func++;
		}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 404 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (3)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(3) - (3)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int((yyvsp[(1) - (3)].charval));
		int type = get_type_int((yyvsp[(2) - (3)].strval));

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (3)].strval), varconst, type, DIM_UNI, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		add_symbol(IS_VARCONST, symbol);

		(yyval.symbol) = copy_symbol(&symbol);
	}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 426 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(4) - (4)].strval), MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size((yyvsp[(3) - (4)].intval), MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(4) - (4)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int((yyvsp[(1) - (4)].charval));
		int type = get_type_int((yyvsp[(2) - (4)].strval));

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(4) - (4)].strval), varconst, type, DIM_ARR, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, (yyvsp[(3) - (4)].intval), NONE_E
			);
		add_symbol(IS_VARCONST, symbol);

		(yyval.symbol) = copy_symbol(&symbol);
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 458 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (3)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(3) - (3)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int((yyvsp[(1) - (3)].charval));
		int type = get_type_int((yyvsp[(2) - (3)].strval));

		if(varconst == IS_CONST) check_const((yyvsp[(3) - (3)].strval), scope, 0);

		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (3)].strval), varconst, type, DIM_UNI, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		
		add_symbol(IS_VARCONST, symbol);
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 481 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(3) - (5)].strval), MAX_ID);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(3) - (5)].strval), scope, 0, 0, NONE_PT);
		check_value(0, (yyvsp[(3) - (5)].strval), (yyvsp[(2) - (5)].strval), (yyvsp[(5) - (5)].symbol));
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int((yyvsp[(1) - (5)].charval));
		int type = get_type_int((yyvsp[(2) - (5)].strval));


		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(3) - (5)].strval), varconst, type, DIM_UNI, scope, NONE_S, 1, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);
		assign_value(&symbol, (yyvsp[(5) - (5)].symbol));
		add_symbol(IS_VARCONST, symbol);
		
		free((yyvsp[(5) - (5)].symbol));
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 506 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(4) - (4)].strval), MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size((yyvsp[(3) - (4)].intval), MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(4) - (4)].strval), scope, 0, 0, NONE_PT);
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int((yyvsp[(1) - (4)].charval));
		int type = get_type_int((yyvsp[(2) - (4)].strval));

		if(varconst == IS_CONST) check_const((yyvsp[(4) - (4)].strval), scope, 0);
		
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(4) - (4)].strval), varconst, type, DIM_ARR, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, (yyvsp[(3) - (4)].intval), NONE_E
			);
		add_symbol(IS_VARCONST, symbol);
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 529 "y.y"
    {
		// verifica daca id-ul depaseste lungimea maxima
		check_length((yyvsp[(4) - (8)].strval), MAX_ID);
		// verifica daca dimensiunea array-ului depaseste lungimea maxima
		check_size((yyvsp[(3) - (8)].intval), MAX_DIM);
		// verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		check_duplicate((yyvsp[(4) - (8)].strval), scope, 0, 0, NONE_PT);
		check_array(0, (yyvsp[(4) - (8)].strval), (yyvsp[(2) - (8)].strval), (yyvsp[(7) - (8)].symbol), (yyvsp[(3) - (8)].intval));
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =

		int varconst = get_varconst_int((yyvsp[(1) - (8)].charval));
		int type = get_type_int((yyvsp[(2) - (8)].strval));
		
		// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
		struct Symbol symbol = create_symbol(
			(yyvsp[(4) - (8)].strval), varconst, type, DIM_ARR, scope, NONE_S, 1, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, (yyvsp[(3) - (8)].intval), NONE_E
			);
		assign_value(&symbol, (yyvsp[(7) - (8)].symbol));
		add_symbol(IS_VARCONST, symbol);

		free((yyvsp[(7) - (8)].symbol));
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 556 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		append_element((yyval.symbol), (yyvsp[(1) - (1)].symbol));

		free((yyvsp[(1) - (1)].symbol));
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 562 "y.y"
    {
		append_element((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 570 "y.y"
    {
		int type = get_string_type((yyvsp[(1) - (1)].strval));
		char chrvalue = (type == TYPE_CHAR) ? (yyvsp[(1) - (1)].strval)[1] : 0;
		char strvalue[MAX_STR] = {0}; if(type == TYPE_STRING) strcpy(strvalue, (yyvsp[(1) - (1)].strval)); 
		
		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, 0, chrvalue, strvalue, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		(yyval.symbol) = copy_symbol(&symbol);
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 582 "y.y"
    {
		int type = get_num_type((yyvsp[(1) - (1)].numval));

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, 0, scope, NONE_S, 0, (yyvsp[(1) - (1)].numval), 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		(yyval.symbol) = copy_symbol(&symbol);
	}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 592 "y.y"
    {
		int type = get_num_type((yyvsp[(2) - (2)].numval));

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, -(yyvsp[(2) - (2)].numval), 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		(yyval.symbol) = copy_symbol(&symbol);
	}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 602 "y.y"
    {
		check_length((yyvsp[(1) - (1)].strval), MAX_ID);
		check_defined((yyvsp[(1) - (1)].strval), scope);
		check_init((yyvsp[(1) - (1)].strval), scope);

		struct Symbol* symbol = get_variable((yyvsp[(1) - (1)].strval), scope);
		
		(yyval.symbol) = copy_symbol(symbol);
	}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 611 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		free((yyvsp[(1) - (1)].symbol));
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 616 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		free((yyvsp[(1) - (1)].symbol));
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 621 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		free((yyvsp[(1) - (1)].symbol));
		// TODO: returneaza valoarea in urma apelului unei functii
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 626 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(2) - (3)].symbol));
		free((yyvsp[(2) - (3)].symbol));
		// TODO: construieste simbolul pt o valoare
	}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 633 "y.y"
    {
		check_length((yyvsp[(1) - (1)].strval), MAX_ID);
		check_defined((yyvsp[(1) - (1)].strval), scope);
		check_init((yyvsp[(1) - (1)].strval), scope);

		struct Symbol* symbol = get_variable((yyvsp[(1) - (1)].strval), scope);
		
		(yyval.symbol) = copy_symbol(symbol);
	}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 642 "y.y"
    {
		int type = get_num_type((yyvsp[(1) - (1)].numval));

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, (yyvsp[(1) - (1)].numval), 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		(yyval.symbol) = copy_symbol(&symbol);
	}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 652 "y.y"
    {
		int type = get_string_type((yyvsp[(1) - (1)].strval));
		char chrvalue = (type == TYPE_CHAR) ? (yyvsp[(1) - (1)].strval)[1] : 0;
		char strvalue[MAX_STR] = {0}; if(type == TYPE_STRING) strcpy(strvalue, (yyvsp[(1) - (1)].strval)); 
		
		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, type, DIM_UNI, scope, NONE_S, 0, 0, chrvalue, strvalue, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		(yyval.symbol) = copy_symbol(&symbol);
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 664 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		free((yyvsp[(1) - (1)].symbol));
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 669 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		free((yyvsp[(1) - (1)].symbol));
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 674 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(1) - (1)].symbol));
		free((yyvsp[(1) - (1)].symbol));
		// TODO: returneaza valoarea in urma apelului unei functii
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 679 "y.y"
    {
		(yyval.symbol) = copy_symbol((yyvsp[(2) - (3)].symbol));
		free((yyvsp[(2) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 685 "y.y"
    {
		add_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 693 "y.y"
    {
		sub_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 701 "y.y"
    {
		mul_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 709 "y.y"
    {
		div_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 717 "y.y"
    {
		eq_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 725 "y.y"
    {
		gt_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));

		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 734 "y.y"
    {
		lt_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 742 "y.y"
    {
		ge_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		(yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 750 "y.y"
    {
		le_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

        (yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 758 "y.y"
    {
		and_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

        (yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 766 "y.y"
    {
		or_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

        (yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 774 "y.y"
    {
		xor_expr((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

        (yyval.symbol) = copy_symbol((yyvsp[(1) - (3)].symbol));
		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 782 "y.y"
    {
		not_expr((yyvsp[(2) - (2)].symbol));

        (yyval.symbol) = copy_symbol((yyvsp[(2) - (2)].symbol));
		free((yyvsp[(2) - (2)].symbol));
		// TODO: construieste simbolul pt o expresie
		// TODO: verifica daca 2 operanzi intr-o expresie au acelasi tip
	}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 799 "y.y"
    {var_in_func++;}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 803 "y.y"
    {
		free((yyvsp[(1) - (2)].symbol));
	}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 813 "y.y"
    {
		// TODO: implementeaza Eval(int expr)
		check_type((yyvsp[(3) - (4)].symbol), TYPE_INT);
		print_symbol((yyvsp[(3) - (4)].symbol));
		print_symbol(0);

		free((yyvsp[(3) - (4)].symbol));
	}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 823 "y.y"
    {
		// TODO: implementeaza afisarea pe ecran
		print_symbol(0);
	}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 827 "y.y"
    {
		// TODO: implementeaza afisarea pe ecran
		print_symbol((yyvsp[(3) - (4)].symbol));
		free((yyvsp[(3) - (4)].symbol));
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 834 "y.y"
    {
		check_length((yyvsp[(1) - (3)].strval), MAX_ID);
		check_defined((yyvsp[(1) - (3)].strval), scope);
		check_const((yyvsp[(1) - (3)].strval), scope, 1);

		struct Symbol* symbol = get_variable((yyvsp[(1) - (3)].strval), scope);
		check_value(symbol, NONE_I, NONE_T, (yyvsp[(3) - (3)].symbol));
		assign_value(symbol, (yyvsp[(3) - (3)].symbol));

		free((yyvsp[(3) - (3)].symbol));
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 845 "y.y"
    {
		check_length((yyvsp[(1) - (5)].strval), MAX_ID);
		check_defined((yyvsp[(1) - (5)].strval), scope);
		check_const((yyvsp[(1) - (5)].strval), scope, 1);

		struct Symbol* symbol = get_variable((yyvsp[(1) - (5)].strval), scope);
		check_array(symbol, NONE_I, NONE_T, (yyvsp[(4) - (5)].symbol), 0);
		assign_value(symbol, (yyvsp[(4) - (5)].symbol));

		free((yyvsp[(4) - (5)].symbol));
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca id-ul depaseste lungimea maxima
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 863 "y.y"
    {
		check_value((yyvsp[(1) - (3)].symbol), NONE_I, NONE_T, (yyvsp[(3) - (3)].symbol));
		assign_value((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca id-ul depaseste lungimea maxima
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 876 "y.y"
    {
		check_value((yyvsp[(1) - (3)].symbol), NONE_I, NONE_T, (yyvsp[(3) - (3)].symbol));
		assign_value((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].symbol));

		free((yyvsp[(1) - (3)].symbol)); free((yyvsp[(3) - (3)].symbol));
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 882 "y.y"
    {
		check_value((yyvsp[(1) - (5)].symbol), NONE_I, NONE_T, (yyvsp[(4) - (5)].symbol));
		assign_value((yyvsp[(1) - (5)].symbol), (yyvsp[(4) - (5)].symbol));

		free((yyvsp[(1) - (5)].symbol)); free((yyvsp[(4) - (5)].symbol));
		// TODO: verifica daca var/func/struct e deja declarat (considera: scope-ul, var vs varglobal vs struct vs func vs func param dif)
		// TODO: verifica daca id-ul depaseste lungimea maxima
		// TODO: verifica daca dimensiunea array-ului depaseste lungimea maxima
		// TODO: verifica daca lungimea unei valori depaseste lungimea maxima
		// TODO: verifica daca const are o val asignata
		// TODO: verifica daca var din dreapta = a fost initializata
		// TODO: verifica daca valoarea din dreapta = are acelasi tip ca var din stanga =
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 898 "y.y"
    {
		check_length((yyvsp[(1) - (4)].strval), MAX_ID);
		check_defined((yyvsp[(1) - (4)].strval), scope);

		struct Symbol* symbol = get_variable((yyvsp[(1) - (4)].strval), scope);
		struct Symbol value = access_array(symbol, (yyvsp[(3) - (4)].symbol));

		(yyval.symbol) = copy_symbol(&value);
		free((yyvsp[(3) - (4)].symbol));
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 911 "y.y"
    {
		check_length((yyvsp[(1) - (3)].strval), MAX_ID);
		check_defined((yyvsp[(1) - (3)].strval), scope);

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		(yyval.symbol) = copy_symbol(&symbol);
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 923 "y.y"
    {
		check_length((yyvsp[(1) - (3)].strval), MAX_ID);
		check_defined((yyvsp[(1) - (3)].strval), scope);

		struct Symbol symbol = create_symbol(
			// id, is, type, dim, scope, structure, init, numvalue, chrvalue, strvalue, n_params, paramvals, paramtypes, n_elements, elements
			NONE_I, 0, 0, 0, scope, NONE_S, 0, 0, 0, NONE_S, 0, NONE_PV, NONE_PT, 0, NONE_E
			);

		(yyval.symbol) = copy_symbol(&symbol);
		free((yyvsp[(3) - (3)].symbol));
		// TODO: returneaza valoarea pt accesului unui element din array/struct
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 939 "y.y"
    {
        check_length((yyvsp[(3) - (6)].strval), MAX_ID);
        check_defined((yyvsp[(3) - (6)].strval), scope);

        struct Symbol* symbol = get_variable((yyvsp[(3) - (6)].strval), scope);
        check_type(symbol, TYPE_STRING);

        concat_string(symbol, (yyvsp[(5) - (6)].symbol));
        
        free((yyvsp[(5) - (6)].symbol));
        // TODO: operatii cu stringuri
        // TODO: verifica daca parametrii sunt stringuri
    }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 952 "y.y"
    {
        check_length((yyvsp[(3) - (6)].strval), MAX_ID);
        check_defined((yyvsp[(3) - (6)].strval), scope);

        struct Symbol* symbol = get_variable((yyvsp[(3) - (6)].strval), scope);
        check_type(symbol, TYPE_STRING);

        copy_string(symbol, (yyvsp[(5) - (6)].symbol));
        
        free((yyvsp[(5) - (6)].symbol));
        // TODO: operatii cu stringuri
        // TODO: verifica daca parametrii sunt stringuri
    }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 967 "y.y"
    {
		free((yyvsp[(3) - (7)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 972 "y.y"
    {
		free((yyvsp[(3) - (5)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 977 "y.y"
    {
		free((yyvsp[(3) - (11)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 982 "y.y"
    {
		free((yyvsp[(3) - (9)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 987 "y.y"
    {
		free((yyvsp[(3) - (9)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 992 "y.y"
    {
		free((yyvsp[(3) - (7)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 999 "y.y"
    {
		free((yyvsp[(3) - (7)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1006 "y.y"
    {
		free((yyvsp[(5) - (17)].symbol)); free((yyvsp[(9) - (17)].symbol)); free((yyvsp[(13) - (17)].symbol));
		// TODO: implementeaza if/else/while/for
		// TODO: implementeaza rularea unei functii si returneaza valoarea
	}
    break;


/* Line 1792 of yacc.c  */
#line 2971 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 1013 "y.y"

void yyerror(char* s){
	printf("Eroare: %s\nLinia: %d\nToken: %s\n", s, yylineno, yytext);
	exit(-1);
}

int main(int argc, char** argv){
	/* extern int yydebug;
	yydebug = 1; */

	yyin = fopen("cod.txt","r");
	yyparse();
} 