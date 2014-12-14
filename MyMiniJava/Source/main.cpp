#include "prettyPrintVisitor.h"
#include <utility>
#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <string>
#include <cassert>

extern "C" int yyparse();
extern FILE* yyin;
extern int yylineno;
extern IProgram* yyprogram;
std::unordered_set< std::string > symbolStorage;

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
				int rCode = yyparse(); // парсим на лексемы

				if( rCode != 0 ) {
					std::cout << "Error code: " << rCode << std::endl;
					break;
				}

				PrettyPrintVisitor prittyPrint;
				yyprogram->Accept( &prittyPrint );

			} while( !feof( yyin ) );
			
		}
	}

	int g;
	std::cin >> g;

	return 0;
}