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
#line 1 "bison.y"
       
#pragma once
#include <cstdio>
#include <iostream>
#include "syntaxTree.h"
#include "grammar.h"

using namespace Tree;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
void yyerror(const char *s);
extern Tree::IProgram* yyprogram = 0;
extern int yylineno;

/* Line 371 of yacc.c  */
#line 85 "bison.tab.cpp"

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison.tab.h".  */
#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
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
     Id = 258,
     IntNum = 259,
     If = 260,
     Else = 261,
     While = 262,
     Main = 263,
     Class = 264,
     Public = 265,
     Static = 266,
     Return = 267,
     Extends = 268,
     Int = 269,
     Bool = 270,
     Void = 271,
     String = 272,
     Print = 273,
     True = 274,
     False = 275,
     This = 276,
     New = 277,
     Length = 278,
     SystemOutPrintln = 279,
     OperatorEq = 280,
     OperatorAnd = 281,
     OperatorMore = 282,
     OperatorLess = 283,
     UMINUS = 284
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 65 "bison.y"

	int ival;
	Tree::IProgram* program;
	Tree::IMainClass* mainClass;
	Tree::IClassDeclList* classDeclList;
	Tree::IClassDecl* classDecl;
	Tree::IVarDeclList* varDeclList;
	Tree::IVarDecl* varDecl;
	Tree::IMethodDeclList* methodDeclList;
	Tree::IMethodDecl* methodDecl;
	Tree::IFormalList* formalList;
	Tree::IType* type;
	Tree::IStmtList* stmtList;
	Tree::IStmt* stmt;
	Tree::IExprList* exprList;
	Tree::IExpr* expr;
	char* sval;


/* Line 387 of yacc.c  */
#line 177 "bison.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
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

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 218 "bison.tab.cpp"

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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNRULES -- Number of states.  */
#define YYNSTATES  145

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,     2,     2,     2,
      39,    40,    31,    29,    43,    30,    35,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    41,     2,     2,     2,     2,
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
      25,    26,    27,    28,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    24,    28,    31,    32,    39,    48,
      51,    52,    66,    69,    70,    74,    75,    80,    81,    83,
      87,    89,    91,    94,    95,    99,   104,   112,   118,   124,
     132,   136,   140,   144,   148,   151,   156,   160,   167,   171,
     175,   177,   179,   181,   183,   185,   191,   196,   199,   203,
     206,   207,   211
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    50,    -1,     9,     3,    38,    10,
      11,    16,     8,    39,    17,    36,    37,     3,    40,    38,
      57,    41,    41,    -1,    55,     3,    42,    -1,    48,    47,
      -1,    -1,     9,     3,    38,    48,    52,    41,    -1,     9,
       3,    13,     3,    38,    48,    52,    41,    -1,    49,    50,
      -1,    -1,    10,    55,     3,    39,    53,    40,    38,    48,
      56,    12,    58,    42,    41,    -1,    52,    51,    -1,    -1,
      55,     3,    54,    -1,    -1,    43,    55,     3,    54,    -1,
      -1,    14,    -1,    14,    36,    37,    -1,    15,    -1,     3,
      -1,    57,    56,    -1,    -1,    38,    56,    41,    -1,     3,
      25,    58,    42,    -1,     5,    39,    58,    40,    57,     6,
      57,    -1,     7,    39,    58,    40,    57,    -1,    18,    39,
      58,    40,    42,    -1,     3,    36,    58,    37,    25,    58,
      42,    -1,    58,    31,    58,    -1,    58,    29,    58,    -1,
      58,    32,    58,    -1,    58,    30,    58,    -1,    30,    58,
      -1,    58,    36,    58,    37,    -1,    58,    35,    23,    -1,
      58,    35,     3,    39,    59,    40,    -1,    58,    28,    58,
      -1,    58,    26,    58,    -1,     4,    -1,    19,    -1,    20,
      -1,     3,    -1,    21,    -1,    22,    14,    36,    58,    37,
      -1,    22,     3,    39,    40,    -1,    33,    58,    -1,    39,
      58,    40,    -1,    58,    60,    -1,    -1,    43,    58,    60,
      -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    86,    86,    90,    94,    98,    99,   103,   104,   108,
     109,   113,   117,   118,   122,   123,   127,   128,   132,   133,
     134,   135,   139,   140,   144,   145,   146,   147,   148,   149,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   175,
     176,   180,   181
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Id", "IntNum", "If", "Else", "While",
  "Main", "Class", "Public", "Static", "Return", "Extends", "Int", "Bool",
  "Void", "String", "Print", "True", "False", "This", "New", "Length",
  "SystemOutPrintln", "OperatorEq", "OperatorAnd", "OperatorMore",
  "OperatorLess", "'+'", "'-'", "'*'", "'/'", "'!'", "UMINUS", "'.'",
  "'['", "']'", "'{'", "'('", "')'", "'}'", "';'", "','", "$accept",
  "Program", "MainClass", "VarDeclaration", "VarDeclarationList",
  "ClassDeclaration", "ClassDeclarationList", "MethodDeclaration",
  "MethodDeclarationList", "FormalList", "FormalRestList", "Type",
  "StatementList", "Statement", "Expr", "ExprList", "ExprRestList", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    43,
      45,    42,    47,    33,   284,    46,    91,    93,   123,    40,
      41,   125,    59,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    47,    48,    48,    49,    49,    50,
      50,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      55,    55,    56,    56,    57,    57,    57,    57,    57,    57,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    59,
      59,    60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,    17,     3,     2,     0,     6,     8,     2,
       0,    13,     2,     0,     3,     0,     4,     0,     1,     3,
       1,     1,     2,     0,     3,     4,     7,     5,     5,     7,
       3,     3,     3,     3,     2,     4,     3,     6,     3,     3,
       1,     1,     1,     1,     1,     5,     4,     2,     3,     2,
       0,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    10,     0,     1,     0,    10,     2,     0,
       0,     9,     0,     0,     6,     0,     0,    13,     0,     6,
      21,    18,    20,     5,     0,     0,     0,    13,     0,     0,
       7,    12,     0,     0,     0,    19,     0,     4,     0,     8,
       0,     0,    15,     0,     0,     0,     0,     0,    17,     0,
       6,     0,    14,     0,    23,     0,     0,     0,     0,     0,
      23,     0,    21,     0,    23,    17,     0,     0,     0,     0,
       0,     0,     0,     0,    22,    16,    43,    40,    41,    42,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,     3,     0,     0,     0,    34,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    25,     0,     0,     0,
       0,     0,     0,     0,    48,    39,    38,    31,    33,    30,
      32,     0,    36,     0,     0,     0,    27,    28,    11,    46,
       0,    50,    35,     0,     0,    45,    52,     0,    29,    26,
       0,    49,    37,    52,    51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    23,    17,     7,     8,    31,    24,    44,
      52,    25,    63,    64,    85,   137,   141
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
      -4,     9,    62,    55,    30,   -67,    72,    55,   -67,    70,
      -7,   -67,    71,    83,   -67,    82,    69,     5,    91,   -67,
     -67,    75,   -67,   -67,     4,   105,    73,     5,    76,     5,
     -67,   -67,    80,    97,    18,   -67,   120,   -67,    90,   -67,
      88,    92,     5,   125,    98,   134,   101,   112,    99,   113,
     -67,     5,   -67,    45,     8,   151,   -15,   116,   124,   128,
      45,   123,   -15,   164,    45,    99,    21,    21,    21,    21,
      21,   127,   136,    21,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,    24,    21,    21,    21,    59,   156,   104,   117,   130,
     -67,   -67,    74,   141,   145,    43,    43,   143,    21,    21,
      21,    21,    21,    21,     6,    21,   -67,   165,    45,    45,
     147,   154,   161,    21,   -67,   189,   189,    61,    61,    43,
      43,   163,   -67,   168,    21,   201,   -67,   -67,   -67,   -67,
     180,    21,   -67,    89,    45,   -67,    41,   173,   -67,   -67,
      21,   -67,   -67,    41,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   -67,    11,   -67,   207,   -67,   195,   -67,
     158,    15,   -11,   -53,   -66,   -67,    84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      61,    86,    87,    88,    89,     1,    13,    92,    20,   121,
      66,    62,     4,    57,    29,    58,    95,    96,    97,    21,
      22,    67,    21,    22,    76,    77,    59,    93,    29,   122,
      27,    14,   115,   116,   117,   118,   119,   120,    94,   123,
      78,    79,    80,    81,    36,    30,    60,   130,    56,    71,
      57,    82,    58,    74,    83,   125,   126,    45,   133,    39,
      84,    54,     5,    59,     6,   136,    55,    98,     9,    99,
     100,   101,   102,   103,   143,    10,   104,   105,   104,   105,
      12,   139,    15,    60,   140,    98,    16,    99,   100,   101,
     102,   103,   102,   103,   104,   105,   104,   105,    18,    26,
      98,   106,    99,   100,   101,   102,   103,    19,    32,   104,
     105,    28,    33,    35,    38,    98,   111,    99,   100,   101,
     102,   103,    37,    40,   104,   105,    41,    42,    46,    43,
      98,   138,    99,   100,   101,   102,   103,    48,    47,   104,
     105,    49,    51,    98,   108,    99,   100,   101,   102,   103,
      50,    53,   104,   105,    65,    68,    98,   109,    99,   100,
     101,   102,   103,    69,    72,   104,   105,    70,    90,    98,
     110,    99,   100,   101,   102,   103,    73,    91,   104,   105,
     112,   113,    98,   114,    99,   100,   101,   102,   103,   127,
     124,   104,   105,   107,    98,   128,    99,   100,   101,   102,
     103,   129,   131,   104,   105,   132,    98,   134,    99,   100,
     101,   102,   103,   142,    11,   104,   105,   135,   100,   101,
     102,   103,    34,    75,   104,   105,     0,   144
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-67)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      53,    67,    68,    69,    70,     9,    13,    73,     3,     3,
      25,     3,     3,     5,    10,     7,    82,    83,    84,    14,
      15,    36,    14,    15,     3,     4,    18,     3,    10,    23,
      19,    38,    98,    99,   100,   101,   102,   103,    14,   105,
      19,    20,    21,    22,    29,    41,    38,   113,     3,    60,
       5,    30,     7,    64,    33,   108,   109,    42,   124,    41,
      39,    50,     0,    18,     9,   131,    51,    26,    38,    28,
      29,    30,    31,    32,   140,     3,    35,    36,    35,    36,
      10,   134,    11,    38,    43,    26,     3,    28,    29,    30,
      31,    32,    31,    32,    35,    36,    35,    36,    16,     8,
      26,    42,    28,    29,    30,    31,    32,    38,     3,    35,
      36,    36,    39,    37,    17,    26,    42,    28,    29,    30,
      31,    32,    42,     3,    35,    36,    36,    39,     3,    37,
      26,    42,    28,    29,    30,    31,    32,     3,    40,    35,
      36,    40,    43,    26,    40,    28,    29,    30,    31,    32,
      38,    38,    35,    36,     3,    39,    26,    40,    28,    29,
      30,    31,    32,    39,    41,    35,    36,    39,    41,    26,
      40,    28,    29,    30,    31,    32,    12,    41,    35,    36,
      39,    36,    26,    40,    28,    29,    30,    31,    32,    42,
      25,    35,    36,    37,    26,    41,    28,    29,    30,    31,
      32,    40,    39,    35,    36,    37,    26,     6,    28,    29,
      30,    31,    32,    40,     7,    35,    36,    37,    29,    30,
      31,    32,    27,    65,    35,    36,    -1,   143
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    45,    46,     3,     0,     9,    49,    50,    38,
       3,    50,    10,    13,    38,    11,     3,    48,    16,    38,
       3,    14,    15,    47,    52,    55,     8,    48,    36,    10,
      41,    51,     3,    39,    52,    37,    55,    42,    17,    41,
       3,    36,    39,    37,    53,    55,     3,    40,     3,    40,
      38,    43,    54,    38,    48,    55,     3,     5,     7,    18,
      38,    57,     3,    56,    57,     3,    25,    36,    39,    39,
      39,    56,    41,    12,    56,    54,     3,     4,    19,    20,
      21,    22,    30,    33,    39,    58,    58,    58,    58,    58,
      41,    41,    58,     3,    14,    58,    58,    58,    26,    28,
      29,    30,    31,    32,    35,    36,    42,    37,    40,    40,
      40,    42,    39,    36,    40,    58,    58,    58,    58,    58,
      58,     3,    23,    58,    25,    57,    57,    42,    41,    40,
      58,    39,    37,    58,     6,    37,    58,    59,    42,    57,
      43,    60,    40,    58,    60
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


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
       `yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 86 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column );  yyprogram = (yyval.program) = new CProgram( info, (yyvsp[(1) - (2)].mainClass), (yyvsp[(2) - (2)].classDeclList) ); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 90 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (17)]).first_line, (yylsp[(1) - (17)]).first_column, (yylsp[(17) - (17)]).last_line, (yylsp[(17) - (17)]).last_column ); (yyval.mainClass) = new CMainClass( info, (yyvsp[(2) - (17)].sval), (yyvsp[(12) - (17)].sval), (yyvsp[(15) - (17)].stmt) ); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 94 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.varDecl) = new CVarDecl( info, (yyvsp[(1) - (3)].type), (yyvsp[(2) - (3)].sval) ); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 98 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.varDeclList) = new CVarDeclList( info, (yyvsp[(2) - (2)].varDecl), (yyvsp[(1) - (2)].varDeclList) ); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 99 "bison.y"
    { (yyval.varDeclList) = 0; }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 103 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (6)]).first_line, (yylsp[(1) - (6)]).first_column, (yylsp[(6) - (6)]).last_line, (yylsp[(6) - (6)]).last_column ); (yyval.classDecl) = new CClassDecl( info, (yyvsp[(2) - (6)].sval), (yyvsp[(4) - (6)].varDeclList), (yyvsp[(5) - (6)].methodDeclList) ); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 104 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (8)]).first_line, (yylsp[(1) - (8)]).first_column, (yylsp[(8) - (8)]).last_line, (yylsp[(8) - (8)]).last_column ); (yyval.classDecl) = new CExtendClassDecl( info, (yyvsp[(2) - (8)].sval), (yyvsp[(4) - (8)].sval), (yyvsp[(6) - (8)].varDeclList), (yyvsp[(7) - (8)].methodDeclList) ); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 108 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.classDeclList) = new CClassDeclList( info, (yyvsp[(1) - (2)].classDecl), (yyvsp[(2) - (2)].classDeclList) ); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 109 "bison.y"
    { (yyval.classDeclList) = 0; }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 113 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (13)]).first_line, (yylsp[(1) - (13)]).first_column, (yylsp[(13) - (13)]).last_line, (yylsp[(13) - (13)]).last_column ); (yyval.methodDecl) = new CMethodDecl( info, (yyvsp[(2) - (13)].type), (yyvsp[(3) - (13)].sval), (yyvsp[(5) - (13)].formalList), (yyvsp[(8) - (13)].varDeclList), (yyvsp[(9) - (13)].stmtList), (yyvsp[(11) - (13)].expr) ); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 117 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.methodDeclList) = new CMethodDeclList( info, (yyvsp[(2) - (2)].methodDecl), (yyvsp[(1) - (2)].methodDeclList) ); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 118 "bison.y"
    { (yyval.methodDeclList) = 0; }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 122 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.formalList) = new CFormalList( info, (yyvsp[(1) - (3)].type), (yyvsp[(2) - (3)].sval), (yyvsp[(3) - (3)].formalList) ); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 123 "bison.y"
    { (yyval.formalList) = 0; }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 127 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (4)]).first_line, (yylsp[(2) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.formalList) = new CFormalList( info, (yyvsp[(2) - (4)].type), (yyvsp[(3) - (4)].sval), (yyvsp[(4) - (4)].formalList) ); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 128 "bison.y"
    { (yyval.formalList) = 0; }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 132 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.type) = new CTypeName( info, "int" ); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 133 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.type) = new CTypeName( info, "int[]" ); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 134 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.type) = new CTypeName( info, "bool" ); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 135 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.type) = new CTypeName( info, (yyvsp[(1) - (1)].sval) ); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 139 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.stmtList) = new CStmtList( info, (yyvsp[(1) - (2)].stmt), (yyvsp[(2) - (2)].stmtList) ); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 140 "bison.y"
    { (yyval.stmtList) = 0; }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 144 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.stmt) = new CGroupStmt( info, (yyvsp[(2) - (3)].stmtList) ); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 145 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(3) - (4)]).last_line, (yylsp[(3) - (4)]).last_column ); (yyval.stmt) = new CAssignStmt( info, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].expr) ); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 146 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column, (yylsp[(7) - (7)]).last_line, (yylsp[(7) - (7)]).last_column ); (yyval.stmt) = new CIfStmt( info, (yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt) ); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 147 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.stmt) = new CWhileStmt( info, (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt) ); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 148 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column ); (yyval.stmt) = new CSOPStmt( info, (yyvsp[(3) - (5)].expr) ); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 149 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (7)]).first_line, (yylsp[(1) - (7)]).first_column, (yylsp[(6) - (7)]).last_line, (yylsp[(6) - (7)]).last_column ); (yyval.stmt) = new CAssignExprStmt( info, (yyvsp[(1) - (7)].sval), (yyvsp[(3) - (7)].expr), (yyvsp[(6) - (7)].expr) ); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 153 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column ); (yyval.expr) = new COpExpr( info, (yyvsp[(1) - (3)].expr), BO_Mult, (yyvsp[(3) - (3)].expr) ); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 154 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column ); (yyval.expr) = new COpExpr( info, (yyvsp[(1) - (3)].expr), BO_Plus, (yyvsp[(3) - (3)].expr) ); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 155 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column ); (yyval.expr) = new COpExpr( info, (yyvsp[(1) - (3)].expr), BO_Div, (yyvsp[(3) - (3)].expr) ); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 156 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(2) - (3)]).last_line, (yylsp[(2) - (3)]).last_column ); (yyval.expr) = new COpExpr( info, (yyvsp[(1) - (3)].expr), BO_Minus, (yyvsp[(3) - (3)].expr) ); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 157 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (2)]).first_line, (yylsp[(2) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.expr) = new CUnaryMinusExpr( info, (yyvsp[(2) - (2)].expr) ); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 158 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.expr) = new CExExpr( info,(yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr));  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 159 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.expr) = new CLengthExpr( info, (yyvsp[(1) - (3)].expr) ); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 160 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (6)]).first_line, (yylsp[(2) - (6)]).first_column, (yylsp[(6) - (6)]).last_line, (yylsp[(6) - (6)]).last_column ); (yyval.expr) = new CMethodCallExpr( info, (yyvsp[(1) - (6)].expr), (yyvsp[(3) - (6)].sval), (yyvsp[(5) - (6)].exprList) ); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 161 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.expr) = new COpExpr( info, (yyvsp[(1) - (3)].expr), BO_Less, (yyvsp[(3) - (3)].expr) ); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 162 "bison.y"
    { CCodeInfo info( (yylsp[(2) - (3)]).first_line, (yylsp[(2) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.expr) = new COpExpr( info, (yyvsp[(1) - (3)].expr), BO_And, (yyvsp[(3) - (3)].expr) ); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 163 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.expr) = new CIntExpr( info, (yyvsp[(1) - (1)].ival) ); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 164 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.expr) = new CTrueExpr( info ); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 165 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.expr) = new CFalseExpr( info ); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 166 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.expr) = new CIdExpr( info, (yyvsp[(1) - (1)].sval) ); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 167 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column ); (yyval.expr) = new CThisExpr( info ); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 168 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(5) - (5)]).last_line, (yylsp[(5) - (5)]).last_column ); (yyval.expr) = new CNewIntExpr( info, (yyvsp[(4) - (5)].expr) ); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 169 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column ); (yyval.expr) = new CNewIdExpr( info, (yyvsp[(2) - (4)].sval) ); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 170 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.expr) = new CNotExpr( info, (yyvsp[(2) - (2)].expr) ); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 171 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.expr) = new CBrExpr( info, (yyvsp[(2) - (3)].expr) ); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 175 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column, (yylsp[(2) - (2)]).last_line, (yylsp[(2) - (2)]).last_column ); (yyval.exprList) = new CExprList( info, (yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].exprList) ); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 176 "bison.y"
    { (yyval.exprList) = 0; }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 180 "bison.y"
    { CCodeInfo info( (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column ); (yyval.exprList) = new CExprList( info, (yyvsp[(2) - (3)].expr), (yyvsp[(3) - (3)].exprList) ); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 181 "bison.y"
    { (yyval.exprList) = 0; }
    break;


/* Line 1792 of yacc.c  */
#line 1960 "bison.tab.cpp"
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
#line 184 "bison.y"
