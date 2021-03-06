﻿#pragma once
#include "syntaxTree.h"
#include "stdio.h"
#include "prettyPrintVisitor.h"
#include <assert.h>
#include <iostream>

using namespace Tree;

std::string identt( "   " );

void PrettyPrintVisitor::Visit( const CProgram& p ) //MainClass ClassDeclList
{
	p.GetMainClass()->Accept( this );
	if( p.GetClassDeclList() ){
		p.GetClassDeclList( )->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CMainClass& p ) //class id { public static void main ( String [] id ) { Statement }}
{
	printf( "class %s { \n%spublic static Void main ( String [] %s ) { \n", p.GetName().c_str(), identt.c_str( ), p.GetArgsName( ).c_str( ) );
	identt += "    ";
	p.GetStmt()->Accept( this );
	identt = identt.substr( 0, identt.length( ) - 4 );
	printf( "%s}\n}\n", identt.c_str( ) );
}

void PrettyPrintVisitor::Visit( const CClassDecl& p ) //class id { VarDeclList MethodDeclList }
{
	identt = "";
	printf( "\n%sclass %s { \n", identt.c_str( ), p.GetName().c_str( ) );
	identt += "    ";
	if( p.GetVarDeclList( ) ) {
		p.GetVarDeclList( )->Accept( this );
	}
	if( p.GetMethodDeclList( ) ) {
		p.GetMethodDeclList( )->Accept( this );
	}
	printf( "\n}\n" );
}

void PrettyPrintVisitor::Visit( const CExtendClassDecl& p ) //class id extends id { VarDeclList MethodDeclList }
{
	identt = "";
	printf( "\n%sclass %s extends %s { \n", identt.c_str( ), p.GetClassName( ).c_str( ), p.GetBaseClassName( ).c_str( ) );
	identt += "    ";
	if( p.GetVarDeclList( ) ) {
		p.GetVarDeclList( )->Accept( this );
	}
	if( p.GetMethodDeclList( ) ) {
		p.GetMethodDeclList( )->Accept( this );
	}
	printf( "\n}\n" );
}

void PrettyPrintVisitor::Visit( const CVarDecl& p ) //Type id
{
	std::cout << identt.c_str( );
	p.GetType()->Accept( this );
	std::cout << ' ' << p.GetName().c_str( ) << " ;\n";
}

void PrettyPrintVisitor::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
	std::cout << identt.c_str( ) << "public ";
	p.GetType( )->Accept( this );
	std::cout << " " << p.GetName() << " ( ";
	if( p.GetFormalList( ) ) {
		p.GetFormalList( )->Accept( this );
	}
	printf( ") { \n" );
	identt += "    ";
	if( p.GetVarDeclList( ) ) {
		p.GetVarDeclList( )->Accept( this );
	}
	if( p.GetStmList( ) ) {
		p.GetStmList( )->Accept( this );
	}
	printf( "\n%sreturn ", identt.c_str( ) );
	p.GetExp( )->Accept( this );
	identt = identt.substr( 0, identt.length( ) - 4 );
	printf( ";\n%s}\n", identt.c_str( ) );
	//identt = identt.substr(0,identt.length() - 4);
}

void PrettyPrintVisitor::Visit( const CGroupStmt& p ) //{ Statement* }
{
	printf( "%s{\n", identt.c_str( ) );
	identt += "    ";
	if( p.GetStmtList( ) ) {
		p.GetStmtList( )->Accept( this );
	}
	identt = identt.substr( 0, identt.length( ) - 4 );
	printf( "%s}\n", identt.c_str( ) );
	identt = identt.substr( 0, identt.length( ) - 4 );
}

void PrettyPrintVisitor::Visit( const CIfStmt& p ) //if ( Exp ) Statement else Statement
{
	std::string idtCopy( identt );
	printf( "%sif ( ", identt.c_str( ) );
	p.GetExp( )->Accept( this );
	printf( " )\n" );
	identt += "    ";
	p.GetStmFirst( )->Accept( this );
	identt = idtCopy;
	printf( "%selse\n", identt.c_str( ) );
	identt += "    ";
	p.GetStmSecond()->Accept( this );
	identt = identt.substr( 0, identt.length( ) - 4 );
}

void PrettyPrintVisitor::Visit( const CWhileStmt& p )//while ( Exp ) Statement
{
	printf( "%swhile ( ", identt.c_str( ) );
	p.GetExpr()->Accept( this );
	printf( " )\n" );
	identt += "    ";
	p.GetStmt()->Accept( this );
	identt.substr( 0, identt.length( ) - 4 );
}

void PrettyPrintVisitor::Visit( const CSOPStmt& p )//System.out.println ( Exp ) ;
{
	printf( "%sSystem.out.println ( ", identt.c_str( ) );
	p.GetExpr()->Accept( this );
	printf( " ) ;\n" );
}

void PrettyPrintVisitor::Visit( const CAssignStmt& p )//id = Exp ;
{
	printf( "%s%s = ", identt.c_str( ), p.GetName().c_str( ) );
	p.GetExpr()->Accept( this );
	printf( ";\n" );
}

void PrettyPrintVisitor::Visit( const CAssignExprStmt& p )//id [ Exp ] = Exp;
{
	printf( "%s%s [ ", identt.c_str( ), p.GetName().c_str( ) );
	p.GetExprId()->Accept( this );
	printf( " ] = " );
	p.GetExprValue()->Accept( this );
	printf( ";\n" );
}

void PrettyPrintVisitor::Visit( const COpExpr& p )//Exp op Exp
{
	p.GetExprFirst()->Accept( this );
	switch ( p.GetOp() )
	{
		case BO_And:
			std::cout << " && ";
			break;
		case BO_Div:
			std::cout << " / ";
			break;
		case BO_Less:
			std::cout << " < ";
			break;
		case BO_Minus:
			std::cout << " - ";
			break;		
		case BO_Mult:
			std::cout << " * ";
			break;
		case BO_Plus:
			std::cout << " + ";
			break;
		default:
			assert( false );
			break;
	}
	p.GetExprSecond()->Accept( this );
}

void PrettyPrintVisitor::Visit( const CExExpr& p )//Exp [ Exp ]
{
	p.GetExpId()->Accept( this );
	printf( "[ " );
	p.GetExp()->Accept( this );
	printf( " ] " );
}

void PrettyPrintVisitor::Visit( const CMethodCallExpr& p )//Exp . id ( ExpList )
{
	p.GetExp( )->Accept( this );
	printf( ". %s ( ", p.GetName().c_str( ) );
	if( p.GetExprList() ) {
		p.GetExprList( )->Accept( this );
	}
	printf( " )" );
}

void PrettyPrintVisitor::Visit( const CIntExpr& p )//num
{
	printf( "%d", p.GetNum( ) );
}

void PrettyPrintVisitor::Visit( const CTrueExpr& p )//true
{
	printf( "true" );
}

void PrettyPrintVisitor::Visit( const CFalseExpr& p )//false
{
	printf( "false" );
}

void PrettyPrintVisitor::Visit( const CThisExpr& p )//this
{
	printf( "this" );
}

void PrettyPrintVisitor::Visit( const CNewIntExpr& p )//new int [ Exp ]
{
	printf( "new int [ " );
	p.GetExpr( )->Accept( this );
	printf( " ]" );
}

void PrettyPrintVisitor::Visit( const CNewIdExpr& p )//new id ()
{
	printf( "new %s ()", p.GetName( ).c_str( ) );
}

void PrettyPrintVisitor::Visit( const CNotExpr& p )//! Exp
{
	printf( "! " );
	p.GetExpr( )->Accept( this );
}

void PrettyPrintVisitor::Visit( const CBrExpr& p )//( Exp )
{
	printf( "( " );
	p.GetExpr( )->Accept( this );
	printf( " )" );
}

void PrettyPrintVisitor::Visit( const CTypeName& p )// id
{
	std::cout << p.GetName();
}


void PrettyPrintVisitor::Visit( const CExprList& p )//Exp , ExpList
{
	p.GetCurrent()->Accept( this );
	std::cout << " ";
	if( p.GetList() ) {
		std::cout << ", ";
		p.GetList( )->Accept( this );
	}
}
 
void PrettyPrintVisitor::Visit( const CFormalList& p )//Type Id FormalRestList
{
	p.GetType()->Accept(this);
	std::cout << " " << p.GetName() << " ";
	if( p.GetFormalList( ) ) {
		std::cout << ", ";
		p.GetFormalList( )->Accept( this );
	}
}


void PrettyPrintVisitor::Visit( const CClassDeclList& p )//ClassDeclList
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CVarDeclList& p )
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CMethodDeclList& p )
{
	p.GetCurrent()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}


void PrettyPrintVisitor::Visit( const CStmtList& p )
{
	p.GetStmt()->Accept( this );
	if( p.GetList() ) {
		p.GetList()->Accept( this );
	}
}


void PrettyPrintVisitor::Visit( const CIdExpr& p )
{
	std::cout << " " << p.GetId() << " ";
}


void PrettyPrintVisitor::Visit( const CLengthExpr& p ) // Expr . length
{
	p.GetExp()->Accept( this );
	std::cout << ". length";

}

void PrettyPrintVisitor::Visit( const CUnaryMinusExpr& p ) // - Expr
{
	std::cout << "-";
	p.GetExpr()->Accept( this );
}