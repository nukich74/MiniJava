#include "iVisitor.h"
#include <vector>
#include <list>
#include "StackFrame.h"
#include "grammar.h"
#include <map>
#include <vector>


namespace Translate {

class CIRTreeVisitor: public Tree::IVisitor {
public:
	//нужно передавать таблицу символов
	CIRTreeVisitor(): currentFrame( 0 ), lastReturnedExp( 0 ), 
		lastReturnedStm( 0 ), lastReturnedAccess( 0 ), lastReturnedExpList( 0 ) {}

	//IVisitor
	virtual void Visit( const Tree::CProgram& p );
	virtual void Visit( const Tree::CMainClass& p );
	virtual void Visit( const Tree::CClassDecl& p );
	virtual void Visit( const Tree::CClassDeclList& p );

	virtual void Visit( const Tree::CExtendClassDecl& p );
	virtual void Visit( const Tree::CVarDecl& p );

	virtual void Visit( const Tree::CMethodDecl& p );
	virtual void Visit( const Tree::CGroupStmt& p );
	virtual void Visit( const Tree::CIfStmt& p );
	virtual void Visit( const Tree::CWhileStmt& p );
	virtual void Visit( const Tree::CSOPStmt& p );
	virtual void Visit( const Tree::CAssignStmt& p );
	virtual void Visit( const Tree::CAssignExprStmt& p );

	virtual void Visit( const Tree::COpExpr& p );
	virtual void Visit( const Tree::CExExpr& p );
	virtual void Visit( const Tree::CMethodCallExpr& p );
	virtual void Visit( const Tree::CIntExpr& p );
	virtual void Visit( const Tree::CTrueExpr& p );
	virtual void Visit( const Tree::CFalseExpr& p );
	virtual void Visit( const Tree::CThisExpr& p );
	virtual void Visit( const Tree::CNewIntExpr& p );
	virtual void Visit( const Tree::CNewIdExpr& p );
	virtual void Visit( const Tree::CNotExpr& p );
	virtual void Visit( const Tree::CBrExpr& p );
	virtual void Visit( const Tree::CNameExpr& p );
	virtual void Visit( const Tree::CIdExpr& p );
	virtual void Visit( const Tree::CLengthExpr& p ); 
	virtual void Visit( const Tree::CUnaryMinusExpr& p );

	virtual void Visit( const Tree::CTypeName& p );

	virtual void Visit( const Tree::CExprList& p );
	virtual void Visit( const Tree::CFormalList& p );
	virtual void Visit( const Tree::CVarDeclList& p );
	virtual void Visit( const Tree::CMethodDeclList& p );
	virtual void Visit( const Tree::CStmtList& p );

	// Каждой функции соответствует фрейм, его мы используем для поиска аргументов, типов и тд
	std::list< StackFrame::CFrame* > functions;
private:

	// Фрейм функции конструируемой в данный момент
	StackFrame::CFrame* currentFrame;
	
	// Таблица символов для программы. Ее используем для конструирования фрейма при входе в функци

	// Нужно для того чтобы в CFrame записать правильно декорированное имя
	std::string className;

	std::map<const std::string, const Tree::IType*> typesAndVariables;
	const IRTree::IExpr* lastReturnedExp;
	const IRTree::IStmt* lastReturnedStm;
	const IRTree::IExprList* lastReturnedExpList;
	const IRTree::IStmtList* lastReturnedStmtList;
	const StackFrame::IAccess* lastReturnedAccess;

};

}