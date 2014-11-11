%option yylineno
%option noyywrap
%{
#include <cstdlib>
#include <cstdio>	
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include "bison.tab.h"

#define YY_DECL extern "C" int yylex()
#define yyterminate() return YY_NULL

/*extern "C" int yywrap() {
	return 1;
}*/


void printToken( const std::string& token ) {
	std::cout << token;
}

%}

NUMBER ([1-9][0-9]*)|(0)
Comment (/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/)|(//.*)*

%%

"class" { printToken( yytext ); return Class; }

"public" { printToken( yytext );  return Public; }

"static" { printToken( yytext );  return Static; }

"void" { printToken( yytext );  return Void; }

"main" {  printToken( yytext ); return Main; }

"String" { printToken( yytext );  return String; }

"extends" { printToken( yytext );  return Extends; }

"return" { printToken( yytext );  return Return; }

"int" { printToken( yytext );  return Int; }

"boolean" {  printToken( yytext ); return Bool; }

"if" { printToken( yytext );  return If; }

"else" { printToken( yytext );  return Else; }

"while" { printToken( yytext );  return While; }

"System.out.println" { printToken( yytext );  return  Print; }

"length" { printToken( yytext ); 	return Length;	}

"true" { printToken( yytext ); 	return True; }

"false" { printToken( yytext ); 	return False; }

"this" { printToken( yytext ); 	return This; }

"new" {	 printToken( yytext ); return New; }

"//"[^"\n"]+ { }

Comment { printToken( yytext );  }

[a-zA-Z_][a-zA-Z0-9_]* { std::cout << yytext; return Id; }

"<" { return OperatorLess; }
">" { return OperatorMore; }
"&&" { return OperatorAnd; }
"=" { std::cout << "="; return OperatorEq; }

[\+\-\*/] return yytext[0];

[\[\]\)\(\{\}\;\.,] {  std::cout << yytext[0]; return yytext[0]; }


({NUMBER}) {  printToken( yytext ); yylval.ival = atoi( yytext ); return IntNum; }

" "	{ std::cout << " "; }
"\n" 	{ std::cout << "\n" << yylineno << ": "; }
"\t"	{ std::cout << "\t"; }



<<EOF>>	{
	std::cout << "EOF" << std::endl;
	yyterminate();
}

. 	{ std::cout  << "Unknown: <" << yytext << ">" << std::endl;  }

%%