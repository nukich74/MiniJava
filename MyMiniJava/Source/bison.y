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


%left '+' '-'
%left '*' '/'
%left OperatorLess OperatorMore OperatorAnd OperatorEq

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
%token _EOF
%start Program

%%
Program 
	:	MainClass ClassDeclarationList { }
	;

MainClass 
	:	Class Id '{' Public Static Void Main '(' String '[' ']' Id ')' '{' Statement '}' '}' {}
	;
	
VarDeclaration 
	: Type Id ';' { std::cout << "declared Var" << std::endl; };
	;

VarDeclarationList 
	:	VarDeclarationList VarDeclaration
	| /*eps*/ { std::cout << "end of var decl" << std::endl; }
	;

ClassDeclaration 
	:	Class Id  '{' VarDeclarationList MethodDeclarationList '}' { }
	|	Class Id Extends Id '{' VarDeclarationList MethodDeclarationList '}' { }
	;

ClassDeclarationList
	:	ClassDeclaration ClassDeclarationList { }
	|	/*epsilon*/
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
	|	Id OperatorEq Expr ';'
	|	If '(' Expr ')' Statement Else Statement
	|	While '(' Expr ')' Statement
	|	Print '(' Expr ')' ';'
	|	Id '[' Expr ']' OperatorEq Expr ';'
	;

Expr
	:	Expr '+' Expr
	|	Expr '-' Expr
	|	Expr '*' Expr
	|	Expr '/' Expr
	|	Expr OperatorLess Expr
	|	Expr OperatorAnd Expr
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
	|	'(' Expr ')'
	;

ExprList
	:	Expr ExprRest 
	|	/*epsilon*/
	;

ExprRest
	: ',' Expr ExprRest
	| /*epsilon*/
	;

%%
