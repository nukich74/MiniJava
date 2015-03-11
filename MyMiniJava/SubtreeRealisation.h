#include "ISubtreeWrapper .h"
#include "ConstantsAndComClasses.h"
#include <assert.h>

namespace Translate {

class CExpConverter : public ISubtreeWrapper {
public:

	CExpConverter( const IExpr* e ) : expr(e) {}
	const IExpr* ToExp() const { return expr; }
	const IStmt* ToStm() const { return new IRTree::CExp( expr ); }
	const IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const;
private:
	const IExpr* expr;
};


class CStmConverter : public ISubtreeWrapper {
public:
	CStmConverter( IStmt* e) : expr( e ) {}
	IExpr* ToExp() const { assert( false ); }
	IStmt* ToStm() const { return expr; }
	IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { 
		assert( false );
	}
private:
	IStmt* expr;
};

//По словам семинариста, у нас только && и < 
class CConditionalWrapper : public ISubtreeWrapper {
	const IExpr* ToExp() const;
	const IStmt* ToStm() const;
};

class CAndWrapper : public CConditionalWrapper {
public:
	CAndWrapper( const IExpr* _left, const IExpr* _right ): left(_left), right(_right) {};
	const IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f);
private:
	const IExpr* left;
	const IExpr* right;
};

class CLessWrapper : public CConditionalWrapper {
public:
	CLessWrapper( const IExpr* _left, const IExpr* _right ): left(_left), right(_right) {};
	const IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f );
private:
	const IExpr* left;
	const IExpr* right;
};


}
