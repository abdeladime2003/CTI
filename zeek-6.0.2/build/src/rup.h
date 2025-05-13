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

#ifndef YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_SRC_RUP_H_INCLUDED
# define YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_SRC_RUP_H_INCLUDED
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
    TOK_COMP = 258,                /* TOK_COMP  */
    TOK_DISABLE = 259,             /* TOK_DISABLE  */
    TOK_DST_IP = 260,              /* TOK_DST_IP  */
    TOK_DST_PORT = 261,            /* TOK_DST_PORT  */
    TOK_ENABLE = 262,              /* TOK_ENABLE  */
    TOK_EVAL = 263,                /* TOK_EVAL  */
    TOK_EVENT = 264,               /* TOK_EVENT  */
    TOK_MIME = 265,                /* TOK_MIME  */
    TOK_HEADER = 266,              /* TOK_HEADER  */
    TOK_IDENT = 267,               /* TOK_IDENT  */
    TOK_INT = 268,                 /* TOK_INT  */
    TOK_IP = 269,                  /* TOK_IP  */
    TOK_IP6 = 270,                 /* TOK_IP6  */
    TOK_IP_OPTIONS = 271,          /* TOK_IP_OPTIONS  */
    TOK_IP_OPTION_SYM = 272,       /* TOK_IP_OPTION_SYM  */
    TOK_IP_PROTO = 273,            /* TOK_IP_PROTO  */
    TOK_PATTERN = 274,             /* TOK_PATTERN  */
    TOK_PATTERN_TYPE = 275,        /* TOK_PATTERN_TYPE  */
    TOK_PAYLOAD_SIZE = 276,        /* TOK_PAYLOAD_SIZE  */
    TOK_PROT = 277,                /* TOK_PROT  */
    TOK_REQUIRES_SIGNATURE = 278,  /* TOK_REQUIRES_SIGNATURE  */
    TOK_REQUIRES_REVERSE_SIGNATURE = 279, /* TOK_REQUIRES_REVERSE_SIGNATURE  */
    TOK_SIGNATURE = 280,           /* TOK_SIGNATURE  */
    TOK_SAME_IP = 281,             /* TOK_SAME_IP  */
    TOK_SRC_IP = 282,              /* TOK_SRC_IP  */
    TOK_SRC_PORT = 283,            /* TOK_SRC_PORT  */
    TOK_TCP_STATE = 284,           /* TOK_TCP_STATE  */
    TOK_UDP_STATE = 285,           /* TOK_UDP_STATE  */
    TOK_STRING = 286,              /* TOK_STRING  */
    TOK_STATE_SYM = 287,           /* TOK_STATE_SYM  */
    TOK_ACTIVE = 288,              /* TOK_ACTIVE  */
    TOK_BOOL = 289,                /* TOK_BOOL  */
    TOK_POLICY_SYMBOL = 290        /* TOK_POLICY_SYMBOL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 84 "rule-parse.y"

	zeek::detail::Rule* rule;
	zeek::detail::RuleHdrTest* hdr_test;
	zeek::detail::maskedvalue_list* vallist;
	std::vector<zeek::IPPrefix>* prefix_val_list;
	zeek::IPPrefix* prefixval;

	bool bl;
	int val;
	char* str;
	zeek::detail::MaskedValue mval;
	zeek::detail::RuleHdrTest::Prot prot;
	zeek::detail::Range range;
	zeek::detail::Rule::PatternType ptype;

#line 115 "/home/abdo/Cti_Project/zeek-6.0.2/build/src/rup.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_HOME_ABDO_CTI_PROJECT_ZEEK_6_0_2_BUILD_SRC_RUP_H_INCLUDED  */
