#define _USE
#include <cstdio>
#include <iostream>
#include <string>
#include "grammar.h"

//#include "prettyPrintVisitor.h"


extern "C" int yyparse();
extern FILE* yyin;
extern int yylineno;

IProgram* core;


void yyerror( const char* s ) {
	std::cout << s << std::endl;
	getchar();
}
 
int main( int argc, char* argv[] )
{

	for( int i = 1; i < argc; i++ ) {
		std::string inputFileName = argv[i];
		std::cout << "Processing file: " << inputFileName << std::endl;

		FILE* program;
		if( fopen_s( &program, inputFileName.c_str(), "r" ) ) {
			std::cout << "I can't open file!" << std::endl;
		} else {
			yylineno = 0;
			yyin = program;

			do {
				int rCode = yyparse();
				if( rCode != 0 ) {
					std::cout << "Error code: " << rCode << std::endl;
					break;
				}
			} while( !feof( yyin ) );
		}
	}


	return 0;
}