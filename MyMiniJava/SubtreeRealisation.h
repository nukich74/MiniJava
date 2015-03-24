#include "ISubtreeWrapper .h"
#include "ConstantsAndComClasses.h"
#include <assert.h>

namespace Translate {

class CExpConverter : public ISubtreeWrapper {
public:

	CExpConverter( const IRTree::IExpr* e ) : expr(e) {}
	const IRTree::IExpr* ToExp() const { return expr; }
	const IRTree::IStmt* ToStm() const { return new IRTree::CExp( expr ); }
	const IRTree::IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const;
private:
	const IRTree::IExpr* expr;
};


class CStmConverter : public ISubtreeWrapper {
public:
	CStmConverter( IRTree::IStmt* e) : expr( e ) {}
	IRTree::IExpr* ToExp() const { assert( false ); }
	IRTree::IStmt* ToStm() const { return expr; }
	IRTree::IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { 
		assert( false );
	}
private:
	IRTree::IStmt* expr;
};

//По словам семинариста, у нас только && и < 
class CConditionalWrapper : public ISubtreeWrapper {
	const IRTree::IExpr* ToExp() const;
	const IRTree::IStmt* ToStm() const;
};

class CAndWrapper : public CConditionalWrapper {
public:
	CAndWrapper( const IRTree::IExpr* _left, const IRTree::IExpr* _right ): left(_left), right(_right) {};
	const IRTree::IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f);
private:
	const IRTree::IExpr* left;
	const IRTree::IExpr* right;
};

class CLessWrapper : public CConditionalWrapper {
public:
	CLessWrapper( const IRTree::IExpr* _left, const IRTree::IExpr* _right ): left(_left), right(_right) {};
	const IRTree::IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f );
private:
	const IRTree::IExpr* left;
	const IRTree::IExpr* right;
};

}
