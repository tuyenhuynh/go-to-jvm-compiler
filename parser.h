/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 8 "parser.y" /* yacc.c:1909  */

	#include <parser.h>

#line 48 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    FUNC = 259,
    RETURN = 260,
    ASSIGN_OP = 261,
    PLUS_ASSIGN_OP = 262,
    MINUS_ASSIGN_OP = 263,
    MUL_ASSIGN_OP = 264,
    DIV_ASSIGN_OP = 265,
    BREAK = 266,
    CONTINUE = 267,
    SWITCH = 268,
    CASE = 269,
    DEFAULT = 270,
    FOR = 271,
    IF = 272,
    ELSE = 273,
    CONST = 274,
    VAR = 275,
    AND_OP = 276,
    OR_OP = 277,
    BITWISE_OR_OP = 278,
    BITWISE_AND_OP = 279,
    BITWISE_XOR_OP = 280,
    HIGHER_OP = 281,
    LOWER_OP = 282,
    HIGHER_OR_EQU_OP = 283,
    LOWER_OR_EQU_OP = 284,
    ADD_OP = 285,
    MINUS_OP = 286,
    MUL_OP = 287,
    DIV_OP = 288,
    MOD_OP = 289,
    EQU_OP = 290,
    NOT_EQU_OP = 291,
    RANGE = 292,
    ENDL = 293,
    NOT_OP = 294,
    STRUCT = 295,
    DECIMAL_NUMBER = 296,
    FLOAT_NUMBER = 297,
    STRING_LITERAL = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
