//Borin Pavel
//IR classes

#pragma once
#include "Temp.h"
#include "ConstantsAndComClasses.h"

//Для вывовда дерева нужно будет ещё Print добавить
namespace IRTree 
{

class CExprList;
class CStmtList;

class IExprList {
public:
	virtual ~IExprList() {}
//	virtual void Accept( IVisitor* ) const = 0;
};

class IStmtList {
public:
	virtual ~IStmtList() {}
//	virtual void Accept( IVisitor* ) const = 0;
};

class IStmt {
public:
	virtual ~IStmt() {}
//	virtual void Accept( IVisitor* ) const = 0;
	virtual const CExprList* Kids() const = 0;
	virtual const IStmt* Build( const CExprList* ) const = 0;
};

class IExpr {
public:
	virtual ~IExpr() {}
//	virtual void Accept( IVisitor* ) const = 0;
	virtual const CExprList* Kids() const = 0;
	virtual const IExpr* Build( const CExprList* ) const = 0;
};

class CConst: public IExpr {
public:
	CConst( const int _value ): value(_value) {};
//	virtual void Accept( IVisitor* ) const {};

	virtual const CExprList* Kids() const
	{
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
	}
	const int value;
};

class CName: public IExpr {
public:
	CName( const Temp::CLabel* _label ): label(_label) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
	}
//	virtual void Accept( IVisitor* ) const {};
	const Temp::CLabel* label;	
};

class CTemp: public IExpr {
public:
	CTemp( const Temp::CTemp* _temp ): temp(_temp) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
	}

//	virtual void Accept( IVisitor* ) const {};
	const Temp::CTemp* temp;
};

class CBinop: public IExpr {
public:
	CBinop( const BinOp _oper, const IExpr* _left, const IExpr* _right ):
		oper(_oper),
		left(_left),
		right(_right) 
	{};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
	}

//	virtual void Accept( IVisitor* ) const {};
	const BinOp oper;
	const IExpr *left, *right;
};

class CMem: public IExpr {
public:
	CMem( const IExpr* _expr ): expr(_expr) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
	}

//	virtual void Accept( IVisitor* ) const {};
	const IExpr* expr;
};

class CCall: public IExpr {
public:
	CCall( const IExpr* _func, const IExprList* _args ): func(_func), args(_args) {}; 
	virtual const CExprList* Kids() const
	{
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
	}

//	virtual void Accept( IVisitor* ) const {};
	const IExpr* func;
	const IExprList* args;
};

class CEseq: public IExpr {
public:
	CEseq( const IStmt* _stm, const IExpr* _expr ): stm(_stm), expr(_expr) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
	}

//	virtual void Accept( IVisitor* ) const {};
	const IStmt* stm;
	const IExpr* expr;
};

class CMove: public IStmt {
public:
	CMove( const IExpr* _dst, const IExpr* _src ): dst(_dst), src(_src) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
	}

//	virtual void Accept( IVisitor* ) const {};
	const IExpr *dst, *src;
};

class CExp: public IStmt {
public:
	CExp( const IExpr* _exp ): exp(_exp) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
	}
//	virtual void Accept( IVisitor* ) const {};
	const IExpr* exp;
};


class CJump: public IStmt {
public:
	CJump( const Temp::CLabel* _label ): label(_label) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
	}
//	virtual void Accept( IVisitor* ) const {};
	const Temp::CLabel* label;
};


class CCJump: public IStmt {
public:
	CCJump( const TEJump _relop, const IExpr* const _left, const IExpr* const _right, const
		Temp::CLabel* _ifTrue, const Temp::CLabel* _ifFalse ):
			relop(_relop),
			left(_left),
			right(_right),
			ifTrue(_ifTrue),
			ifFalse(_ifFalse) {};
	virtual const CExprList* Kids() const
	{
	}

	virtual const IStmt* Build( const CExprList* kids ) const
	{
	}

//	virtual void Accept( IVisitor* ) const {};
	const TEJump relop;
	const IExpr* left, *right;
	const Temp::CLabel *ifTrue, *ifFalse;
};

class CSeq: public IStmt {
public:
	CSeq( const IStmt* _left, const IStmt* _right, const IStmt* _last = 0 ):
		left(_left),
		right(_right), last( _last ) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
	}
//	virtual void Accept( IVisitor* ) const {};
	const IStmt *left, *right, *last;
};

class CLabel: public IStmt {
public:
	CLabel( const Temp::CLabel* _label ): label(_label) {};
	virtual const CExprList* Kids() const
	{
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
	}
//	virtual void Accept( IVisitor* ) const {};
	const Temp::CLabel* label;
};

class CExprList : public IExprList {
public:
	CExprList( const IExpr* expr, const IExprList* expList ) : 
		curExpr( expr ), nextExprs( expList )
		{};

//	virtual void Accept( IVisitor* ) const {};
	const IExpr* GetCurrent() const { return curExpr; };
	const IExprList* GetNextExprs() const { return nextExprs; };

private:
	const IExpr* curExpr;
	const IExprList* nextExprs;
};

class CStmtList : public IStmtList {
public:
	CStmtList( const IStmt* stmt, const IStmtList* stmtList ) : 
		curStmt( stmt ), nextStmts( stmtList )
		{};

//	virtual void Accept( IVisitor* ) const {};
	const IStmt* GetCurrent() const { return curStmt; };
	const IStmtList* GetNextStmts() const { return nextStmts; };
private:
	const IStmt* curStmt;
	const IStmtList* nextStmts;
};

};