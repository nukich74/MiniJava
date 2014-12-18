#pragma once
#include "iVisitor.h"
#include "syntaxTree.h"
#include "ErrorMessage.h"
#include <queue>

namespace SymbolsTable {

	class CTCVisitor : public IVisitor {
	public:
		CTCVisitor( const std::map< std::string, CClassInfo* >& _table ) : table( _table ) { } 

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
		void Visit( const CIdExpr& p );
		void Visit( const CLengthExpr& p );
		void Visit( const CUnaryMinusExpr& p );


		void Visit( const CTypeName& p );
		void Visit( const CExprList& p );
		void Visit( const CFormalList& p );
		void Visit( const CClassDeclList& p );
		void Visit( const CVarDeclList& p );
		void Visit( const CMethodDeclList& p );
		void Visit( const CStmtList& p );

		
		const std::map< std::string, CClassInfo* >* GetTable() const { return &table; }
		bool isSuccessfull() { return errorsStack.size() > 0; }

	private:
		CMethodInfo* currentMethod;
		CClassInfo* currentClass;
		const std::map < std::string, CClassInfo* >& table;
		std::queue< CSemanticError > errorsStack;
	};
}	




