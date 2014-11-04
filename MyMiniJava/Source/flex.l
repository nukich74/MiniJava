%option noyywrap
%{
#include <stdlib.h>
#include <stdio.h>	
#include <string.h>
#include <math.h>
#include "bison.tab.h"
#include <iostream>

#define YY_DECL extern "C" int yylex()
#define yyterminate() return YY_NULL
%}

NUMBER ([1-9][0-9]*)|(0)
Comment (/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/)|(//.*)*

%%

"class" { std::cout << yytext << std::endl; return Class; }

"public" { std::cout << yytext << std::endl;  return Public; }

"static" { std::cout << yytext << std::endl;  return Static; }

"void" { std::cout << yytext << std::endl;  return Void; }

"main" {  std::cout << yytext << std::endl; return Main; }

"String" { std::cout << yytext << std::endl;  return String; }

"extends" { std::cout << yytext << std::endl;  return Extends; }

"return" { std::cout << yytext << std::endl;  return Return; }

"int" { std::cout << yytext << std::endl;  return Int; }

"boolean" {  std::cout << yytext << std::endl; return Bool; }

"if" { std::cout << yytext << std::endl;  return If; }

"else" { std::cout << yytext << std::endl;  return Else; }

"while" { std::cout << yytext << std::endl;  return While; }

"System.out.println" { std::cout << yytext << std::endl;  return  Print; }

"length" { std::cout << yytext << std::endl; 	return Length;	}

"true" { std::cout << yytext << std::endl; 	return True; }

"false" { std::cout << yytext << std::endl; 	return False; }

"this" { std::cout << yytext << std::endl; 	return This; }

"new" {	 std::cout << yytext << std::endl; return New; }

"<" { return OperatorLess; }
">" { return OperatorMore; }
"&&" { return OperatorAnd; }
"=" { std::cout << "=" << std::endl; return OperatorEq; }

[\+\-\*/] return yytext[0];

Comment { std::cout << yytext << std::endl;  }

[\[\]\)\(\{\}\;\.] {  std::cout << yytext[0] << std::endl; return yytext[0]; }

[a-zA-Z_][a-zA-Z0-9_]* { std::cout << "Found id: " << yytext << std::endl; return Id; }


({NUMBER}) {  std::cout << yytext << std::endl; yylval.ival = atoi( yytext ); return IntNum; }

"\n" 	{ std::cout << "blank" << std::endl; }

"\t"	{ std::cout << "blank" << std::endl; }

" "	{ std::cout << "blank" << std::endl; }

<<EOF>>	{
	std::cout << "EOF" << std::endl;
}

. 	{ std::cout  << "Unknown: <" << yytext << ">" << std::endl;  }

%%