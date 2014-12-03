%{       
#pragma once
#include <cstdio>
#include <iostream>
#include "syntaxTree.h"
#include "grammar.h"

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
void yyerror(const char *s);

%} 

%error-verbose
%verbose

%type<prog> Program
%type<mClass> MainClass
%type<clssDeclList> ClassDeclarationList
%type<clssDecl> ClassDeclaration
%type<varDeclList> VarDeclarationList
%type<varDecl> VarDeclaration
%type<methDeclList> MethodDeclarationList
%type<methDecl> MethodDeclaration
%type<formalList> FormalList
%type<formalList> FormalRestList
%type<type> Type
%type<stmtList> StatementList
%type<stmt> Statement
%type<exprList> ExprList
%type<exprList> ExprRestList
%type<expr> Expr

%token<sval> Id

%token IntNum
%token If Else While Main Class Public Static Return Extends

%token Int
%token Bool
%token Void
%token String

%token Print
%token True
%token False
%token This
%token New
%token Length
%token SystemOutPrintln
%start Program


%left OperatorLess OperatorMore OperatorAnd OperatorEq
%left '+' '-'
%left '*' '/'
%left UMINUS '!'
%left '.' '[' ']'

%union {
	int ival;
	IProgram* prog;
	IMainClass* mClass;
	IClassDeclList* clssDeclList;
	IClassDecl* clssDecl;
	IVarDeclList* varDeclList;
	IVarDecl* varDecl;
	IMethodDeclList* methDeclList;
	IMethodDecl* methDecl;
	IFormalList* formalList;
	IType* type;
	IStmtList* stmtList;
	IStmt* stmt;
	IExprList* exprList;
	IExpr* expr;
	char sval[100];
}

%%
Program 
	:	MainClass ClassDeclarationList { $$ = new CProgram( $1, $2 ); }
	;

MainClass 
	:	Class Id '{' Public Static Void Main '(' String '[' ']' Id ')' '{' Statement '}' '}' { $$ = new CMainClass( $2, $12, $15 ); }
	;
	
VarDeclaration 
	: Type Id ';' { $$ = 0; /*TODO*/ }
	;

VarDeclarationList 
	:	VarDeclarationList VarDeclaration { $$ = 0; /*TODO*/ }
	| /*eps*/ { $$ = 0; }
	;

ClassDeclaration 
	:	Class Id  '{' VarDeclarationList MethodDeclarationList '}' { }
	|	Class Id Extends Id '{' VarDeclarationList MethodDeclarationList '}' { }
	;

ClassDeclarationList
	:	ClassDeclaration ClassDeclarationList { $$ = 0; /*TODO*/ }
	|	/*epsilon*/ { $$ = 0; } 
	;

MethodDeclaration
	: Public Type Id '(' FormalList ')' '{' VarDeclarationList StatementList Return Expr ';' '}' { $$ = 0; /*TODO*/ }
	;

MethodDeclarationList
	:	MethodDeclarationList MethodDeclaration { $$ = 0; /*TODO*/ }
	|	/*epsilon*/ { $$ = 0; }
	;

FormalList	
	:	Type Id FormalRestList { $$ = 0; /*TODO*/ }
	|	/*epsilon*/ { $$ = 0; }
	;

FormalRestList
	: ',' Type Id FormalRestList { $$ = 0; /*TODO*/ }
	| /*epsilon*/ { $$ = 0; }
	;

Type
	:	Int { $$ = 0; /*TODO*/ }
	|	Int '[' ']' { $$ = 0; /*TODO*/ }
    |	Bool { $$ = 0; /*TODO*/ }
    |	Id { $$ = 0; /*TODO*/ }
	;

StatementList
	:	Statement StatementList { $$ = 0; /*TODO*/ }
	|	/*epsilon*/ { $$ = 0; }
	;

Statement
	:	'{' StatementList '}' { $$ = 0; /*TODO*/ }
	|	Id OperatorEq Expr ';' { $$ = 0; /*TODO*/ }
	|	If '(' Expr ')' Statement Else Statement { $$ = 0; /*TODO*/ }
	|	While '(' Expr ')' Statement { $$ = 0; /*TODO*/ }
	|	Print '(' Expr ')' ';' { $$ = 0; /*TODO*/ }
	|	Id '[' Expr ']' OperatorEq Expr ';' { $$ = 0; /*TODO*/ }
	;

Expr
	:	Expr '*' Expr { $$ = new COpExpr( $1, BO_Mult, $3 ); }
	|   Expr '+' Expr { $$ = new COpExpr( $1, BO_Plus, $3 ); }
	|	Expr '/' Expr { $$ = new COpExpr( $1, BO_Div, $3 ); }
	|	Expr '-' Expr { $$ = new COpExpr( $1, BO_Minus, $3 ); }
	|	'-' Expr %prec UMINUS { /*TODO*/ }
	|	Expr '[' Expr ']' { $$ = new CExExpr($1, $3);  }
	|	Expr '.' Length { /*TODO*/ }
	|	Expr '.' Id '(' ExprList ')' { /*TODO*/ }
	|	Expr OperatorLess Expr { $$ = new COpExpr( $1, BO_Less, $3 ); }
	|	Expr OperatorAnd Expr { $$ = new COpExpr( $1, BO_And, $3 ); }
	|	IntNum { /*TODO*/ }
	|	True { $$ = new CTrueExpr(); }
	|	False { $$ = new CFalseExpr(); }
	|	Id { /*TODO*/ }
	|	This { $$ = new CThisExpr(); }
	|	New Int '[' Expr ']' { $$ = new CNewIntExpr( $4 ); }
	|	New Id '(' ')' { $$ = new CNewIdExpr( $2 ); }
	|	'!' Expr { $$ = new CNotExpr( $2 ); }
	|	'(' Expr ')' {/*TODO*/}
	;

ExprList
	:	Expr ExprRestList { $$ = new CExprList( $1, $2 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

ExprRestList
	: ',' Expr ExprRestList { $$ = new CExprList( $2, $3 ); }
	| /*epsilon*/ { $$ = 0; }
	;

%%