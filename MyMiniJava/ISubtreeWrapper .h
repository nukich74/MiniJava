#include "IntermidRepresent.h"


namespace Translate {

class ISubtreeWrapper {
public:
	virtual ~ISubtreeWrapper() { };
	virtual const IRTree::IExpr* ToExp() const = 0; // как Expr
	virtual const IRTree::IStmt* ToStm() const = 0; // как Stm
	virtual const IRTree::IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0; // как if/jump
};

}