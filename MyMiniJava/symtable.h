#pragma once
#include "iVisitor.h"
#include "grammar.h"

namespace SymbolsTable {
	

	class CClassInfo;
	class CMethodInfo;
	class CSymbolsTable;


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


	/*
	class CVariableInf {
	public:
		CVariableInf( std::string  _c, std::string _name, CVariableInf* _next );
		void addType( std::string _c );
		void addName( std::string _name );
		void addNext( CVariableInf* _next );
		std::string getType( );
		std::string getName( );
		CVariableInf* getNext( );
		void Print( );
		int Length( ) const;

	private:
		std::string c;
		std::string name;
		CVariableInf* next;
	};



	class CMethodInfo {
	public:
		CMethodInfo( std::string _c, std::string  _name, CVariableInf* _par, CVariableInf* _loc, CMethodInfo* _next );
		std::string getType( );
		std::string getName( );
		CVariableInf* getPar( );
		CVariableInf* getLoc( );
		CMethodInfo* getNext( );
		void addType( std::string _c );
		void addName( std::string _name );
		void addPar( CVariableInf* _par );
		void addLoc( CVariableInf* _loc );
		void addNext( CMethodInfo* _next );
		std::string findTVar( std::string id );
		void Print( );
		int FormalsCount( );

	private:
		std::string c;
		std::string name;
		CVariableInf* par;
		CVariableInf* loc;
		CMethodInfo* next;
	};

	class CClassInfo {
	public:
		CClassInfo( std::string _c, CVariableInf* _var, CMethodInfo* _meth, CClassInfo* _next, std::string _ext );
		void addName( std::string _c );
		void addVar( CVariableInf * _var );
		void addMeth( CMethodInfo * _meth );
		void addNext( CClassInfo * _next );
		void addExt( std::string _ext );
		std::string getName( );
		CVariableInf* getVar( );
		CMethodInfo* getMeth( );
		CClassInfo* getNext( );
		std::string getExt( );
		std::string findTVar( std::string id, CSymbolsTable* table );
		CMethodInfo* FindMethod( std::string id, CSymbolsTable* table );
		void Print( );
		bool lookUpVarOffset( std::string id, CSymbolsTable* table, int& offset );
		int getCountVar( CSymbolsTable* table );
		int findOffsetVar( std::string id, CSymbolsTable* table );
	private:
		std::string c;
		CVariableInf* var;
		CMethodInfo* meth;
		CClassInfo* next;
		std::string ext;
	};

	class CSymbolsTable {
	};
	*/

}	

