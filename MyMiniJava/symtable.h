#pragma once
#include "iVisitor.h"
#include "grammar.h"

namespace SymbolsTable {
	class CSymbolsTable;
	class CVariableInfo;
	class CMethodInfo;
	class CClassInfo;
	
	class CSTVisitor : public IVisitor {
	public:
		void Visit( const CProgram& p );
		void Visit( const CMainClass& p );

		void Visit( const CClassDecl& p );
		void Visit( const CExtendClassDecl& p );
		void Visit( const CVarDecl& p );
		void Visit( const CMethodDecl& p );

		void Visit( const CGroupStmt& p );
		void Visit( const CIfStmt& p );
		void Visit( const CWhileStmt& p );
		void Visit( const CSOPStmt& p );
		void Visit( const CAssignStmt& p );
		void Visit( const CAssignExprStmt& p );

		void Visit( const COpExpr& p );
		void Visit( const CExExpr& p );
		void Visit( const CMethodCallExpr& p );
		void Visit( const CIntExpr& p );
		void Visit( const CTrueExpr& p );
		void Visit( const CFalseExpr& p );
		void Visit( const CNameExpr& p );
		void Visit( const CThisExpr& p );
		void Visit( const CNewIntExpr& p );
		void Visit( const CNewIdExpr& p );
		void Visit( const CNotExpr& p );
		void Visit( const CBrExpr& p );

		void Visit( const CTypeName& p );

		void Visit( const CExprList& p );
		void Visit( const CFormalList& p );
		void Visit( const CClassDeclList& p );
		void Visit( const CVarDeclList& p );
		void Visit( const CMethodDeclList& p );
		void Visit( const CStmtList& p );
	private:
		CClassInfo* currentMethod;
		CMethodInfo* currentClass;
		CSymbolsTable* currentVariable;
	};
}	