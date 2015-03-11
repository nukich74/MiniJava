#include "IntermidRepresent.h"
#include "grammar.h"


namespace Translate {

class ISubtreeWrapper {
public:
	virtual ~ISubtreeWrapper() { };
	virtual const IExpr* ToExp() const = 0; // как Expr
	virtual const IStmt* ToStm() const = 0; // как Stm
	virtual const IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0; // как if/jump
};

}