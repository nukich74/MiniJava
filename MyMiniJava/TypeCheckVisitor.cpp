#pragma once
#include "ClassInfo.h"
#include <map>
#include <utility>
#include "TypeCheckVisitor.h"
#include "syntaxTree.h"
#include <cassert>

using namespace SymbolsTable;

void CTCVisitor::Visit( const CProgram& p ) //MainClass ClassDeclList
{
	p.GetMainClass()->Accept( this );
	if( p.GetClassDeclList() ){
		p.GetClassDeclList()->Accept( this );
	}
}


void CTCVisitor::Visit( const CMainClass& p ) //class id { public static void main ( String [] id ) { Statement }}
{
	auto mainClassIter = table.find( p.GetName() );
	
	assert( mainClassIter != table.end() );

	currentClass = mainClassIter->second;
	currentMethod = currentClass->GetMethods()[0];
	
	p.GetStmt()->Accept( this );
	
	currentMethod = 0;
	currentClass = 0;
}

void CTCVisitor::Visit( const CClassDeclList& p )//ClassDeclList
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
}

void CTCVisitor::Visit( const CClassDecl& p ) //class id { VarDeclList MethodDeclList }
{

	assert( currentMethod == 0 ); 

	auto classIter = table.find( p.GetName() );
	assert( classIter != table.end() );
	currentClass = classIter->second;

	if( p.GetMethodDeclList() != 0 ) {
		p.GetMethodDeclList()->Accept( this );
	}
	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}

	currentClass = 0;
}

void CTCVisitor::Visit( const CExtendClassDecl& p ) //class id extends id { VarDeclList MethodDeclList }
{
	assert( currentMethod == 0 ); 	

	auto classIter = table.find( p.GetClassName() );
	assert( classIter != table.end() );
	currentClass = classIter->second;


	if( p.GetMethodDeclList() != 0 ) {
		p.GetMethodDeclList()->Accept( this );
	}
	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}

	currentClass = 0;
}

void CTCVisitor::Visit( const CVarDecl& p ) //Type id
{ 
	assert( currentClass != 0 );

}

void CTCVisitor::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}

	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}

	currentMethod = 0;	
}

void CTCVisitor::Visit( const CFormalList& p )//Type Id FormalRestList
{
	assert( currentMethod != 0 ); 

	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}	
}


void CTCVisitor::Visit( const CVarDeclList& p )
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}

void CTCVisitor::Visit( const CMethodDeclList& p )
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}


void CTCVisitor::Visit( const CStmtList& p )
{
	p.GetStmt()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}


void CTCVisitor::Visit( const CGroupStmt& p ) //{ Statement* }
{
}

void CTCVisitor::Visit( const CIfStmt& p ) //if ( Exp ) Statement else Statement
{
}

void CTCVisitor::Visit( const CWhileStmt& p )//while ( Exp ) Statement
{
}

void CTCVisitor::Visit( const CSOPStmt& p )//System.out.println ( Exp ) ;
{
}

void CTCVisitor::Visit( const CAssignStmt& p )//id = Exp ;
{
}

void CTCVisitor::Visit( const CAssignExprStmt& p )//id [ Exp ] = Exp;
{
}

void CTCVisitor::Visit( const COpExpr& p )//Exp op Exp
{
}

void CTCVisitor::Visit( const CExExpr& p )//Exp [ Exp ]
{
}

void CTCVisitor::Visit( const CMethodCallExpr& p )//Exp . id ( ExpList )
{
}

void CTCVisitor::Visit( const CIntExpr& p )//num
{
}

void CTCVisitor::Visit( const CTrueExpr& p )//true
{
}

void CTCVisitor::Visit( const CFalseExpr& p )//false
{
}

void CTCVisitor::Visit( const CNameExpr& p )//id
{
}

void CTCVisitor::Visit( const CThisExpr& p )//this
{
}

void CTCVisitor::Visit( const CNewIntExpr& p )//new int [ Exp ]
{
}

void CTCVisitor::Visit( const CNewIdExpr& p )//new id ()
{
}

void CTCVisitor::Visit( const CNotExpr& p )//! Exp
{
}

void CTCVisitor::Visit( const CBrExpr& p )//( Exp )
{
}

void CTCVisitor::Visit( const CTypeName& p )// id
{
}


void CTCVisitor::Visit( const CExprList& p )//Exp , ExpList
{
}
 
void CTCVisitor::Visit( const CIdExpr& p )
{
}


void CTCVisitor::Visit( const CLengthExpr& p ) // Expr . length
{
}

void CTCVisitor::Visit( const CUnaryMinusExpr& p ) // - Expr
{
}