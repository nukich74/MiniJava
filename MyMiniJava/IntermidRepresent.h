//Borin Pavel
//IR classes

#pragma once
#include "Temp.h"
#include "grammar.h"
#include "ConstantsAndComClasses.h"

//Для вывовда дерева нужно будет ещё Print добавить
namespace IRTree 
{

class CConst: public IExpr {
public:
	CConst( int _value ): value(_value) {};

	const int value;
};

class CName: public IExpr {
public:
	CName( Temp::CLabel* _label ): label(_label) {};

	const Temp::CLabel* label;	
};

class CTemp: public IExpr {
public:
	CTemp( Temp::CTemp* _temp ): temp(_temp) {};

	const Temp::CTemp* temp;
};

class CBinop: public IExpr {
public:
	CBinop( BinOp _oper, IExpr* _left, IExpr* _right ):
		oper(_oper),
		left(_left),
		right(_right) 
	{};

	const BinOp oper;
	const IExpr *left, *right;
};

class CMem: public IExpr {
public:
	CMem( IExpr* _expr ): expr(_expr) {};

	const IExpr* expr;
};

class CCall: public IExpr {
public:
	CCall( IExpr* _func, IExprList* _args ): func(_func), args(_args) {}; 

	const IExpr* func;
	const IExprList* args;

};

class CEseq: public IExpr {
public:
	CEseq( IStmt* _stm, IExpr* _expr ): stm(_stm), expr(_expr) {};

	const IStmt* stm;
	const IExpr* expr;
};

class CMove: public IStmt {
public:
	CMove( IExpr* _dst, IExpr* _src ): dst(_dst), src(_src) {};

	const IExpr *dst, *src;
};

class CExp: public IStmt {
public:
	CExp( IExpr* _exp ): exp(_exp) {};

	const IExpr* exp;
};


class CJump: public IStmt {
public:
	CJump( Temp::CLabel* _label ): label(_label) {};

	const Temp::CLabel* label;
};


class CCJump: public IStmt {
public:
	CCJump( BinOp _relop, IExpr* _left, IExpr* _right,
		Temp::CLabel* _ifTrue, Temp::CLabel* _ifFalse ):
			relop(_relop),
			left(_left),
			right(_right),
			ifTrue(_ifTrue),
			ifFalse(_ifFalse) {};

	const BinOp relop;
	const IExpr* left, *right;
	const Temp::CLabel *ifTrue, *ifFalse;
};

class CSeq: public IStmt {
public:
	CSeq( IStmt* _left, IStmt* _right ):
		left(_left),
		right(_right) {};

	const IStmt *left, *right;
};

class CLabel: public IStmt {
public:
	CLabel( Temp::CLabel* _label ): label(_label) {};

	const Temp::CLabel* label;
};

}