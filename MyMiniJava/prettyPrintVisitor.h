#pragma once
#include "iVisitor.h"
#include "syntaxTree.h"
 
class PrettyPrintVisitor: public Tree::IVisitor
{
public:
	void Visit( const Tree::CProgram& p );
	void Visit( const Tree::CMainClass& p );

	void Visit( const Tree::CClassDecl& p );
	void Visit( const Tree::CExtendClassDecl& p );
	void Visit( const Tree::CVarDecl& p );
	void Visit( const Tree::CMethodDecl& p );

	void Visit( const Tree::CGroupStmt& p );
	void Visit( const Tree::CIfStmt& p );
	void Visit( const Tree::CWhileStmt& p );
	void Visit( const Tree::CSOPStmt& p );
	void Visit( const Tree::CAssignStmt& p );
	void Visit( const Tree::CAssignExprStmt& p );

	void Visit( const Tree::COpExpr& p );
	void Visit( const Tree::CExExpr& p );
	void Visit( const Tree::CMethodCallExpr& p );
	void Visit( const Tree::CIntExpr& p );
	void Visit( const Tree::CTrueExpr& p );
	void Visit( const Tree::CFalseExpr& p );
	void Visit( const Tree::CNameExpr& p );
	void Visit( const Tree::CThisExpr& p );
	void Visit( const Tree::CNewIntExpr& p );
	void Visit( const Tree::CNewIdExpr& p );
	void Visit( const Tree::CNotExpr& p );
	void Visit( const Tree::CBrExpr& p );
	void Visit( const Tree::CIdExpr& p );
	void Visit( const Tree::CLengthExpr& p );
	void Visit( const Tree::CUnaryMinusExpr& p );


	void Visit( const Tree::CTypeName& p );

	void Visit( const Tree::CExprList& p );
	void Visit( const Tree::CFormalList& p );
	void Visit( const Tree::CClassDeclList& p );
	void Visit( const Tree::CVarDeclList& p );
	void Visit( const Tree::CMethodDeclList& p );
	void Visit( const Tree::CStmtList& p );
};