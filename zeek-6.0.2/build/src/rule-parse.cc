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
   especially those whose name start with YY_ or rules__.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with rules_ or YY, to avoid
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
#line 1 "rule-parse.y"

#include "zeek/zeek-config.h"
#include <stdio.h>
#include <netinet/in.h>
#include <vector>

#include "zeek/RuleAction.h"
#include "zeek/RuleCondition.h"
#include "zeek/RuleMatcher.h"
#include "zeek/Reporter.h"
#include "zeek/IPAddr.h"
#include "zeek/net_util.h"

using namespace zeek::detail;

extern void begin_PS();
extern void end_PS();

zeek::detail::Rule* current_rule = nullptr;
const char* current_rule_file = nullptr;

static uint8_t ip4_mask_to_len(uint32_t mask)
	{
	if ( mask == 0xffffffff )
	    return 32;

	uint32_t x = ~mask + 1;
	uint8_t len;
	for ( len = 0; len < 32 && (! (x & (1 << len))); ++len );

	return 32 - len;
	}

#line 105 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"

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

#include "rup.h"
/* Symbol kind.  */
enum rules_symbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_COMP = 3,                   /* TOK_COMP  */
  YYSYMBOL_TOK_DISABLE = 4,                /* TOK_DISABLE  */
  YYSYMBOL_TOK_DST_IP = 5,                 /* TOK_DST_IP  */
  YYSYMBOL_TOK_DST_PORT = 6,               /* TOK_DST_PORT  */
  YYSYMBOL_TOK_ENABLE = 7,                 /* TOK_ENABLE  */
  YYSYMBOL_TOK_EVAL = 8,                   /* TOK_EVAL  */
  YYSYMBOL_TOK_EVENT = 9,                  /* TOK_EVENT  */
  YYSYMBOL_TOK_MIME = 10,                  /* TOK_MIME  */
  YYSYMBOL_TOK_HEADER = 11,                /* TOK_HEADER  */
  YYSYMBOL_TOK_IDENT = 12,                 /* TOK_IDENT  */
  YYSYMBOL_TOK_INT = 13,                   /* TOK_INT  */
  YYSYMBOL_TOK_IP = 14,                    /* TOK_IP  */
  YYSYMBOL_TOK_IP6 = 15,                   /* TOK_IP6  */
  YYSYMBOL_TOK_IP_OPTIONS = 16,            /* TOK_IP_OPTIONS  */
  YYSYMBOL_TOK_IP_OPTION_SYM = 17,         /* TOK_IP_OPTION_SYM  */
  YYSYMBOL_TOK_IP_PROTO = 18,              /* TOK_IP_PROTO  */
  YYSYMBOL_TOK_PATTERN = 19,               /* TOK_PATTERN  */
  YYSYMBOL_TOK_PATTERN_TYPE = 20,          /* TOK_PATTERN_TYPE  */
  YYSYMBOL_TOK_PAYLOAD_SIZE = 21,          /* TOK_PAYLOAD_SIZE  */
  YYSYMBOL_TOK_PROT = 22,                  /* TOK_PROT  */
  YYSYMBOL_TOK_REQUIRES_SIGNATURE = 23,    /* TOK_REQUIRES_SIGNATURE  */
  YYSYMBOL_TOK_REQUIRES_REVERSE_SIGNATURE = 24, /* TOK_REQUIRES_REVERSE_SIGNATURE  */
  YYSYMBOL_TOK_SIGNATURE = 25,             /* TOK_SIGNATURE  */
  YYSYMBOL_TOK_SAME_IP = 26,               /* TOK_SAME_IP  */
  YYSYMBOL_TOK_SRC_IP = 27,                /* TOK_SRC_IP  */
  YYSYMBOL_TOK_SRC_PORT = 28,              /* TOK_SRC_PORT  */
  YYSYMBOL_TOK_TCP_STATE = 29,             /* TOK_TCP_STATE  */
  YYSYMBOL_TOK_UDP_STATE = 30,             /* TOK_UDP_STATE  */
  YYSYMBOL_TOK_STRING = 31,                /* TOK_STRING  */
  YYSYMBOL_TOK_STATE_SYM = 32,             /* TOK_STATE_SYM  */
  YYSYMBOL_TOK_ACTIVE = 33,                /* TOK_ACTIVE  */
  YYSYMBOL_TOK_BOOL = 34,                  /* TOK_BOOL  */
  YYSYMBOL_TOK_POLICY_SYMBOL = 35,         /* TOK_POLICY_SYMBOL  */
  YYSYMBOL_36_ = 36,                       /* '{'  */
  YYSYMBOL_37_ = 37,                       /* '}'  */
  YYSYMBOL_38_ = 38,                       /* '['  */
  YYSYMBOL_39_ = 39,                       /* ']'  */
  YYSYMBOL_40_ = 40,                       /* '!'  */
  YYSYMBOL_41_ = 41,                       /* '&'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* '-'  */
  YYSYMBOL_44_ = 44,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_rule_list = 46,                 /* rule_list  */
  YYSYMBOL_rule = 47,                      /* rule  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_rule_attr_list = 49,            /* rule_attr_list  */
  YYSYMBOL_rule_attr = 50,                 /* rule_attr  */
  YYSYMBOL_51_2 = 51,                      /* $@2  */
  YYSYMBOL_52_3 = 52,                      /* $@3  */
  YYSYMBOL_hdr_expr = 53,                  /* hdr_expr  */
  YYSYMBOL_value_list = 54,                /* value_list  */
  YYSYMBOL_prefix_value_list = 55,         /* prefix_value_list  */
  YYSYMBOL_prefix_value = 56,              /* prefix_value  */
  YYSYMBOL_ranged_value = 57,              /* ranged_value  */
  YYSYMBOL_value = 58,                     /* value  */
  YYSYMBOL_rangeopt = 59,                  /* rangeopt  */
  YYSYMBOL_range = 60,                     /* range  */
  YYSYMBOL_ipoption_list = 61,             /* ipoption_list  */
  YYSYMBOL_state_list = 62,                /* state_list  */
  YYSYMBOL_integer = 63,                   /* integer  */
  YYSYMBOL_opt_negate = 64,                /* opt_negate  */
  YYSYMBOL_opt_strength = 65,              /* opt_strength  */
  YYSYMBOL_string = 66,                    /* string  */
  YYSYMBOL_pattern = 67                    /* pattern  */
};
typedef enum rules_symbol_kind_t rules_symbol_kind_t;




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
typedef __INT_LEAST8_TYPE__ rules_type_int8;
#elif defined YY_STDINT_H
typedef int_least8_t rules_type_int8;
#else
typedef signed char rules_type_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ rules_type_int16;
#elif defined YY_STDINT_H
typedef int_least16_t rules_type_int16;
#else
typedef short rules_type_int16;
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
typedef __UINT_LEAST8_TYPE__ rules_type_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t rules_type_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char rules_type_uint8;
#else
typedef short rules_type_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ rules_type_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t rules_type_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short rules_type_uint16;
#else
typedef int rules_type_uint16;
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
typedef rules_type_int8 rules__state_t;

/* State numbers in computations.  */
typedef int rules__state_fast_t;

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

/* Suppress an incorrect diagnostic about rules_lval being uninitialized.  */
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

#if !defined rules_overflow

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
#endif /* !defined rules_overflow */

#if (! defined rules_overflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union rules_alloc
{
  rules__state_t rules_ss_alloc;
  YYSTYPE rules_vs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union rules_alloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (rules__state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T rules_newbytes;                                         \
        YYCOPY (&rules_ptr->Stack_alloc, Stack, rules_size);                    \
        Stack = &rules_ptr->Stack_alloc;                                    \
        rules_newbytes = rules_stacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        rules_ptr += rules_newbytes / YYSIZEOF (*rules_ptr);                        \
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
          YYPTRDIFF_T rules_i;                      \
          for (rules_i = 0; rules_i < (Count); rules_i++)   \
            (Dst)[rules_i] = (Src)[rules_i];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   111

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by rules_lex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (rules_symbol_kind_t, rules_translate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by rules_lex.  */
static const rules_type_int8 rules_translate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,     2,     2,     2,    41,     2,
       2,     2,     2,     2,    42,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const rules_type_int16 rules_rline[] =
{
       0,   103,   103,   105,   110,   109,   119,   120,   124,   131,
     138,   138,   138,   143,   146,   152,   185,   194,   197,   200,
     203,   206,   209,   216,   222,   225,   228,   231,   234,   237,
     244,   251,   256,   264,   269,   282,   290,   292,   302,   304,
     309,   313,   321,   326,   331,   336,   344,   349,   353,   367,
     369,   373,   375,   377,   382,   384,   389,   391,   396,   398,
     403,   405,   410,   413,   417,   420,   424,   426,   431,   433
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (rules_symbol_kind_t, rules_stos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *rules_symbol_name (rules_symbol_kind_t rules_symbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const rules_tname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_COMP",
  "TOK_DISABLE", "TOK_DST_IP", "TOK_DST_PORT", "TOK_ENABLE", "TOK_EVAL",
  "TOK_EVENT", "TOK_MIME", "TOK_HEADER", "TOK_IDENT", "TOK_INT", "TOK_IP",
  "TOK_IP6", "TOK_IP_OPTIONS", "TOK_IP_OPTION_SYM", "TOK_IP_PROTO",
  "TOK_PATTERN", "TOK_PATTERN_TYPE", "TOK_PAYLOAD_SIZE", "TOK_PROT",
  "TOK_REQUIRES_SIGNATURE", "TOK_REQUIRES_REVERSE_SIGNATURE",
  "TOK_SIGNATURE", "TOK_SAME_IP", "TOK_SRC_IP", "TOK_SRC_PORT",
  "TOK_TCP_STATE", "TOK_UDP_STATE", "TOK_STRING", "TOK_STATE_SYM",
  "TOK_ACTIVE", "TOK_BOOL", "TOK_POLICY_SYMBOL", "'{'", "'}'", "'['",
  "']'", "'!'", "'&'", "','", "'-'", "':'", "$accept", "rule_list", "rule",
  "$@1", "rule_attr_list", "rule_attr", "$@2", "$@3", "hdr_expr",
  "value_list", "prefix_value_list", "prefix_value", "ranged_value",
  "value", "rangeopt", "range", "ipoption_list", "state_list", "integer",
  "opt_negate", "opt_strength", "string", "pattern", YY_NULLPTR
};

static const char *
rules_symbol_name (rules_symbol_kind_t rules_symbol)
{
  return rules_tname[rules_symbol];
}
#endif

#define YYPACT_NINF (-72)

#define rules_pact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define rules_table_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const rules_type_int8 rules_pact[] =
{
     -72,    24,   -72,    -8,   -72,   -72,   -30,   -72,     9,   -23,
      49,    56,    37,   -72,    -5,    -5,    54,    58,    74,    -7,
      75,    10,    11,   -72,    76,    77,    51,    51,    47,   -72,
     -72,   -72,    42,    50,   -72,    52,   -72,   -72,   -72,    40,
      48,   -72,   -72,    43,    31,   -72,   -72,    -3,   -72,    59,
     -72,    72,   -72,    78,    42,    50,   -72,    55,    55,   -72,
     -72,   -72,   -72,    57,   -72,   -72,    45,   -72,    61,   -72,
     -72,   -72,    62,   -72,    59,    79,   -72,    61,   -72,   -72,
      59,    63,   -72,    64,   -72,   -72,   -72,    57,    61,    66,
      46,    80,    53,   -72,   -72,    81,    65,    67,   -72,   -72,
      36,    59,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
      -1,    59,   -72,   -72,    50,    59,    61,    86,    60,   -72,
     -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const rules_type_int8 rules_defact[] =
{
       3,     0,     1,     0,     2,     4,     0,     7,     0,     0,
       0,     0,     0,    10,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,     0,     0,     0,     0,     0,     5,
       6,    20,     0,     0,    19,     0,    67,    66,    17,    65,
       0,    13,    57,    14,     0,    69,    68,     0,    21,     0,
      24,     0,    26,     0,     0,     0,    59,    31,    32,    33,
      45,    46,    47,     8,    44,    41,    49,    50,     9,    40,
      39,    11,    63,    18,     0,     0,    15,    16,    61,    60,
       0,     0,    51,    54,    23,    25,    27,    29,    30,     0,
       0,     0,     0,    12,    62,     0,     0,    54,    56,    52,
       0,    53,    58,    43,    42,    48,    38,    37,    36,    64,
       0,     0,    22,    55,     0,     0,    35,     0,     0,    49,
      34
};

/* YYPGOTO[NTERM-NUM].  */
static const rules_type_int8 rules_pgoto[] =
{
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -44,
      38,     1,     3,   -71,   -72,    26,   -72,    82,   -46,   -72,
     -72,    91,     7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const rules_type_int8 rules_defgoto[] =
{
       0,     1,     4,     6,     8,    30,    35,    93,    41,    68,
      63,    64,    69,    70,    81,    82,    43,    57,   113,    95,
      73,    38,    48
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const rules_type_int8 rules_table[] =
{
      77,    83,   114,    84,     5,    45,     7,    36,    31,    78,
      79,    88,    46,     9,    10,    11,    12,    13,    14,    15,
      16,   108,    50,    52,     2,    17,    37,    18,    97,    19,
      20,    47,    21,    22,    99,    23,    24,    25,    26,    27,
     115,    80,    28,    65,    66,    67,    29,   120,    45,     3,
      51,    53,    32,    76,    60,    46,    61,    62,   103,    33,
      61,    62,    65,    66,    67,   106,    66,    67,    34,   117,
     116,    78,    79,   119,    67,    42,    40,    44,    49,    54,
      55,    59,    72,    56,    85,    75,    74,    71,    91,   118,
      86,   104,    87,   105,   109,   107,    98,    89,   102,    90,
      96,     0,   100,    92,   110,    94,    39,   112,   101,    58,
       0,   111
};

static const rules_type_int8 rules_check[] =
{
      44,    47,     3,    49,    12,    12,    36,    12,    31,    12,
      13,    55,    19,     4,     5,     6,     7,     8,     9,    10,
      11,    92,    12,    12,     0,    16,    31,    18,    74,    20,
      21,    38,    23,    24,    80,    26,    27,    28,    29,    30,
      41,    44,    33,    12,    13,    14,    37,   118,    12,    25,
      40,    40,     3,    22,    12,    19,    14,    15,    12,     3,
      14,    15,    12,    13,    14,    12,    13,    14,    31,   115,
     114,    12,    13,    13,    14,    17,    22,     3,     3,     3,
       3,    34,    42,    32,    12,    42,    38,    35,    43,     3,
      12,    90,    54,    13,    13,    92,    17,    42,    32,    42,
      74,    -1,    39,    42,    39,    43,    15,   100,    44,    27,
      -1,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const rules_type_int8 rules_stos[] =
{
       0,    46,     0,    25,    47,    12,    48,    36,    49,     4,
       5,     6,     7,     8,     9,    10,    11,    16,    18,    20,
      21,    23,    24,    26,    27,    28,    29,    30,    33,    37,
      50,    31,     3,     3,    31,    51,    12,    31,    66,    66,
      22,    53,    17,    61,     3,    12,    19,    38,    67,     3,
      12,    40,    12,    40,     3,     3,    32,    62,    62,    34,
      12,    14,    15,    55,    56,    12,    13,    14,    54,    57,
      58,    35,    42,    65,    38,    42,    22,    54,    12,    13,
      44,    59,    60,    63,    63,    12,    12,    55,    54,    42,
      42,    43,    42,    52,    43,    64,    60,    63,    17,    63,
      39,    44,    32,    12,    56,    13,    12,    57,    58,    13,
      39,    44,    67,    63,     3,    41,    54,    63,     3,    13,
      58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const rules_type_int8 rules_r1[] =
{
       0,    45,    46,    46,    48,    47,    49,    49,    50,    50,
      51,    52,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    53,    53,    54,    54,    54,    54,
      54,    54,    55,    55,    55,    55,    56,    56,    57,    58,
      58,    59,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const rules_type_int8 rules_r2[] =
{
       0,     2,     2,     0,     0,     6,     2,     0,     3,     3,
       0,     0,     4,     2,     2,     3,     3,     2,     3,     2,
       2,     2,     5,     3,     2,     3,     2,     3,     1,     3,
       3,     2,     2,     2,     8,     6,     3,     3,     3,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     2,     2,     1,     3,     3,     1,     3,     1,
       1,     1,     1,     0,     3,     0,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define rules_errok         (rules_errstatus = 0)
#define rules_clearin       (rules_char = YYEMPTY)

#define YYACCEPT        goto rules_acceptlab
#define YYABORT         goto rules_abortlab
#define YYERROR         goto rules_errorlab
#define YYNOMEM         goto rules_exhaustedlab


#define YYRECOVERING()  (!!rules_errstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (rules_char == YYEMPTY)                                        \
      {                                                           \
        rules_char = (Token);                                         \
        rules_lval = (Value);                                         \
        YYPOPSTACK (rules_len);                                       \
        rules_state = *rules_ssp;                                         \
        goto rules_backup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        rules_error (YY_("syntax error: cannot back up")); \
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
  if (rules_debug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (rules_debug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      rules__symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
rules__symbol_value_print (FILE *rules_o,
                       rules_symbol_kind_t rules_kind, YYSTYPE const * const rules_valuep)
{
  FILE *rules_output = rules_o;
  YY_USE (rules_output);
  if (!rules_valuep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (rules_kind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
rules__symbol_print (FILE *rules_o,
                 rules_symbol_kind_t rules_kind, YYSTYPE const * const rules_valuep)
{
  YYFPRINTF (rules_o, "%s %s (",
             rules_kind < YYNTOKENS ? "token" : "nterm", rules_symbol_name (rules_kind));

  rules__symbol_value_print (rules_o, rules_kind, rules_valuep);
  YYFPRINTF (rules_o, ")");
}

/*------------------------------------------------------------------.
| rules__stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
rules__stack_print (rules__state_t *rules_bottom, rules__state_t *rules_top)
{
  YYFPRINTF (stderr, "Stack now");
  for (; rules_bottom <= rules_top; rules_bottom++)
    {
      int rules_bot = *rules_bottom;
      YYFPRINTF (stderr, " %d", rules_bot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (rules_debug)                                                  \
    rules__stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
rules__reduce_print (rules__state_t *rules_ssp, YYSTYPE *rules_vsp,
                 int rules_rule)
{
  int rules_lno = rules_rline[rules_rule];
  int rules_nrhs = rules_r2[rules_rule];
  int rules_i;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             rules_rule - 1, rules_lno);
  /* The symbols being reduced.  */
  for (rules_i = 0; rules_i < rules_nrhs; rules_i++)
    {
      YYFPRINTF (stderr, "   $%d = ", rules_i + 1);
      rules__symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+rules_ssp[rules_i + 1 - rules_nrhs]),
                       &rules_vsp[(rules_i + 1) - (rules_nrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (rules_debug)                          \
    rules__reduce_print (rules_ssp, rules_vsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int rules_debug;
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
rules_destruct (const char *rules_msg,
            rules_symbol_kind_t rules_kind, YYSTYPE *rules_valuep)
{
  YY_USE (rules_valuep);
  if (!rules_msg)
    rules_msg = "Deleting";
  YY_SYMBOL_PRINT (rules_msg, rules_kind, rules_valuep, rules_locationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (rules_kind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int rules_char;

/* The semantic value of the lookahead symbol.  */
YYSTYPE rules_lval;
/* Number of syntax errors so far.  */
int rules_nerrs;




/*----------.
| rules_parse.  |
`----------*/

int
rules_parse (void)
{
    rules__state_fast_t rules_state = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int rules_errstatus = 0;

    /* Refer to the stacks through separate pointers, to allow rules_overflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T rules_stacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    rules__state_t rules_ssa[YYINITDEPTH];
    rules__state_t *rules_ss = rules_ssa;
    rules__state_t *rules_ssp = rules_ss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE rules_vsa[YYINITDEPTH];
    YYSTYPE *rules_vs = rules_vsa;
    YYSTYPE *rules_vsp = rules_vs;

  int rules_n;
  /* The return value of rules_parse.  */
  int rules_result;
  /* Lookahead symbol kind.  */
  rules_symbol_kind_t rules_token = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE rules_val;



#define YYPOPSTACK(N)   (rules_vsp -= (N), rules_ssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int rules_len = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  rules_char = YYEMPTY; /* Cause a token to be read.  */

  goto rules_setstate;


/*------------------------------------------------------------.
| rules_newstate -- push a new state, which is found in rules_state.  |
`------------------------------------------------------------*/
rules_newstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  rules_ssp++;


/*--------------------------------------------------------------------.
| rules_setstate -- set current state (the top of the stack) to rules_state.  |
`--------------------------------------------------------------------*/
rules_setstate:
  YYDPRINTF ((stderr, "Entering state %d\n", rules_state));
  YY_ASSERT (0 <= rules_state && rules_state < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *rules_ssp = YY_CAST (rules__state_t, rules_state);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (rules_ss, rules_ssp);

  if (rules_ss + rules_stacksize - 1 <= rules_ssp)
#if !defined rules_overflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T rules_size = rules_ssp - rules_ss + 1;

# if defined rules_overflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        rules__state_t *rules_ss1 = rules_ss;
        YYSTYPE *rules_vs1 = rules_vs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if rules_overflow is a macro.  */
        rules_overflow (YY_("memory exhausted"),
                    &rules_ss1, rules_size * YYSIZEOF (*rules_ssp),
                    &rules_vs1, rules_size * YYSIZEOF (*rules_vsp),
                    &rules_stacksize);
        rules_ss = rules_ss1;
        rules_vs = rules_vs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= rules_stacksize)
        YYNOMEM;
      rules_stacksize *= 2;
      if (YYMAXDEPTH < rules_stacksize)
        rules_stacksize = YYMAXDEPTH;

      {
        rules__state_t *rules_ss1 = rules_ss;
        union rules_alloc *rules_ptr =
          YY_CAST (union rules_alloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (rules_stacksize))));
        if (! rules_ptr)
          YYNOMEM;
        YYSTACK_RELOCATE (rules_ss_alloc, rules_ss);
        YYSTACK_RELOCATE (rules_vs_alloc, rules_vs);
#  undef YYSTACK_RELOCATE
        if (rules_ss1 != rules_ssa)
          YYSTACK_FREE (rules_ss1);
      }
# endif

      rules_ssp = rules_ss + rules_size - 1;
      rules_vsp = rules_vs + rules_size - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, rules_stacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (rules_ss + rules_stacksize - 1 <= rules_ssp)
        YYABORT;
    }
#endif /* !defined rules_overflow && !defined YYSTACK_RELOCATE */


  if (rules_state == YYFINAL)
    YYACCEPT;

  goto rules_backup;


/*-----------.
| rules_backup.  |
`-----------*/
rules_backup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  rules_n = rules_pact[rules_state];
  if (rules_pact_value_is_default (rules_n))
    goto rules_default;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (rules_char == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      rules_char = rules_lex ();
    }

  if (rules_char <= YYEOF)
    {
      rules_char = YYEOF;
      rules_token = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (rules_char == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      rules_char = YYUNDEF;
      rules_token = YYSYMBOL_YYerror;
      goto rules_errlab1;
    }
  else
    {
      rules_token = YYTRANSLATE (rules_char);
      YY_SYMBOL_PRINT ("Next token is", rules_token, &rules_lval, &rules_lloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  rules_n += rules_token;
  if (rules_n < 0 || YYLAST < rules_n || rules_check[rules_n] != rules_token)
    goto rules_default;
  rules_n = rules_table[rules_n];
  if (rules_n <= 0)
    {
      if (rules_table_value_is_error (rules_n))
        goto rules_errlab;
      rules_n = -rules_n;
      goto rules_reduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (rules_errstatus)
    rules_errstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", rules_token, &rules_lval, &rules_lloc);
  rules_state = rules_n;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++rules_vsp = rules_lval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  rules_char = YYEMPTY;
  goto rules_newstate;


/*-----------------------------------------------------------.
| rules_default -- do the default action for the current state.  |
`-----------------------------------------------------------*/
rules_default:
  rules_n = rules_defact[rules_state];
  if (rules_n == 0)
    goto rules_errlab;
  goto rules_reduce;


/*-----------------------------.
| rules_reduce -- do a reduction.  |
`-----------------------------*/
rules_reduce:
  /* rules_n is the number of a rule to reduce with.  */
  rules_len = rules_r2[rules_n];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  rules_val = rules_vsp[1-rules_len];


  YY_REDUCE_PRINT (rules_n);
  switch (rules_n)
    {
  case 2: /* rule_list: rule_list rule  */
#line 104 "rule-parse.y"
                        { zeek::detail::rule_matcher->AddRule((rules_vsp[0].rule)); }
#line 1241 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 4: /* $@1: %empty  */
#line 110 "rule-parse.y"
                        {
			zeek::detail::Location l(current_rule_file, rules_line_number+1, 0, 0, 0);
			current_rule = new zeek::detail::Rule(rules_lval.str, l);
			}
#line 1250 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 5: /* rule: TOK_SIGNATURE TOK_IDENT $@1 '{' rule_attr_list '}'  */
#line 115 "rule-parse.y"
                        { (rules_val.rule) = current_rule; }
#line 1256 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 8: /* rule_attr: TOK_DST_IP TOK_COMP prefix_value_list  */
#line 125 "rule-parse.y"
                        {
			current_rule->AddHdrTest(new zeek::detail::RuleHdrTest(
				zeek::detail::RuleHdrTest::IPDst,
				(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), *((rules_vsp[0].prefix_val_list))));
			}
#line 1266 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 9: /* rule_attr: TOK_DST_PORT TOK_COMP value_list  */
#line 132 "rule-parse.y"
                        { // Works for both TCP and UDP
			current_rule->AddHdrTest(new zeek::detail::RuleHdrTest(
				zeek::detail::RuleHdrTest::TCP, 2, 2,
				(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), (rules_vsp[0].vallist)));
			}
#line 1276 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 10: /* $@2: %empty  */
#line 138 "rule-parse.y"
                         { begin_PS(); }
#line 1282 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 11: /* $@3: %empty  */
#line 138 "rule-parse.y"
                                                           { end_PS(); }
#line 1288 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 12: /* rule_attr: TOK_EVAL $@2 TOK_POLICY_SYMBOL $@3  */
#line 139 "rule-parse.y"
                        {
			current_rule->AddCondition(new zeek::detail::RuleConditionEval((rules_vsp[-1].str)));
			}
#line 1296 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 13: /* rule_attr: TOK_HEADER hdr_expr  */
#line 144 "rule-parse.y"
                        { current_rule->AddHdrTest((rules_vsp[0].hdr_test)); }
#line 1302 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 14: /* rule_attr: TOK_IP_OPTIONS ipoption_list  */
#line 147 "rule-parse.y"
                        {
			current_rule->AddCondition(
				new zeek::detail::RuleConditionIPOptions((rules_vsp[0].val)));
			}
#line 1311 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 15: /* rule_attr: TOK_IP_PROTO TOK_COMP TOK_PROT  */
#line 153 "rule-parse.y"
                        {
			int proto = 0;
			switch ( (rules_vsp[0].prot) ) {
			case zeek::detail::RuleHdrTest::ICMP: proto = IPPROTO_ICMP; break;
			case zeek::detail::RuleHdrTest::ICMPv6: proto = IPPROTO_ICMPV6; break;
			// signature matching against outer packet headers of IP-in-IP
			// tunneling not supported, so do a no-op there
			case zeek::detail::RuleHdrTest::IP: proto = 0; break;
			case zeek::detail::RuleHdrTest::IPv6: proto = 0; break;
			case zeek::detail::RuleHdrTest::TCP: proto = IPPROTO_TCP; break;
			case zeek::detail::RuleHdrTest::UDP: proto = IPPROTO_UDP; break;
			default:
				rules_error("internal_error: unknown protocol");
			}

			if ( proto )
				{
				auto* vallist = new zeek::detail::maskedvalue_list;
				auto* val = new zeek::detail::MaskedValue();

				val->val = proto;
				val->mask = 0xffffffff;
				vallist->push_back(val);

				// offset & size params are dummies, actual next proto value in
				// header is retrieved dynamically via IP_Hdr::NextProto()
				current_rule->AddHdrTest(new zeek::detail::RuleHdrTest(
					zeek::detail::RuleHdrTest::NEXT, 0, 0,
					(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), vallist));
				}
			}
#line 1347 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 16: /* rule_attr: TOK_IP_PROTO TOK_COMP value_list  */
#line 186 "rule-parse.y"
                        {
			// offset & size params are dummies, actual next proto value in
			// header is retrieved dynamically via IP_Hdr::NextProto()
			current_rule->AddHdrTest(new zeek::detail::RuleHdrTest(
				zeek::detail::RuleHdrTest::NEXT, 0, 0,
				(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), (rules_vsp[0].vallist)));
			}
#line 1359 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 17: /* rule_attr: TOK_EVENT string  */
#line 195 "rule-parse.y"
                        { current_rule->AddAction(new zeek::detail::RuleActionEvent((rules_vsp[0].str))); }
#line 1365 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 18: /* rule_attr: TOK_MIME string opt_strength  */
#line 198 "rule-parse.y"
                        { current_rule->AddAction(new zeek::detail::RuleActionMIME((rules_vsp[-1].str), (rules_vsp[0].val))); }
#line 1371 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 19: /* rule_attr: TOK_ENABLE TOK_STRING  */
#line 201 "rule-parse.y"
                        { current_rule->AddAction(new zeek::detail::RuleActionEnable((rules_vsp[0].str))); }
#line 1377 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 20: /* rule_attr: TOK_DISABLE TOK_STRING  */
#line 204 "rule-parse.y"
                        { current_rule->AddAction(new zeek::detail::RuleActionDisable((rules_vsp[0].str))); }
#line 1383 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 21: /* rule_attr: TOK_PATTERN_TYPE pattern  */
#line 207 "rule-parse.y"
                        { current_rule->AddPattern((rules_vsp[0].str), (rules_vsp[-1].ptype)); }
#line 1389 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 22: /* rule_attr: TOK_PATTERN_TYPE '[' rangeopt ']' pattern  */
#line 210 "rule-parse.y"
                        {
			if ( (rules_vsp[-2].range).offset > 0 )
				zeek::reporter->Warning("Offsets are currently ignored for patterns");
			current_rule->AddPattern((rules_vsp[0].str), (rules_vsp[-4].ptype), 0, (rules_vsp[-2].range).len);
			}
#line 1399 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 23: /* rule_attr: TOK_PAYLOAD_SIZE TOK_COMP integer  */
#line 217 "rule-parse.y"
                        {
			current_rule->AddCondition(
				new zeek::detail::RuleConditionPayloadSize((rules_vsp[0].val), (zeek::detail::RuleConditionPayloadSize::Comp) ((rules_vsp[-1].val))));
			}
#line 1408 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 24: /* rule_attr: TOK_REQUIRES_SIGNATURE TOK_IDENT  */
#line 223 "rule-parse.y"
                        { current_rule->AddRequires((rules_vsp[0].str), 0, 0); }
#line 1414 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 25: /* rule_attr: TOK_REQUIRES_SIGNATURE '!' TOK_IDENT  */
#line 226 "rule-parse.y"
                        { current_rule->AddRequires((rules_vsp[0].str), 0, 1); }
#line 1420 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 26: /* rule_attr: TOK_REQUIRES_REVERSE_SIGNATURE TOK_IDENT  */
#line 229 "rule-parse.y"
                        { current_rule->AddRequires((rules_vsp[0].str), 1, 0); }
#line 1426 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 27: /* rule_attr: TOK_REQUIRES_REVERSE_SIGNATURE '!' TOK_IDENT  */
#line 232 "rule-parse.y"
                        { current_rule->AddRequires((rules_vsp[0].str), 1, 1); }
#line 1432 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 28: /* rule_attr: TOK_SAME_IP  */
#line 235 "rule-parse.y"
                        { current_rule->AddCondition(new zeek::detail::RuleConditionSameIP()); }
#line 1438 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 29: /* rule_attr: TOK_SRC_IP TOK_COMP prefix_value_list  */
#line 238 "rule-parse.y"
                        {
			current_rule->AddHdrTest(new zeek::detail::RuleHdrTest(
				zeek::detail::RuleHdrTest::IPSrc,
				(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), *((rules_vsp[0].prefix_val_list))));
			}
#line 1448 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 30: /* rule_attr: TOK_SRC_PORT TOK_COMP value_list  */
#line 245 "rule-parse.y"
                        { // Works for both TCP and UDP
			current_rule->AddHdrTest(new zeek::detail::RuleHdrTest(
				zeek::detail::RuleHdrTest::TCP, 0, 2,
				(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), (rules_vsp[0].vallist)));
			}
#line 1458 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 31: /* rule_attr: TOK_TCP_STATE state_list  */
#line 252 "rule-parse.y"
                        {
			current_rule->AddCondition(new zeek::detail::RuleConditionTCPState((rules_vsp[0].val)));
			}
#line 1466 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 32: /* rule_attr: TOK_UDP_STATE state_list  */
#line 257 "rule-parse.y"
                        {
			if ( (rules_vsp[0].val) & zeek::detail::RULE_STATE_ESTABLISHED )
				rules_error("'established' is not a valid 'udp-state'");

			current_rule->AddCondition(new zeek::detail::RuleConditionUDPState((rules_vsp[0].val)));
			}
#line 1477 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 33: /* rule_attr: TOK_ACTIVE TOK_BOOL  */
#line 265 "rule-parse.y"
                        { current_rule->SetActiveStatus((rules_vsp[0].bl)); }
#line 1483 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 34: /* hdr_expr: TOK_PROT '[' range ']' '&' integer TOK_COMP value  */
#line 270 "rule-parse.y"
                        {
			auto* vallist = new zeek::detail::maskedvalue_list;
			auto* val = new zeek::detail::MaskedValue();

			val->val = (rules_vsp[0].mval).val;
			val->mask = (rules_vsp[-2].val);
			vallist->push_back(val);

			(rules_val.hdr_test) = new zeek::detail::RuleHdrTest((rules_vsp[-7].prot), (rules_vsp[-5].range).offset, (rules_vsp[-5].range).len,
					(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), vallist);
			}
#line 1499 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 35: /* hdr_expr: TOK_PROT '[' range ']' TOK_COMP value_list  */
#line 283 "rule-parse.y"
                        {
			(rules_val.hdr_test) = new zeek::detail::RuleHdrTest((rules_vsp[-5].prot), (rules_vsp[-3].range).offset, (rules_vsp[-3].range).len,
						(zeek::detail::RuleHdrTest::Comp) (rules_vsp[-1].val), (rules_vsp[0].vallist));
			}
#line 1508 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 36: /* value_list: value_list ',' value  */
#line 291 "rule-parse.y"
                        { (rules_vsp[-2].vallist)->push_back(new zeek::detail::MaskedValue((rules_vsp[0].mval))); (rules_val.vallist) = (rules_vsp[-2].vallist); }
#line 1514 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 37: /* value_list: value_list ',' ranged_value  */
#line 293 "rule-parse.y"
                        {
			int numVals = (rules_vsp[0].vallist)->length();
			for ( int idx = 0; idx < numVals; idx++ )
				{
				zeek::detail::MaskedValue* val = (*(rules_vsp[0].vallist))[idx];
				(rules_vsp[-2].vallist)->push_back(val);
				}
			(rules_val.vallist) = (rules_vsp[-2].vallist);
			}
#line 1528 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 38: /* value_list: value_list ',' TOK_IDENT  */
#line 303 "rule-parse.y"
                        { id_to_maskedvallist((rules_vsp[0].str), (rules_vsp[-2].vallist)); (rules_val.vallist) = (rules_vsp[-2].vallist); }
#line 1534 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 39: /* value_list: value  */
#line 305 "rule-parse.y"
                        {
			(rules_val.vallist) = new zeek::detail::maskedvalue_list();
			(rules_val.vallist)->push_back(new zeek::detail::MaskedValue((rules_vsp[0].mval)));
			}
#line 1543 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 40: /* value_list: ranged_value  */
#line 310 "rule-parse.y"
                        {
			(rules_val.vallist) = (rules_vsp[0].vallist);
			}
#line 1551 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 41: /* value_list: TOK_IDENT  */
#line 314 "rule-parse.y"
                        {
			(rules_val.vallist) = new zeek::detail::maskedvalue_list();
			id_to_maskedvallist((rules_vsp[0].str), (rules_val.vallist));
			}
#line 1560 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 42: /* prefix_value_list: prefix_value_list ',' prefix_value  */
#line 322 "rule-parse.y"
                        {
			(rules_val.prefix_val_list) = (rules_vsp[-2].prefix_val_list);
			(rules_val.prefix_val_list)->push_back(*((rules_vsp[0].prefixval)));
			}
#line 1569 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 43: /* prefix_value_list: prefix_value_list ',' TOK_IDENT  */
#line 327 "rule-parse.y"
                        {
			(rules_val.prefix_val_list) = (rules_vsp[-2].prefix_val_list);
			id_to_maskedvallist((rules_vsp[0].str), 0, (rules_vsp[-2].prefix_val_list));
			}
#line 1578 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 44: /* prefix_value_list: prefix_value  */
#line 332 "rule-parse.y"
                        {
			(rules_val.prefix_val_list) = new std::vector<zeek::IPPrefix>();
			(rules_val.prefix_val_list)->push_back(*((rules_vsp[0].prefixval)));
			}
#line 1587 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 45: /* prefix_value_list: TOK_IDENT  */
#line 337 "rule-parse.y"
                        {
			(rules_val.prefix_val_list) = new std::vector<zeek::IPPrefix>();
			id_to_maskedvallist((rules_vsp[0].str), 0, (rules_val.prefix_val_list));
			}
#line 1596 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 46: /* prefix_value: TOK_IP  */
#line 345 "rule-parse.y"
                        {
			(rules_val.prefixval) = new zeek::IPPrefix(zeek::IPAddr(IPv4, &((rules_vsp[0].mval).val), zeek::IPAddr::Host),
			                        ip4_mask_to_len((rules_vsp[0].mval).mask));
			}
#line 1605 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 48: /* ranged_value: TOK_INT '-' TOK_INT  */
#line 354 "rule-parse.y"
                        {
			(rules_val.vallist) = new zeek::detail::maskedvalue_list();
			for ( int val = (rules_vsp[-2].val); val <= (rules_vsp[0].val); val++ )
				{
				auto* masked = new zeek::detail::MaskedValue();
				masked->val = val;
				masked->mask = 0xffffffff;
				(rules_val.vallist)->push_back(masked);
				}
			}
#line 1620 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 49: /* value: TOK_INT  */
#line 368 "rule-parse.y"
                        { (rules_val.mval).val = (rules_vsp[0].val); (rules_val.mval).mask = 0xffffffff; }
#line 1626 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 51: /* rangeopt: range  */
#line 374 "rule-parse.y"
                        { (rules_val.range) = (rules_vsp[0].range); }
#line 1632 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 52: /* rangeopt: ':' integer  */
#line 376 "rule-parse.y"
                        { (rules_val.range).offset = 0; (rules_val.range).len = (rules_vsp[0].val); }
#line 1638 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 53: /* rangeopt: integer ':'  */
#line 378 "rule-parse.y"
                        { (rules_val.range).offset = (rules_vsp[-1].val); (rules_val.range).len = UINT_MAX; }
#line 1644 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 54: /* range: integer  */
#line 383 "rule-parse.y"
                        { (rules_val.range).offset = (rules_vsp[0].val); (rules_val.range).len = 1; }
#line 1650 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 55: /* range: integer ':' integer  */
#line 385 "rule-parse.y"
                        { (rules_val.range).offset = (rules_vsp[-2].val); (rules_val.range).len = (rules_vsp[0].val); }
#line 1656 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 56: /* ipoption_list: ipoption_list ',' TOK_IP_OPTION_SYM  */
#line 390 "rule-parse.y"
                        { (rules_val.val) = (rules_vsp[-2].val) | (rules_vsp[0].val); }
#line 1662 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 57: /* ipoption_list: TOK_IP_OPTION_SYM  */
#line 392 "rule-parse.y"
                        { (rules_val.val) = (rules_vsp[0].val); }
#line 1668 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 58: /* state_list: state_list ',' TOK_STATE_SYM  */
#line 397 "rule-parse.y"
                        { (rules_val.val) = (rules_vsp[-2].val) | (rules_vsp[0].val); }
#line 1674 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 59: /* state_list: TOK_STATE_SYM  */
#line 399 "rule-parse.y"
                        { (rules_val.val) = (rules_vsp[0].val); }
#line 1680 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 60: /* integer: TOK_INT  */
#line 404 "rule-parse.y"
                        { (rules_val.val) = (rules_vsp[0].val); }
#line 1686 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 61: /* integer: TOK_IDENT  */
#line 406 "rule-parse.y"
                        { (rules_val.val) = id_to_uint((rules_vsp[0].str)); }
#line 1692 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 62: /* opt_negate: '-'  */
#line 411 "rule-parse.y"
                        { (rules_val.bl) = true; }
#line 1698 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 63: /* opt_negate: %empty  */
#line 413 "rule-parse.y"
                        { (rules_val.bl) = false; }
#line 1704 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 64: /* opt_strength: ',' opt_negate TOK_INT  */
#line 418 "rule-parse.y"
                        { (rules_val.val) = (rules_vsp[-1].bl) ? -(rules_vsp[0].val) : (rules_vsp[0].val); }
#line 1710 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 65: /* opt_strength: %empty  */
#line 420 "rule-parse.y"
                        { (rules_val.val) = 0; }
#line 1716 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 66: /* string: TOK_STRING  */
#line 425 "rule-parse.y"
                        { (rules_val.str) = (rules_vsp[0].str); }
#line 1722 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 67: /* string: TOK_IDENT  */
#line 427 "rule-parse.y"
                        { (rules_val.str) = id_to_str((rules_vsp[0].str)); }
#line 1728 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 68: /* pattern: TOK_PATTERN  */
#line 432 "rule-parse.y"
                        { (rules_val.str) = (rules_vsp[0].str); }
#line 1734 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;

  case 69: /* pattern: TOK_IDENT  */
#line 434 "rule-parse.y"
                        { (rules_val.str) = id_to_str((rules_vsp[0].str)); }
#line 1740 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"
    break;


#line 1744 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.cc"

      default: break;
    }
  /* User semantic actions sometimes alter rules_char, and that requires
     that rules_token be updated with the new translation.  We take the
     approach of translating immediately before every use of rules_token.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering rules_char or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (rules_symbol_kind_t, rules_r1[rules_n]), &rules_val, &rules_loc);

  YYPOPSTACK (rules_len);
  rules_len = 0;

  *++rules_vsp = rules_val;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int rules_lhs = rules_r1[rules_n] - YYNTOKENS;
    const int rules_i = rules_pgoto[rules_lhs] + *rules_ssp;
    rules_state = (0 <= rules_i && rules_i <= YYLAST && rules_check[rules_i] == *rules_ssp
               ? rules_table[rules_i]
               : rules_defgoto[rules_lhs]);
  }

  goto rules_newstate;


/*--------------------------------------.
| rules_errlab -- here on detecting error.  |
`--------------------------------------*/
rules_errlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  rules_token = rules_char == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (rules_char);
  /* If not already recovering from an error, report this error.  */
  if (!rules_errstatus)
    {
      ++rules_nerrs;
      rules_error (YY_("syntax error"));
    }

  if (rules_errstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (rules_char <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (rules_char == YYEOF)
            YYABORT;
        }
      else
        {
          rules_destruct ("Error: discarding",
                      rules_token, &rules_lval);
          rules_char = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto rules_errlab1;


/*---------------------------------------------------.
| rules_errorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
rules_errorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label rules_errorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++rules_nerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (rules_len);
  rules_len = 0;
  YY_STACK_PRINT (rules_ss, rules_ssp);
  rules_state = *rules_ssp;
  goto rules_errlab1;


/*-------------------------------------------------------------.
| rules_errlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
rules_errlab1:
  rules_errstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      rules_n = rules_pact[rules_state];
      if (!rules_pact_value_is_default (rules_n))
        {
          rules_n += YYSYMBOL_YYerror;
          if (0 <= rules_n && rules_n <= YYLAST && rules_check[rules_n] == YYSYMBOL_YYerror)
            {
              rules_n = rules_table[rules_n];
              if (0 < rules_n)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (rules_ssp == rules_ss)
        YYABORT;


      rules_destruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (rules_state), rules_vsp);
      YYPOPSTACK (1);
      rules_state = *rules_ssp;
      YY_STACK_PRINT (rules_ss, rules_ssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++rules_vsp = rules_lval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (rules_n), rules_vsp, rules_lsp);

  rules_state = rules_n;
  goto rules_newstate;


/*-------------------------------------.
| rules_acceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
rules_acceptlab:
  rules_result = 0;
  goto rules_returnlab;


/*-----------------------------------.
| rules_abortlab -- YYABORT comes here.  |
`-----------------------------------*/
rules_abortlab:
  rules_result = 1;
  goto rules_returnlab;


/*-----------------------------------------------------------.
| rules_exhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
rules_exhaustedlab:
  rules_error (YY_("memory exhausted"));
  rules_result = 2;
  goto rules_returnlab;


/*----------------------------------------------------------.
| rules_returnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
rules_returnlab:
  if (rules_char != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      rules_token = YYTRANSLATE (rules_char);
      rules_destruct ("Cleanup: discarding lookahead",
                  rules_token, &rules_lval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (rules_len);
  YY_STACK_PRINT (rules_ss, rules_ssp);
  while (rules_ssp != rules_ss)
    {
      rules_destruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*rules_ssp), rules_vsp);
      YYPOPSTACK (1);
    }
#ifndef rules_overflow
  if (rules_ss != rules_ssa)
    YYSTACK_FREE (rules_ss);
#endif

  return rules_result;
}

#line 437 "rule-parse.y"


void rules_error(const char* msg)
	{
	zeek::reporter->Error("Error in signature (%s:%d): %s\n",
	                      current_rule_file, rules_line_number+1, msg);
	zeek::detail::rule_matcher->SetParseError();
	}

void rules_error(const char* msg, const char* addl)
	{
	zeek::reporter->Error("Error in signature (%s:%d): %s (%s)\n",
	                      current_rule_file, rules_line_number+1, msg, addl);
	zeek::detail::rule_matcher->SetParseError();
	}

void rules_error(zeek::detail::Rule* r, const char* msg)
	{
	const zeek::detail::Location& l = r->GetLocation();
	zeek::reporter->Error("Error in signature %s (%s:%d): %s\n",
	                      r->ID(), l.filename, l.first_line, msg);
	zeek::detail::rule_matcher->SetParseError();
	}

int rules_wrap(void)
	{
	return 1;
	}
