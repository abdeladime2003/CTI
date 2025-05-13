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
#line 1 "builtin-func.y"

#include <vector>
#include <set>
#include <string>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>

#include "module_util.h"

using namespace std;

extern int line_number;
extern char* input_filename;
extern char* input_filename_with_path;
extern char* plugin;
extern bool alternative_mode;

#define print_line_directive(fp) fprintf(fp, "\n#line %d \"%s\"\n", line_number, input_filename_with_path)

extern FILE* fp_zeek_init;
extern FILE* fp_func_def;
extern FILE* fp_func_h;
extern FILE* fp_func_init;
extern FILE* fp_netvar_h;
extern FILE* fp_netvar_def;
extern FILE* fp_netvar_init;

bool in_c_code = false;
string current_module = GLOBAL_MODULE_NAME;
int definition_type;
string type_name;

// Alternate event prototypes are only written to the .zeek file, but
// don't need any further changes to C++ source/header files, so this
// set keeps track of whether the first event prototype information has
// already been defined/written to the C++ files.
static std::set<std::string> events;

enum {
	C_SEGMENT_DEF,
	FUNC_DEF,
	EVENT_DEF,
	TYPE_DEF,
	CONST_DEF,
};

// Holds the name of a declared object (function, enum, record type, event,
// etc. and information about namespaces, etc.
struct decl_struct {
	string module_name;
	string bare_name; // name without module or namespace
	string c_namespace_start; // "opening" namespace for use in netvar_*
	string c_namespace_end;   // closing "}" for all the above namespaces
	string c_fullname; // fully qualified name (namespace::....) for use in netvar_init
	string zeek_fullname; // fully qualified zeek name, for netvar (and lookup_ID())
	string zeek_name;  // the name as we read it from input. What we write into the .zeek file

	// special cases for events. Events have an EventHandlerPtr
	// and a enqueue_* function. This name is for the enqueue_* function
	string enqueue_c_namespace_start;
	string enqueue_c_namespace_end;
	string enqueue_c_barename;
	string enqueue_c_fullname;
} decl;

void set_definition_type(int type, const char *arg_type_name)
	{
	definition_type = type;
	if ( type == TYPE_DEF && arg_type_name )
		type_name = string(arg_type_name);
	else
		type_name = "";
	}

void set_decl_name(const char *name)
	{
	decl.bare_name = extract_var_name(name);

	// make_full_var_name prepends the correct module, if any
	// then we can extract the module name again.
	string varname = make_full_var_name(current_module.c_str(), name);
	decl.module_name = extract_module_name(varname.c_str());

	decl.c_namespace_start = "";
	decl.c_namespace_end = "";
	decl.c_fullname = "";
	decl.zeek_fullname = "";
	decl.zeek_name = "";

	decl.enqueue_c_fullname = "";
	decl.enqueue_c_barename = string("enqueue_") + decl.bare_name;
	decl.enqueue_c_namespace_start = "";
	decl.enqueue_c_namespace_end = "";

	switch ( definition_type ) {
	case TYPE_DEF:
		decl.c_namespace_start = "namespace BifType { namespace " + type_name + "{ ";
		decl.c_namespace_end = " } }";
		decl.c_fullname = "BifType::" + type_name + "::";
		break;

	case CONST_DEF:
		decl.c_namespace_start = "namespace BifConst { ";
		decl.c_namespace_end = " } ";
		decl.c_fullname = "BifConst::";
		break;

	case FUNC_DEF:
		decl.c_namespace_start = "namespace BifFunc { ";
		decl.c_namespace_end = " } ";
		decl.c_fullname = "BifFunc::";
		break;

	case EVENT_DEF:
		decl.c_namespace_start = "";
		decl.c_namespace_end = "";
		decl.c_fullname = "::";  // need this for namespace qualified events due do event_c_body
		decl.enqueue_c_namespace_start = "namespace BifEvent { ";
		decl.enqueue_c_namespace_end = " } ";
		decl.enqueue_c_fullname = "zeek::BifEvent::";
		break;

	default:
		break;
	}

	if ( decl.module_name != GLOBAL_MODULE_NAME )
		{
		decl.c_namespace_start += "namespace " + decl.module_name + " { ";
		decl.c_namespace_end += string(" }");
		decl.c_fullname += decl.module_name + "::";
		decl.zeek_fullname += decl.module_name + "::";

		decl.enqueue_c_namespace_start  += "namespace " + decl.module_name + " { ";
		decl.enqueue_c_namespace_end += " } ";
		decl.enqueue_c_fullname += decl.module_name + "::";
		}

	decl.zeek_fullname += decl.bare_name;
	decl.c_fullname += decl.bare_name;
	decl.zeek_name += name;
	decl.enqueue_c_fullname += decl.enqueue_c_barename;
	}

const char* arg_list_name = "BiF_ARGS";

#include "bif_arg.h"

/* Map bif/zeek type names to C types for use in const declaration */
static struct {
	const char* bif_type;
	const char* zeek_type;
	const char* c_type;
	const char* c_type_smart;
	const char* accessor;
	const char* accessor_smart;
	const char* cast_smart;
	const char* constructor;
	const char* ctor_smatr;
} builtin_types[] = {
#define DEFINE_BIF_TYPE(id, bif_type, zeek_type, c_type, c_type_smart, accessor, accessor_smart, cast_smart, constructor, ctor_smart) \
	{bif_type, zeek_type, c_type, c_type_smart, accessor, accessor_smart, cast_smart, constructor, ctor_smart},
#include "bif_type.def"
#undef DEFINE_BIF_TYPE
};

int get_type_index(const char *type_name)
	{
	for ( int i = 0; builtin_types[i].bif_type[0] != '\0'; ++i )
		{
		if ( strcmp(builtin_types[i].bif_type, type_name) == 0 )
			return i;
		}
		return TYPE_OTHER;
	}


int var_arg; // whether the number of arguments is variable
std::vector<BuiltinFuncArg*> args;

extern int yyerror(const char[]);
extern int yywarn(const char msg[]);
extern int yylex();

char* concat(const char* str1, const char* str2)
	{
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	char* s = new char[len1 + len2 +1];

	memcpy(s, str1, len1);
	memcpy(s + len1, str2, len2);

	s[len1+len2] = '\0';

	return s;
	}

static void print_event_c_prototype_args(FILE* fp)
	{
	for ( auto i = 0u; i < args.size(); ++i )
		{
		if ( i > 0 )
			fprintf(fp, ", ");

		args[i]->PrintCArg(fp, i);
		}
	}

static void print_event_c_prototype_header(FILE* fp)
	{
	fprintf(fp, "namespace zeek { %s void %s(zeek::analyzer::Analyzer* analyzer%s",
	        decl.enqueue_c_namespace_start.c_str(),
	        decl.enqueue_c_barename.c_str(),
	        args.size() ? ", " : "" );

	print_event_c_prototype_args(fp);
	fprintf(fp, ")");
	fprintf(fp, "; %s }\n", decl.enqueue_c_namespace_end.c_str());
	}

static void print_event_c_prototype_impl(FILE* fp)
	{
	fprintf(fp, "void %s(zeek::analyzer::Analyzer* analyzer%s",
	        decl.enqueue_c_fullname.c_str(),
	        args.size() ? ", " : "" );

	print_event_c_prototype_args(fp);
	fprintf(fp, ")");
	fprintf(fp, "\n");
	}

static void print_event_c_body(FILE* fp)
	{
	fprintf(fp, "\t{\n");
	fprintf(fp, "\t// Note that it is intentional that here we do not\n");
	fprintf(fp, "\t// check if %s is NULL, which should happen *before*\n",
		decl.c_fullname.c_str());
	fprintf(fp, "\t// %s is called to avoid unnecessary Val\n",
		decl.enqueue_c_fullname.c_str());
	fprintf(fp, "\t// allocation.\n");
	fprintf(fp, "\n");

	BuiltinFuncArg* connection_arg = nullptr;

	fprintf(fp, "\tzeek::event_mgr.Enqueue(%s, zeek::Args{\n", decl.c_fullname.c_str());

	for ( int i = 0; i < (int) args.size(); ++i )
		{
		fprintf(fp, "\t        ");
		args[i]->PrintValConstructor(fp);
		fprintf(fp, ",\n");

		if ( args[i]->Type() == TYPE_CONNECTION )
			{
			if ( connection_arg == nullptr )
				connection_arg = args[i];
			else
				{
				// We are seeing two connection type arguments.
				yywarn("Warning: with more than connection-type "
				       "event arguments, bifcl only passes "
				       "the first one to EventMgr as cookie.");
				}
			}
		}

	fprintf(fp, "\t        },\n\t    zeek::util::detail::SOURCE_LOCAL, analyzer ? analyzer->GetID() : 0");

	if ( connection_arg )
		// Pass the connection to the EventMgr as the "cookie"
		fprintf(fp, ", %s", connection_arg->Name());

	fprintf(fp, ");\n");
	fprintf(fp, "\t}\n\n");
	//fprintf(fp, "%s // end namespace\n", decl.enqueue_c_namespace_end.c_str());
	}

void record_bif_item(const char* id, const char* type)
	{
	if ( ! plugin )
		return;

	fprintf(fp_func_init, "\tplugin->AddBifItem(\"%s\", zeek::plugin::BifItem::%s);\n", id, type);
	}


#line 362 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"

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

#include "bif_parse.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_LPP = 3,                    /* TOK_LPP  */
  YYSYMBOL_TOK_RPP = 4,                    /* TOK_RPP  */
  YYSYMBOL_TOK_LPB = 5,                    /* TOK_LPB  */
  YYSYMBOL_TOK_RPB = 6,                    /* TOK_RPB  */
  YYSYMBOL_TOK_LPPB = 7,                   /* TOK_LPPB  */
  YYSYMBOL_TOK_RPPB = 8,                   /* TOK_RPPB  */
  YYSYMBOL_TOK_VAR_ARG = 9,                /* TOK_VAR_ARG  */
  YYSYMBOL_TOK_BOOL = 10,                  /* TOK_BOOL  */
  YYSYMBOL_TOK_FUNCTION = 11,              /* TOK_FUNCTION  */
  YYSYMBOL_TOK_EVENT = 12,                 /* TOK_EVENT  */
  YYSYMBOL_TOK_CONST = 13,                 /* TOK_CONST  */
  YYSYMBOL_TOK_ENUM = 14,                  /* TOK_ENUM  */
  YYSYMBOL_TOK_OF = 15,                    /* TOK_OF  */
  YYSYMBOL_TOK_TYPE = 16,                  /* TOK_TYPE  */
  YYSYMBOL_TOK_RECORD = 17,                /* TOK_RECORD  */
  YYSYMBOL_TOK_SET = 18,                   /* TOK_SET  */
  YYSYMBOL_TOK_VECTOR = 19,                /* TOK_VECTOR  */
  YYSYMBOL_TOK_OPAQUE = 20,                /* TOK_OPAQUE  */
  YYSYMBOL_TOK_TABLE = 21,                 /* TOK_TABLE  */
  YYSYMBOL_TOK_MODULE = 22,                /* TOK_MODULE  */
  YYSYMBOL_TOK_ARGS = 23,                  /* TOK_ARGS  */
  YYSYMBOL_TOK_ARG = 24,                   /* TOK_ARG  */
  YYSYMBOL_TOK_ARGC = 25,                  /* TOK_ARGC  */
  YYSYMBOL_TOK_ID = 26,                    /* TOK_ID  */
  YYSYMBOL_TOK_ATTR = 27,                  /* TOK_ATTR  */
  YYSYMBOL_TOK_CSTR = 28,                  /* TOK_CSTR  */
  YYSYMBOL_TOK_LF = 29,                    /* TOK_LF  */
  YYSYMBOL_TOK_WS = 30,                    /* TOK_WS  */
  YYSYMBOL_TOK_COMMENT = 31,               /* TOK_COMMENT  */
  YYSYMBOL_TOK_ATOM = 32,                  /* TOK_ATOM  */
  YYSYMBOL_TOK_INT = 33,                   /* TOK_INT  */
  YYSYMBOL_TOK_C_TOKEN = 34,               /* TOK_C_TOKEN  */
  YYSYMBOL_35_ = 35,                       /* ','  */
  YYSYMBOL_36_ = 36,                       /* ':'  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_38_ = 38,                       /* '='  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_builtin_lang = 40,              /* builtin_lang  */
  YYSYMBOL_definitions = 41,               /* definitions  */
  YYSYMBOL_definition = 42,                /* definition  */
  YYSYMBOL_module_def = 43,                /* module_def  */
  YYSYMBOL_type_def = 44,                  /* type_def  */
  YYSYMBOL_type_def_types = 45,            /* type_def_types  */
  YYSYMBOL_opt_func_attrs = 46,            /* opt_func_attrs  */
  YYSYMBOL_event_def = 47,                 /* event_def  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_func_def = 49,                  /* func_def  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_enum_def = 51,                  /* enum_def  */
  YYSYMBOL_enum_def_1 = 52,                /* enum_def_1  */
  YYSYMBOL_enum_list = 53,                 /* enum_list  */
  YYSYMBOL_const_def = 54,                 /* const_def  */
  YYSYMBOL_attr_list = 55,                 /* attr_list  */
  YYSYMBOL_opt_attr_list = 56,             /* opt_attr_list  */
  YYSYMBOL_func_prefix = 57,               /* func_prefix  */
  YYSYMBOL_event_prefix = 58,              /* event_prefix  */
  YYSYMBOL_end_of_head = 59,               /* end_of_head  */
  YYSYMBOL_typed_head = 60,                /* typed_head  */
  YYSYMBOL_plain_head = 61,                /* plain_head  */
  YYSYMBOL_head_1 = 62,                    /* head_1  */
  YYSYMBOL_arg_begin = 63,                 /* arg_begin  */
  YYSYMBOL_arg_end = 64,                   /* arg_end  */
  YYSYMBOL_args = 65,                      /* args  */
  YYSYMBOL_args_1 = 66,                    /* args_1  */
  YYSYMBOL_type = 67,                      /* type  */
  YYSYMBOL_arg = 68,                       /* arg  */
  YYSYMBOL_return_type = 69,               /* return_type  */
  YYSYMBOL_body = 70,                      /* body  */
  YYSYMBOL_c_code_begin = 71,              /* c_code_begin  */
  YYSYMBOL_c_code_end = 72,                /* c_code_end  */
  YYSYMBOL_body_start = 73,                /* body_start  */
  YYSYMBOL_body_end = 74,                  /* body_end  */
  YYSYMBOL_c_code_segment = 75,            /* c_code_segment  */
  YYSYMBOL_c_body = 76,                    /* c_body  */
  YYSYMBOL_c_atom = 77,                    /* c_atom  */
  YYSYMBOL_opt_ws = 78                     /* opt_ws  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  145

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    37,
       2,    38,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   312,   312,   320,   327,   334,   335,   336,   337,   338,
     339,   340,   344,   358,   382,   384,   386,   388,   392,   395,
     399,   398,   411,   410,   414,   441,   457,   462,   467,   471,
     514,   517,   521,   523,   526,   530,   535,   540,   545,   566,
     631,   635,   638,   639,   643,   645,   653,   655,   659,   661,
     669,   678,   686,   693,   696,   733,   739,   742,   744,   748,
     750,   752,   754,   756,   758,   760,   762,   767,   769,   771,
     784
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_LPP", "TOK_RPP",
  "TOK_LPB", "TOK_RPB", "TOK_LPPB", "TOK_RPPB", "TOK_VAR_ARG", "TOK_BOOL",
  "TOK_FUNCTION", "TOK_EVENT", "TOK_CONST", "TOK_ENUM", "TOK_OF",
  "TOK_TYPE", "TOK_RECORD", "TOK_SET", "TOK_VECTOR", "TOK_OPAQUE",
  "TOK_TABLE", "TOK_MODULE", "TOK_ARGS", "TOK_ARG", "TOK_ARGC", "TOK_ID",
  "TOK_ATTR", "TOK_CSTR", "TOK_LF", "TOK_WS", "TOK_COMMENT", "TOK_ATOM",
  "TOK_INT", "TOK_C_TOKEN", "','", "':'", "';'", "'='", "$accept",
  "builtin_lang", "definitions", "definition", "module_def", "type_def",
  "type_def_types", "opt_func_attrs", "event_def", "$@1", "func_def",
  "$@2", "enum_def", "enum_def_1", "enum_list", "const_def", "attr_list",
  "opt_attr_list", "func_prefix", "event_prefix", "end_of_head",
  "typed_head", "plain_head", "head_1", "arg_begin", "arg_end", "args",
  "args_1", "type", "arg", "return_type", "body", "c_code_begin",
  "c_code_end", "body_start", "body_end", "c_code_segment", "c_body",
  "c_atom", "opt_ws", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-105)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -105,     1,    73,    67,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,   139,   145,   151,
     157,    67,     9,   163,   163,   101,    67,  -105,  -105,  -105,
    -105,   -20,  -105,  -105,   -20,   -23,  -105,   -20,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,     6,  -105,   120,    29,
     123,    18,  -105,    -8,  -105,   108,    23,  -105,    -8,  -105,
    -105,    25,    -5,    35,  -105,  -105,    67,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,    67,    88,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,   169,    67,    82,    67,
      76,    31,  -105,  -105,  -105,    67,    35,   131,   180,     4,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
     -13,    67,  -105,  -105,  -105,  -105,    44,   111,    41,  -105,
      -1,  -105,   180,    88,  -105,  -105,  -105,  -105,  -105,   175,
    -105,  -105,    67,  -105,  -105
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      70,     0,     2,     4,     1,    52,    34,    35,    70,    70,
      70,    70,    70,    11,    10,     5,     6,     8,    28,     9,
      70,    70,     7,    68,    67,    69,    70,     0,     0,     0,
       0,     3,     0,     0,     0,    53,    57,    70,    70,    70,
      70,    33,    70,    70,    19,     0,    70,    19,    62,    61,
      63,    59,    64,    65,    66,    60,     0,    70,     0,     0,
       0,     0,    31,    32,    24,     0,     0,    22,    70,    70,
      37,     0,    42,    43,    20,    56,    58,    70,    70,    70,
      12,    30,    70,    70,    40,    39,    36,    18,     0,    41,
      70,    70,    49,    70,    70,    36,     0,    25,     0,    26,
       0,     0,    70,    47,    70,    38,     0,     0,    33,     0,
      70,    14,    15,    16,    17,    70,    70,    52,    23,    70,
       0,    50,    70,    70,    45,    21,     0,     0,     0,    54,
       0,    70,    33,     0,    29,    13,    70,    53,    51,     0,
      44,    48,    27,    55,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -105,  -105,  -105,  -105,  -105,  -105,  -105,    -2,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,   -41,  -104,  -105,  -105,
     -45,  -105,    17,  -105,  -105,  -105,  -105,  -105,   -77,   -44,
    -105,  -105,   -54,   -70,  -105,  -105,  -105,   -31,  -105,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    12,    13,    14,   115,    67,    15,    95,
      16,    86,    17,    18,    32,    19,    63,    64,    20,    21,
     101,    44,    45,    46,    85,    90,    71,    72,   104,    94,
      70,   118,    26,    56,   119,   138,    22,    35,    57,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       3,     4,   131,    68,   124,   137,    68,    62,    27,    28,
      29,    30,    31,    69,    75,    41,    23,    24,    25,    81,
      33,    34,    48,    49,    50,    51,    84,    52,   140,    89,
      91,    53,    54,    55,    78,    42,   117,    58,    59,    60,
      61,   125,    65,    66,    92,    74,    73,    23,    24,    25,
     109,    47,    23,    24,    25,    80,   141,    76,    23,    24,
      25,    93,   122,   129,    23,    24,    25,   143,    87,    88,
      23,    24,    25,    23,    24,    25,   136,    96,    97,    98,
       5,   134,    99,   100,     6,     7,     8,     9,   130,    10,
     105,   106,     0,   107,   108,    11,    23,    24,    25,   111,
     112,   113,   120,   114,   121,    23,    24,    25,   102,   116,
     126,    23,    24,    25,   103,   127,   128,    23,    24,    25,
       0,     0,   132,   133,    48,    49,    50,    51,     0,    52,
       0,   139,     0,    53,    54,    55,   142,    23,    24,    25,
      23,    24,    25,    82,     0,     0,    83,     0,   135,    23,
      24,    25,    23,    24,    25,     0,    77,     0,     0,    79,
      23,    24,    25,     0,     0,    37,     0,   123,    23,    24,
      25,    38,     0,     0,    23,    24,    25,    39,     0,     0,
      23,    24,    25,    40,     0,     0,    23,    24,    25,    43,
       0,     0,    23,    24,    25,   110,     0,     0,    23,    24,
      25,   144,     0,     0,    23,    24,    25,    62,     0,    23,
      24,    25
};

static const yytype_int16 yycheck[] =
{
       0,     0,    15,    44,   108,     6,    47,    27,     8,     9,
      10,    11,    12,    36,     8,     6,    29,    30,    31,    27,
      20,    21,    23,    24,    25,    26,     3,    28,   132,     4,
      35,    32,    33,    34,     5,    26,     5,    37,    38,    39,
      40,    37,    42,    43,     9,    47,    46,    29,    30,    31,
      95,    34,    29,    30,    31,    37,   133,    57,    29,    30,
      31,    26,   106,   117,    29,    30,    31,   137,    68,    69,
      29,    30,    31,    29,    30,    31,    35,    77,    78,    79,
       7,    37,    82,    83,    11,    12,    13,    14,   119,    16,
      90,    91,    -1,    93,    94,    22,    29,    30,    31,    17,
      18,    19,   102,    21,   104,    29,    30,    31,    20,    33,
     110,    29,    30,    31,    26,   115,   116,    29,    30,    31,
      -1,    -1,   122,   123,    23,    24,    25,    26,    -1,    28,
      -1,   131,    -1,    32,    33,    34,   136,    29,    30,    31,
      29,    30,    31,    35,    -1,    -1,    38,    -1,    37,    29,
      30,    31,    29,    30,    31,    -1,    36,    -1,    -1,    36,
      29,    30,    31,    -1,    -1,    26,    -1,    36,    29,    30,
      31,    26,    -1,    -1,    29,    30,    31,    26,    -1,    -1,
      29,    30,    31,    26,    -1,    -1,    29,    30,    31,    26,
      -1,    -1,    29,    30,    31,    26,    -1,    -1,    29,    30,
      31,    26,    -1,    -1,    29,    30,    31,    27,    -1,    29,
      30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    41,    78,     0,     7,    11,    12,    13,    14,
      16,    22,    42,    43,    44,    47,    49,    51,    52,    54,
      57,    58,    75,    29,    30,    31,    71,    78,    78,    78,
      78,    78,    53,    78,    78,    76,    78,    26,    26,    26,
      26,     6,    26,    26,    60,    61,    62,    61,    23,    24,
      25,    26,    28,    32,    33,    34,    72,    77,    78,    78,
      78,    78,    27,    55,    56,    78,    78,    46,    55,    36,
      69,    65,    66,    78,    46,     8,    78,    36,     5,    36,
      37,    27,    35,    38,     3,    63,    50,    78,    78,     4,
      64,    35,     9,    26,    68,    48,    78,    78,    78,    78,
      78,    59,    20,    26,    67,    78,    78,    78,    78,    59,
      26,    17,    18,    19,    21,    45,    33,     5,    70,    73,
      78,    78,    68,    36,    56,    37,    78,    78,    78,    71,
      76,    15,    78,    78,    37,    37,    35,     6,    74,    78,
      56,    67,    78,    72,    26
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    43,    44,    45,    45,    45,    45,    46,    46,
      48,    47,    50,    49,    51,    52,    53,    53,    53,    54,
      55,    55,    56,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    78,    78,
      78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     9,     1,     1,     1,     1,     2,     0,
       0,     7,     0,     7,     4,     6,     5,     9,     0,     9,
       2,     1,     1,     0,     1,     1,     0,     2,     4,     3,
       1,     1,     1,     1,     6,     4,     5,     1,     5,     1,
       4,     3,     0,     0,     2,     2,     5,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       0
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
  case 2: /* builtin_lang: definitions  */
#line 313 "builtin-func.y"
                        {
			fprintf(fp_zeek_init, "} # end of export section\n");
			fprintf(fp_zeek_init, "module %s;\n", GLOBAL_MODULE_NAME);
			}
#line 1543 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 3: /* definitions: definitions definition opt_ws  */
#line 321 "builtin-func.y"
                        {
			if ( in_c_code )
				fprintf(fp_func_def, "%s", (yyvsp[0].str));
			else
				fprintf(fp_zeek_init, "%s", (yyvsp[0].str));
			}
#line 1554 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 4: /* definitions: opt_ws  */
#line 328 "builtin-func.y"
                        {
			fprintf(fp_zeek_init, "export {\n");
			fprintf(fp_zeek_init, "%s", (yyvsp[0].str));
			}
#line 1563 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 12: /* module_def: TOK_MODULE opt_ws TOK_ID opt_ws ';'  */
#line 345 "builtin-func.y"
                        {
			current_module = string((yyvsp[-2].str));
			fprintf(fp_zeek_init, "module %s;\n", (yyvsp[-2].str));
			}
#line 1572 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 13: /* type_def: TOK_TYPE opt_ws TOK_ID opt_ws ':' opt_ws type_def_types opt_ws ';'  */
#line 359 "builtin-func.y"
                        {
			set_decl_name((yyvsp[-6].str));

			fprintf(fp_netvar_h, "namespace zeek { %s extern zeek::IntrusivePtr<zeek::%sType> %s; %s}\n",
				decl.c_namespace_start.c_str(), type_name.c_str(),
				decl.bare_name.c_str(), decl.c_namespace_end.c_str());

			fprintf(fp_netvar_def, "namespace zeek { %s zeek::IntrusivePtr<zeek::%sType> %s; %s}\n",
				decl.c_namespace_start.c_str(), type_name.c_str(),
				decl.bare_name.c_str(), decl.c_namespace_end.c_str());
			fprintf(fp_netvar_def, "%s zeek::%sType * %s; %s\n",
				decl.c_namespace_start.c_str(), type_name.c_str(),
				decl.bare_name.c_str(), decl.c_namespace_end.c_str());

			fprintf(fp_netvar_init,
				"\tzeek::%s = zeek::id::find_type<zeek::%sType>(\"%s\");\n",
				decl.c_fullname.c_str(), type_name.c_str(),
				decl.zeek_fullname.c_str());

			record_bif_item(decl.zeek_fullname.c_str(), "TYPE");
			}
#line 1598 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 14: /* type_def_types: TOK_RECORD  */
#line 383 "builtin-func.y"
                        { set_definition_type(TYPE_DEF, "Record"); }
#line 1604 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 15: /* type_def_types: TOK_SET  */
#line 385 "builtin-func.y"
                        { set_definition_type(TYPE_DEF, "Set"); }
#line 1610 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 16: /* type_def_types: TOK_VECTOR  */
#line 387 "builtin-func.y"
                        { set_definition_type(TYPE_DEF, "Vector"); }
#line 1616 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 17: /* type_def_types: TOK_TABLE  */
#line 389 "builtin-func.y"
                        { set_definition_type(TYPE_DEF, "Table"); }
#line 1622 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 18: /* opt_func_attrs: attr_list opt_ws  */
#line 393 "builtin-func.y"
                { (yyval.str) = (yyvsp[-1].str); }
#line 1628 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 19: /* opt_func_attrs: %empty  */
#line 395 "builtin-func.y"
                { (yyval.str) = ""; }
#line 1634 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 20: /* $@1: %empty  */
#line 399 "builtin-func.y"
                        { fprintf(fp_zeek_init, "%s", (yyvsp[0].str)); }
#line 1640 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 21: /* event_def: event_prefix opt_ws plain_head opt_func_attrs $@1 end_of_head ';'  */
#line 400 "builtin-func.y"
                        {
			if ( events.find(decl.zeek_fullname) == events.end() )
				{
				print_event_c_prototype_header(fp_func_h);
				print_event_c_prototype_impl(fp_func_def);
				print_event_c_body(fp_func_def);
				events.insert(decl.zeek_fullname);
				}
			}
#line 1654 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 22: /* $@2: %empty  */
#line 411 "builtin-func.y"
                        { fprintf(fp_zeek_init, "%s", (yyvsp[0].str)); }
#line 1660 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 24: /* enum_def: enum_def_1 enum_list TOK_RPB opt_attr_list  */
#line 415 "builtin-func.y"
                        {
			// First, put an end to the enum type decl.
			fprintf(fp_zeek_init, "} ");
			fprintf(fp_zeek_init, "%s", (yyvsp[0].str));
			fprintf(fp_zeek_init, ";\n");
			if ( decl.module_name != GLOBAL_MODULE_NAME )
				fprintf(fp_netvar_h, "}; } }\n");
			else
				fprintf(fp_netvar_h, "}; }\n");

			// Now generate the netvar's.
			fprintf(fp_netvar_h, "namespace zeek { %s extern zeek::IntrusivePtr<zeek::EnumType> %s; %s}\n",
				decl.c_namespace_start.c_str(), decl.bare_name.c_str(), decl.c_namespace_end.c_str());
			fprintf(fp_netvar_def, "namespace zeek { %s zeek::IntrusivePtr<zeek::EnumType> %s; %s}\n",
				decl.c_namespace_start.c_str(), decl.bare_name.c_str(), decl.c_namespace_end.c_str());
			fprintf(fp_netvar_def, "%s zeek::EnumType * %s; %s\n",
				decl.c_namespace_start.c_str(), decl.bare_name.c_str(), decl.c_namespace_end.c_str());

			fprintf(fp_netvar_init,
				"\tzeek::%s = zeek::id::find_type<zeek::EnumType>(\"%s\");\n",
				decl.c_fullname.c_str(), decl.zeek_fullname.c_str());

			record_bif_item(decl.zeek_fullname.c_str(), "TYPE");
			}
#line 1689 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 25: /* enum_def_1: TOK_ENUM opt_ws TOK_ID opt_ws TOK_LPB opt_ws  */
#line 442 "builtin-func.y"
                        {
			set_definition_type(TYPE_DEF, "Enum");
			set_decl_name((yyvsp[-3].str));
			fprintf(fp_zeek_init, "type %s: enum %s{%s", decl.zeek_name.c_str(), (yyvsp[-2].str), (yyvsp[0].str));

			// this is the namespace were the enumerators are defined, not where
			// the type is defined.
			// We don't support fully qualified names as enumerators. Use a module name
			fprintf(fp_netvar_h, "namespace BifEnum { ");
			if ( decl.module_name != GLOBAL_MODULE_NAME )
				fprintf(fp_netvar_h, "namespace %s { ", decl.module_name.c_str());
			fprintf(fp_netvar_h, "enum %s {\n", (yyvsp[-3].str));
			}
#line 1707 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 26: /* enum_list: enum_list TOK_ID opt_ws ',' opt_ws  */
#line 458 "builtin-func.y"
                        {
			fprintf(fp_zeek_init, "%s%s,%s", (yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[0].str));
			fprintf(fp_netvar_h, "\t%s,\n", (yyvsp[-3].str));
			}
#line 1716 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 27: /* enum_list: enum_list TOK_ID opt_ws '=' opt_ws TOK_INT opt_ws ',' opt_ws  */
#line 463 "builtin-func.y"
                        {
			fprintf(fp_zeek_init, "%s = %s%s,%s", (yyvsp[-7].str), (yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[0].str));
			fprintf(fp_netvar_h, "\t%s = %s,\n", (yyvsp[-7].str), (yyvsp[-3].str));
			}
#line 1725 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 29: /* const_def: TOK_CONST opt_ws TOK_ID opt_ws ':' opt_ws TOK_ID opt_ws ';'  */
#line 472 "builtin-func.y"
                        {
			set_definition_type(CONST_DEF, 0);
			set_decl_name((yyvsp[-6].str));
			int typeidx = get_type_index((yyvsp[-2].str));
			char accessor[1024];
			char accessor_smart[1024];

			snprintf(accessor, sizeof(accessor), builtin_types[typeidx].accessor, "");
			snprintf(accessor_smart, sizeof(accessor_smart), builtin_types[typeidx].accessor_smart, "");


			fprintf(fp_netvar_h, "namespace zeek { %s extern %s %s; %s }\n",
					decl.c_namespace_start.c_str(),
					builtin_types[typeidx].c_type_smart, decl.bare_name.c_str(),
					decl.c_namespace_end.c_str());

			fprintf(fp_netvar_def, "namespace zeek { %s %s %s; %s }\n",
					decl.c_namespace_start.c_str(),
					builtin_types[typeidx].c_type_smart, decl.bare_name.c_str(),
					decl.c_namespace_end.c_str());
			fprintf(fp_netvar_def, "%s %s %s; %s\n",
					decl.c_namespace_start.c_str(),
					builtin_types[typeidx].c_type, decl.bare_name.c_str(),
					decl.c_namespace_end.c_str());

			if ( alternative_mode && ! plugin )
				fprintf(fp_netvar_init, "\tzeek::detail::bif_initializers.emplace_back([]()\n");

			fprintf(fp_netvar_init, "\t{\n");
			fprintf(fp_netvar_init, "\tconst auto& v = zeek::id::find_const%s(\"%s\");\n",
					builtin_types[typeidx].cast_smart, decl.zeek_fullname.c_str());
			fprintf(fp_netvar_init, "\tzeek::%s = v%s;\n",
					decl.c_fullname.c_str(), accessor_smart);
			fprintf(fp_netvar_init, "\t}\n");

			if ( alternative_mode && ! plugin )
				fprintf(fp_netvar_init, "\t);\n");

			record_bif_item(decl.zeek_fullname.c_str(), "CONSTANT");
			}
#line 1770 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 30: /* attr_list: attr_list TOK_ATTR  */
#line 515 "builtin-func.y"
                        { (yyval.str) = concat((yyvsp[-1].str), (yyvsp[0].str)); }
#line 1776 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 33: /* opt_attr_list: %empty  */
#line 523 "builtin-func.y"
                { (yyval.str) = ""; }
#line 1782 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 34: /* func_prefix: TOK_FUNCTION  */
#line 527 "builtin-func.y"
                        { set_definition_type(FUNC_DEF, 0); }
#line 1788 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 35: /* event_prefix: TOK_EVENT  */
#line 531 "builtin-func.y"
                        { set_definition_type(EVENT_DEF, 0); }
#line 1794 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 36: /* end_of_head: %empty  */
#line 535 "builtin-func.y"
                        {
			fprintf(fp_zeek_init, ";\n");
			}
#line 1802 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 37: /* typed_head: plain_head return_type  */
#line 541 "builtin-func.y"
                        {
			}
#line 1809 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 38: /* plain_head: head_1 args arg_end opt_ws  */
#line 546 "builtin-func.y"
                        {
			if ( var_arg )
				fprintf(fp_zeek_init, "va_args: any");
			else
				{
				for ( int i = 0; i < (int) args.size(); ++i )
					{
					if ( i > 0 )
						fprintf(fp_zeek_init, ", ");
					args[i]->PrintZeek(fp_zeek_init);
					}
				}

			fprintf(fp_zeek_init, ")");

			fprintf(fp_zeek_init, "%s", (yyvsp[0].str));
			fprintf(fp_func_def, "%s", (yyvsp[0].str));
			}
#line 1832 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 39: /* head_1: TOK_ID opt_ws arg_begin  */
#line 567 "builtin-func.y"
                        {
			const char* method_type = nullptr;
			set_decl_name((yyvsp[-2].str));

			if ( definition_type == FUNC_DEF )
				{
				method_type = "function";
				print_line_directive(fp_func_def);
				}
			else if ( definition_type == EVENT_DEF )
				method_type = "event";

			if ( method_type )
				fprintf(fp_zeek_init,
					"global %s: %s%s(",
					decl.zeek_name.c_str(), method_type, (yyvsp[-1].str));

			if ( definition_type == FUNC_DEF )
				{
				fprintf(fp_func_init,
					"\t(void) new zeek::detail::BuiltinFunc(zeek::%s_bif, \"%s\", 0);\n",
					decl.c_fullname.c_str(), decl.zeek_fullname.c_str());

				// This is the "canonical" version, with argument type and order
				// mostly for historical reasons.  There's also no "zeek_" prefix
				// in the function name itself, but does have a "_bif" suffix
				// to potentially help differentiate from other functions
				// (e.g. ones at global scope that may be used to implement
				// the BIF itself).
				fprintf(fp_func_h,
					"namespace zeek { %sextern zeek::detail::BifReturnVal %s_bif(zeek::detail::Frame* frame, const zeek::Args*);%s }\n",
					decl.c_namespace_start.c_str(), decl.bare_name.c_str(), decl.c_namespace_end.c_str());

				fprintf(fp_func_def,
					"zeek::detail::BifReturnVal zeek::%s_bif(zeek::detail::Frame* frame, const zeek::Args* %s)",
					decl.c_fullname.c_str(), arg_list_name);

				record_bif_item(decl.zeek_fullname.c_str(), "FUNCTION");
				}
			else if ( definition_type == EVENT_DEF )
				{
				if ( events.find(decl.zeek_fullname) == events.end() )
					{
					// TODO: add namespace for events here
					fprintf(fp_netvar_h,
						"%sextern zeek::EventHandlerPtr %s; %s\n",
						decl.c_namespace_start.c_str(), decl.bare_name.c_str(), decl.c_namespace_end.c_str());

					fprintf(fp_netvar_def,
					        "%szeek::EventHandlerPtr %s; %s\n",
					        decl.c_namespace_start.c_str(), decl.bare_name.c_str(), decl.c_namespace_end.c_str());

					fprintf(fp_netvar_init,
						"\t%s = zeek::event_registry->Register(\"%s\");\n",
						decl.c_fullname.c_str(), decl.zeek_fullname.c_str());

					record_bif_item(decl.zeek_fullname.c_str(), "EVENT");
					// C++ prototypes of zeek_event_* functions will
					// be generated later.
					}
				}
			}
#line 1899 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 40: /* arg_begin: TOK_LPP  */
#line 632 "builtin-func.y"
                        { args.clear(); var_arg = 0; }
#line 1905 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 43: /* args: opt_ws  */
#line 640 "builtin-func.y"
                        { /* empty, to avoid yacc complaint about type clash */ }
#line 1911 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 44: /* args_1: args_1 ',' opt_ws arg opt_ws opt_attr_list  */
#line 644 "builtin-func.y"
                        { if ( ! args.empty() ) args[args.size()-1]->SetAttrStr((yyvsp[0].str)); }
#line 1917 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 45: /* args_1: opt_ws arg opt_ws opt_attr_list  */
#line 646 "builtin-func.y"
                        { if ( ! args.empty() ) args[args.size()-1]->SetAttrStr((yyvsp[0].str)); }
#line 1923 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 46: /* type: TOK_OPAQUE opt_ws TOK_OF opt_ws TOK_ID  */
#line 654 "builtin-func.y"
                        { (yyval.str) = concat("opaque of ", (yyvsp[0].str)); }
#line 1929 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 47: /* type: TOK_ID  */
#line 656 "builtin-func.y"
                        { (yyval.str) = (yyvsp[0].str); }
#line 1935 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 48: /* arg: TOK_ID opt_ws ':' opt_ws type  */
#line 660 "builtin-func.y"
                        { args.push_back(new BuiltinFuncArg((yyvsp[-4].str), (yyvsp[0].str))); }
#line 1941 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 49: /* arg: TOK_VAR_ARG  */
#line 662 "builtin-func.y"
                        {
			if ( definition_type == EVENT_DEF )
				yyerror("events cannot have variable arguments");
			var_arg = 1;
			}
#line 1951 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 50: /* return_type: ':' opt_ws type opt_ws  */
#line 670 "builtin-func.y"
                        {
			BuiltinFuncArg* ret = new BuiltinFuncArg("", (yyvsp[-1].str));
			ret->PrintZeek(fp_zeek_init);
			delete ret;
			fprintf(fp_func_def, "%s", (yyvsp[0].str));
			}
#line 1962 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 51: /* body: body_start c_body body_end  */
#line 679 "builtin-func.y"
                        {
			fprintf(fp_func_def, " // end of %s\n", decl.c_fullname.c_str());
			print_line_directive(fp_func_def);
			}
#line 1971 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 52: /* c_code_begin: %empty  */
#line 686 "builtin-func.y"
                        {
			in_c_code = true;
			print_line_directive(fp_func_def);
			}
#line 1980 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 53: /* c_code_end: %empty  */
#line 693 "builtin-func.y"
                        { in_c_code = false; }
#line 1986 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 54: /* body_start: TOK_LPB c_code_begin  */
#line 697 "builtin-func.y"
                        {
			int implicit_arg = 0;
			int argc = args.size();

			fprintf(fp_func_def, "{");

			if ( argc > 0 || ! var_arg )
				fprintf(fp_func_def, "\n");

			if ( ! var_arg )
				{
				fprintf(fp_func_def, "\tif ( %s->size() != %d )\n", arg_list_name, argc);
				fprintf(fp_func_def, "\t\t{\n");
				fprintf(fp_func_def,
					"\t\tzeek::emit_builtin_error(zeek::util::fmt(\"%s() takes exactly %d argument(s), got %%lu\", %s->size()));\n",
					decl.zeek_fullname.c_str(), argc, arg_list_name);
				fprintf(fp_func_def, "\t\treturn nullptr;\n");
				fprintf(fp_func_def, "\t\t}\n");
				}
			else if ( argc > 0 )
				{
				fprintf(fp_func_def, "\tif ( %s->size() < %d )\n", arg_list_name, argc);
				fprintf(fp_func_def, "\t\t{\n");
				fprintf(fp_func_def,
					"\t\tzeek::emit_builtin_error(zeek::util::fmt(\"%s() takes at least %d argument(s), got %%lu\", %s->size()));\n",
					decl.zeek_fullname.c_str(), argc, arg_list_name);
				fprintf(fp_func_def, "\t\treturn nullptr;\n");
				fprintf(fp_func_def, "\t\t}\n");
				}

			for ( int i = 0; i < (int) args.size(); ++i )
				args[i]->PrintCDef(fp_func_def, i + implicit_arg, var_arg);
			print_line_directive(fp_func_def);
			}
#line 2025 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 55: /* body_end: TOK_RPB c_code_end  */
#line 734 "builtin-func.y"
                        {
			fprintf(fp_func_def, "}");
			}
#line 2033 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 57: /* c_body: opt_ws  */
#line 743 "builtin-func.y"
                        { fprintf(fp_func_def, "%s", (yyvsp[0].str)); }
#line 2039 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 58: /* c_body: c_body c_atom opt_ws  */
#line 745 "builtin-func.y"
                        { fprintf(fp_func_def, "%s", (yyvsp[0].str)); }
#line 2045 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 59: /* c_atom: TOK_ID  */
#line 749 "builtin-func.y"
                        { fprintf(fp_func_def, "%s", (yyvsp[0].str)); }
#line 2051 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 60: /* c_atom: TOK_C_TOKEN  */
#line 751 "builtin-func.y"
                        { fprintf(fp_func_def, "%s", (yyvsp[0].str)); }
#line 2057 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 61: /* c_atom: TOK_ARG  */
#line 753 "builtin-func.y"
                        { fprintf(fp_func_def, "(*%s)", arg_list_name); }
#line 2063 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 62: /* c_atom: TOK_ARGS  */
#line 755 "builtin-func.y"
                        { fprintf(fp_func_def, "%s", arg_list_name); }
#line 2069 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 63: /* c_atom: TOK_ARGC  */
#line 757 "builtin-func.y"
                        { fprintf(fp_func_def, "%s->size()", arg_list_name); }
#line 2075 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 64: /* c_atom: TOK_CSTR  */
#line 759 "builtin-func.y"
                        { fprintf(fp_func_def, "%s", (yyvsp[0].str)); }
#line 2081 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 65: /* c_atom: TOK_ATOM  */
#line 761 "builtin-func.y"
                        { fprintf(fp_func_def, "%c", (yyvsp[0].val)); }
#line 2087 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 66: /* c_atom: TOK_INT  */
#line 763 "builtin-func.y"
                        { fprintf(fp_func_def, "%s", (yyvsp[0].str)); }
#line 2093 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 67: /* opt_ws: opt_ws TOK_WS  */
#line 768 "builtin-func.y"
                        { (yyval.str) = concat((yyvsp[-1].str), (yyvsp[0].str)); }
#line 2099 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 68: /* opt_ws: opt_ws TOK_LF  */
#line 770 "builtin-func.y"
                        { (yyval.str) = concat((yyvsp[-1].str), "\n"); }
#line 2105 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 69: /* opt_ws: opt_ws TOK_COMMENT  */
#line 772 "builtin-func.y"
                        {
			if ( in_c_code )
				(yyval.str) = concat((yyvsp[-1].str), (yyvsp[0].str));
			else
				if ( (yyvsp[0].str)[1] == '#' )
					// This is a special type of comment that is used to
					// generate zeek script documentation, so pass it through.
					(yyval.str) = concat((yyvsp[-1].str), (yyvsp[0].str));
				else
					(yyval.str) = (yyvsp[-1].str);
			}
#line 2121 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;

  case 70: /* opt_ws: %empty  */
#line 784 "builtin-func.y"
                        { (yyval.str) = ""; }
#line 2127 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"
    break;


#line 2131 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.cc"

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

#line 787 "builtin-func.y"


extern char* yytext;
extern char* input_filename;
extern int line_number;
void err_exit(void);

void print_msg(const char msg[])
	{
	int msg_len = strlen(msg) + strlen(yytext) + 64;
	char* msgbuf = new char[msg_len];

	if ( yytext[0] == '\n' )
		snprintf(msgbuf, msg_len, "%s, on previous line", msg);

	else if ( yytext[0] == '\0' )
		snprintf(msgbuf, msg_len, "%s, at end of file", msg);

	else
		snprintf(msgbuf, msg_len, "%s, at or near \"%s\"", msg, yytext);

	/*
	extern int column;
	sprintf(msgbuf, "%*s\n%*s\n", column, "^", column, msg);
	*/

	if ( input_filename )
		fprintf(stderr, "%s:%d: ", input_filename, line_number);
	else
		fprintf(stderr, "line %d: ", line_number);
	fprintf(stderr, "%s\n", msgbuf);

	delete [] msgbuf;
	}

int yywarn(const char msg[])
	{
	print_msg(msg);
	return 0;
	}

int yyerror(const char msg[])
	{
	print_msg(msg);

	err_exit();
	return 0;
	}
