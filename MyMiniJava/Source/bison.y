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
extern int yylineno;
%} 

%error-verbose
%verbose
%locations

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
	char* sval;
}

%%
Program 
	:	MainClass ClassDeclarationList { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column );  yyprogram = $$ = new CProgram( info, $1, $2 ); }
	;

MainClass 
	:	Class Id '{' Public Static Void Main '(' String '[' ']' Id ')' '{' Statement '}' '}' { CCodeInfo info( @1.first_line, @1.first_column, @17.last_line, @17.last_column ); $$ = new CMainClass( info, $2, $12, $15 ); }
	;
	
VarDeclaration 
	: Type Id ';' { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CVarDecl( info, $1, $2 ); }
	;

VarDeclarationList 
	:	VarDeclarationList VarDeclaration { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CVarDeclList( info, $2, $1 ); }
	| /*eps*/ { $$ = 0; }
	;

ClassDeclaration 
	:	Class Id  '{' VarDeclarationList MethodDeclarationList '}' { CCodeInfo info( @1.first_line, @1.first_column, @6.last_line, @6.last_column ); $$ = new CClassDecl( info, $2, $4, $5 ); }
	|	Class Id Extends Id '{' VarDeclarationList MethodDeclarationList '}' { CCodeInfo info( @1.first_line, @1.first_column, @8.last_line, @8.last_column ); $$ = new CExtendClassDecl( info, $2, $4, $6, $7 ); }
	;

ClassDeclarationList
	:	ClassDeclaration ClassDeclarationList { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CClassDeclList( info, $1, $2 ); }
	|	/*epsilon*/ { $$ = 0; } 
	;

MethodDeclaration
	: Public Type Id '(' FormalList ')' '{' VarDeclarationList StatementList Return Expr ';' '}' { CCodeInfo info( @1.first_line, @1.first_column, @13.last_line, @13.last_column ); $$ = new CMethodDecl( info, $2, $3, $5, $8, $9, $11 ); }
	;

MethodDeclarationList
	:	MethodDeclarationList MethodDeclaration { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CMethodDeclList( info, $2, $1 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

FormalList	
	:	Type Id FormalRestList { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CFormalList( info, $1, $2, $3 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

FormalRestList
	: ',' Type Id FormalRestList { CCodeInfo info( @2.first_line, @2.first_column, @4.last_line, @4.last_column ); $$ = new CFormalList( info, $2, $3, $4 ); }
	| /*epsilon*/ { $$ = 0; }
	;

Type
	:	Int { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CTypeName( info, "int" ); }
	|	Int '[' ']' { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CTypeName( info, "array" ); }
    |	Bool { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CTypeName( info, "bool" ); }
    |	Id { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CTypeName( info, $1 ); }
	;

StatementList
	:	Statement StatementList { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CStmtList( info, $1, $2 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

Statement
	:	'{' StatementList '}' { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CGroupStmt( info, $2 ); }
	|	Id OperatorEq Expr ';' { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CAssignStmt( info, $1, $3 ); }
	|	If '(' Expr ')' Statement Else Statement { CCodeInfo info( @1.first_line, @1.first_column, @7.last_line, @7.last_column ); $$ = new CIfStmt( info, $3, $5, $7 ); }
	|	While '(' Expr ')' Statement { CCodeInfo info( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CWhileStmt( info, $3, $5 ); }
	|	Print '(' Expr ')' ';' { CCodeInfo info( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CSOPStmt( info, $3 ); }
	|	Id '[' Expr ']' OperatorEq Expr ';' { CCodeInfo info( @1.first_line, @1.first_column, @6.last_line, @6.last_column ); $$ = new CAssignExprStmt( info, $1, $3, $6 ); }
	;

Expr
	:	Expr '*' Expr { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new COpExpr( info, $1, BO_Mult, $3 ); }
	|   Expr '+' Expr { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new COpExpr( info, $1, BO_Plus, $3 ); }
	|	Expr '/' Expr { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new COpExpr( info, $1, BO_Div, $3 ); }
	|	Expr '-' Expr { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new COpExpr( info, $1, BO_Minus, $3 ); }
	|	'-' Expr %prec UMINUS { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CUnaryMinusExpr( info, $2 ); }
	|	Expr '[' Expr ']' { CCodeInfo info( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CExExpr( info,$1, $3);  }
	|	Expr '.' Length { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CLengthExpr( info, $1 ); }
	|	Expr '.' Id '(' ExprList ')' { CCodeInfo info( @1.first_line, @1.first_column, @6.last_line, @6.last_column ); $$ = new CMethodCallExpr( info, $1, $3, $5 ); }
	|	Expr OperatorLess Expr { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new COpExpr( info, $1, BO_Less, $3 ); }
	|	Expr OperatorAnd Expr { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new COpExpr( info, $1, BO_And, $3 ); }
	|	IntNum { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CIntExpr( info, $1 ); }
	|	True { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CTrueExpr( info ); }
	|	False { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CFalseExpr( info ); }
	|	Id { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CIdExpr( info, $1 ); }
	|	This { CCodeInfo info( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CThisExpr( info ); }
	|	New Int '[' Expr ']' { CCodeInfo info( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CNewIntExpr( info, $4 ); }
	|	New Id '(' ')' { CCodeInfo info( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CNewIdExpr( info, $2 ); }
	|	'!' Expr { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CNotExpr( info, $2 ); }
	|	'(' Expr ')' { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CBrExpr( info, $2 ); }
	;

ExprList
	:	Expr ExprRestList { CCodeInfo info( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CExprList( info, $1, $2 ); }
	|	/*epsilon*/ { $$ = 0; }
	;

ExprRestList
	: ',' Expr ExprRestList { CCodeInfo info( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExprList( info, $2, $3 ); }
	| /*epsilon*/ { $$ = 0; }
	;

%%