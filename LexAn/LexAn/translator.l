%{
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for strcpy() and exit() */
#include <stdio.h> /* for printf() */
#include <iostream>
#include "miniJava.h"  /*сейчас пишем лексический анализатор*/
#include "miniJavaInter.hpp"
%}




IDENT [A-Za-z][A-Za-z0-9]*
NUMERAL ([1-9][0-9]*)|0


%option noyywrap

%%

"program"       { return PROGRAM;}

"end."          {}   


","		{ return ','; }
"integer"	{ return INTEGER; }
";"             { return ';'; }
":"		{ return ':'; }
"return"   	{ return RETURN; }

"readln"	{ return READLN; }
"writeln"       { return WRITELN; }
"write"         { return WRITE; }


"begin"         { return BEGIN; }
"end"           { return END; }
"var"		{ return VAR; }
"<>"            { return NR; }


"while"         { return WHILE; }
"do"            { return DO; }  
"for"  		{ return FOR; }
"to"		{ return TO; }  


"print" 	{ return PRINT; }
"if"		{ return IF; }
"then"		{ return THEN; }
"else"		{ return ELSE; }
"endif"		{ return ENDIF; }
{NUMERAL}	{ yylval.int_val = atoi(yytext); return NUMERAL; }
{IDENT}		{ strcpy(yylval.ident_name, yytext); return IDENT; }
"="		{ return EQ; }
"<"		{ return '<'; }
">"		{ return '>'; }
"**"		{ return POW; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
"("		{ return '('; }
")"		{ return ')'; }


\n|;		{ return '\n'; }


   
" "            	
.		{ printf("Lexical error: symbol '%c'!\n", yytext[0]); exit(1); }

%%

