//Борин, Столбов
#pragma once
#include "iVisitor.h" 
#include"IntermidRepresent.h"
#include"grammar.h"
#include "IRHelpers.h"
#include <list>
//#include <SymbolsTable.h>
#include "StackFrame.h"

namespace IRTranslate {

	class CIRTreeVisitor : public IVisitor {
	public:

		//IVisitor
		virtual void Visit( const CProgram& p );
		virtual void Visit( const CMainClass& p );
		virtual void Visit( const CClassDecl& p );
		virtual void Visit( const CClassDeclList& p );

		virtual void Visit( const CExtendClassDecl& p );
		virtual void Visit( const CVarDecl& p );

		virtual void Visit( const CMethodDecl& p );
		virtual void Visit( const CGroupStmt& p );
		virtual void Visit( const CIfStmt& p );
		virtual void Visit( const CWhileStmt& p );
		virtual void Visit( const CSOPStmt& p );
		virtual void Visit( const CAssignStmt& p );
		virtual void Visit( const CAssignExprStmt& p );

		virtual void Visit( const COpExpr& p );
		virtual void Visit( const CExExpr& p );
		virtual void Visit( const CMethodCallExpr& p );
		virtual void Visit( const CIntExpr& p );
		virtual void Visit( const CTrueExpr& p );
		virtual void Visit( const CFalseExpr& p );
		virtual void Visit( const CThisExpr& p );
		virtual void Visit( const CNewIntExpr& p );
		virtual void Visit( const CNewIdExpr& p );
		virtual void Visit( const CNotExpr& p );
		virtual void Visit( const CBrExpr& p );
		virtual void Visit( const CNameExpr& p );
		virtual void Visit( const CIdExpr& p );
		virtual void Visit( const CLengthExpr& p );
		virtual void Visit( const CUnaryMinusExpr& p );

		virtual void Visit( const CTypeName& p );

		virtual void Visit( const CExprList& p );
		virtual void Visit( const CFormalList& p );
		virtual void Visit( const CVarDeclList& p );
		virtual void Visit( const CMethodDeclList& p );
		virtual void Visit( const CStmtList& p );

	private:

		StackFrame::CFrame* currentFrame;

		//const SymbolsTable::CSymbolsTable& symbolsTable;

		std::string className;

		const IExpr* lastReturnedExp;
		const IStmt* lastReturnedStm;
		const StackFrame::IAccess* lastReturnedAccess;

	};
}