/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_SRC_ZEEKPARSE_H_INCLUDED
# define YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_SRC_ZEEKPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_ADD = 258,                 /* TOK_ADD  */
    TOK_ADD_TO = 259,              /* TOK_ADD_TO  */
    TOK_ADDR = 260,                /* TOK_ADDR  */
    TOK_ANY = 261,                 /* TOK_ANY  */
    TOK_ATENDIF = 262,             /* TOK_ATENDIF  */
    TOK_ATELSE = 263,              /* TOK_ATELSE  */
    TOK_ATIF = 264,                /* TOK_ATIF  */
    TOK_ATIFDEF = 265,             /* TOK_ATIFDEF  */
    TOK_ATIFNDEF = 266,            /* TOK_ATIFNDEF  */
    TOK_BOOL = 267,                /* TOK_BOOL  */
    TOK_BREAK = 268,               /* TOK_BREAK  */
    TOK_CASE = 269,                /* TOK_CASE  */
    TOK_OPTION = 270,              /* TOK_OPTION  */
    TOK_CONST = 271,               /* TOK_CONST  */
    TOK_CONSTANT = 272,            /* TOK_CONSTANT  */
    TOK_COPY = 273,                /* TOK_COPY  */
    TOK_COUNT = 274,               /* TOK_COUNT  */
    TOK_DEFAULT = 275,             /* TOK_DEFAULT  */
    TOK_DELETE = 276,              /* TOK_DELETE  */
    TOK_DOUBLE = 277,              /* TOK_DOUBLE  */
    TOK_ELSE = 278,                /* TOK_ELSE  */
    TOK_ENUM = 279,                /* TOK_ENUM  */
    TOK_EVENT = 280,               /* TOK_EVENT  */
    TOK_EXPORT = 281,              /* TOK_EXPORT  */
    TOK_FALLTHROUGH = 282,         /* TOK_FALLTHROUGH  */
    TOK_FILE = 283,                /* TOK_FILE  */
    TOK_FOR = 284,                 /* TOK_FOR  */
    TOK_FUNCTION = 285,            /* TOK_FUNCTION  */
    TOK_GLOBAL = 286,              /* TOK_GLOBAL  */
    TOK_HOOK = 287,                /* TOK_HOOK  */
    TOK_ID = 288,                  /* TOK_ID  */
    TOK_IF = 289,                  /* TOK_IF  */
    TOK_INT = 290,                 /* TOK_INT  */
    TOK_INTERVAL = 291,            /* TOK_INTERVAL  */
    TOK_LIST = 292,                /* TOK_LIST  */
    TOK_MODULE = 293,              /* TOK_MODULE  */
    TOK_LOCAL = 294,               /* TOK_LOCAL  */
    TOK_WHEN_LOCAL = 295,          /* TOK_WHEN_LOCAL  */
    TOK_NEXT = 296,                /* TOK_NEXT  */
    TOK_OF = 297,                  /* TOK_OF  */
    TOK_OPAQUE = 298,              /* TOK_OPAQUE  */
    TOK_PATTERN = 299,             /* TOK_PATTERN  */
    TOK_PATTERN_END = 300,         /* TOK_PATTERN_END  */
    TOK_PATTERN_TEXT = 301,        /* TOK_PATTERN_TEXT  */
    TOK_PORT = 302,                /* TOK_PORT  */
    TOK_PRINT = 303,               /* TOK_PRINT  */
    TOK_RECORD = 304,              /* TOK_RECORD  */
    TOK_REDEF = 305,               /* TOK_REDEF  */
    TOK_REMOVE_FROM = 306,         /* TOK_REMOVE_FROM  */
    TOK_RETURN = 307,              /* TOK_RETURN  */
    TOK_SCHEDULE = 308,            /* TOK_SCHEDULE  */
    TOK_SET = 309,                 /* TOK_SET  */
    TOK_STRING = 310,              /* TOK_STRING  */
    TOK_SUBNET = 311,              /* TOK_SUBNET  */
    TOK_SWITCH = 312,              /* TOK_SWITCH  */
    TOK_TABLE = 313,               /* TOK_TABLE  */
    TOK_TIME = 314,                /* TOK_TIME  */
    TOK_TIMEOUT = 315,             /* TOK_TIMEOUT  */
    TOK_TYPE = 316,                /* TOK_TYPE  */
    TOK_VECTOR = 317,              /* TOK_VECTOR  */
    TOK_WHEN = 318,                /* TOK_WHEN  */
    TOK_WHILE = 319,               /* TOK_WHILE  */
    TOK_AS = 320,                  /* TOK_AS  */
    TOK_IS = 321,                  /* TOK_IS  */
    TOK_ATTR_ADD_FUNC = 322,       /* TOK_ATTR_ADD_FUNC  */
    TOK_ATTR_DEFAULT = 323,        /* TOK_ATTR_DEFAULT  */
    TOK_ATTR_OPTIONAL = 324,       /* TOK_ATTR_OPTIONAL  */
    TOK_ATTR_REDEF = 325,          /* TOK_ATTR_REDEF  */
    TOK_ATTR_DEL_FUNC = 326,       /* TOK_ATTR_DEL_FUNC  */
    TOK_ATTR_EXPIRE_FUNC = 327,    /* TOK_ATTR_EXPIRE_FUNC  */
    TOK_ATTR_EXPIRE_CREATE = 328,  /* TOK_ATTR_EXPIRE_CREATE  */
    TOK_ATTR_EXPIRE_READ = 329,    /* TOK_ATTR_EXPIRE_READ  */
    TOK_ATTR_EXPIRE_WRITE = 330,   /* TOK_ATTR_EXPIRE_WRITE  */
    TOK_ATTR_RAW_OUTPUT = 331,     /* TOK_ATTR_RAW_OUTPUT  */
    TOK_ATTR_ON_CHANGE = 332,      /* TOK_ATTR_ON_CHANGE  */
    TOK_ATTR_BROKER_STORE = 333,   /* TOK_ATTR_BROKER_STORE  */
    TOK_ATTR_BROKER_STORE_ALLOW_COMPLEX = 334, /* TOK_ATTR_BROKER_STORE_ALLOW_COMPLEX  */
    TOK_ATTR_BACKEND = 335,        /* TOK_ATTR_BACKEND  */
    TOK_ATTR_PRIORITY = 336,       /* TOK_ATTR_PRIORITY  */
    TOK_ATTR_LOG = 337,            /* TOK_ATTR_LOG  */
    TOK_ATTR_ERROR_HANDLER = 338,  /* TOK_ATTR_ERROR_HANDLER  */
    TOK_ATTR_GROUP = 339,          /* TOK_ATTR_GROUP  */
    TOK_ATTR_TYPE_COLUMN = 340,    /* TOK_ATTR_TYPE_COLUMN  */
    TOK_ATTR_DEPRECATED = 341,     /* TOK_ATTR_DEPRECATED  */
    TOK_ATTR_IS_ASSIGNED = 342,    /* TOK_ATTR_IS_ASSIGNED  */
    TOK_ATTR_IS_USED = 343,        /* TOK_ATTR_IS_USED  */
    TOK_ATTR_ORDERED = 344,        /* TOK_ATTR_ORDERED  */
    TOK_DEBUG = 345,               /* TOK_DEBUG  */
    TOK_NO_TEST = 346,             /* TOK_NO_TEST  */
    TOK_OR_OR = 347,               /* TOK_OR_OR  */
    TOK_AND_AND = 348,             /* TOK_AND_AND  */
    TOK_LE = 349,                  /* TOK_LE  */
    TOK_GE = 350,                  /* TOK_GE  */
    TOK_EQ = 351,                  /* TOK_EQ  */
    TOK_NE = 352,                  /* TOK_NE  */
    TOK_IN = 353,                  /* TOK_IN  */
    TOK_NOT_IN = 354,              /* TOK_NOT_IN  */
    TOK_LSHIFT = 355,              /* TOK_LSHIFT  */
    TOK_RSHIFT = 356,              /* TOK_RSHIFT  */
    TOK_INCR = 357,                /* TOK_INCR  */
    TOK_DECR = 358,                /* TOK_DECR  */
    TOK_HAS_FIELD = 359,           /* TOK_HAS_FIELD  */
    TOK_HAS_ATTR = 360             /* TOK_HAS_ATTR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 350 "parse.y"

	bool b;
	char* str;
	zeek::detail::ID* id;
	zeek::IDPList* id_l;
	zeek::detail::InitClass ic;
	zeek::Val* val;
	zeek::RE_Matcher* re;
	zeek::detail::Expr* expr;
	zeek::detail::EventExpr* event_expr;
	zeek::detail::Stmt* stmt;
	zeek::detail::ListExpr* list;
	zeek::Type* type;
	zeek::RecordType* record;
	zeek::FuncType* func_type;
	zeek::TypeList* type_l;
	zeek::TypeDecl* type_decl;
	zeek::type_decl_list* type_decl_l;
	zeek::detail::Case* c_case;
	zeek::detail::case_list* case_l;
	zeek::detail::Attr* attr;
	std::vector<zeek::detail::AttrPtr>* attr_l;
	zeek::detail::AttrTag attrtag;
	zeek::FuncType::Capture* capture;
	zeek::FuncType::CaptureList* captures;
	zeek::detail::WhenInfo* when_clause;
	struct
		{
		bool ignore_case;
		bool single_line;
		} re_modes;

#line 202 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/zeekparse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_SRC_ZEEKPARSE_H_INCLUDED  */
