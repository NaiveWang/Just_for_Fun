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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROCESSOR = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    FOR = 262,
    CONTINUE = 263,
    BREAK = 264,
    REBOOT = 265,
    RETURN = 266,
    HALT = 267,
    INT = 268,
    REAL = 269,
    CHAR = 270,
    STATIC = 271,
    VOID = 272,
    STRING = 273,
    EQUAL = 274,
    DIFF = 275,
    GRTEQU = 276,
    LESEQU = 277,
    RAND = 278,
    ROR = 279,
    ID = 280,
    CONSTANT_INT = 281,
    CONSTANT_REAL = 282,
    CONSTANT_CHAR = 283,
    CONSTANT_STRING = 284,
    SHL = 285,
    SHR = 286,
    SAR = 287,
    INC = 288,
    DEC = 289,
    ASSAR = 290,
    ASSHL = 291,
    ASSHR = 292,
    ASADD = 293,
    ASSUB = 294,
    ASDIV = 295,
    ASMOD = 296,
    ASMUL = 297,
    ASAND = 298,
    ASOR = 299,
    ASEOR = 300
  };
#endif
/* Tokens.  */
#define PROCESSOR 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define FOR 262
#define CONTINUE 263
#define BREAK 264
#define REBOOT 265
#define RETURN 266
#define HALT 267
#define INT 268
#define REAL 269
#define CHAR 270
#define STATIC 271
#define VOID 272
#define STRING 273
#define EQUAL 274
#define DIFF 275
#define GRTEQU 276
#define LESEQU 277
#define RAND 278
#define ROR 279
#define ID 280
#define CONSTANT_INT 281
#define CONSTANT_REAL 282
#define CONSTANT_CHAR 283
#define CONSTANT_STRING 284
#define SHL 285
#define SHR 286
#define SAR 287
#define INC 288
#define DEC 289
#define ASSAR 290
#define ASSHL 291
#define ASSHR 292
#define ASADD 293
#define ASSUB 294
#define ASDIV 295
#define ASMOD 296
#define ASMUL 297
#define ASAND 298
#define ASOR 299
#define ASEOR 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
