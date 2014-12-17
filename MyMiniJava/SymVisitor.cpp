#pragma once
#include "ClassInfo.h"
#include <map>
#include <utility>
#include "SymVisitor.h"
#include "syntaxTree.h"
#include <cassert>

using namespace SymbolsTable;

void CSTVisitor::Visit( const CProgram& p ) //MainClass ClassDeclList
{
	p.GetMainClass()->Accept( this );
	if( p.GetClassDeclList() ){
		p.GetClassDeclList()->Accept( this );
	}
}


void CSTVisitor::Visit( const CMainClass& p ) //class id { public static void main ( String [] id ) { Statement }}
{
	// добавляем класс в таблицу символов
	CClassInfo* mainClass = new CClassInfo( p.GetNameFirst(), "" );
	
	CMethodInfo* mainFunction = new CMethodInfo( "void", "main" );
	(*mainClass).AddMethod( mainFunction );

	// переменные, переданные в агрументах main(), есть локальными переменными
	//CVariableInfo* mainParams =  new CVariableInfo( "String", p.GetArgsName, VT_ARRAY);
	CVariableInfo* mainParams =  new CVariableInfo( "String", p.GetArgsName(), false);
	(*mainClass).AddLocalVar( mainParams );

	// почему то, то что добавляет в таблицу здесь не видит в main
	table[p.GetNameFirst()] = mainClass;
	//table.insert( std::pair<std::string, CClassInfo*>( p.GetNameFirst(), mainClass ) );

	p.GetStmt()->Accept( this );

}

void CSTVisitor::Visit( const CClassDeclList& p )//ClassDeclList
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() != 0 ) {
		p.GetList()->Accept( this );
	}
}

void CSTVisitor::Visit( const CClassDecl& p ) //class id { VarDeclList MethodDeclList }
{

	assert( currentMethod == 0 ); 
	//assert( currentClass == 0 ); // класс внутри класса не объявляем (если мы внутри, то вылетем) (?)

	CClassInfo* clazz = new CClassInfo( p.GetName(), "" );
	currentClass = clazz;

	if( p.GetMethodDeclList() != 0 ) {
		p.GetMethodDeclList()->Accept( this );
	}
	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}

	if( table.find( p.GetName() ) == table.end() ) {
		table.insert( std::make_pair( p.GetName(), clazz ) );
	} else {
		errorsStack.push( CNameRedefinition( p.GetName(), p.GetLocation() ) );
	}
	currentClass = 0;
}

void CSTVisitor::Visit( const CExtendClassDecl& p ) //class id extends id { VarDeclList MethodDeclList }
{
	assert( currentMethod == 0 ); 
	//assert( currentClass == 0 );
	
	CClassInfo * clazz = new CClassInfo( p.GetClassName(), p.GetBaseClassName() );
	currentClass = clazz;
	
	if( p.GetMethodDeclList() != 0 ) {
		p.GetMethodDeclList()->Accept( this );
	}
	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}
	if( table.find( p.GetClassName() ) == table.end() ) {
		table.insert( std::make_pair( p.GetClassName(), clazz ) );
	} else {
		errorsStack.push( CNameRedefinition( p.GetClassName(), p.GetLocation() ) );
	}
	currentClass = 0;
}

void CSTVisitor::Visit( const CVarDecl& p ) //Type id
{ 
	assert( currentClass != 0 );
	// (TODO?) может не работать не тестировал
	CVariableInfo* variable = new CVariableInfo( p.GetType()->GetName(), p.GetName(), false );

	if( currentMethod == 0 ) {
		if( currentClass->HaveVariable( p.GetName() ) ) {
			errorsStack.push( CNameRedefinition( p.GetName(), p.GetLocation() ) );
		} else {
			currentClass->AddLocalVar( variable );
		}
	} else {
		if( currentMethod->HaveInArgs( p.GetName() ) || currentMethod->HaveLocalVar( p.GetName() ) )  {
			errorsStack.push( CNameRedefinition( p.GetName(), p.GetLocation() ) );
		} else {
			currentMethod->AddLocalVar( variable );			
		}
	}
}

void CSTVisitor::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
	// (TODO?)
	CMethodInfo* method = new CMethodInfo( p.GetType()->GetName(), p.GetName() );
	currentMethod = method;

	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}

	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}
	currentClass->AddMethod( method );
	currentMethod = 0;	
}

void CSTVisitor::Visit( const CFormalList& p )//Type Id FormalRestList
{
	assert( currentMethod != 0 ); 
	CVariableInfo* variable = new CVariableInfo( p.GetType()->GetName(), p.GetName(), false );
	currentMethod->AddArgument( variable );
	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}	
}


void CSTVisitor::Visit( const CVarDeclList& p )
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}

void CSTVisitor::Visit( const CMethodDeclList& p )
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}


void CSTVisitor::Visit( const CStmtList& p )
{
	p.GetStmt()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}


void CSTVisitor::Visit( const CGroupStmt& p ) //{ Statement* }
{
}

void CSTVisitor::Visit( const CIfStmt& p ) //if ( Exp ) Statement else Statement
{
}

void CSTVisitor::Visit( const CWhileStmt& p )//while ( Exp ) Statement
{
}

void CSTVisitor::Visit( const CSOPStmt& p )//System.out.println ( Exp ) ;
{
}

void CSTVisitor::Visit( const CAssignStmt& p )//id = Exp ;
{
}

void CSTVisitor::Visit( const CAssignExprStmt& p )//id [ Exp ] = Exp;
{
}

void CSTVisitor::Visit( const COpExpr& p )//Exp op Exp
{
}

void CSTVisitor::Visit( const CExExpr& p )//Exp [ Exp ]
{
}

void CSTVisitor::Visit( const CMethodCallExpr& p )//Exp . id ( ExpList )
{
}

void CSTVisitor::Visit( const CIntExpr& p )//num
{
}

void CSTVisitor::Visit( const CTrueExpr& p )//true
{
}

void CSTVisitor::Visit( const CFalseExpr& p )//false
{
}

void CSTVisitor::Visit( const CNameExpr& p )//id
{
}

void CSTVisitor::Visit( const CThisExpr& p )//this
{
}

void CSTVisitor::Visit( const CNewIntExpr& p )//new int [ Exp ]
{
}

void CSTVisitor::Visit( const CNewIdExpr& p )//new id ()
{
}

void CSTVisitor::Visit( const CNotExpr& p )//! Exp
{
}

void CSTVisitor::Visit( const CBrExpr& p )//( Exp )
{
}

void CSTVisitor::Visit( const CTypeName& p )// id
{
}


void CSTVisitor::Visit( const CExprList& p )//Exp , ExpList
{
}
 
void CSTVisitor::Visit( const CIdExpr& p )
{
}


void CSTVisitor::Visit( const CLengthExpr& p ) // Expr . length
{
}

void CSTVisitor::Visit( const CUnaryMinusExpr& p ) // - Expr
{
}