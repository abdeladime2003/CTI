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

#ifndef YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_AUXIL_BINPAC_SRC_PAC_PARSE_H_INCLUDED
# define YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_AUXIL_BINPAC_SRC_PAC_PARSE_H_INCLUDED
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
    TOK_TYPE = 258,                /* TOK_TYPE  */
    TOK_RECORD = 259,              /* TOK_RECORD  */
    TOK_CASE = 260,                /* TOK_CASE  */
    TOK_ENUM = 261,                /* TOK_ENUM  */
    TOK_LET = 262,                 /* TOK_LET  */
    TOK_FUNCTION = 263,            /* TOK_FUNCTION  */
    TOK_REFINE = 264,              /* TOK_REFINE  */
    TOK_CASEFUNC = 265,            /* TOK_CASEFUNC  */
    TOK_CASETYPE = 266,            /* TOK_CASETYPE  */
    TOK_TYPEATTR = 267,            /* TOK_TYPEATTR  */
    TOK_HELPERHEADER = 268,        /* TOK_HELPERHEADER  */
    TOK_HELPERCODE = 269,          /* TOK_HELPERCODE  */
    TOK_RIGHTARROW = 270,          /* TOK_RIGHTARROW  */
    TOK_DEFAULT = 271,             /* TOK_DEFAULT  */
    TOK_OF = 272,                  /* TOK_OF  */
    TOK_PADDING = 273,             /* TOK_PADDING  */
    TOK_TO = 274,                  /* TOK_TO  */
    TOK_ALIGN = 275,               /* TOK_ALIGN  */
    TOK_WITHINPUT = 276,           /* TOK_WITHINPUT  */
    TOK_INT8 = 277,                /* TOK_INT8  */
    TOK_INT16 = 278,               /* TOK_INT16  */
    TOK_INT32 = 279,               /* TOK_INT32  */
    TOK_INT64 = 280,               /* TOK_INT64  */
    TOK_UINT8 = 281,               /* TOK_UINT8  */
    TOK_UINT16 = 282,              /* TOK_UINT16  */
    TOK_UINT32 = 283,              /* TOK_UINT32  */
    TOK_UINT64 = 284,              /* TOK_UINT64  */
    TOK_ID = 285,                  /* TOK_ID  */
    TOK_NUMBER = 286,              /* TOK_NUMBER  */
    TOK_REGEX = 287,               /* TOK_REGEX  */
    TOK_STRING = 288,              /* TOK_STRING  */
    TOK_BEGIN_RE = 289,            /* TOK_BEGIN_RE  */
    TOK_END_RE = 290,              /* TOK_END_RE  */
    TOK_ATTR_ALSO = 291,           /* TOK_ATTR_ALSO  */
    TOK_ATTR_BYTEORDER = 292,      /* TOK_ATTR_BYTEORDER  */
    TOK_ATTR_CHECK = 293,          /* TOK_ATTR_CHECK  */
    TOK_ATTR_CHUNKED = 294,        /* TOK_ATTR_CHUNKED  */
    TOK_ATTR_ENFORCE = 295,        /* TOK_ATTR_ENFORCE  */
    TOK_ATTR_EXPORTSOURCEDATA = 296, /* TOK_ATTR_EXPORTSOURCEDATA  */
    TOK_ATTR_IF = 297,             /* TOK_ATTR_IF  */
    TOK_ATTR_LENGTH = 298,         /* TOK_ATTR_LENGTH  */
    TOK_ATTR_LET = 299,            /* TOK_ATTR_LET  */
    TOK_ATTR_LINEBREAKER = 300,    /* TOK_ATTR_LINEBREAKER  */
    TOK_ATTR_MULTILINE = 301,      /* TOK_ATTR_MULTILINE  */
    TOK_ATTR_ONELINE = 302,        /* TOK_ATTR_ONELINE  */
    TOK_ATTR_REFCOUNT = 303,       /* TOK_ATTR_REFCOUNT  */
    TOK_ATTR_REQUIRES = 304,       /* TOK_ATTR_REQUIRES  */
    TOK_ATTR_RESTOFDATA = 305,     /* TOK_ATTR_RESTOFDATA  */
    TOK_ATTR_RESTOFFLOW = 306,     /* TOK_ATTR_RESTOFFLOW  */
    TOK_ATTR_TRANSIENT = 307,      /* TOK_ATTR_TRANSIENT  */
    TOK_ATTR_UNTIL = 308,          /* TOK_ATTR_UNTIL  */
    TOK_ANALYZER = 309,            /* TOK_ANALYZER  */
    TOK_CONNECTION = 310,          /* TOK_CONNECTION  */
    TOK_FLOW = 311,                /* TOK_FLOW  */
    TOK_STATE = 312,               /* TOK_STATE  */
    TOK_ACTION = 313,              /* TOK_ACTION  */
    TOK_WHEN = 314,                /* TOK_WHEN  */
    TOK_HELPER = 315,              /* TOK_HELPER  */
    TOK_DATAUNIT = 316,            /* TOK_DATAUNIT  */
    TOK_FLOWDIR = 317,             /* TOK_FLOWDIR  */
    TOK_WITHCONTEXT = 318,         /* TOK_WITHCONTEXT  */
    TOK_LPB_EXTERN = 319,          /* TOK_LPB_EXTERN  */
    TOK_LPB_HEADER = 320,          /* TOK_LPB_HEADER  */
    TOK_LPB_CODE = 321,            /* TOK_LPB_CODE  */
    TOK_LPB_MEMBER = 322,          /* TOK_LPB_MEMBER  */
    TOK_LPB_INIT = 323,            /* TOK_LPB_INIT  */
    TOK_LPB_CLEANUP = 324,         /* TOK_LPB_CLEANUP  */
    TOK_LPB_EOF = 325,             /* TOK_LPB_EOF  */
    TOK_LPB = 326,                 /* TOK_LPB  */
    TOK_RPB = 327,                 /* TOK_RPB  */
    TOK_EMBEDDED_ATOM = 328,       /* TOK_EMBEDDED_ATOM  */
    TOK_EMBEDDED_STRING = 329,     /* TOK_EMBEDDED_STRING  */
    TOK_PAC_VAL = 330,             /* TOK_PAC_VAL  */
    TOK_PAC_SET = 331,             /* TOK_PAC_SET  */
    TOK_PAC_TYPE = 332,            /* TOK_PAC_TYPE  */
    TOK_PAC_TYPEOF = 333,          /* TOK_PAC_TYPEOF  */
    TOK_PAC_CONST_DEF = 334,       /* TOK_PAC_CONST_DEF  */
    TOK_END_PAC = 335,             /* TOK_END_PAC  */
    TOK_EXTERN = 336,              /* TOK_EXTERN  */
    TOK_PLUSEQ = 337,              /* TOK_PLUSEQ  */
    TOK_OR = 338,                  /* TOK_OR  */
    TOK_AND = 339,                 /* TOK_AND  */
    TOK_EQUAL = 340,               /* TOK_EQUAL  */
    TOK_NEQ = 341,                 /* TOK_NEQ  */
    TOK_LE = 342,                  /* TOK_LE  */
    TOK_GE = 343,                  /* TOK_GE  */
    TOK_LSHIFT = 344,              /* TOK_LSHIFT  */
    TOK_RSHIFT = 345,              /* TOK_RSHIFT  */
    TOK_SIZEOF = 346,              /* TOK_SIZEOF  */
    TOK_OFFSETOF = 347             /* TOK_OFFSETOF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 136 "pac_parse.yy"

	ActionParam		*actionparam;
	ActionParamType		*actionparamtype;
	AnalyzerElement		*aelem;
	AnalyzerElementList	*aelemlist;
	Attr			*attr;
	AttrList		*attrlist;
	ConstString		*cstr;
	CaseExpr		*caseexpr;
	CaseExprList		*caseexprlist;
	CaseField		*casefield;
	CaseFieldList 		*casefieldlist;
	ContextField		*contextfield;
	ContextFieldList 	*contextfieldlist;
	Decl			*decl;
	EmbeddedCode		*embedded_code;
	Enum			*enumitem;
	EnumList		*enumlist;
	Expr			*expr;
	ExprList 		*exprlist;
	Field 			*field;
	FieldList 		*fieldlist;
	Function		*function;
	ID			*id;
	InputBuffer		*input;
	LetFieldList		*letfieldlist;
	LetField		*letfield;
	Number			*num;
	PacPrimitive		*pacprimitive;
	Param 			*param;
	ParamList 		*paramlist;
	RecordFieldList 	*recordfieldlist;
	RecordField		*recordfield;
	RegEx			*regex;
	StateVar		*statevar;
	StateVarList		*statevarlist;
	const char		*str;
	Type 			*type;
	int			val;

#line 197 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/binpac/src/pac_parse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_AUXIL_BINPAC_SRC_PAC_PARSE_H_INCLUDED  */
