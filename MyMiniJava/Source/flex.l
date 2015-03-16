%option yylineno
%option noyywrap
%{
#pragma once
#include <cstdlib>
#include <cstdio>	
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include "syntaxTree.h"
#include "bison.tab.h"
#include <sstream>
#include <unordered_set>

int curr_line = 1;
int curr_col = 1;

static void updateLocation(){
	yylloc.first_line   = curr_line;
	yylloc.first_column = curr_col;

	for( char* s = yytext; *s != '\0'; s++ ){
		if( *s == '\n' ) {
			curr_line++;
			curr_col = 1;
		} else {
			curr_col++;
		}
	}

	yylloc.last_line   = curr_line;
	yylloc.last_column = curr_col - 1;
}


#define YY_USER_ACTION updateLocation();
#define YY_DECL extern "C" int yylex()
#define yyterminate() return YY_NULL

extern std::unordered_set< std::string > symbolStorage;
char* data;

/*extern "C" int yywrap() {
	return 1;
}*/


void printToken( const std::string& token ) {
//	std::cout << token;
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

[a-zA-Z_][a-zA-Z0-9_]* { 
	printToken( yytext ); 
	//так нельзя наверное?
	data = new char[strlen( yytext ) + 1];
	strcpy_s( data, strlen( yytext ) + 1, yytext );
	auto insertRes = symbolStorage.insert( data );
	if( insertRes.second == false ) {
		delete[] data;
	}
	yylval.sval = const_cast<char*>( ( insertRes.first )->c_str() );
	return Id; 
}

"<" { return OperatorLess; }
">" { return OperatorMore; }
"&&" { return OperatorAnd; }
"=" { printToken( "=" ); return OperatorEq; }

[\+\-\*/] return yytext[0];

[\[\]\)\(\{\}\;\.,!] {  printToken( yytext ); return yytext[0]; }


({NUMBER}) {  printToken( yytext ); yylval.ival = atoi( yytext ); return IntNum; }

" "	{ printToken( " " ); }
"\n" 	{ printToken( "\n" + std::to_string( yylineno ) + ": " ); }
"\t"	{ printToken( "\t" ); }



<<EOF>>	{
	printToken( "EOF\n" );
	yyterminate();
}

. 	{ 
	std::cout  << "Unknown: <" << yytext << ">" << std::endl;  
	getchar(); //нужно остановиться, если
}

%%