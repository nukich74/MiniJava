%{
#include <stdlib.h>
#include <stdio.h>	
#include <string.h>

static int lineNumber = 0;
static int linePositionNumber = 0;

%}

NUMBER ([1-9][0-9]*)|(0)
ID 		[a-zA-z][_a-z0-9a-z]*
BINARYOP ([\<\+\-\*])|(\&\&)
Comment (/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/)|(//.*)*

%%

"class" {
	printf( "CLASS" );
}

"public" {
	printf( "PUBLIC" );
	
}

"static" {
	printf( "STATIC" );
	
}

"void" {
	printf( "VOID" );
	
}

"main" {
	printf( "MAIN" );
	
}

"String" {
	printf( "STRING" );
	
}

"extends" {
	printf( "EXTENDS" );
}

"return" {
	printf( "RETURN" );
	
}

"int" {
	printf( "INT" );
	
}

"boolean" {
	printf( "BOOL" );
	
}

"if" {
	printf( "IF" );
	
}

"else" {
	printf( "ELSE" );
	
}

"while" {
	printf( "WHILE" );
	
}

"System.out.println" {
	printf( "PRINT" );
	
}

"length" {
	printf( "LENGHT" );
	
}

"true" {
	printf( "TRUE" );
	
}

"false" {
	printf( "FALSE" );
	
}

"this" {
	printf("THIS");
	
}

"new" {
	printf("NEW");
	
}

";"	{
	printf( "SEMICOLON" );
	
}

Comment {
	printf( "COMMENT(%s)", yytext + 2 );
	
}

"\"".*"\"" {
	printf( "STR(%s)", yytext );
	
}

"," {
	printf( "COMMA" );
	
}

"!" {
	printf( "NOT" );
	
}

"*" {
	printf( "STAR" );
	
}

"{" {
	printf( "LBRACE" );
	
}

"}" {
	printf( "RBRACE" );
	
}

"(" {
	printf( "LPAREN" );
	
}

")" {
	printf( "RPAREN" );
	
}

{ID} {
	printf( "ID(%s)", yytext );
	
}

("-"?{NUMBER}|{NUMBER}) {
	printf( "NUM(%s)", yytext );
	
}

(("-"?{NUMBER}"."{NUMBER})|({NUMBER}"."{NUMBER}))	{
	printf( "REAL(%s)", yytext );
	
}

[\t\r\n\ ]+ 	{
	printf( "\n" );
}

<<EOF>>	{
	printf( "EOF" );
	yyterminate();
}

. 	{
	return yytext[0];
}

%%