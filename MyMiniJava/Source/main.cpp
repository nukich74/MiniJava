#pragma once

#include "prettyPrintVisitor.h"
#include <utility>
#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <string>
#include <cassert>
#include "SymVisitor.h"
#include "TypeCheckVisitor.h"
#include <IRTreeVisitor.h>

//#define DEBUG_TO_FILE


using namespace SymbolsTable;

//extern std::map< std::string, CClassInfo* > table;

typedef std::map< std::string,  CClassInfo* > SymbolTable;

extern "C" int yyparse();
extern FILE* yyin;
extern int yylineno;
extern IProgram* yyprogram;
std::unordered_set< std::string > symbolStorage;

void yyerror( const char* s ) {
	std::cout << s << std::endl;
	getchar();
}
 

void SymbolTablePrint(const SymbolTable* symbolTable) {

	std::cout << "Symbol table size: " << symbolTable->size() << std::endl;
				
	for( auto it = symbolTable->begin(); it != symbolTable->end(); ++it ) {
		std::cout << "-------------------------------" << std::endl;
		std::cout << "Class name : " << it->first << "\n" << std::endl;
		std::cout << "Class methods: \n" << std::endl;
		for ( auto z = it->second->GetMethods().begin(); z != it->second->GetMethods().end(); ++z ) {
			std::cout << (*z)->GetName() << std::endl;
					
		}

		std::cout << "\n";
		std::cout << "Class variables: \n" << std::endl;
		for ( auto z = it->second->GetLocals().begin(); z != it->second->GetLocals().end(); ++z ) {
			std::cout << (*z)->GetName() << std::endl;
					
		}
	}
				
	std::cout << "-------------------------------" << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << "\n\n";
}


int main( int argc, char* argv[] )
{

#ifdef DEBUG_TO_FILE
	freopen( "debugOutput.txt", "w", stdout);
#endif

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

				//PrettyPrintVisitor prittyPrint;
				//yyprogram->Accept( &prittyPrint );

				SymbolsTable::CSTVisitor symbolTableVisitor;
				yyprogram->Accept( &symbolTableVisitor );

				const SymbolTable* symbolTable = symbolTableVisitor.GetTable();
				SymbolsTable::CTCVisitor typeCheckVisitor( *symbolTable );

				yyprogram->Accept( &typeCheckVisitor );

				SymbolTablePrint(symbolTable);

				Translate::CIRTreeVisitor cIrTreeVis;
				yyprogram->Accept( &cIrTreeVis );
				
			} while( !feof( yyin ) );
			
		}
	}

#ifndef DEBUG_TO_FILE
	system( "pause" );
#endif
	return 0;
}