%{
#include <stdio.h> /* for printf() */
#include <stdlib.h>
#include "miniJava.h"
#include <iostream>

// должны быть объявлены
// приоритет, чтобы писать операции основываясь на приоритетах при этом не изменяя правил грамматики (решает проблемы неоднозначности)
int yylex(void);
void yyerror(char const*);

%}

%union {
	Expr *expr;

	Expr *var;

	LogExpr *log_expr;
	Stmt *stmt;
	ListStmt *list_stmt;

	ListExpr *list_expr;

	int int_val;
	char ident_name[256];
}; /* тип yylval */

/* Precedence */
%left '+' '-'
%left '*' '/'
%right POW
%nonassoc UMINUS

%token <int_val> NUMERAL
%token <ident_name> IDENT
%token PRINT IF THEN ELSE ENDIF EQ NR WHILE DO BEGIN END FOR TO VAR READLN WRITELN WRITE RETURN INTEGER PROBEL PROGRAM

%type <expr> expr

%type <expr> var

%type <log_expr> log_expr
%type <list_stmt> list_stmt
%type <stmt> stmt

%type <list_expr> list_expr

%%

program
	: list_stmt { Program = $1; }
	;



list_stmt
	: list_stmt stmt separator { $1->add($2); $$=$1; }
	| /* epsilon */ { $$ = new ListStmt; }
	;

list_expr
	: list_expr expr gap { $1->add($2); $$=$1; }
	| /* epsilon */ { $$ = new ListExpr; }
	;

gap
	: ','
	| gap ','
	| ':'
	;

separator
	: '\n'
	| separator '\n'
	;

var
	: PROGRAM IDENT ';' separator VAR list_expr INTEGER ';' separator BEGIN { $$ = new ExprForVar($6); }
	;

stmt
	: PRINT expr { $$ = new StmtPrint($2, true); } 
	| var  
	| RETURN '(' expr ')'  { $$ = new StmtReturn($3); }	
	| RETURN  { $$ = new StmtReturn(NULL); }
	| IDENT ':' EQ expr ';' { $$ = new StmtAssign($1, $4); }
	| IF log_expr THEN separator stmt ';' { $$  = new StmtIfWithOneExpr($2, $5, NULL); }
	| IF log_expr THEN separator stmt separator ELSE separator stmt { $$ = new StmtIfWithOneExpr($2, $5, $9); }
	| IF log_expr THEN separator BEGIN separator list_stmt END separator ELSE separator BEGIN separator list_stmt END { $$ = new StmtIf($2, $7, $14); }
	| IF log_expr THEN separator BEGIN separator list_stmt END ';' { $$ = new StmtIf($2, $7, NULL); }
	| WHILE log_expr DO separator BEGIN separator list_stmt END  { $$ = new StmtWhile($2, $7); }
	| WHILE log_expr DO separator stmt { $$ = new StmtWhileForOneCommand($2, $5); }
	| FOR IDENT EQ expr TO expr DO separator BEGIN separator list_stmt END { $$ = new StmtFor($2, $4, $6, $11); }
	| FOR IDENT EQ expr TO expr DO separator stmt { $$ = new StmtForForOneCommand($2, $4, $6, $9); }
	| READLN '(' IDENT ')'  { $$ = new StmtReadln($3); }
	| WRITELN '(' expr ')'  { $$ = new StmtPrint($3, true); }
	| WRITE '(' expr ')'  { $$ = new StmtPrint($3, false); }
	;

log_expr
	: expr '<' expr { $$ = new LogExpr('<', $1, $3); }
	| expr '>' expr { $$ = new LogExpr('>', $1, $3); }
	| expr EQ expr	{ $$ = new LogExpr('=', $1, $3); }
	| expr NR expr  { $$ = new LogExpr('n', $1, $3); }
	;
expr
	: IDENT  { $$ = new ExprVariable($1); }
	| NUMERAL 		{ $$ = new ExprNumeral($1); }
	| '-' expr %prec UMINUS	{ $$ = new ExprArith(UMINUS, $2, NULL); }
	| expr '+' expr		{ $$ = new ExprArith('+', $1, $3); }
	| expr '-' expr		{ $$ = new ExprArith('-', $1, $3); }
	| expr '*' expr		{ $$ = new ExprArith('*', $1, $3); }
	| expr '/' expr		{ $$ = new ExprArith('/', $1, $3); }	
	| expr POW expr		{ $$ = new ExprArith(POW, $1, $3); }
	| '(' expr ')'		{ $$ = $2; }
	;

%%
