//Borin Pavel
//IR classes

#pragma once
#include <assert.h>
#include "Temp.h"
#include "ConstantsAndComClasses.h"
#include "IRPrint.h"

//Для вывовда дерева нужно будет ещё Print добавить
namespace IRTree 
{

class IExpr;
class IStmt;

class IExprList {
public:
	virtual ~IExprList() {}
	virtual void Accept( IRTreePrinter* p ) const = 0;
};

class IStmtList {
public:
	virtual ~IStmtList() {}
	virtual void Accept( IRTreePrinter* p ) const = 0;
};


class CExprList : public IExprList {
public:
	CExprList( const IExpr* expr, const IExprList* expList ) : 
		curExpr( expr ), nextExprs( expList )
		{};

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
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

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const IStmt* GetCurrent() const { return curStmt; };
	const IStmtList* GetNextStmts() const { return nextStmts; };
private:
	const IStmt* curStmt;
	const IStmtList* nextStmts;
};

class IStmt {
public:
	virtual ~IStmt() {}
	virtual void Accept( IRTreePrinter* p ) const = 0;
	virtual const CExprList* Kids() const = 0;
	virtual const IStmt* Build( const CExprList* ) const = 0;
};

class IExpr {
public:
	virtual ~IExpr() {}
	virtual void Accept( IRTreePrinter* p ) const = 0;
	virtual const CExprList* Kids() const = 0;
	virtual const IExpr* Build( const CExprList* ) const = 0;
};

class CConst: public IExpr {
public:
	CConst( const int _value ): value(_value) {};
	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); };

	virtual const CExprList* Kids() const
	{
		return 0;
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
		return this;
	}
	const int value;
};

class CName: public IExpr {
public:
	CName( const Temp::CLabel* _label ): label(_label) {};
	virtual const CExprList* Kids() const
	{
		return 0;
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
		return this;
	}
	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const Temp::CLabel* label;	
};

class CTemp: public IExpr {
public:
	CTemp( const Temp::CTemp* _temp ): temp(_temp) {};
	virtual const CExprList* Kids() const
	{
		return 0;
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
		return this;
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
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
		return new CExprList( left, new CExprList( right, 0 ) );
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
		return new CBinop( oper, kids->GetCurrent(), static_cast<const IRTree::CExprList*>( kids->GetNextExprs() )->GetCurrent() );
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const BinOp oper;
	const IExpr *left, *right;
};

class CMem: public IExpr {
public:
	CMem( const IExpr* _expr ): expr(_expr) {};
	virtual const CExprList* Kids() const
	{
		return new CExprList( expr, 0 );
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
		return new CMem( kids->GetCurrent() );
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const IExpr* expr;
};

class CCall: public IExpr {
public:
	CCall( const IExpr* _func, const IExprList* _args ): func(_func), args(_args) {}; 
	virtual const CExprList* Kids() const
	{
		return new CExprList( func, args );
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
		return new CCall( kids->GetCurrent(), kids->GetNextExprs() );
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const IExpr* func;
	const IExprList* args;
};

class CEseq: public IExpr {
public:
	CEseq( const IStmt* _stm, const IExpr* _expr ): stm(_stm), expr(_expr) {};
	virtual const CExprList* Kids() const
	{
		assert( false );
		return 0;
	}
	virtual const IExpr* Build( const CExprList* kids ) const
	{
		assert( false );
		return 0;
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const IStmt* stm;
	const IExpr* expr;
};

class CMove: public IStmt {
public:
	CMove( const IExpr* _dst, const IExpr* _src ): dst(_dst), src(_src) {};
	virtual const CExprList* Kids() const
	{
		return new CExprList( dst, new CExprList( src, 0 ) );
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
		return new CMove( kids->GetCurrent(), static_cast<const CExprList*>( kids->GetNextExprs() )->GetCurrent() );
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const IExpr *dst, *src;
};

class CExp: public IStmt {
public:
	CExp( const IExpr* _exp ): exp(_exp) {};
	virtual const CExprList* Kids() const
	{
		return new CExprList( exp, 0 );
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
		return new CExp( kids->GetCurrent() );
	}
	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const IExpr* exp;
};


class CJump: public IStmt {
public:
	CJump( const Temp::CLabel* _label ): label(_label) {};
	virtual const CExprList* Kids() const
	{
		return 0;
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
		return new CJump( label );
	}
	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
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
	
	static TEJump BuildNotCondition( TEJump relop ) {
		switch( relop ) {
			case CJ_EQ:  return CJ_NE;
			case CJ_NE:  return CJ_EQ;
			case CJ_LT:  return CJ_GE;
			case CJ_GE:  return CJ_LT;
			case CJ_GT:  return CJ_LE;
			case CJ_LE:  return CJ_GT;
			case CJ_ULT: return CJ_UGE;
			case CJ_UGE: return CJ_ULT;
			case CJ_UGT: return CJ_ULE;
			case CJ_ULE: return CJ_UGT;
			default:
				assert( false );
		}
	}

	virtual const CExprList* Kids() const
	{
		return new CExprList( left, new CExprList( right, 0) );
	}

	virtual const IStmt* Build( const CExprList* kids ) const
	{
		return new CCJump( relop, kids->GetCurrent(), 
			static_cast<const CExprList*>( kids->GetNextExprs() )->GetCurrent(), ifTrue, ifFalse );
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
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
		assert( false );
		return 0;
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
		assert( false );
		return 0;
	}

	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const IStmt *left, *right, *last;
};

class CLabel: public IStmt {
public:
	CLabel( const Temp::CLabel* _label ): label(_label) {};
	virtual const CExprList* Kids() const
	{
		return 0;
	}
	virtual const IStmt* Build( const CExprList* kids ) const
	{
		return new CLabel( label );
	}
	virtual void Accept( IRTreePrinter* p ) const { p->Visit( *this ); }
	const Temp::CLabel* label;
};



};