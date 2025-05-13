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
#line 83 "pac_parse.yy"


#include "pac_action.h"
#include "pac_analyzer.h"
#include "pac_array.h"
#include "pac_attr.h"
#include "pac_case.h"
#include "pac_common.h"
#include "pac_conn.h"
#include "pac_context.h"
#include "pac_cstr.h"
#include "pac_dataptr.h"
#include "pac_dataunit.h"
#include "pac_dbg.h"
#include "pac_decl.h"
#include "pac_embedded.h"
#include "pac_enum.h"
#include "pac_exception.h"
#include "pac_expr.h"
#include "pac_exttype.h"
#include "pac_flow.h"
#include "pac_func.h"
#include "pac_id.h"
#include "pac_inputbuf.h"
#include "pac_let.h"
#include "pac_output.h"
#include "pac_param.h"
#include "pac_paramtype.h"
#include "pac_primitive.h"
#include "pac_record.h"
#include "pac_redef.h"
#include "pac_regex.h"
#include "pac_state.h"
#include "pac_strtype.h"
#include "pac_type.h"
#include "pac_utils.h"
#include "pac_withinput.h"

extern int yyerror(const char msg[]);
extern int yylex();
extern int yychar;
extern char* yytext;
extern int yyleng;
extern void begin_RE();
extern void end_RE();

extern string input_filename;
extern int line_number;
extern Output* header_output;
extern Output* source_output;


#line 124 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"

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

#include "pac_parse.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_TYPE = 3,                   /* TOK_TYPE  */
  YYSYMBOL_TOK_RECORD = 4,                 /* TOK_RECORD  */
  YYSYMBOL_TOK_CASE = 5,                   /* TOK_CASE  */
  YYSYMBOL_TOK_ENUM = 6,                   /* TOK_ENUM  */
  YYSYMBOL_TOK_LET = 7,                    /* TOK_LET  */
  YYSYMBOL_TOK_FUNCTION = 8,               /* TOK_FUNCTION  */
  YYSYMBOL_TOK_REFINE = 9,                 /* TOK_REFINE  */
  YYSYMBOL_TOK_CASEFUNC = 10,              /* TOK_CASEFUNC  */
  YYSYMBOL_TOK_CASETYPE = 11,              /* TOK_CASETYPE  */
  YYSYMBOL_TOK_TYPEATTR = 12,              /* TOK_TYPEATTR  */
  YYSYMBOL_TOK_HELPERHEADER = 13,          /* TOK_HELPERHEADER  */
  YYSYMBOL_TOK_HELPERCODE = 14,            /* TOK_HELPERCODE  */
  YYSYMBOL_TOK_RIGHTARROW = 15,            /* TOK_RIGHTARROW  */
  YYSYMBOL_TOK_DEFAULT = 16,               /* TOK_DEFAULT  */
  YYSYMBOL_TOK_OF = 17,                    /* TOK_OF  */
  YYSYMBOL_TOK_PADDING = 18,               /* TOK_PADDING  */
  YYSYMBOL_TOK_TO = 19,                    /* TOK_TO  */
  YYSYMBOL_TOK_ALIGN = 20,                 /* TOK_ALIGN  */
  YYSYMBOL_TOK_WITHINPUT = 21,             /* TOK_WITHINPUT  */
  YYSYMBOL_TOK_INT8 = 22,                  /* TOK_INT8  */
  YYSYMBOL_TOK_INT16 = 23,                 /* TOK_INT16  */
  YYSYMBOL_TOK_INT32 = 24,                 /* TOK_INT32  */
  YYSYMBOL_TOK_INT64 = 25,                 /* TOK_INT64  */
  YYSYMBOL_TOK_UINT8 = 26,                 /* TOK_UINT8  */
  YYSYMBOL_TOK_UINT16 = 27,                /* TOK_UINT16  */
  YYSYMBOL_TOK_UINT32 = 28,                /* TOK_UINT32  */
  YYSYMBOL_TOK_UINT64 = 29,                /* TOK_UINT64  */
  YYSYMBOL_TOK_ID = 30,                    /* TOK_ID  */
  YYSYMBOL_TOK_NUMBER = 31,                /* TOK_NUMBER  */
  YYSYMBOL_TOK_REGEX = 32,                 /* TOK_REGEX  */
  YYSYMBOL_TOK_STRING = 33,                /* TOK_STRING  */
  YYSYMBOL_TOK_BEGIN_RE = 34,              /* TOK_BEGIN_RE  */
  YYSYMBOL_TOK_END_RE = 35,                /* TOK_END_RE  */
  YYSYMBOL_TOK_ATTR_ALSO = 36,             /* TOK_ATTR_ALSO  */
  YYSYMBOL_TOK_ATTR_BYTEORDER = 37,        /* TOK_ATTR_BYTEORDER  */
  YYSYMBOL_TOK_ATTR_CHECK = 38,            /* TOK_ATTR_CHECK  */
  YYSYMBOL_TOK_ATTR_CHUNKED = 39,          /* TOK_ATTR_CHUNKED  */
  YYSYMBOL_TOK_ATTR_ENFORCE = 40,          /* TOK_ATTR_ENFORCE  */
  YYSYMBOL_TOK_ATTR_EXPORTSOURCEDATA = 41, /* TOK_ATTR_EXPORTSOURCEDATA  */
  YYSYMBOL_TOK_ATTR_IF = 42,               /* TOK_ATTR_IF  */
  YYSYMBOL_TOK_ATTR_LENGTH = 43,           /* TOK_ATTR_LENGTH  */
  YYSYMBOL_TOK_ATTR_LET = 44,              /* TOK_ATTR_LET  */
  YYSYMBOL_TOK_ATTR_LINEBREAKER = 45,      /* TOK_ATTR_LINEBREAKER  */
  YYSYMBOL_TOK_ATTR_MULTILINE = 46,        /* TOK_ATTR_MULTILINE  */
  YYSYMBOL_TOK_ATTR_ONELINE = 47,          /* TOK_ATTR_ONELINE  */
  YYSYMBOL_TOK_ATTR_REFCOUNT = 48,         /* TOK_ATTR_REFCOUNT  */
  YYSYMBOL_TOK_ATTR_REQUIRES = 49,         /* TOK_ATTR_REQUIRES  */
  YYSYMBOL_TOK_ATTR_RESTOFDATA = 50,       /* TOK_ATTR_RESTOFDATA  */
  YYSYMBOL_TOK_ATTR_RESTOFFLOW = 51,       /* TOK_ATTR_RESTOFFLOW  */
  YYSYMBOL_TOK_ATTR_TRANSIENT = 52,        /* TOK_ATTR_TRANSIENT  */
  YYSYMBOL_TOK_ATTR_UNTIL = 53,            /* TOK_ATTR_UNTIL  */
  YYSYMBOL_TOK_ANALYZER = 54,              /* TOK_ANALYZER  */
  YYSYMBOL_TOK_CONNECTION = 55,            /* TOK_CONNECTION  */
  YYSYMBOL_TOK_FLOW = 56,                  /* TOK_FLOW  */
  YYSYMBOL_TOK_STATE = 57,                 /* TOK_STATE  */
  YYSYMBOL_TOK_ACTION = 58,                /* TOK_ACTION  */
  YYSYMBOL_TOK_WHEN = 59,                  /* TOK_WHEN  */
  YYSYMBOL_TOK_HELPER = 60,                /* TOK_HELPER  */
  YYSYMBOL_TOK_DATAUNIT = 61,              /* TOK_DATAUNIT  */
  YYSYMBOL_TOK_FLOWDIR = 62,               /* TOK_FLOWDIR  */
  YYSYMBOL_TOK_WITHCONTEXT = 63,           /* TOK_WITHCONTEXT  */
  YYSYMBOL_TOK_LPB_EXTERN = 64,            /* TOK_LPB_EXTERN  */
  YYSYMBOL_TOK_LPB_HEADER = 65,            /* TOK_LPB_HEADER  */
  YYSYMBOL_TOK_LPB_CODE = 66,              /* TOK_LPB_CODE  */
  YYSYMBOL_TOK_LPB_MEMBER = 67,            /* TOK_LPB_MEMBER  */
  YYSYMBOL_TOK_LPB_INIT = 68,              /* TOK_LPB_INIT  */
  YYSYMBOL_TOK_LPB_CLEANUP = 69,           /* TOK_LPB_CLEANUP  */
  YYSYMBOL_TOK_LPB_EOF = 70,               /* TOK_LPB_EOF  */
  YYSYMBOL_TOK_LPB = 71,                   /* TOK_LPB  */
  YYSYMBOL_TOK_RPB = 72,                   /* TOK_RPB  */
  YYSYMBOL_TOK_EMBEDDED_ATOM = 73,         /* TOK_EMBEDDED_ATOM  */
  YYSYMBOL_TOK_EMBEDDED_STRING = 74,       /* TOK_EMBEDDED_STRING  */
  YYSYMBOL_TOK_PAC_VAL = 75,               /* TOK_PAC_VAL  */
  YYSYMBOL_TOK_PAC_SET = 76,               /* TOK_PAC_SET  */
  YYSYMBOL_TOK_PAC_TYPE = 77,              /* TOK_PAC_TYPE  */
  YYSYMBOL_TOK_PAC_TYPEOF = 78,            /* TOK_PAC_TYPEOF  */
  YYSYMBOL_TOK_PAC_CONST_DEF = 79,         /* TOK_PAC_CONST_DEF  */
  YYSYMBOL_TOK_END_PAC = 80,               /* TOK_END_PAC  */
  YYSYMBOL_TOK_EXTERN = 81,                /* TOK_EXTERN  */
  YYSYMBOL_82_ = 82,                       /* '='  */
  YYSYMBOL_TOK_PLUSEQ = 83,                /* TOK_PLUSEQ  */
  YYSYMBOL_84_ = 84,                       /* ';'  */
  YYSYMBOL_85_ = 85,                       /* ','  */
  YYSYMBOL_86_ = 86,                       /* '?'  */
  YYSYMBOL_87_ = 87,                       /* ':'  */
  YYSYMBOL_TOK_OR = 88,                    /* TOK_OR  */
  YYSYMBOL_TOK_AND = 89,                   /* TOK_AND  */
  YYSYMBOL_TOK_EQUAL = 90,                 /* TOK_EQUAL  */
  YYSYMBOL_TOK_NEQ = 91,                   /* TOK_NEQ  */
  YYSYMBOL_TOK_LE = 92,                    /* TOK_LE  */
  YYSYMBOL_TOK_GE = 93,                    /* TOK_GE  */
  YYSYMBOL_94_ = 94,                       /* '<'  */
  YYSYMBOL_95_ = 95,                       /* '>'  */
  YYSYMBOL_96_ = 96,                       /* '&'  */
  YYSYMBOL_97_ = 97,                       /* '|'  */
  YYSYMBOL_98_ = 98,                       /* '^'  */
  YYSYMBOL_TOK_LSHIFT = 99,                /* TOK_LSHIFT  */
  YYSYMBOL_TOK_RSHIFT = 100,               /* TOK_RSHIFT  */
  YYSYMBOL_101_ = 101,                     /* '+'  */
  YYSYMBOL_102_ = 102,                     /* '-'  */
  YYSYMBOL_103_ = 103,                     /* '*'  */
  YYSYMBOL_104_ = 104,                     /* '/'  */
  YYSYMBOL_105_ = 105,                     /* '%'  */
  YYSYMBOL_106_ = 106,                     /* '~'  */
  YYSYMBOL_107_ = 107,                     /* '!'  */
  YYSYMBOL_TOK_SIZEOF = 108,               /* TOK_SIZEOF  */
  YYSYMBOL_TOK_OFFSETOF = 109,             /* TOK_OFFSETOF  */
  YYSYMBOL_110_ = 110,                     /* '('  */
  YYSYMBOL_111_ = 111,                     /* ')'  */
  YYSYMBOL_112_ = 112,                     /* '['  */
  YYSYMBOL_113_ = 113,                     /* ']'  */
  YYSYMBOL_114_ = 114,                     /* '.'  */
  YYSYMBOL_115_ = 115,                     /* '{'  */
  YYSYMBOL_116_ = 116,                     /* '}'  */
  YYSYMBOL_YYACCEPT = 117,                 /* $accept  */
  YYSYMBOL_decls = 118,                    /* decls  */
  YYSYMBOL_decl = 119,                     /* decl  */
  YYSYMBOL_decl_with_attr = 120,           /* decl_with_attr  */
  YYSYMBOL_121_1 = 121,                    /* $@1  */
  YYSYMBOL_122_2 = 122,                    /* $@2  */
  YYSYMBOL_123_3 = 123,                    /* $@3  */
  YYSYMBOL_124_4 = 124,                    /* $@4  */
  YYSYMBOL_125_5 = 125,                    /* $@5  */
  YYSYMBOL_126_6 = 126,                    /* $@6  */
  YYSYMBOL_127_7 = 127,                    /* $@7  */
  YYSYMBOL_128_8 = 128,                    /* $@8  */
  YYSYMBOL_decl_without_attr = 129,        /* decl_without_attr  */
  YYSYMBOL_optsemicolon = 130,             /* optsemicolon  */
  YYSYMBOL_tok_id = 131,                   /* tok_id  */
  YYSYMBOL_analyzercontext = 132,          /* analyzercontext  */
  YYSYMBOL_contextfieldlist = 133,         /* contextfieldlist  */
  YYSYMBOL_contextfield = 134,             /* contextfield  */
  YYSYMBOL_funcproto = 135,                /* funcproto  */
  YYSYMBOL_function = 136,                 /* function  */
  YYSYMBOL_optparams = 137,                /* optparams  */
  YYSYMBOL_paramlist = 138,                /* paramlist  */
  YYSYMBOL_param = 139,                    /* param  */
  YYSYMBOL_optinit = 140,                  /* optinit  */
  YYSYMBOL_opttype = 141,                  /* opttype  */
  YYSYMBOL_type = 142,                     /* type  */
  YYSYMBOL_type3 = 143,                    /* type3  */
  YYSYMBOL_type2 = 144,                    /* type2  */
  YYSYMBOL_type1 = 145,                    /* type1  */
  YYSYMBOL_recordfieldlist = 146,          /* recordfieldlist  */
  YYSYMBOL_recordfield = 147,              /* recordfield  */
  YYSYMBOL_recordfield0 = 148,             /* recordfield0  */
  YYSYMBOL_padding = 149,                  /* padding  */
  YYSYMBOL_optfieldid = 150,               /* optfieldid  */
  YYSYMBOL_caseindex = 151,                /* caseindex  */
  YYSYMBOL_casefieldlist = 152,            /* casefieldlist  */
  YYSYMBOL_casefield = 153,                /* casefield  */
  YYSYMBOL_casefield0 = 154,               /* casefield0  */
  YYSYMBOL_optexprlist = 155,              /* optexprlist  */
  YYSYMBOL_exprlist = 156,                 /* exprlist  */
  YYSYMBOL_expr = 157,                     /* expr  */
  YYSYMBOL_cstr = 158,                     /* cstr  */
  YYSYMBOL_regex = 159,                    /* regex  */
  YYSYMBOL_caseexprlist = 160,             /* caseexprlist  */
  YYSYMBOL_caseexpr = 161,                 /* caseexpr  */
  YYSYMBOL_enumlist = 162,                 /* enumlist  */
  YYSYMBOL_enumlist1 = 163,                /* enumlist1  */
  YYSYMBOL_enumitem = 164,                 /* enumitem  */
  YYSYMBOL_conn = 165,                     /* conn  */
  YYSYMBOL_flow = 166,                     /* flow  */
  YYSYMBOL_sahlist = 167,                  /* sahlist  */
  YYSYMBOL_sah = 168,                      /* sah  */
  YYSYMBOL_statevarlist = 169,             /* statevarlist  */
  YYSYMBOL_statevar = 170,                 /* statevar  */
  YYSYMBOL_actionparam = 171,              /* actionparam  */
  YYSYMBOL_actionparamtype = 172,          /* actionparamtype  */
  YYSYMBOL_embedded_code = 173,            /* embedded_code  */
  YYSYMBOL_embedded_pac_primitive = 174,   /* embedded_pac_primitive  */
  YYSYMBOL_optargs = 175,                  /* optargs  */
  YYSYMBOL_letfieldlist = 176,             /* letfieldlist  */
  YYSYMBOL_letfield = 177,                 /* letfield  */
  YYSYMBOL_withinputfield = 178,           /* withinputfield  */
  YYSYMBOL_input = 179,                    /* input  */
  YYSYMBOL_optattrs = 180,                 /* optattrs  */
  YYSYMBOL_attrlist = 181,                 /* attrlist  */
  YYSYMBOL_optcomma = 182,                 /* optcomma  */
  YYSYMBOL_attr = 183,                     /* attr  */
  YYSYMBOL_optlinebreaker = 184            /* optlinebreaker  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  117
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  193
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  428

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   347


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
       2,     2,     2,   107,     2,     2,     2,   105,    96,     2,
     110,   111,   103,   101,    85,   102,   114,   104,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    87,    84,
      94,    82,    95,    86,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   112,     2,   113,    98,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   115,    97,   116,   106,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    83,    88,    89,
      90,    91,    92,    93,    99,   100,   108,   109
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   180,   180,   183,   188,   193,   199,   199,   204,   204,
     208,   213,   213,   217,   217,   222,   222,   226,   226,   230,
     230,   234,   234,   238,   242,   246,   250,   254,   260,   264,
     268,   272,   278,   279,   282,   286,   290,   294,   298,   302,
     308,   314,   320,   325,   331,   337,   342,   347,   353,   358,
     363,   368,   374,   379,   386,   389,   396,   399,   405,   412,
     416,   423,   427,   431,   435,   442,   446,   450,   454,   460,
     466,   471,   478,   482,   488,   493,   498,   505,   509,   515,
     521,   527,   532,   539,   543,   550,   553,   559,   564,   571,
     575,   579,   583,   587,   591,   595,   599,   605,   609,   613,
     617,   621,   625,   629,   633,   637,   641,   645,   649,   653,
     657,   661,   665,   669,   673,   677,   681,   685,   689,   693,
     697,   701,   707,   713,   720,   723,   730,   734,   740,   744,
     750,   755,   762,   766,   772,   778,   786,   789,   796,   800,
     804,   808,   812,   816,   824,   828,   832,   839,   842,   849,
     855,   861,   865,   872,   875,   880,   885,   892,   896,   900,
     904,   911,   914,   920,   925,   931,   936,   943,   951,   958,
     961,   967,   973,   981,   982,   985,   989,   993,   997,  1001,
    1005,  1009,  1013,  1017,  1021,  1025,  1029,  1033,  1037,  1041,
    1045,  1049,  1056,  1059
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_TYPE",
  "TOK_RECORD", "TOK_CASE", "TOK_ENUM", "TOK_LET", "TOK_FUNCTION",
  "TOK_REFINE", "TOK_CASEFUNC", "TOK_CASETYPE", "TOK_TYPEATTR",
  "TOK_HELPERHEADER", "TOK_HELPERCODE", "TOK_RIGHTARROW", "TOK_DEFAULT",
  "TOK_OF", "TOK_PADDING", "TOK_TO", "TOK_ALIGN", "TOK_WITHINPUT",
  "TOK_INT8", "TOK_INT16", "TOK_INT32", "TOK_INT64", "TOK_UINT8",
  "TOK_UINT16", "TOK_UINT32", "TOK_UINT64", "TOK_ID", "TOK_NUMBER",
  "TOK_REGEX", "TOK_STRING", "TOK_BEGIN_RE", "TOK_END_RE", "TOK_ATTR_ALSO",
  "TOK_ATTR_BYTEORDER", "TOK_ATTR_CHECK", "TOK_ATTR_CHUNKED",
  "TOK_ATTR_ENFORCE", "TOK_ATTR_EXPORTSOURCEDATA", "TOK_ATTR_IF",
  "TOK_ATTR_LENGTH", "TOK_ATTR_LET", "TOK_ATTR_LINEBREAKER",
  "TOK_ATTR_MULTILINE", "TOK_ATTR_ONELINE", "TOK_ATTR_REFCOUNT",
  "TOK_ATTR_REQUIRES", "TOK_ATTR_RESTOFDATA", "TOK_ATTR_RESTOFFLOW",
  "TOK_ATTR_TRANSIENT", "TOK_ATTR_UNTIL", "TOK_ANALYZER", "TOK_CONNECTION",
  "TOK_FLOW", "TOK_STATE", "TOK_ACTION", "TOK_WHEN", "TOK_HELPER",
  "TOK_DATAUNIT", "TOK_FLOWDIR", "TOK_WITHCONTEXT", "TOK_LPB_EXTERN",
  "TOK_LPB_HEADER", "TOK_LPB_CODE", "TOK_LPB_MEMBER", "TOK_LPB_INIT",
  "TOK_LPB_CLEANUP", "TOK_LPB_EOF", "TOK_LPB", "TOK_RPB",
  "TOK_EMBEDDED_ATOM", "TOK_EMBEDDED_STRING", "TOK_PAC_VAL", "TOK_PAC_SET",
  "TOK_PAC_TYPE", "TOK_PAC_TYPEOF", "TOK_PAC_CONST_DEF", "TOK_END_PAC",
  "TOK_EXTERN", "'='", "TOK_PLUSEQ", "';'", "','", "'?'", "':'", "TOK_OR",
  "TOK_AND", "TOK_EQUAL", "TOK_NEQ", "TOK_LE", "TOK_GE", "'<'", "'>'",
  "'&'", "'|'", "'^'", "TOK_LSHIFT", "TOK_RSHIFT", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'~'", "'!'", "TOK_SIZEOF", "TOK_OFFSETOF", "'('", "')'",
  "'['", "']'", "'.'", "'{'", "'}'", "$accept", "decls", "decl",
  "decl_with_attr", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8",
  "decl_without_attr", "optsemicolon", "tok_id", "analyzercontext",
  "contextfieldlist", "contextfield", "funcproto", "function", "optparams",
  "paramlist", "param", "optinit", "opttype", "type", "type3", "type2",
  "type1", "recordfieldlist", "recordfield", "recordfield0", "padding",
  "optfieldid", "caseindex", "casefieldlist", "casefield", "casefield0",
  "optexprlist", "exprlist", "expr", "cstr", "regex", "caseexprlist",
  "caseexpr", "enumlist", "enumlist1", "enumitem", "conn", "flow",
  "sahlist", "sah", "statevarlist", "statevar", "actionparam",
  "actionparamtype", "embedded_code", "embedded_pac_primitive", "optargs",
  "letfieldlist", "letfield", "withinputfield", "input", "optattrs",
  "attrlist", "optcomma", "attr", "optlinebreaker", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-284)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-171)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -284,   663,  -284,   207,   207,   207,   207,   134,   207,   207,
     207,  -284,  -284,  -284,    12,   -65,  1174,  -284,  -284,  -284,
    -284,  -284,  -284,  -284,  -284,  -284,  -284,   -88,   102,  -284,
     207,   207,   207,   207,   207,   207,   -28,  -284,  -284,   248,
     607,   664,   207,  -284,  -284,   -44,   531,  -284,   531,  -284,
     531,   -32,   -62,   -27,   -51,   -47,  -284,   -46,  -284,  -284,
    -284,   531,  -284,   570,  -284,   -42,   -43,   -14,   207,  -284,
     531,  -284,    -6,    -5,     5,     8,    18,    28,    13,   -42,
     -42,   -42,  -284,  -284,  -284,   531,   531,   531,   207,  -284,
    -284,  -284,  -284,   531,   531,  -284,  -284,    48,   531,   531,
     531,   -26,   -12,   531,  -284,   993,  -284,  -284,   993,   993,
     531,  -284,   531,   531,   531,  -284,   531,   993,  -284,  1174,
     207,    33,   207,   717,    36,    34,   -68,  -284,   680,   993,
      11,    17,  1174,    26,    27,    32,    54,    56,    64,    76,
     688,   715,   742,    51,  -284,   993,   502,    92,   421,   -56,
     -56,   207,   207,   796,   531,   531,   531,   531,   531,   531,
     531,   531,   531,   531,   531,   531,   531,   531,   531,   531,
     531,   531,   531,   531,   531,   207,   993,    15,   993,   823,
     850,    81,   109,   993,  -284,   -60,   644,   113,    14,   114,
    -284,   531,    93,  -284,    99,  -284,  -284,   531,  -284,   717,
     207,   125,  -284,  -284,  -284,   650,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,  -284,  -284,  -284,  -284,   531,   105,  -284,
     106,   108,  -284,   879,  1046,  1071,  1096,  1096,  1096,  1096,
    1096,  1096,   518,   518,   518,   104,   104,   421,   421,   -56,
     -56,   -56,   112,   906,  -284,  -284,   138,   145,   148,  -284,
    -284,  -284,   531,  -284,   121,  -284,  -284,  -284,   531,  -284,
     207,   221,   993,   531,   450,   993,  -284,  -284,   717,   323,
     357,   173,   225,   453,    84,   123,    67,   128,   130,    67,
     769,  -284,  -284,  -284,   531,  -284,  -284,   717,    36,  -284,
    -284,   993,  -284,   993,  -284,   140,   -59,  -284,   935,  -284,
     234,  -284,     1,   175,   241,  -284,   180,  1174,    19,   207,
     151,   207,   186,   187,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,   190,   189,  -284,  -284,  -284,  -284,   393,
    1020,     0,  1174,     6,  -284,  -284,  -284,   531,   531,  -284,
     207,  -284,  -284,   207,  -284,  -284,   215,   207,   207,   690,
    1156,  1164,  1172,   242,  -284,  -284,   531,  -284,  -284,  -284,
     192,   201,  1174,  -284,   657,   438,   993,   993,   203,   204,
     172,   193,   197,   197,  -284,  -284,  -284,  -284,  -284,   993,
    1174,  -284,  -284,  -284,    -7,  -284,  -284,   717,   717,  -284,
     212,   216,   207,   531,   246,   226,  -284,   531,   531,   531,
    -284,  -284,   242,  -284,   219,   206,   218,   208,  -284,   993,
     993,   964,  -284,   207,   261,  -284,   531,  -284,   222,  -284,
    -284,   224,   207,  1180,   254,  -284,  -284,  -284
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,   153,   153,   153,     0,    32,   169,     5,    39,    38,
      34,    36,    35,    37,     6,    11,     8,     0,     0,    10,
       0,     0,     0,     0,     0,     0,    17,    19,    21,     0,
       0,     0,     0,    33,     3,     0,     0,   177,     0,   179,
       0,     0,     0,     0,     0,   192,   186,     0,   188,   189,
     190,     0,     4,   173,   172,    49,     0,    56,    52,   153,
       0,    47,     0,     0,     0,     0,     0,     0,     0,    49,
      49,    49,    30,   154,   155,     0,     0,     0,     0,   156,
      28,    29,    13,     0,     0,    90,   122,     0,     0,     0,
       0,     0,     0,     0,    89,   176,   120,   121,   178,   180,
       0,   165,     0,     0,     0,   185,    85,   191,   174,     0,
      52,     0,     0,     0,    54,     0,     0,    51,     0,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,   175,     0,     0,    97,   103,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,     0,     0,   181,     0,   183,     0,
       0,     0,    86,    88,   171,     0,     0,   132,     0,   128,
     131,     0,    65,    57,    61,    68,    67,     0,     9,     0,
       0,     0,    46,   124,    81,   173,   136,   136,   136,    42,
      16,   136,   136,   136,   157,   158,   159,     0,     0,   123,
       0,     0,    95,     0,   117,   116,   109,   110,   112,   111,
     114,   113,   104,   105,   106,   107,   108,    98,    99,   100,
     101,   102,     0,     0,    92,   182,    56,     0,     0,   184,
     193,   187,     0,    48,     0,     7,    58,    59,     0,    12,
     129,     0,    79,     0,     0,    55,    53,    50,     0,     0,
       0,     0,     0,     0,     0,     0,   134,     0,     0,   135,
       0,   124,    93,    94,     0,    96,    91,     0,    54,   163,
     164,    87,    70,   133,   130,     0,     0,    63,     0,    44,
       0,    24,     0,     0,     0,    23,     0,   169,     0,     0,
       0,     0,     0,     0,   153,   153,   153,   153,    25,   137,
      26,    27,    40,     0,     0,    18,    20,    22,   160,     0,
     118,    61,   169,     0,    81,    66,    62,     0,     0,   125,
       0,    80,    82,     0,   144,   147,     0,     0,     0,     0,
       0,     0,     0,     0,    41,   119,     0,   166,    78,    60,
       0,     0,   169,    73,     0,     0,   127,   126,     0,     0,
       0,     0,   161,   161,   138,   139,   140,   141,    43,   168,
     169,    77,    69,    71,     0,    72,    64,     0,     0,   145,
       0,     0,     0,    85,     0,     0,   167,     0,     0,     0,
      84,    83,     0,   148,     0,     0,     0,     0,   142,    75,
      76,     0,   149,     0,     0,   162,    85,    74,   151,   150,
     153,     0,     0,     0,     0,   152,   146,   143
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,  -284,
    -284,  -284,  -284,  -284,    -3,  -284,  -284,  -284,  -284,    37,
      97,   223,   142,    59,   103,  -284,  -284,  -166,  -279,  -284,
    -284,  -284,  -284,  -284,  -284,    21,  -284,  -284,  -169,  -222,
      -4,   -86,   -83,    70,  -284,  -284,  -284,    88,   146,  -284,
      45,  -284,  -284,  -284,  -284,  -284,    -2,  -284,   -10,  -284,
    -284,  -284,  -284,  -283,   227,  -284,   245,  -284
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    15,    16,    65,    67,    66,   144,    78,    79,
      80,    81,    17,    44,   104,   210,   274,   324,    28,    29,
     121,   126,   127,   198,   124,   255,   256,   193,   194,   333,
     361,   362,   363,   364,   261,   270,   306,   307,   181,   182,
     183,   106,   107,   269,   303,   188,   189,   190,   275,   278,
     276,   319,   370,   391,   405,   419,    39,    89,   394,   177,
     247,   248,   380,    62,    63,   119,    64,   115
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,    25,    26,    27,   242,    36,    37,    38,   331,    18,
      40,    41,   397,   398,    19,    42,   338,   200,    18,    43,
     257,   356,    68,    19,   342,   200,   252,    72,    73,    74,
      75,    76,    77,   266,   343,   -15,    20,   195,    93,    92,
     196,   296,   105,   201,   108,    20,   109,   302,   308,   357,
     110,   253,   335,   111,   173,   112,   174,   117,   175,   113,
      21,    22,    23,   114,   116,   125,   129,   128,   120,    21,
      22,    23,   122,   123,   378,   309,   136,   130,   131,   383,
     147,   140,   141,   142,   151,   143,   252,    18,   132,   145,
     146,   133,    19,   358,   148,   149,   150,   396,   152,   153,
     195,   134,   299,   196,   252,   399,   176,   302,   178,   179,
     180,   135,   264,   195,    20,   186,   196,   125,   197,   187,
     192,   199,   359,   412,   310,   311,   203,   219,   312,   313,
     259,   245,   204,   217,   314,   315,   316,   317,    21,    22,
      23,   206,   207,   308,    30,    31,    32,   208,   220,   221,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   209,
     243,   211,   244,    69,   246,    18,   137,   138,   139,   212,
      19,   309,   195,   192,    70,   196,    71,   262,    33,    34,
      35,   213,   251,   265,   252,   258,   192,   125,   385,   260,
     322,   195,    20,   263,   196,   168,   169,   170,   171,   172,
      18,   264,   268,   280,   173,    19,   174,   282,   175,   283,
     281,   400,   401,   285,   406,   287,    21,    22,    23,   289,
     310,   311,   290,   309,   312,   313,   292,    20,   295,   325,
     314,   315,   316,   317,   326,    18,   327,   421,   291,   337,
      19,   271,   272,   273,   293,   334,   340,   187,   279,   339,
     298,    21,    22,    23,   341,   192,   345,   195,   347,   348,
     196,   323,    20,   354,   371,    96,    97,   353,   195,   381,
     330,   196,   310,   311,   192,   382,   312,   313,   389,   318,
     387,   388,   314,   315,   316,   317,    21,    22,    23,   402,
     403,   195,   195,   392,   196,   196,    27,   393,   346,   407,
     408,   413,   349,   350,   351,   352,   195,   414,   416,   196,
      82,    83,    84,    85,    86,    87,    18,    88,    94,   415,
     360,    19,   420,   366,   367,   424,   422,   368,   427,   300,
     369,   320,   267,   185,   372,   373,   344,   332,   294,   288,
     192,   329,   379,    20,    95,   365,    96,    97,   277,   205,
      18,   192,    94,   395,   184,    19,     0,   390,     0,     0,
       0,     0,     0,   304,     0,     0,     0,    21,    22,    23,
       0,     0,     0,     0,   192,   192,     0,    20,    95,   404,
      96,    97,     0,   409,   410,   411,    18,     0,    94,   192,
       0,    19,     0,     0,     0,     0,     0,     0,     0,   300,
     418,    21,    22,    23,     0,     0,     0,     0,   423,   425,
       0,     0,     0,    20,    95,    98,    96,    97,     0,    99,
     100,   101,   102,   103,     0,     0,     0,     0,     0,   301,
       0,    18,     0,    94,     0,     0,    19,    21,    22,    23,
       0,     0,     0,    18,   304,    94,     0,     0,    19,    98,
       0,   309,     0,    99,   100,   101,   102,   103,    20,    95,
       0,    96,    97,   305,     0,     0,     0,     0,     0,     0,
      20,    95,     0,    96,    97,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    23,    98,     0,     0,     0,    99,
     100,   101,   102,   103,    21,    22,    23,     0,     0,   355,
     310,   311,     0,     0,   312,   313,     0,     0,     0,   218,
     314,   315,   316,   317,   170,   171,   172,     0,     0,     0,
       0,   173,     0,   174,    18,   175,    94,     0,     0,    19,
      98,     0,     0,     0,    99,   100,   101,   102,   103,     0,
       0,     0,    98,     0,   386,     0,    99,   100,   101,   102,
     103,    20,    95,   297,    96,    97,     0,     0,     0,   321,
    -170,     0,     0,  -170,     0,     0,  -170,  -170,  -170,  -170,
       0,     0,     0,     0,     0,    21,    22,    23,   154,     0,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     0,
       0,     0,   173,     0,   174,     0,   175,   166,   167,   168,
     169,   170,   171,   172,  -170,  -170,  -170,     0,   173,     0,
     174,     0,   175,    98,  -170,  -170,  -170,    99,   100,   101,
     102,   103,     0,     0,     0,     0,     0,    18,   254,   191,
     -31,  -170,    19,   -31,  -170,   118,   -31,   -31,   -31,   -31,
      18,     0,   191,     2,     0,    19,     3,     0,     0,     4,
       5,     6,     7,     0,    20,   384,     0,    96,    97,    90,
      83,    84,    85,    86,    87,     0,    88,    20,     0,     0,
      96,    97,     0,     0,     0,     0,     0,     0,    21,    22,
      23,     0,     0,     0,   -31,   -31,   -31,     0,     0,     0,
       0,    21,    22,    23,   -31,   -31,   -31,     8,     9,    10,
      18,     0,   191,     0,     0,    19,     0,    11,    12,    13,
       0,   -31,     0,     0,   -31,   118,    91,    83,    84,    85,
      86,    87,     0,    88,    14,     0,     0,    20,     0,     0,
      96,    97,   202,    83,    84,    85,    86,    87,     0,    88,
       0,     0,   374,    83,    84,    85,    86,    87,   214,    88,
       0,    21,    22,    23,   154,     0,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,   215,     0,     0,   173,     0,
     174,   154,   175,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,   216,     0,     0,   173,     0,   174,   154,   175,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,   328,
       0,     0,   173,     0,   174,   154,   175,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,   173,
       0,   174,   154,   175,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,     0,     0,   173,   222,   174,   154,
     175,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,   249,   174,   154,   175,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,     0,     0,
     173,   250,   174,     0,   175,   154,   284,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,   173,
       0,   174,   154,   175,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,     0,     0,   173,     0,   174,   286,
     175,   154,     0,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,   173,     0,   174,   336,   175,
     154,     0,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,     0,     0,   173,     0,   174,   417,   175,   154,
       0,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,   173,     0,   174,     0,   175,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     0,     0,     0,     0,
     173,     0,   174,     0,   175,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,     0,     0,   173,     0,   174,     0,
     175,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,   173,     0,   174,     0,   175,  -171,  -171,  -171,  -171,
    -171,  -171,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     0,     0,     0,     0,   173,     0,   174,     0,
     175,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,   375,    83,
      84,    85,    86,    87,     0,    88,   376,    83,    84,    85,
      86,    87,     0,    88,   377,    83,    84,    85,    86,    87,
       0,    88,   426,    83,    84,    85,    86,    87,     0,    88
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,     6,   173,     8,     9,    10,   287,     3,
      12,    13,    19,    20,     8,     3,    15,    85,     3,    84,
     186,    21,   110,     8,   307,    85,    85,    30,    31,    32,
      33,    34,    35,   199,    15,    63,    30,   123,    82,    42,
     123,   263,    46,   111,    48,    30,    50,   269,   270,   332,
      82,   111,   111,   115,   110,    82,   112,    61,   114,   110,
      54,    55,    56,   110,   110,    68,    70,    69,   110,    54,
      55,    56,   115,    87,   353,     8,    63,    83,    83,   362,
      32,    85,    86,    87,   110,    88,    85,     3,    83,    93,
      94,    83,     8,    87,    98,    99,   100,   380,   110,   103,
     186,    83,   268,   186,    85,   112,   110,   329,   112,   113,
     114,    83,   112,   199,    30,    82,   199,   120,    82,   122,
     123,    87,   116,   402,    57,    58,   115,    35,    61,    62,
     116,   116,   115,    82,    67,    68,    69,    70,    54,    55,
      56,   115,   115,   365,    10,    11,    12,   115,   151,   152,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   115,
     174,   115,   175,    71,   177,     3,    79,    80,    81,   115,
       8,     8,   268,   186,    82,   268,    84,   191,    54,    55,
      56,   115,   111,   197,    85,    82,   199,   200,   364,    85,
     116,   287,    30,   110,   287,   101,   102,   103,   104,   105,
       3,   112,    87,   217,   110,     8,   112,   111,   114,   111,
     115,   387,   388,   111,   393,    87,    54,    55,    56,    84,
      57,    58,    84,     8,    61,    62,   115,    30,    17,   116,
      67,    68,    69,    70,   116,     3,   116,   416,   252,    15,
       8,   206,   207,   208,   258,   115,    15,   260,   213,    84,
     264,    54,    55,    56,    84,   268,   115,   353,    82,    82,
     353,   274,    30,    84,    59,    33,    34,    87,   364,    87,
     284,   364,    57,    58,   287,    84,    61,    62,   116,   116,
      87,    87,    67,    68,    69,    70,    54,    55,    56,    87,
      84,   387,   388,   110,   387,   388,   309,   110,   311,    63,
      84,    92,   314,   315,   316,   317,   402,   111,   110,   402,
      72,    73,    74,    75,    76,    77,     3,    79,     5,   111,
     333,     8,    71,   337,   338,   111,   114,   340,    84,    16,
     343,   116,   200,   120,   347,   348,   309,   288,   260,   246,
     353,   281,   356,    30,    31,   334,    33,    34,   212,   132,
       3,   364,     5,   373,   119,     8,    -1,   370,    -1,    -1,
      -1,    -1,    -1,    16,    -1,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,   387,   388,    -1,    30,    31,   392,
      33,    34,    -1,   397,   398,   399,     3,    -1,     5,   402,
      -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
     413,    54,    55,    56,    -1,    -1,    -1,    -1,   420,   422,
      -1,    -1,    -1,    30,    31,   102,    33,    34,    -1,   106,
     107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,   116,
      -1,     3,    -1,     5,    -1,    -1,     8,    54,    55,    56,
      -1,    -1,    -1,     3,    16,     5,    -1,    -1,     8,   102,
      -1,     8,    -1,   106,   107,   108,   109,   110,    30,    31,
      -1,    33,    34,   116,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,   102,    -1,    -1,    -1,   106,
     107,   108,   109,   110,    54,    55,    56,    -1,    -1,   116,
      57,    58,    -1,    -1,    61,    62,    -1,    -1,    -1,    17,
      67,    68,    69,    70,   103,   104,   105,    -1,    -1,    -1,
      -1,   110,    -1,   112,     3,   114,     5,    -1,    -1,     8,
     102,    -1,    -1,    -1,   106,   107,   108,   109,   110,    -1,
      -1,    -1,   102,    -1,   116,    -1,   106,   107,   108,   109,
     110,    30,    31,   113,    33,    34,    -1,    -1,    -1,   116,
       0,    -1,    -1,     3,    -1,    -1,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    86,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    -1,    -1,
      -1,    -1,   110,    -1,   112,    -1,   114,    99,   100,   101,
     102,   103,   104,   105,    54,    55,    56,    -1,   110,    -1,
     112,    -1,   114,   102,    64,    65,    66,   106,   107,   108,
     109,   110,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       0,    81,     8,     3,    84,    85,     6,     7,     8,     9,
       3,    -1,     5,     0,    -1,     8,     3,    -1,    -1,     6,
       7,     8,     9,    -1,    30,    18,    -1,    33,    34,    72,
      73,    74,    75,    76,    77,    -1,    79,    30,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    54,    55,    56,    64,    65,    66,    54,    55,    56,
       3,    -1,     5,    -1,    -1,     8,    -1,    64,    65,    66,
      -1,    81,    -1,    -1,    84,    85,    72,    73,    74,    75,
      76,    77,    -1,    79,    81,    -1,    -1,    30,    -1,    -1,
      33,    34,    72,    73,    74,    75,    76,    77,    -1,    79,
      -1,    -1,    72,    73,    74,    75,    76,    77,    80,    79,
      -1,    54,    55,    56,    86,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,    -1,    80,    -1,    -1,   110,    -1,
     112,    86,   114,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    80,    -1,    -1,   110,    -1,   112,    86,   114,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,    -1,    80,
      -1,    -1,   110,    -1,   112,    86,   114,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,   110,
      -1,   112,    86,   114,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,   110,   111,   112,    86,
     114,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,   110,   111,   112,    86,   114,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
     110,   111,   112,    -1,   114,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,   110,
      -1,   112,    86,   114,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,   110,    -1,   112,   113,
     114,    86,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,   110,    -1,   112,   113,   114,
      86,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,   110,    -1,   112,   113,   114,    86,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,   110,    -1,   112,    -1,   114,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
     110,    -1,   112,    -1,   114,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,   110,    -1,   112,    -1,
     114,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,   110,    -1,   112,    -1,   114,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,    -1,    -1,    -1,    -1,   110,    -1,   112,    -1,
     114,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    72,    73,
      74,    75,    76,    77,    -1,    79,    72,    73,    74,    75,
      76,    77,    -1,    79,    72,    73,    74,    75,    76,    77,
      -1,    79,    72,    73,    74,    75,    76,    77,    -1,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   118,     0,     3,     6,     7,     8,     9,    54,    55,
      56,    64,    65,    66,    81,   119,   120,   129,     3,     8,
      30,    54,    55,    56,   131,   131,   131,   131,   135,   136,
      10,    11,    12,    54,    55,    56,   131,   131,   131,   173,
     173,   173,     3,    84,   130,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   180,   181,   183,   121,   123,   122,   110,    71,
      82,    84,   131,   131,   131,   131,   131,   131,   125,   126,
     127,   128,    72,    73,    74,    75,    76,    77,    79,   174,
      72,    72,   131,    82,     5,    31,    33,    34,   102,   106,
     107,   108,   109,   110,   131,   157,   158,   159,   157,   157,
      82,   115,    82,   110,   110,   184,   110,   157,    85,   182,
     110,   137,   115,    87,   141,   131,   138,   139,   173,   157,
      83,    83,    83,    83,    83,    83,    63,   137,   137,   137,
     157,   157,   157,   131,   124,   157,   157,    32,   157,   157,
     157,   110,   110,   157,    86,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   110,   112,   114,   157,   176,   157,   157,
     157,   155,   156,   157,   183,   138,    82,   131,   162,   163,
     164,     5,   131,   144,   145,   158,   159,    82,   140,    87,
      85,   111,    72,   115,   115,   181,   115,   115,   115,   115,
     132,   115,   115,   115,    80,    80,    80,    82,    17,    35,
     131,   131,   111,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   155,   157,   131,   116,   131,   177,   178,   111,
     111,   111,    85,   111,     4,   142,   143,   144,    82,   116,
      85,   151,   157,   110,   112,   157,   144,   139,    87,   160,
     152,   167,   167,   167,   133,   165,   167,   165,   166,   167,
     157,   115,   111,   111,    87,   111,   113,    87,   141,    84,
      84,   157,   115,   157,   164,    17,   156,   113,   157,   144,
      16,   116,   156,   161,    16,   116,   153,   154,   156,     8,
      57,    58,    61,    62,    67,    68,    69,    70,   116,   168,
     116,   116,   116,   131,   134,   116,   116,   116,    80,   160,
     157,   145,   140,   146,   115,   111,   113,    15,    15,    84,
      15,    84,   180,    15,   136,   115,   131,    82,    82,   173,
     173,   173,   173,    87,    84,   116,    21,   180,    87,   116,
     131,   147,   148,   149,   150,   152,   157,   157,   131,   131,
     169,    59,   131,   131,    72,    72,    72,    72,   145,   157,
     179,    87,    84,   180,    18,   144,   116,    87,    87,   116,
     131,   170,   110,   110,   175,   175,   180,    19,    20,   112,
     144,   144,    87,    84,   131,   171,   155,    63,    84,   157,
     157,   157,   145,    92,   111,   111,   110,   113,   131,   172,
      71,   155,   114,   173,   111,   131,    72,    84
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   117,   118,   118,   119,   119,   121,   120,   122,   120,
     120,   123,   120,   124,   120,   125,   120,   126,   120,   127,
     120,   128,   120,   120,   120,   120,   120,   120,   129,   129,
     129,   129,   130,   130,   131,   131,   131,   131,   131,   131,
     132,   133,   133,   134,   135,   136,   136,   136,   137,   137,
     138,   138,   138,   139,   140,   140,   141,   141,   142,   143,
     143,   144,   144,   144,   144,   145,   145,   145,   145,   146,
     146,   147,   148,   148,   149,   149,   149,   150,   150,   151,
     152,   152,   153,   154,   154,   155,   155,   156,   156,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   158,   159,   160,   160,   161,   161,   162,   162,
     163,   163,   164,   164,   165,   166,   167,   167,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   169,   169,   170,
     171,   172,   172,   173,   173,   173,   173,   174,   174,   174,
     174,   175,   175,   176,   176,   176,   177,   178,   179,   180,
     180,   181,   181,   182,   182,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   184,   184
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     2,     1,     0,     6,     0,     5,
       2,     0,     6,     0,     4,     0,     5,     0,     7,     0,
       7,     0,     7,     7,     7,     7,     7,     7,     3,     3,
       3,     5,     0,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     0,     3,     6,     3,     4,     2,     3,     0,
       3,     1,     0,     3,     0,     2,     0,     2,     1,     1,
       4,     1,     4,     3,     6,     1,     4,     1,     1,     3,
       0,     2,     2,     1,     5,     4,     4,     2,     1,     1,
       3,     0,     2,     5,     5,     0,     1,     3,     1,     1,
       1,     4,     3,     4,     4,     3,     4,     2,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     5,     6,
       1,     1,     1,     3,     0,     3,     3,     3,     1,     2,
       3,     1,     1,     3,     1,     1,     0,     2,     3,     3,
       3,     3,     5,     9,     2,     4,     9,     0,     3,     3,
       3,     1,     3,     0,     2,     2,     2,     3,     3,     3,
       5,     0,     3,     3,     3,     0,     4,     6,     1,     0,
       1,     3,     1,     0,     1,     3,     2,     1,     2,     1,
       2,     3,     4,     3,     4,     2,     1,     4,     1,     1,
       1,     2,     0,     3
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
  YY_USE (yykind);
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
  case 2: /* decls: %empty  */
#line 180 "pac_parse.yy"
                                {
				// Put initialization here
				}
#line 1772 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 3: /* decls: decls decl optsemicolon  */
#line 184 "pac_parse.yy"
                                {
				}
#line 1779 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 4: /* decl: decl_with_attr optattrs  */
#line 189 "pac_parse.yy"
                                {
				(yyval.decl) = (yyvsp[-1].decl);
				(yyvsp[-1].decl)->AddAttrs((yyvsp[0].attrlist));
				}
#line 1788 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 5: /* decl: decl_without_attr  */
#line 194 "pac_parse.yy"
                                {
				(yyval.decl) = (yyvsp[0].decl);
				}
#line 1796 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 6: /* $@1: %empty  */
#line 199 "pac_parse.yy"
                                        { current_decl_id = (yyvsp[0].id); }
#line 1802 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 7: /* decl_with_attr: TOK_TYPE tok_id $@1 optparams '=' type  */
#line 200 "pac_parse.yy"
                                {
				TypeDecl* decl = new TypeDecl((yyvsp[-4].id), (yyvsp[-2].paramlist), (yyvsp[0].type));
				(yyval.decl) = decl;
				}
#line 1811 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 8: /* $@2: %empty  */
#line 204 "pac_parse.yy"
                                       { current_decl_id = (yyvsp[0].id); }
#line 1817 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 9: /* decl_with_attr: TOK_LET tok_id $@2 opttype optinit  */
#line 205 "pac_parse.yy"
                                {
				(yyval.decl) = new LetDecl((yyvsp[-3].id), (yyvsp[-1].type), (yyvsp[0].expr));
				}
#line 1825 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 10: /* decl_with_attr: TOK_FUNCTION function  */
#line 209 "pac_parse.yy"
                                {
				current_decl_id = (yyvsp[0].function)->id();
				(yyval.decl) = new FuncDecl((yyvsp[0].function));
				}
#line 1834 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 11: /* $@3: %empty  */
#line 213 "pac_parse.yy"
                                        { current_decl_id = (yyvsp[0].id); }
#line 1840 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 12: /* decl_with_attr: TOK_ENUM tok_id $@3 '{' enumlist '}'  */
#line 214 "pac_parse.yy"
                                {
				(yyval.decl) = new EnumDecl((yyvsp[-4].id), (yyvsp[-1].enumlist));
				}
#line 1848 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 13: /* $@4: %empty  */
#line 217 "pac_parse.yy"
                                                   { current_decl_id = (yyvsp[0].id); }
#line 1854 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 14: /* decl_with_attr: TOK_EXTERN TOK_TYPE tok_id $@4  */
#line 218 "pac_parse.yy"
                                {
				Type *extern_type = new ExternType((yyvsp[-1].id), ExternType::PLAIN);
				(yyval.decl) = new TypeDecl((yyvsp[-1].id), 0, extern_type);
				}
#line 1863 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 15: /* $@5: %empty  */
#line 222 "pac_parse.yy"
                                            { current_decl_id = (yyvsp[0].id); }
#line 1869 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 16: /* decl_with_attr: TOK_ANALYZER tok_id $@5 TOK_WITHCONTEXT analyzercontext  */
#line 223 "pac_parse.yy"
                                {
				(yyval.decl) = new AnalyzerContextDecl((yyvsp[-3].id), (yyvsp[0].contextfieldlist));
				}
#line 1877 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 17: /* $@6: %empty  */
#line 226 "pac_parse.yy"
                                            { current_decl_id = (yyvsp[0].id); }
#line 1883 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 18: /* decl_with_attr: TOK_ANALYZER tok_id $@6 optparams '{' conn '}'  */
#line 227 "pac_parse.yy"
                                {
				(yyval.decl) = new ConnDecl((yyvsp[-5].id), (yyvsp[-3].paramlist), (yyvsp[-1].aelemlist));
				}
#line 1891 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 19: /* $@7: %empty  */
#line 230 "pac_parse.yy"
                                              { current_decl_id = (yyvsp[0].id); }
#line 1897 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 20: /* decl_with_attr: TOK_CONNECTION tok_id $@7 optparams '{' conn '}'  */
#line 231 "pac_parse.yy"
                                {
				(yyval.decl) = new ConnDecl((yyvsp[-5].id), (yyvsp[-3].paramlist), (yyvsp[-1].aelemlist));
				}
#line 1905 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 21: /* $@8: %empty  */
#line 234 "pac_parse.yy"
                                        { current_decl_id = (yyvsp[0].id); }
#line 1911 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 22: /* decl_with_attr: TOK_FLOW tok_id $@8 optparams '{' flow '}'  */
#line 235 "pac_parse.yy"
                                {
				(yyval.decl) = new FlowDecl((yyvsp[-5].id), (yyvsp[-3].paramlist), (yyvsp[-1].aelemlist));
				}
#line 1919 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 23: /* decl_with_attr: TOK_REFINE TOK_CASETYPE tok_id TOK_PLUSEQ '{' casefieldlist '}'  */
#line 239 "pac_parse.yy"
                                {
				(yyval.decl) = ProcessCaseTypeRedef((yyvsp[-4].id), (yyvsp[-1].casefieldlist));
				}
#line 1927 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 24: /* decl_with_attr: TOK_REFINE TOK_CASEFUNC tok_id TOK_PLUSEQ '{' caseexprlist '}'  */
#line 243 "pac_parse.yy"
                                {
				(yyval.decl) = ProcessCaseExprRedef((yyvsp[-4].id), (yyvsp[-1].caseexprlist));
				}
#line 1935 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 25: /* decl_with_attr: TOK_REFINE TOK_ANALYZER tok_id TOK_PLUSEQ '{' sahlist '}'  */
#line 247 "pac_parse.yy"
                                {
				(yyval.decl) = ProcessAnalyzerRedef((yyvsp[-4].id), Decl::CONN, (yyvsp[-1].aelemlist));
				}
#line 1943 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 26: /* decl_with_attr: TOK_REFINE TOK_CONNECTION tok_id TOK_PLUSEQ '{' sahlist '}'  */
#line 251 "pac_parse.yy"
                                {
				(yyval.decl) = ProcessAnalyzerRedef((yyvsp[-4].id), Decl::CONN, (yyvsp[-1].aelemlist));
				}
#line 1951 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 27: /* decl_with_attr: TOK_REFINE TOK_FLOW tok_id TOK_PLUSEQ '{' sahlist '}'  */
#line 255 "pac_parse.yy"
                                {
				(yyval.decl) = ProcessAnalyzerRedef((yyvsp[-4].id), Decl::FLOW, (yyvsp[-1].aelemlist));
				}
#line 1959 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 28: /* decl_without_attr: TOK_LPB_HEADER embedded_code TOK_RPB  */
#line 261 "pac_parse.yy"
                                {
				(yyval.decl) = new HelperDecl(HelperDecl::HEADER, 0, (yyvsp[-1].embedded_code));
				}
#line 1967 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 29: /* decl_without_attr: TOK_LPB_CODE embedded_code TOK_RPB  */
#line 265 "pac_parse.yy"
                                {
				(yyval.decl) = new HelperDecl(HelperDecl::CODE, 0, (yyvsp[-1].embedded_code));
				}
#line 1975 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 30: /* decl_without_attr: TOK_LPB_EXTERN embedded_code TOK_RPB  */
#line 269 "pac_parse.yy"
                                {
				(yyval.decl) = new HelperDecl(HelperDecl::EXTERN, 0, (yyvsp[-1].embedded_code));
				}
#line 1983 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 31: /* decl_without_attr: TOK_REFINE TOK_TYPEATTR tok_id TOK_PLUSEQ attrlist  */
#line 273 "pac_parse.yy"
                                {
				(yyval.decl) = ProcessTypeAttrRedef((yyvsp[-2].id), (yyvsp[0].attrlist));
				}
#line 1991 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 34: /* tok_id: TOK_ID  */
#line 283 "pac_parse.yy"
                                {
				(yyval.id) = (yyvsp[0].id);
				}
#line 1999 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 35: /* tok_id: TOK_CONNECTION  */
#line 287 "pac_parse.yy"
                                {
				(yyval.id) = new ID("connection");
				}
#line 2007 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 36: /* tok_id: TOK_ANALYZER  */
#line 291 "pac_parse.yy"
                                {
				(yyval.id) = new ID("analyzer");
				}
#line 2015 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 37: /* tok_id: TOK_FLOW  */
#line 295 "pac_parse.yy"
                                {
				(yyval.id) = new ID("flow");
				}
#line 2023 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 38: /* tok_id: TOK_FUNCTION  */
#line 299 "pac_parse.yy"
                                {
				(yyval.id) = new ID("function");
				}
#line 2031 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 39: /* tok_id: TOK_TYPE  */
#line 303 "pac_parse.yy"
                                {
				(yyval.id) = new ID("type");
				}
#line 2039 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 40: /* analyzercontext: '{' contextfieldlist '}'  */
#line 309 "pac_parse.yy"
                                {
				(yyval.contextfieldlist) = (yyvsp[-1].contextfieldlist);
				}
#line 2047 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 41: /* contextfieldlist: contextfieldlist contextfield ';'  */
#line 315 "pac_parse.yy"
                                {
				(yyvsp[-2].contextfieldlist)->push_back((yyvsp[-1].contextfield));
				(yyval.contextfieldlist) = (yyvsp[-2].contextfieldlist);
				}
#line 2056 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 42: /* contextfieldlist: %empty  */
#line 320 "pac_parse.yy"
                                {
				(yyval.contextfieldlist) = new ContextFieldList();
				}
#line 2064 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 43: /* contextfield: tok_id ':' type1  */
#line 326 "pac_parse.yy"
                                {
				(yyval.contextfield) = new ContextField((yyvsp[-2].id), (yyvsp[0].type));
				}
#line 2072 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 44: /* funcproto: tok_id '(' paramlist ')' ':' type2  */
#line 332 "pac_parse.yy"
                                {
				(yyval.function) = new Function((yyvsp[-5].id), (yyvsp[0].type), (yyvsp[-3].paramlist));
				}
#line 2080 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 45: /* function: funcproto '=' expr  */
#line 338 "pac_parse.yy"
                                {
				(yyvsp[-2].function)->set_expr((yyvsp[0].expr));
				(yyval.function) = (yyvsp[-2].function);
				}
#line 2089 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 46: /* function: funcproto TOK_LPB embedded_code TOK_RPB  */
#line 343 "pac_parse.yy"
                                {
				(yyvsp[-3].function)->set_code((yyvsp[-1].embedded_code));
				(yyval.function) = (yyvsp[-3].function);
				}
#line 2098 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 47: /* function: funcproto ';'  */
#line 348 "pac_parse.yy"
                                {
				(yyval.function) = (yyvsp[-1].function);
				}
#line 2106 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 48: /* optparams: '(' paramlist ')'  */
#line 354 "pac_parse.yy"
                                {
				(yyval.paramlist) = (yyvsp[-1].paramlist);
				}
#line 2114 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 49: /* optparams: %empty  */
#line 358 "pac_parse.yy"
                                {
				(yyval.paramlist) = 0;
				}
#line 2122 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 50: /* paramlist: paramlist ',' param  */
#line 364 "pac_parse.yy"
                                {
				(yyvsp[-2].paramlist)->push_back((yyvsp[0].param));
				(yyval.paramlist) = (yyvsp[-2].paramlist);
				}
#line 2131 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 51: /* paramlist: param  */
#line 369 "pac_parse.yy"
                                {
				(yyval.paramlist) = new ParamList();
				(yyval.paramlist)->push_back((yyvsp[0].param));
				}
#line 2140 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 52: /* paramlist: %empty  */
#line 374 "pac_parse.yy"
                                {
				(yyval.paramlist) = new ParamList();
				}
#line 2148 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 53: /* param: tok_id ':' type2  */
#line 380 "pac_parse.yy"
                                {
				(yyval.param) = new Param((yyvsp[-2].id), (yyvsp[0].type));
				}
#line 2156 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 54: /* optinit: %empty  */
#line 386 "pac_parse.yy"
                                {
				(yyval.expr) = 0;
				}
#line 2164 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 55: /* optinit: '=' expr  */
#line 390 "pac_parse.yy"
                                {
				(yyval.expr) = (yyvsp[0].expr);
				}
#line 2172 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 56: /* opttype: %empty  */
#line 396 "pac_parse.yy"
                                {
				(yyval.type) = 0;
				}
#line 2180 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 57: /* opttype: ':' type2  */
#line 400 "pac_parse.yy"
                                {
				(yyval.type) = (yyvsp[0].type);
				}
#line 2188 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 58: /* type: type3  */
#line 406 "pac_parse.yy"
                                {
				(yyval.type) = (yyvsp[0].type);
				}
#line 2196 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 59: /* type3: type2  */
#line 413 "pac_parse.yy"
                                {
				(yyval.type) = (yyvsp[0].type);
				}
#line 2204 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 60: /* type3: TOK_RECORD '{' recordfieldlist '}'  */
#line 417 "pac_parse.yy"
                                {
				(yyval.type) = new RecordType((yyvsp[-1].recordfieldlist));
				}
#line 2212 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 61: /* type2: type1  */
#line 424 "pac_parse.yy"
                                {
				(yyval.type) = (yyvsp[0].type);
				}
#line 2220 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 62: /* type2: type1 '[' expr ']'  */
#line 428 "pac_parse.yy"
                                {
				(yyval.type) = new ArrayType((yyvsp[-3].type), (yyvsp[-1].expr));
				}
#line 2228 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 63: /* type2: type1 '[' ']'  */
#line 432 "pac_parse.yy"
                                {
				(yyval.type) = new ArrayType((yyvsp[-2].type));
				}
#line 2236 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 64: /* type2: TOK_CASE caseindex TOK_OF '{' casefieldlist '}'  */
#line 436 "pac_parse.yy"
                                {
				(yyval.type) = new CaseType((yyvsp[-4].expr), (yyvsp[-1].casefieldlist));
				}
#line 2244 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 65: /* type1: tok_id  */
#line 443 "pac_parse.yy"
                                {
				(yyval.type) = Type::LookUpByID((yyvsp[0].id));
				}
#line 2252 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 66: /* type1: tok_id '(' exprlist ')'  */
#line 447 "pac_parse.yy"
                                {
				(yyval.type) = new ParameterizedType((yyvsp[-3].id), (yyvsp[-1].exprlist));
				}
#line 2260 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 67: /* type1: regex  */
#line 451 "pac_parse.yy"
                                {
				(yyval.type) = new StringType((yyvsp[0].regex));
				}
#line 2268 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 68: /* type1: cstr  */
#line 455 "pac_parse.yy"
                                {
				(yyval.type) = new StringType((yyvsp[0].cstr));
				}
#line 2276 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 69: /* recordfieldlist: recordfieldlist recordfield ';'  */
#line 461 "pac_parse.yy"
                                {
				(yyvsp[-2].recordfieldlist)->push_back((yyvsp[-1].recordfield));
				(yyval.recordfieldlist) = (yyvsp[-2].recordfieldlist);
				}
#line 2285 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 70: /* recordfieldlist: %empty  */
#line 466 "pac_parse.yy"
                                {
				(yyval.recordfieldlist) = new RecordFieldList();
				}
#line 2293 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 71: /* recordfield: recordfield0 optattrs  */
#line 472 "pac_parse.yy"
                                {
				(yyvsp[-1].recordfield)->AddAttr((yyvsp[0].attrlist));
				(yyval.recordfield) = (yyvsp[-1].recordfield);
				}
#line 2302 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 72: /* recordfield0: optfieldid type2  */
#line 479 "pac_parse.yy"
                                {
				(yyval.recordfield) = new RecordDataField((yyvsp[-1].id), (yyvsp[0].type));
				}
#line 2310 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 73: /* recordfield0: padding  */
#line 483 "pac_parse.yy"
                                {
				(yyval.recordfield) = (yyvsp[0].recordfield);
				}
#line 2318 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 74: /* padding: optfieldid TOK_PADDING '[' expr ']'  */
#line 489 "pac_parse.yy"
                                {
				(yyval.recordfield) = new RecordPaddingField(
					(yyvsp[-4].id), PAD_BY_LENGTH, (yyvsp[-1].expr));
				}
#line 2327 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 75: /* padding: optfieldid TOK_PADDING TOK_TO expr  */
#line 494 "pac_parse.yy"
                                {
				(yyval.recordfield) = new RecordPaddingField(
					(yyvsp[-3].id), PAD_TO_OFFSET, (yyvsp[0].expr));
				}
#line 2336 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 76: /* padding: optfieldid TOK_PADDING TOK_ALIGN expr  */
#line 499 "pac_parse.yy"
                                {
				(yyval.recordfield) = new RecordPaddingField(
					(yyvsp[-3].id), PAD_TO_NEXT_WORD, (yyvsp[0].expr));
				}
#line 2345 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 77: /* optfieldid: tok_id ':'  */
#line 506 "pac_parse.yy"
                                {
				(yyval.id) = (yyvsp[-1].id);
				}
#line 2353 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 78: /* optfieldid: ':'  */
#line 510 "pac_parse.yy"
                                {
				(yyval.id) = ID::NewAnonymousID("anonymous_field_");
				}
#line 2361 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 79: /* caseindex: expr  */
#line 516 "pac_parse.yy"
                                {
				(yyval.expr) = (yyvsp[0].expr);
				}
#line 2369 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 80: /* casefieldlist: casefieldlist casefield ';'  */
#line 522 "pac_parse.yy"
                                {
				(yyvsp[-2].casefieldlist)->push_back((yyvsp[-1].casefield));
				(yyval.casefieldlist) = (yyvsp[-2].casefieldlist);
				}
#line 2378 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 81: /* casefieldlist: %empty  */
#line 527 "pac_parse.yy"
                                {
				(yyval.casefieldlist) = new CaseFieldList();
				}
#line 2386 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 82: /* casefield: casefield0 optattrs  */
#line 533 "pac_parse.yy"
                                {
				(yyvsp[-1].casefield)->AddAttr((yyvsp[0].attrlist));
				(yyval.casefield) = (yyvsp[-1].casefield);
				}
#line 2395 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 83: /* casefield0: exprlist TOK_RIGHTARROW tok_id ':' type2  */
#line 540 "pac_parse.yy"
                                {
				(yyval.casefield) = new CaseField((yyvsp[-4].exprlist), (yyvsp[-2].id), (yyvsp[0].type));
				}
#line 2403 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 84: /* casefield0: TOK_DEFAULT TOK_RIGHTARROW tok_id ':' type2  */
#line 544 "pac_parse.yy"
                                {
				(yyval.casefield) = new CaseField(0, (yyvsp[-2].id), (yyvsp[0].type));
				}
#line 2411 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 85: /* optexprlist: %empty  */
#line 550 "pac_parse.yy"
                                {
				(yyval.exprlist) = 0;
				}
#line 2419 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 86: /* optexprlist: exprlist  */
#line 554 "pac_parse.yy"
                                {
				(yyval.exprlist) = (yyvsp[0].exprlist);
				}
#line 2427 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 87: /* exprlist: exprlist ',' expr  */
#line 560 "pac_parse.yy"
                                {
				(yyvsp[-2].exprlist)->push_back((yyvsp[0].expr));
				(yyval.exprlist) = (yyvsp[-2].exprlist);
				}
#line 2436 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 88: /* exprlist: expr  */
#line 565 "pac_parse.yy"
                                {
				(yyval.exprlist) = new ExprList();
				(yyval.exprlist)->push_back((yyvsp[0].expr));
				}
#line 2445 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 89: /* expr: tok_id  */
#line 572 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr((yyvsp[0].id));
				}
#line 2453 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 90: /* expr: TOK_NUMBER  */
#line 576 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr((yyvsp[0].num));
				}
#line 2461 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 91: /* expr: expr '[' expr ']'  */
#line 580 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_SUBSCRIPT, (yyvsp[-3].expr), (yyvsp[-1].expr));
				}
#line 2469 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 92: /* expr: expr '.' tok_id  */
#line 584 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_MEMBER, (yyvsp[-2].expr), new Expr((yyvsp[0].id)));
				}
#line 2477 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 93: /* expr: TOK_SIZEOF '(' tok_id ')'  */
#line 588 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_SIZEOF, new Expr((yyvsp[-1].id)));
				}
#line 2485 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 94: /* expr: TOK_OFFSETOF '(' tok_id ')'  */
#line 592 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_OFFSETOF, new Expr((yyvsp[-1].id)));
				}
#line 2493 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 95: /* expr: '(' expr ')'  */
#line 596 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_PAREN, (yyvsp[-1].expr));
				}
#line 2501 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 96: /* expr: expr '(' optexprlist ')'  */
#line 600 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_CALL,
				              (yyvsp[-3].expr),
				              new Expr((yyvsp[-1].exprlist)));
				}
#line 2511 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 97: /* expr: '-' expr  */
#line 606 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_NEG, (yyvsp[0].expr));
				}
#line 2519 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 98: /* expr: expr '+' expr  */
#line 610 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_PLUS, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2527 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 99: /* expr: expr '-' expr  */
#line 614 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_MINUS, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2535 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 100: /* expr: expr '*' expr  */
#line 618 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_TIMES, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2543 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 101: /* expr: expr '/' expr  */
#line 622 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_DIV, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2551 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 102: /* expr: expr '%' expr  */
#line 626 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_MOD, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2559 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 103: /* expr: '~' expr  */
#line 630 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_BITNOT, (yyvsp[0].expr));
				}
#line 2567 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 104: /* expr: expr '&' expr  */
#line 634 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_BITAND, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2575 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 105: /* expr: expr '|' expr  */
#line 638 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_BITOR, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2583 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 106: /* expr: expr '^' expr  */
#line 642 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_BITXOR, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2591 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 107: /* expr: expr TOK_LSHIFT expr  */
#line 646 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_LSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2599 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 108: /* expr: expr TOK_RSHIFT expr  */
#line 650 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_RSHIFT, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2607 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 109: /* expr: expr TOK_EQUAL expr  */
#line 654 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_EQUAL, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2615 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 110: /* expr: expr TOK_NEQ expr  */
#line 658 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_NEQ, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2623 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 111: /* expr: expr TOK_GE expr  */
#line 662 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_GE, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2631 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 112: /* expr: expr TOK_LE expr  */
#line 666 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_LE, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2639 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 113: /* expr: expr '>' expr  */
#line 670 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_GT, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2647 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 114: /* expr: expr '<' expr  */
#line 674 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_LT, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2655 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 115: /* expr: '!' expr  */
#line 678 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_NOT, (yyvsp[0].expr));
				}
#line 2663 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 116: /* expr: expr TOK_AND expr  */
#line 682 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_AND, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2671 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 117: /* expr: expr TOK_OR expr  */
#line 686 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_OR, (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2679 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 118: /* expr: expr '?' expr ':' expr  */
#line 690 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr(Expr::EXPR_COND, (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
				}
#line 2687 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 119: /* expr: TOK_CASE expr TOK_OF '{' caseexprlist '}'  */
#line 694 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr((yyvsp[-4].expr), (yyvsp[-1].caseexprlist));
				}
#line 2695 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 120: /* expr: cstr  */
#line 698 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr((yyvsp[0].cstr));
				}
#line 2703 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 121: /* expr: regex  */
#line 702 "pac_parse.yy"
                                {
				(yyval.expr) = new Expr((yyvsp[0].regex));
				}
#line 2711 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 122: /* cstr: TOK_STRING  */
#line 708 "pac_parse.yy"
                                {
				(yyval.cstr) = new ConstString((yyvsp[0].str));
				}
#line 2719 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 123: /* regex: TOK_BEGIN_RE TOK_REGEX TOK_END_RE  */
#line 714 "pac_parse.yy"
                                {
				(yyval.regex) = new RegEx((yyvsp[-1].str));
				}
#line 2727 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 124: /* caseexprlist: %empty  */
#line 720 "pac_parse.yy"
                                {
				(yyval.caseexprlist) = new CaseExprList();
				}
#line 2735 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 125: /* caseexprlist: caseexprlist caseexpr ';'  */
#line 724 "pac_parse.yy"
                                {
				(yyvsp[-2].caseexprlist)->push_back((yyvsp[-1].caseexpr));
				(yyval.caseexprlist) = (yyvsp[-2].caseexprlist);
				}
#line 2744 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 126: /* caseexpr: exprlist TOK_RIGHTARROW expr  */
#line 731 "pac_parse.yy"
                                {
				(yyval.caseexpr) = new CaseExpr((yyvsp[-2].exprlist), (yyvsp[0].expr));
				}
#line 2752 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 127: /* caseexpr: TOK_DEFAULT TOK_RIGHTARROW expr  */
#line 735 "pac_parse.yy"
                                {
				(yyval.caseexpr) = new CaseExpr(0, (yyvsp[0].expr));
				}
#line 2760 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 128: /* enumlist: enumlist1  */
#line 741 "pac_parse.yy"
                                {
				(yyval.enumlist) = (yyvsp[0].enumlist);
				}
#line 2768 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 129: /* enumlist: enumlist1 ','  */
#line 745 "pac_parse.yy"
                                {
				(yyval.enumlist) = (yyvsp[-1].enumlist);
				}
#line 2776 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 130: /* enumlist1: enumlist1 ',' enumitem  */
#line 751 "pac_parse.yy"
                                {
				(yyvsp[-2].enumlist)->push_back((yyvsp[0].enumitem));
				(yyval.enumlist) = (yyvsp[-2].enumlist);
				}
#line 2785 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 131: /* enumlist1: enumitem  */
#line 756 "pac_parse.yy"
                                {
				(yyval.enumlist) = new EnumList();
				(yyval.enumlist)->push_back((yyvsp[0].enumitem));
				}
#line 2794 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 132: /* enumitem: tok_id  */
#line 763 "pac_parse.yy"
                                {
				(yyval.enumitem) = new Enum((yyvsp[0].id));
				}
#line 2802 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 133: /* enumitem: tok_id '=' expr  */
#line 767 "pac_parse.yy"
                                {
				(yyval.enumitem) = new Enum((yyvsp[-2].id), (yyvsp[0].expr));
				}
#line 2810 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 134: /* conn: sahlist  */
#line 773 "pac_parse.yy"
                                {
				(yyval.aelemlist) = (yyvsp[0].aelemlist);
				}
#line 2818 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 135: /* flow: sahlist  */
#line 779 "pac_parse.yy"
                                {
				(yyval.aelemlist) = (yyvsp[0].aelemlist);
				}
#line 2826 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 136: /* sahlist: %empty  */
#line 786 "pac_parse.yy"
                                {
				(yyval.aelemlist) = new AnalyzerElementList();
				}
#line 2834 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 137: /* sahlist: sahlist sah  */
#line 790 "pac_parse.yy"
                                {
				(yyvsp[-1].aelemlist)->push_back((yyvsp[0].aelem));
				(yyval.aelemlist) = (yyvsp[-1].aelemlist);
				}
#line 2843 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 138: /* sah: TOK_LPB_MEMBER embedded_code TOK_RPB  */
#line 797 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerHelper(AnalyzerHelper::MEMBER_DECLS, (yyvsp[-1].embedded_code));
				}
#line 2851 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 139: /* sah: TOK_LPB_INIT embedded_code TOK_RPB  */
#line 801 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerHelper(AnalyzerHelper::INIT_CODE, (yyvsp[-1].embedded_code));
				}
#line 2859 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 140: /* sah: TOK_LPB_CLEANUP embedded_code TOK_RPB  */
#line 805 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerHelper(AnalyzerHelper::CLEANUP_CODE, (yyvsp[-1].embedded_code));
				}
#line 2867 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 141: /* sah: TOK_LPB_EOF embedded_code TOK_RPB  */
#line 809 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerHelper(AnalyzerHelper::EOF_CODE, (yyvsp[-1].embedded_code));
				}
#line 2875 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 142: /* sah: TOK_FLOWDIR '=' tok_id optargs ';'  */
#line 813 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerFlow((AnalyzerFlow::Direction) (yyvsp[-4].val), (yyvsp[-2].id), (yyvsp[-1].exprlist));
				}
#line 2883 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 143: /* sah: TOK_DATAUNIT '=' tok_id optargs TOK_WITHCONTEXT '(' optexprlist ')' ';'  */
#line 817 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerDataUnit(
					(AnalyzerDataUnit::DataUnitType) (yyvsp[-8].val),
					(yyvsp[-6].id),
					(yyvsp[-5].exprlist),
					(yyvsp[-2].exprlist));
				}
#line 2895 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 144: /* sah: TOK_FUNCTION function  */
#line 825 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerFunction((yyvsp[0].function));
				}
#line 2903 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 145: /* sah: TOK_STATE '{' statevarlist '}'  */
#line 829 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerState((yyvsp[-1].statevarlist));
				}
#line 2911 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 146: /* sah: TOK_ACTION tok_id TOK_WHEN '(' actionparam ')' TOK_LPB embedded_code TOK_RPB  */
#line 833 "pac_parse.yy"
                                {
				(yyval.aelem) = new AnalyzerAction((yyvsp[-7].id), (AnalyzerAction::When) (yyvsp[-6].val), (yyvsp[-4].actionparam), (yyvsp[-1].embedded_code));
				}
#line 2919 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 147: /* statevarlist: %empty  */
#line 839 "pac_parse.yy"
                                {
				(yyval.statevarlist) = new StateVarList();
				}
#line 2927 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 148: /* statevarlist: statevarlist statevar ';'  */
#line 843 "pac_parse.yy"
                                {
				(yyvsp[-2].statevarlist)->push_back((yyvsp[-1].statevar));
				(yyval.statevarlist) = (yyvsp[-2].statevarlist);
				}
#line 2936 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 149: /* statevar: tok_id ':' type1  */
#line 850 "pac_parse.yy"
                                {
				(yyval.statevar) = new StateVar((yyvsp[-2].id), (yyvsp[0].type));
				}
#line 2944 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 150: /* actionparam: tok_id TOK_LE actionparamtype  */
#line 856 "pac_parse.yy"
                                {
				(yyval.actionparam) = new ActionParam((yyvsp[-2].id), (yyvsp[0].actionparamtype));
				}
#line 2952 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 151: /* actionparamtype: tok_id  */
#line 862 "pac_parse.yy"
                                {
				(yyval.actionparamtype) = new ActionParamType((yyvsp[0].id));
				}
#line 2960 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 152: /* actionparamtype: tok_id '.' tok_id  */
#line 866 "pac_parse.yy"
                                {
				(yyval.actionparamtype) = new ActionParamType((yyvsp[-2].id), (yyvsp[0].id));
				}
#line 2968 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 153: /* embedded_code: %empty  */
#line 872 "pac_parse.yy"
                                {
				(yyval.embedded_code) = new EmbeddedCode();
				}
#line 2976 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 154: /* embedded_code: embedded_code TOK_EMBEDDED_ATOM  */
#line 876 "pac_parse.yy"
                                {
				(yyvsp[-1].embedded_code)->Append((yyvsp[0].val));
				(yyval.embedded_code) = (yyvsp[-1].embedded_code);
				}
#line 2985 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 155: /* embedded_code: embedded_code TOK_EMBEDDED_STRING  */
#line 881 "pac_parse.yy"
                                {
				(yyvsp[-1].embedded_code)->Append((yyvsp[0].str));
				(yyval.embedded_code) = (yyvsp[-1].embedded_code);
				}
#line 2994 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 156: /* embedded_code: embedded_code embedded_pac_primitive  */
#line 886 "pac_parse.yy"
                                {
				(yyvsp[-1].embedded_code)->Append((yyvsp[0].pacprimitive));
				(yyval.embedded_code) = (yyvsp[-1].embedded_code);
				}
#line 3003 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 157: /* embedded_pac_primitive: TOK_PAC_VAL expr TOK_END_PAC  */
#line 893 "pac_parse.yy"
                                {
				(yyval.pacprimitive) = new PPVal((yyvsp[-1].expr));
				}
#line 3011 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 158: /* embedded_pac_primitive: TOK_PAC_SET expr TOK_END_PAC  */
#line 897 "pac_parse.yy"
                                {
				(yyval.pacprimitive) = new PPSet((yyvsp[-1].expr));
				}
#line 3019 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 159: /* embedded_pac_primitive: TOK_PAC_TYPE expr TOK_END_PAC  */
#line 901 "pac_parse.yy"
                                {
				(yyval.pacprimitive) = new PPType((yyvsp[-1].expr));
				}
#line 3027 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 160: /* embedded_pac_primitive: TOK_PAC_CONST_DEF tok_id '=' expr TOK_END_PAC  */
#line 905 "pac_parse.yy"
                                {
				(yyval.pacprimitive) = new PPConstDef((yyvsp[-3].id), (yyvsp[-1].expr));
				}
#line 3035 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 161: /* optargs: %empty  */
#line 911 "pac_parse.yy"
                                {
				(yyval.exprlist) = 0;
				}
#line 3043 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 162: /* optargs: '(' optexprlist ')'  */
#line 915 "pac_parse.yy"
                                {
				(yyval.exprlist) = (yyvsp[-1].exprlist);
				}
#line 3051 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 163: /* letfieldlist: letfieldlist letfield ';'  */
#line 921 "pac_parse.yy"
                                {
				(yyvsp[-2].fieldlist)->push_back((yyvsp[-1].field));
				(yyval.fieldlist) = (yyvsp[-2].fieldlist);
				}
#line 3060 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 164: /* letfieldlist: letfieldlist withinputfield ';'  */
#line 926 "pac_parse.yy"
                                {
				(yyvsp[-2].fieldlist)->push_back((yyvsp[-1].field));
				(yyval.fieldlist) = (yyvsp[-2].fieldlist);
				}
#line 3069 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 165: /* letfieldlist: %empty  */
#line 931 "pac_parse.yy"
                                {
				(yyval.fieldlist) = new FieldList();
				}
#line 3077 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 166: /* letfield: tok_id opttype optinit optattrs  */
#line 937 "pac_parse.yy"
                                {
				(yyval.field) = new LetField((yyvsp[-3].id), (yyvsp[-2].type), (yyvsp[-1].expr));
				(yyval.field)->AddAttr((yyvsp[0].attrlist));
				}
#line 3086 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 167: /* withinputfield: tok_id ':' type1 TOK_WITHINPUT input optattrs  */
#line 944 "pac_parse.yy"
                                {
				(yyval.field) = new WithInputField((yyvsp[-5].id), (yyvsp[-3].type), (yyvsp[-1].input));
				(yyval.field)->AddAttr((yyvsp[0].attrlist));
				}
#line 3095 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 168: /* input: expr  */
#line 952 "pac_parse.yy"
                                {
				(yyval.input) = new InputBuffer((yyvsp[0].expr));
				}
#line 3103 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 169: /* optattrs: %empty  */
#line 958 "pac_parse.yy"
                                {
				(yyval.attrlist) = 0;
				}
#line 3111 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 170: /* optattrs: attrlist  */
#line 962 "pac_parse.yy"
                                {
				(yyval.attrlist) = (yyvsp[0].attrlist);
				}
#line 3119 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 171: /* attrlist: attrlist optcomma attr  */
#line 968 "pac_parse.yy"
                                {
				if ( (yyvsp[0].attr) )
					(yyvsp[-2].attrlist)->push_back((yyvsp[0].attr));
				(yyval.attrlist) = (yyvsp[-2].attrlist);
				}
#line 3129 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 172: /* attrlist: attr  */
#line 974 "pac_parse.yy"
                                {
				(yyval.attrlist) = new AttrList();
				if ( (yyvsp[0].attr) )
					(yyval.attrlist)->push_back((yyvsp[0].attr));
				}
#line 3139 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 175: /* attr: TOK_ATTR_BYTEORDER '=' expr  */
#line 986 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_BYTEORDER, (yyvsp[0].expr));
				}
#line 3147 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 176: /* attr: TOK_ATTR_CHECK expr  */
#line 990 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_CHECK, (yyvsp[0].expr));
				}
#line 3155 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 177: /* attr: TOK_ATTR_CHUNKED  */
#line 994 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_CHUNKED);
				}
#line 3163 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 178: /* attr: TOK_ATTR_ENFORCE expr  */
#line 998 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_ENFORCE, (yyvsp[0].expr));
				}
#line 3171 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 179: /* attr: TOK_ATTR_EXPORTSOURCEDATA  */
#line 1002 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_EXPORTSOURCEDATA);
				}
#line 3179 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 180: /* attr: TOK_ATTR_IF expr  */
#line 1006 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_IF, (yyvsp[0].expr));
				}
#line 3187 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 181: /* attr: TOK_ATTR_LENGTH '=' expr  */
#line 1010 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_LENGTH, (yyvsp[0].expr));
				}
#line 3195 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 182: /* attr: TOK_ATTR_LET '{' letfieldlist '}'  */
#line 1014 "pac_parse.yy"
                                {
				(yyval.attr) = new LetAttr((yyvsp[-1].fieldlist));
				}
#line 3203 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 183: /* attr: TOK_ATTR_LINEBREAKER '=' expr  */
#line 1018 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_LINEBREAKER, (yyvsp[0].expr));
				}
#line 3211 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 184: /* attr: TOK_ATTR_MULTILINE '(' expr ')'  */
#line 1022 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_MULTILINE, (yyvsp[-1].expr));
				}
#line 3219 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 185: /* attr: TOK_ATTR_ONELINE optlinebreaker  */
#line 1026 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_ONELINE, (yyvsp[0].expr));
				}
#line 3227 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 186: /* attr: TOK_ATTR_REFCOUNT  */
#line 1030 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_REFCOUNT);
				}
#line 3235 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 187: /* attr: TOK_ATTR_REQUIRES '(' optexprlist ')'  */
#line 1034 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_REQUIRES, (yyvsp[-1].exprlist));
				}
#line 3243 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 188: /* attr: TOK_ATTR_RESTOFDATA  */
#line 1038 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_RESTOFDATA);
				}
#line 3251 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 189: /* attr: TOK_ATTR_RESTOFFLOW  */
#line 1042 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_RESTOFFLOW);
				}
#line 3259 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 190: /* attr: TOK_ATTR_TRANSIENT  */
#line 1046 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_TRANSIENT);
				}
#line 3267 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 191: /* attr: TOK_ATTR_UNTIL expr  */
#line 1050 "pac_parse.yy"
                                {
				(yyval.attr) = new Attr(ATTR_UNTIL, (yyvsp[0].expr));
				}
#line 3275 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 192: /* optlinebreaker: %empty  */
#line 1056 "pac_parse.yy"
                                {
				(yyval.expr) = 0;
				}
#line 3283 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;

  case 193: /* optlinebreaker: '(' expr ')'  */
#line 1060 "pac_parse.yy"
                                {
				(yyval.expr) = (yyvsp[-1].expr);
				}
#line 3291 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"
    break;


#line 3295 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.cc"

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

#line 1065 "pac_parse.yy"


const ID* current_decl_id = 0;

int yyerror(const char msg[])
	{
	auto n = strlen(msg) + yyleng + 64;
	char* msgbuf = new char[n];

	if ( ! yychar || ! yytext || yytext[0] == '\0' )
		snprintf(msgbuf, n, "%s, at end of file", msg);

	else if ( yytext[0] == '\n' )
		snprintf(msgbuf, n, "%s, on previous line", msg);

	else
		snprintf(msgbuf, n, "%s, at or near \"%s\"", msg, yytext);

	/*
	extern int column;
	sprintf(msgbuf, "%*s\n%*s\n", column, "^", column, msg);
	*/

	if ( ! input_filename.empty() )
		fprintf(stderr, "%s:%d: ", input_filename.c_str(), line_number);
	else
		fprintf(stderr, "line %d: ", line_number);
	fprintf(stderr, "%s", msgbuf);
	fprintf(stderr, " (yychar=%d)", yychar);
	fprintf(stderr, "\n");

	delete [] msgbuf;
	return 0;
        }
