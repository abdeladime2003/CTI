/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "re-parse.y"

#include <cstdlib>

#include "zeek/RE.h"
#include "zeek/CCL.h"
#include "zeek/NFA.h"
#include "zeek/EquivClass.h"
#include "zeek/Reporter.h"

int csize = 256;
int syntax_error = 0;

namespace zeek::detail {
	int cupper(int sym);
	int clower(int sym);
}

void yyerror(const char msg[]);

#line 91 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "re-parse.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_CHAR = 3,                   /* TOK_CHAR  */
  YYSYMBOL_TOK_NUMBER = 4,                 /* TOK_NUMBER  */
  YYSYMBOL_TOK_CCL = 5,                    /* TOK_CCL  */
  YYSYMBOL_TOK_CCE = 6,                    /* TOK_CCE  */
  YYSYMBOL_TOK_CASE_INSENSITIVE = 7,       /* TOK_CASE_INSENSITIVE  */
  YYSYMBOL_TOK_SINGLE_LINE = 8,            /* TOK_SINGLE_LINE  */
  YYSYMBOL_9_ = 9,                         /* '|'  */
  YYSYMBOL_10_ = 10,                       /* '*'  */
  YYSYMBOL_11_ = 11,                       /* '+'  */
  YYSYMBOL_12_ = 12,                       /* '?'  */
  YYSYMBOL_13_ = 13,                       /* '{'  */
  YYSYMBOL_14_ = 14,                       /* ','  */
  YYSYMBOL_15_ = 15,                       /* '}'  */
  YYSYMBOL_16_ = 16,                       /* '.'  */
  YYSYMBOL_17_ = 17,                       /* '"'  */
  YYSYMBOL_18_ = 18,                       /* '('  */
  YYSYMBOL_19_ = 19,                       /* ')'  */
  YYSYMBOL_20_ = 20,                       /* '^'  */
  YYSYMBOL_21_ = 21,                       /* '$'  */
  YYSYMBOL_22_ = 22,                       /* '['  */
  YYSYMBOL_23_ = 23,                       /* ']'  */
  YYSYMBOL_24_ = 24,                       /* '-'  */
  YYSYMBOL_YYACCEPT = 25,                  /* $accept  */
  YYSYMBOL_flexrule = 26,                  /* flexrule  */
  YYSYMBOL_re = 27,                        /* re  */
  YYSYMBOL_series = 28,                    /* series  */
  YYSYMBOL_singleton = 29,                 /* singleton  */
  YYSYMBOL_full_ccl = 30,                  /* full_ccl  */
  YYSYMBOL_ccl = 31,                       /* ccl  */
  YYSYMBOL_ccl_expr = 32,                  /* ccl_expr  */
  YYSYMBOL_string = 33                     /* string  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   58

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  50

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   263


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    17,     2,    21,     2,     2,     2,
      18,    19,    10,    11,    14,    24,    16,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    12,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,    23,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    13,     9,    15,     2,     2,     2,     2,
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
       5,     6,     7,     8
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    40,    40,    43,    47,    49,    51,    54,    56,    59,
      62,    65,    68,    92,   104,   117,   123,   130,   133,   136,
     139,   142,   145,   159,   165,   172,   175,   182,   214,   225,
     228,   231,   239,   250
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_CHAR",
  "TOK_NUMBER", "TOK_CCL", "TOK_CCE", "TOK_CASE_INSENSITIVE",
  "TOK_SINGLE_LINE", "'|'", "'*'", "'+'", "'?'", "'{'", "','", "'}'",
  "'.'", "'\"'", "'('", "')'", "'^'", "'$'", "'['", "']'", "'-'",
  "$accept", "flexrule", "re", "series", "singleton", "full_ccl", "ccl",
  "ccl_expr", "string", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-16)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-7)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,   -16,   -16,   -16,    22,    22,   -16,   -16,    22,   -16,
     -16,   -15,     7,    19,    22,    43,   -16,    -6,    27,    17,
      28,   -16,     8,   -16,    22,    43,   -16,   -16,   -16,    12,
     -16,   -16,   -16,   -16,   -16,     9,    21,   -16,   -16,   -16,
      22,    36,   -16,    30,    20,   -16,   -16,    26,   -16,   -16
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,    22,    17,     6,     6,    15,    33,     6,    23,
      24,    30,     0,     2,     5,     8,    16,     0,     0,     0,
       0,    30,     0,     1,     0,     7,     9,    10,    11,     0,
      20,    21,    32,    18,    19,     0,    28,    31,    25,    29,
       4,     0,    26,     0,     0,    14,    27,     0,    13,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -16,   -16,    44,    33,   -14,   -16,    37,   -16,   -16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    22,    39,    19
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      25,    -6,     1,    24,     2,    21,     3,    23,     4,     5,
      -6,    36,    36,    30,    37,    37,    41,     6,     7,     8,
      32,     9,    10,    11,    47,     2,    25,     3,    24,     4,
       5,    38,    42,    46,    33,    48,    24,    24,     6,     7,
       8,    49,     9,    10,    11,    43,    31,    34,    17,    18,
      44,    45,    20,    26,    27,    28,    29,    40,    35
};

static const yytype_int8 yycheck[] =
{
      14,     0,     1,     9,     3,    20,     5,     0,     7,     8,
       9,     3,     3,    19,     6,     6,     4,    16,    17,    18,
       3,    20,    21,    22,     4,     3,    40,     5,     9,     7,
       8,    23,    23,     3,    17,    15,     9,     9,    16,    17,
      18,    15,    20,    21,    22,    24,    19,    19,     4,     5,
      14,    15,     8,    10,    11,    12,    13,    24,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     5,     7,     8,    16,    17,    18,    20,
      21,    22,    26,    27,    28,    29,    30,    27,    27,    33,
      27,    20,    31,     0,     9,    29,    10,    11,    12,    13,
      19,    19,     3,    17,    19,    31,     3,     6,    23,    32,
      28,     4,    23,    24,    14,    15,     3,     4,    15,    15
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    25,    26,    26,    27,    27,    27,    28,    28,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    30,    30,    31,    31,    31,
      31,    32,    33,    33
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     0,     2,     1,     2,
       2,     2,     6,     5,     4,     1,     1,     1,     3,     3,
       3,     3,     1,     1,     1,     3,     4,     4,     2,     2,
       0,     1,     2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_re: /* re  */
#line 37 "re-parse.y"
            { delete ((*yyvaluep).mach_val); }
#line 873 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
        break;

    case YYSYMBOL_series: /* series  */
#line 37 "re-parse.y"
            { delete ((*yyvaluep).mach_val); }
#line 879 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
        break;

    case YYSYMBOL_singleton: /* singleton  */
#line 37 "re-parse.y"
            { delete ((*yyvaluep).mach_val); }
#line 885 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
        break;

    case YYSYMBOL_string: /* string  */
#line 37 "re-parse.y"
            { delete ((*yyvaluep).mach_val); }
#line 891 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* flexrule: re  */
#line 41 "re-parse.y"
                        { (yyvsp[0].mach_val)->AddAccept(1); zeek::detail::nfa = (yyvsp[0].mach_val); }
#line 1161 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 3: /* flexrule: error  */
#line 44 "re-parse.y"
                        { return 1; }
#line 1167 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 4: /* re: re '|' series  */
#line 48 "re-parse.y"
                        { (yyval.mach_val) = zeek::detail::make_alternate((yyvsp[-2].mach_val), (yyvsp[0].mach_val)); }
#line 1173 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 6: /* re: %empty  */
#line 51 "re-parse.y"
                        { (yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::EpsilonState()); }
#line 1179 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 7: /* series: series singleton  */
#line 55 "re-parse.y"
                        { (yyvsp[-1].mach_val)->AppendMachine((yyvsp[0].mach_val)); (yyval.mach_val) = (yyvsp[-1].mach_val); }
#line 1185 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 9: /* singleton: singleton '*'  */
#line 60 "re-parse.y"
                        { (yyvsp[-1].mach_val)->MakeClosure(); (yyval.mach_val) = (yyvsp[-1].mach_val); }
#line 1191 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 10: /* singleton: singleton '+'  */
#line 63 "re-parse.y"
                        { (yyvsp[-1].mach_val)->MakePositiveClosure(); (yyval.mach_val) = (yyvsp[-1].mach_val); }
#line 1197 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 11: /* singleton: singleton '?'  */
#line 66 "re-parse.y"
                        { (yyvsp[-1].mach_val)->MakeOptional(); (yyval.mach_val) = (yyvsp[-1].mach_val); }
#line 1203 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 12: /* singleton: singleton '{' TOK_NUMBER ',' TOK_NUMBER '}'  */
#line 69 "re-parse.y"
                        {
			if ( (yyvsp[-3].int_val) > (yyvsp[-1].int_val) || (yyvsp[-3].int_val) < 0 )
				zeek::detail::synerr("bad iteration values");
			else
				{
				if ( (yyvsp[-3].int_val) == 0 )
					{
					if ( (yyvsp[-1].int_val) == 0 )
						{
						(yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::EpsilonState());
						Unref((yyvsp[-5].mach_val));
						}
					else
						{
						(yyvsp[-5].mach_val)->MakeRepl(1, (yyvsp[-1].int_val));
						(yyvsp[-5].mach_val)->MakeOptional();
						}
					}
				else
					(yyvsp[-5].mach_val)->MakeRepl((yyvsp[-3].int_val), (yyvsp[-1].int_val));
				}
			}
#line 1230 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 13: /* singleton: singleton '{' TOK_NUMBER ',' '}'  */
#line 93 "re-parse.y"
                        {
			if ( (yyvsp[-2].int_val) < 0 )
				zeek::detail::synerr("iteration value must be positive");
			else if ( (yyvsp[-2].int_val) == 0 )
				(yyvsp[-4].mach_val)->MakeClosure();
			else
				(yyvsp[-4].mach_val)->MakeRepl((yyvsp[-2].int_val), NO_UPPER_BOUND);

			(yyval.mach_val) = (yyvsp[-4].mach_val);
			}
#line 1245 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 14: /* singleton: singleton '{' TOK_NUMBER '}'  */
#line 105 "re-parse.y"
                        {
			if ( (yyvsp[-1].int_val) < 0 )
				zeek::detail::synerr("iteration value must be positive");
			else if ( (yyvsp[-1].int_val) == 0 )
				{
				Unref((yyvsp[-3].mach_val));
				(yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::EpsilonState());
				}
			else
				(yyvsp[-3].mach_val)->LinkCopies((yyvsp[-1].int_val)-1);
			}
#line 1261 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 15: /* singleton: '.'  */
#line 118 "re-parse.y"
                        {
			(yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::NFA_State(
                zeek::detail::rem->AnyCCL(zeek::detail::re_single_line)));
			}
#line 1270 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 16: /* singleton: full_ccl  */
#line 124 "re-parse.y"
                        {
			(yyvsp[0].ccl_val)->Sort();
			zeek::detail::rem->EC()->CCL_Use((yyvsp[0].ccl_val));
			(yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::NFA_State((yyvsp[0].ccl_val)));
			}
#line 1280 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 17: /* singleton: TOK_CCL  */
#line 131 "re-parse.y"
                        { (yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::NFA_State((yyvsp[0].ccl_val))); }
#line 1286 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 18: /* singleton: '"' string '"'  */
#line 134 "re-parse.y"
                        { (yyval.mach_val) = (yyvsp[-1].mach_val); }
#line 1292 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 19: /* singleton: '(' re ')'  */
#line 137 "re-parse.y"
                        { (yyval.mach_val) = (yyvsp[-1].mach_val); }
#line 1298 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 20: /* singleton: TOK_CASE_INSENSITIVE re ')'  */
#line 140 "re-parse.y"
                        { (yyval.mach_val) = (yyvsp[-1].mach_val); zeek::detail::case_insensitive = false; }
#line 1304 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 21: /* singleton: TOK_SINGLE_LINE re ')'  */
#line 143 "re-parse.y"
                        { (yyval.mach_val) = (yyvsp[-1].mach_val); zeek::detail::re_single_line = false; }
#line 1310 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 22: /* singleton: TOK_CHAR  */
#line 146 "re-parse.y"
                        {
			auto sym = (yyvsp[0].int_val);

			if ( sym < 0 || ( sym >= NUM_SYM && sym != SYM_EPSILON ) )
				{
				zeek::reporter->Error("bad symbol %d (compiling pattern /%s/)", sym,
				                      zeek::detail::RE_parse_input);
				return 1;
				}

			(yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::NFA_State(sym, zeek::detail::rem->EC()));
			}
#line 1327 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 23: /* singleton: '^'  */
#line 160 "re-parse.y"
                        {
			(yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::NFA_State(SYM_BOL, zeek::detail::rem->EC()));
			(yyval.mach_val)->MarkBOL();
			}
#line 1336 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 24: /* singleton: '$'  */
#line 166 "re-parse.y"
                        {
			(yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::NFA_State(SYM_EOL, zeek::detail::rem->EC()));
			(yyval.mach_val)->MarkEOL();
			}
#line 1345 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 25: /* full_ccl: '[' ccl ']'  */
#line 173 "re-parse.y"
                        { (yyval.ccl_val) = (yyvsp[-1].ccl_val); }
#line 1351 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 26: /* full_ccl: '[' '^' ccl ']'  */
#line 176 "re-parse.y"
                        {
			(yyvsp[-1].ccl_val)->Negate();
			(yyval.ccl_val) = (yyvsp[-1].ccl_val);
			}
#line 1360 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 27: /* ccl: ccl TOK_CHAR '-' TOK_CHAR  */
#line 183 "re-parse.y"
                        {
			if ( (yyvsp[-2].int_val) > (yyvsp[0].int_val) )
				zeek::detail::synerr("negative range in character class");

			else if ( zeek::detail::case_insensitive &&
				  (isalpha((yyvsp[-2].int_val)) || isalpha((yyvsp[0].int_val))) )
				{
				if ( isalpha((yyvsp[-2].int_val)) && isalpha((yyvsp[0].int_val)) &&
				     isupper((yyvsp[-2].int_val)) == isupper((yyvsp[0].int_val)) )
					{ // Compatible range, do both versions
					int l2 = tolower((yyvsp[-2].int_val));
					int l4 = tolower((yyvsp[0].int_val));

					for ( int i = l2; i<= l4; ++i )
						{
						(yyvsp[-3].ccl_val)->Add(i);
						(yyvsp[-3].ccl_val)->Add(toupper(i));
						}
					}

				else
					zeek::detail::synerr("ambiguous case-insensitive character class");
				}

			else
				{
				for ( int i = (yyvsp[-2].int_val); i <= (yyvsp[0].int_val); ++i )
					(yyvsp[-3].ccl_val)->Add(i);
				}
			}
#line 1395 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 28: /* ccl: ccl TOK_CHAR  */
#line 215 "re-parse.y"
                        {
			if ( zeek::detail::case_insensitive && isalpha((yyvsp[0].int_val)) )
				{
				(yyvsp[-1].ccl_val)->Add(zeek::detail::clower((yyvsp[0].int_val)));
				(yyvsp[-1].ccl_val)->Add(zeek::detail::cupper((yyvsp[0].int_val)));
				}
			else
				(yyvsp[-1].ccl_val)->Add((yyvsp[0].int_val));
			}
#line 1409 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 30: /* ccl: %empty  */
#line 228 "re-parse.y"
                        { (yyval.ccl_val) = zeek::detail::curr_ccl; }
#line 1415 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 31: /* ccl_expr: TOK_CCE  */
#line 232 "re-parse.y"
                        {
			for ( int c = 0; c < csize; ++c )
				if ( isascii(c) && (yyvsp[0].cce_val)(c) )
					zeek::detail::curr_ccl->Add(c);
			}
#line 1425 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 32: /* string: string TOK_CHAR  */
#line 240 "re-parse.y"
                        {
			// Even if case-insensitivity is set,
			// leave this alone; that provides a way
			// of "escaping" out of insensitivity
			// if needed.
			(yyvsp[-1].mach_val)->AppendState(new zeek::detail::NFA_State((yyvsp[0].int_val), zeek::detail::rem->EC()));
			(yyval.mach_val) = (yyvsp[-1].mach_val);
			}
#line 1438 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;

  case 33: /* string: %empty  */
#line 250 "re-parse.y"
                        { (yyval.mach_val) = new zeek::detail::NFA_Machine(new zeek::detail::EpsilonState()); }
#line 1444 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"
    break;


#line 1448 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rep.cc"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 252 "re-parse.y"


namespace zeek::detail {

int cupper(int sym)
	{
	return (isascii(sym) && islower(sym)) ?  toupper(sym) : sym;
	}

int clower(int sym)
	{
	return (isascii(sym) && isupper(sym)) ?  tolower(sym) : sym;
	}

void synerr(const char str[])
	{
	syntax_error = true;
	zeek::reporter->Error("%s (compiling pattern /%s/)", str, RE_parse_input);
	}

} // namespace zeek::detail

void yyerror(const char msg[])
	{
	}
