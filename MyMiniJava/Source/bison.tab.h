/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     Id = 258,
     IntNum = 259,
     If = 260,
     Else = 261,
     While = 262,
     Main = 263,
     Class = 264,
     Public = 265,
     Static = 266,
     Return = 267,
     Extends = 268,
     Int = 269,
     Bool = 270,
     Void = 271,
     String = 272,
     Print = 273,
     True = 274,
     False = 275,
     This = 276,
     New = 277,
     Length = 278,
     SystemOutPrintln = 279,
     OperatorEq = 280,
     OperatorAnd = 281,
     OperatorMore = 282,
     OperatorLess = 283,
     UMINUS = 284
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 62 "bison.y"

	int ival;
	IProgram* program;
	IMainClass* mainClass;
	IClassDeclList* classDeclList;
	IClassDecl* classDecl;
	IVarDeclList* varDeclList;
	IVarDecl* varDecl;
	IMethodDeclList* methodDeclList;
	IMethodDecl* methodDecl;
	IFormalList* formalList;
	IType* type;
	IStmtList* stmtList;
	IStmt* stmt;
	IExprList* exprList;
	IExpr* expr;
	char sval[100];


/* Line 2058 of yacc.c  */
#line 106 "bison.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */
