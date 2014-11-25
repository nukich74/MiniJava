#pragma once
#include "iVisitor.h"
#include "syntaxTree.cpp"
 
class PrettyPrintVisitor: public IVisitor
{
public:
	~PrettyPrintVisitor();
	void Visit( const CProgram& p );
	void Visit( const CMainClass& p );
	void Visit( const CClassDeclList& p );
	void Visit( const CClassDecl& p );	
};