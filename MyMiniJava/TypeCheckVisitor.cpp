#pragma once
#include "ClassInfo.h"
#include <map>
#include <utility>
#include "TypeCheckVisitor.h"
#include "syntaxTree.h"
#include <cassert>
#include <set>
#include <algorithm>

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

	if( isCyclicInheritance( p.GetClassName() ) ) {
		errorsStack.push( new CCyclicInheritance( p.GetClassName(), p.GetLocation() ) );
	}

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

	// проверка: можем ли объявить переменную данного типа

	const CTypeName* retType = static_cast<const CTypeName*>( p.GetType() );
	//не POD-тип && нет в таблице
	if( !retType->isPOD() && table.find( p.GetType()->GetName() ) == table.end() ) {
		errorsStack.push( new CNoSuchType( retType->GetName(), retType->GetLocation() ) ); 	
	}
}

void CTCVisitor::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
	for( auto &item : currentClass->GetMethods() ) {
		if( item->GetName() == p.GetName() ) {
			currentMethod = item;
		}
	}

	assert( currentMethod != 0 );
	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}

	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}

	const CTypeName* retType = static_cast<const CTypeName*>( p.GetType() );
	if( !retType->isPOD() && !haveClass( p.GetType()->GetName() ) ) {
		errorsStack.push( new CNoSuchType( retType->GetName(), retType->GetLocation() ) );
	}

	currentMethod = 0;	
}

void CTCVisitor::Visit( const CFormalList& p )//Type Id FormalRestList
{
	assert( currentMethod != 0 ); 
	const CTypeName* type = static_cast<const CTypeName*>( p.GetType() );
	if( !type->isPOD() && !haveClass( type->GetName() ) ) {
		errorsStack.push( new CNoSuchType( type->GetName(), type->GetLocation() ) );
	}

	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}	
}

void CTCVisitor::Visit( const CVarDeclList& p )
{
	const CTypeName* type = static_cast<const CTypeName*>( static_cast< const CVarDecl* >( p.GetCurrent() )->GetType() );
	if( !type->isPOD() && !haveClass( type->GetName() ) ) {
		errorsStack.push( new CNoSuchType( type->GetName(), type->GetLocation() ) );
	}

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
	if( p.GetStmtList( ) ) {
		p.GetStmtList( )->Accept( this );
	}
}

void CTCVisitor::Visit( const CIfStmt& p ) //if ( Exp ) Statement else Statement
{
	p.GetExp( )->Accept( this );
	p.GetStmFirst( )->Accept( this );
	p.GetStmSecond()->Accept( this );
}

void CTCVisitor::Visit( const CWhileStmt& p )//while ( Exp ) Statement
{
	p.GetExpr()->Accept( this );
	p.GetStmt()->Accept( this );
}

void CTCVisitor::Visit( const CSOPStmt& p )//System.out.println ( Exp ) ;
{
	p.GetExpr()->Accept( this );
}

void CTCVisitor::Visit( const CAssignStmt& p )//id = Exp ;
{
	p.GetExpr()->Accept( this );
}

void CTCVisitor::Visit( const CAssignExprStmt& p )//id [ Exp ] = Exp;
{	
	p.GetExprId()->Accept( this );
	p.GetExprValue()->Accept( this );
}

void CTCVisitor::Visit( const COpExpr& p )//Exp op Exp
{
	p.GetExprFirst()->Accept( this );
	p.GetExprSecond()->Accept( this );
}

void CTCVisitor::Visit( const CExExpr& p )//Exp [ Exp ]
{
	p.GetExpId()->Accept( this );
	p.GetExp()->Accept( this );
}

void CTCVisitor::Visit( const CMethodCallExpr& p )//Exp . id ( ExpList )
{
	p.GetExp( )->Accept( this );
	if( p.GetExprList() ) {
		p.GetExprList( )->Accept( this );
	}

	//CMethodInfo* info = findMethodInClass( p.GetName(), currentClass );
	//assert( info != 0 );
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
	p.GetExpr( )->Accept( this );
}

void CTCVisitor::Visit( const CNewIdExpr& p )//new id ()
{

}

void CTCVisitor::Visit( const CNotExpr& p )//! Exp
{
	p.GetExpr( )->Accept( this );
}

void CTCVisitor::Visit( const CBrExpr& p )//( Exp )
{
	p.GetExpr( )->Accept( this );
}

void CTCVisitor::Visit( const CTypeName& p )// id
{
	if( !currentMethod->HaveInArgs( p.GetName() ) && !currentMethod->HaveLocalVar( p.GetName() ) )
	{
		if( !currentClass->HaveVariable( p.GetName() ) ) {
			errorsStack.push( new CNoSuchVariable( p.GetName(), p.GetLocation() ) );
		}
	}
}


void CTCVisitor::Visit( const CExprList& p )//Exp , ExpList
{
	// выражения записанные через запятую (,)
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList( )->Accept( this );
	}
}
 

void CTCVisitor::Visit( const CIdExpr& p ) // id
{
	if( !haveIdInScope( p.GetId() ) ) {
		errorsStack.push( new CNoSuchVariable( p.GetId(), p.GetLocation() ) );
	}
}


void CTCVisitor::Visit( const CLengthExpr& p ) // Expr . length
{
	p.GetExp()->Accept( this );
}

void CTCVisitor::Visit( const CUnaryMinusExpr& p ) // - Expr
{
	p.GetExpr()->Accept( this );
}

bool CTCVisitor::isCyclicInheritance( const std::string& id ) {
	CClassInfo* vertex = findClass( id );
	std::hash_set< std::string > used;
	while( vertex != 0 && vertex->GetExtendedName() != "" ) {
		if( used.find( vertex->GetExtendedName() ) != used.end() ) {
			return true; //нашли цикл
		} else {
			used.insert( vertex->GetExtendedName() );
			vertex = findClass( vertex->GetExtendedName() );
		}
	}
	return false;
}

CMethodInfo* CTCVisitor::findMethodInClass( const std::string& methodName, const CClassInfo* clazz )
{
	const CClassInfo* ptr = clazz;
	while( clazz != 0 ) {
		for( auto& item : clazz->GetMethods() ) {
			if( item->GetName() == methodName ) {
				return item;
			}
		}
		if( clazz->GetExtendedName() == "" ) {
			break;
		} else {
			clazz = findClass( clazz->GetExtendedName() );
		}
	}
	return 0;
}

bool CTCVisitor::haveClass( const std::string& id ) {
	return table.find( id ) != table.end();
}

CClassInfo* CTCVisitor::findClass( const std::string& id ) {
	auto iter = table.find( id );
	return ( iter == table.end() ) ? 0 : iter->second;
}

bool CTCVisitor::haveIdInScope( const std::string& id ) {
	//простая проверка есть ли переменная с таким id
	if( currentClass->HaveVariable( id ) || currentMethod->HaveInArgs( id ) || 
		currentMethod->HaveLocalVar( id ) ) { 
			return true;
	}
	//на самом деле переменная могла быть определена в родительском классе
	if( !isCyclicInheritance( currentClass->GetName() ) ) {
		CClassInfo* root = currentClass;
		while ( root->GetExtendedName() != "" ) {
			CClassInfo* parent = findClass( root->GetExtendedName() );
			if( parent == 0 ) {
				return false; // скорее все произошла ошибка, класс не был найден.							
			} else {
				if( parent->HaveVariable( id ) ) {
					return true;	//нашли			
				} else {
					root = parent; 	//поробуем поискать у родителя			
				}
			}
		}
	}
	return false; //поиск закончился а мы ничего не нашли.
}