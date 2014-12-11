#pragma once
#include "SymbolTable.h"
#include "SymVisitor.h"

using namespace SymbolsTable;

void CSTVisitor::Visit( const CProgram& p ) //MainClass ClassDeclList
{
}

void CSTVisitor::Visit( const CMainClass& p ) //class id { public static void main ( String [] id ) { Statement }}
{
}

void CSTVisitor::Visit( const CClassDecl& p ) //class id { VarDeclList MethodDeclList }
{
}

void CSTVisitor::Visit( const CExtendClassDecl& p ) //class id extends id { VarDeclList MethodDeclList }
{
}

void CSTVisitor::Visit( const CVarDecl& p ) //Type id
{
}

void CSTVisitor::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
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
 
void CSTVisitor::Visit( const CFormalList& p )//Type Id FormalRestList
{
}


void CSTVisitor::Visit( const CClassDeclList& p )//ClassDeclList
{
}

void CSTVisitor::Visit( const CVarDeclList& p )
{
}

void CSTVisitor::Visit( const CMethodDeclList& p )
{
}


void CSTVisitor::Visit( const CStmtList& p )
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