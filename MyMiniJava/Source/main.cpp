#pragma once
//"$(SolutionDir)samples\treevisitor.java"  "$(SolutionDir)samples\binarysearch.java" "$(SolutionDir)samples\binarytree.java" "$(SolutionDir)samples\bubblesort.java" "$(SolutionDir)samples\linearsearch.java" "$(SolutionDir)samples\quicksort.java" "$(SolutionDir)errorSamples\cycle.java" 
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
#include "IRTransformer.h"
#include <cstdlib>
#include <ctime>
#include "BlockTracing.h"
#include "IRTreePrinter.h"
#include "RegisterDistribution.h"
#include "AsmTreeMaker.h"
#include "Builders.h"

#define DEBUG_TO_FILE

using namespace SymbolsTable;

typedef std::map< std::string,  CClassInfo* > SymbolTable;

extern "C" int yyparse();
extern FILE* yyin;
extern int yylineno;
extern Tree::IProgram* yyprogram;
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

void printErrors( const std::vector< CSemanticError* >& errors ) {
	for( auto& item: errors ) {
		std::cout << item->What() << '\n';
	}
}


int main( int argc, char* argv[] )
{
	std::srand( std::time(0) );
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
			extern int curr_line;
			extern int curr_col;
			curr_line = 1;
			curr_col = 1;
			
			do {
				int rCode = yyparse(); // ������ �� �������

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

				if( !symbolTableVisitor.isSuccessfull() ) {
					printErrors( symbolTableVisitor.GetErrors() );
					continue;
				}
				if( !typeCheckVisitor.isSuccessfull() ) {
					printErrors( typeCheckVisitor.GetErrors() );
					continue;
				}

				//SymbolTablePrint(symbolTable);

				Translate::CIRTreeVisitor cIrTreeVis( symbolTable );
				yyprogram->Accept( &cIrTreeVis );

				int functionId = 0;
				for( auto& item : cIrTreeVis.functions ) {
					Canon::CCanon cc;
					Canon::CTracer tr;
					IRTree::IRTreePrinter printer;
					const IRTree::IStmt* root = item->funcRoot;

					root->Accept( &printer );
					std::cout << item->name << " Before:" << std::endl << printer.GetResult() << std::endl;
					printer.Clear();

					const IRTree::CStmtList* linearList = cc.Linearize( root );
					linearList->Accept( &printer );
					std::cout << "After eseq/seq/call transform:" << std::endl << printer.GetResult() << std::endl;

					printer.Clear();
					const IRTree::CStmtList* result = tr.Transform( linearList );
					result->Accept( &printer );
					std::cout << "After block processing:" << std::endl << printer.GetResult();

					
					Assembler::CAsmTreeMaker treeMaker( item );
					treeMaker.InitializeTree( result );
					std::cout << "\nAsmInstr\n";
					std::cout << item->name << '\n';
					std::cout << treeMaker.GetAsmInstr().size() << std::endl;
					Assembler::CInterferenceGraph graph( treeMaker.GetAsmInstr(), item->GetRegisters() );

					auto code = graph.GetCode();
					auto colors = graph.GetColors();

					std::cout << "Colors:\n";
					for( auto it : colors ) {
						std::cout << it.first << ' ' << it.second << std::endl;
					}
					
					PrologEpilogBuilder::IntermidInstructionBuilder builder;
					auto epilog = builder.AddEpilog( item );
					auto prolog = builder.AddProlog( item );
					std::cout << "Commands:\n";
					for( const auto& item : prolog ) {
						std::cout << item << '\n';
					}
					for( auto cmd : code ) {
						std::cout << cmd->FormatInstr( colors );
					}
					for( const auto& item : epilog ) {
						std::cout << item << '\n';
					}
				}

			} while( !feof( yyin ) );
			
		}
	}

#ifndef DEBUG_TO_FILE
	system( "pause" );
#endif
	return 0;
}