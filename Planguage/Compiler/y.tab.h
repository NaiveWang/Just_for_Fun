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
    SUSPEND = 268,
    INT = 269,
    REAL = 270,
    CHAR = 271,
    STRING = 272,
    STATIC = 273,
    VOID = 274,
    EQUAL = 275,
    DIFF = 276,
    GRTEQU = 277,
    LESEQU = 278,
    RAND = 279,
    ROR = 280,
    ID = 281,
    CONSTANT_INT = 282,
    CONSTANT_REAL = 283,
    CONSTANT_CHAR = 284,
    CONSTANT_STRING = 285,
    CONSTANT_HEX = 286,
    CONSTANT_OCT = 287,
    SHL = 288,
    SHR = 289,
    SAR = 290,
    INC = 291,
    DEC = 292,
    ASSAR = 293,
    ASSHL = 294,
    ASSHR = 295,
    ASADD = 296,
    ASSUB = 297,
    ASDIV = 298,
    ASMOD = 299,
    ASMUL = 300,
    ASAND = 301,
    ASOR = 302,
    ASEOR = 303
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
#define SUSPEND 268
#define INT 269
#define REAL 270
#define CHAR 271
#define STRING 272
#define STATIC 273
#define VOID 274
#define EQUAL 275
#define DIFF 276
#define GRTEQU 277
#define LESEQU 278
#define RAND 279
#define ROR 280
#define ID 281
#define CONSTANT_INT 282
#define CONSTANT_REAL 283
#define CONSTANT_CHAR 284
#define CONSTANT_STRING 285
#define CONSTANT_HEX 286
#define CONSTANT_OCT 287
#define SHL 288
#define SHR 289
#define SAR 290
#define INC 291
#define DEC 292
#define ASSAR 293
#define ASSHL 294
#define ASSHR 295
#define ASADD 296
#define ASSUB 297
#define ASDIV 298
#define ASMOD 299
#define ASMUL 300
#define ASAND 301
#define ASOR 302
#define ASEOR 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
