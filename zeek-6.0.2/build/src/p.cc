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
#line 1 "parse.y"

// See the file "COPYING" in the main distribution directory for copyright.
#line 82 "parse.y"

#include <cstdlib>
#include <cstring>
#include <cassert>

#include <set>
#include <string>

#include "zeek/input.h"
#include "zeek/ZeekList.h"
#include "zeek/Desc.h"
#include "zeek/Expr.h"
#include "zeek/Func.h"
#include "zeek/Stmt.h"
#include "zeek/Val.h"
#include "zeek/Var.h"
#include "zeek/RE.h"
#include "zeek/Scope.h"
#include "zeek/Reporter.h"
#include "zeek/ScriptCoverageManager.h"
#include "zeek/ScriptValidation.h"
#include "zeek/zeekygen/Manager.h"
#include "zeek/module_util.h"
#include "zeek/IntrusivePtr.h"

extern const char* filename;  // Absolute path of file currently being parsed.
extern const char* last_filename; // Absolute path of last file parsed.
extern const char* last_tok_filename;
extern const char* last_last_tok_filename;

extern int conditional_epoch; // let's us track embedded conditionals

// Whether the file we're currently parsing includes @if conditionals.
extern bool current_file_has_conditionals;

extern YYLTYPE GetCurrentLocation();
extern int yyerror(const char[]);
extern int zeeklex();

#define YYLLOC_DEFAULT(Current, Rhs, N) \
	(Current) = (Rhs)[(N)];

using namespace zeek;
using namespace zeek::detail;

// Part of the module facility: while parsing, keep track of which
// module to put things in.
std::string zeek::detail::current_module = GLOBAL_MODULE_NAME;

bool is_export = false; // true if in an export {} block

// When parsing an expression for the debugger, where to put the result
// (obviously not reentrant).
extern Expr* g_curr_debug_expr;
extern bool in_debug;
extern const char* g_curr_debug_error;

extern int in_when_cond;

static int in_hook = 0;
int in_init = 0;
int in_record = 0;
static int in_record_redef = 0;
static int in_enum_redef = 0;
bool resolving_global_ID = false;
bool defining_global_ID = false;
std::vector<int> saved_in_init;
static int expr_list_has_opt_comma = 0;

std::vector<std::set<const ID*>> locals_at_this_scope;
static std::unordered_set<const ID*> out_of_scope_locals;

static Location func_hdr_location;
static int func_hdr_cond_epoch = 0;
EnumType* cur_enum_type = nullptr;
static ID* cur_decl_type_id = nullptr;

std::set<std::string> module_names;

static void parse_new_enum(void)
	{
	// Starting a new enum definition.
	assert(cur_enum_type == nullptr);

	if ( cur_decl_type_id )
		{
		auto name = make_full_var_name(current_module.c_str(), cur_decl_type_id->Name());
		cur_enum_type = new EnumType(name);
		}
	else
		reporter->FatalError("incorrect syntax for enum type declaration");
	}

static void parse_redef_enum(ID* id)
	{
	// Redef an enum. id points to the enum to be redefined.
	// Let cur_enum_type point to it.
	assert(cur_enum_type == nullptr);

	// abort on errors; enums need to be accessible to continue parsing
	if ( ! id->GetType() )
		reporter->FatalError("unknown enum identifier \"%s\"", id->Name());
	else
		{
		if ( ! id->GetType() || id->GetType()->Tag() != TYPE_ENUM )
			reporter->FatalError("identifier \"%s\" is not an enum", id->Name());
		cur_enum_type = id->GetType()->AsEnumType();
		}
	}

static void parse_redef_record_field(ID* id, const char* field, InitClass ic,
                                     std::unique_ptr<std::vector<AttrPtr>> attrs)
	{
	if ( ! id->GetType() )
		{
		reporter->FatalError("unknown record identifier \"%s\"", id->Name());
		return;
		}

	auto t = id->GetType();
	if ( ! t || t->Tag() != TYPE_RECORD )
		{
		reporter->FatalError("identifier \"%s\" has type \"%s\", expected \"record\"",
		                     id->Name(), type_name(t->Tag()));
		return;
		}

	auto rt = t->AsRecordType();
	auto idx = rt->FieldOffset(field);
	if ( idx < 0 )
		{
		reporter->FatalError("field \"%s\" not in record \"%s\"", field, id->Name());
		return;
		}

	auto decl = rt->FieldDecl(idx);
	if ( ! decl->attrs )
		if ( ic == INIT_EXTRA )
			decl->attrs = make_intrusive<detail::Attributes>(decl->type,
			                                                 true /* in_record */,
			                                                 false /* is_global */);

	for ( const auto& attr : *attrs )
		{
		// At this point, only support &log redef'ing.
		if ( attr->Tag() != ATTR_LOG )
			{
				reporter->FatalError("Can only redef \"&log\" attributes of record fields");
				return;
			}

		if ( ic == INIT_EXTRA )
			decl->attrs->AddAttr(attr, true /* is_redef */);
		else
			// Removing attributes is a noop if they don't exist.
			if ( decl->attrs )
				decl->attrs->RemoveAttr(attr->Tag());
		}
	}

static void extend_record(ID* id, std::unique_ptr<type_decl_list> fields,
                          std::unique_ptr<std::vector<AttrPtr>> attrs)
	{
	const auto& types = Type::Aliases(id->Name());

	if ( types.empty() )
		{
		id->Error("failed to redef record: no types found in alias map");
		return;
		}

	bool add_log_attr = false;

	if ( attrs )
		for ( const auto& at : *attrs )
			if ( at->Tag() == ATTR_LOG )
				{
				add_log_attr = true;
				break;
				}

	for ( const auto& t : types )
		{
		auto error = t->AsRecordType()->AddFields(*fields, add_log_attr);

		if ( error )
			{
			id->Error(error);
			break;
			}
		}
	}

static AttributesPtr
make_attributes(std::vector<AttrPtr>* attrs,
                TypePtr t, bool in_record, bool is_global)
	{
	if ( ! attrs )
		return nullptr;

	auto rval = make_intrusive<Attributes>(std::move(*attrs), std::move(t),
	                                       in_record, is_global);
	delete attrs;
	return rval;
	}

static bool expr_is_table_type_name(const Expr* expr)
	{
	if ( expr->Tag() != EXPR_NAME )
		return false;

	const auto& type = expr->GetType();

	if ( type->IsTable() )
		return true;

	if ( type->Tag() == TYPE_TYPE )
		return type->AsTypeType()->GetType()->IsTable();

	return false;
	}

static void check_loop_var(const IDPtr& var)
	{
	if ( var->IsGlobal() )
 		var->Error("global variable used in 'for' loop");

 	if ( var->IsConst() )
 		var->Error("constant used in 'for' loop");
	}

static void build_global(ID* id, Type* t, InitClass ic, Expr* e,
                         std::vector<AttrPtr>* attrs, DeclType dt)
	{
	IDPtr id_ptr{AdoptRef{}, id};
	TypePtr t_ptr{AdoptRef{}, t};
	ExprPtr e_ptr{AdoptRef{}, e};

	auto attrs_ptr = attrs ? std::make_unique<std::vector<AttrPtr>>(*attrs) : nullptr;

	add_global(id_ptr, std::move(t_ptr), ic, e_ptr, std::move(attrs_ptr), dt);

	if ( dt == VAR_REDEF )
		zeekygen_mgr->Redef(id, ::filename, ic, std::move(e_ptr));
	else
		zeekygen_mgr->Identifier(std::move(id_ptr));
	}

static StmtPtr build_local(ID* id, Type* t, InitClass ic, Expr* e,
                           std::vector<AttrPtr>* attrs, DeclType dt,
                           bool do_coverage)
	{
	IDPtr id_ptr{AdoptRef{}, id};
	TypePtr t_ptr{AdoptRef{}, t};
	ExprPtr e_ptr{AdoptRef{}, e};

	auto attrs_ptr = attrs ? std::make_unique<std::vector<AttrPtr>>(*attrs) : nullptr;

	auto init = add_local(std::move(id_ptr), std::move(t_ptr), ic,
	                      e_ptr, std::move(attrs_ptr), dt);

	if ( do_coverage )
		script_coverage_mgr.AddStmt(init.get());

	return init;
	}

#line 342 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"

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

#include "zeekparse.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_ADD = 3,                    /* TOK_ADD  */
  YYSYMBOL_TOK_ADD_TO = 4,                 /* TOK_ADD_TO  */
  YYSYMBOL_TOK_ADDR = 5,                   /* TOK_ADDR  */
  YYSYMBOL_TOK_ANY = 6,                    /* TOK_ANY  */
  YYSYMBOL_TOK_ATENDIF = 7,                /* TOK_ATENDIF  */
  YYSYMBOL_TOK_ATELSE = 8,                 /* TOK_ATELSE  */
  YYSYMBOL_TOK_ATIF = 9,                   /* TOK_ATIF  */
  YYSYMBOL_TOK_ATIFDEF = 10,               /* TOK_ATIFDEF  */
  YYSYMBOL_TOK_ATIFNDEF = 11,              /* TOK_ATIFNDEF  */
  YYSYMBOL_TOK_BOOL = 12,                  /* TOK_BOOL  */
  YYSYMBOL_TOK_BREAK = 13,                 /* TOK_BREAK  */
  YYSYMBOL_TOK_CASE = 14,                  /* TOK_CASE  */
  YYSYMBOL_TOK_OPTION = 15,                /* TOK_OPTION  */
  YYSYMBOL_TOK_CONST = 16,                 /* TOK_CONST  */
  YYSYMBOL_TOK_CONSTANT = 17,              /* TOK_CONSTANT  */
  YYSYMBOL_TOK_COPY = 18,                  /* TOK_COPY  */
  YYSYMBOL_TOK_COUNT = 19,                 /* TOK_COUNT  */
  YYSYMBOL_TOK_DEFAULT = 20,               /* TOK_DEFAULT  */
  YYSYMBOL_TOK_DELETE = 21,                /* TOK_DELETE  */
  YYSYMBOL_TOK_DOUBLE = 22,                /* TOK_DOUBLE  */
  YYSYMBOL_TOK_ELSE = 23,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_ENUM = 24,                  /* TOK_ENUM  */
  YYSYMBOL_TOK_EVENT = 25,                 /* TOK_EVENT  */
  YYSYMBOL_TOK_EXPORT = 26,                /* TOK_EXPORT  */
  YYSYMBOL_TOK_FALLTHROUGH = 27,           /* TOK_FALLTHROUGH  */
  YYSYMBOL_TOK_FILE = 28,                  /* TOK_FILE  */
  YYSYMBOL_TOK_FOR = 29,                   /* TOK_FOR  */
  YYSYMBOL_TOK_FUNCTION = 30,              /* TOK_FUNCTION  */
  YYSYMBOL_TOK_GLOBAL = 31,                /* TOK_GLOBAL  */
  YYSYMBOL_TOK_HOOK = 32,                  /* TOK_HOOK  */
  YYSYMBOL_TOK_ID = 33,                    /* TOK_ID  */
  YYSYMBOL_TOK_IF = 34,                    /* TOK_IF  */
  YYSYMBOL_TOK_INT = 35,                   /* TOK_INT  */
  YYSYMBOL_TOK_INTERVAL = 36,              /* TOK_INTERVAL  */
  YYSYMBOL_TOK_LIST = 37,                  /* TOK_LIST  */
  YYSYMBOL_TOK_MODULE = 38,                /* TOK_MODULE  */
  YYSYMBOL_TOK_LOCAL = 39,                 /* TOK_LOCAL  */
  YYSYMBOL_TOK_WHEN_LOCAL = 40,            /* TOK_WHEN_LOCAL  */
  YYSYMBOL_TOK_NEXT = 41,                  /* TOK_NEXT  */
  YYSYMBOL_TOK_OF = 42,                    /* TOK_OF  */
  YYSYMBOL_TOK_OPAQUE = 43,                /* TOK_OPAQUE  */
  YYSYMBOL_TOK_PATTERN = 44,               /* TOK_PATTERN  */
  YYSYMBOL_TOK_PATTERN_END = 45,           /* TOK_PATTERN_END  */
  YYSYMBOL_TOK_PATTERN_TEXT = 46,          /* TOK_PATTERN_TEXT  */
  YYSYMBOL_TOK_PORT = 47,                  /* TOK_PORT  */
  YYSYMBOL_TOK_PRINT = 48,                 /* TOK_PRINT  */
  YYSYMBOL_TOK_RECORD = 49,                /* TOK_RECORD  */
  YYSYMBOL_TOK_REDEF = 50,                 /* TOK_REDEF  */
  YYSYMBOL_TOK_REMOVE_FROM = 51,           /* TOK_REMOVE_FROM  */
  YYSYMBOL_TOK_RETURN = 52,                /* TOK_RETURN  */
  YYSYMBOL_TOK_SCHEDULE = 53,              /* TOK_SCHEDULE  */
  YYSYMBOL_TOK_SET = 54,                   /* TOK_SET  */
  YYSYMBOL_TOK_STRING = 55,                /* TOK_STRING  */
  YYSYMBOL_TOK_SUBNET = 56,                /* TOK_SUBNET  */
  YYSYMBOL_TOK_SWITCH = 57,                /* TOK_SWITCH  */
  YYSYMBOL_TOK_TABLE = 58,                 /* TOK_TABLE  */
  YYSYMBOL_TOK_TIME = 59,                  /* TOK_TIME  */
  YYSYMBOL_TOK_TIMEOUT = 60,               /* TOK_TIMEOUT  */
  YYSYMBOL_TOK_TYPE = 61,                  /* TOK_TYPE  */
  YYSYMBOL_TOK_VECTOR = 62,                /* TOK_VECTOR  */
  YYSYMBOL_TOK_WHEN = 63,                  /* TOK_WHEN  */
  YYSYMBOL_TOK_WHILE = 64,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_AS = 65,                    /* TOK_AS  */
  YYSYMBOL_TOK_IS = 66,                    /* TOK_IS  */
  YYSYMBOL_TOK_ATTR_ADD_FUNC = 67,         /* TOK_ATTR_ADD_FUNC  */
  YYSYMBOL_TOK_ATTR_DEFAULT = 68,          /* TOK_ATTR_DEFAULT  */
  YYSYMBOL_TOK_ATTR_OPTIONAL = 69,         /* TOK_ATTR_OPTIONAL  */
  YYSYMBOL_TOK_ATTR_REDEF = 70,            /* TOK_ATTR_REDEF  */
  YYSYMBOL_TOK_ATTR_DEL_FUNC = 71,         /* TOK_ATTR_DEL_FUNC  */
  YYSYMBOL_TOK_ATTR_EXPIRE_FUNC = 72,      /* TOK_ATTR_EXPIRE_FUNC  */
  YYSYMBOL_TOK_ATTR_EXPIRE_CREATE = 73,    /* TOK_ATTR_EXPIRE_CREATE  */
  YYSYMBOL_TOK_ATTR_EXPIRE_READ = 74,      /* TOK_ATTR_EXPIRE_READ  */
  YYSYMBOL_TOK_ATTR_EXPIRE_WRITE = 75,     /* TOK_ATTR_EXPIRE_WRITE  */
  YYSYMBOL_TOK_ATTR_RAW_OUTPUT = 76,       /* TOK_ATTR_RAW_OUTPUT  */
  YYSYMBOL_TOK_ATTR_ON_CHANGE = 77,        /* TOK_ATTR_ON_CHANGE  */
  YYSYMBOL_TOK_ATTR_BROKER_STORE = 78,     /* TOK_ATTR_BROKER_STORE  */
  YYSYMBOL_TOK_ATTR_BROKER_STORE_ALLOW_COMPLEX = 79, /* TOK_ATTR_BROKER_STORE_ALLOW_COMPLEX  */
  YYSYMBOL_TOK_ATTR_BACKEND = 80,          /* TOK_ATTR_BACKEND  */
  YYSYMBOL_TOK_ATTR_PRIORITY = 81,         /* TOK_ATTR_PRIORITY  */
  YYSYMBOL_TOK_ATTR_LOG = 82,              /* TOK_ATTR_LOG  */
  YYSYMBOL_TOK_ATTR_ERROR_HANDLER = 83,    /* TOK_ATTR_ERROR_HANDLER  */
  YYSYMBOL_TOK_ATTR_GROUP = 84,            /* TOK_ATTR_GROUP  */
  YYSYMBOL_TOK_ATTR_TYPE_COLUMN = 85,      /* TOK_ATTR_TYPE_COLUMN  */
  YYSYMBOL_TOK_ATTR_DEPRECATED = 86,       /* TOK_ATTR_DEPRECATED  */
  YYSYMBOL_TOK_ATTR_IS_ASSIGNED = 87,      /* TOK_ATTR_IS_ASSIGNED  */
  YYSYMBOL_TOK_ATTR_IS_USED = 88,          /* TOK_ATTR_IS_USED  */
  YYSYMBOL_TOK_ATTR_ORDERED = 89,          /* TOK_ATTR_ORDERED  */
  YYSYMBOL_TOK_DEBUG = 90,                 /* TOK_DEBUG  */
  YYSYMBOL_TOK_NO_TEST = 91,               /* TOK_NO_TEST  */
  YYSYMBOL_92_ = 92,                       /* ','  */
  YYSYMBOL_93_ = 93,                       /* '='  */
  YYSYMBOL_94_ = 94,                       /* '?'  */
  YYSYMBOL_95_ = 95,                       /* ':'  */
  YYSYMBOL_TOK_OR_OR = 96,                 /* TOK_OR_OR  */
  YYSYMBOL_TOK_AND_AND = 97,               /* TOK_AND_AND  */
  YYSYMBOL_98_ = 98,                       /* '<'  */
  YYSYMBOL_99_ = 99,                       /* '>'  */
  YYSYMBOL_TOK_LE = 100,                   /* TOK_LE  */
  YYSYMBOL_TOK_GE = 101,                   /* TOK_GE  */
  YYSYMBOL_TOK_EQ = 102,                   /* TOK_EQ  */
  YYSYMBOL_TOK_NE = 103,                   /* TOK_NE  */
  YYSYMBOL_TOK_IN = 104,                   /* TOK_IN  */
  YYSYMBOL_TOK_NOT_IN = 105,               /* TOK_NOT_IN  */
  YYSYMBOL_106_ = 106,                     /* '|'  */
  YYSYMBOL_107_ = 107,                     /* '^'  */
  YYSYMBOL_108_ = 108,                     /* '&'  */
  YYSYMBOL_TOK_LSHIFT = 109,               /* TOK_LSHIFT  */
  YYSYMBOL_TOK_RSHIFT = 110,               /* TOK_RSHIFT  */
  YYSYMBOL_111_ = 111,                     /* '+'  */
  YYSYMBOL_112_ = 112,                     /* '-'  */
  YYSYMBOL_113_ = 113,                     /* '*'  */
  YYSYMBOL_114_ = 114,                     /* '/'  */
  YYSYMBOL_115_ = 115,                     /* '%'  */
  YYSYMBOL_TOK_INCR = 116,                 /* TOK_INCR  */
  YYSYMBOL_TOK_DECR = 117,                 /* TOK_DECR  */
  YYSYMBOL_118_ = 118,                     /* '!'  */
  YYSYMBOL_119_ = 119,                     /* '~'  */
  YYSYMBOL_120_ = 120,                     /* '$'  */
  YYSYMBOL_121_ = 121,                     /* '['  */
  YYSYMBOL_122_ = 122,                     /* ']'  */
  YYSYMBOL_123_ = 123,                     /* '('  */
  YYSYMBOL_124_ = 124,                     /* ')'  */
  YYSYMBOL_TOK_HAS_FIELD = 125,            /* TOK_HAS_FIELD  */
  YYSYMBOL_TOK_HAS_ATTR = 126,             /* TOK_HAS_ATTR  */
  YYSYMBOL_127_ = 127,                     /* '{'  */
  YYSYMBOL_128_ = 128,                     /* '}'  */
  YYSYMBOL_129_ = 129,                     /* ';'  */
  YYSYMBOL_YYACCEPT = 130,                 /* $accept  */
  YYSYMBOL_zeek = 131,                     /* zeek  */
  YYSYMBOL_132_1 = 132,                    /* $@1  */
  YYSYMBOL_133_2 = 133,                    /* $@2  */
  YYSYMBOL_decl_list = 134,                /* decl_list  */
  YYSYMBOL_opt_expr = 135,                 /* opt_expr  */
  YYSYMBOL_when_clause = 136,              /* when_clause  */
  YYSYMBOL_when_head = 137,                /* when_head  */
  YYSYMBOL_when_start = 138,               /* when_start  */
  YYSYMBOL_when_flavor = 139,              /* when_flavor  */
  YYSYMBOL_when_captures = 140,            /* when_captures  */
  YYSYMBOL_when_condition = 141,           /* when_condition  */
  YYSYMBOL_142_3 = 142,                    /* $@3  */
  YYSYMBOL_143_4 = 143,                    /* $@4  */
  YYSYMBOL_expr = 144,                     /* expr  */
  YYSYMBOL_145_5 = 145,                    /* $@5  */
  YYSYMBOL_146_6 = 146,                    /* $@6  */
  YYSYMBOL_147_7 = 147,                    /* $@7  */
  YYSYMBOL_148_8 = 148,                    /* $@8  */
  YYSYMBOL_149_9 = 149,                    /* $@9  */
  YYSYMBOL_150_10 = 150,                   /* $@10  */
  YYSYMBOL_151_11 = 151,                   /* $@11  */
  YYSYMBOL_152_12 = 152,                   /* $@12  */
  YYSYMBOL_rhs = 153,                      /* rhs  */
  YYSYMBOL_154_13 = 154,                   /* $@13  */
  YYSYMBOL_rhs_expr_list = 155,            /* rhs_expr_list  */
  YYSYMBOL_expr_list = 156,                /* expr_list  */
  YYSYMBOL_opt_expr_list = 157,            /* opt_expr_list  */
  YYSYMBOL_enum_body = 158,                /* enum_body  */
  YYSYMBOL_enum_body_list = 159,           /* enum_body_list  */
  YYSYMBOL_enum_body_elem = 160,           /* enum_body_elem  */
  YYSYMBOL_type = 161,                     /* type  */
  YYSYMBOL_162_14 = 162,                   /* $@14  */
  YYSYMBOL_163_15 = 163,                   /* $@15  */
  YYSYMBOL_164_16 = 164,                   /* $@16  */
  YYSYMBOL_type_list = 165,                /* type_list  */
  YYSYMBOL_type_decl_list = 166,           /* type_decl_list  */
  YYSYMBOL_type_decl = 167,                /* type_decl  */
  YYSYMBOL_formal_args = 168,              /* formal_args  */
  YYSYMBOL_formal_args_decl_list = 169,    /* formal_args_decl_list  */
  YYSYMBOL_formal_args_decl = 170,         /* formal_args_decl  */
  YYSYMBOL_decl = 171,                     /* decl  */
  YYSYMBOL_172_17 = 172,                   /* $@17  */
  YYSYMBOL_173_18 = 173,                   /* $@18  */
  YYSYMBOL_174_19 = 174,                   /* $@19  */
  YYSYMBOL_175_20 = 175,                   /* $@20  */
  YYSYMBOL_176_21 = 176,                   /* $@21  */
  YYSYMBOL_177_22 = 177,                   /* $@22  */
  YYSYMBOL_178_23 = 178,                   /* $@23  */
  YYSYMBOL_179_24 = 179,                   /* $@24  */
  YYSYMBOL_180_25 = 180,                   /* $@25  */
  YYSYMBOL_181_26 = 181,                   /* $@26  */
  YYSYMBOL_conditional_list = 182,         /* conditional_list  */
  YYSYMBOL_conditional = 183,              /* conditional  */
  YYSYMBOL_func_hdr = 184,                 /* func_hdr  */
  YYSYMBOL_func_body = 185,                /* func_body  */
  YYSYMBOL_186_27 = 186,                   /* $@27  */
  YYSYMBOL_187_28 = 187,                   /* $@28  */
  YYSYMBOL_lambda_body = 188,              /* lambda_body  */
  YYSYMBOL_189_29 = 189,                   /* $@29  */
  YYSYMBOL_190_30 = 190,                   /* $@30  */
  YYSYMBOL_anonymous_function = 191,       /* anonymous_function  */
  YYSYMBOL_begin_lambda = 192,             /* begin_lambda  */
  YYSYMBOL_opt_captures = 193,             /* opt_captures  */
  YYSYMBOL_capture_list = 194,             /* capture_list  */
  YYSYMBOL_capture = 195,                  /* capture  */
  YYSYMBOL_opt_deep = 196,                 /* opt_deep  */
  YYSYMBOL_func_params = 197,              /* func_params  */
  YYSYMBOL_opt_type = 198,                 /* opt_type  */
  YYSYMBOL_init_class = 199,               /* init_class  */
  YYSYMBOL_opt_init = 200,                 /* opt_init  */
  YYSYMBOL_201_31 = 201,                   /* $@31  */
  YYSYMBOL_202_32 = 202,                   /* $@32  */
  YYSYMBOL_index_slice = 203,              /* index_slice  */
  YYSYMBOL_opt_attr = 204,                 /* opt_attr  */
  YYSYMBOL_attr_list = 205,                /* attr_list  */
  YYSYMBOL_attr = 206,                     /* attr  */
  YYSYMBOL_stmt = 207,                     /* stmt  */
  YYSYMBOL_208_33 = 208,                   /* $@33  */
  YYSYMBOL_stmt_list = 209,                /* stmt_list  */
  YYSYMBOL_event = 210,                    /* event  */
  YYSYMBOL_case_list = 211,                /* case_list  */
  YYSYMBOL_case = 212,                     /* case  */
  YYSYMBOL_case_type_list = 213,           /* case_type_list  */
  YYSYMBOL_case_type = 214,                /* case_type  */
  YYSYMBOL_for_head = 215,                 /* for_head  */
  YYSYMBOL_local_id_list = 216,            /* local_id_list  */
  YYSYMBOL_local_id = 217,                 /* local_id  */
  YYSYMBOL_global_id = 218,                /* global_id  */
  YYSYMBOL_219_34 = 219,                   /* $@34  */
  YYSYMBOL_def_global_id = 220,            /* def_global_id  */
  YYSYMBOL_221_35 = 221,                   /* $@35  */
  YYSYMBOL_222_36 = 222,                   /* $@36  */
  YYSYMBOL_event_id = 223,                 /* event_id  */
  YYSYMBOL_224_37 = 224,                   /* $@37  */
  YYSYMBOL_global_or_event_id = 225,       /* global_or_event_id  */
  YYSYMBOL_resolve_id = 226,               /* resolve_id  */
  YYSYMBOL_opt_no_test = 227,              /* opt_no_test  */
  YYSYMBOL_opt_no_test_block = 228,        /* opt_no_test_block  */
  YYSYMBOL_opt_deprecated = 229,           /* opt_deprecated  */
  YYSYMBOL_expr_list_opt_comma = 230       /* expr_list_opt_comma  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3254

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  130
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  290
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  771

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   360


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   118,     2,     2,   120,   115,   108,     2,
     123,   124,   113,   111,    92,   112,     2,   114,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    95,   129,
      98,    93,    99,    94,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   121,     2,   122,   107,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   127,   106,   128,   119,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    96,    97,   100,
     101,   102,   103,   104,   105,   109,   110,   116,   117,   125,
     126
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   387,   387,   386,   416,   416,   423,   424,   428,   431,
     435,   443,   447,   455,   461,   469,   472,   477,   479,   483,
     483,   483,   488,   494,   500,   506,   512,   518,   524,   560,
     566,   572,   593,   599,   620,   626,   632,   638,   644,   650,
     656,   662,   668,   674,   680,   686,   692,   698,   704,   710,
     716,   723,   722,   743,   752,   761,   763,   769,   776,   775,
     785,   791,   799,   825,   831,   831,   831,   839,   846,   853,
     859,   852,   902,   902,   915,   921,   923,   929,   994,  1000,
    1000,  1017,  1024,  1030,  1037,  1037,  1042,  1045,  1047,  1051,
    1057,  1066,  1068,  1072,  1078,  1086,  1088,  1097,  1110,  1118,
    1128,  1133,  1138,  1143,  1148,  1153,  1158,  1163,  1168,  1173,
    1178,  1183,  1188,  1194,  1201,  1203,  1200,  1210,  1210,  1217,
    1225,  1233,  1239,  1245,  1251,  1257,  1263,  1269,  1275,  1295,
    1297,  1305,  1310,  1316,  1329,  1331,  1334,  1338,  1340,  1342,
    1347,  1356,  1363,  1363,  1366,  1371,  1379,  1384,  1384,  1403,
    1402,  1411,  1410,  1418,  1417,  1425,  1427,  1429,  1424,  1442,
    1441,  1453,  1452,  1459,  1462,  1463,  1467,  1469,  1471,  1473,
    1475,  1480,  1489,  1496,  1505,  1516,  1525,  1515,  1545,  1551,
    1544,  1577,  1582,  1601,  1604,  1608,  1613,  1622,  1648,  1651,
    1655,  1657,  1662,  1665,  1669,  1670,  1671,  1672,  1676,  1676,
    1676,  1679,  1683,  1707,  1709,  1713,  1715,  1723,  1725,  1727,
    1729,  1731,  1733,  1735,  1737,  1739,  1741,  1743,  1745,  1747,
    1749,  1751,  1753,  1755,  1757,  1759,  1761,  1763,  1765,  1767,
    1783,  1789,  1788,  1805,  1813,  1821,  1829,  1838,  1845,  1852,
    1859,  1867,  1875,  1883,  1891,  1899,  1907,  1915,  1923,  1930,
    1936,  1946,  1954,  1961,  1966,  1973,  1977,  2003,  2006,  2010,
    2013,  2016,  2021,  2024,  2032,  2038,  2055,  2079,  2084,  2111,
    2129,  2131,  2139,  2165,  2165,  2170,  2170,  2170,  2175,  2175,
    2180,  2218,  2232,  2235,  2239,  2242,  2246,  2249,  2263,  2266,
    2267
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_ADD",
  "TOK_ADD_TO", "TOK_ADDR", "TOK_ANY", "TOK_ATENDIF", "TOK_ATELSE",
  "TOK_ATIF", "TOK_ATIFDEF", "TOK_ATIFNDEF", "TOK_BOOL", "TOK_BREAK",
  "TOK_CASE", "TOK_OPTION", "TOK_CONST", "TOK_CONSTANT", "TOK_COPY",
  "TOK_COUNT", "TOK_DEFAULT", "TOK_DELETE", "TOK_DOUBLE", "TOK_ELSE",
  "TOK_ENUM", "TOK_EVENT", "TOK_EXPORT", "TOK_FALLTHROUGH", "TOK_FILE",
  "TOK_FOR", "TOK_FUNCTION", "TOK_GLOBAL", "TOK_HOOK", "TOK_ID", "TOK_IF",
  "TOK_INT", "TOK_INTERVAL", "TOK_LIST", "TOK_MODULE", "TOK_LOCAL",
  "TOK_WHEN_LOCAL", "TOK_NEXT", "TOK_OF", "TOK_OPAQUE", "TOK_PATTERN",
  "TOK_PATTERN_END", "TOK_PATTERN_TEXT", "TOK_PORT", "TOK_PRINT",
  "TOK_RECORD", "TOK_REDEF", "TOK_REMOVE_FROM", "TOK_RETURN",
  "TOK_SCHEDULE", "TOK_SET", "TOK_STRING", "TOK_SUBNET", "TOK_SWITCH",
  "TOK_TABLE", "TOK_TIME", "TOK_TIMEOUT", "TOK_TYPE", "TOK_VECTOR",
  "TOK_WHEN", "TOK_WHILE", "TOK_AS", "TOK_IS", "TOK_ATTR_ADD_FUNC",
  "TOK_ATTR_DEFAULT", "TOK_ATTR_OPTIONAL", "TOK_ATTR_REDEF",
  "TOK_ATTR_DEL_FUNC", "TOK_ATTR_EXPIRE_FUNC", "TOK_ATTR_EXPIRE_CREATE",
  "TOK_ATTR_EXPIRE_READ", "TOK_ATTR_EXPIRE_WRITE", "TOK_ATTR_RAW_OUTPUT",
  "TOK_ATTR_ON_CHANGE", "TOK_ATTR_BROKER_STORE",
  "TOK_ATTR_BROKER_STORE_ALLOW_COMPLEX", "TOK_ATTR_BACKEND",
  "TOK_ATTR_PRIORITY", "TOK_ATTR_LOG", "TOK_ATTR_ERROR_HANDLER",
  "TOK_ATTR_GROUP", "TOK_ATTR_TYPE_COLUMN", "TOK_ATTR_DEPRECATED",
  "TOK_ATTR_IS_ASSIGNED", "TOK_ATTR_IS_USED", "TOK_ATTR_ORDERED",
  "TOK_DEBUG", "TOK_NO_TEST", "','", "'='", "'?'", "':'", "TOK_OR_OR",
  "TOK_AND_AND", "'<'", "'>'", "TOK_LE", "TOK_GE", "TOK_EQ", "TOK_NE",
  "TOK_IN", "TOK_NOT_IN", "'|'", "'^'", "'&'", "TOK_LSHIFT", "TOK_RSHIFT",
  "'+'", "'-'", "'*'", "'/'", "'%'", "TOK_INCR", "TOK_DECR", "'!'", "'~'",
  "'$'", "'['", "']'", "'('", "')'", "TOK_HAS_FIELD", "TOK_HAS_ATTR",
  "'{'", "'}'", "';'", "$accept", "zeek", "$@1", "$@2", "decl_list",
  "opt_expr", "when_clause", "when_head", "when_start", "when_flavor",
  "when_captures", "when_condition", "$@3", "$@4", "expr", "$@5", "$@6",
  "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "rhs", "$@13",
  "rhs_expr_list", "expr_list", "opt_expr_list", "enum_body",
  "enum_body_list", "enum_body_elem", "type", "$@14", "$@15", "$@16",
  "type_list", "type_decl_list", "type_decl", "formal_args",
  "formal_args_decl_list", "formal_args_decl", "decl", "$@17", "$@18",
  "$@19", "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "$@26",
  "conditional_list", "conditional", "func_hdr", "func_body", "$@27",
  "$@28", "lambda_body", "$@29", "$@30", "anonymous_function",
  "begin_lambda", "opt_captures", "capture_list", "capture", "opt_deep",
  "func_params", "opt_type", "init_class", "opt_init", "$@31", "$@32",
  "index_slice", "opt_attr", "attr_list", "attr", "stmt", "$@33",
  "stmt_list", "event", "case_list", "case", "case_type_list", "case_type",
  "for_head", "local_id_list", "local_id", "global_id", "$@34",
  "def_global_id", "$@35", "$@36", "event_id", "$@37",
  "global_or_event_id", "resolve_id", "opt_no_test", "opt_no_test_block",
  "opt_deprecated", "expr_list_opt_comma", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-539)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-199)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -77,  -539,    52,  3193,  2568,  -539,  -539,  -539,   -34,   -27,
      19,  -539,  -539,  -539,   -65,  -539,  -539,  -539,   113,   137,
    -539,  -539,  -539,  -539,  -539,  -539,    40,    31,  -539,  -539,
     139,    57,  2568,    68,    69,    70,  2568,  2568,  2568,  -539,
    2568,  2568,  2568,  2568,   161,  2568,  2568,  2074,  -539,  -539,
    2568,   162,   163,   102,  -539,   102,    76,   175,  -539,    76,
     102,    76,    80,  -539,  -539,  -539,  -539,   175,   117,   996,
    -539,  2568,   196,  -539,    76,  2568,  -539,   120,  2568,  1099,
    2568,  -539,  2568,  2139,   111,   111,   169,   111,   111,   111,
     111,    32,  2074,   125,   106,  1294,  2330,  2330,  3092,  3092,
    -539,  2660,  2568,  2568,  2568,  2568,  2568,  2568,  2568,  2568,
    2568,  2568,  2568,  2568,  2568,  2568,  2568,  2568,  2568,  2568,
    2568,  2568,   205,  2660,  -539,   207,  1359,   105,   118,  3092,
      81,  -539,    81,   208,  1297,  -539,  -539,  -539,  1297,    81,
    1297,  -539,   239,    76,   127,   102,  -539,  -539,  2568,   122,
     139,  2568,   215,   130,   126,   131,   139,   133,  2568,  2303,
    2568,  -539,   134,  -539,  -539,  -539,   203,   996,    50,   394,
    -539,   173,  -539,   996,   119,  1424,  -539,   -61,  -539,   236,
     128,  -539,  2873,  2330,   -52,   215,   149,  2568,   155,   235,
     246,  2568,   188,  2568,  -539,  -539,  -539,  -539,  2074,  -539,
    -539,  -539,  -539,  -539,  -539,  -539,   165,   171,   254,    76,
     176,  -539,  -539,  -539,   256,   258,  -539,  -539,   178,   182,
    -539,  -539,   185,  -539,   265,  -539,  -539,  -539,  2330,  1489,
    2793,  2873,  2901,  2901,  2901,  2901,  2901,  2901,   469,   469,
     609,  2285,   574,   292,   292,   157,   157,   111,   111,   111,
    -539,   213,  1554,   -41,  2568,  -539,  -539,  -539,  -539,  -539,
    -539,  -539,  -539,  2422,  -539,  2422,   216,   189,   -73,  -539,
     221,   222,  -539,  -539,   223,   228,   229,   231,   238,  -539,
     243,   245,  -539,   253,   255,  -539,  -539,   262,   263,   269,
    -539,  -539,  -539,  -539,  1297,  -539,   195,  -539,  2422,  -539,
     201,  1297,   316,   359,    81,  3092,   722,   273,   102,   845,
     247,   237,   273,    22,  2568,   102,   273,   -71,  -539,   273,
     968,  1164,  2568,   278,  2568,  -539,   132,  -539,   273,  2568,
    -539,  -539,  -539,  -539,  -539,   196,  -539,  -539,  -539,  -539,
    -539,  2568,  -539,   260,  1297,   266,  -539,  -539,  2074,  -539,
    2074,  2568,  -539,   208,  3092,  -539,   208,  3092,   358,  -539,
    3092,  3092,  3092,  -539,  2568,  2568,  -539,  -539,  1297,  2330,
    1297,  3092,   297,   208,   208,  2568,  2568,  2568,  2568,  2568,
    2568,  2568,  2568,  2568,  2568,  2568,  2568,  2568,   376,  -539,
    -539,  1297,  -539,  -539,   343,   270,  2422,  1297,   273,  -539,
    -539,    81,   273,  2568,   273,  -539,    74,   139,  1619,    81,
    -539,   273,  -539,   273,  -539,  1684,  -539,  -539,  1229,   274,
     308,   277,  2568,  -539,  1034,  -539,  -539,  -539,  -539,  -539,
    -539,   282,   286,   125,   377,   295,  -539,   296,  -539,  -539,
    -539,  -539,   -35,   -32,  -539,  2691,   294,  2074,   298,   299,
    -539,   300,  1297,  3092,  -539,  -539,  2074,  2074,  2074,  2074,
    2074,  2074,  2074,  2074,  2074,  2074,  2074,  2074,  2074,  -539,
     301,   377,   417,   372,  -539,  1297,   302,  -539,  2422,  -539,
     303,  -539,   391,  2568,   -28,  -539,   996,  2422,  -539,  -539,
      29,   996,   750,   278,   309,  -539,  2074,   273,   996,   996,
    1297,  -539,  -539,  -539,    -7,   305,   333,  -539,  -539,  -539,
     393,  3092,  -539,   392,  -539,  -539,  -539,  -539,  -539,  -539,
    -539,  -539,   307,   311,   312,  -539,   315,  -539,  1297,  -539,
     332,  1749,   139,    77,   418,  1297,  2541,   345,  -539,  -539,
    -539,  -539,  -539,  -539,  -539,  -539,   318,   319,  -539,   355,
      28,  -539,  -539,   377,   356,   324,  -539,  -539,  3092,   325,
    1297,  1297,   393,  -539,   326,  2568,  -539,  -539,   423,  2568,
     996,   328,  3137,   -48,    75,  -539,  -539,   873,   334,  -539,
    -539,   445,   378,   446,  -539,  3092,  -539,  -539,  -539,  2206,
    2656,   337,   273,  1814,   363,  1879,  -539,   273,   403,  -539,
     408,  -539,   996,  -539,  -539,  -539,  -539,  -539,  1297,   341,
     342,  1297,  -539,  -539,  2568,  -539,  -539,   439,   996,  -539,
     996,   344,  -539,  -539,   347,  1944,  -539,  -539,  -539,  -539,
    -539,   139,   351,   354,  2660,  2660,  2660,  2660,  2660,  2660,
     447,  2449,  2449,  3137,  3137,  -539,  2660,  2660,  2660,  2660,
    2660,  2660,  2660,  2660,  2660,  2660,  2660,  2660,  2660,  2660,
    2660,  2660,  2660,  2660,  2660,  2660,  2660,  2204,   440,   360,
     442,   365,   468,  2660,  2660,   388,  2568,  -539,   264,   264,
     264,   264,   264,   264,    38,  2204,  2449,  2009,  2822,  2952,
    2980,  2980,  2980,  2980,  2980,  2980,   494,   494,  2639,  2404,
    1125,  1188,  1188,   220,   220,   264,   264,   264,  3137,   208,
    3137,  3092,  3137,  2204,  2952,  2449,   387,  2568,  2660,  2660,
     396,    -1,  1362,   398,  2204,  2742,  -539,   470,   425,   431,
     432,   433,   436,   437,   438,   443,   444,   448,   449,   450,
     451,  1362,  -539,  3137,  2660,  2660,  2660,  2660,  2660,  2660,
    2660,  2660,  2660,  2660,  2660,  2660,  2660,  1362,  2204,  2204,
    2204,  2204,  2204,  2204,  2204,  2204,  2204,  2204,  2204,  2204,
    2204
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       7,     4,     0,     2,     0,     1,   169,   170,     0,     0,
       0,   275,   275,   278,     0,   275,   275,   275,     0,   273,
     275,   255,     6,   163,   161,    78,     0,   184,    72,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    79,
       0,     0,     0,     0,     0,    92,     0,     5,    75,    55,
       0,     0,     0,   193,   273,   193,     0,     0,   142,     0,
     193,     0,     0,   273,   278,   273,   147,     0,     0,     3,
     164,     0,   189,   164,     0,     0,   272,     0,     0,     0,
      92,    64,    92,     0,    29,    28,     0,    24,    25,    26,
      27,   184,    90,   290,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    69,     0,     0,     0,     0,     0,
     194,   276,   194,   136,   204,   280,   279,     7,   204,   194,
     204,   141,     0,     0,   155,   193,   274,   159,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    16,     0,   231,   252,   249,    11,     0,     0,     0,
     253,    55,   254,     0,     0,     0,   188,     0,   186,     0,
       0,   182,    73,     0,     0,     0,     0,    92,     0,    81,
       0,     0,     0,   289,    91,    62,    22,    84,    86,    31,
      33,   109,   111,   100,   102,   103,     0,     0,   126,     0,
       0,   281,   101,   105,   119,     0,   107,   108,     0,     0,
     106,   110,     0,   104,     0,    82,   128,    83,     0,     0,
      43,    42,    46,    48,    47,    49,    44,    45,    60,    61,
      38,    39,    37,    40,    41,    30,    32,    34,    35,    36,
      56,     0,    90,     0,    92,    74,   166,   167,   168,   192,
     196,   197,   195,   201,   277,   201,     0,     0,   134,   139,
       0,     0,   208,   209,     0,     0,     0,     0,     0,   222,
       0,     0,   216,     0,     0,   226,   227,     0,     0,   228,
     210,   211,   230,   172,   203,   206,     0,   171,   201,   173,
       0,   204,     0,     0,   194,     0,     0,   283,   193,     0,
       0,     0,   283,     0,     0,   193,   283,     0,    15,   283,
       0,     0,     0,   285,     0,    12,    18,    19,   283,     0,
     238,   175,   165,   162,    23,   189,   183,   187,   178,   181,
      53,     0,    63,     0,   204,     0,    68,    80,    57,    58,
      89,    88,   117,   136,     0,   122,   136,     0,     0,   114,
       0,     0,     0,    52,     0,     9,    54,    70,   204,     0,
     204,     0,   191,     0,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
     143,   204,   149,   174,   151,     0,   201,   204,   283,   282,
     241,   194,   283,    92,   283,   242,     0,     0,     0,   194,
     240,   283,   243,   283,   258,     0,   284,   255,     0,     0,
      17,     0,     0,   251,     0,   255,   185,   255,    76,    67,
      65,     0,     0,   290,     0,     0,   125,     0,   120,   127,
     132,   130,     0,     0,   121,    50,     0,     8,     0,     0,
     199,     0,   204,     0,   138,   137,   212,   207,   213,   218,
     219,   220,   221,   214,   215,   217,   223,   224,   225,   229,
       0,     0,     0,     0,   156,   204,     0,   245,   201,   246,
       0,   234,     0,     0,     0,   271,     0,   201,   233,   244,
       0,     0,     0,   285,     0,    14,    20,   283,   176,   179,
     204,    59,    85,    87,   288,     0,    93,    95,   123,   124,
     115,     0,   113,     0,   202,    71,   145,   200,   146,   140,
     190,   144,     0,     0,     0,   132,     0,   160,   204,   256,
       0,     0,     0,     0,   235,   204,     0,     0,   237,   257,
     239,   232,   255,    19,    21,   250,     0,     0,    66,   286,
       0,    99,   118,    94,     0,     0,   131,   129,     0,     0,
       0,     0,   157,   148,     0,     0,   266,   270,     0,     0,
       0,     0,     0,     0,     0,   263,   255,     0,     0,   177,
     180,     0,   288,     0,    96,     0,   116,   112,   150,     0,
       0,     0,   283,     0,     0,     0,   236,   283,   264,   255,
       0,   255,   261,    10,    13,   287,    97,    98,   204,     0,
       0,   204,   248,   268,     0,   267,   247,     0,   259,   262,
     260,     0,   152,   154,     0,     0,   265,   133,   158,   269,
      72,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,   126,     0,
     119,     0,     0,     0,     0,     0,    92,    64,    29,    28,
      24,    25,    26,    27,   184,    86,     0,     0,    43,    42,
      46,    48,    47,    49,    44,    45,    60,    61,    38,    39,
      37,    40,    41,    30,    32,    34,    35,    36,     0,   136,
       0,     0,     0,    89,    73,     0,     0,    92,     0,     0,
       0,     0,   204,     0,    57,    50,   191,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   204,   212,   207,
     213,   218,   219,   220,   221,   214,   215,   217,   223,   224,
     225
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -539,  -539,  -539,  -539,   352,   151,  -539,  -539,  -539,  -539,
    -539,   -10,  -539,  -539,    -4,  -107,  -539,  -138,  -197,  -539,
    -539,   -84,  -539,   -95,  -539,  -539,   -75,   -53,    78,  -539,
      -5,   -45,  -539,  -539,  -539,  -352,    25,  -539,  -341,  -539,
    -251,  -539,  -539,  -539,  -539,  -539,  -539,  -539,  -539,  -539,
    -539,  -539,   478,     8,  -539,  -539,  -539,  -539,   121,  -539,
    -539,  -539,   527,  -539,   230,   227,  -539,    21,   -25,  -114,
    -248,  -539,  -539,   -49,  -133,  -538,  -288,  -159,  -539,  -401,
     370,  -539,  -539,  -539,   -43,  -539,  -539,  -146,   153,  -539,
      53,  -539,  -539,   499,  -539,   491,  -539,  -253,    71,   -16,
     135
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,    21,     4,     3,   251,   165,   166,   167,   168,
     419,   421,   422,   544,   169,   228,   431,   187,   500,   254,
     448,    75,    86,   199,   351,   432,    93,    94,   505,   506,
     507,   441,   440,   555,   434,   442,   510,   556,   267,   268,
     269,    22,   137,   145,   471,   472,   473,   303,   525,   591,
     305,    70,   174,   170,    24,   333,   425,   546,   339,   427,
     547,    48,   192,    74,   177,   178,   179,   355,   130,   263,
     368,   369,   517,    49,   429,   294,   295,   172,   323,    69,
     311,   490,   539,   574,   575,   173,   484,    77,    66,    67,
      53,    54,   264,    56,    57,   136,   226,   400,   417,   551,
     194
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,   293,   200,   184,   308,   297,   389,   299,   325,   443,
     315,    23,   435,     1,   330,   437,   492,   370,   265,   373,
     171,   341,   589,   590,   498,   298,   499,   186,    79,   188,
     132,   335,    83,    84,    85,   139,    87,    88,    89,    90,
     341,    92,    95,   536,   673,   582,   126,   599,   253,   537,
     391,   341,     5,   225,   227,   406,   374,   511,   411,   405,
     511,   336,    58,   410,   532,    55,   412,   175,    59,    60,
      61,   182,   342,    68,    92,   423,    92,   134,    92,   549,
     138,   366,   140,   317,   259,   260,   550,   512,   340,    50,
     513,   511,   198,   198,   533,   181,    51,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   171,   252,
     304,   727,   454,   455,   171,   191,     6,     7,     8,     9,
      10,   718,   261,   363,   345,     6,     7,     8,     9,    10,
     583,   577,    52,   407,   306,   477,    62,   309,   475,   479,
     176,   481,    72,    72,    92,   320,   321,   538,   488,    72,
     489,    63,    64,    71,   301,  -189,   482,   600,   393,   568,
     601,   326,    76,   327,   262,   602,    98,    99,   483,   198,
      78,   569,   332,    92,   741,   240,    65,   348,   332,   350,
     396,    80,    81,    82,    91,   127,   128,   129,   618,   133,
     620,   367,     6,     7,     8,     9,    10,   131,   135,   141,
      11,    12,   147,   183,   176,   190,   142,   193,   144,   741,
      13,    14,    98,    99,   198,    15,    16,    17,   195,   257,
     528,   122,   123,    18,   124,   449,   125,   451,   250,   535,
     255,   266,   258,   300,   545,    19,   331,   302,   310,   313,
      92,   307,    25,    26,   314,   338,    20,   322,   470,   312,
     397,   485,   316,   324,   476,    27,   329,    28,    29,   337,
     119,   120,   121,   344,   450,    30,   433,   122,   123,   346,
     124,   349,   125,   401,    31,   643,   644,   478,    32,    33,
     409,   347,   352,    34,   353,   487,   354,    35,   357,   356,
     358,   389,   389,   360,    23,   359,   361,   362,   365,   436,
     408,   371,   438,   372,   375,   376,   377,   444,   415,   519,
     418,   378,   379,   390,   380,   424,   452,   534,   392,   643,
     644,   381,   540,   664,   665,   666,   382,   350,   383,   612,
     122,   123,   526,   124,   616,   125,   384,    92,   385,   394,
     480,    40,    41,    42,    43,   386,   387,    98,    99,   721,
     445,   447,   388,   395,   399,   198,   404,   548,   720,   416,
     403,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   122,   123,   567,   124,   428,   125,
     430,   439,   453,   469,  -153,   564,   494,   474,    96,    92,
     335,   495,   571,   117,   118,   119,   120,   121,   520,   338,
     504,   596,   122,   123,   502,   124,   514,   125,   496,   508,
     509,   523,   515,   524,   530,   553,   554,   529,   516,   518,
     521,   527,   543,   552,   558,   559,   565,   171,   560,   561,
     576,   570,   171,   171,   563,    97,   579,   580,   581,   171,
     171,   585,   586,   389,   588,   592,   594,   597,   604,    98,
      99,   573,   605,   607,   549,   611,   557,   614,   617,   572,
     622,   623,   626,   627,   676,   621,   628,   677,   624,   531,
     684,   715,   708,   709,   710,   675,   711,   100,   101,   296,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     712,   722,   743,   587,   122,   123,   446,   124,   744,   125,
     726,   171,   742,   328,   745,   746,   747,   598,   171,   748,
     749,   750,   667,   578,    98,    99,   751,   752,   686,   717,
     608,   753,   754,   755,   756,   757,   674,   200,   584,   522,
     562,   180,   501,   171,    73,   343,   420,   619,   146,   643,
     644,   593,   426,   143,   542,   595,   606,     0,   503,   171,
       0,   171,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,     0,     0,     0,   122,
     123,   363,   124,     0,   125,     0,     0,     0,   225,   227,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
     625,     0,     0,     0,   122,   123,     0,   124,     0,   125,
     340,     0,     0,   716,   548,     0,     0,     0,     0,     0,
     678,   679,   680,   681,   682,   683,     0,   685,   685,    98,
      99,     0,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   700,   701,   702,   703,   704,
     705,   706,   707,   436,   723,   438,     0,   444,     0,   713,
     714,     0,    92,     0,    98,    99,     0,     0,     0,     0,
       0,     0,   685,   115,   116,   117,   118,   119,   120,   121,
       0,     0,     0,     0,   122,   123,     0,   124,   587,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   685,     0,    92,   724,   725,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,    96,     0,     0,   122,
     123,     0,   124,     0,   125,     0,     0,     0,     0,     0,
     758,   759,   760,   761,   762,   763,   764,   765,   766,   767,
     768,   769,   770,   148,     0,     0,     0,     6,     7,     8,
       9,    10,     0,   149,     0,     0,   150,    25,    26,     0,
       0,   151,     0,    97,     0,   152,     0,   153,     0,   154,
      27,     0,    28,    29,   155,     0,     0,    98,    99,   156,
      30,   157,     0,     0,     0,     0,     0,     0,   158,    31,
       0,     0,   159,    32,    33,     0,     0,   160,    34,     0,
       0,     0,    35,   161,   162,   100,   101,     0,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,     0,     0,
       0,     0,   122,   123,     0,   124,     0,   125,     0,    96,
       0,   398,     0,     0,     0,     0,    36,     0,     0,     0,
       0,    37,    38,     0,    39,     0,    40,    41,    42,    43,
      44,    45,     0,    46,     0,     0,   148,   163,   541,   164,
       6,     7,     8,     9,    10,     0,   149,     0,     0,   150,
      25,    26,     0,     0,   151,     0,    97,     0,   152,     0,
     153,     0,   154,    27,     0,    28,    29,   155,     0,     0,
      98,    99,   156,    30,   157,     0,     0,     0,     0,     0,
       0,   158,    31,     0,     0,   159,    32,    33,     0,     0,
     160,    34,     0,     0,     0,    35,   161,   162,   100,   101,
       0,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,   122,   123,     0,   124,     0,
     125,     0,    96,     0,   402,     0,     0,     0,     0,    36,
       0,     0,     0,     0,    37,    38,     0,    39,     0,    40,
      41,    42,    43,    44,    45,     0,    46,     0,     0,   148,
     163,   603,   164,     6,     7,     8,     9,    10,     0,   149,
       0,     0,   150,    25,    26,     0,     0,   151,     0,    97,
       0,   152,     0,   153,     0,   154,    27,     0,    28,    29,
     155,     0,     0,    98,    99,   156,    30,   157,    96,     0,
       0,     0,     0,     0,   158,    31,     0,     0,   159,    32,
      33,     0,     0,   160,    34,     0,     0,     0,    35,   161,
     162,   100,   101,     0,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     0,    97,     0,     0,   122,   123,
       0,   124,     0,   125,     0,     0,     0,   413,     0,    98,
      99,     0,    36,    96,     0,     0,     0,    37,    38,     0,
      39,     0,    40,    41,    42,    43,    44,    45,     0,    46,
       0,     0,     0,   163,     0,   164,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      97,     0,     0,     0,   122,   123,     0,   124,     0,   125,
       0,     0,     0,   497,    98,    99,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     643,   644,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,    97,     0,     0,     0,   122,
     123,     0,   124,     0,   125,     0,   185,     0,     0,    98,
      99,     0,     0,    96,   660,   661,   662,   663,   664,   665,
     666,     0,     0,     0,     0,   122,   123,     0,   124,     0,
     125,     0,     0,   643,   644,     0,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      97,     0,     0,     0,   122,   123,     0,   124,     0,   125,
       0,   414,     0,     0,    98,    99,     0,     0,    96,   662,
     663,   664,   665,   666,     0,     0,     0,     0,   122,   123,
       0,   124,     0,   125,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,    97,     0,     0,     0,   122,
     123,     0,   124,     0,   125,     0,   493,     0,     0,    98,
      99,     0,     0,    96,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      97,     0,     0,     0,   122,   123,     0,   124,   196,   125,
       0,     0,     0,     0,    98,    99,     0,     0,    96,   728,
     729,   272,   273,   730,   731,   732,   733,   734,   279,   735,
     736,   282,   737,   738,   285,   286,   739,   740,   289,   290,
     291,   292,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,    97,     0,     0,     0,   122,
     123,     0,   124,   256,   125,     0,     0,     0,     0,    98,
      99,     0,     0,   641,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     642,     0,     0,     0,   122,   123,     0,   124,   334,   125,
       0,     0,     0,     0,   643,   644,     0,     0,   641,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   645,   646,   364,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   642,     0,     0,     0,   122,
     123,     0,   124,     0,   125,     0,     0,     0,     0,   643,
     644,     0,     0,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   645,   646,    -8,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
      97,     0,     0,     0,   122,   123,     0,   124,     0,   125,
       0,     0,     0,     0,    98,    99,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,    97,     0,     0,     0,   122,
     123,     0,   124,   486,   125,     0,     0,     0,     0,    98,
      99,     0,     0,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      97,     0,     0,     0,   122,   123,     0,   124,   491,   125,
       0,     0,     0,     0,    98,    99,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,    97,     0,     0,     0,   122,
     123,     0,   124,   566,   125,     0,     0,     0,     0,    98,
      99,     0,     0,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      97,     0,     0,     0,   122,   123,     0,   124,   613,   125,
       0,     0,     0,     0,    98,    99,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,    97,     0,     0,     0,   122,
     123,     0,   124,   615,   125,     0,     0,     0,     0,    98,
      99,     0,     0,   641,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     642,     0,     0,     0,   122,   123,     0,   124,   629,   125,
       0,     0,     0,     0,   643,   644,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   645,   646,   719,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,    97,     0,     0,     0,   122,
     123,     0,   124,     0,   125,     0,     0,     0,     0,    98,
      99,     0,     0,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      97,     0,     0,     0,   122,   123,     0,   124,     0,   125,
       0,     0,     0,     0,    98,    99,     0,     0,   641,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,     0,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   189,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   642,     0,     0,     0,   122,
     123,     0,   124,     0,   125,     0,     0,     0,     0,   643,
     644,     0,     0,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,     0,   645,   646,     0,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   664,   665,   666,
      25,    26,     0,     0,   122,   123,     0,   124,     0,   125,
       0,     0,     0,    27,   609,    28,    29,     0,     0,     0,
       0,     0,     0,    30,     0,     0,     0,    25,    26,     0,
      98,    99,    31,     0,     0,     0,    32,    33,     0,     0,
      27,    34,    28,    29,     0,    35,   318,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,    32,    33,     0,     0,     0,    34,     0,
       0,     0,    35,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,   122,   123,     0,   124,    36,
     125,     0,     0,     0,    37,    38,     0,    39,     0,    40,
      41,    42,    43,    44,    45,     0,    46,     0,     0,     0,
       0,     0,   319,     0,     0,     0,    36,     0,     0,  -198,
    -198,    37,    38,     0,    39,     0,    40,    41,    42,    43,
      44,    45,  -198,    46,  -198,  -198,     0,   197,     0,     0,
       0,     0,  -198,     0,     0,     0,    25,    26,     0,   643,
     644,  -198,     0,     0,     0,  -198,  -198,     0,     0,    27,
    -198,   630,    29,     0,  -198,     0,     0,     0,     0,   631,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,    32,   632,     0,     0,     0,   633,     0,     0,
       0,    35,   659,   660,   661,   662,   663,   664,   665,   666,
       0,     0,     0,     0,   122,   123,     0,   124,  -198,   125,
       0,     0,     0,  -198,  -198,     0,  -198,     0,  -198,  -198,
    -198,  -198,  -198,  -198,     0,  -198,     0,     0,     0,  -198,
       0,     0,     0,     0,     0,    36,     0,     0,    25,    26,
     634,   635,     0,    39,     0,   636,   637,   638,   639,   640,
      45,    27,    46,   630,    29,     0,   197,     0,     0,     0,
       0,   631,     0,     0,     0,    25,    26,     0,     0,     0,
      31,     0,     0,     0,    32,   632,     0,     0,    27,   633,
      28,    29,   572,    35,     0,     0,     0,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,    32,    33,     0,     0,     0,    34,     0,     0,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,   634,   635,     0,    39,     0,   636,   637,   638,
     639,   640,    45,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,    25,    26,    37,
      38,     0,    39,     0,    40,    41,    42,    43,    44,    45,
      27,    46,   630,    29,     0,     0,     0,     0,     0,     0,
     631,     0,     0,     0,   643,   644,     0,     0,     0,    31,
       0,     0,     0,    32,   632,     0,     0,     0,   633,     0,
       0,     0,    35,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   658,   659,   660,   661,
     662,   663,   664,   665,   666,     0,    98,    99,     0,   122,
     123,     0,   124,     0,   125,     0,    36,     0,     0,     0,
       0,   634,   635,     0,    39,     0,   636,   637,   638,   639,
     640,    45,     0,    46,   610,   101,     0,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   643,   644,     0,
       0,   122,   123,     0,   124,     0,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   646,     0,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,    98,    99,
       0,     0,   122,   123,     0,   124,     0,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   643,   644,     0,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,   122,   123,     0,   124,     0,   125,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,    98,    99,
       0,     0,   122,   123,     0,   124,     0,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    98,    99,     0,     0,
       0,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,   122,   123,     0,   124,     0,   125,  -199,
    -199,  -199,  -199,  -199,  -199,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   643,   644,     0,
       0,   122,   123,     0,   124,     0,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   643,   644,     0,     0,     0,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,     0,     0,
       0,     0,   122,   123,     0,   124,     0,   125,  -199,  -199,
    -199,  -199,  -199,  -199,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,     0,   201,   202,     0,
     122,   123,     0,   124,   203,   125,     0,     0,     0,     0,
       0,   204,     0,     0,   205,     0,   206,   207,     0,     0,
     208,     0,   209,     0,   210,   211,     0,   212,   213,   214,
       0,     0,     0,     0,     0,   215,   216,     0,     0,   217,
       0,   218,   201,   202,     0,     0,   219,   220,   221,   203,
     222,   223,     0,     0,   224,     0,   204,     0,     0,   205,
       0,   206,   207,     0,     0,   668,     0,   669,     0,   210,
     211,     0,   212,   213,   670,     0,     0,     0,     0,     0,
     215,   216,     0,     0,   217,     0,   218,     0,     0,     0,
       0,   219,   220,   221,     0,   671,   223,     0,     0,   672,
       6,     7,     8,     9,    10,     0,     0,     0,    11,    12,
       0,     0,     0,     0,     0,     0,     0,     0,    13,    14,
       0,     0,     0,    15,    16,    17,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20
};

static const yytype_int16 yycheck[] =
{
       4,   134,    97,    78,   150,   138,   294,   140,   167,   361,
     156,     3,   353,    90,   173,   356,   417,   265,   132,    92,
      69,    92,   560,   561,   425,   139,   427,    80,    32,    82,
      55,    92,    36,    37,    38,    60,    40,    41,    42,    43,
      92,    45,    46,    14,    92,    17,    50,    95,   123,    20,
     298,    92,     0,    98,    99,    33,   129,    92,   129,   312,
      92,   122,   127,   316,    92,    12,   319,    71,    15,    16,
      17,    75,   124,    20,    78,   328,    80,    56,    82,    86,
      59,   122,    61,   158,   129,     4,    93,   122,   183,   123,
     122,    92,    96,    97,   122,    74,   123,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   167,   123,
     145,   122,   373,   374,   173,    93,     7,     8,     9,    10,
      11,    93,    51,   228,   187,     7,     8,     9,    10,    11,
     112,   542,   123,   121,   148,   398,    33,   151,   396,   402,
      18,   404,   121,   121,   158,   159,   160,   128,   411,   121,
     413,    24,    25,   123,   143,    33,    92,    92,   301,    92,
      95,   121,    33,   123,    93,   576,    65,    66,   104,   183,
     123,   104,   174,   187,   722,   189,    49,   191,   180,   193,
     304,   123,   123,   123,    33,    33,    33,    95,   599,   123,
     601,   254,     7,     8,     9,    10,    11,    54,    33,   129,
      15,    16,    95,    93,    18,    46,    63,    92,    65,   757,
      25,    26,    65,    66,   228,    30,    31,    32,   122,   124,
     478,   120,   121,    38,   123,   368,   125,   370,    33,   487,
      33,    33,   124,     4,   497,    50,   127,   120,    33,   123,
     254,   129,    17,    18,   123,   127,    61,   123,   391,   129,
     305,   407,   129,    60,   397,    30,    93,    32,    33,    33,
     113,   114,   115,   124,   369,    40,   351,   120,   121,   124,
     123,    93,   125,   308,    49,    65,    66,   401,    53,    54,
     315,    45,   127,    58,   123,   409,    42,    62,    42,   123,
      42,   589,   590,   121,   296,   127,   121,    42,    95,   354,
     314,    95,   357,   124,    93,    93,    93,   362,   322,   452,
     324,    93,    93,   128,    93,   329,   371,   486,   127,    65,
      66,    93,   491,   113,   114,   115,    93,   341,    93,   592,
     120,   121,   475,   123,   597,   125,    93,   351,    93,    33,
     403,   116,   117,   118,   119,    93,    93,    65,    66,   711,
     364,   365,    93,     4,    91,   369,   129,   500,   709,    91,
     123,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   120,   121,   532,   123,   128,   125,
     124,    33,    95,    17,    51,   528,   122,   127,     4,   403,
      92,   124,   535,   111,   112,   113,   114,   115,   453,   127,
      33,   570,   120,   121,   128,   123,   122,   125,   422,   124,
     124,     4,   124,    51,    33,    92,    33,   124,   129,   129,
     129,   129,   123,   128,    42,   128,   104,   486,   127,   127,
      95,    23,   491,   492,   129,    51,   128,   128,    93,   498,
     499,    95,   128,   741,   129,   129,    33,   129,   124,    65,
      66,   536,    17,    17,    86,   128,   511,   104,    65,    61,
     129,   129,    33,   129,   123,   608,   129,   123,   611,   483,
      33,    93,    42,   123,    42,   631,   121,    93,    94,   137,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      42,   124,    42,   558,   120,   121,   365,   123,    93,   125,
     124,   570,   124,   129,    93,    93,    93,   572,   577,    93,
      93,    93,   536,   543,    65,    66,    93,    93,   645,   677,
     585,    93,    93,    93,    93,   742,   630,   642,   553,   471,
     525,    73,   431,   602,    27,   185,   326,   600,    67,    65,
      66,   565,   335,    64,   493,   569,   582,    -1,   433,   618,
      -1,   620,    -1,    -1,    -1,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,    -1,    -1,    -1,   120,
     121,   686,   123,    -1,   125,    -1,    -1,    -1,   643,   644,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     614,    -1,    -1,    -1,   120,   121,    -1,   123,    -1,   125,
     715,    -1,    -1,   676,   757,    -1,    -1,    -1,    -1,    -1,
     634,   635,   636,   637,   638,   639,    -1,   641,   642,    65,
      66,    -1,   646,   647,   648,   649,   650,   651,   652,   653,
     654,   655,   656,   657,   658,   659,   660,   661,   662,   663,
     664,   665,   666,   708,   717,   710,    -1,   712,    -1,   673,
     674,    -1,   676,    -1,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,   686,   109,   110,   111,   112,   113,   114,   115,
      -1,    -1,    -1,    -1,   120,   121,    -1,   123,   743,   125,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   715,    -1,   717,   718,   719,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,     4,    -1,    -1,   120,
     121,    -1,   123,    -1,   125,    -1,    -1,    -1,    -1,    -1,
     744,   745,   746,   747,   748,   749,   750,   751,   752,   753,
     754,   755,   756,     3,    -1,    -1,    -1,     7,     8,     9,
      10,    11,    -1,    13,    -1,    -1,    16,    17,    18,    -1,
      -1,    21,    -1,    51,    -1,    25,    -1,    27,    -1,    29,
      30,    -1,    32,    33,    34,    -1,    -1,    65,    66,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      -1,    -1,    52,    53,    54,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    63,    64,    93,    94,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    -1,    -1,
      -1,    -1,   120,   121,    -1,   123,    -1,   125,    -1,     4,
      -1,   129,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,
      -1,   111,   112,    -1,   114,    -1,   116,   117,   118,   119,
     120,   121,    -1,   123,    -1,    -1,     3,   127,   128,   129,
       7,     8,     9,    10,    11,    -1,    13,    -1,    -1,    16,
      17,    18,    -1,    -1,    21,    -1,    51,    -1,    25,    -1,
      27,    -1,    29,    30,    -1,    32,    33,    34,    -1,    -1,
      65,    66,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    -1,    52,    53,    54,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    63,    64,    93,    94,
      -1,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    -1,    -1,    -1,    -1,   120,   121,    -1,   123,    -1,
     125,    -1,     4,    -1,   129,    -1,    -1,    -1,    -1,   106,
      -1,    -1,    -1,    -1,   111,   112,    -1,   114,    -1,   116,
     117,   118,   119,   120,   121,    -1,   123,    -1,    -1,     3,
     127,   128,   129,     7,     8,     9,    10,    11,    -1,    13,
      -1,    -1,    16,    17,    18,    -1,    -1,    21,    -1,    51,
      -1,    25,    -1,    27,    -1,    29,    30,    -1,    32,    33,
      34,    -1,    -1,    65,    66,    39,    40,    41,     4,    -1,
      -1,    -1,    -1,    -1,    48,    49,    -1,    -1,    52,    53,
      54,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    63,
      64,    93,    94,    -1,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,    -1,    51,    -1,    -1,   120,   121,
      -1,   123,    -1,   125,    -1,    -1,    -1,   129,    -1,    65,
      66,    -1,   106,     4,    -1,    -1,    -1,   111,   112,    -1,
     114,    -1,   116,   117,   118,   119,   120,   121,    -1,   123,
      -1,    -1,    -1,   127,    -1,   129,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,    -1,   125,
      -1,    -1,    -1,   129,    65,    66,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    93,    94,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,    -1,   125,    -1,   127,    -1,    -1,    65,
      66,    -1,    -1,     4,   109,   110,   111,   112,   113,   114,
     115,    -1,    -1,    -1,    -1,   120,   121,    -1,   123,    -1,
     125,    -1,    -1,    65,    66,    -1,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,    -1,   125,
      -1,   127,    -1,    -1,    65,    66,    -1,    -1,     4,   111,
     112,   113,   114,   115,    -1,    -1,    -1,    -1,   120,   121,
      -1,   123,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,    -1,   125,    -1,   127,    -1,    -1,    65,
      66,    -1,    -1,     4,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,   124,   125,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,     4,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    93,    94,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,   124,   125,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,   124,   125,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,    -1,   125,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,    -1,   125,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,   124,   125,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,   124,   125,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,   124,   125,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,   124,   125,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,   124,   125,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,   124,   125,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,    -1,   125,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      51,    -1,    -1,    -1,   120,   121,    -1,   123,    -1,   125,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    -1,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    51,    -1,    -1,    -1,   120,
     121,    -1,   123,    -1,   125,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    93,    94,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      17,    18,    -1,    -1,   120,   121,    -1,   123,    -1,   125,
      -1,    -1,    -1,    30,   128,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    17,    18,    -1,
      65,    66,    49,    -1,    -1,    -1,    53,    54,    -1,    -1,
      30,    58,    32,    33,    -1,    62,    63,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,   108,   109,   110,   111,   112,   113,   114,
     115,    -1,    -1,    -1,    -1,   120,   121,    -1,   123,   106,
     125,    -1,    -1,    -1,   111,   112,    -1,   114,    -1,   116,
     117,   118,   119,   120,   121,    -1,   123,    -1,    -1,    -1,
      -1,    -1,   129,    -1,    -1,    -1,   106,    -1,    -1,    17,
      18,   111,   112,    -1,   114,    -1,   116,   117,   118,   119,
     120,   121,    30,   123,    32,    33,    -1,   127,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    17,    18,    -1,    65,
      66,    49,    -1,    -1,    -1,    53,    54,    -1,    -1,    30,
      58,    32,    33,    -1,    62,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    62,   108,   109,   110,   111,   112,   113,   114,   115,
      -1,    -1,    -1,    -1,   120,   121,    -1,   123,   106,   125,
      -1,    -1,    -1,   111,   112,    -1,   114,    -1,   116,   117,
     118,   119,   120,   121,    -1,   123,    -1,    -1,    -1,   127,
      -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,    17,    18,
     111,   112,    -1,   114,    -1,   116,   117,   118,   119,   120,
     121,    30,   123,    32,    33,    -1,   127,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    53,    54,    -1,    -1,    30,    58,
      32,    33,    61,    62,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,
      -1,    -1,   111,   112,    -1,   114,    -1,   116,   117,   118,
     119,   120,   121,    -1,   123,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,    -1,    17,    18,   111,
     112,    -1,   114,    -1,   116,   117,   118,   119,   120,   121,
      30,   123,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,    65,    66,    -1,   120,
     121,    -1,   123,    -1,   125,    -1,   106,    -1,    -1,    -1,
      -1,   111,   112,    -1,   114,    -1,   116,   117,   118,   119,
     120,   121,    -1,   123,   128,    94,    -1,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    65,    66,    -1,
      -1,   120,   121,    -1,   123,    -1,   125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    65,    66,
      -1,    -1,   120,   121,    -1,   123,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    -1,
      -1,    -1,    -1,   120,   121,    -1,   123,    -1,   125,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    65,    66,
      -1,    -1,   120,   121,    -1,   123,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    -1,
      -1,    -1,    -1,   120,   121,    -1,   123,    -1,   125,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    65,    66,    -1,
      -1,   120,   121,    -1,   123,    -1,   125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    -1,    -1,
      -1,    -1,   120,   121,    -1,   123,    -1,   125,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    -1,     5,     6,    -1,
     120,   121,    -1,   123,    12,   125,    -1,    -1,    -1,    -1,
      -1,    19,    -1,    -1,    22,    -1,    24,    25,    -1,    -1,
      28,    -1,    30,    -1,    32,    33,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    47,
      -1,    49,     5,     6,    -1,    -1,    54,    55,    56,    12,
      58,    59,    -1,    -1,    62,    -1,    19,    -1,    -1,    22,
      -1,    24,    25,    -1,    -1,    28,    -1,    30,    -1,    32,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    -1,    47,    -1,    49,    -1,    -1,    -1,
      -1,    54,    55,    56,    -1,    58,    59,    -1,    -1,    62,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    90,   131,   134,   133,     0,     7,     8,     9,    10,
      11,    15,    16,    25,    26,    30,    31,    32,    38,    50,
      61,   132,   171,   183,   184,    17,    18,    30,    32,    33,
      40,    49,    53,    54,    58,    62,   106,   111,   112,   114,
     116,   117,   118,   119,   120,   121,   123,   144,   191,   203,
     123,   123,   123,   220,   221,   220,   223,   224,   127,   220,
     220,   220,    33,    24,    25,    49,   218,   219,   220,   209,
     181,   123,   121,   192,   193,   151,    33,   217,   123,   144,
     123,   123,   123,   144,   144,   144,   152,   144,   144,   144,
     144,    33,   144,   156,   157,   144,     4,    51,    65,    66,
      93,    94,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   120,   121,   123,   125,   144,    33,    33,    95,
     198,   218,   198,   123,   197,    33,   225,   172,   197,   198,
     197,   129,   218,   223,   218,   173,   225,    95,     3,    13,
      16,    21,    25,    27,    29,    34,    39,    41,    48,    52,
      57,    63,    64,   127,   129,   136,   137,   138,   139,   144,
     183,   203,   207,   215,   182,   144,    18,   194,   195,   196,
     182,   197,   144,    93,   156,   127,   157,   147,   157,   106,
      46,    93,   192,    92,   230,   122,   124,   127,   144,   153,
     153,     5,     6,    12,    19,    22,    24,    25,    28,    30,
      32,    33,    35,    36,    37,    43,    44,    47,    49,    54,
      55,    56,    58,    59,    62,   161,   226,   161,   145,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
      33,   135,   144,   156,   149,    33,   124,   124,   124,   161,
       4,    51,    93,   199,   222,   199,    33,   168,   169,   170,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   204,   205,   206,   134,   204,   199,   204,
       4,   197,   120,   177,   198,   180,   144,   129,   217,   144,
      33,   210,   129,   123,   123,   217,   129,   156,    63,   129,
     144,   144,   123,   208,    60,   207,   121,   123,   129,    93,
     207,   127,   183,   185,   124,    92,   122,    33,   127,   188,
     153,    92,   124,   210,   124,   157,   124,    45,   144,    93,
     144,   154,   127,   123,    42,   197,   123,    42,    42,   127,
     121,   121,    42,   153,    95,    95,   122,   157,   200,   201,
     200,    95,   124,    92,   129,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,   206,
     128,   200,   127,   204,    33,     4,   199,   161,   129,    91,
     227,   198,   129,   123,   129,   227,    33,   121,   144,   198,
     227,   129,   227,   129,   127,   144,    91,   228,   144,   140,
     194,   141,   142,   227,   144,   186,   195,   189,   128,   204,
     124,   146,   155,   156,   164,   168,   161,   168,   161,    33,
     162,   161,   165,   165,   161,   144,   135,   144,   150,   204,
     153,   204,   161,    95,   170,   170,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,    17,
     204,   174,   175,   176,   127,   200,   204,   227,   199,   227,
     157,   227,    92,   104,   216,   217,   124,   199,   227,   227,
     211,   124,   209,   127,   122,   124,   144,   129,   209,   209,
     148,   188,   128,   230,    33,   158,   159,   160,   124,   124,
     166,    92,   122,   122,   122,   124,   129,   202,   129,   204,
     161,   129,   158,     4,    51,   178,   204,   129,   200,   124,
      33,   144,    92,   122,   207,   200,    14,    20,   128,   212,
     207,   128,   228,   123,   143,   227,   187,   190,   204,    86,
      93,   229,   128,    92,    33,   163,   167,   161,    42,   128,
     127,   127,   166,   129,   204,   104,   124,   217,    92,   104,
      23,   204,    61,   156,   213,   214,    95,   209,   141,   128,
     128,    93,    17,   112,   160,    95,   128,   161,   129,   205,
     205,   179,   129,   144,    33,   144,   207,   129,   161,    95,
      92,    95,   209,   128,   124,    17,   229,    17,   161,   128,
     128,   128,   227,   124,   104,   124,   227,    65,   209,   214,
     209,   204,   129,   129,   204,   144,    33,   129,   129,   124,
      32,    40,    54,    58,   111,   112,   116,   117,   118,   119,
     120,     4,    51,    65,    66,    93,    94,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   144,    28,    30,
      37,    58,    62,    92,   151,   217,   123,   123,   144,   144,
     144,   144,   144,   144,    33,   144,   145,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,    42,   123,
      42,   121,    42,   144,   144,    93,   157,   147,    93,    95,
     168,   165,   124,   157,   144,   144,   124,   122,    67,    68,
      71,    72,    73,    74,    75,    77,    78,    80,    81,    84,
      85,   205,   124,    42,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,   148,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   130,   132,   131,   133,   131,   134,   134,   135,   135,
     136,   136,   137,   138,   138,   139,   139,   140,   140,   142,
     143,   141,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   144,   144,   144,   144,   144,   144,   146,   144,
     144,   144,   144,   144,   147,   148,   144,   144,   144,   149,
     150,   144,   151,   144,   144,   144,   144,   144,   144,   152,
     144,   144,   144,   144,   154,   153,   153,   155,   155,   156,
     156,   157,   157,   158,   158,   159,   159,   160,   160,   160,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   162,   163,   161,   164,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   165,
     165,   166,   166,   167,   168,   168,   168,   169,   169,   169,
     170,   171,   172,   171,   171,   171,   171,   173,   171,   174,
     171,   175,   171,   176,   171,   177,   178,   179,   171,   180,
     171,   181,   171,   171,   182,   182,   183,   183,   183,   183,
     183,   184,   184,   184,   184,   186,   187,   185,   189,   190,
     188,   191,   192,   193,   193,   194,   194,   195,   196,   196,
     197,   197,   198,   198,   199,   199,   199,   199,   201,   202,
     200,   200,   203,   204,   204,   205,   205,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   208,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   209,   209,   210,   211,   211,   212,
     212,   212,   213,   213,   214,   214,   215,   215,   215,   215,
     216,   216,   217,   219,   218,   221,   222,   220,   224,   223,
     225,   226,   227,   227,   228,   228,   229,   229,   229,   230,
     230
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     0,     3,     2,     0,     1,     0,
       7,     1,     2,     7,     4,     2,     1,     1,     0,     0,
       0,     3,     3,     4,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     0,     4,     4,     4,     1,     3,     4,     0,     6,
       3,     3,     3,     4,     0,     0,     7,     5,     4,     0,
       0,     6,     0,     3,     3,     1,     5,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     1,     2,     0,     3,
       1,     2,     0,     1,     2,     1,     3,     4,     4,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     4,     0,     0,     6,     0,     5,     1,
       3,     3,     2,     4,     4,     3,     1,     3,     1,     3,
       1,     2,     0,     5,     1,     2,     0,     3,     3,     1,
       4,     3,     0,     5,     7,     7,     7,     0,     8,     0,
       9,     0,    11,     0,    11,     0,     0,     0,    12,     0,
       7,     0,     4,     1,     0,     2,     4,     4,     4,     1,
       1,     4,     4,     4,     5,     0,     0,     5,     0,     0,
       5,     4,     2,     3,     0,     3,     1,     2,     1,     0,
       5,     3,     2,     0,     0,     1,     1,     1,     0,     0,
       3,     0,     6,     1,     0,     2,     1,     3,     1,     1,
       1,     1,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     1,     1,     1,     3,
       1,     0,     5,     4,     4,     5,     7,     5,     2,     5,
       3,     3,     3,     3,     4,     4,     4,     8,     8,     1,
       5,     3,     1,     1,     2,     0,     4,     2,     0,     4,
       4,     3,     3,     1,     2,     4,     6,     8,     8,    10,
       3,     1,     1,     0,     2,     0,     0,     3,     0,     2,
       1,     1,     1,     0,     1,     0,     1,     3,     0,     1,
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 387 "parse.y"
                        {
			// Without the following, in some scenarios the
			// location associated with global statements gets
			// associated with the last @load'd file rather than
			// the script that includes the global statements.
			auto loc = zeek::detail::GetCurrentLocation();
			if ( loc.filename )
				set_location(loc);
			}
#line 2712 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 3: /* zeek: decl_list $@1 stmt_list  */
#line 397 "parse.y"
                        {
			if ( stmts )
				stmts->AsStmtList()->Stmts().push_back((yyvsp[0].stmt));
			else
				stmts = (yyvsp[0].stmt);

			// Do some further validation on the parsed AST unless
			// we already know there were errors.
			if ( zeek::reporter->Errors() == 0 )
				zeek::detail::script_validation();

			// Any objects creates from here on out should not
			// have file positions associated with them.
			set_location(no_location);
			}
#line 2732 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 4: /* $@2: %empty  */
#line 416 "parse.y"
                          { in_debug = true; }
#line 2738 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 5: /* zeek: TOK_DEBUG $@2 expr  */
#line 417 "parse.y"
                        {
			g_curr_debug_expr = (yyvsp[0].expr);
			}
#line 2746 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 8: /* opt_expr: expr  */
#line 429 "parse.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 2752 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 9: /* opt_expr: %empty  */
#line 431 "parse.y"
                        { (yyval.expr) = 0; }
#line 2758 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 10: /* when_clause: when_head TOK_TIMEOUT expr '{' opt_no_test_block stmt_list '}'  */
#line 436 "parse.y"
                        {
			set_location((yylsp[-6]), (yylsp[0]));
			(yyvsp[-6].when_clause)->AddTimeout({AdoptRef{}, (yyvsp[-4].expr)}, {AdoptRef{}, (yyvsp[-1].stmt)});
			if ( (yyvsp[-2].b) )
			    script_coverage_mgr.DecIgnoreDepth();
			}
#line 2769 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 12: /* when_head: when_start stmt  */
#line 448 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyvsp[-1].when_clause)->AddBody({AdoptRef{}, (yyvsp[0].stmt)});
			}
#line 2778 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 13: /* when_start: when_flavor '[' when_captures ']' '(' when_condition ')'  */
#line 456 "parse.y"
                        {
			set_location((yylsp[-6]), (yylsp[0]));
			(yyval.when_clause) = new WhenInfo({AdoptRef{}, (yyvsp[-1].expr)}, (yyvsp[-4].captures), (yyvsp[-6].b));
			}
#line 2787 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 14: /* when_start: when_flavor '(' when_condition ')'  */
#line 462 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			(yyval.when_clause) = new WhenInfo({AdoptRef{}, (yyvsp[-1].expr)}, nullptr, (yyvsp[-3].b));
			}
#line 2796 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 15: /* when_flavor: TOK_RETURN TOK_WHEN  */
#line 470 "parse.y"
                        { (yyval.b) = true; }
#line 2802 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 16: /* when_flavor: TOK_WHEN  */
#line 473 "parse.y"
                        { (yyval.b) = false; }
#line 2808 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 18: /* when_captures: %empty  */
#line 479 "parse.y"
                { (yyval.captures) = new zeek::FuncType::CaptureList; }
#line 2814 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 19: /* $@3: %empty  */
#line 483 "parse.y"
                { ++in_when_cond; }
#line 2820 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 20: /* $@4: %empty  */
#line 483 "parse.y"
                                         { --in_when_cond; }
#line 2826 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 21: /* when_condition: $@3 expr $@4  */
#line 484 "parse.y"
                        { (yyval.expr) = (yyvsp[-1].expr); }
#line 2832 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 22: /* expr: '(' expr ')'  */
#line 489 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = (yyvsp[-1].expr); (yyval.expr)->MarkParen();
			}
#line 2841 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 23: /* expr: TOK_COPY '(' expr ')'  */
#line 495 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			(yyval.expr) = new CloneExpr({AdoptRef{}, (yyvsp[-1].expr)});
			}
#line 2850 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 24: /* expr: TOK_INCR expr  */
#line 501 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyval.expr) = new IncrExpr(EXPR_INCR, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 2859 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 25: /* expr: TOK_DECR expr  */
#line 507 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyval.expr) = new IncrExpr(EXPR_DECR, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 2868 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 26: /* expr: '!' expr  */
#line 513 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyval.expr) = new NotExpr({AdoptRef{}, (yyvsp[0].expr)});
			}
#line 2877 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 27: /* expr: '~' expr  */
#line 519 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyval.expr) = new ComplementExpr({AdoptRef{}, (yyvsp[0].expr)});
			}
#line 2886 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 28: /* expr: '-' expr  */
#line 525 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyval.expr) = new NegExpr({AdoptRef{}, (yyvsp[0].expr)});

			if ( ! (yyval.expr)->IsError() && (yyvsp[0].expr)->IsConst() )
				{
				auto v = (yyvsp[0].expr)->ExprVal();
				auto tag = v->GetType()->Tag();

				if ( tag == TYPE_COUNT )
					{
					auto c = v->AsCount();
					uint64_t int_max = static_cast<uint64_t>(INT64_MAX) + 1;

					if ( c <= int_max )
						{
						auto ce = new ConstExpr(val_mgr->Int(-c));
						Unref((yyval.expr));
						(yyval.expr) = ce;
						}
					else
						{
						(yyval.expr)->Error("literal is outside range of 'int' values");
						(yyval.expr)->SetError();
						}
					}
				else
					{
					auto ce = new ConstExpr((yyval.expr)->Eval(nullptr));
					Unref((yyval.expr));
					(yyval.expr) = ce;
					}
				}
			}
#line 2925 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 29: /* expr: '+' expr  */
#line 561 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyval.expr) = new PosExpr({AdoptRef{}, (yyvsp[0].expr)});
			}
#line 2934 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 30: /* expr: expr '+' expr  */
#line 567 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new AddExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 2943 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 31: /* expr: expr TOK_ADD_TO rhs  */
#line 573 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));

			ExprPtr lhs = {AdoptRef{}, (yyvsp[-2].expr)};
			ExprPtr rhs = {AdoptRef{}, (yyvsp[0].expr)};
			auto tag1 = (yyvsp[-2].expr)->GetType()->Tag();

			if ( IsArithmetic((yyvsp[-2].expr)->GetType()->Tag()) )
				{
				ExprPtr sum = make_intrusive<AddExpr>(lhs, rhs);

				if ( sum->GetType()->Tag() != tag1 )
					sum = make_intrusive<ArithCoerceExpr>(sum, tag1);

				(yyval.expr) = new AssignExpr(lhs, sum, false);
				}
			else
				(yyval.expr) = new AddToExpr(lhs, rhs);
			}
#line 2967 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 32: /* expr: expr '-' expr  */
#line 594 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new SubExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 2976 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 33: /* expr: expr TOK_REMOVE_FROM rhs  */
#line 600 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));

			ExprPtr lhs = {AdoptRef{}, (yyvsp[-2].expr)};
			ExprPtr rhs = {AdoptRef{}, (yyvsp[0].expr)};
			auto tag1 = (yyvsp[-2].expr)->GetType()->Tag();

			if ( IsArithmetic(tag1) )
				{
				ExprPtr sum = make_intrusive<SubExpr>(lhs, rhs);

				if ( sum->GetType()->Tag() != tag1 )
					sum = make_intrusive<ArithCoerceExpr>(sum, tag1);

				(yyval.expr) = new AssignExpr(lhs, sum, false);
				}
			else
				(yyval.expr) = new RemoveFromExpr(lhs, rhs);
			}
#line 3000 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 34: /* expr: expr '*' expr  */
#line 621 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new TimesExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3009 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 35: /* expr: expr '/' expr  */
#line 627 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new DivideExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3018 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 36: /* expr: expr '%' expr  */
#line 633 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new ModExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3027 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 37: /* expr: expr '&' expr  */
#line 639 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new BitExpr(EXPR_AND, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3036 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 38: /* expr: expr '|' expr  */
#line 645 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new BitExpr(EXPR_OR, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3045 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 39: /* expr: expr '^' expr  */
#line 651 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new BitExpr(EXPR_XOR, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3054 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 40: /* expr: expr TOK_LSHIFT expr  */
#line 657 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new BitExpr(EXPR_LSHIFT, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3063 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 41: /* expr: expr TOK_RSHIFT expr  */
#line 663 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new BitExpr(EXPR_RSHIFT, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3072 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 42: /* expr: expr TOK_AND_AND expr  */
#line 669 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new BoolExpr(EXPR_AND_AND, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3081 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 43: /* expr: expr TOK_OR_OR expr  */
#line 675 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new BoolExpr(EXPR_OR_OR, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3090 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 44: /* expr: expr TOK_EQ expr  */
#line 681 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new EqExpr(EXPR_EQ, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3099 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 45: /* expr: expr TOK_NE expr  */
#line 687 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new EqExpr(EXPR_NE, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3108 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 46: /* expr: expr '<' expr  */
#line 693 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new RelExpr(EXPR_LT, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3117 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 47: /* expr: expr TOK_LE expr  */
#line 699 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new RelExpr(EXPR_LE, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3126 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 48: /* expr: expr '>' expr  */
#line 705 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new RelExpr(EXPR_GT, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3135 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 49: /* expr: expr TOK_GE expr  */
#line 711 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new RelExpr(EXPR_GE, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3144 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 50: /* expr: expr '?' expr ':' expr  */
#line 717 "parse.y"
                        {
			set_location((yylsp[-4]), (yylsp[0]));
			(yyval.expr) = new CondExpr({AdoptRef{}, (yyvsp[-4].expr)}, {AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3153 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 51: /* $@5: %empty  */
#line 723 "parse.y"
                        {
			// Prevent usage of trailing commas on the left-hand
			// side of list expressions (e.g. in table inits).
			if ( (yyvsp[-1].expr)->Tag() == EXPR_LIST && expr_list_has_opt_comma )
				(yyvsp[-1].expr)->Error("incorrect syntax for list expression "
				          "on left-hand side of assignment: "
				          "trailing comma not allowed");
			}
#line 3166 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 52: /* expr: expr '=' $@5 rhs  */
#line 732 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[-1]));

			if ( (yyvsp[-3].expr)->Tag() == EXPR_INDEX && (yyvsp[-3].expr)->AsIndexExpr()->IsSlice() )
				reporter->Error("index slice assignment may not be used"
				                      " in arbitrary expression contexts, only"
				                      " as a statement");

			(yyval.expr) = get_assign_expr({AdoptRef{}, (yyvsp[-3].expr)}, {AdoptRef{}, (yyvsp[0].expr)}, in_init).release();
			}
#line 3181 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 53: /* expr: TOK_WHEN_LOCAL local_id '=' rhs  */
#line 744 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			if ( ! locals_at_this_scope.empty() )
			       locals_at_this_scope.back().insert((yyvsp[-2].id));
			(yyval.expr) = add_and_assign_local({AdoptRef{}, (yyvsp[-2].id)}, {AdoptRef{}, (yyvsp[0].expr)},
			                                        val_mgr->True()).release();
			}
#line 3193 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 54: /* expr: expr '[' expr_list ']'  */
#line 753 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			if ( in_when_cond > 0 )
				(yyval.expr) = new IndexExprWhen({AdoptRef{}, (yyvsp[-3].expr)}, {AdoptRef{}, (yyvsp[-1].list)});
			else
				(yyval.expr) = new IndexExpr({AdoptRef{}, (yyvsp[-3].expr)}, {AdoptRef{}, (yyvsp[-1].list)});
			}
#line 3205 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 56: /* expr: expr '$' TOK_ID  */
#line 764 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new FieldExpr({AdoptRef{}, (yyvsp[-2].expr)}, (yyvsp[0].str));
			}
#line 3214 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 57: /* expr: '$' TOK_ID '=' expr  */
#line 770 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			(yyval.expr) = new FieldAssignExpr((yyvsp[-2].str), {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3223 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 58: /* $@6: %empty  */
#line 776 "parse.y"
                        {
			func_hdr_location = (yylsp[-3]);
			(yyvsp[-1].id)->SetInferReturnType(true);
			}
#line 3232 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 59: /* expr: '$' TOK_ID begin_lambda '=' $@6 lambda_body  */
#line 781 "parse.y"
                        {
			(yyval.expr) = new FieldAssignExpr((yyvsp[-4].str), IntrusivePtr{AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3240 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 60: /* expr: expr TOK_IN expr  */
#line 786 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new InExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3249 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 61: /* expr: expr TOK_NOT_IN expr  */
#line 792 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new NotExpr(make_intrusive<InExpr>(
			        ExprPtr{AdoptRef{}, (yyvsp[-2].expr)},
			        ExprPtr{AdoptRef{}, (yyvsp[0].expr)}));
			}
#line 3260 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 62: /* expr: '[' opt_expr_list ']'  */
#line 800 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));

			bool is_record_ctor = true;

			// If every expression in the list is a field assignment,
			// then treat it as a record constructor, else as a list
			// used for an initializer. Interpret no expressions
			// as an empty record constructor.

			for ( int i = 0; i < (yyvsp[-1].list)->Exprs().length(); ++i )
				{
				if ( (yyvsp[-1].list)->Exprs()[i]->Tag() != EXPR_FIELD_ASSIGN )
					{
					is_record_ctor = false;
					break;
					}
				}

			if ( is_record_ctor )
				(yyval.expr) = new RecordConstructorExpr({AdoptRef{}, (yyvsp[-1].list)});
			else
				(yyval.expr) = (yyvsp[-1].list);
			}
#line 3289 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 63: /* expr: TOK_RECORD '(' expr_list ')'  */
#line 826 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			(yyval.expr) = new RecordConstructorExpr({AdoptRef{}, (yyvsp[-1].list)});
			}
#line 3298 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 64: /* $@7: %empty  */
#line 831 "parse.y"
                              { ++in_init; }
#line 3304 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 65: /* $@8: %empty  */
#line 831 "parse.y"
                                                               { --in_init; }
#line 3310 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 66: /* expr: TOK_TABLE '(' $@7 opt_expr_list ')' $@8 opt_attr  */
#line 833 "parse.y"
                        { // the ++in_init fixes up the parsing of "[x] = y"
			set_location((yylsp[-6]), (yylsp[-2]));
			std::unique_ptr<std::vector<AttrPtr>> attrs{(yyvsp[0].attr_l)};
			(yyval.expr) = new TableConstructorExpr({AdoptRef{}, (yyvsp[-3].list)}, std::move(attrs));
			}
#line 3320 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 67: /* expr: TOK_SET '(' opt_expr_list ')' opt_attr  */
#line 840 "parse.y"
                        {
			set_location((yylsp[-4]), (yylsp[-1]));
			std::unique_ptr<std::vector<AttrPtr>> attrs{(yyvsp[0].attr_l)};
			(yyval.expr) = new SetConstructorExpr({AdoptRef{}, (yyvsp[-2].list)}, std::move(attrs));
			}
#line 3330 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 68: /* expr: TOK_VECTOR '(' opt_expr_list ')'  */
#line 847 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			(yyval.expr) = new VectorConstructorExpr({AdoptRef{}, (yyvsp[-1].list)});
			}
#line 3339 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 69: /* $@9: %empty  */
#line 853 "parse.y"
                        {
			if ( expr_is_table_type_name((yyvsp[-1].expr)) )
				++in_init;
			}
#line 3348 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 70: /* $@10: %empty  */
#line 859 "parse.y"
                        {
			if ( expr_is_table_type_name((yyvsp[-3].expr)) )
				--in_init;
			}
#line 3357 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 71: /* expr: expr '(' $@9 opt_expr_list $@10 ')'  */
#line 865 "parse.y"
                        {
			set_location((yylsp[-5]), (yylsp[0]));

			if ( (yyvsp[-5].expr)->Tag() == EXPR_NAME && (yyvsp[-5].expr)->AsNameExpr()->Id()->IsType() )
				{
				const auto& ctor_type = (yyvsp[-5].expr)->AsNameExpr()->Id()->GetType();

				switch ( ctor_type->Tag() ) {
				case TYPE_RECORD:
					{
					auto rt = cast_intrusive<RecordType>(ctor_type);
					(yyval.expr) = new RecordConstructorExpr(rt, ListExprPtr{AdoptRef{}, (yyvsp[-2].list)});
					}
					break;

				case TYPE_TABLE:
					if ( ctor_type->IsTable() )
						(yyval.expr) = new TableConstructorExpr({AdoptRef{}, (yyvsp[-2].list)}, 0, ctor_type);
					else
						(yyval.expr) = new SetConstructorExpr({AdoptRef{}, (yyvsp[-2].list)}, 0, ctor_type);

					break;

				case TYPE_VECTOR:
					(yyval.expr) = new VectorConstructorExpr({AdoptRef{}, (yyvsp[-2].list)}, ctor_type);
					break;

				default:
					(yyvsp[-5].expr)->Error("constructor type not implemented");
					YYERROR;
				}
				}

			else
				(yyval.expr) = new CallExpr({AdoptRef{}, (yyvsp[-5].expr)}, {AdoptRef{}, (yyvsp[-2].list)}, in_hook > 0, in_when_cond);
			}
#line 3398 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 72: /* $@11: %empty  */
#line 902 "parse.y"
                         { ++in_hook; }
#line 3404 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 73: /* expr: TOK_HOOK $@11 expr  */
#line 903 "parse.y"
                        {
			--in_hook;
			set_location((yylsp[-2]), (yylsp[0]));

			if ( (yyvsp[0].expr)->Tag() != EXPR_CALL )
				(yyvsp[0].expr)->Error("not a valid hook call expression");
			else if ( (yyvsp[0].expr)->AsCallExpr()->Func()->GetType()->AsFuncType()->Flavor() != FUNC_FLAVOR_HOOK )
				(yyvsp[0].expr)->Error("hook keyword should only be used to call hooks");

			(yyval.expr) = (yyvsp[0].expr);
			}
#line 3420 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 74: /* expr: expr TOK_HAS_FIELD TOK_ID  */
#line 916 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new HasFieldExpr({AdoptRef{}, (yyvsp[-2].expr)}, (yyvsp[0].str));
			}
#line 3429 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 76: /* expr: TOK_SCHEDULE expr '{' event '}'  */
#line 924 "parse.y"
                        {
			set_location((yylsp[-4]), (yylsp[0]));
			(yyval.expr) = new ScheduleExpr({AdoptRef{}, (yyvsp[-3].expr)}, {AdoptRef{}, (yyvsp[-1].event_expr)});
			}
#line 3438 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 77: /* expr: TOK_ID  */
#line 930 "parse.y"
                        {
			set_location((yylsp[0]));
			auto id = lookup_ID((yyvsp[0].str), current_module.c_str());

			if ( ! id )
				{
				if ( ! in_debug )
					{
/*	// CHECK THAT THIS IS NOT GLOBAL.
					id = install_ID($1, current_module.c_str(),
							        false, is_export);
*/

					yyerror(util::fmt("unknown identifier %s", (yyvsp[0].str)));
					YYERROR;
					}
				else
					{
					yyerror(util::fmt("unknown identifier %s", (yyvsp[0].str)));
					YYERROR;
					}
				}
			else
				{
				if ( id->IsDeprecated() )
					reporter->Deprecation(id->GetDeprecationWarning());

				if ( id->IsBlank() )
					{
					(yyval.expr) = new NameExpr(std::move(id));
					(yyval.expr)->SetError("blank identifier used in expression");
					}
				else if ( ! id->GetType() )
					{
					id->Error("undeclared variable");
					id->SetType(error_type());
					(yyval.expr) = new NameExpr(std::move(id));
					}

				else if ( id->IsEnumConst() )
					{
					if ( IsErrorType(id->GetType()->Tag()) )
						{
						// The most-relevant error message should already be reported, so
						// just bail out.
						YYERROR;
						}

					EnumType* t = id->GetType()->AsEnumType();
					auto intval = t->Lookup(id->ModuleName(), id->Name());
					if ( intval < 0 )
						reporter->InternalError("enum value not found for %s", id->Name());
					(yyval.expr) = new ConstExpr(t->GetEnumVal(intval));
					}
				else
					{
					if ( out_of_scope_locals.count(id.get()) > 0 )
						id->Error("use of out-of-scope local; move declaration to outer scope");

					(yyval.expr) = new NameExpr(std::move(id));
					}
				}
			}
#line 3506 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 78: /* expr: TOK_CONSTANT  */
#line 995 "parse.y"
                        {
			set_location((yylsp[0]));
			(yyval.expr) = new ConstExpr({AdoptRef{}, (yyvsp[0].val)});
			}
#line 3515 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 79: /* $@12: %empty  */
#line 1000 "parse.y"
                    { begin_RE(); }
#line 3521 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 80: /* expr: '/' $@12 TOK_PATTERN_TEXT TOK_PATTERN_END  */
#line 1001 "parse.y"
                        {
			set_location((yylsp[-1]));

			auto* re = new RE_Matcher((yyvsp[-1].str));
			delete [] (yyvsp[-1].str);

			if ( (yyvsp[0].re_modes).ignore_case )
				re->MakeCaseInsensitive();

			if ( (yyvsp[0].re_modes).single_line )
				re->MakeSingleLine();

			re->Compile();
			(yyval.expr) = new ConstExpr(make_intrusive<PatternVal>(re));
			}
#line 3541 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 81: /* expr: '|' expr '|'  */
#line 1018 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			ExprPtr e{AdoptRef{}, (yyvsp[-1].expr)};
			(yyval.expr) = new SizeExpr(std::move(e));
			}
#line 3551 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 82: /* expr: expr TOK_AS type  */
#line 1025 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new CastExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].type)});
			}
#line 3560 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 83: /* expr: expr TOK_IS type  */
#line 1031 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyval.expr) = new IsExpr({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].type)});
			}
#line 3569 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 84: /* $@13: %empty  */
#line 1037 "parse.y"
                    { ++in_init; }
#line 3575 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 85: /* rhs: '{' $@13 rhs_expr_list '}'  */
#line 1038 "parse.y"
                        {
			--in_init;
			(yyval.expr) = (yyvsp[-1].list);
			}
#line 3584 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 88: /* rhs_expr_list: %empty  */
#line 1047 "parse.y"
                { (yyval.list) = new ListExpr(); }
#line 3590 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 89: /* expr_list: expr_list ',' expr  */
#line 1052 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[0]));
			(yyvsp[-2].list)->Append({AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3599 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 90: /* expr_list: expr  */
#line 1058 "parse.y"
                        {
			set_location((yylsp[0]));
			expr_list_has_opt_comma = 0;
			(yyval.list) = new ListExpr({AdoptRef{}, (yyvsp[0].expr)});
			}
#line 3609 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 92: /* opt_expr_list: %empty  */
#line 1068 "parse.y"
                { (yyval.list) = new ListExpr(); }
#line 3615 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 93: /* enum_body: enum_body_list  */
#line 1073 "parse.y"
                        {
			(yyval.type) = cur_enum_type;
			cur_enum_type = nullptr;
			}
#line 3624 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 94: /* enum_body: enum_body_list ','  */
#line 1079 "parse.y"
                        {
			(yyval.type) = cur_enum_type;
			cur_enum_type = nullptr;
			}
#line 3633 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 97: /* enum_body_elem: TOK_ID '=' TOK_CONSTANT opt_deprecated  */
#line 1098 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[-1]));
			assert(cur_enum_type);

			if ( (yyvsp[-1].val)->GetType()->Tag() != TYPE_COUNT )
				reporter->Error("enumerator is not a count constant");
			else
				cur_enum_type->AddName(current_module, (yyvsp[-3].str),
				                       (yyvsp[-1].val)->InternalUnsigned(), is_export, (yyvsp[0].expr),
				                       in_enum_redef != 0);
			}
#line 3649 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 98: /* enum_body_elem: TOK_ID '=' '-' TOK_CONSTANT  */
#line 1111 "parse.y"
                        {
			// We only accept counts as enumerator, but we want to return a nice
			// error message if users try to use a negative integer (will also
			// catch other cases, but that's fine.)
			reporter->Error("enumerator is not a count constant");
			}
#line 3660 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 99: /* enum_body_elem: TOK_ID opt_deprecated  */
#line 1119 "parse.y"
                        {
			set_location((yylsp[-1]));
			assert(cur_enum_type);
			cur_enum_type->AddName(current_module, (yyvsp[-1].str), is_export, (yyvsp[0].expr),
			                       in_enum_redef != 0);
			}
#line 3671 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 100: /* type: TOK_BOOL  */
#line 1128 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_BOOL)->Ref();
				}
#line 3680 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 101: /* type: TOK_INT  */
#line 1133 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_INT)->Ref();
				}
#line 3689 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 102: /* type: TOK_COUNT  */
#line 1138 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_COUNT)->Ref();
				}
#line 3698 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 103: /* type: TOK_DOUBLE  */
#line 1143 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_DOUBLE)->Ref();
				}
#line 3707 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 104: /* type: TOK_TIME  */
#line 1148 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_TIME)->Ref();
				}
#line 3716 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 105: /* type: TOK_INTERVAL  */
#line 1153 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_INTERVAL)->Ref();
				}
#line 3725 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 106: /* type: TOK_STRING  */
#line 1158 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_STRING)->Ref();
				}
#line 3734 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 107: /* type: TOK_PATTERN  */
#line 1163 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_PATTERN)->Ref();
				}
#line 3743 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 108: /* type: TOK_PORT  */
#line 1168 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_PORT)->Ref();
				}
#line 3752 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 109: /* type: TOK_ADDR  */
#line 1173 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_ADDR)->Ref();
				}
#line 3761 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 110: /* type: TOK_SUBNET  */
#line 1178 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_SUBNET)->Ref();
				}
#line 3770 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 111: /* type: TOK_ANY  */
#line 1183 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = base_type(TYPE_ANY)->Ref();
				}
#line 3779 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 112: /* type: TOK_TABLE '[' type_list ']' TOK_OF type  */
#line 1189 "parse.y"
                                {
				set_location((yylsp[-5]), (yylsp[0]));
				(yyval.type) = new TableType({AdoptRef{}, (yyvsp[-3].type_l)}, {AdoptRef{}, (yyvsp[0].type)});
				}
#line 3788 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 113: /* type: TOK_SET '[' type_list ']'  */
#line 1195 "parse.y"
                                {
				set_location((yylsp[-3]), (yylsp[0]));
				(yyval.type) = new SetType({AdoptRef{}, (yyvsp[-1].type_l)}, nullptr);
				}
#line 3797 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 114: /* $@14: %empty  */
#line 1201 "parse.y"
                        { ++in_record; }
#line 3803 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 115: /* $@15: %empty  */
#line 1203 "parse.y"
                        { --in_record; }
#line 3809 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 116: /* type: TOK_RECORD '{' $@14 type_decl_list $@15 '}'  */
#line 1205 "parse.y"
                                {
				set_location((yylsp[-5]), (yylsp[-1]));
				(yyval.type) = new RecordType((yyvsp[-2].type_decl_l));
				}
#line 3818 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 117: /* $@16: %empty  */
#line 1210 "parse.y"
                             { set_location((yylsp[-1])); parse_new_enum(); }
#line 3824 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 118: /* type: TOK_ENUM '{' $@16 enum_body '}'  */
#line 1211 "parse.y"
                                {
				set_location((yylsp[-4]), (yylsp[0]));
				(yyvsp[-1].type)->UpdateLocationEndInfo((yylsp[0]));
				(yyval.type) = (yyvsp[-1].type);
				}
#line 3834 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 119: /* type: TOK_LIST  */
#line 1218 "parse.y"
                                {
				set_location((yylsp[0]));
				// $$ = new TypeList();
				reporter->Error("list type not implemented");
				(yyval.type) = 0;
				}
#line 3845 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 120: /* type: TOK_LIST TOK_OF type  */
#line 1226 "parse.y"
                                {
				set_location((yylsp[-2]));
				// $$ = new TypeList($3);
				reporter->Error("list type not implemented");
				(yyval.type) = 0;
				}
#line 3856 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 121: /* type: TOK_VECTOR TOK_OF type  */
#line 1234 "parse.y"
                                {
				set_location((yylsp[-2]), (yylsp[0]));
				(yyval.type) = new VectorType({AdoptRef{}, (yyvsp[0].type)});
				}
#line 3865 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 122: /* type: TOK_FUNCTION func_params  */
#line 1240 "parse.y"
                                {
				set_location((yylsp[-1]), (yylsp[0]));
				(yyval.type) = (yyvsp[0].func_type);
				}
#line 3874 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 123: /* type: TOK_EVENT '(' formal_args ')'  */
#line 1246 "parse.y"
                                {
				set_location((yylsp[-3]), (yylsp[-1]));
				(yyval.type) = new FuncType({AdoptRef{}, (yyvsp[-1].record)}, nullptr, FUNC_FLAVOR_EVENT);
				}
#line 3883 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 124: /* type: TOK_HOOK '(' formal_args ')'  */
#line 1252 "parse.y"
                                {
				set_location((yylsp[-3]), (yylsp[-1]));
				(yyval.type) = new FuncType({AdoptRef{}, (yyvsp[-1].record)}, base_type(TYPE_BOOL), FUNC_FLAVOR_HOOK);
				}
#line 3892 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 125: /* type: TOK_FILE TOK_OF type  */
#line 1258 "parse.y"
                                {
				set_location((yylsp[-2]), (yylsp[0]));
				(yyval.type) = new FileType({AdoptRef{}, (yyvsp[0].type)});
				}
#line 3901 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 126: /* type: TOK_FILE  */
#line 1264 "parse.y"
                                {
				set_location((yylsp[0]));
				(yyval.type) = new FileType(base_type(TYPE_STRING));
				}
#line 3910 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 127: /* type: TOK_OPAQUE TOK_OF TOK_ID  */
#line 1270 "parse.y"
                                {
				set_location((yylsp[-2]), (yylsp[0]));
				(yyval.type) = new OpaqueType((yyvsp[0].str));
				}
#line 3919 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 128: /* type: resolve_id  */
#line 1276 "parse.y"
                        {
			if ( ! (yyvsp[0].id) || ! ((yyval.type) = (yyvsp[0].id)->IsType() ? (yyvsp[0].id)->GetType().get() : nullptr) )
				{
				NullStmt here;
				if ( (yyvsp[0].id) )
					(yyvsp[0].id)->Error("not a Zeek type", &here);
				(yyval.type) = error_type()->Ref();
				}
			else
				{
				Ref((yyval.type));

				if ( (yyvsp[0].id)->IsDeprecated() )
					reporter->Deprecation((yyvsp[0].id)->GetDeprecationWarning());
				}
			}
#line 3940 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 129: /* type_list: type_list ',' type  */
#line 1296 "parse.y"
                        { (yyvsp[-2].type_l)->AppendEvenIfNotPure({AdoptRef{}, (yyvsp[0].type)}); }
#line 3946 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 130: /* type_list: type  */
#line 1298 "parse.y"
                        {
			(yyval.type_l) = new TypeList({NewRef{}, (yyvsp[0].type)});
			(yyval.type_l)->Append({AdoptRef{}, (yyvsp[0].type)});
			}
#line 3955 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 131: /* type_decl_list: type_decl_list type_decl  */
#line 1306 "parse.y"
                        {
			(yyvsp[-1].type_decl_l)->push_back((yyvsp[0].type_decl));
			}
#line 3963 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 132: /* type_decl_list: %empty  */
#line 1310 "parse.y"
                        {
			(yyval.type_decl_l) = new type_decl_list();
			}
#line 3971 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 133: /* type_decl: TOK_ID ':' type opt_attr ';'  */
#line 1317 "parse.y"
                        {
			set_location((yylsp[-4]), (yylsp[-1]));
			auto attrs = make_attributes((yyvsp[-1].attr_l), {NewRef{}, (yyvsp[-2].type)}, in_record > 0, false);
			(yyval.type_decl) = new TypeDecl((yyvsp[-4].str), {AdoptRef{}, (yyvsp[-2].type)}, std::move(attrs));

			if ( in_record > 0 && cur_decl_type_id )
				zeekygen_mgr->RecordField(cur_decl_type_id, (yyval.type_decl), ::filename,
				                                        in_record_redef != 0);
			}
#line 3985 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 134: /* formal_args: formal_args_decl_list  */
#line 1330 "parse.y"
                        { (yyval.record) = new RecordType((yyvsp[0].type_decl_l)); }
#line 3991 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 135: /* formal_args: formal_args_decl_list ';'  */
#line 1332 "parse.y"
                        { (yyval.record) = new RecordType((yyvsp[-1].type_decl_l)); }
#line 3997 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 136: /* formal_args: %empty  */
#line 1334 "parse.y"
                        { (yyval.record) = new RecordType(new type_decl_list()); }
#line 4003 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 137: /* formal_args_decl_list: formal_args_decl_list ';' formal_args_decl  */
#line 1339 "parse.y"
                        { (yyvsp[-2].type_decl_l)->push_back((yyvsp[0].type_decl)); }
#line 4009 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 138: /* formal_args_decl_list: formal_args_decl_list ',' formal_args_decl  */
#line 1341 "parse.y"
                        { (yyvsp[-2].type_decl_l)->push_back((yyvsp[0].type_decl)); }
#line 4015 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 139: /* formal_args_decl_list: formal_args_decl  */
#line 1343 "parse.y"
                        { (yyval.type_decl_l) = new type_decl_list(); (yyval.type_decl_l)->push_back((yyvsp[0].type_decl)); }
#line 4021 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 140: /* formal_args_decl: TOK_ID ':' type opt_attr  */
#line 1348 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			auto attrs = make_attributes((yyvsp[0].attr_l), {NewRef{}, (yyvsp[-1].type)}, true, false);
			(yyval.type_decl) = new TypeDecl((yyvsp[-3].str), {AdoptRef{}, (yyvsp[-1].type)}, std::move(attrs));
			}
#line 4031 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 141: /* decl: TOK_MODULE TOK_ID ';'  */
#line 1357 "parse.y"
                        {
			current_module = (yyvsp[-1].str);
			module_names.insert((yyvsp[-1].str));
			zeekygen_mgr->ModuleUsage(::filename, current_module);
			}
#line 4041 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 142: /* $@17: %empty  */
#line 1363 "parse.y"
                               { is_export = true; }
#line 4047 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 143: /* decl: TOK_EXPORT '{' $@17 decl_list '}'  */
#line 1364 "parse.y"
                        { is_export = false; }
#line 4053 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 144: /* decl: TOK_GLOBAL def_global_id opt_type init_class opt_init opt_attr ';'  */
#line 1367 "parse.y"
                        {
			build_global((yyvsp[-5].id), (yyvsp[-4].type), (yyvsp[-3].ic), (yyvsp[-2].expr), (yyvsp[-1].attr_l), VAR_REGULAR);
			}
#line 4061 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 145: /* decl: TOK_OPTION def_global_id opt_type init_class opt_init opt_attr ';'  */
#line 1372 "parse.y"
                        {
			if ( (yyvsp[-5].id)->IsBlank() )
				(yyvsp[-5].id)->Error("blank identifier used as option");
			else
				build_global((yyvsp[-5].id), (yyvsp[-4].type), (yyvsp[-3].ic), (yyvsp[-2].expr), (yyvsp[-1].attr_l), VAR_OPTION);
			}
#line 4072 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 146: /* decl: TOK_CONST def_global_id opt_type init_class opt_init opt_attr ';'  */
#line 1380 "parse.y"
                        {
			build_global((yyvsp[-5].id), (yyvsp[-4].type), (yyvsp[-3].ic), (yyvsp[-2].expr), (yyvsp[-1].attr_l), VAR_CONST);
			}
#line 4080 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 147: /* $@18: %empty  */
#line 1384 "parse.y"
                                    {
			if ( (yyvsp[0].id)->IsType() )
				{
				auto tag = (yyvsp[0].id)->GetType()->Tag();
				auto tstr = type_name(tag);
				if ( tag == TYPE_RECORD || tag == TYPE_ENUM )
					yyerror(zeek::util::fmt("redef of %s type %s is missing %s keyword",
								tstr, (yyvsp[0].id)->Name(), tstr));
				else
					yyerror(zeek::util::fmt("can not redef %s type %s", tstr, (yyvsp[0].id)->Name()));

				YYERROR;  // bail
				}
		}
#line 4099 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 148: /* decl: TOK_REDEF global_id $@18 opt_type init_class opt_init opt_attr ';'  */
#line 1398 "parse.y"
                        {
			build_global((yyvsp[-6].id), (yyvsp[-4].type), (yyvsp[-3].ic), (yyvsp[-2].expr), (yyvsp[-1].attr_l), VAR_REDEF);
			}
#line 4107 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 149: /* $@19: %empty  */
#line 1403 "parse.y"
                        { ++in_enum_redef; parse_redef_enum((yyvsp[-2].id)); zeekygen_mgr->Redef((yyvsp[-2].id), ::filename); }
#line 4113 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 150: /* decl: TOK_REDEF TOK_ENUM global_id TOK_ADD_TO '{' $@19 enum_body '}' ';'  */
#line 1405 "parse.y"
                        {
			--in_enum_redef;
			// Zeekygen already grabbed new enum IDs as the type created them.
			}
#line 4122 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 151: /* $@20: %empty  */
#line 1411 "parse.y"
                        { cur_decl_type_id = (yyvsp[-2].id); zeekygen_mgr->Redef((yyvsp[-2].id), ::filename, INIT_EXTRA); }
#line 4128 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 152: /* decl: TOK_REDEF TOK_RECORD global_id '$' TOK_ID $@20 TOK_ADD_TO '{' attr_list '}' ';'  */
#line 1413 "parse.y"
                        {
			cur_decl_type_id = 0;
			parse_redef_record_field((yyvsp[-8].id), (yyvsp[-6].str), INIT_EXTRA, std::unique_ptr<std::vector<AttrPtr>>((yyvsp[-2].attr_l)));
			}
#line 4137 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 153: /* $@21: %empty  */
#line 1418 "parse.y"
                        { cur_decl_type_id = (yyvsp[-2].id); zeekygen_mgr->Redef((yyvsp[-2].id), ::filename, INIT_REMOVE); }
#line 4143 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 154: /* decl: TOK_REDEF TOK_RECORD global_id '$' TOK_ID $@21 TOK_REMOVE_FROM '{' attr_list '}' ';'  */
#line 1420 "parse.y"
                        {
			cur_decl_type_id = 0;
			parse_redef_record_field((yyvsp[-8].id), (yyvsp[-6].str), INIT_REMOVE, std::unique_ptr<std::vector<AttrPtr>>((yyvsp[-2].attr_l)));
			}
#line 4152 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 155: /* $@22: %empty  */
#line 1425 "parse.y"
                        { cur_decl_type_id = (yyvsp[0].id); zeekygen_mgr->Redef((yyvsp[0].id), ::filename); }
#line 4158 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 156: /* $@23: %empty  */
#line 1427 "parse.y"
                        { ++in_record; ++in_record_redef; }
#line 4164 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 157: /* $@24: %empty  */
#line 1429 "parse.y"
                        { --in_record; --in_record_redef; }
#line 4170 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 158: /* decl: TOK_REDEF TOK_RECORD global_id $@22 TOK_ADD_TO '{' $@23 type_decl_list $@24 '}' opt_attr ';'  */
#line 1431 "parse.y"
                        {
			cur_decl_type_id = 0;

			if ( ! (yyvsp[-9].id)->GetType() )
				(yyvsp[-9].id)->Error("unknown identifier");
			else
				extend_record((yyvsp[-9].id), std::unique_ptr<type_decl_list>((yyvsp[-4].type_decl_l)),
				              std::unique_ptr<std::vector<AttrPtr>>((yyvsp[-1].attr_l)));
			}
#line 4184 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 159: /* $@25: %empty  */
#line 1442 "parse.y"
                        { cur_decl_type_id = (yyvsp[-1].id); zeekygen_mgr->StartType({NewRef{}, (yyvsp[-1].id)});  }
#line 4190 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 160: /* decl: TOK_TYPE def_global_id ':' $@25 type opt_attr ';'  */
#line 1444 "parse.y"
                        {
			cur_decl_type_id = 0;
			IntrusivePtr id{AdoptRef{}, (yyvsp[-5].id)};
			add_type(id.get(), {AdoptRef{}, (yyvsp[-2].type)},
			                       std::unique_ptr<std::vector<AttrPtr>>{(yyvsp[-1].attr_l)});
			zeekygen_mgr->Identifier(std::move(id));
			}
#line 4202 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 161: /* $@26: %empty  */
#line 1453 "parse.y"
                        {
			func_hdr_location = (yylsp[0]);
			func_hdr_cond_epoch = conditional_epoch;
			}
#line 4211 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 166: /* conditional: TOK_ATIF '(' expr ')'  */
#line 1468 "parse.y"
                        { do_atif((yyvsp[-1].expr)); }
#line 4217 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 167: /* conditional: TOK_ATIFDEF '(' TOK_ID ')'  */
#line 1470 "parse.y"
                        { do_atifdef((yyvsp[-1].str)); }
#line 4223 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 168: /* conditional: TOK_ATIFNDEF '(' TOK_ID ')'  */
#line 1472 "parse.y"
                        { do_atifndef((yyvsp[-1].str)); }
#line 4229 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 169: /* conditional: TOK_ATENDIF  */
#line 1474 "parse.y"
                        { do_atendif(); }
#line 4235 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 170: /* conditional: TOK_ATELSE  */
#line 1476 "parse.y"
                        { do_atelse(); }
#line 4241 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 171: /* func_hdr: TOK_FUNCTION def_global_id func_params opt_attr  */
#line 1481 "parse.y"
                        {
			IntrusivePtr id{AdoptRef{}, (yyvsp[-2].id)};
			begin_func(id, current_module.c_str(),
				                     FUNC_FLAVOR_FUNCTION, false, {NewRef{}, (yyvsp[-1].func_type)},
			                         std::unique_ptr<std::vector<AttrPtr>>{(yyvsp[0].attr_l)});
			(yyval.func_type) = (yyvsp[-1].func_type);
			zeekygen_mgr->Identifier(std::move(id));
			}
#line 4254 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 172: /* func_hdr: TOK_EVENT event_id func_params opt_attr  */
#line 1490 "parse.y"
                        {
			begin_func({NewRef{}, (yyvsp[-2].id)}, current_module.c_str(),
				                     FUNC_FLAVOR_EVENT, false, {NewRef{}, (yyvsp[-1].func_type)},
			                         std::unique_ptr<std::vector<AttrPtr>>{(yyvsp[0].attr_l)});
			(yyval.func_type) = (yyvsp[-1].func_type);
			}
#line 4265 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 173: /* func_hdr: TOK_HOOK def_global_id func_params opt_attr  */
#line 1497 "parse.y"
                        {
			(yyvsp[-1].func_type)->ClearYieldType(FUNC_FLAVOR_HOOK);
			(yyvsp[-1].func_type)->SetYieldType(base_type(TYPE_BOOL));
			begin_func({NewRef{}, (yyvsp[-2].id)}, current_module.c_str(),
				                     FUNC_FLAVOR_HOOK, false, {NewRef{}, (yyvsp[-1].func_type)},
			                         std::unique_ptr<std::vector<AttrPtr>>{(yyvsp[0].attr_l)});
			(yyval.func_type) = (yyvsp[-1].func_type);
			}
#line 4278 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 174: /* func_hdr: TOK_REDEF TOK_EVENT event_id func_params opt_attr  */
#line 1506 "parse.y"
                        {
			begin_func({NewRef{}, (yyvsp[-2].id)}, current_module.c_str(),
				                     FUNC_FLAVOR_EVENT, true, {NewRef{}, (yyvsp[-1].func_type)},
			                         std::unique_ptr<std::vector<AttrPtr>>{(yyvsp[0].attr_l)});
			(yyval.func_type) = (yyvsp[-1].func_type);
			}
#line 4289 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 175: /* $@27: %empty  */
#line 1516 "parse.y"
                        {
			saved_in_init.push_back(in_init);
			in_init = 0;

			locals_at_this_scope.clear();
			out_of_scope_locals.clear();
			}
#line 4301 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 176: /* $@28: %empty  */
#line 1525 "parse.y"
                        {
			in_init = saved_in_init.back();
			saved_in_init.pop_back();
			}
#line 4310 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 177: /* func_body: '{' $@27 stmt_list $@28 '}'  */
#line 1531 "parse.y"
                        {
			set_location(func_hdr_location, (yylsp[0]));

			bool free_of_conditionals = true;
			if ( current_file_has_conditionals ||
			     conditional_epoch > func_hdr_cond_epoch )
				free_of_conditionals = false;

			end_func({AdoptRef{}, (yyvsp[-2].stmt)}, current_module.c_str(), free_of_conditionals);
			}
#line 4325 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 178: /* $@29: %empty  */
#line 1545 "parse.y"
                        {
			saved_in_init.push_back(in_init);
			in_init = 0;
			}
#line 4334 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 179: /* $@30: %empty  */
#line 1551 "parse.y"
                        {
			in_init = saved_in_init.back();
			saved_in_init.pop_back();
			}
#line 4343 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 180: /* lambda_body: '{' $@29 stmt_list $@30 '}'  */
#line 1557 "parse.y"
                        {
			set_location((yylsp[-4]), (yylsp[0]));

			// Code duplication here is sad but needed.
			// end_func actually instantiates the function
			// and associates it with an ID. We perform that
			// association later and need to return a lambda
			// expression.

			// Gather the ingredients for a Func from the
			// current scope.
			auto ingredients = std::make_unique<FunctionIngredients>(
				current_scope(), IntrusivePtr{AdoptRef{}, (yyvsp[-2].stmt)}, current_module.c_str());
			auto outer_ids = gather_outer_ids(pop_scope(), ingredients->Body());

			(yyval.expr) = new LambdaExpr(std::move(ingredients), std::move(outer_ids));
			}
#line 4365 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 181: /* anonymous_function: TOK_FUNCTION begin_lambda conditional_list lambda_body  */
#line 1578 "parse.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 4371 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 182: /* begin_lambda: opt_captures func_params  */
#line 1583 "parse.y"
                        {
			auto id = current_scope()->GenerateTemporary("anonymous-function");
			begin_func(id, current_module.c_str(), FUNC_FLAVOR_FUNCTION, false, {AdoptRef{}, (yyvsp[0].func_type)});

			std::optional<FuncType::CaptureList> captures;

			if ( (yyvsp[-1].captures) )
				{
				captures = *(yyvsp[-1].captures);
				delete (yyvsp[-1].captures);
				}

			(yyvsp[0].func_type)->SetCaptures(std::move(captures));
			(yyval.id) = id.release();
			}
#line 4391 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 183: /* opt_captures: '[' capture_list ']'  */
#line 1602 "parse.y"
                        { (yyval.captures) = (yyvsp[-1].captures); }
#line 4397 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 184: /* opt_captures: %empty  */
#line 1604 "parse.y"
                        { (yyval.captures) = nullptr; }
#line 4403 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 185: /* capture_list: capture_list ',' capture  */
#line 1609 "parse.y"
                        {
			(yyvsp[-2].captures)->push_back(*(yyvsp[0].capture));
			delete (yyvsp[0].capture);
			}
#line 4412 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 186: /* capture_list: capture  */
#line 1614 "parse.y"
                        {
			(yyval.captures) = new zeek::FuncType::CaptureList;
			(yyval.captures)->push_back(*(yyvsp[0].capture));
			delete (yyvsp[0].capture);
			}
#line 4422 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 187: /* capture: opt_deep TOK_ID  */
#line 1623 "parse.y"
                        {
			set_location((yylsp[0]));
			auto id = lookup_ID((yyvsp[0].str), current_module.c_str());

			if ( ! id )
				reporter->Error("no such local identifier: %s", (yyvsp[0].str));
			else if ( id->IsType() )
				{
				reporter->Error("cannot specify type in capture: %s", (yyvsp[0].str));
				id = nullptr;
				}
			else if ( id->IsGlobal() )
				{
				reporter->Error("cannot specify global in capture: %s", (yyvsp[0].str));
				id = nullptr;
				}

			delete [] (yyvsp[0].str);

			(yyval.capture) = new FuncType::Capture;
			(yyval.capture)->id = id;
			(yyval.capture)->deep_copy = (yyvsp[-1].b);
			}
#line 4450 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 188: /* opt_deep: TOK_COPY  */
#line 1649 "parse.y"
                        { (yyval.b) = true; }
#line 4456 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 189: /* opt_deep: %empty  */
#line 1651 "parse.y"
                        { (yyval.b) = false; }
#line 4462 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 190: /* func_params: '(' formal_args ')' ':' type  */
#line 1656 "parse.y"
                        { (yyval.func_type) = new FuncType({AdoptRef{}, (yyvsp[-3].record)}, {AdoptRef{}, (yyvsp[0].type)}, FUNC_FLAVOR_FUNCTION); }
#line 4468 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 191: /* func_params: '(' formal_args ')'  */
#line 1658 "parse.y"
                        { (yyval.func_type) = new FuncType({AdoptRef{}, (yyvsp[-1].record)}, base_type(TYPE_VOID), FUNC_FLAVOR_FUNCTION); }
#line 4474 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 192: /* opt_type: ':' type  */
#line 1663 "parse.y"
                        { (yyval.type) = (yyvsp[0].type); }
#line 4480 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 193: /* opt_type: %empty  */
#line 1665 "parse.y"
                        { (yyval.type) = 0; }
#line 4486 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 194: /* init_class: %empty  */
#line 1669 "parse.y"
                                { (yyval.ic) = INIT_NONE; }
#line 4492 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 195: /* init_class: '='  */
#line 1670 "parse.y"
                                { (yyval.ic) = INIT_FULL; }
#line 4498 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 196: /* init_class: TOK_ADD_TO  */
#line 1671 "parse.y"
                                { (yyval.ic) = INIT_EXTRA; }
#line 4504 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 197: /* init_class: TOK_REMOVE_FROM  */
#line 1672 "parse.y"
                                { (yyval.ic) = INIT_REMOVE; }
#line 4510 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 198: /* $@31: %empty  */
#line 1676 "parse.y"
                { ++in_init; }
#line 4516 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 199: /* $@32: %empty  */
#line 1676 "parse.y"
                                   { --in_init; }
#line 4522 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 200: /* opt_init: $@31 rhs $@32  */
#line 1677 "parse.y"
                        { (yyval.expr) = (yyvsp[-1].expr); }
#line 4528 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 201: /* opt_init: %empty  */
#line 1679 "parse.y"
                        { (yyval.expr) = 0; }
#line 4534 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 202: /* index_slice: expr '[' opt_expr ':' opt_expr ']'  */
#line 1684 "parse.y"
                        {
			set_location((yylsp[-5]), (yylsp[0]));

			auto low = (yyvsp[-3].expr) ? ExprPtr{AdoptRef{}, (yyvsp[-3].expr)} :
			                make_intrusive<ConstExpr>(val_mgr->Count(0));

			auto high = (yyvsp[-1].expr) ? ExprPtr{AdoptRef{}, (yyvsp[-1].expr)} :
			                 make_intrusive<SizeExpr>(
			                     ExprPtr{NewRef{}, (yyvsp[-5].expr)});

			if ( ! IsIntegral(low->GetType()->Tag()) || ! IsIntegral(high->GetType()->Tag()) )
				reporter->Error("slice notation must have integral values as indexes");

			auto le = make_intrusive<ListExpr>(std::move(low));
			le->Append(std::move(high));

			if ( in_when_cond > 0  )
				(yyval.expr) = new IndexExprWhen({AdoptRef{}, (yyvsp[-5].expr)}, std::move(le), true);
			else
				(yyval.expr) = new IndexExpr({AdoptRef{}, (yyvsp[-5].expr)}, std::move(le), true);
			}
#line 4560 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 204: /* opt_attr: %empty  */
#line 1709 "parse.y"
                        { (yyval.attr_l) = nullptr; }
#line 4566 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 205: /* attr_list: attr_list attr  */
#line 1714 "parse.y"
                        { (yyvsp[-1].attr_l)->emplace_back(AdoptRef{}, (yyvsp[0].attr)); }
#line 4572 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 206: /* attr_list: attr  */
#line 1716 "parse.y"
                        {
			(yyval.attr_l) = new std::vector<AttrPtr>;
			(yyval.attr_l)->emplace_back(AdoptRef{}, (yyvsp[0].attr));
			}
#line 4581 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 207: /* attr: TOK_ATTR_DEFAULT '=' expr  */
#line 1724 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_DEFAULT, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4587 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 208: /* attr: TOK_ATTR_OPTIONAL  */
#line 1726 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_OPTIONAL); }
#line 4593 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 209: /* attr: TOK_ATTR_REDEF  */
#line 1728 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_REDEF); }
#line 4599 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 210: /* attr: TOK_ATTR_IS_ASSIGNED  */
#line 1730 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_IS_ASSIGNED); }
#line 4605 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 211: /* attr: TOK_ATTR_IS_USED  */
#line 1732 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_IS_USED); }
#line 4611 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 212: /* attr: TOK_ATTR_ADD_FUNC '=' expr  */
#line 1734 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_ADD_FUNC, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4617 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 213: /* attr: TOK_ATTR_DEL_FUNC '=' expr  */
#line 1736 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_DEL_FUNC, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4623 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 214: /* attr: TOK_ATTR_ON_CHANGE '=' expr  */
#line 1738 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_ON_CHANGE, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4629 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 215: /* attr: TOK_ATTR_BROKER_STORE '=' expr  */
#line 1740 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_BROKER_STORE, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4635 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 216: /* attr: TOK_ATTR_BROKER_STORE_ALLOW_COMPLEX  */
#line 1742 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_BROKER_STORE_ALLOW_COMPLEX); }
#line 4641 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 217: /* attr: TOK_ATTR_BACKEND '=' expr  */
#line 1744 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_BACKEND, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4647 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 218: /* attr: TOK_ATTR_EXPIRE_FUNC '=' expr  */
#line 1746 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_EXPIRE_FUNC, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4653 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 219: /* attr: TOK_ATTR_EXPIRE_CREATE '=' expr  */
#line 1748 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_EXPIRE_CREATE, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4659 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 220: /* attr: TOK_ATTR_EXPIRE_READ '=' expr  */
#line 1750 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_EXPIRE_READ, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4665 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 221: /* attr: TOK_ATTR_EXPIRE_WRITE '=' expr  */
#line 1752 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_EXPIRE_WRITE, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4671 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 222: /* attr: TOK_ATTR_RAW_OUTPUT  */
#line 1754 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_RAW_OUTPUT); }
#line 4677 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 223: /* attr: TOK_ATTR_PRIORITY '=' expr  */
#line 1756 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_PRIORITY, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4683 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 224: /* attr: TOK_ATTR_GROUP '=' expr  */
#line 1758 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_GROUP, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4689 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 225: /* attr: TOK_ATTR_TYPE_COLUMN '=' expr  */
#line 1760 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_TYPE_COLUMN, {AdoptRef{}, (yyvsp[0].expr)}); }
#line 4695 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 226: /* attr: TOK_ATTR_LOG  */
#line 1762 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_LOG); }
#line 4701 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 227: /* attr: TOK_ATTR_ERROR_HANDLER  */
#line 1764 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_ERROR_HANDLER); }
#line 4707 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 228: /* attr: TOK_ATTR_DEPRECATED  */
#line 1766 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_DEPRECATED); }
#line 4713 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 229: /* attr: TOK_ATTR_DEPRECATED '=' TOK_CONSTANT  */
#line 1768 "parse.y"
                        {
			if ( IsString((yyvsp[0].val)->GetType()->Tag()) )
				(yyval.attr) = new Attr(
					ATTR_DEPRECATED,
					make_intrusive<ConstExpr>(IntrusivePtr{AdoptRef{}, (yyvsp[0].val)}));
			else
				{
				ODesc d;
				(yyvsp[0].val)->Describe(&d);
				Unref((yyvsp[0].val));
				reporter->Error("'&deprecated=%s' must use a string literal",
				                      d.Description());
				(yyval.attr) = new Attr(ATTR_DEPRECATED);
				}
			}
#line 4733 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 230: /* attr: TOK_ATTR_ORDERED  */
#line 1784 "parse.y"
                        { (yyval.attr) = new Attr(ATTR_ORDERED); }
#line 4739 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 231: /* $@33: %empty  */
#line 1789 "parse.y"
                        {
			std::set<const ID*> id_set;
			locals_at_this_scope.emplace_back(id_set);
			}
#line 4748 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 232: /* stmt: '{' $@33 opt_no_test_block stmt_list '}'  */
#line 1794 "parse.y"
                        {
			auto& scope_locals = locals_at_this_scope.back();
			out_of_scope_locals.insert(scope_locals.begin(), scope_locals.end());
			locals_at_this_scope.pop_back();

			set_location((yylsp[-4]), (yylsp[0]));
			(yyval.stmt) = (yyvsp[-1].stmt);
			if ( (yyvsp[-2].b) )
			    script_coverage_mgr.DecIgnoreDepth();
			}
#line 4763 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 233: /* stmt: TOK_PRINT expr_list ';' opt_no_test  */
#line 1806 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[-1]));
			(yyval.stmt) = new PrintStmt(IntrusivePtr{AdoptRef{}, (yyvsp[-2].list)});
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4774 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 234: /* stmt: TOK_EVENT event ';' opt_no_test  */
#line 1814 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[-1]));
			(yyval.stmt) = new EventStmt({AdoptRef{}, (yyvsp[-2].event_expr)});
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4785 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 235: /* stmt: TOK_IF '(' expr ')' stmt  */
#line 1822 "parse.y"
                        {
			reject_directive((yyvsp[0].stmt));
			set_location((yylsp[-4]), (yylsp[-1]));
			(yyval.stmt) = new IfStmt({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].stmt)}, make_intrusive<NullStmt>());
			script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4796 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 236: /* stmt: TOK_IF '(' expr ')' stmt TOK_ELSE stmt  */
#line 1830 "parse.y"
                        {
			reject_directive((yyvsp[-2].stmt));
			reject_directive((yyvsp[0].stmt));
			set_location((yylsp[-6]), (yylsp[-3]));
			(yyval.stmt) = new IfStmt({AdoptRef{}, (yyvsp[-4].expr)}, {AdoptRef{}, (yyvsp[-2].stmt)}, {AdoptRef{}, (yyvsp[0].stmt)});
			script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4808 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 237: /* stmt: TOK_SWITCH expr '{' case_list '}'  */
#line 1839 "parse.y"
                        {
			set_location((yylsp[-4]), (yylsp[-3]));
			(yyval.stmt) = new SwitchStmt({AdoptRef{}, (yyvsp[-3].expr)}, (yyvsp[-1].case_l));
			script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4818 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 238: /* stmt: for_head stmt  */
#line 1846 "parse.y"
                        {
			reject_directive((yyvsp[0].stmt));
			(yyvsp[-1].stmt)->AsForStmt()->AddBody({AdoptRef{}, (yyvsp[0].stmt)});
			script_coverage_mgr.AddStmt((yyvsp[-1].stmt));
			}
#line 4828 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 239: /* stmt: TOK_WHILE '(' expr ')' stmt  */
#line 1853 "parse.y"
                        {
			reject_directive((yyvsp[0].stmt));
			(yyval.stmt) = new WhileStmt({AdoptRef{}, (yyvsp[-2].expr)}, {AdoptRef{}, (yyvsp[0].stmt)});
			script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4838 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 240: /* stmt: TOK_NEXT ';' opt_no_test  */
#line 1860 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[-1]));
			(yyval.stmt) = new NextStmt;
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4849 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 241: /* stmt: TOK_BREAK ';' opt_no_test  */
#line 1868 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[-1]));
			(yyval.stmt) = new BreakStmt;
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4860 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 242: /* stmt: TOK_FALLTHROUGH ';' opt_no_test  */
#line 1876 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[-1]));
			(yyval.stmt) = new FallthroughStmt;
			if ( ! (yyvsp[0].b) )
				script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4871 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 243: /* stmt: TOK_RETURN ';' opt_no_test  */
#line 1884 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[-1]));
			(yyval.stmt) = new ReturnStmt(0);
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4882 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 244: /* stmt: TOK_RETURN expr ';' opt_no_test  */
#line 1892 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[-2]));
			(yyval.stmt) = new ReturnStmt({AdoptRef{}, (yyvsp[-2].expr)});
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4893 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 245: /* stmt: TOK_ADD expr ';' opt_no_test  */
#line 1900 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[-1]));
			(yyval.stmt) = new AddStmt({AdoptRef{}, (yyvsp[-2].expr)});
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4904 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 246: /* stmt: TOK_DELETE expr ';' opt_no_test  */
#line 1908 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[-1]));
			(yyval.stmt) = new DelStmt({AdoptRef{}, (yyvsp[-2].expr)});
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4915 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 247: /* stmt: TOK_LOCAL local_id opt_type init_class opt_init opt_attr ';' opt_no_test  */
#line 1916 "parse.y"
                        {
			set_location((yylsp[-7]), (yylsp[-1]));
			if ( ! locals_at_this_scope.empty() )
			       locals_at_this_scope.back().insert((yyvsp[-6].id));
			(yyval.stmt) = build_local((yyvsp[-6].id), (yyvsp[-5].type), (yyvsp[-4].ic), (yyvsp[-3].expr), (yyvsp[-2].attr_l), VAR_REGULAR, ! (yyvsp[0].b)).release();
			}
#line 4926 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 248: /* stmt: TOK_CONST local_id opt_type init_class opt_init opt_attr ';' opt_no_test  */
#line 1924 "parse.y"
                        {
			set_location((yylsp[-7]), (yylsp[-2]));

			(yyval.stmt) = build_local((yyvsp[-6].id), (yyvsp[-5].type), (yyvsp[-4].ic), (yyvsp[-3].expr), (yyvsp[-2].attr_l), VAR_CONST, ! (yyvsp[0].b)).release();
			}
#line 4936 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 249: /* stmt: when_clause  */
#line 1931 "parse.y"
                        {
			(yyval.stmt) = new WhenStmt((yyvsp[0].when_clause));
			script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4945 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 250: /* stmt: index_slice '=' expr ';' opt_no_test  */
#line 1937 "parse.y"
                        {
			set_location((yylsp[-4]), (yylsp[-1]));
			(yyval.stmt) = new ExprStmt(get_assign_expr({AdoptRef{}, (yyvsp[-4].expr)},
			                                  {AdoptRef{}, (yyvsp[-2].expr)}, in_init));

			if ( ! (yyvsp[0].b) )
				script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4958 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 251: /* stmt: expr ';' opt_no_test  */
#line 1947 "parse.y"
                        {
			set_location((yylsp[-2]), (yylsp[-1]));
			(yyval.stmt) = new ExprStmt({AdoptRef{}, (yyvsp[-2].expr)});
			if ( ! (yyvsp[0].b) )
			    script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4969 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 252: /* stmt: ';'  */
#line 1955 "parse.y"
                        {
			set_location((yylsp[0]), (yylsp[0]));
			(yyval.stmt) = new NullStmt;
			script_coverage_mgr.AddStmt((yyval.stmt));
			}
#line 4979 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 253: /* stmt: conditional  */
#line 1962 "parse.y"
                        { (yyval.stmt) = new NullStmt(true /* is_directive */); }
#line 4985 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 254: /* stmt_list: stmt_list stmt  */
#line 1967 "parse.y"
                        {
			set_location((yylsp[-1]), (yylsp[0]));
			(yyvsp[-1].stmt)->AsStmtList()->Stmts().push_back((yyvsp[0].stmt));
			(yyvsp[-1].stmt)->UpdateLocationEndInfo((yylsp[0]));
			}
#line 4995 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 255: /* stmt_list: %empty  */
#line 1973 "parse.y"
                        { (yyval.stmt) = new StmtList(); }
#line 5001 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 256: /* event: TOK_ID '(' opt_expr_list ')'  */
#line 1978 "parse.y"
                        {
			set_location((yylsp[-3]), (yylsp[0]));
			const auto& id = lookup_ID((yyvsp[-3].str), current_module.c_str());

			if ( id )
				{
				if ( ! id->IsGlobal() )
					{
					yyerror(util::fmt("local identifier \"%s\" cannot be used to reference an event", (yyvsp[-3].str)));
					YYERROR;
					}

				if ( id->IsDeprecated() )
					reporter->Deprecation(id->GetDeprecationWarning());

				(yyval.event_expr) = new EventExpr(id->Name(), {AdoptRef{}, (yyvsp[-1].list)});
				}
			else
				{
				(yyval.event_expr) = new EventExpr((yyvsp[-3].str), {AdoptRef{}, (yyvsp[-1].list)});
				}
			}
#line 5028 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 257: /* case_list: case_list case  */
#line 2004 "parse.y"
                        { (yyvsp[-1].case_l)->push_back((yyvsp[0].c_case)); }
#line 5034 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 258: /* case_list: %empty  */
#line 2006 "parse.y"
                        { (yyval.case_l) = new case_list; }
#line 5040 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 259: /* case: TOK_CASE expr_list ':' stmt_list  */
#line 2011 "parse.y"
                        { (yyval.c_case) = new Case({AdoptRef{}, (yyvsp[-2].list)}, nullptr, {AdoptRef{}, (yyvsp[0].stmt)}); }
#line 5046 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 260: /* case: TOK_CASE case_type_list ':' stmt_list  */
#line 2014 "parse.y"
                        { (yyval.c_case) = new Case(nullptr, (yyvsp[-2].id_l), {AdoptRef{}, (yyvsp[0].stmt)}); }
#line 5052 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 261: /* case: TOK_DEFAULT ':' stmt_list  */
#line 2017 "parse.y"
                        { (yyval.c_case) = new Case(nullptr, nullptr, {AdoptRef{}, (yyvsp[0].stmt)}); }
#line 5058 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 262: /* case_type_list: case_type_list ',' case_type  */
#line 2022 "parse.y"
                        { (yyvsp[-2].id_l)->push_back((yyvsp[0].id)); }
#line 5064 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 263: /* case_type_list: case_type  */
#line 2025 "parse.y"
                        {
			(yyval.id_l) = new IDPList;
			(yyval.id_l)->push_back((yyvsp[0].id));
			}
#line 5073 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 264: /* case_type: TOK_TYPE type  */
#line 2033 "parse.y"
                        {
			(yyval.id) = new ID(0, SCOPE_FUNCTION, 0);
			(yyval.id)->SetType({AdoptRef{}, (yyvsp[0].type)});
			}
#line 5082 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 265: /* case_type: TOK_TYPE type TOK_AS TOK_ID  */
#line 2039 "parse.y"
                        {
			const char* name = (yyvsp[0].str);
			TypePtr type{AdoptRef{}, (yyvsp[-2].type)};
			auto case_var = lookup_ID(name, current_module.c_str());

			if ( case_var && case_var->IsGlobal() )
				case_var->Error("already a global identifier");
			else
				case_var = install_ID(name, current_module.c_str(), false, false);

			add_local(case_var, std::move(type), INIT_NONE, nullptr, nullptr,
			                        VAR_REGULAR);
			(yyval.id) = case_var.release();
			}
#line 5101 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 266: /* for_head: TOK_FOR '(' TOK_ID TOK_IN expr ')'  */
#line 2056 "parse.y"
                        {
			set_location((yylsp[-5]), (yylsp[0]));

			// This rule needs to be separate from the loop
			// body so that we execute these actions - defining
			// the local variable - prior to parsing the body,
			// which might refer to the variable.
			auto loop_var = lookup_ID((yyvsp[-3].str), current_module.c_str());

			if ( loop_var )
				check_loop_var(loop_var);
			else
				{
				loop_var = install_ID((yyvsp[-3].str), current_module.c_str(),
				                                    false, false);
				}

			auto* loop_vars = new IDPList;
			loop_vars->push_back(loop_var.release());

			(yyval.stmt) = new ForStmt(loop_vars, {AdoptRef{}, (yyvsp[-1].expr)});
			}
#line 5128 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 267: /* for_head: TOK_FOR '(' '[' local_id_list ']' TOK_IN expr ')'  */
#line 2080 "parse.y"
                        {
			(yyval.stmt) = new ForStmt((yyvsp[-4].id_l), {AdoptRef{}, (yyvsp[-1].expr)});
			}
#line 5136 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 268: /* for_head: TOK_FOR '(' TOK_ID ',' TOK_ID TOK_IN expr ')'  */
#line 2085 "parse.y"
                        {
			set_location((yylsp[-7]), (yylsp[0]));
			const char* module = current_module.c_str();

			// Check for previous definitions of key and
			// value variables.
			auto key_var = lookup_ID((yyvsp[-5].str), module);
			auto val_var = lookup_ID((yyvsp[-3].str), module);

			// Validate previous definitions as needed.
			if ( key_var )
				check_loop_var(key_var);
			else
				key_var = install_ID((yyvsp[-5].str), module, false, false);

			if ( val_var )
				check_loop_var(val_var);
			else
				val_var = install_ID((yyvsp[-3].str), module, false, false);

			auto* loop_vars = new IDPList;
			loop_vars->push_back(key_var.release());

			(yyval.stmt) = new ForStmt(loop_vars, {AdoptRef{}, (yyvsp[-1].expr)}, std::move(val_var));
			}
#line 5166 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 269: /* for_head: TOK_FOR '(' '[' local_id_list ']' ',' TOK_ID TOK_IN expr ')'  */
#line 2112 "parse.y"
                        {
			set_location((yylsp[-9]), (yylsp[0]));
			const char* module = current_module.c_str();

			// Validate value variable
			auto val_var = lookup_ID((yyvsp[-3].str), module);

			if ( val_var )
				check_loop_var(val_var);
			else
				val_var = install_ID((yyvsp[-3].str), module, false, false);

			(yyval.stmt) = new ForStmt((yyvsp[-6].id_l), {AdoptRef{}, (yyvsp[-1].expr)}, std::move(val_var));
			}
#line 5185 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 270: /* local_id_list: local_id_list ',' local_id  */
#line 2130 "parse.y"
                        { (yyvsp[-2].id_l)->push_back((yyvsp[0].id)); }
#line 5191 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 271: /* local_id_list: local_id  */
#line 2132 "parse.y"
                        {
			(yyval.id_l) = new IDPList;
			(yyval.id_l)->push_back((yyvsp[0].id));
			}
#line 5200 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 272: /* local_id: TOK_ID  */
#line 2140 "parse.y"
                        {
			set_location((yylsp[0]));
			auto id = lookup_ID((yyvsp[0].str), current_module.c_str());
			(yyval.id) = id.release();

			if ( (yyval.id) )
				{
				if ( (yyval.id)->IsGlobal() && ! (yyval.id)->IsBlank() )
					(yyval.id)->Error("already a global identifier");

				if ( (yyval.id)->IsConst() && ! (yyval.id)->IsBlank() )
 					(yyval.id)->Error("already a const identifier");

				delete [] (yyvsp[0].str);
				}

			else
				{
				(yyval.id) = install_ID((yyvsp[0].str), current_module.c_str(),
				                              false, is_export).release();
				}
			}
#line 5227 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 273: /* $@34: %empty  */
#line 2165 "parse.y"
        { resolving_global_ID = 1; }
#line 5233 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 274: /* global_id: $@34 global_or_event_id  */
#line 2166 "parse.y"
                { (yyval.id) = (yyvsp[0].id); }
#line 5239 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 275: /* $@35: %empty  */
#line 2170 "parse.y"
        { defining_global_ID = 1; }
#line 5245 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 276: /* $@36: %empty  */
#line 2170 "parse.y"
                                              { defining_global_ID = 0; }
#line 5251 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 277: /* def_global_id: $@35 global_id $@36  */
#line 2171 "parse.y"
                { (yyval.id) = (yyvsp[-1].id); }
#line 5257 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 278: /* $@37: %empty  */
#line 2175 "parse.y"
        { resolving_global_ID = 0; }
#line 5263 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 279: /* event_id: $@37 global_or_event_id  */
#line 2176 "parse.y"
                { (yyval.id) = (yyvsp[0].id); }
#line 5269 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 280: /* global_or_event_id: TOK_ID  */
#line 2181 "parse.y"
                        {
			set_location((yylsp[0]));
			auto id = lookup_ID((yyvsp[0].str), current_module.c_str(), false,
			                    defining_global_ID);
			(yyval.id) = id.release();

			if ( (yyval.id) )
				{
				if ( ! (yyval.id)->IsGlobal() )
					(yyval.id)->Error("already a local identifier");

				if ( (yyval.id)->IsDeprecated() )
					{
					const auto& t = (yyval.id)->GetType();

					if ( t->Tag() != TYPE_FUNC ||
					     t->AsFuncType()->Flavor() != FUNC_FLAVOR_FUNCTION )
						reporter->Deprecation((yyval.id)->GetDeprecationWarning());
					}

				delete [] (yyvsp[0].str);
				}

			else
				{
				const char* module_name =
					resolving_global_ID ?
						current_module.c_str() : 0;

				(yyval.id) = install_ID((yyvsp[0].str), module_name,
				                              true, is_export).release();
				}
			}
#line 5307 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 281: /* resolve_id: TOK_ID  */
#line 2219 "parse.y"
                        {
			set_location((yylsp[0]));
			auto id = lookup_ID((yyvsp[0].str), current_module.c_str());
			(yyval.id) = id.release();

			if ( ! (yyval.id) )
				reporter->Error("identifier not defined: %s", (yyvsp[0].str));

			delete [] (yyvsp[0].str);
			}
#line 5322 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 282: /* opt_no_test: TOK_NO_TEST  */
#line 2233 "parse.y"
                        { (yyval.b) = true; }
#line 5328 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 283: /* opt_no_test: %empty  */
#line 2235 "parse.y"
                        { (yyval.b) = false; }
#line 5334 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 284: /* opt_no_test_block: TOK_NO_TEST  */
#line 2240 "parse.y"
                        { (yyval.b) = true; script_coverage_mgr.IncIgnoreDepth(); }
#line 5340 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 285: /* opt_no_test_block: %empty  */
#line 2242 "parse.y"
                        { (yyval.b) = false; }
#line 5346 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 286: /* opt_deprecated: TOK_ATTR_DEPRECATED  */
#line 2247 "parse.y"
                        { (yyval.expr) = new ConstExpr(make_intrusive<StringVal>("")); }
#line 5352 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 287: /* opt_deprecated: TOK_ATTR_DEPRECATED '=' TOK_CONSTANT  */
#line 2250 "parse.y"
                        {
			if ( IsString((yyvsp[0].val)->GetType()->Tag()) )
				(yyval.expr) = new ConstExpr({AdoptRef{}, (yyvsp[0].val)});
			else
				{
				ODesc d;
				(yyvsp[0].val)->Describe(&d);
				reporter->Error("'&deprecated=%s' must use a string literal",
				                      d.Description());
				(yyval.expr) = new ConstExpr(make_intrusive<StringVal>(""));
				}
			}
#line 5369 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 288: /* opt_deprecated: %empty  */
#line 2263 "parse.y"
                        { (yyval.expr) = nullptr; }
#line 5375 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;

  case 289: /* expr_list_opt_comma: ','  */
#line 2266 "parse.y"
                         { expr_list_has_opt_comma = 1; }
#line 5381 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"
    break;


#line 5385 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/p.cc"

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
  *++yylsp = yyloc;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2270 "parse.y"


int yyerror(const char msg[])
	{
	if ( in_debug )
		g_curr_debug_error = util::copy_string(msg);

	if ( last_tok[0] == '\n' )
		reporter->Error("%s, on previous line", msg);
	else if ( last_tok[0] == '\0' )
		{
		if ( last_filename )
			reporter->Error("%s, at end of file %s", msg, last_filename);
		else
			reporter->Error("%s, at end of file", msg);
		}
	else
		{
		if ( last_last_tok_filename && last_tok_filename &&
		     ! util::streq(last_last_tok_filename, last_tok_filename) )
			reporter->Error("%s, at or near \"%s\" or end of file %s",
			                      msg, last_tok, last_last_tok_filename);
		else
			reporter->Error("%s, at or near \"%s\"", msg, last_tok);
		}

	return 0;
	}
