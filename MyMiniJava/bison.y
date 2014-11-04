%{       
#include <cstdio>
#include <iostream>

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
void yyerror(const char *s);

%} 

%union {
	int ival;
	float fval;
}

%error-verbose


%left '<' '>' '='
%left '+' '-'
%left '*' '/'
%left '&'
%nonassoc UMinus '!'

%token VarDeclarations
%token StatememtList
%token Id
%token IntNum
%token FloatNum
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

%%
Program 
	:	MainClass ClassDeclarationList { }
	;

MainClass 
	:	Class Id '{' Public Static Void Main '(' String '[' ']' SR_BRACKET Id ')' '{' Statement '}' '}' {}
	;
	
VarDeclaration 
	: Type Id ';' { };
	;

VarDeclarationList 
	:	VarDeclarationList VarDeclaration
	|	/*epsilon*/
	;

ClassDeclaration 
	:	ClassDeclaration Class Id  '{' VarDeclaration MethodDeclaration '}' { }
	|	ClassDeclaration Class Id Extends Id '{' VarDeclarationList MethodDeclarationList '}' { }
	| /* epsilon */  { }
	;

ClassDeclarationList
	:	ClassDeclaration ClassDeclarationList { }
	|	/*epsilon*/ { }
	;

MethodDeclaration
	: Public Type Id '(' FormalList ')' '{' VarDeclarationList StatementList Return Expr ';' '}'
	;

MethodDeclarationList
	:	MethodDeclarationList MethodDeclaration 
	|	/*epsilon*/
	;

FormalList	
	:	Type Id FormalRestList
	|	/*epsilon*/
	;

FormalRestList
	: ',' Type Id FormalRestList
	| /*epsilon*/
	;

Type
	:	Int
    |	Bool
    |	Id
	;

StatementList
	:	Statement StatementList
	|	/*epsilon*/
	;

Statement
	:	'{' StatementList '}'
	|	If '(' Expr ')' Statement Else Statement
	|	While '(' Expr ')' Statement
	|	Print '(' Expr ')' ';'
	|	Id '=' Expr ';'
	|	Id '[' Expr ']' '=' Expr ';'
	;

Expr
	:	Expr '+' Expr
	|	Expr '-' Expr
	|	Expr '*' Expr
	|	Expr '/' Expr
	|	Expr '&' Expr
	|	Expr '[' Expr ']'
	|	Expr '.' Length
	|	Expr '.' Id '(' ExprList ')'
	|	IntNum
	|	FloatNum
	|	True
	|	False
	|	Id 
	|	This
	|	New Int '[' Expr ']'
	|	New Id '(' ')'
	|	'!' Expr
	|	'(' Expr ')'
	;

ExprList
	:	Expr ExprRest 
	|	/*epsilon*/
	;

ExprRest
	: ',' Expr 
	| /*epsilon*/
	;

%%
