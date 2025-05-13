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

#ifndef YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_AUXIL_BIFCL_BIF_PARSE_H_INCLUDED
# define YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_AUXIL_BIFCL_BIF_PARSE_H_INCLUDED
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
    TOK_LPP = 258,                 /* TOK_LPP  */
    TOK_RPP = 259,                 /* TOK_RPP  */
    TOK_LPB = 260,                 /* TOK_LPB  */
    TOK_RPB = 261,                 /* TOK_RPB  */
    TOK_LPPB = 262,                /* TOK_LPPB  */
    TOK_RPPB = 263,                /* TOK_RPPB  */
    TOK_VAR_ARG = 264,             /* TOK_VAR_ARG  */
    TOK_BOOL = 265,                /* TOK_BOOL  */
    TOK_FUNCTION = 266,            /* TOK_FUNCTION  */
    TOK_EVENT = 267,               /* TOK_EVENT  */
    TOK_CONST = 268,               /* TOK_CONST  */
    TOK_ENUM = 269,                /* TOK_ENUM  */
    TOK_OF = 270,                  /* TOK_OF  */
    TOK_TYPE = 271,                /* TOK_TYPE  */
    TOK_RECORD = 272,              /* TOK_RECORD  */
    TOK_SET = 273,                 /* TOK_SET  */
    TOK_VECTOR = 274,              /* TOK_VECTOR  */
    TOK_OPAQUE = 275,              /* TOK_OPAQUE  */
    TOK_TABLE = 276,               /* TOK_TABLE  */
    TOK_MODULE = 277,              /* TOK_MODULE  */
    TOK_ARGS = 278,                /* TOK_ARGS  */
    TOK_ARG = 279,                 /* TOK_ARG  */
    TOK_ARGC = 280,                /* TOK_ARGC  */
    TOK_ID = 281,                  /* TOK_ID  */
    TOK_ATTR = 282,                /* TOK_ATTR  */
    TOK_CSTR = 283,                /* TOK_CSTR  */
    TOK_LF = 284,                  /* TOK_LF  */
    TOK_WS = 285,                  /* TOK_WS  */
    TOK_COMMENT = 286,             /* TOK_COMMENT  */
    TOK_ATOM = 287,                /* TOK_ATOM  */
    TOK_INT = 288,                 /* TOK_INT  */
    TOK_C_TOKEN = 289              /* TOK_C_TOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 305 "builtin-func.y"

	const char* str;
	int val;

#line 103 "/home/abdo/Cti_Project/zeek-6.0.2/build/auxil/bifcl/bif_parse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_AUXIL_BIFCL_BIF_PARSE_H_INCLUDED  */
