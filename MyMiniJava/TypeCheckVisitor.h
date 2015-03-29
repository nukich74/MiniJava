#pragma once
#include "iVisitor.h"
#include "syntaxTree.h"
#include "ErrorMessage.h"
#include <queue>
#include <hash_set>
#include <stack>

namespace SymbolsTable {

	class CTCVisitor : public Tree::IVisitor {
	public:
		CTCVisitor( const std::map< std::string, CClassInfo* >& _table ) : table( _table ) { } 

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

		const std::map< std::string, CClassInfo* >* GetTable() const { return &table; }
		bool isSuccessfull() { return errorsStack.size() == 0; }
		const std::vector< CSemanticError* >& GetErrors() const { return errorsStack; }
	private:
		std::string lastType;
		CMethodInfo* currentMethod;
		CClassInfo* currentClass;
		std::vector< CSemanticError* > errorsStack;
		const std::map < std::string, CClassInfo* >& table;
		std::stack< std::vector< CVariableInfo* > > currentArgsStack;
		std::stack< std::string > lastTypesStorage;
		int currentArgsCount;
		bool isCyclicInheritance( const std::string& id );
		CMethodInfo* findMethodInClass( const std::string& methodName, const CClassInfo* clazz );
		CVariableInfo* findVarInScope( const std::string& id );
		CClassInfo* findClass( const std::string& id );
		bool haveClass( const std::string& id );
	};
}	




