#include "iVisitor.h"
#include <vector>
#include <list>
#include "StackFrame.h"
#include <map>
#include <vector>


namespace Translate {

class CIRTreeVisitor: public IVisitor {
public:
	//нужно передавать таблицу символов
	CIRTreeVisitor(): currentFrame( 0 ), lastReturnedExp( 0 ), 
		lastReturnedStm( 0 ), lastReturnedAccess( 0 ), lastReturnedExpList( 0 ) {}

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

	// Каждой функции соответствует фрейм, его мы используем для поиска аргументов, типов и тд
	std::list< StackFrame::CFrame* > functions;
private:

	// Фрейм функции конструируемой в данный момент
	StackFrame::CFrame* currentFrame;
	
	// Таблица символов для программы. Ее используем для конструирования фрейма при входе в функци

	// Нужно для того чтобы в CFrame записать правильно декорированное имя
	std::string className;

	std::map<const std::string, const IType*> typesAndVariables;
	const IExpr* lastReturnedExp;
	const IStmt* lastReturnedStm;
	const IExprList* lastReturnedExpList;
	const IStmtList* lastReturnedStmtList;
	const StackFrame::IAccess* lastReturnedAccess;

};

}