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
extern IProgram* yyprogram = 0;

%} 

%error-verbose
%verbose

%type<program> Program
%type<mainClass> MainClass
%type<classDeclList> ClassDeclarationList
%type<classDecl> ClassDeclaration
%type<varDeclList> VarDeclarationList
%type<varDecl> VarDeclaration
%type<methodDeclList> MethodDeclarationList
%type<methodDecl> MethodDeclaration
%type<formalList> FormalList
%type<formalList> FormalRestList
%type<type> Type
%type<stmtList> StatementList
%type<stmt> Statement
%type<exprList> ExprList
%type<exprList> ExprRestList
%type<expr> Expr

%token<sval> Id

%token<ival> IntNum
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
}

%%
Program 
	:	MainClass ClassDeclarationList { yyprogram = $$ = new CProgram( $1, $2 ); }
	;

MainClass 
	:	Class Id '{' Public Static Void Main '(' String '[' ']' Id ')' '{' Statement '}' '}' { $$ = new CMainClass( $2, $12, $15 ); }
	;
	
VarDeclaration 
	: Type Id ';' { $$ = new CVarDecl( $1, $2 ); }
	;

VarDeclarationList 
	:	VarDeclarationList VarDeclaration { $$ = new CVarDeclList( $2, $1 ); }
	| /*eps*/ { $$ = 0; }
	;

ClassDeclaration 
	:	Class Id  '{' VarDeclarationList MethodDeclarationList '}' { $$ = new CClassDecl( $2, $4, $5 ); }
	|	Class Id Extends Id '{' VarDeclarationList MethodDeclarationList '}' { $$ = new CExtendClassDecl( $2, $4, $6, $7 ); }
	;

ClassDeclarationList
	:	ClassDeclaration ClassDeclarationList { $$ = new CClassDeclList( $1, $2 ); }
	|	/*epsilon*/ { $$ = 0; } 
	;

MethodDeclaration
	: Public Type Id '(' FormalList ')' '{' VarDeclarationList StatementList Return Expr ';' '}' { $$ = new CMethodDecl( $2, $3, $5, $8, $9, $11 ); }
	;

MethodDeclarationList
	:	MethodDeclarationList MethodDeclaration { $$ = new CMethodDeclList( $2, $1 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

FormalList	
	:	Type Id FormalRestList { $$ = new CFormalList( $1, $2, $3 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

FormalRestList
	: ',' Type Id FormalRestList { $$ = new CFormalList( $2, $3, $4 ); }
	| /*epsilon*/ { $$ = 0; }
	;

Type
	:	Int { $$ = new CTypeName( "int" ); }
	|	Int '[' ']' { $$ = new CTypeName( "array" ); }
    |	Bool { $$ = new CTypeName( "bool" ); }
    |	Id { $$ = new CTypeName( $1 ); }
	;

StatementList
	:	Statement StatementList { $$ = new CStmtList( $1, $2 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

Statement
	:	'{' StatementList '}' { $$ = new CGroupStmt( $2 ); }
	|	Id OperatorEq Expr ';' { $$ = new CAssignStmt( $1, $3 ); }
	|	If '(' Expr ')' Statement Else Statement { $$ = new CIfStmt( $3, $5, $7 ); }
	|	While '(' Expr ')' Statement { $$ = new CWhileStmt( $3, $5 ); }
	|	Print '(' Expr ')' ';' { $$ = new CSOPStmt( $3 ); }
	|	Id '[' Expr ']' OperatorEq Expr ';' { $$ = new CAssignExprStmt( $1, $3, $6 ); }
	;

Expr
	:	Expr '*' Expr { $$ = new COpExpr( $1, BO_Mult, $3 ); }
	|   Expr '+' Expr { $$ = new COpExpr( $1, BO_Plus, $3 ); }
	|	Expr '/' Expr { $$ = new COpExpr( $1, BO_Div, $3 ); }
	|	Expr '-' Expr { $$ = new COpExpr( $1, BO_Minus, $3 ); }
	|	'-' Expr %prec UMINUS { $$ = new CUnaryMinusExpr( $2 ); }
	|	Expr '[' Expr ']' { $$ = new CExExpr($1, $3);  }
	|	Expr '.' Length { $$ = new CLengthExpr( $1 ); }
	|	Expr '.' Id '(' ExprList ')' { $$ = new CMethodCallExpr( $1, $3, $5 ); }
	|	Expr OperatorLess Expr { $$ = new COpExpr( $1, BO_Less, $3 ); }
	|	Expr OperatorAnd Expr { $$ = new COpExpr( $1, BO_And, $3 ); }
	|	IntNum { $$ = new CIntExpr( $1 ); }
	|	True { $$ = new CTrueExpr(); }
	|	False { $$ = new CFalseExpr(); }
	|	Id { $$ = new CIdExpr( $1 ); }
	|	This { $$ = new CThisExpr(); }
	|	New Int '[' Expr ']' { $$ = new CNewIntExpr( $4 ); }
	|	New Id '(' ')' { $$ = new CNewIdExpr( $2 ); }
	|	'!' Expr { $$ = new CNotExpr( $2 ); }
	|	'(' Expr ')' { $$ = new CBrExpr( $2 ); }
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