#pragma once
#include "syntaxTree.h"
#include "stdio.h"
#include "TypeCheckVisitor.h"
#include <assert.h>
#include <iostream>

using namespace SymbolsTable;

void CTCVisitor::Visit( const CProgram& p ) //MainClass ClassDeclList
{
}

void CTCVisitor::Visit( const CMainClass& p ) //class id { public static void main ( String [] id ) { Statement }}
{
}

void CTCVisitor::Visit( const CClassDecl& p ) //class id { VarDeclList MethodDeclList }
{
}

void CTCVisitor::Visit( const CExtendClassDecl& p ) //class id extends id { VarDeclList MethodDeclList }
{
}

void CTCVisitor::Visit( const CVarDecl& p ) //Type id
{
}

void CTCVisitor::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
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
 
void CTCVisitor::Visit( const CFormalList& p )//Type Id FormalRestList
{
}


void CTCVisitor::Visit( const CClassDeclList& p )//ClassDeclList
{
}

void CTCVisitor::Visit( const CVarDeclList& p )
{
}

void CTCVisitor::Visit( const CMethodDeclList& p )
{
}


void CTCVisitor::Visit( const CStmtList& p )
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